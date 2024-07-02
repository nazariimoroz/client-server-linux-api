#include "client.h"
#include "server.h"

int main(int argc, char* argv[])
{	
    if( argc != 2 )
    {
		std::cerr << "Usage: " << argv[0] << " <server|client>" << std::endl;
        exit( EXIT_FAILURE );
    }

    if( argv[1] == "server"s )
        server();
	else if( argv[1] == "client"s )
		client();
	else
	{
		std::cerr << "Usage: " << argv[0] << " <server|client>" << std::endl;
		exit( EXIT_FAILURE );
    }
	
	return 0;
}

