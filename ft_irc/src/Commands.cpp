#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRCParser.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

Commands::Commands(Server* server) : _server(server) {
}

Commands::~Commands() {
}

void Commands::processCommand(Client* client, const std::string& rawCommand) {
    IRCParser parser;
    IRCMessage msg = parser.parseMessage(rawCommand);
    
    if (msg.command.empty()) {
        return;
    }
    
    // Log received command for debugging
    std::cout << "Client " << client->getNickname() << " sent: " << msg.command;
    if (!msg.params.empty()) {
        std::cout << " " << msg.params[0];
    }
    std::cout << std::endl;
    
    std::transform(msg.command.begin(), msg.command.end(), msg.command.begin(), ::toupper);
    
    // Authentication commands
    if (msg.command == "PASS") {
        cmdPass(client, msg);
    } else if (msg.command == "NICK") {
        cmdNick(client, msg);
    } else if (msg.command == "USER") {
        cmdUser(client, msg);
    }
    // Commands requiring authentication
    else if (!client->isAuthenticated()) {
        sendNumericReply(client, 451, "You have not registered");
    }
    // Channel and messaging commands
    else if (msg.command == "JOIN") {
        cmdJoin(client, msg);
    } else if (msg.command == "PART") {
        cmdPart(client, msg);
    } else if (msg.command == "PRIVMSG") {
        cmdPrivmsg(client, msg);
    } else if (msg.command == "KICK") {
        cmdKick(client, msg);
    } else if (msg.command == "INVITE") {
        cmdInvite(client, msg);
    } else if (msg.command == "TOPIC") {
        cmdTopic(client, msg);
    } else if (msg.command == "MODE") {
        cmdMode(client, msg);
    } else if (msg.command == "WHO") {
        cmdWho(client, msg);
    } else if (msg.command == "QUIT") {
        cmdQuit(client, msg);
    } else if (msg.command == "PING") {
        cmdPing(client, msg);
    } else {
        sendNumericReply(client, 421, msg.command + " :Unknown command");
    }
}

void Commands::cmdPass(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "PASS :Not enough parameters");
        return;
    }
    
    if (client->isAuthenticated()) {
        sendNumericReply(client, 462, ":You may not reregister");
        return;
    }
    
    if (msg.params[0] == _server->getPassword()) {
        client->setAuthenticated(true);
    } else {
        sendNumericReply(client, 464, ":Password incorrect");
    }
}

void Commands::cmdNick(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 431, ":No nickname given");
        return;
    }
    
    std::string newNick = msg.params[0];
    if (!isValidNickname(newNick)) {
        sendNumericReply(client, 432, newNick + " :Erroneous nickname");
        return;
    }
    
    Client* existing = _server->getClientByNick(newNick);
    if (existing && existing != client) {
        sendNumericReply(client, 433, newNick + " :Nickname is already in use");
        return;
    }
    
    std::string oldNick = client->getNickname();
    client->setNickname(newNick);
    
    if (!oldNick.empty()) {
        std::string message = ":" + oldNick + " NICK :" + newNick;
        _server->sendToClient(client->getFd(), message);
    }
    
    if (client->isAuthenticated() && !client->getNickname().empty() && !client->getUsername().empty() && !client->isRegistered()) {
        client->setRegistered(true);
        sendWelcome(client);
    }
}

void Commands::cmdUser(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 4) {
        sendNumericReply(client, 461, "USER :Not enough parameters");
        return;
    }
    
    if (client->isRegistered()) {
        sendNumericReply(client, 462, ":You may not reregister");
        return;
    }
    
    client->setUsername(msg.params[0]);
    client->setRealname(msg.params[3]);
    
    if (client->isAuthenticated() && !client->getNickname().empty() && !client->getUsername().empty() && !client->isRegistered()) {
        client->setRegistered(true);
        sendWelcome(client);
    }
}

