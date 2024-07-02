#include "defines.h"

std::mutex out_mutex;
void read_client( int client_sockfd );



void server()
{
    int sockfd = init_tcp_socket();

    sockaddr_in address = init_internet_addresses(PORT, IP);
    socklen_t addrlen = sizeof( address );

    if( bind( sockfd, (struct sockaddr*)&address, addrlen) < 0 )
    {
        std::cerr << "bind failed" << std::endl;
        exit( EXIT_FAILURE );
    }
    if( listen( sockfd, 1 ) < 0 )
    {
        std::cerr << "listen failed" << std::endl;
        exit( EXIT_FAILURE );
    }

    std::cout << "Waiting for a client..." << std::endl;

    int accepted_sockfd;
    while( true )
    {
        if( ( accepted_sockfd = accept( sockfd, (struct sockaddr*)&address, &addrlen ) ) < 0 )
        {
            std::cerr << "accept failed" << std::endl;
            exit( EXIT_FAILURE );
        }

        std::cout << "Client connected" << std::endl;
        std::thread new_socket_thread( &read_client , accepted_sockfd );
        new_socket_thread.detach();
    }

    close( sockfd );
}


void read_client( int client_sockfd )
{
    char buffer[1024] = { 0 };
    ssize_t bytes_read;

    while( true )
    {
        if( ( bytes_read = read( client_sockfd, buffer, 1024 ) ) < 0 )
        {
            out_mutex.lock();
            std::cerr << "read failed" << std::endl;
            out_mutex.unlock();
            exit( EXIT_FAILURE );
        }
 
        if( bytes_read > 0 )
        {
		    out_mutex.lock();
            std::cout << "Client: " << buffer << std::endl;
		    out_mutex.unlock();

			if(buffer == "hello"s)
                send( client_sockfd, "world", 6, 0);
            else if( buffer == "disconnect"s )
            {
                send( client_sockfd, "Server disconnected you", 25, 0);
			    out_mutex.lock();
			    std::cout << "Client disconnected" << std::endl;
			    out_mutex.unlock();
                break;
            }
            else
                send( client_sockfd, buffer, strlen(buffer) + 1, 0);
            memset( buffer, 0, 1024 );
        }

        if( check_on_close(client_sockfd, buffer) )
        {
			out_mutex.lock();
			std::cout << "Client disconnected" << std::endl;
			out_mutex.unlock();
			break;
		}
    }

    close( client_sockfd );
}



