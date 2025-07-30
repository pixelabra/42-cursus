#include "FileTransfer.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>

// Static member initialization
uint16_t FileTransfer::_nextPort = 1024;

FileTransfer::FileTransfer(Server* server) : _server(server) {
}

FileTransfer::~FileTransfer() {
    // Clean up all active sessions
    for (std::map<std::string, DCCSession>::iterator it = _activeSessions.begin();
         it != _activeSessions.end(); ++it) {
        closeDCCSession(it->first);
    }
    _activeSessions.clear();
}

std::string FileTransfer::getSessionKey(const std::string& sender, const std::string& receiver, const std::string& filename) {
    return sender + "_" + receiver + "_" + filename;
}

uint32_t FileTransfer::ipStringToLong(const std::string& ip) {
    // Convert "127.0.0.1" to decimal form (2130706433)
    std::istringstream iss(ip);
    std::string octet;
    std::vector<int> octets;
    
    while (std::getline(iss, octet, '.')) {
        octets.push_back(atoi(octet.c_str()));
    }
    
    if (octets.size() != 4) {
        return 2130706433; // Default to 127.0.0.1
    }
    
    return (static_cast<uint32_t>(octets[0]) << 24) |
           (static_cast<uint32_t>(octets[1]) << 16) |
           (static_cast<uint32_t>(octets[2]) << 8) |
           static_cast<uint32_t>(octets[3]);
}

std::string FileTransfer::ipLongToString(uint32_t ip) {
    std::ostringstream oss;
    oss << ((ip >> 24) & 0xFF) << "." 
        << ((ip >> 16) & 0xFF) << "." 
        << ((ip >> 8) & 0xFF) << "." 
        << (ip & 0xFF);
    return oss.str();
}

uint16_t FileTransfer::getNextAvailablePort() {
    if (_nextPort >= 65535) {
        _nextPort = 1024;
    }
    return _nextPort++;
}

bool FileTransfer::isDCCMessage(const std::string& message) {
    return message.length() > 2 && message[0] == '\x01' && message[message.length()-1] == '\x01';
}

void FileTransfer::processDCCMessage(Client* client, const std::string& target, const std::string& message) {
    if (!isDCCMessage(message)) {
        return;
    }
    
    // Remove CTCP delimiters (\x01)
    std::string dccContent = message.substr(1, message.length() - 2);
    
    // Parse DCC command: "DCC SEND filename ip port size"
    std::istringstream iss(dccContent);
    std::vector<std::string> params;
    std::string param;
    
    while (iss >> param) {
        params.push_back(param);
    }
    
    if (params.size() < 2) {
        return; // Invalid DCC message
    }
    
    // Convert command to uppercase
    std::transform(params[0].begin(), params[0].end(), params[0].begin(), ::toupper);
    std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::toupper);
    
    if (params[0] == "DCC") {
        if (params[1] == "SEND" && params.size() >= 5) {
            parseDCCSend(client, target, params);
        } else if (params[1] == "ACCEPT" && params.size() >= 4) {
            parseDCCAccept(client, params);
        } else if (params[1] == "RESUME" && params.size() >= 4) {
            parseDCCResume(client, params);
        } else if (params[1] == "CHAT" && params.size() >= 4) {
            parseDCCChat(client, target, params);
        }
    }
}

