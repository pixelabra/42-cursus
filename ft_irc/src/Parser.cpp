/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:34:39 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:36:51 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

Message Parser::parseMessage(const std::string& rawMessage) {
    Message message;
    std::string line = trim(rawMessage);
    
    if (line.empty()) {
        return message;
    }
    
    size_t pos = 0;
    
    if (line[0] == ':') {
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            message.prefix = line.substr(1, spacePos - 1);
            pos = spacePos + 1;
        }
    }
    
    size_t nextSpace = line.find(' ', pos);
    if (nextSpace == std::string::npos) {
        message.command = line.substr(pos);
        return message;
    }
    
    message.command = line.substr(pos, nextSpace - pos);
    pos = nextSpace + 1;
    
    while (pos < line.length()) {
        if (line[pos] == ':') {
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

std::vector<std::string> Parser::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    
    return result;
}

std::string Parser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}
