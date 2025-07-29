#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRCParser.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
#include "Colors.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

Commands::Commands(Server* server) : _server(server) {
}

Commands::~Commands() {
}

void Commands::processCommand(Client* client, const IRCMessage& msg) {
    if (msg.command.empty()) {
        return;
    }
    std::string command = msg.command;
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    // Authentication commands and pre-auth compatibility commands
    if (command == "PASS") {
        cmdPass(client, msg);
    } else if (command == "NICK") {
        cmdNick(client, msg);
    } else if (command == "USER") {
        cmdUser(client, msg);
    } else if (command == "CAP") {
        cmdCap(client, msg);  // Allow CAP before authentication for irssi compatibility
    } else if (command == "PONG") {
        // PONG responses are acceptable, just ignore
        return;
    }
    // Commands requiring authentication
    else if (!client->isAuthenticated()) {
        sendNumericReply(client, 451, "You have not registered");
    }
    // Channel and messaging commands
    else if (command == "JOIN") {
        cmdJoin(client, msg);
    } else if (command == "PART") {
        cmdPart(client, msg);
    } else if (command == "PRIVMSG") {
        cmdPrivmsg(client, msg);
    } else if (command == "KICK") {
        cmdKick(client, msg);
    } else if (command == "INVITE") {
        cmdInvite(client, msg);
    } else if (command == "TOPIC") {
        cmdTopic(client, msg);
    } else if (command == "MODE") {
        cmdMode(client, msg);
    } else if (command == "WHO") {
        cmdWho(client, msg);
    } else if (command == "QUIT") {
        cmdQuit(client, msg);
    } else if (command == "PING") {
        cmdPing(client, msg);
    } else {
        sendNumericReply(client, 421, command + std::string(": ") + RED + "Unknown command" + RESET);
    }
}

void Commands::cmdPass(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, std::string("PASS: ") + RED + "Not enough parameters" + RESET);
        return;
    }

    if (client->isAuthenticated()) {
        sendNumericReply(client, 462, std::string(": ") + RED + "You may not reregister" + RESET);
        return;
    }

    if (msg.params[0] == _server->getPassword()) {
        client->setAuthenticated(true);
    } else {
        sendNumericReply(client, 464, std::string(": ") + RED + "Password incorrect" + RESET);
    }
}

void Commands::cmdNick(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 431, std::string(": ") + RED + "No nickname given" + RESET);
        return;
    }

    std::string newNick = msg.params[0];
    if (!isValidNickname(newNick)) {
        sendNumericReply(client, 432, newNick + ": " + RED + "Erroneous nickname" + RESET);
        return;
    }

    Client* existing = _server->getClientByNick(newNick);
    if (existing && existing != client) {
        sendNumericReply(client, 433, newNick + ": " + RED + "Nickname is already in use" + RESET);
        return;
    }

    std::string oldNick = client->getNickname();
    client->setNickname(newNick);

    if (!oldNick.empty()) {
        std::string message = std::string(":") + oldNick + " NICK " + newNick;
        _server->sendToClient(client->getFd(), message);
    }

    if (client->isAuthenticated() && !client->getNickname().empty() && !client->getUsername().empty() && !client->isRegistered()) {
        client->setRegistered(true);
        sendWelcome(client);
    }
}

