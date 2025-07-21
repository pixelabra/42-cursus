/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"
#include <sstream>

Commands::Commands(Server* server) : _server(server)
{
}

Commands::~Commands()
{
}

void Commands::processCommand(Client* client, const std::string& line)
{
    if (line.empty())
        return;
    
    std::vector<std::string> params = parseCommand(line);
    if (params.empty())
        return;
    
    std::string command = Utils::toUpperCase(params[0]);
    
    // Handle commands based on client state
    if (command == "PASS")
        handlePass(client, params);
    else if (command == "NICK")
        handleNick(client, params);
    else if (command == "USER")
        handleUser(client, params);
    else if (command == "QUIT")
        handleQuit(client, params);
    else if (command == "PING")
        handlePing(client, params);
    else if (command == "PONG")
        handlePong(client, params);
    else if (!client->isRegistered())
    {
        // Client must be registered for other commands
        return;
    }
    else if (command == "JOIN")
        handleJoin(client, params);
    else if (command == "PART")
        handlePart(client, params);
    else if (command == "TOPIC")
        handleTopic(client, params);
    else if (command == "NAMES")
        handleNames(client, params);
    else if (command == "LIST")
        handleList(client, params);
    else if (command == "PRIVMSG")
        handlePrivmsg(client, params);
    else if (command == "NOTICE")
        handleNotice(client, params);
    else if (command == "KICK")
        handleKick(client, params);
    else if (command == "INVITE")
        handleInvite(client, params);
    else if (command == "MODE")
        handleMode(client, params);
    else
    {
        // Unknown command
        _server->sendToClient(client, "421 " + client->getNickname() + " " + command + " :Unknown command\r\n");
    }
}

void Commands::handlePass(Client* client, const std::vector<std::string>& params)
{
    if (client->isAuthenticated())
    {
        _server->sendToClient(client, "462 :You may not reregister\r\n");
        return;
    }
    
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 PASS :Not enough parameters\r\n");
        return;
    }
    
    if (params[1] == _server->getPassword())
    {
        client->setAuthenticated(true);
    }
    else
    {
        _server->sendToClient(client, "464 :Password incorrect\r\n");
    }
}

void Commands::handleNick(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "431 :No nickname given\r\n");
        return;
    }
    
    std::string newNick = params[1];
    
    if (!Utils::isValidNickname(newNick))
    {
        _server->sendToClient(client, "432 " + newNick + " :Erroneous nickname\r\n");
        return;
    }
    
    if (_server->getClientByNickname(newNick) && _server->getClientByNickname(newNick) != client)
    {
        _server->sendToClient(client, "433 " + newNick + " :Nickname is already in use\r\n");
        return;
    }
    
    std::string oldNick = client->getNickname();
    client->setNickname(newNick);
    
    if (client->isRegistered() && !oldNick.empty())
    {
        // Notify all channels about nick change
        const std::set<std::string>& channels = client->getChannels();
        for (std::set<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it)
        {
            broadcastToChannel(*it, ":" + oldNick + "!" + client->getUsername() + "@" + 
                             client->getHostname() + " NICK :" + newNick + "\r\n", NULL);
        }
    }
    
    if (client->getState() == REGISTERING)
        sendWelcome(client);
}

void Commands::handleUser(Client* client, const std::vector<std::string>& params)
{
    if (client->hasUsername())
    {
        _server->sendToClient(client, "462 :You may not reregister\r\n");
        return;
    }
    
    if (params.size() < 5)
    {
        _server->sendToClient(client, "461 USER :Not enough parameters\r\n");
        return;
    }
    
    client->setUsername(params[1]);
    client->setRealname(params[4]);
    
    if (client->getState() == REGISTERING)
        sendWelcome(client);
}

void Commands::handleQuit(Client* client, const std::vector<std::string>& params)
{
    std::string reason = "Client Quit";
    if (params.size() > 1)
        reason = params[1];
    
    // Notify all channels
    const std::set<std::string>& channels = client->getChannels();
    for (std::set<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        broadcastToChannel(*it, ":" + client->getPrefix() + " QUIT :" + reason + "\r\n", client);
        _server->leaveChannel(client, *it);
    }
    
    _server->disconnectClient(client);
}

void Commands::handlePing(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 PING :Not enough parameters\r\n");
        return;
    }
    
    _server->sendToClient(client, "PONG " + _server->getServerName() + " :" + params[1] + "\r\n");
}

void Commands::handlePong(Client* client, const std::vector<std::string>& params)
{
    // PONG received, client is alive
    (void)client;
    (void)params;
}