void Commands::cmdJoin(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "JOIN :Not enough parameters");
        return;
    }
    
    std::string channelName = msg.params[0];
    std::string key = (msg.params.size() > 1) ? msg.params[1] : "";
    
    if (channelName[0] != '#') {
        sendNumericReply(client, 403, channelName + " :No such channel");
        return;
    }
    
    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        channel = _server->createChannel(channelName, client);
    } else {
        if (!channel->canJoin(client, key)) {
            if (channel->isInviteOnly()) {
                sendNumericReply(client, 473, channelName + " :Cannot join channel (+i) - invite only");
            } else {
                sendNumericReply(client, 473, channelName + " :Cannot join channel");
            }
            return;
        }
        channel->addMember(client);
        // Remove from invite list once joined (invite is used up)
        if (channel->isInvited(client)) {
            channel->removeFromInviteList(client);
        }
    }
    
    // Send JOIN confirmation
    std::string joinMsg = ":" + client->getPrefix() + " JOIN " + channelName;
    _server->sendToClient(client->getFd(), joinMsg);
    _server->broadcastToChannel(channelName, joinMsg, client);
    
    // Send topic if exists
    if (!channel->getTopic().empty()) {
        sendNumericReply(client, 332, channelName + " :" + channel->getTopic());
    }
    
    // Send names list
    sendNumericReply(client, 353, "= " + channelName + " :" + channel->getMembersList());
    sendNumericReply(client, 366, channelName + " :End of /NAMES list");
}

void Commands::cmdPart(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "PART :Not enough parameters");
        return;
    }
    
    std::string channelName = msg.params[0];
    Channel* channel = _server->getChannel(channelName);
    
    if (!channel || !channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + " :You're not on that channel");
        return;
    }
    
    std::string reason = (msg.params.size() > 1) ? msg.params[1] : "";
    std::string partMsg = ":" + client->getPrefix() + " PART " + channelName;
    if (!reason.empty()) {
        partMsg += " :" + reason;
    }
    
    _server->sendToClient(client->getFd(), partMsg);
    _server->broadcastToChannel(channelName, partMsg, client);
    
    channel->removeMember(client);
}

void Commands::cmdPrivmsg(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, "PRIVMSG :Not enough parameters");
        return;
    }
    
    std::string target = msg.params[0];
    std::string message = msg.params[1];
    
    // Check for DCC file transfer messages
    if (_server->getFileTransfer()->isDCCMessage(message)) {
        _server->getFileTransfer()->processDCCMessage(client, target, message);
        return;
    }
    
    if (target[0] == '#') {
        // Channel message
        Channel* channel = _server->getChannel(target);
        if (!channel) {
            sendNumericReply(client, 403, target + " :No such channel");
            return;
        }
        
        if (!channel->isMember(client)) {
            sendNumericReply(client, 442, target + " :You're not on that channel");
            return;
        }
        
        std::string privmsg = ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message;
        _server->broadcastToChannel(target, privmsg, client);
        
        // Process bot commands in channel
        _server->getBot()->processMessage(client, target, message);
    } else {
        // Private message
        Client* targetClient = _server->getClientByNick(target);
        if (!targetClient) {
            // Check if it's a message to the bot
            if (target == _server->getBot()->getBotNick()) {
                _server->getBot()->processMessage(client, client->getNickname(), message);
                return;
            }
            sendNumericReply(client, 401, target + " :No such nick/channel");
            return;
        }
        
        std::string privmsg = ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message;
        _server->sendToClient(targetClient->getFd(), privmsg);
    }
}

void Commands::cmdKick(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, "KICK :Not enough parameters. Usage: KICK <channel> <nickname> [reason]");
        return;
    }
    
    std::string channelName = msg.params[0];
    std::string targetNick = msg.params[1];
    std::string reason = (msg.params.size() > 2) ? msg.params[2] : client->getNickname();
    
    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        sendNumericReply(client, 403, channelName + " :No such channel");
        return;
    }
    
    if (!channel->isOperator(client)) {
        sendNumericReply(client, 482, channelName + " :You're not channel operator");
        return;
    }
    
    Client* targetClient = _server->getClientByNick(targetNick);
    if (!targetClient || !channel->isMember(targetClient)) {
        sendNumericReply(client, 441, targetNick + " " + channelName + " :They aren't on that channel");
        return;
    }
    
    std::string kickMsg = ":" + client->getPrefix() + " KICK " + channelName + " " + targetNick + " :" + reason;
    _server->sendToClient(targetClient->getFd(), kickMsg);
    _server->broadcastToChannel(channelName, kickMsg, NULL);
    
    channel->removeMember(targetClient);
}

