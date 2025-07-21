/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include <map>

class Channel
{
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::set<std::string> _members;
    std::set<std::string> _operators;
    std::set<std::string> _invited;
    bool _inviteOnly;
    bool _topicRestricted;
    int _userLimit;
    std::string _creationTime;
    
public:
    Channel(const std::string& name);
    ~Channel();
    
    // Getters
    const std::string& getName() const;
    const std::string& getTopic() const;
    const std::string& getKey() const;
    const std::set<std::string>& getMembers() const;
    const std::set<std::string>& getOperators() const;
    const std::set<std::string>& getInvited() const;
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    int getUserLimit() const;
    const std::string& getCreationTime() const;
    
    // Setters
    void setTopic(const std::string& topic);
    void setKey(const std::string& key);
    void setInviteOnly(bool inviteOnly);
    void setTopicRestricted(bool topicRestricted);
    void setUserLimit(int limit);
    
    // Member management
    bool addMember(const std::string& nickname);
    void removeMember(const std::string& nickname);
    bool isMember(const std::string& nickname) const;
    size_t getMemberCount() const;
    
    // Operator management
    void addOperator(const std::string& nickname);
    void removeOperator(const std::string& nickname);
    bool isOperator(const std::string& nickname) const;
    
    // Invite management
    void addInvite(const std::string& nickname);
    void removeInvite(const std::string& nickname);
    bool isInvited(const std::string& nickname) const;
    
    // Helper methods
    bool canJoin(const std::string& nickname, const std::string& key) const;
    std::string getModeString() const;
    std::string getMemberList() const;
};

#endif
