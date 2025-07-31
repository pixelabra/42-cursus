/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:41:32 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:58:13 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, const std::string& hostname, int clientNumber) 
    : _fd(fd), _clientNumber(clientNumber), _hostname(hostname), _authenticated(false), _registered(false), _ignoreOversizedInput(false), _consecutiveZeroReads(0) {
}

Client::~Client() {}

void Client::addToBuffer(const std::string& data) {
    _buffer += data;

    if (_buffer.length() > 512) {
        _buffer = _buffer.substr(_buffer.length() - 512);
    }
}

bool Client::getNextCommand(std::string& command) {
    size_t pos = _buffer.find("\r\n");
    if (pos == std::string::npos) {
        pos = _buffer.find('\n');
    }
    
    if (pos != std::string::npos) {
        command = _buffer.substr(0, pos);
        
        if (command.length() > 510) {
            command = command.substr(0, 510);
        }
        
        _buffer.erase(0, pos + ((_buffer[pos] == '\r') ? 2 : 1));
        return true;
    }
    
    if (_buffer.length() > 1024) {
        _buffer.clear();
    }
    
    return false;
}

std::string Client::getPrefix() const {
    if (_nickname.empty()) {
        return _hostname;
    }
    return _nickname + "!" + _username + "@" + _hostname;
}
