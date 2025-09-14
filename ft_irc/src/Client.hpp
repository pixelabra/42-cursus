/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:40:55 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:41:38 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <algorithm>

class Client {
private:
    int _fd;
    int _clientNumber;
    std::string _hostname;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _buffer;
    bool _authenticated;
    bool _registered;
    bool _ignoreOversizedInput;
    int _consecutiveZeroReads;

public:
    Client(int fd, const std::string& hostname, int clientNumber);
    ~Client();

    // getters
    int getFd() const { return _fd; }
    int getClientNumber() const { return _clientNumber; }
    const std::string& getHostname() const { return _hostname; }
    const std::string& getNickname() const { return _nickname; }
    const std::string& getUsername() const { return _username; }
    const std::string& getRealname() const { return _realname; }
    bool isAuthenticated() const { return _authenticated; }
    bool isRegistered() const { return _registered; }

    // setters
    void setNickname(const std::string& nick) { _nickname = nick; }
    void setUsername(const std::string& user) { _username = user; }
    void setRealname(const std::string& real) { _realname = real; }
    void setAuthenticated(bool auth) { _authenticated = auth; }
    void setRegistered(bool reg) { _registered = reg; }

    // buffer management
    void addToBuffer(const std::string& data);
    bool getNextCommand(std::string& command);
    const std::string& getBuffer() const { return _buffer; }
    void clearBuffer() { _buffer.clear(); }
    
    // oversized message handling
    bool isIgnoringOversizedInput() const { return _ignoreOversizedInput; }
    void setIgnoreOversizedInput(bool ignore) { _ignoreOversizedInput = ignore; }
    
    // zero-read tracking for ctrl-d handling
    int getConsecutiveZeroReads() const { return _consecutiveZeroReads; }
    void incrementZeroReads() { _consecutiveZeroReads++; }
    void resetZeroReads() { _consecutiveZeroReads = 0; }

    // util functions
    std::string getPrefix() const;
};

#endif