void Commands::cmdUser(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 4) {
        sendNumericReply(client, 461, std::string("USER: ") + RED + "Not enough parameters" + RESET);
        return;
    }

    if (client->isRegistered()) {
        sendNumericReply(client, 462, std::string(": ") + RED + "You may not reregister" + RESET);
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
        sendNumericReply(client, 461, std::string("JOIN: ") + RED + "Not enough parameters" + RESET);
        return;
    }

    std::string channelName = msg.params[0];
    std::string key = (msg.params.size() > 1) ? msg.params[1] : "";

    if (channelName[0] != '#') {
        sendNumericReply(client, 403, channelName + ": " + RED + "No such channel" + RESET);
        return;
    }

    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        channel = _server->createChannel(channelName, client);
    } else {
        if (!channel->canJoin(client, key)) {
            if (channel->isInviteOnly()) {
                sendNumericReply(client, 473, channelName + ": " + RED + "Cannot join channel (+i) - invite only" + RESET);
            } else {
                sendNumericReply(client, 473, channelName + ": " + RED + "Cannot join channel" + RESET);
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
    std::string joinMsg = std::string(":") + client->getPrefix() + " JOIN " + channelName;
    _server->sendToClient(client->getFd(), joinMsg);
    _server->broadcastToChannel(channelName, joinMsg, client);

    // Send topic if exists
    if (!channel->getTopic().empty()) {
        sendNumericReply(client, 332, channelName + ": " + CYAN + channel->getTopic() + RESET);
    }

    // Send names list
    sendNumericReply(client, 353, "= " + channelName + " :" + channel->getMembersList());
    sendNumericReply(client, 366, channelName + " :End of /NAMES list");
}

void Commands::cmdPart(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, std::string("PART: ") + RED + "Not enough parameters" + RESET);
        return;
    }

    std::string channelName = msg.params[0];
    Channel* channel = _server->getChannel(channelName);

    if (!channel || !channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + ": " + RED + "You're not on that channel" + RESET);
        return;
    }

    std::string reason = (msg.params.size() > 1) ? msg.params[1] : "";
    std::string partMsg = std::string(":") + client->getPrefix() + " PART " + channelName;
    if (!reason.empty()) {
        partMsg += ": " + reason;
    }

    _server->sendToClient(client->getFd(), partMsg);
    _server->broadcastToChannel(channelName, partMsg, client);

    channel->removeMember(client);
}

void Commands::cmdPrivmsg(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, std::string("PRIVMSG: ") + RED + "Not enough parameters" + RESET);
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
            sendNumericReply(client, 403, target + ": " + RED + "No such channel" + RESET);
            return;
        }

        if (!channel->isMember(client)) {
            sendNumericReply(client, 442, target + ": " + RED + "You're not on that channel" + RESET);
            return;
        }

        std::string privmsg = std::string(":") + client->getPrefix() + " PRIVMSG " + target + " :" + message;

        // Echo message back to sender (so they see it in their channel window)
        // _server->sendToClient(client->getFd(), privmsg);

        // Broadcast to other channel members
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
            sendNumericReply(client, 401, target + ": " + RED + "No such nick/channel" + RESET);
            return;
        }

        std::string privmsg = std::string(":") + client->getPrefix() + " PRIVMSG " + target + " :" + message;
        _server->sendToClient(targetClient->getFd(), privmsg);
    }
}

void Commands::cmdKick(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, std::string("KICK: ") + RED + "Not enough parameters. Usage: KICK <channel> <nickname> [reason]" + RESET);
        return;
    }

    std::string channelName = msg.params[0];
    std::string targetNick = msg.params[1];
    std::string reason = (msg.params.size() > 2) ? msg.params[2] : client->getNickname();

    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        sendNumericReply(client, 403, channelName + ": " + RED + "No such channel" + RESET);
        return;
    }

    if (!channel->isOperator(client)) {
        sendNumericReply(client, 482, channelName + ": " + RED + "You're not channel operator" + RESET);
        return;
    }

    Client* targetClient = _server->getClientByNick(targetNick);
    if (!targetClient || !channel->isMember(targetClient)) {
        sendNumericReply(client, 441, targetNick + " " + channelName + ": " + RED + "They aren't on that channel" + RESET);
        return;
    }

    std::string kickMsg = std::string(":") + BOLD + client->getPrefix() + " KICK " + channelName + " " + targetNick + ":" + RESET + " " + reason;
    _server->sendToClient(targetClient->getFd(), kickMsg);
    _server->broadcastToChannel(channelName, kickMsg, NULL);

    channel->removeMember(targetClient);
}

