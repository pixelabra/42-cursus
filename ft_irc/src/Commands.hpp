/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:35:49 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:37:16 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

class Server;
class Client;
struct Message;

class Commands {
private:
    Server* _server;
    
    // auth commands
    void cmdPass(Client* client, const Message& msg);
    void cmdNick(Client* client, const Message& msg);
    void cmdUser(Client* client, const Message& msg);
    
    // channel commands
    void cmdJoin(Client* client, const Message& msg);
    void cmdPart(Client* client, const Message& msg);
    void cmdPrivmsg(Client* client, const Message& msg);
    void cmdNotice(Client* client, const Message& msg);
    void cmdKick(Client* client, const Message& msg);
    void cmdInvite(Client* client, const Message& msg);
    void cmdTopic(Client* client, const Message& msg);
    void cmdMode(Client* client, const Message& msg);
    
    // util commands
    void cmdWho(Client* client, const Message& msg);
    void cmdQuit(Client* client, const Message& msg);
    void cmdPing(Client* client, const Message& msg);
    void cmdCap(Client* client, const Message& msg);
    
    // helpers
    void sendWelcome(Client* client);
    void sendNumericReply(Client* client, int code, const std::string& message);
    bool isValidNickname(const std::string& nick);

public:
    Commands(Server* server);
    ~Commands();

    void processCommand(Client* client, const Message& msg);
};

#endif
