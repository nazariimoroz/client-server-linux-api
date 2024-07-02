#include "defines.h"

void client()
{
    int sockfd = init_tcp_socket();

    sockaddr_in address = init_internet_addresses(PORT, IP);
    socklen_t addrlen = sizeof( address );

    if( connect( sockfd, (struct sockaddr*)&address, sizeof( address ) ) < 0 )
    {
        std::cout << "connect failed" << std::endl;
        exit( EXIT_FAILURE );
    }

	std::cout << "Connected to server" << std::endl;
    std::string message_to_send;
    ssize_t bytes_read;
	char buffer[1024];
    while( true )
    {
        std::cout << "Message: ";
        std::getline( std::cin, message_to_send );
        if( send( sockfd, message_to_send.c_str(), message_to_send.size(), 0 ) < 0 )
        {
            std::cerr << "send failed" << std::endl;
            exit( EXIT_FAILURE );
        }

        if( ( bytes_read = read( sockfd, buffer, 1024 ) ) < 0 )
        {
            std::cerr << "read failed" << std::endl;
            exit( EXIT_FAILURE );
        }
        if( bytes_read > 0 )
        {
            std::cout << "Server: " << buffer << std::endl;
            memset( buffer, 0, 1024 );
        }
		
        if( check_on_close(sockfd, buffer) )
        {
            std::cout << "Server closed" << std::endl;
            break;
        }
    }

	close( sockfd );
}
