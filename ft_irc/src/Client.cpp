#include "Client.hpp"
#include <algorithm>

Client::Client(int fd, const std::string& hostname, int clientNumber) 
    : _fd(fd), _clientNumber(clientNumber), _hostname(hostname), _authenticated(false), _registered(false) {
}

Client::~Client() {
}

void Client::addToBuffer(const std::string& data) {
    _buffer += data;
    
    // IRC RFC 2812: Prevent buffer from accumulating oversized messages
    if (_buffer.length() > 512) {
        // Keep only the last 512 characters to prevent memory issues
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
        
        // IRC RFC 2812: Maximum message length is 512 characters including CRLF
        if (command.length() > 510) {
            command = command.substr(0, 510); // Truncate to legal IRC length
        }
        
        _buffer.erase(0, pos + ((_buffer[pos] == '\r') ? 2 : 1));
        return true;
    }
    
    // Prevent buffer from growing too large with incomplete messages
    if (_buffer.length() > 1024) {
        _buffer.clear(); // Reset if buffer gets too large
    }
    
    return false;
}

std::string Client::getPrefix() const {
    if (_nickname.empty()) {
        return _hostname;
    }
    return _nickname + "!" + _username + "@" + _hostname;
}