void Commands::handleJoin(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 JOIN :Not enough parameters\r\n");
        return;
    }
    
    std::vector<std::string> channels = Utils::split(params[1], ',');
    std::vector<std::string> keys;
    
    if (params.size() > 2)
        keys = Utils::split(params[2], ',');
    
    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string channelName = channels[i];
        std::string key = (i < keys.size()) ? keys[i] : "";
        
        if (!Utils::isValidChannelName(channelName))
        {
            _server->sendToClient(client, "403 " + client->getNickname() + " " + channelName + " :No such channel\r\n");
            continue;
        }
        
        Channel* channel = _server->getChannel(channelName);
        if (!channel)
        {
            channel = _server->createChannel(channelName);
        }
        
        if (!channel->canJoin(client->getNickname(), key))
        {
            if (channel->isInviteOnly())
                _server->sendToClient(client, "473 " + client->getNickname() + " " + channelName + " :Cannot join channel (+i)\r\n");
            else if (!channel->getKey().empty() && key != channel->getKey())
                _server->sendToClient(client, "475 " + client->getNickname() + " " + channelName + " :Cannot join channel (+k)\r\n");
            else if (channel->getUserLimit() > 0 && static_cast<int>(channel->getMemberCount()) >= channel->getUserLimit())
                _server->sendToClient(client, "471 " + client->getNickname() + " " + channelName + " :Cannot join channel (+l)\r\n");
            continue;
        }
        
        channel->addMember(client->getNickname());
        client->joinChannel(channelName);
        
        // Send JOIN message to all channel members
        broadcastToChannel(channelName, ":" + client->getPrefix() + " JOIN :" + channelName + "\r\n", NULL);
        
        // Send topic if exists
        if (!channel->getTopic().empty())
        {
            _server->sendToClient(client, "332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic() + "\r\n");
        }
        else
        {
            _server->sendToClient(client, "331 " + client->getNickname() + " " + channelName + " :No topic is set\r\n");
        }
        
        // Send names list
        sendChannelMemberList(client, channelName);
    }
}

void Commands::handlePart(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 PART :Not enough parameters\r\n");
        return;
    }
    
    std::vector<std::string> channels = Utils::split(params[1], ',');
    std::string reason = (params.size() > 2) ? params[2] : client->getNickname();
    
    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string channelName = channels[i];
        Channel* channel = _server->getChannel(channelName);
        
        if (!channel || !channel->isMember(client->getNickname()))
        {
            _server->sendToClient(client, "442 " + client->getNickname() + " " + channelName + " :You're not on that channel\r\n");
            continue;
        }
        
        broadcastToChannel(channelName, ":" + client->getPrefix() + " PART " + channelName + " :" + reason + "\r\n", NULL);
        
        _server->leaveChannel(client, channelName);
    }
}

