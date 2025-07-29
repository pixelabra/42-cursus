#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

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

    // Getters
    int getFd() const { return _fd; }
    int getClientNumber() const { return _clientNumber; }
    const std::string& getHostname() const { return _hostname; }
    const std::string& getNickname() const { return _nickname; }
    const std::string& getUsername() const { return _username; }
    const std::string& getRealname() const { return _realname; }
    bool isAuthenticated() const { return _authenticated; }
    bool isRegistered() const { return _registered; }

    // Setters
    void setNickname(const std::string& nick) { _nickname = nick; }
    void setUsername(const std::string& user) { _username = user; }
    void setRealname(const std::string& real) { _realname = real; }
    void setAuthenticated(bool auth) { _authenticated = auth; }
    void setRegistered(bool reg) { _registered = reg; }

    // Buffer management
    void addToBuffer(const std::string& data);
    bool getNextCommand(std::string& command);
    const std::string& getBuffer() const { return _buffer; }
    void clearBuffer() { _buffer.clear(); }
    
    // Oversized message handling
    bool isIgnoringOversizedInput() const { return _ignoreOversizedInput; }
    void setIgnoreOversizedInput(bool ignore) { _ignoreOversizedInput = ignore; }
    
    // Zero-read tracking for Ctrl+D handling
    int getConsecutiveZeroReads() const { return _consecutiveZeroReads; }
    void incrementZeroReads() { _consecutiveZeroReads++; }
    void resetZeroReads() { _consecutiveZeroReads = 0; }

    // Utility functions
    std::string getPrefix() const;
};

#endif
