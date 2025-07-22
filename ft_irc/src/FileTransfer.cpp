#include "FileTransfer.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

FileTransfer::FileTransfer(Server* server) : _server(server) {
}

FileTransfer::~FileTransfer() {
    // Clean up active sessions
    for (std::map<std::string, FileTransferSession>::iterator it = _sessions.begin(); 
         it != _sessions.end(); ++it) {
        if (it->second.outputFile) {
            it->second.outputFile->close();
            delete it->second.outputFile;
        }
    }
}

std::string FileTransfer::generateSessionId() {
    static int counter = 0;
    std::ostringstream oss;
    oss << "session_" << ++counter;
    return oss.str();
}

void FileTransfer::sendDCCMessage(Client* client, const std::string& message) {
    std::string dccMsg = ":" + client->getPrefix() + " PRIVMSG " + client->getNickname() + " :\x01" + message + "\x01";
    _server->sendToClient(client->getFd(), dccMsg);
}

bool FileTransfer::isDCCMessage(const std::string& message) {
    return message.length() > 2 && message[0] == '\x01' && message[message.length()-1] == '\x01';
}

void FileTransfer::processDCCMessage(Client* client, const std::string& target, const std::string& message) {
    if (!isDCCMessage(message)) {
        return;
    }
    
    // Remove CTCP delimiters
    std::string dccContent = message.substr(1, message.length() - 2);
    
    std::istringstream iss(dccContent);
    std::string command;
    iss >> command;
    
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    if (command == "DCC") {
        std::string subcommand;
        iss >> subcommand;
        std::transform(subcommand.begin(), subcommand.end(), subcommand.begin(), ::toupper);
        
        if (subcommand == "SEND") {
            std::string filename;
            size_t fileSize;
            iss >> filename >> fileSize;
            
            if (!filename.empty() && fileSize > 0) {
                handleDCCSend(client, target, filename, fileSize);
            }
        } else if (subcommand == "ACCEPT") {
            std::string filename, senderNick;
            iss >> filename >> senderNick;
            
            if (!filename.empty() && !senderNick.empty()) {
                handleDCCAccept(client, senderNick, filename);
            }
        }
    }
}

void FileTransfer::handleDCCSend(Client* sender, const std::string& target, const std::string& filename, size_t fileSize) {
    Client* receiver = _server->getClientByNick(target);
    if (!receiver) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: Target user not found";
        _server->sendToClient(sender->getFd(), errorMsg);
        return;
    }
    
    // Create transfer session
    std::string sessionId = generateSessionId();
    FileTransferSession session;
    session.filename = filename;
    session.sender = sender->getNickname();
    session.receiver = receiver->getNickname();
    session.fileSize = fileSize;
    session.bytesTransferred = 0;
    session.active = false;
    
    _sessions[sessionId] = session;
    
    // Send DCC SEND request to receiver
    std::ostringstream dccMsg;
    dccMsg << "\001DCC SEND " << filename << " " << sessionId << " " << fileSize << "\001";
    std::string privMsg = ":" + sender->getPrefix() + " PRIVMSG " + receiver->getNickname() + " :" + dccMsg.str();
    _server->sendToClient(receiver->getFd(), privMsg);
    
    // Notify sender
    std::string notifyMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                           " :DCC SEND request sent to " + target + " for " + filename;
    _server->sendToClient(sender->getFd(), notifyMsg);
    
    std::cout << "DCC SEND: " << sender->getNickname() << " -> " << target << " (" << filename << ", " << fileSize << " bytes)" << std::endl;
}