void FileTransfer::handleDCCSend(Client* sender, const std::string& target, const std::string& filename, const std::string& filepath) {
    Client* receiver = _server->getClientByNick(target);
    if (!receiver) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: Target user not found";
        _server->sendToClient(sender->getFd(), errorMsg);
        return;
    }
    
    // Determine file path and check if file exists
    std::string actualFilePath = filepath;
    if (actualFilePath.empty()) {
        actualFilePath = filename; // Use filename as path if no specific path provided
    }
    
    if (!fileExists(actualFilePath)) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: File not found: " + filename;
        _server->sendToClient(sender->getFd(), errorMsg);
        return;
    }
    
    uint32_t fileSize = getFileSize(actualFilePath);
    if (fileSize == 0) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: Unable to read file size: " + filename;
        _server->sendToClient(sender->getFd(), errorMsg);
        return;
    }
    
    // Get next available port and create server socket
    uint16_t port = getNextAvailablePort();
    int serverSocket = createDCCServer(port);
    if (serverSocket < 0) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: Cannot create server socket";
        _server->sendToClient(sender->getFd(), errorMsg);
        return;
    }
    
    // Create DCC session
    DCCSession session;
    session.filename = filename;
    session.filepath = actualFilePath;
    session.senderNick = sender->getNickname();
    session.receiverNick = receiver->getNickname();
    session.ip = ipStringToLong("127.0.0.1");
    session.port = port;
    session.fileSize = fileSize;
    session.bytesTransferred = 0;
    session.serverSocket = serverSocket;
    session.clientSocket = -1;
    session.active = true;
    session.isReceiver = false;
    session.inputFile = new std::ifstream(actualFilePath.c_str(), std::ios::binary);
    session.outputFile = NULL;
    
    if (!session.inputFile->is_open()) {
        std::string errorMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                              " :DCC SEND failed: Cannot open file for reading: " + filename;
        _server->sendToClient(sender->getFd(), errorMsg);
        delete session.inputFile;
        close(serverSocket);
        return;
    }
    
    std::string sessionKey = getSessionKey(sender->getNickname(), receiver->getNickname(), filename);
    _activeSessions[sessionKey] = session;
    
    // Send DCC SEND request to receiver
    std::ostringstream dccMsg;
    dccMsg << "\001DCC SEND " << filename << " " << session.ip << " " << session.port << " " << session.fileSize << "\001";
    std::string privMsg = ":" + sender->getPrefix() + " PRIVMSG " + receiver->getNickname() + " :" + dccMsg.str();
    _server->sendToClient(receiver->getFd(), privMsg);
    
    // Notify sender
    std::ostringstream portStr;
    portStr << session.port;
    std::string notifyMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                           " :DCC SEND " + filename + " to " + target + " initiated (port " + portStr.str() + ")";
    _server->sendToClient(sender->getFd(), notifyMsg);
    
    std::cout << "DCC SEND: " << sender->getNickname() << " -> " << target 
              << " (" << filename << ", " << fileSize << " bytes, port " << session.port << ")" << std::endl;
}

void FileTransfer::parseDCCSend(Client* client, const std::string& target, const std::vector<std::string>& params) {
    // DCC SEND filename ip port size
    if (params.size() < 5) return;
    
    std::string filename = params[2];
    uint32_t ip = static_cast<uint32_t>(atol(params[3].c_str()));
    uint16_t port = static_cast<uint16_t>(atoi(params[4].c_str()));
    uint32_t fileSize = static_cast<uint32_t>(atol(params[5].c_str()));
    
    // Create session for incoming file
    DCCSession session;
    session.filename = filename;
    session.senderNick = client->getNickname();
    session.receiverNick = target;
    session.ip = ip;
    session.port = port;
    session.fileSize = fileSize;
    session.active = false;
    
    std::string sessionKey = getSessionKey(client->getNickname(), target, filename);
    _activeSessions[sessionKey] = session;
    
    // Notify receiver that a file transfer was offered
    Client* receiver = _server->getClientByNick(target);
    if (receiver) {
        std::ostringstream msg;
        msg << ":" << client->getPrefix() << " PRIVMSG " << target 
            << " :DCC file transfer offered: " << filename 
            << " (" << fileSize << " bytes) from " << ipLongToString(ip) 
            << ":" << port;
        _server->sendToClient(receiver->getFd(), msg.str());
    }
    
    std::cout << "DCC SEND offer: " << filename << " (" << fileSize << " bytes) "
              << "from " << client->getNickname() << " to " << target << std::endl;
}

void FileTransfer::parseDCCAccept(Client* client, const std::vector<std::string>& params) {
    // DCC ACCEPT filename port position
    if (params.size() < 4) return;
    
    std::string filename = params[2];
    uint16_t port = static_cast<uint16_t>(atoi(params[3].c_str()));
    
    // Find matching session
    std::string sessionKey = "";
    for (std::map<std::string, DCCSession>::iterator it = _activeSessions.begin();
         it != _activeSessions.end(); ++it) {
        if (it->second.filename == filename && it->second.port == port &&
            it->second.receiverNick == client->getNickname()) {
            sessionKey = it->first;
            break;
        }
    }
    
    if (sessionKey.empty()) {
        std::string errorMsg = ":" + client->getPrefix() + " PRIVMSG " + client->getNickname() + 
                              " :DCC ACCEPT failed: No matching transfer found";
        _server->sendToClient(client->getFd(), errorMsg);
        return;
    }
    
    DCCSession& session = _activeSessions[sessionKey];
    
    // Set up receiver session
    session.isReceiver = true;
    std::string safeFilename = "received_" + filename;
    session.outputFile = new std::ofstream(safeFilename.c_str(), std::ios::binary);
    
    if (!session.outputFile->is_open()) {
        std::string errorMsg = ":" + client->getPrefix() + " PRIVMSG " + client->getNickname() + 
                              " :DCC ACCEPT failed: Cannot create output file";
        _server->sendToClient(client->getFd(), errorMsg);
        delete session.outputFile;
        session.outputFile = NULL;
        closeDCCSession(sessionKey);
        return;
    }
    
    // Notify both parties that transfer is starting
    Client* sender = _server->getClientByNick(session.senderNick);
    if (sender) {
        std::string senderMsg = ":" + client->getPrefix() + " PRIVMSG " + sender->getNickname() + 
                               " :DCC transfer accepted for " + filename;
        _server->sendToClient(sender->getFd(), senderMsg);
    }
    
    std::string receiverMsg = ":" + client->getPrefix() + " PRIVMSG " + client->getNickname() + 
                             " :DCC transfer starting: " + filename + " (saved as " + safeFilename + ")";
    _server->sendToClient(client->getFd(), receiverMsg);
    
    std::cout << "DCC ACCEPT: " << client->getNickname() << " accepted " << filename 
              << " from " << session.senderNick << std::endl;
    
    // Connect to sender's server socket and start transfer
    if (connectDCCClient(session.ip, session.port, sessionKey)) {
        // Start receiving data
        transferFileData(sessionKey);
    }
}

