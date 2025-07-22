#include "IRCParser.hpp"
#include <sstream>
#include <algorithm>

IRCParser::IRCParser() {
}

IRCParser::~IRCParser() {
}

IRCMessage IRCParser::parseMessage(const std::string& rawMessage) {
    IRCMessage message;
    std::string line = trim(rawMessage);
    
    if (line.empty()) {
        return message;
    }
    
    size_t pos = 0;
    
    // Check for prefix
    if (line[0] == ':') {
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            message.prefix = line.substr(1, spacePos - 1);
            pos = spacePos + 1;
        }
    }
    
    // Extract command
    size_t nextSpace = line.find(' ', pos);
    if (nextSpace == std::string::npos) {
        message.command = line.substr(pos);
        return message;
    }
    
    message.command = line.substr(pos, nextSpace - pos);
    pos = nextSpace + 1;
    
    // Extract parameters
    while (pos < line.length()) {
        if (line[pos] == ':') {
            // Trailing parameter
            message.params.push_back(line.substr(pos + 1));
            break;
        }
        
        nextSpace = line.find(' ', pos);
        if (nextSpace == std::string::npos) {
            message.params.push_back(line.substr(pos));
            break;
        }
        
        message.params.push_back(line.substr(pos, nextSpace - pos));
        pos = nextSpace + 1;
    }
    
    return message;
}

std::vector<std::string> IRCParser::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    
    return result;
}

std::string IRCParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}
