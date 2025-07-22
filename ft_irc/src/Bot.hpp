#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <vector>
#include <map>

class Server;
class Client;

class Bot {
private:
    Server* _server;
    std::string _botNick;
    std::map<std::string, std::string> _responses;
    std::vector<std::string> _helpCommands;
    
    void initializeResponses();
    void sendBotMessage(Client* client, const std::string& message);
    void sendBotMessage(const std::string& channel, const std::string& message);
    
    // Bot command handlers
    void handleHelpCommand(Client* client, const std::string& channel);
    void handleTimeCommand(Client* client, const std::string& channel);
    void handleJokeCommand(Client* client, const std::string& channel);
    void handleQuoteCommand(Client* client, const std::string& channel);
    void handleStatsCommand(Client* client, const std::string& channel);
    void handleWeatherCommand(Client* client, const std::string& channel, const std::string& args);
    
public:
    Bot(Server* server);
    ~Bot();
    
    // Main processing function
    void processMessage(Client* client, const std::string& target, const std::string& message);
    
    // Bot management
    bool isBotCommand(const std::string& message);
    std::string getBotNick() const { return _botNick; }
};

#endif
