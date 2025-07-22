#ifndef IRCPARSER_HPP
#define IRCPARSER_HPP

#include <string>
#include <vector>

struct IRCMessage {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    
    IRCMessage() {}
};

class IRCParser {
public:
    IRCParser();
    ~IRCParser();

    IRCMessage parseMessage(const std::string& rawMessage);
    
private:
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string trim(const std::string& str);
};

#endif
