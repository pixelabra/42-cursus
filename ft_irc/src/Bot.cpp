#include "Bot.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

Bot::Bot(Server* server) : _server(server), _botNick("IRCBot") {
    initializeResponses();
}

Bot::~Bot() {
}

void Bot::initializeResponses() {
    _responses["hello"] = "Hello there! How can I help you today?";
    _responses["hi"] = "Hi! Nice to meet you!";
    _responses["help"] = "I'm an IRC bot. Try !help for available commands.";
    _responses["thanks"] = "You're welcome!";
    _responses["thank you"] = "My pleasure!";
    
    _helpCommands.push_back("!help - Show this help message");
    _helpCommands.push_back("!time - Show current server time");
    _helpCommands.push_back("!joke - Tell a random joke");
    _helpCommands.push_back("!quote - Show an inspirational quote");
    _helpCommands.push_back("!stats - Show server statistics");
    _helpCommands.push_back("!weather <city> - Get weather info (mock)");
}

bool Bot::isBotCommand(const std::string& message) {
    return !message.empty() && (message[0] == '!' || 
           message.find(_botNick) != std::string::npos ||
           message.find("bot") != std::string::npos);
}

void Bot::processMessage(Client* client, const std::string& target, const std::string& message) {
    if (!isBotCommand(message)) {
        // Only respond to direct mentions or specific greetings to the bot
        std::string lowerMsg = message;
        std::transform(lowerMsg.begin(), lowerMsg.end(), lowerMsg.begin(), ::tolower);
        
        // Respond to greetings in private messages OR when bot is mentioned in channels
        if (target[0] != '#' || // Private message - respond to all greetings
            lowerMsg.find(_botNick) != std::string::npos || 
            lowerMsg.find("ircbot") != std::string::npos) {
            
            for (std::map<std::string, std::string>::const_iterator it = _responses.begin(); 
                 it != _responses.end(); ++it) {
                if (lowerMsg.find(it->first) != std::string::npos) {
                    if (target[0] == '#') {
                        sendBotMessage(target, client->getNickname() + ": " + it->second);
                    } else {
                        sendBotMessage(client, it->second);
                    }
                    return;
                }
            }
        }
        return;
    }
    
    // Parse command
    std::istringstream iss(message);
    std::string command;
    iss >> command;
    
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    
    if (command == "!help") {
        handleHelpCommand(client, target);
    } else if (command == "!time") {
        handleTimeCommand(client, target);
    } else if (command == "!joke") {
        handleJokeCommand(client, target);
    } else if (command == "!quote") {
        handleQuoteCommand(client, target);
    } else if (command == "!stats") {
        handleStatsCommand(client, target);
    } else if (command == "!weather") {
        std::string args;
        std::getline(iss, args);
        handleWeatherCommand(client, target, args);
    } else if (message.find(_botNick) != std::string::npos || message.find("bot") != std::string::npos) {
        std::string response = "Hello " + client->getNickname() + "! I'm " + _botNick + ". Type !help for available commands.";
        if (target[0] == '#') {
            sendBotMessage(target, response);
        } else {
            sendBotMessage(client, response);
        }
    }
}

void Bot::handleHelpCommand(Client* client, const std::string& channel) {
    std::string helpMsg = "Available bot commands:";
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + helpMsg);
        for (std::vector<std::string>::const_iterator it = _helpCommands.begin(); 
             it != _helpCommands.end(); ++it) {
            sendBotMessage(channel, *it);
        }
    } else {
        sendBotMessage(client, helpMsg);
        for (std::vector<std::string>::const_iterator it = _helpCommands.begin(); 
             it != _helpCommands.end(); ++it) {
            sendBotMessage(client, *it);
        }
    }
}

void Bot::handleTimeCommand(Client* client, const std::string& channel) {
    std::time_t now = std::time(0);
    std::string timeStr = std::ctime(&now);
    // Remove trailing newline
    if (!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
        timeStr.erase(timeStr.length()-1);
    }
    
    std::string response = "Current server time: " + timeStr;
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + response);
    } else {
        sendBotMessage(client, response);
    }
}

