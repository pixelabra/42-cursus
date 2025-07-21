/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands.hpp"
#include "Utils.hpp"

Server* Server::_instance = NULL;

Server::Server(int port, const std::string& password) : _port(port), _password(password),
                                                        _serverName("ircserv"), _serverSocket(-1),
                                                        _commands(NULL), _running(false)
{
    _instance = this;
    _commands = new Commands(this);
}

Server::~Server()
{
    stop();
    cleanupClients();
    cleanupChannels();
    
    if (_commands)
        delete _commands;
    
    if (_serverSocket != -1)
        close(_serverSocket);
}

bool Server::start()
{
    if (!setupSocket())
        return false;
    
    setupSignalHandlers();
    
    // Add server socket to poll set
    struct pollfd serverPfd;
    serverPfd.fd = _serverSocket;
    serverPfd.events = POLLIN;
    serverPfd.revents = 0;
    _pollFds.push_back(serverPfd);
    
    _running = true;
    std::cout << "IRC Server started on port " << _port << std::endl;
    
    return true;
}

void Server::run()
{
    while (_running)
    {
        // Poll for events
        int pollResult = poll(&_pollFds[0], _pollFds.size(), -1);
        
        if (pollResult < 0)
        {
            if (errno == EINTR)
                continue; // Interrupted by signal, continue
            
            std::cerr << "Poll error: " << strerror(errno) << std::endl;
            break;
        }
        
        // Check all file descriptors
        for (size_t i = 0; i < _pollFds.size(); ++i)
        {
            if (_pollFds[i].revents & POLLIN)
            {
                if (_pollFds[i].fd == _serverSocket)
                {
                    // New client connection
                    acceptNewClient();
                }
                else
                {
                    // Client data available
                    Client* client = getClientByFd(_pollFds[i].fd);
                    if (client)
                        handleClientData(client);
                }
            }
            
            if (_pollFds[i].revents & POLLOUT)
            {
                // Client ready for writing
                Client* client = getClientByFd(_pollFds[i].fd);
                if (client)
                    handleClientWrite(client);
            }
            
            if (_pollFds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
            {
                // Client disconnected or error
                if (_pollFds[i].fd != _serverSocket)
                {
                    Client* client = getClientByFd(_pollFds[i].fd);
                    if (client)
                        disconnectClient(client);
                }
            }
        }
    }
}

void Server::stop()
{
    _running = false;
    std::cout << "IRC Server stopping..." << std::endl;
}

void Server::acceptNewClient()
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    if (clientSocket < 0)
    {
        std::cerr << "Accept error: " << strerror(errno) << std::endl;
        return;
    }
    
    // Set non-blocking
    int flags = fcntl(clientSocket, F_GETFL, 0);
    fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
    
    // Create client object
    Client* client = new Client(clientSocket);
    client->setHostname(inet_ntoa(clientAddr.sin_addr));
    
    _clients[clientSocket] = client;
    
    // Add to poll set
    struct pollfd clientPfd;
    clientPfd.fd = clientSocket;
    clientPfd.events = POLLIN;
    clientPfd.revents = 0;
    _pollFds.push_back(clientPfd);
    
    std::cout << "New client connected: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
}

void Server::handleClientData(Client* client)
{
    char buffer[4096];
    ssize_t bytesRead = recv(client->getFd(), buffer, sizeof(buffer) - 1, 0);
    
    if (bytesRead <= 0)
    {
        if (bytesRead == 0)
            std::cout << "Client " << client->getNickname() << " disconnected" << std::endl;
        else if (errno != EAGAIN && errno != EWOULDBLOCK)
            std::cerr << "Recv error: " << strerror(errno) << std::endl;
        
        disconnectClient(client);
        return;
    }
    
    buffer[bytesRead] = '\0';
    client->appendToBuffer(std::string(buffer, bytesRead));
    
    // Process complete messages
    std::string line;
    while (!(line = client->extractLine()).empty())
    {
        processClientMessage(client, line);
    }
}

void Server::handleClientWrite(Client* client)
{
    const std::string& sendBuffer = client->getSendBuffer();
    if (sendBuffer.empty())
    {
        // Update poll events to remove POLLOUT
        for (size_t i = 0; i < _pollFds.size(); ++i)
        {
            if (_pollFds[i].fd == client->getFd())
            {
                _pollFds[i].events = POLLIN;
                break;
            }
        }
        return;
    }
    
    ssize_t bytesSent = send(client->getFd(), sendBuffer.c_str(), sendBuffer.length(), 0);
    
    if (bytesSent > 0)
    {
        client->clearSendBuffer(bytesSent);
        
        // If buffer is empty, remove POLLOUT event
        if (client->getSendBuffer().empty())
        {
            for (size_t i = 0; i < _pollFds.size(); ++i)
            {
                if (_pollFds[i].fd == client->getFd())
                {
                    _pollFds[i].events = POLLIN;
                    break;
                }
            }
        }
    }
    else if (bytesSent < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        std::cerr << "Send error: " << strerror(errno) << std::endl;
        disconnectClient(client);
    }
}