void Commands::cmdInvite(Client* client, const IRCMessage& msg) {
    if (msg.params.size() < 2) {
        sendNumericReply(client, 461, std::string("INVITE: ") + RED + "Not enough parameters. Usage: INVITE <nickname> <channel>" + RESET);
        return;
    }

    std::string targetNick = msg.params[0];
    std::string channelName = msg.params[1];

    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        sendNumericReply(client, 403, channelName + ": " + RED + "No such channel" + RESET);
        return;
    }

    if (!channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + ": " + RED + "You're not on that channel" + RESET);
        return;
    }

    if (channel->isInviteOnly() && !channel->isOperator(client)) {
        sendNumericReply(client, 482, channelName + ": " + RED + "You're not channel operator" + RESET);
        return;
    }

    Client* targetClient = _server->getClientByNick(targetNick);
    if (!targetClient) {
        sendNumericReply(client, 401, targetNick + ": " + RED + "No such nick/channel" + RESET);
        return;
    }

    if (channel->isMember(targetClient)) {
        sendNumericReply(client, 443, targetNick + " " + channelName + ": " + RED + "is already on channel" + RESET);
        return;
    }

    // Add to invite list
    channel->addToInviteList(targetClient);

    // Send invite to target
    std::string inviteMsg = std::string(":") + BOLD + client->getPrefix() + " INVITE " + targetNick + ":" + RESET + " " + channelName;
    _server->sendToClient(targetClient->getFd(), inviteMsg);

    // Confirm to sender
    sendNumericReply(client, 341, targetNick + " " + channelName);

    // Add confirmation message
    std::string confirmMsg = std::string(":ircserv!server@ircserver PRIVMSG ") + client->getNickname() + ": " + GREEN + client->getNickname() + " invited " + targetNick + " to " + channelName + RESET;
    _server->sendToClient(client->getFd(), confirmMsg);
}

void Commands::cmdTopic(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, std::string("TOPIC: ") + RED + "Not enough parameters. Usage: TOPIC <channel> [topic]" + RESET);
        return;
    }

    std::string channelName = msg.params[0];
    Channel* channel = _server->getChannel(channelName);

    if (!channel) {
        sendNumericReply(client, 403, channelName + ": " + RED + "No such channel" + RESET);
        return;
    }

    if (!channel->isMember(client)) {
        sendNumericReply(client, 442, channelName + ": " + RED + "You're not on that channel" + RESET);
        return;
    }

    if (msg.params.size() == 1) {
        // View topic
        if (channel->getTopic().empty()) {
            sendNumericReply(client, 331, channelName + ": " + YELLOW + "No topic is set" + RESET);
        } else {
            sendNumericReply(client, 332, channelName + ": " + CYAN + channel->getTopic() + RESET);
        }
    } else {
        // Set topic
        if (channel->isTopicRestricted() && !channel->isOperator(client)) {
            sendNumericReply(client, 482, channelName + ": " + RED + "You're not channel operator" + RESET);
            return;
        }

        std::string newTopic = msg.params[1];
        channel->setTopic(newTopic);

        std::string topicMsg = std::string(":") + BOLD + client->getPrefix() + " TOPIC " + channelName + ":" + RESET + " " + newTopic;
        _server->sendToClient(client->getFd(), topicMsg);
        _server->broadcastToChannel(channelName, topicMsg, client);
    }
}

void Commands::cmdMode(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, std::string("MODE: ") + RED + "Not enough parameters. Usage: MODE <channel> [+/-modes] [parameters]" + RESET);
        return;
    }

    std::string target = msg.params[0];
    
    // Check if it's a user mode (MODE nickname +flags)
    if (target == client->getNickname()) {
        // Handle user modes (like MODE john +i from irssi)
        // if (msg.params.size() > 1) {
        //     std::string modeString = msg.params[1];
        //     // Accept user modes but don't implement functionality (basic IRC compliance)
        //     std::string modeMsg = ":" + client->getPrefix() + " MODE " + target + " " + modeString;
        //     _server->sendToClient(client->getFd(), modeMsg);
        // }
        _server->sendToClient(client->getFd(), "User modes unavailable.");
        return;
    }
    
    // Handle channel modes
    Channel* channel = _server->getChannel(target);
    if (!channel) {
        sendNumericReply(client, 403, target + ": " + RED + "No such channel" + RESET);
        return;
    }

    if (!channel->isOperator(client)) {
        sendNumericReply(client, 482, target + ": " + RED + "You're not channel operator" + RESET);
        return;
    }

    if (msg.params.size() == 1) {
        // View modes (simplified)
        std::string modes = "+";
        if (channel->isInviteOnly()) modes += "i";
        if (channel->isTopicRestricted()) modes += "t";
        if (!channel->getKey().empty()) modes += "k";
        if (channel->getUserLimit() > 0) modes += "l";

        sendNumericReply(client, 324, target + " " + modes);
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
            std::string statusMsg = ":ircserv!server@ircserver PRIVMSG " + target + ": " + client->getNickname() + " set channel " + target + (adding ? " to invite only" : " to open access");
            _server->broadcastToChannel(target, statusMsg);
        } else if (mode == 't') {
            channel->setTopicRestricted(adding);
            std::string statusMsg = ":ircserv!server@ircserver PRIVMSG " + target + ": " + client->getNickname() + (adding ? " restricted topic changes to operators" : " allowed topic changes by all members") + " in " + target;
            _server->broadcastToChannel(target, statusMsg);
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

    std::string modeMsg = ":" + client->getPrefix() + " MODE " + target + " " + modeString;
    _server->sendToClient(client->getFd(), modeMsg);
    _server->broadcastToChannel(target, modeMsg, client);
}

