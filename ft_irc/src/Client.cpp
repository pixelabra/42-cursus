#include "Client.hpp"
#include <algorithm>

Client::Client(int fd, const std::string& hostname, int clientNumber) 
    : _fd(fd), _clientNumber(clientNumber), _hostname(hostname), _authenticated(false), _registered(false) {
}

Client::~Client() {
}

void Client::addToBuffer(const std::string& data) {
    _buffer += data;
}

bool Client::getNextCommand(std::string& command) {
    size_t pos = _buffer.find("\r\n");
    if (pos == std::string::npos) {
        pos = _buffer.find('\n');
    }
    
    if (pos != std::string::npos) {
        command = _buffer.substr(0, pos);
        _buffer.erase(0, pos + ((_buffer[pos] == '\r') ? 2 : 1));
        return true;
    }
    return false;
}

std::string Client::getPrefix() const {
    if (_nickname.empty()) {
        return _hostname;
    }
    return _nickname + "!" + _username + "@" + _hostname;
}