void Commands::handleTopic(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 TOPIC :Not enough parameters\r\n");
        return;
    }
    
    std::string channelName = params[1];
    Channel* channel = _server->getChannel(channelName);
    
    if (!channel)
    {
        _server->sendToClient(client, "403 " + client->getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    
    if (!channel->isMember(client->getNickname()))
    {
        _server->sendToClient(client, "442 " + client->getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }
    
    if (params.size() == 2)
    {
        // Get topic
        if (channel->getTopic().empty())
            _server->sendToClient(client, "331 " + client->getNickname() + " " + channelName + " :No topic is set\r\n");
        else
            _server->sendToClient(client, "332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic() + "\r\n");
    }
    else
    {
        // Set topic
        if (channel->isTopicRestricted() && !channel->isOperator(client->getNickname()))
        {
            _server->sendToClient(client, "482 " + client->getNickname() + " " + channelName + " :You're not channel operator\r\n");
            return;
        }
        
        std::string newTopic = params[2];
        channel->setTopic(newTopic);
        
        broadcastToChannel(channelName, ":" + client->getPrefix() + " TOPIC " + channelName + " :" + newTopic + "\r\n", NULL);
    }
}

void Commands::handleNames(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        // List all channels - simplified implementation
        _server->sendToClient(client, "366 " + client->getNickname() + " * :End of /NAMES list\r\n");
        return;
    }
    
    std::vector<std::string> channels = Utils::split(params[1], ',');
    
    for (size_t i = 0; i < channels.size(); ++i)
    {
        sendChannelMemberList(client, channels[i]);
    }
}

void Commands::handleList(Client* client, const std::vector<std::string>& params)
{
    (void)params;
    
    const std::map<std::string, Channel*>& channels = _server->getChannels();
    
    _server->sendToClient(client, "321 " + client->getNickname() + " Channel :Users  Name\r\n");
    
    for (std::map<std::string, Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        Channel* channel = it->second;
        _server->sendToClient(client, "322 " + client->getNickname() + " " + channel->getName() + " " + 
                            Utils::intToString(channel->getMemberCount()) + " :" + channel->getTopic() + "\r\n");
    }
    
    _server->sendToClient(client, "323 " + client->getNickname() + " :End of /LIST\r\n");
}

void Commands::handlePrivmsg(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "411 " + client->getNickname() + " :No recipient given (PRIVMSG)\r\n");
        return;
    }
    
    if (params.size() < 3)
    {
        _server->sendToClient(client, "412 " + client->getNickname() + " :No text to send\r\n");
        return;
    }
    
    std::string target = params[1];
    std::string message = params[2];
    
    if (target[0] == '#' || target[0] == '&')
    {
        // Channel message
        Channel* channel = _server->getChannel(target);
        if (!channel)
        {
            _server->sendToClient(client, "403 " + client->getNickname() + " " + target + " :No such channel\r\n");
            return;
        }
        
        if (!channel->isMember(client->getNickname()))
        {
            _server->sendToClient(client, "404 " + client->getNickname() + " " + target + " :Cannot send to channel\r\n");
            return;
        }
        
        broadcastToChannel(target, ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n", client);
    }
    else
    {
        // Private message
        Client* targetClient = _server->getClientByNickname(target);
        if (!targetClient)
        {
            _server->sendToClient(client, "401 " + client->getNickname() + " " + target + " :No such nick/channel\r\n");
            return;
        }
        
        _server->sendToClient(targetClient, ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
    }
}

void Commands::handleNotice(Client* client, const std::vector<std::string>& params)
{
    // NOTICE is like PRIVMSG but doesn't generate error replies
    if (params.size() < 3)
        return;
    
    std::string target = params[1];
    std::string message = params[2];
    
    if (target[0] == '#' || target[0] == '&')
    {
        // Channel notice
        Channel* channel = _server->getChannel(target);
        if (channel && channel->isMember(client->getNickname()))
        {
            broadcastToChannel(target, ":" + client->getPrefix() + " NOTICE " + target + " :" + message + "\r\n", client);
        }
    }
    else
    {
        // Private notice
        Client* targetClient = _server->getClientByNickname(target);
        if (targetClient)
        {
            _server->sendToClient(targetClient, ":" + client->getPrefix() + " NOTICE " + target + " :" + message + "\r\n");
        }
    }
}

void Commands::handleKick(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 3)
    {
        _server->sendToClient(client, "461 KICK :Not enough parameters\r\n");
        return;
    }
    
    std::string channelName = params[1];
    std::string targetNick = params[2];
    std::string reason = (params.size() > 3) ? params[3] : client->getNickname();
    
    Channel* channel = _server->getChannel(channelName);
    if (!channel)
    {
        _server->sendToClient(client, "403 " + client->getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    
    if (!channel->isOperator(client->getNickname()))
    {
        _server->sendToClient(client, "482 " + client->getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }
    
    if (!channel->isMember(targetNick))
    {
        _server->sendToClient(client, "441 " + client->getNickname() + " " + targetNick + " " + channelName + " :They aren't on that channel\r\n");
        return;
    }
    
    Client* targetClient = _server->getClientByNickname(targetNick);
    
    broadcastToChannel(channelName, ":" + client->getPrefix() + " KICK " + channelName + " " + targetNick + " :" + reason + "\r\n", NULL);
    
    if (targetClient)
        _server->leaveChannel(targetClient, channelName);
    else
        channel->removeMember(targetNick);
}

void Commands::handleInvite(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 3)
    {
        _server->sendToClient(client, "461 INVITE :Not enough parameters\r\n");
        return;
    }
    
    std::string targetNick = params[1];
    std::string channelName = params[2];
    
    Channel* channel = _server->getChannel(channelName);
    if (!channel)
    {
        _server->sendToClient(client, "403 " + client->getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    
    if (!channel->isMember(client->getNickname()))
    {
        _server->sendToClient(client, "442 " + client->getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }
    
    if (channel->isInviteOnly() && !channel->isOperator(client->getNickname()))
    {
        _server->sendToClient(client, "482 " + client->getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }
    
    Client* targetClient = _server->getClientByNickname(targetNick);
    if (!targetClient)
    {
        _server->sendToClient(client, "401 " + client->getNickname() + " " + targetNick + " :No such nick/channel\r\n");
        return;
    }
    
    if (channel->isMember(targetNick))
    {
        _server->sendToClient(client, "443 " + client->getNickname() + " " + targetNick + " " + channelName + " :is already on channel\r\n");
        return;
    }
    
    channel->addInvite(targetNick);
    
    _server->sendToClient(client, "341 " + client->getNickname() + " " + targetNick + " " + channelName + "\r\n");
    _server->sendToClient(targetClient, ":" + client->getPrefix() + " INVITE " + targetNick + " :" + channelName + "\r\n");
}

void Commands::handleMode(Client* client, const std::vector<std::string>& params)
{
    if (params.size() < 2)
    {
        _server->sendToClient(client, "461 MODE :Not enough parameters\r\n");
        return;
    }
    
    std::string target = params[1];
    
    if (target[0] == '#' || target[0] == '&')
    {
        // Channel mode
        Channel* channel = _server->getChannel(target);
        if (!channel)
        {
            _server->sendToClient(client, "403 " + client->getNickname() + " " + target + " :No such channel\r\n");
            return;
        }
        
        if (params.size() == 2)
        {
            // Query mode
            _server->sendToClient(client, "324 " + client->getNickname() + " " + target + " " + channel->getModeString() + "\r\n");
            return;
        }
        
        if (!channel->isOperator(client->getNickname()))
        {
            _server->sendToClient(client, "482 " + client->getNickname() + " " + target + " :You're not channel operator\r\n");
            return;
        }
        
        std::string modeStr = params[2];
        size_t paramIndex = 3;
        bool adding = true;
        
        for (size_t i = 0; i < modeStr.length(); ++i)
        {
            char mode = modeStr[i];
            
            if (mode == '+')
                adding = true;
            else if (mode == '-')
                adding = false;
            else if (mode == 'i')
            {
                channel->setInviteOnly(adding);
                broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " " + (adding ? "+i" : "-i") + "\r\n", NULL);
            }
            else if (mode == 't')
            {
                channel->setTopicRestricted(adding);
                broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " " + (adding ? "+t" : "-t") + "\r\n", NULL);
            }
            else if (mode == 'k')
            {
                if (adding && paramIndex < params.size())
                {
                    std::string key = params[paramIndex++];
                    channel->setKey(key);
                    broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " +k " + key + "\r\n", NULL);
                }
                else if (!adding)
                {
                    channel->setKey("");
                    broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " -k\r\n", NULL);
                }
            }
            else if (mode == 'l')
            {
                if (adding && paramIndex < params.size())
                {
                    int limit = Utils::stringToInt(params[paramIndex++]);
                    channel->setUserLimit(limit);
                    broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " +l " + Utils::intToString(limit) + "\r\n", NULL);
                }
                else if (!adding)
                {
                    channel->setUserLimit(0);
                    broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " -l\r\n", NULL);
                }
            }
            else if (mode == 'o')
            {
                if (paramIndex < params.size())
                {
                    std::string targetNick = params[paramIndex++];
                    if (channel->isMember(targetNick))
                    {
                        if (adding)
                            channel->addOperator(targetNick);
                        else
                            channel->removeOperator(targetNick);
                        
                        broadcastToChannel(target, ":" + client->getPrefix() + " MODE " + target + " " + 
                                         (adding ? "+o " : "-o ") + targetNick + "\r\n", NULL);
                    }
                }
            }
        }
    }
    else
    {
        // User mode - simplified implementation
        if (target != client->getNickname())
        {
            _server->sendToClient(client, "502 " + client->getNickname() + " :Can't change mode for other users\r\n");
            return;
        }
        
        if (params.size() == 2)
        {
            _server->sendToClient(client, "221 " + client->getNickname() + " +\r\n");
        }
    }
}

std::vector<std::string> Commands::parseCommand(const std::string& line)
{
    std::vector<std::string> params;
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token)
    {
        if (token[0] == ':' && !params.empty())
        {
            // Rest of line is one parameter
            std::string rest;
            std::getline(iss, rest);
            token += rest;
            token = token.substr(1); // Remove leading ':'
        }
        params.push_back(token);
    }
    
    return params;
}