void Commands::cmdWho(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 315, std::string("*: ") + YELLOW + "End of /WHO list" + RESET);
        return;
    }

    std::string target = msg.params[0];
    Channel* channel = _server->getChannel(target);

    if (channel) {
        const std::vector<Client*>& members = channel->getMembers();
        for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
            std::ostringstream oss;
            oss << target << " " << (*it)->getUsername() << " " << (*it)->getHostname() 
                << " server " << (*it)->getNickname() << " H: 0 " << (*it)->getRealname();
            sendNumericReply(client, 352, oss.str());
        }
    }

    sendNumericReply(client, 315, target + ": " + YELLOW + "End of /WHO list" + RESET);
}

void Commands::cmdQuit(Client* client, const IRCMessage& msg) {
    std::string reason = (msg.params.empty()) ? "Client Quit" : msg.params[0];
    std::string quitMsg = std::string(":") + client->getPrefix() + " QUIT :" + reason;

    // Broadcast quit message to all channels the client is in
    _server->broadcastQuitMessage(client, quitMsg);

    // Remove client from all channels - server will handle disconnect
    _server->removeClientFromChannels(client);
    // Note: Client will be disconnected by the server after command processing
}

void Commands::cmdPing(Client* client, const IRCMessage& msg) {
    if (msg.params.empty()) {
        sendNumericReply(client, 461, std::string("PING: ") + RED + "Not enough parameters" + RESET);
        return;
    }

    std::string pongMsg = std::string("PONG: ") + GREEN + msg.params[0] + RESET;
    _server->sendToClient(client->getFd(), pongMsg);
}

void Commands::cmdCap(Client* client, const IRCMessage& msg) {
    // Handle CAP (Client Capability Negotiation) - irssi compatibility
    if (msg.params.empty()) {
        return; // Ignore malformed CAP commands
    }

    std::string subCommand = msg.params[0];
    std::transform(subCommand.begin(), subCommand.end(), subCommand.begin(), ::toupper);

    if (subCommand == "LS") {
        // List capabilities - we don't support any advanced capabilities
        std::string nickname = client->getNickname().empty() ? "*" : client->getNickname();
        std::string response = ":ircserv CAP " + nickname + " LS :\r\n";
        _server->sendToClient(client->getFd(), response);
    } else if (subCommand == "END") {
        // End capability negotiation - client is ready to continue
        // No response needed, client will proceed with normal registration
        return;
    }
    // Ignore other CAP commands (REQ, ACK, etc.) for basic IRC compatibility
}

void Commands::sendWelcome(Client* client) {
    // Send standard IRC welcome sequence (001-004 replies)
    sendNumericReply(client, 001, std::string(": Welcome to the Internet Relay Network " + client->getPrefix()));
    sendNumericReply(client, 002, std::string(": Your host is ircserv, running version 1.0"));
    sendNumericReply(client, 003, std::string(": This server was created today"));
    sendNumericReply(client, 004, std::string("ircserv 1.0 o itkol"));

    // Send additional numeric replies that irssi expects
    sendNumericReply(client, 005, std::string("CHANTYPES=# PREFIX=(o)@ CHANLIMIT=#:10 CHANNELLEN=50 NICKLEN=9 NETWORK=ircserv : are supported by this server"));

    // Send MOTD (Message of the Day) - Critical for irssi to recognize connection completion
    sendNumericReply(client, 375, std::string(": - ircserv Message of the day - "));
    sendNumericReply(client, 372, std::string(": - Welcome to the IRC server!"));
    sendNumericReply(client, 372, std::string(": - This server is ready for use."));
    sendNumericReply(client, 376, std::string(": End of /MOTD command"));
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
