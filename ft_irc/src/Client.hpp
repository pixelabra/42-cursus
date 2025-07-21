/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>
# include <set>

enum ClientState
{
    CONNECTING,
    AUTHENTICATING,
    REGISTERING,
    REGISTERED
};

class Client
{
private:
    int _fd;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;
    std::string _buffer;
    std::string _sendBuffer;
    ClientState _state;
    bool _authenticated;
    bool _hasNick;
    bool _hasUser;
    std::set<std::string> _channels;
    
public:
    Client(int fd);
    ~Client();
    
    // Getters
    int getFd() const;
    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getRealname() const;
    const std::string& getHostname() const;
    const std::string& getBuffer() const;
    const std::string& getSendBuffer() const;
    ClientState getState() const;
    bool isAuthenticated() const;
    bool hasNickname() const;
    bool hasUsername() const;
    bool isRegistered() const;
    const std::set<std::string>& getChannels() const;
    
    // Setters
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    void setRealname(const std::string& realname);
    void setHostname(const std::string& hostname);
    void setState(ClientState state);
    void setAuthenticated(bool auth);
    void setHasNickname(bool hasNick);
    void setHasUsername(bool hasUser);
    
    // Buffer operations
    void appendToBuffer(const std::string& data);
    void clearBuffer();
    std::string extractLine();
    void appendToSendBuffer(const std::string& data);
    void clearSendBuffer(size_t bytes);
    
    // Channel operations
    void joinChannel(const std::string& channel);
    void leaveChannel(const std::string& channel);
    bool isInChannel(const std::string& channel) const;
    
    // Helper methods
    std::string getPrefix() const;
    void updateState();
};

#endif
