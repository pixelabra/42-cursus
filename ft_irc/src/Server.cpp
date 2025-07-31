/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:30:51 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:44:27 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Parser.hpp"
#include "Commands.hpp"
#include "Bot.hpp"
#include "Colors.hpp"

Server::Server(int port, const std::string& password) : _serverSocket(-1), _port(port), _password(password), _parser(NULL), _commands(NULL), _bot(NULL), _running(false), _clientCounter(0) {
    try {
        _parser = new Parser();
        _commands = new Commands(this);
        _bot = new Bot(this);
        setupSocket();
    } catch (...) {
        delete _parser;
        delete _commands;
        delete _bot;
        throw;
    }
}

Server::~Server() {
    if (_serverSocket != -1) {
        close(_serverSocket);
    }
    
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        delete it->second;
    }
    
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        delete it->second;
    }
    
    delete _parser;
    delete _commands;
    delete _bot;
}

void Server::setupSocket() {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1) {
        close(_serverSocket);
        throw std::runtime_error("Failed to set socket to non-blocking");
    }

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
        int pollResult = poll(&_pollFds[0], _pollFds.size(), 100);
        if (pollResult < 0) {
            break;
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
        return;
    }

    if (_clients.size() >= 10) {
        std::cout << "Connection refused: Max number of clients reached (10)" << std::endl;
        close(clientSocket);
        return;
    }

    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
        close(clientSocket);
        return;
    }

    _clientCounter++;
    Client* newClient = new Client(clientSocket, inet_ntoa(clientAddr.sin_addr), _clientCounter);
    _clients[clientSocket] = newClient;

    struct pollfd pfd;
    pfd.fd = clientSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "New client connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;
}

void Server::handleClientData(int clientFd) {
    char buffer[512];
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

    std::string incomingData(buffer, bytesRead);
    
    if (client->isIgnoringOversizedInput()) {
        if (incomingData.find('\n') != std::string::npos || incomingData.find('\r') != std::string::npos) {
            client->setIgnoreOversizedInput(false);
            std::cout << "End of oversized input detected from client " << client->getClientNumber() << " - resuming normal processing" << std::endl;
            
            size_t newlinePos = std::max(incomingData.find('\n'), incomingData.find('\r'));
            if (newlinePos != std::string::npos && newlinePos + 1 < incomingData.length()) {
                std::string remainingData = incomingData.substr(newlinePos + 1);
                if (!remainingData.empty()) {
                    client->addToBuffer(remainingData);
                }
            }
        }
        return;
    }
    
    if (client->getBuffer().length() + incomingData.length() > 512) {
        client->clearBuffer();
        client->setIgnoreOversizedInput(true);
        std::cout << "Rejecting oversized message from client " << client->getClientNumber() << " - ignoring input until newline" << std::endl;
        
        std::string errorMsg = ":ircserv 417 " + client->getNickname() + " :Input line was too long\r\n";
        send(clientFd, errorMsg.c_str(), errorMsg.length(), 0);
        return;
    }
    
    client->addToBuffer(incomingData);
    
    std::string command;
    while (client->getNextCommand(command)) {
        if (client->getNickname().empty()) {
            std::cout << CYAN << "Client " << client->getClientNumber() << RESET << " sent: " << BOLD << command << RESET << std::endl;
        } else {
            std::cout << CYAN << "Client " << client->getClientNumber() << " " << client->getNickname() << RESET << " sent: " << BOLD << command << RESET << std::endl;
        }
        
        Message msg = _parser->parseMessage(command);
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
    if (_channels.size() >= 10)
        return NULL;
    Channel* channel = new Channel(name, creator);
    _channels[name] = channel;
    return channel;
}

void Server::sendToClient(int clientFd, const std::string& message) {
    std::string fullMessage = message + "\r\n";
    ssize_t result = send(clientFd, fullMessage.c_str(), fullMessage.length(), 0);
    if (result < 0) {
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
    
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
    }
    
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }
    
    std::cout << "Server shutdown complete." << std::endl;
}