void Server::disconnectClient(Client* client)
{
    if (!client)
        return;
    
    int fd = client->getFd();
    
    // Remove from channels
    const std::set<std::string>& channels = client->getChannels();
    for (std::set<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        leaveChannel(client, *it);
    }
    
    // Remove from poll set
    for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it)
    {
        if (it->fd == fd)
        {
            _pollFds.erase(it);
            break;
        }
    }
    
    // Close socket and cleanup
    close(fd);
    delete client;
    _clients.erase(fd);
}

Client* Server::getClientByFd(int fd)
{
    std::map<int, Client*>::iterator it = _clients.find(fd);
    return (it != _clients.end()) ? it->second : NULL;
}

Client* Server::getClientByNickname(const std::string& nickname)
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getNickname() == nickname)
            return it->second;
    }
    return NULL;
}

Channel* Server::getChannel(const std::string& name)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    return (it != _channels.end()) ? it->second : NULL;
}

Channel* Server::createChannel(const std::string& name)
{
    Channel* channel = new Channel(name);
    _channels[name] = channel;
    return channel;
}

void Server::removeChannel(const std::string& name)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end())
    {
        delete it->second;
        _channels.erase(it);
    }
}

void Server::joinChannel(Client* client, const std::string& channelName)
{
    Channel* channel = getChannel(channelName);
    if (!channel)
        channel = createChannel(channelName);
    
    channel->addMember(client->getNickname());
    client->joinChannel(channelName);
}

void Server::leaveChannel(Client* client, const std::string& channelName)
{
    Channel* channel = getChannel(channelName);
    if (!channel)
        return;
    
    channel->removeMember(client->getNickname());
    client->leaveChannel(channelName);
    
    // Remove empty channel
    if (channel->getMemberCount() == 0)
        removeChannel(channelName);
}

const std::map<std::string, Channel*>& Server::getChannels() const
{
    return _channels;
}

void Server::sendToClient(Client* client, const std::string& message)
{
    if (!client)
        return;
    
    client->appendToSendBuffer(message);
    
    // Add POLLOUT event if not already set
    for (size_t i = 0; i < _pollFds.size(); ++i)
    {
        if (_pollFds[i].fd == client->getFd())
        {
            _pollFds[i].events = POLLIN | POLLOUT;
            break;
        }
    }
}

void Server::broadcastToChannel(const std::string& channelName, const std::string& message, Client* exclude)
{
    Channel* channel = getChannel(channelName);
    if (!channel)
        return;
    
    const std::set<std::string>& members = channel->getMembers();
    for (std::set<std::string>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        Client* client = getClientByNickname(*it);
        if (client && client != exclude)
            sendToClient(client, message);
    }
}

const std::string& Server::getPassword() const
{
    return _password;
}

const std::string& Server::getServerName() const
{
    return _serverName;
}

void Server::signalHandler(int signal)
{
    if (signal == SIGINT || signal == SIGTERM)
    {
        if (_instance)
            _instance->stop();
    }
}

bool Server::setupSocket()
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
    {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        return false;
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "Setsockopt failed: " << strerror(errno) << std::endl;
        close(_serverSocket);
        return false;
    }
    
    // Set non-blocking
    int flags = fcntl(_serverSocket, F_GETFL, 0);
    fcntl(_serverSocket, F_SETFL, flags | O_NONBLOCK);
    
    // Bind
    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);
    
    if (bind(_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        close(_serverSocket);
        return false;
    }
    
    // Listen
    if (listen(_serverSocket, 10) < 0)
    {
        std::cerr << "Listen failed: " << strerror(errno) << std::endl;
        close(_serverSocket);
        return false;
    }
    
    return true;
}

void Server::setupSignalHandlers()
{
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGPIPE, SIG_IGN); // Ignore broken pipe signals
}

void Server::cleanupClients()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        close(it->first);
        delete it->second;
    }
    _clients.clear();
}

void Server::cleanupChannels()
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        delete it->second;
    }
    _channels.clear();
}

void Server::processClientMessage(Client* client, const std::string& message)
{
    if (message.empty())
        return;
    
    std::cout << "Received from " << client->getNickname() << ": " << message << std::endl;
    
    if (_commands)
        _commands->processCommand(client, message);
}
