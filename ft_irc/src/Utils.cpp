/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/21 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <ctime>

std::vector<std::string> Utils::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

std::string Utils::trim(const std::string& str)
{
    std::string::size_type start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    
    std::string::size_type end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string Utils::toLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string Utils::toUpperCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool Utils::isValidNickname(const std::string& nickname)
{
    if (nickname.empty() || nickname.length() > 9)
        return false;
    
    // First character must be letter or special character
    if (!std::isalpha(nickname[0]) && nickname[0] != '[' && nickname[0] != ']' &&
        nickname[0] != '{' && nickname[0] != '}' && nickname[0] != '\\' &&
        nickname[0] != '|' && nickname[0] != '^' && nickname[0] != '_')
        return false;
    
    // Rest can be letters, digits, or special characters
    for (std::string::size_type i = 1; i < nickname.length(); ++i)
    {
        char c = nickname[i];
        if (!std::isalnum(c) && c != '[' && c != ']' && c != '{' && c != '}' &&
            c != '\\' && c != '|' && c != '^' && c != '_' && c != '-')
            return false;
    }
    return true;
}

bool Utils::isValidChannelName(const std::string& channel)
{
    if (channel.empty() || channel.length() > 50)
        return false;
    
    if (channel[0] != '#' && channel[0] != '&')
        return false;
    
    // Channel names cannot contain spaces, commas, or control characters
    for (std::string::size_type i = 1; i < channel.length(); ++i)
    {
        char c = channel[i];
        if (c == ' ' || c == ',' || c == '\a' || c < 32 || c == 127)
            return false;
    }
    return true;
}

std::string Utils::getCurrentTime()
{
    std::time_t now = std::time(0);
    return intToString(static_cast<int>(now));
}

int Utils::stringToInt(const std::string& str)
{
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

std::string Utils::intToString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}
