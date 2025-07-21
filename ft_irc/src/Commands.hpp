/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <string>
# include <vector>

class Server;
class Client;

class Commands
{
private:
    Server* _server;
    
public:
    Commands(Server* server);
    ~Commands();
    
    void processCommand(Client* client, const std::string& line);
    
private:
    // Connection commands
    void handlePass(Client* client, const std::vector<std::string>& params);
    void handleNick(Client* client, const std::vector<std::string>& params);
    void handleUser(Client* client, const std::vector<std::string>& params);
    void handleQuit(Client* client, const std::vector<std::string>& params);
    void handlePing(Client* client, const std::vector<std::string>& params);
    void handlePong(Client* client, const std::vector<std::string>& params);
    
    // Channel commands
    void handleJoin(Client* client, const std::vector<std::string>& params);
    void handlePart(Client* client, const std::vector<std::string>& params);
    void handleTopic(Client* client, const std::vector<std::string>& params);
    void handleNames(Client* client, const std::vector<std::string>& params);
    void handleList(Client* client, const std::vector<std::string>& params);
    
    // Message commands
    void handlePrivmsg(Client* client, const std::vector<std::string>& params);
    void handleNotice(Client* client, const std::vector<std::string>& params);
    
    // Operator commands
    void handleKick(Client* client, const std::vector<std::string>& params);
    void handleInvite(Client* client, const std::vector<std::string>& params);
    void handleMode(Client* client, const std::vector<std::string>& params);
    
    // Helper methods
    std::vector<std::string> parseCommand(const std::string& line);
    void sendWelcome(Client* client);
    void broadcastToChannel(const std::string& channel, const std::string& message, Client* exclude);
    void sendChannelMemberList(Client* client, const std::string& channel);
};

// IRC Reply codes
# define RPL_WELCOME 001
# define RPL_YOURHOST 002
# define RPL_CREATED 003
# define RPL_MYINFO 004
# define RPL_UMODEIS 221
# define RPL_CHANNELMODEIS 324
# define RPL_NOTOPIC 331
# define RPL_TOPIC 332
# define RPL_INVITING 341
# define RPL_NAMREPLY 353
# define RPL_ENDOFNAMES 366

# define ERR_NOSUCHNICK 401
# define ERR_NOSUCHCHANNEL 403
# define ERR_CANNOTSENDTOCHAN 404
# define ERR_NORECIPIENT 411
# define ERR_NOTEXTTOSEND 412
# define ERR_UNKNOWNCOMMAND 421
# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_USERNOTINCHANNEL 441
# define ERR_NOTONCHANNEL 442
# define ERR_USERONCHANNEL 443
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTRED 462
# define ERR_PASSWDMISMATCH 464
# define ERR_CHANNELISFULL 471
# define ERR_INVITEONLYCHAN 473
# define ERR_BADCHANNELKEY 475
# define ERR_CHANOPRIVSNEEDED 482

#endif
