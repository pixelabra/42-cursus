/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:29:41 by ppolinta          #+#    #+#             */
/*   Updated: 2025/07/31 21:29:49 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

Server* g_server = NULL;

void signalHandler(int signal) {
    (void)signal;
    if (g_server) {
        std::cout << "\nShutting down server..." << std::endl;
        g_server->shutdown();
        delete g_server;
        std::exit(0);
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        std::cerr << "Error: Invalid port number" << std::endl;
        return 1;
    }

    std::string password = argv[2];
    if (password.empty()) {
        std::cerr << "Error: Password cannot be empty" << std::endl;
        return 1;
    }
    for (size_t i = 0; i < password.size(); i++) {
        if (password[i] < 33 || password[i] > 126) {
            std::cerr << "Error: Password contains invalid characters" << std::endl;
            return 1;
        }
    }

    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGTSTP, signalHandler);
    std::signal(SIGQUIT, signalHandler);

    try {
        Server* server = new Server(port, password);
        g_server = server;
        server->run();
        delete server;
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        if (g_server) {
            delete g_server;
        }
        return 1;
    }

    return 0;
}
