/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:14:02 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:33:31 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <cstring>

class Client;
class Channel;
class Parser;
class Commands;
class FileTransfer;
class Bot;

class Server {
private:
    int _serverSocket;
    int _port;
    std::string _password;
    std::vector<struct pollfd> _pollFds;
    std::map<int, Client*> _clients;
    std::map<std::string, Channel*> _channels;
    Parser* _parser;
    Commands* _commands;
    Bot* _bot;
    bool _running;
    int _clientCounter;

    void setupSocket();
    void acceptNewClient();
    void handleClientData(int clientFd);
    void disconnectClient(int clientFd);
    void cleanupPollFds();

public:
    Server(int port, const std::string& password);
    ~Server();
    
    void run();
    void shutdown();
    
    // getters
    const std::string& getPassword() const { return _password; }
    std::map<int, Client*>& getClients() { return _clients; }
    std::map<std::string, Channel*>& getChannels() { return _channels; }
    Client* getClient(int fd);
    Client* getClientByNick(const std::string& nick);
    Channel* getChannel(const std::string& name);
    Channel* createChannel(const std::string& name, Client* creator);
    Bot* getBot() { return _bot; }
    
    // util
    void sendToClient(int clientFd, const std::string& message);
    void broadcastToChannel(const std::string& channelName, const std::string& message, Client* sender = NULL);
    void broadcastQuitMessage(Client* client, const std::string& quitMsg);
    void removeClientFromChannels(Client* client);
};

#endif
