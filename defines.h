#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <cerrno>
#include <thread>
#include <mutex>
#include <cstring>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

using namespace std::string_literals;
constexpr auto PORT = 7777;
constexpr auto IP = INADDR_ANY;

int init_tcp_socket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
        std::cerr << "socket failed" << std::endl;
        exit( EXIT_FAILURE );
	}
    return sockfd;
}

sockaddr_in init_internet_addresses(uint16_t port, uint32_t ip) {
    sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = ip;
    return address;
}

bool check_on_close( int sockfd, char( &buffer )[1024] )
{
	return recv( sockfd, buffer, sizeof( buffer ), MSG_PEEK | MSG_DONTWAIT ) == 0;
}
