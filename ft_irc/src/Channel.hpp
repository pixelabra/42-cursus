/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:42:05 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:42:51 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

class Client;

class Channel {
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::vector<Client*> _members;
    std::set<Client*> _operators;
    std::set<Client*> _inviteList;
    bool _inviteOnly;
    bool _topicRestricted;
    int _userLimit;

public:
    Channel(const std::string& name, Client* creator);
    ~Channel();

    // getters
    const std::string& getName() const { return _name; }
    const std::string& getTopic() const { return _topic; }
    const std::string& getKey() const { return _key; }
    const std::vector<Client*>& getMembers() const { return _members; }
    bool isInviteOnly() const { return _inviteOnly; }
    bool isTopicRestricted() const { return _topicRestricted; }
    int getUserLimit() const { return _userLimit; }

    // setters
    void setTopic(const std::string& topic) { _topic = topic; }
    void setKey(const std::string& key) { _key = key; }
    void setInviteOnly(bool inviteOnly) { _inviteOnly = inviteOnly; }
    void setTopicRestricted(bool restricted) { _topicRestricted = restricted; }
    void setUserLimit(int limit) { _userLimit = limit; }

    // member management
    bool addMember(Client* client);
    void removeMember(Client* client);
    bool isMember(Client* client) const;

    // operator management
    void addOperator(Client* client);
    void removeOperator(Client* client);
    bool isOperator(Client* client) const;

    // invite management
    void addToInviteList(Client* client);
    void removeFromInviteList(Client* client);
    bool isInvited(Client* client) const;

    // utility functions
    std::string getMembersList() const;
    bool canJoin(Client* client, const std::string& key = "") const;
};

#endif
