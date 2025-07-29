#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRCParser.hpp"
#include "Commands.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
#include "Colors.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <cstring>

Server::Server(int port, const std::string& password) : _serverSocket(-1), _port(port), _password(password), _parser(NULL), _commands(NULL), _fileTransfer(NULL), _bot(NULL), _running(false), _clientCounter(0) {
    try {
        _parser = new IRCParser();
        _commands = new Commands(this);
        _fileTransfer = new FileTransfer(this);
        _bot = new Bot(this);
        setupSocket();
    } catch (...) {
        // Clean up any allocated objects if setupSocket fails
        delete _parser;
        delete _commands;
        delete _fileTransfer;
        delete _bot;
        throw; // Re-throw the exception
    }
}

Server::~Server() {
    if (_serverSocket != -1) {
        close(_serverSocket);
    }
    
    // Clean up clients
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        delete it->second;
    }
    
    // Clean up channels
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        delete it->second;
    }
    
    // Safe delete (handles NULL pointers)
    delete _parser;
    delete _commands;
    delete _fileTransfer;
    delete _bot;
}

void Server::setupSocket() {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    // Set socket to non-blocking
    int flags = fcntl(_serverSocket, F_GETFL, 0);
    if (flags == -1 || fcntl(_serverSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
        close(_serverSocket);
        throw std::runtime_error("Failed to set socket to non-blocking");
    }

    // Set SO_REUSEADDR
    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to set socket options");
    }

    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);

    if (bind(_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(_serverSocket, 10) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to listen on socket");
    }

    // Add server socket to poll fds
    struct pollfd pfd;
    pfd.fd = _serverSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "IRC Server started on port " << _port << std::endl;
}

void Server::run() {
    _running = true;
    while (_running) {
        int pollResult = poll(&_pollFds[0], _pollFds.size(), 100); // 100ms timeout
        if (pollResult < 0) {
            break; // Exit gracefully on error
        }

        for (size_t i = 0; i < _pollFds.size() && _running; ++i) {
            if (_pollFds[i].revents & POLLIN) {
                if (_pollFds[i].fd == _serverSocket) {
                    acceptNewClient();
                } else {
                    handleClientData(_pollFds[i].fd);
                }
            }
            if (_pollFds[i].revents & (POLLHUP | POLLERR)) {
                if (_pollFds[i].fd != _serverSocket) {
                    disconnectClient(_pollFds[i].fd);
                }
            }
        }
        cleanupPollFds();
    }
}

void Server::acceptNewClient() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    
    int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
    if (clientSocket < 0) {
        return; // Non-blocking, so this is normal
    }

    // Set client socket to non-blocking
    // int flags = fcntl(clientSocket, F_GETFL, 0);
    // if (flags == -1 || fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
    //     close(clientSocket);
    //     return;
    // }
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
        close(clientSocket);
        return;
    }

    // Create client object with incremented counter
    _clientCounter++;
    Client* newClient = new Client(clientSocket, inet_ntoa(clientAddr.sin_addr), _clientCounter);
    _clients[clientSocket] = newClient;

    // Add to poll fds
    struct pollfd pfd;
    pfd.fd = clientSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "New client connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;
}

void Server::handleClientData(int clientFd) {
    char buffer[512];  // IRC RFC 2812 standard: 512 bytes max per message
    ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesRead <= 0) {
        disconnectClient(clientFd);
        return;
    }

    buffer[bytesRead] = '\0';
    Client* client = getClient(clientFd);
    if (!client) {
        return;
    }

    // Add to client's buffer with length check
    std::string incomingData(buffer, bytesRead);
    
    // Reject if client buffer would exceed IRC limits
    if (client->getBuffer().length() + incomingData.length() > 512) {
        // Don't add oversized data, just process what we have
        std::cout << "Rejecting oversized message from client " << client->getClientNumber() << std::endl;
    } else {
        client->addToBuffer(incomingData);
    }
    
    // Process complete commands
    std::string command;
    while (client->getNextCommand(command)) {
        if (client->getNickname().empty()) {
            std::cout << CYAN << "Client " << client->getClientNumber() << RESET << " sent: " << BOLD << command << RESET << std::endl;
        } else {
            std::cout << CYAN << "Client " << client->getClientNumber() << " " << client->getNickname() << RESET << " sent: " << BOLD << command << RESET << std::endl;
        }
        
        IRCMessage msg = _parser->parseMessage(command);
        _commands->processCommand(client, msg);
    }
}

void Server::disconnectClient(int clientFd) {
    Client* client = getClient(clientFd);
    if (client) {
        std::cout << "Client " << client->getNickname() << " disconnected" << std::endl;
        removeClientFromChannels(client);
        delete client;
        _clients.erase(clientFd);
    }
    close(clientFd);
}

void Server::cleanupPollFds() {
    for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ) {
        if (it->fd != _serverSocket && _clients.find(it->fd) == _clients.end()) {
            it = _pollFds.erase(it);
        } else {
            ++it;
        }
    }
}

Client* Server::getClient(int fd) {
    std::map<int, Client*>::iterator it = _clients.find(fd);
    return (it != _clients.end()) ? it->second : NULL;
}

Client* Server::getClientByNick(const std::string& nick) {
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nick) {
            return it->second;
        }
    }
    return NULL;
}

Channel* Server::getChannel(const std::string& name) {
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    return (it != _channels.end()) ? it->second : NULL;
}

Channel* Server::createChannel(const std::string& name, Client* creator) {
    Channel* channel = new Channel(name, creator);
    _channels[name] = channel;
    return channel;
}

void Server::sendToClient(int clientFd, const std::string& message) {
    std::string fullMessage = message + "\r\n";
    ssize_t result = send(clientFd, fullMessage.c_str(), fullMessage.length(), 0);
    if (result < 0) {
        // Client might have disconnected, handle gracefully
        std::cout << "Failed to send message to client " << clientFd << std::endl;
    }
}

void Server::broadcastToChannel(const std::string& channelName, const std::string& message, Client* sender) {
    Channel* channel = getChannel(channelName);
    if (!channel) {
        return;
    }

    const std::vector<Client*>& members = channel->getMembers();
    for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (*it != sender) {
            sendToClient((*it)->getFd(), message);
        }
    }
}

void Server::broadcastQuitMessage(Client* client, const std::string& quitMsg) {
    // Broadcast quit message to all channels the client is in
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        Channel* channel = it->second;
        if (channel->isMember(client)) {
            broadcastToChannel(it->first, quitMsg, client);
        }
    }
}

void Server::removeClientFromChannels(Client* client) {
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ) {
        Channel* channel = it->second;
        channel->removeMember(client);
        
        if (channel->getMembers().empty()) {
            delete channel;
            std::map<std::string, Channel*>::iterator toErase = it;
            ++it;
            _channels.erase(toErase);
        } else {
            ++it;
        }
    }
}

void Server::shutdown() {
    _running = false;
    
    // Send QUIT messages to all clients and close their connections
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
    }
    
    // Close server socket
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }
    
    std::cout << "Server shutdown complete." << std::endl;
}