void Commands::cmdInvite(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, "INVITE :Not enough parameters. Usage: INVITE <nickname> <channel>");
        return;
    }
    
    std::string targetNick = msg.params[0];
    std::string channelName = msg.params[1];
    
    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        sendNumericReply(client, 403, channelName + " :No such channel");
        return;
    }
    
    if (!channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + " :You're not on that channel");
        return;
    }
    
    if (channel->isInviteOnly() && !channel->isOperator(client)) {
        sendNumericReply(client, 482, channelName + " :You're not channel operator");
        return;
    }
    
    Client* targetClient = _server->getClientByNick(targetNick);
    if (!targetClient) {
        sendNumericReply(client, 401, targetNick + " :No such nick/channel");
        return;
    }
    
    if (channel->isMember(targetClient)) {
        sendNumericReply(client, 443, targetNick + " " + channelName + " :is already on channel");
        return;
    }
    
    // Add to invite list
    channel->addToInviteList(targetClient);
    
    // Send invite to target
    std::string inviteMsg = ":" + client->getPrefix() + " INVITE " + targetNick + " " + channelName;
    _server->sendToClient(targetClient->getFd(), inviteMsg);
    
    // Confirm to sender
    sendNumericReply(client, 341, targetNick + " " + channelName);
    
    // Add confirmation message
    std::string confirmMsg = ":ircserv!server@ircserver PRIVMSG " + client->getNickname() + " :" + client->getNickname() + " invited " + targetNick + " to " + channelName;
    _server->sendToClient(client->getFd(), confirmMsg);
}

void Commands::cmdTopic(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "TOPIC :Not enough parameters. Usage: TOPIC <channel> [topic]");
        return;
    }
    
    std::string channelName = msg.params[0];
    Channel* channel = _server->getChannel(channelName);
    
    if (!channel) {
        sendNumericReply(client, 403, channelName + " :No such channel");
        return;
    }
    
    if (!channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + " :You're not on that channel");
        return;
    }
    
    if (msg.params.size() == 1) {
        // View topic
        if (channel->getTopic().empty()) {
            sendNumericReply(client, 331, channelName + " :No topic is set");
        } else {
            sendNumericReply(client, 332, channelName + " :" + channel->getTopic());
        }
    } else {
        // Set topic
        if (channel->isTopicRestricted() && !channel->isOperator(client)) {
            sendNumericReply(client, 482, channelName + " :You're not channel operator");
            return;
        }
        
        std::string newTopic = msg.params[1];
        channel->setTopic(newTopic);
        
        std::string topicMsg = ":" + client->getPrefix() + " TOPIC " + channelName + " :" + newTopic;
        _server->sendToClient(client->getFd(), topicMsg);
        _server->broadcastToChannel(channelName, topicMsg, client);
    }
}

