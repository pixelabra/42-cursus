/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:30:25 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/21 14:30:25 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Utils.hpp"
#include <sstream>

Channel::Channel(const std::string& name) : _name(name), _inviteOnly(false),
                                           _topicRestricted(true), _userLimit(0)
{
    _creationTime = Utils::getCurrentTime();
}

Channel::~Channel()
{
}

// Getters
const std::string& Channel::getName() const
{
    return _name;
}

const std::string& Channel::getTopic() const
{
    return _topic;
}

const std::string& Channel::getKey() const
{
    return _key;
}

const std::set<std::string>& Channel::getMembers() const
{
    return _members;
}

const std::set<std::string>& Channel::getOperators() const
{
    return _operators;
}

const std::set<std::string>& Channel::getInvited() const
{
    return _invited;
}

bool Channel::isInviteOnly() const
{
    return _inviteOnly;
}

bool Channel::isTopicRestricted() const
{
    return _topicRestricted;
}

int Channel::getUserLimit() const
{
    return _userLimit;
}

const std::string& Channel::getCreationTime() const
{
    return _creationTime;
}

// Setters
void Channel::setTopic(const std::string& topic)
{
    _topic = topic;
}

void Channel::setKey(const std::string& key)
{
    _key = key;
}

void Channel::setInviteOnly(bool inviteOnly)
{
    _inviteOnly = inviteOnly;
}

void Channel::setTopicRestricted(bool topicRestricted)
{
    _topicRestricted = topicRestricted;
}

void Channel::setUserLimit(int limit)
{
    _userLimit = limit;
}

// Member management
bool Channel::addMember(const std::string& nickname)
{
    if (_userLimit > 0 && static_cast<int>(_members.size()) >= _userLimit)
        return false;
    
    _members.insert(nickname);
    
    // First member becomes operator
    if (_members.size() == 1)
        _operators.insert(nickname);
    
    // Remove from invited list if present
    _invited.erase(nickname);
    
    return true;
}

void Channel::removeMember(const std::string& nickname)
{
    _members.erase(nickname);
    _operators.erase(nickname);
    _invited.erase(nickname);
}

bool Channel::isMember(const std::string& nickname) const
{
    return _members.find(nickname) != _members.end();
}

size_t Channel::getMemberCount() const
{
    return _members.size();
}

// Operator management
void Channel::addOperator(const std::string& nickname)
{
    if (isMember(nickname))
        _operators.insert(nickname);
}

void Channel::removeOperator(const std::string& nickname)
{
    _operators.erase(nickname);
}

bool Channel::isOperator(const std::string& nickname) const
{
    return _operators.find(nickname) != _operators.end();
}

// Invite management
void Channel::addInvite(const std::string& nickname)
{
    _invited.insert(nickname);
}

void Channel::removeInvite(const std::string& nickname)
{
    _invited.erase(nickname);
}

bool Channel::isInvited(const std::string& nickname) const
{
    return _invited.find(nickname) != _invited.end();
}

// Helper methods
bool Channel::canJoin(const std::string& nickname, const std::string& key) const
{
    // Check if already a member
    if (isMember(nickname))
        return false;
    
    // Check user limit
    if (_userLimit > 0 && static_cast<int>(_members.size()) >= _userLimit)
        return false;
    
    // Check invite-only mode
    if (_inviteOnly && !isInvited(nickname))
        return false;
    
    // Check key
    if (!_key.empty() && key != _key)
        return false;
    
    return true;
}

std::string Channel::getModeString() const
{
    std::string modes = "+";
    
    if (_inviteOnly)
        modes += "i";
    if (_topicRestricted)
        modes += "t";
    if (!_key.empty())
        modes += "k";
    if (_userLimit > 0)
        modes += "l";
    
    if (modes == "+")
        modes = "";
    
    return modes;
}

std::string Channel::getMemberList() const
{
    std::string list;
    
    for (std::set<std::string>::const_iterator it = _members.begin(); 
         it != _members.end(); ++it)
    {
        if (!list.empty())
            list += " ";
        
        if (isOperator(*it))
            list += "@";
        
        list += *it;
    }
    
    return list;
}