void FileTransfer::parseDCCResume(Client* client, const std::vector<std::string>& params) {
    // DCC RESUME filename port position
    if (params.size() < 5) return;
    
    std::string filename = params[2];
    uint16_t port = static_cast<uint16_t>(atoi(params[3].c_str()));
    uint32_t position = static_cast<uint32_t>(atol(params[4].c_str()));
    
    std::cout << "DCC RESUME request: " << filename << " from position " << position 
              << " (port " << port << ") by " << client->getNickname() << std::endl;
    
    // In a real implementation, would handle resume logic
    std::string resumeMsg = ":" + client->getPrefix() + " PRIVMSG " + client->getNickname() + 
                           " :DCC RESUME not implemented in this server";
    _server->sendToClient(client->getFd(), resumeMsg);
}

void FileTransfer::parseDCCChat(Client* client, const std::string& target, const std::vector<std::string>& params) {
    // DCC CHAT chat ip port
    if (params.size() < 5) return;
    
    uint32_t ip = static_cast<uint32_t>(atol(params[3].c_str()));
    uint16_t port = static_cast<uint16_t>(atoi(params[4].c_str()));
    
    std::cout << "DCC CHAT request from " << client->getNickname() << " to " << target 
              << " (" << ipLongToString(ip) << ":" << port << ")" << std::endl;
    
    // Notify target about chat request
    Client* targetClient = _server->getClientByNick(target);
    if (targetClient) {
        std::string chatMsg = ":" + client->getPrefix() + " PRIVMSG " + target + 
                             " :DCC CHAT request from " + client->getNickname() + 
                             " (DCC CHAT not fully implemented)";
        _server->sendToClient(targetClient->getFd(), chatMsg);
    }
}

int FileTransfer::createDCCServer(uint16_t port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "DCC: Failed to create socket: " << strerror(errno) << std::endl;
        return -1;
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cout << "DCC: Failed to set socket options: " << strerror(errno) << std::endl;
        close(serverSocket);
        return -1;
    }
    
    // Bind to port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    if (bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "DCC: Failed to bind to port " << port << ": " << strerror(errno) << std::endl;
        close(serverSocket);
        return -1;
    }
    
    // Listen for connections
    if (listen(serverSocket, 1) < 0) {
        std::cout << "DCC: Failed to listen: " << strerror(errno) << std::endl;
        close(serverSocket);
        return -1;
    }
    
    std::cout << "DCC: Server listening on port " << port << std::endl;
    return serverSocket;
}