void Commands::cmdMode(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "MODE :Not enough parameters. Usage: MODE <channel> [+/-modes] [parameters]");
        return;
    }
    
    std::string channelName = msg.params[0];
    Channel* channel = _server->getChannel(channelName);
    
    if (!channel) {
        sendNumericReply(client, 403, channelName + " :No such channel");
        return;
    }
    
    if (!channel->isOperator(client)) {
        sendNumericReply(client, 482, channelName + " :You're not channel operator");
        return;
    }
    
    if (msg.params.size() == 1) {
        // View modes (simplified)
        std::string modes = "+";
        if (channel->isInviteOnly()) modes += "i";
        if (channel->isTopicRestricted()) modes += "t";
        if (!channel->getKey().empty()) modes += "k";
        if (channel->getUserLimit() > 0) modes += "l";
        
        sendNumericReply(client, 324, channelName + " " + modes);
        return;
    }
    
    std::string modeString = msg.params[1];
    bool adding = true;
    int paramIndex = 2;
    
    for (size_t i = 0; i < modeString.length(); ++i) {
        char mode = modeString[i];
        
        if (mode == '+') {
            adding = true;
        } else if (mode == '-') {
            adding = false;
        } else if (mode == 'i') {
            channel->setInviteOnly(adding);
            std::string statusMsg = ":ircserv!server@ircserver PRIVMSG " + client->getNickname() + " :" + client->getNickname() + " set channel " + channelName + (adding ? " to invite only" : " to open access");
            _server->sendToClient(client->getFd(), statusMsg);
        } else if (mode == 't') {
            channel->setTopicRestricted(adding);
            std::string statusMsg = ":ircserv!server@ircserver PRIVMSG " + client->getNickname() + " :" + client->getNickname() + (adding ? " restricted topic changes to operators" : " allowed topic changes by all members") + " in " + channelName;
            _server->sendToClient(client->getFd(), statusMsg);
        } else if (mode == 'k') {
            if (adding && paramIndex < static_cast<int>(msg.params.size())) {
                channel->setKey(msg.params[paramIndex++]);
            } else {
                channel->setKey("");
            }
        } else if (mode == 'l') {
            if (adding && paramIndex < static_cast<int>(msg.params.size())) {
                int limit = std::atoi(msg.params[paramIndex++].c_str());
                channel->setUserLimit(limit);
            } else {
                channel->setUserLimit(0);
            }
        } else if (mode == 'o') {
            if (paramIndex < static_cast<int>(msg.params.size())) {
                Client* targetClient = _server->getClientByNick(msg.params[paramIndex++]);
                if (targetClient && channel->isMember(targetClient)) {
                    if (adding) {
                        channel->addOperator(targetClient);
                    } else {
                        channel->removeOperator(targetClient);
                    }
                }
            }
        }
    }
    
    std::string modeMsg = ":" + client->getPrefix() + " MODE " + channelName + " " + modeString;
    _server->sendToClient(client->getFd(), modeMsg);
    _server->broadcastToChannel(channelName, modeMsg, client);
}

void Commands::cmdWho(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 315, "* :End of /WHO list");
        return;
    }
    
    std::string target = msg.params[0];
    Channel* channel = _server->getChannel(target);
    
    if (channel) {
        const std::vector<Client*>& members = channel->getMembers();
        for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
            std::ostringstream oss;
            oss << target << " " << (*it)->getUsername() << " " << (*it)->getHostname() 
                << " server " << (*it)->getNickname() << " H :0 " << (*it)->getRealname();
            sendNumericReply(client, 352, oss.str());
        }
    }
    
    sendNumericReply(client, 315, target + " :End of /WHO list");
}

void Commands::cmdQuit(Client* client, const IRCMessage& msg) {
    std::string reason = (msg.params.empty()) ? "Client Quit" : msg.params[0];
    std::string quitMsg = ":" + client->getPrefix() + " QUIT :" + reason;
    
    // Broadcast quit message to all channels
    _server->removeClientFromChannels(client);
    
    // Client will be disconnected by server
}

void Commands::cmdPing(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, "PING :Not enough parameters");
        return;
    }
    
    std::string pongMsg = "PONG :" + msg.params[0];
    _server->sendToClient(client->getFd(), pongMsg);
}

void Commands::sendWelcome(Client* client) {
    sendNumericReply(client, 001, ":Welcome to the Internet Relay Network " + client->getPrefix());
    sendNumericReply(client, 002, ":Your host is ircserv, running version 1.0");
    sendNumericReply(client, 003, ":This server was created today");
    sendNumericReply(client, 004, "ircserv 1.0 o itkol");
}

void Commands::sendNumericReply(Client* client, int code, const std::string& message) {
    std::ostringstream oss;
    oss << ":ircserv " << code << " " << client->getNickname() << " " << message;
    _server->sendToClient(client->getFd(), oss.str());
}

bool Commands::isValidNickname(const std::string& nick) {
    if (nick.empty() || nick.length() > 9) {
        return false;
    }
    
    for (size_t i = 0; i < nick.length(); ++i) {
        char c = nick[i];
        if (i == 0) {
            if (!std::isalpha(c) && c != '_') {
                return false;
            }
        } else {
            if (!std::isalnum(c) && c != '_' && c != '-') {
                return false;
            }
        }
    }
    
    return true;
}
