/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:43:15 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:43:17 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

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
    
    void handleHelpCommand(Client* client, const std::string& channel);
    void handleTimeCommand(Client* client, const std::string& channel);
    void handleJokeCommand(Client* client, const std::string& channel);
    void handleQuoteCommand(Client* client, const std::string& channel);
    void handleStatsCommand(Client* client, const std::string& channel);
    
public:
    Bot(Server* server);
    ~Bot();
    
    void processMessage(Client* client, const std::string& target, const std::string& message);
    
    bool isBotCommand(const std::string& message);
    std::string getBotNick() const { return _botNick; }
};

#endif