void Commands::sendWelcome(Client* client)
{
    if (!client->isAuthenticated() || !client->hasNickname() || !client->hasUsername())
        return;
    
    client->setState(REGISTERED);
    
    std::string serverName = _server->getServerName();
    std::string nick = client->getNickname();
    
    _server->sendToClient(client, "001 " + nick + " :Welcome to the Internet Relay Network " + client->getPrefix() + "\r\n");
    _server->sendToClient(client, "002 " + nick + " :Your host is " + serverName + ", running version 1.0\r\n");
    _server->sendToClient(client, "003 " + nick + " :This server was created " + Utils::getCurrentTime() + "\r\n");
    _server->sendToClient(client, "004 " + nick + " " + serverName + " 1.0 o iklmnopstv\r\n");
}

void Commands::broadcastToChannel(const std::string& channel, const std::string& message, Client* exclude)
{
    _server->broadcastToChannel(channel, message, exclude);
}

void Commands::sendChannelMemberList(Client* client, const std::string& channelName)
{
    Channel* channel = _server->getChannel(channelName);
    if (!channel)
    {
        _server->sendToClient(client, "366 " + client->getNickname() + " " + channelName + " :End of /NAMES list\r\n");
        return;
    }
    
    std::string memberList = channel->getMemberList();
    _server->sendToClient(client, "353 " + client->getNickname() + " = " + channelName + " :" + memberList + "\r\n");
    _server->sendToClient(client, "366 " + client->getNickname() + " " + channelName + " :End of /NAMES list\r\n");
}
