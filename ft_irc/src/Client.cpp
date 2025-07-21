/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sstream>

Client::Client(int fd) : _fd(fd), _state(CONNECTING), _authenticated(false),
                        _hasNick(false), _hasUser(false)
{
    _hostname = "localhost";
}

Client::~Client()
{
}

// Getters
int Client::getFd() const
{
    return _fd;
}

const std::string& Client::getNickname() const
{
    return _nickname;
}

const std::string& Client::getUsername() const
{
    return _username;
}

const std::string& Client::getRealname() const
{
    return _realname;
}

const std::string& Client::getHostname() const
{
    return _hostname;
}

const std::string& Client::getBuffer() const
{
    return _buffer;
}

const std::string& Client::getSendBuffer() const
{
    return _sendBuffer;
}

ClientState Client::getState() const
{
    return _state;
}

bool Client::isAuthenticated() const
{
    return _authenticated;
}

bool Client::hasNickname() const
{
    return _hasNick;
}

bool Client::hasUsername() const
{
    return _hasUser;
}

bool Client::isRegistered() const
{
    return _state == REGISTERED;
}

const std::set<std::string>& Client::getChannels() const
{
    return _channels;
}

// Setters
void Client::setNickname(const std::string& nickname)
{
    _nickname = nickname;
    _hasNick = !nickname.empty();
    updateState();
}

void Client::setUsername(const std::string& username)
{
    _username = username;
    _hasUser = !username.empty();
    updateState();
}

void Client::setRealname(const std::string& realname)
{
    _realname = realname;
}

void Client::setHostname(const std::string& hostname)
{
    _hostname = hostname;
}

void Client::setState(ClientState state)
{
    _state = state;
}

void Client::setAuthenticated(bool auth)
{
    _authenticated = auth;
    updateState();
}

void Client::setHasNickname(bool hasNick)
{
    _hasNick = hasNick;
    updateState();
}

void Client::setHasUsername(bool hasUser)
{
    _hasUser = hasUser;
    updateState();
}

// Buffer operations
void Client::appendToBuffer(const std::string& data)
{
    _buffer += data;
}

void Client::clearBuffer()
{
    _buffer.clear();
}

std::string Client::extractLine()
{
    std::string::size_type pos = _buffer.find("\r\n");
    if (pos == std::string::npos)
        pos = _buffer.find("\n");
    
    if (pos != std::string::npos)
    {
        std::string line = _buffer.substr(0, pos);
        _buffer.erase(0, pos + (_buffer[pos] == '\r' ? 2 : 1));
        return line;
    }
    return "";
}

void Client::appendToSendBuffer(const std::string& data)
{
    _sendBuffer += data;
}

void Client::clearSendBuffer(size_t bytes)
{
    if (bytes >= _sendBuffer.length())
        _sendBuffer.clear();
    else
        _sendBuffer.erase(0, bytes);
}

// Channel operations
void Client::joinChannel(const std::string& channel)
{
    _channels.insert(channel);
}

void Client::leaveChannel(const std::string& channel)
{
    _channels.erase(channel);
}

bool Client::isInChannel(const std::string& channel) const
{
    return _channels.find(channel) != _channels.end();
}

// Helper methods
std::string Client::getPrefix() const
{
    return _nickname + "!" + _username + "@" + _hostname;
}

void Client::updateState()
{
    if (_state == CONNECTING && _authenticated)
    {
        _state = AUTHENTICATING;
    }
    else if (_state == AUTHENTICATING && _hasNick && _hasUser)
    {
        _state = REGISTERING;
    }
    else if (_state == REGISTERING)
    {
        _state = REGISTERED;
    }
}
