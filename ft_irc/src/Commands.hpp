#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

class Server;
class Client;
struct IRCMessage;

class Commands {
private:
    Server* _server;
    
    // Authentication commands
    void cmdPass(Client* client, const IRCMessage& msg);
    void cmdNick(Client* client, const IRCMessage& msg);
    void cmdUser(Client* client, const IRCMessage& msg);
    
    // Channel commands
    void cmdJoin(Client* client, const IRCMessage& msg);
    void cmdPart(Client* client, const IRCMessage& msg);
    void cmdPrivmsg(Client* client, const IRCMessage& msg);
    void cmdNotice(Client* client, const IRCMessage& msg);
    void cmdKick(Client* client, const IRCMessage& msg);
    void cmdInvite(Client* client, const IRCMessage& msg);
    void cmdTopic(Client* client, const IRCMessage& msg);
    void cmdMode(Client* client, const IRCMessage& msg);
    
    // Utility commands
    void cmdWho(Client* client, const IRCMessage& msg);
    void cmdQuit(Client* client, const IRCMessage& msg);
    void cmdPing(Client* client, const IRCMessage& msg);
    void cmdCap(Client* client, const IRCMessage& msg);
    
    // Helper functions
    void sendWelcome(Client* client);
    void sendNumericReply(Client* client, int code, const std::string& message);
    bool isValidNickname(const std::string& nick);

public:
    Commands(Server* server);
    ~Commands();

    void processCommand(Client* client, const IRCMessage& msg);
};

#endif