bool FileTransfer::connectDCCClient(uint32_t ip, uint16_t port, const std::string& sessionKey) {
    std::map<std::string, DCCSession>::iterator it = _activeSessions.find(sessionKey);
    if (it == _activeSessions.end()) {
        return false;
    }
    
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cout << "DCC: Failed to create client socket: " << strerror(errno) << std::endl;
        return false;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port = htons(port);
    
    if (connect(clientSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "DCC: Failed to connect to " << ipLongToString(ip) << ":" << port 
                  << " - " << strerror(errno) << std::endl;
        close(clientSocket);
        return false;
    }
    
    it->second.clientSocket = clientSocket;
    std::cout << "DCC: Connected to " << ipLongToString(ip) << ":" << port << std::endl;
    return true;
}

void FileTransfer::handleDCCConnection(const std::string& sessionKey) {
    std::map<std::string, DCCSession>::iterator it = _activeSessions.find(sessionKey);
    if (it == _activeSessions.end()) {
        return;
    }
    
    DCCSession& session = it->second;
    
    if (!session.isReceiver) {
        // Handle as sender - wait for receiver to connect to our server socket
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        std::cout << "DCC: Waiting for receiver connection on port " << session.port << std::endl;
        session.clientSocket = accept(session.serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (session.clientSocket < 0) {
            std::cout << "DCC: Failed to accept connection: " << strerror(errno) << std::endl;
            closeDCCSession(sessionKey);
            return;
        }
        
        std::cout << "DCC: Receiver connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;
        
        // Start file transfer as sender
        transferFileData(sessionKey);
    }
}

void FileTransfer::transferFileData(const std::string& sessionKey) {
    std::map<std::string, DCCSession>::iterator it = _activeSessions.find(sessionKey);
    if (it == _activeSessions.end()) {
        return;
    }
    
    DCCSession& session = it->second;
    
    if (session.isReceiver) {
        // Receive file data
        char buffer[8192];
        ssize_t bytesRead;
        
        while (session.bytesTransferred < session.fileSize) {
            bytesRead = recv(session.clientSocket, buffer, sizeof(buffer), 0);
            
            if (bytesRead <= 0) {
                if (bytesRead == 0) {
                    std::cout << "DCC: Connection closed by sender" << std::endl;
                } else {
                    std::cout << "DCC: Receive error: " << strerror(errno) << std::endl;
                }
                break;
            }
            
            session.outputFile->write(buffer, bytesRead);
            session.bytesTransferred += bytesRead;
            
            std::cout << "DCC: Received " << bytesRead << " bytes (" 
                      << session.bytesTransferred << "/" << session.fileSize << ")" << std::endl;
            
            // Send acknowledgment (bytes received so far)
            uint32_t ack = htonl(session.bytesTransferred);
            send(session.clientSocket, &ack, sizeof(ack), 0);
        }
        
    } else {
        // Send file data
        char buffer[8192];
        
        while (session.bytesTransferred < session.fileSize && session.inputFile->good()) {
            session.inputFile->read(buffer, sizeof(buffer));
            std::streamsize bytesRead = session.inputFile->gcount();
            
            if (bytesRead > 0) {
                ssize_t bytesSent = send(session.clientSocket, buffer, bytesRead, 0);
                
                if (bytesSent <= 0) {
                    std::cout << "DCC: Send error: " << strerror(errno) << std::endl;
                    break;
                }
                
                session.bytesTransferred += bytesSent;
                
                std::cout << "DCC: Sent " << bytesSent << " bytes (" 
                          << session.bytesTransferred << "/" << session.fileSize << ")" << std::endl;
                
                // Wait for acknowledgment
                uint32_t ack;
                if (recv(session.clientSocket, &ack, sizeof(ack), 0) <= 0) {
                    std::cout << "DCC: Failed to receive acknowledgment" << std::endl;
                    break;
                }
                
                uint32_t ackBytes = ntohl(ack);
                std::cout << "DCC: Acknowledgment received: " << ackBytes << " bytes" << std::endl;
            }
        }
    }
    
    // Notify completion
    Client* sender = _server->getClientByNick(session.senderNick);
    Client* receiver = _server->getClientByNick(session.receiverNick);
    
    std::ostringstream completionMsg;
    completionMsg << "DCC transfer completed: " << session.filename 
                  << " (" << session.bytesTransferred << "/" << session.fileSize << " bytes)";
    
    if (sender) {
        std::string senderMsg = ":" + sender->getPrefix() + " PRIVMSG " + sender->getNickname() + " :" + completionMsg.str();
        _server->sendToClient(sender->getFd(), senderMsg);
    }
    
    if (receiver) {
        std::string receiverMsg = ":" + receiver->getPrefix() + " PRIVMSG " + receiver->getNickname() + " :" + completionMsg.str();
        _server->sendToClient(receiver->getFd(), receiverMsg);
    }
    
    std::cout << "DCC COMPLETE: " << session.senderNick << " -> " << session.receiverNick 
              << " (" << session.filename << ", " << session.bytesTransferred << " bytes)" << std::endl;
    
    // Clean up session
    closeDCCSession(sessionKey);
}

void FileTransfer::closeDCCSession(const std::string& sessionKey) {
    std::map<std::string, DCCSession>::iterator it = _activeSessions.find(sessionKey);
    if (it == _activeSessions.end()) {
        return;
    }
    
    DCCSession& session = it->second;
    
    if (session.inputFile) {
        session.inputFile->close();
        delete session.inputFile;
    }
    
    if (session.outputFile) {
        session.outputFile->close();
        delete session.outputFile;
    }
    
    if (session.serverSocket >= 0) {
        close(session.serverSocket);
    }
    
    if (session.clientSocket >= 0) {
        close(session.clientSocket);
    }
    
    _activeSessions.erase(it);
    std::cout << "DCC: Session " << sessionKey << " closed" << std::endl;
}

uint32_t FileTransfer::getFileSize(const std::string& filepath) {
    struct stat st;
    if (stat(filepath.c_str(), &st) == 0) {
        return static_cast<uint32_t>(st.st_size);
    }
    return 0;
}

bool FileTransfer::fileExists(const std::string& filepath) {
    struct stat st;
    return (stat(filepath.c_str(), &st) == 0);
}