void Bot::handleJokeCommand(Client* client, const std::string& channel) {
    std::vector<std::string> jokes;
    jokes.push_back("Why do programmers prefer dark mode? Because light attracts bugs!");
    jokes.push_back("How do you comfort a JavaScript bug? You console it!");
    jokes.push_back("Why do Java developers wear glasses? Because they can't C#!");
    jokes.push_back("What's the best thing about Boolean? Even if you're wrong, you're only off by a bit!");
    jokes.push_back("Why did the developer go broke? Because he used up all his cache!");
    
    srand(static_cast<unsigned int>(std::time(0)));
    std::string joke = jokes[rand() % jokes.size()];
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + joke);
    } else {
        sendBotMessage(client, joke);
    }
}

void Bot::handleQuoteCommand(Client* client, const std::string& channel) {
    std::vector<std::string> quotes;
    quotes.push_back("\"The only way to do great work is to love what you do.\" - Steve Jobs");
    quotes.push_back("\"Code is like humor. When you have to explain it, it's bad.\" - Cory House");
    quotes.push_back("\"First, solve the problem. Then, write the code.\" - John Johnson");
    quotes.push_back("\"The best error message is the one that never shows up.\" - Thomas Fuchs");
    quotes.push_back("\"Programming isn't about what you know; it's about what you can figure out.\" - Chris Pine");
    
    srand(static_cast<unsigned int>(std::time(0)));
    std::string quote = quotes[rand() % quotes.size()];
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + quote);
    } else {
        sendBotMessage(client, quote);
    }
}

void Bot::handleStatsCommand(Client* client, const std::string& channel) {
    std::map<int, Client*>& clients = _server->getClients();
    std::map<std::string, Channel*>& channels = _server->getChannels();
    
    std::ostringstream stats;
    stats << "Server Statistics - Connected clients: " << clients.size() 
          << ", Active channels: " << channels.size();
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + stats.str());
    } else {
        sendBotMessage(client, stats.str());
    }
}

void Bot::handleWeatherCommand(Client* client, const std::string& channel, const std::string& args) {
    std::string city = args;
    // Remove leading/trailing whitespace
    size_t start = city.find_first_not_of(" \t");
    if (start != std::string::npos) {
        city = city.substr(start);
        size_t end = city.find_last_not_of(" \t");
        if (end != std::string::npos) {
            city = city.substr(0, end + 1);
        }
    }
    
    if (city.empty()) {
        std::string response = "Usage: !weather <city>";
        if (channel[0] == '#') {
            sendBotMessage(channel, client->getNickname() + ": " + response);
        } else {
            sendBotMessage(client, response);
        }
        return;
    }
    
    // Mock weather response
    std::vector<std::string> conditions;
    conditions.push_back("sunny");
    conditions.push_back("cloudy");
    conditions.push_back("rainy");
    conditions.push_back("snowy");
    conditions.push_back("partly cloudy");
    
    srand(static_cast<unsigned int>(std::time(0)));
    std::string condition = conditions[rand() % conditions.size()];
    int temperature = (rand() % 40) - 5; // -5 to 35 degrees
    
    std::ostringstream weather;
    weather << "Weather in " << city << ": " << condition << ", " << temperature << "°C";
    weather << " (Note: This is mock data for demonstration)";
    
    if (channel[0] == '#') {
        sendBotMessage(channel, client->getNickname() + ": " + weather.str());
    } else {
        sendBotMessage(client, weather.str());
    }
}

void Bot::sendBotMessage(Client* client, const std::string& message) {
    std::string botMsg = ":" + _botNick + "!bot@ircserver PRIVMSG " + client->getNickname() + " :" + message;
    _server->sendToClient(client->getFd(), botMsg);
}

void Bot::sendBotMessage(const std::string& channel, const std::string& message) {
    Channel* chan = _server->getChannel(channel);
    if (!chan) {
        return;
    }
    
    std::string botMsg = ":" + _botNick + "!bot@ircserver PRIVMSG " + channel + " :" + message;
    const std::vector<Client*>& members = chan->getMembers();
    
    for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        _server->sendToClient((*it)->getFd(), botMsg);
    }
}
