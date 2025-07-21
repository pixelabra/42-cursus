/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <cerrno>
# include <cstring>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <set>

class Client;
class Channel;
class Commands;

class Server
{
private:
    int _port;
    std::string _password;
    std::string _serverName;
    int _serverSocket;
    std::vector<struct pollfd> _pollFds;
    std::map<int, Client*> _clients;
    std::map<std::string, Channel*> _channels;
    Commands* _commands;
    bool _running;
    
    static Server* _instance;
    
public:
    Server(int port, const std::string& password);
    ~Server();
    
    // Core server functions
    bool start();
    void run();
    void stop();
    
    // Client management
    void acceptNewClient();
    void handleClientData(Client* client);
    void handleClientWrite(Client* client);
    void disconnectClient(Client* client);
    Client* getClientByFd(int fd);
    Client* getClientByNickname(const std::string& nickname);
    
    // Channel management
    Channel* getChannel(const std::string& name);
    Channel* createChannel(const std::string& name);
    void removeChannel(const std::string& name);
    void joinChannel(Client* client, const std::string& channelName);
    void leaveChannel(Client* client, const std::string& channelName);
    const std::map<std::string, Channel*>& getChannels() const;
    
    // Message sending
    void sendToClient(Client* client, const std::string& message);
    void broadcastToChannel(const std::string& channel, const std::string& message, Client* exclude);
    
    // Getters
    const std::string& getPassword() const;
    const std::string& getServerName() const;
    
    // Signal handling
    static void signalHandler(int signal);
    
private:
    bool setupSocket();
    void setupSignalHandlers();
    void cleanupClients();
    void cleanupChannels();
    void processClientMessage(Client* client, const std::string& message);
};

#endif