void FileTransfer::handleDCCAccept(Client* receiver, const std::string& senderNick, const std::string& filename) {
    // Find matching session
    std::string sessionId;
    for (std::map<std::string, FileTransferSession>::iterator it = _sessions.begin(); 
         it != _sessions.end(); ++it) {
        if (it->second.sender == senderNick && 
            it->second.receiver == receiver->getNickname() && 
            it->second.filename == filename) {
            sessionId = it->first;
            break;
        }
    }
    
    if (sessionId.empty()) {
        std::string errorMsg = ":" + receiver->getPrefix() + " PRIVMSG " + receiver->getNickname() + 
                              " :DCC ACCEPT failed: No matching transfer request found";
        _server->sendToClient(receiver->getFd(), errorMsg);
        return;
    }
    
    FileTransferSession& session = _sessions[sessionId];
    
    // Create output file
    std::string safeFilename = "received_" + filename;
    session.outputFile = new std::ofstream(safeFilename.c_str(), std::ios::binary);
    
    if (!session.outputFile->is_open()) {
        std::string errorMsg = ":" + receiver->getPrefix() + " PRIVMSG " + receiver->getNickname() + 
                              " :DCC ACCEPT failed: Cannot create output file";
        _server->sendToClient(receiver->getFd(), errorMsg);
        delete session.outputFile;
        session.outputFile = NULL;
        _sessions.erase(sessionId);
        return;
    }
    
    session.active = true;
    
    // Notify both parties
    Client* sender = _server->getClientByNick(session.sender);
    if (sender) {
        std::string senderMsg = ":" + receiver->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                               " :\001DCC ACCEPT " + filename + " " + sessionId + "\001";
        _server->sendToClient(sender->getFd(), senderMsg);
    }
    
    std::string receiverMsg = ":" + receiver->getPrefix() + " PRIVMSG " + receiver->getNickname() + 
                             " :DCC transfer started for " + filename + " (saving as " + safeFilename + ")";
    _server->sendToClient(receiver->getFd(), receiverMsg);
    
    std::cout << "DCC ACCEPT: " << receiver->getNickname() << " accepted transfer from " << senderNick << " (" << filename << ")" << std::endl;
    
    // Simulate file transfer completion (in a real implementation, this would handle actual data transfer)
    handleFileTransferComplete(sessionId);
}

void FileTransfer::handleFileData(const std::string& sessionId, const char* data, size_t size) {
    std::map<std::string, FileTransferSession>::iterator it = _sessions.find(sessionId);
    if (it == _sessions.end() || !it->second.active || !it->second.outputFile) {
        return;
    }
    
    FileTransferSession& session = it->second;
    
    // Write data to file
    session.outputFile->write(data, size);
    session.bytesTransferred += size;
    
    // Check if transfer is complete
    if (session.bytesTransferred >= session.fileSize) {
        handleFileTransferComplete(sessionId);
    }
}

void FileTransfer::handleFileTransferComplete(const std::string& sessionId) {
    std::map<std::string, FileTransferSession>::iterator it = _sessions.find(sessionId);
    if (it == _sessions.end()) {
        return;
    }
    
    FileTransferSession& session = it->second;
    
    // Close file
    if (session.outputFile) {
        session.outputFile->close();
        delete session.outputFile;
        session.outputFile = NULL;
    }
    
    // Notify both parties
    Client* sender = _server->getClientByNick(session.sender);
    Client* receiver = _server->getClientByNick(session.receiver);
    
    std::ostringstream completionMsg;
    completionMsg << "DCC transfer completed: " << session.filename 
                  << " (" << session.bytesTransferred << " bytes)";
    
    if (sender) {
        std::string senderMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + " :" + completionMsg.str();
        _server->sendToClient(sender->getFd(), senderMsg);
    }
    
    if (receiver) {
        std::string receiverMsg = ":" + receiver->getPrefix() + " PRIVMSG " + receiver->getNickname() + " :" + completionMsg.str();
        _server->sendToClient(receiver->getFd(), receiverMsg);
    }
    
    std::cout << "DCC COMPLETE: " << session.sender << " -> " << session.receiver << " (" << session.filename << ")" << std::endl;
    
    // Remove session
    _sessions.erase(it);
}
