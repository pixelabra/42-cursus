/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:42:37 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:42:48 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(const std::string& name, Client* creator) 
    : _name(name), _inviteOnly(false), _topicRestricted(true), _userLimit(0) {
    addMember(creator);
    addOperator(creator);
}

Channel::~Channel() {
}

bool Channel::addMember(Client* client) {
    if (isMember(client)) {
        return false;
    }
    
    if (_userLimit > 0 && static_cast<int>(_members.size()) >= _userLimit) {
        return false;
    }
    
    _members.push_back(client);
    return true;
}

void Channel::removeMember(Client* client) {
    std::vector<Client*>::iterator it = std::find(_members.begin(), _members.end(), client);
    if (it != _members.end()) {
        _members.erase(it);
    }
    removeOperator(client);
    removeFromInviteList(client);
    removeFromInviteList(client);
}

bool Channel::isMember(Client* client) const {
    return std::find(_members.begin(), _members.end(), client) != _members.end();
}

void Channel::addOperator(Client* client) {
    _operators.insert(client);
}

void Channel::removeOperator(Client* client) {
    _operators.erase(client);
}

bool Channel::isOperator(Client* client) const {
    return _operators.find(client) != _operators.end();
}

std::string Channel::getMembersList() const {
    std::ostringstream oss;
    for (std::vector<Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if (it != _members.begin()) {
            oss << " ";
        }
        if (isOperator(*it)) {
            oss << "@";
        }
        oss << (*it)->getNickname();
    }
    return oss.str();
}

void Channel::addToInviteList(Client* client) {
    _inviteList.insert(client);
}

void Channel::removeFromInviteList(Client* client) {
    _inviteList.erase(client);
}

bool Channel::isInvited(Client* client) const {
    return _inviteList.find(client) != _inviteList.end();
}

bool Channel::canJoin(Client* client, const std::string& key) const {
    if (_inviteOnly && !isInvited(client)) {
        return false;
    }
    
    if (!_key.empty() && _key != key) {
        return false;
    }
    
    if (_userLimit > 0 && static_cast<int>(_members.size()) >= _userLimit) {
        return false;
    }
    
    return true;
}
