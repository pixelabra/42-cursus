#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>

class Client;
class Channel;
class IRCParser;
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
    IRCParser* _parser;
    Commands* _commands;
    FileTransfer* _fileTransfer;
    Bot* _bot;
    bool _running;
    int _clientCounter;  // For numbering clients

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
    
    // Getters
    const std::string& getPassword() const { return _password; }
    std::map<int, Client*>& getClients() { return _clients; }
    std::map<std::string, Channel*>& getChannels() { return _channels; }
    Client* getClient(int fd);
    Client* getClientByNick(const std::string& nick);
    Channel* getChannel(const std::string& name);
    Channel* createChannel(const std::string& name, Client* creator);
    FileTransfer* getFileTransfer() { return _fileTransfer; }
    Bot* getBot() { return _bot; }
    
    // Utility functions
    void sendToClient(int clientFd, const std::string& message);
    void broadcastToChannel(const std::string& channelName, const std::string& message, Client* sender = NULL);
    void broadcastQuitMessage(Client* client, const std::string& quitMsg);
    void removeClientFromChannels(Client* client);
};

#endif
