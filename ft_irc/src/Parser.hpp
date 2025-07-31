/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:34:37 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 22:35:55 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Parser_HPP
#define Parser_HPP

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Message {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    
    Message() {}
};

class Parser {
public:
    Parser();
    ~Parser();

    Message parseMessage(const std::string& rawMessage);
    
private:
    std::string trim(const std::string& str);
};

#endif
