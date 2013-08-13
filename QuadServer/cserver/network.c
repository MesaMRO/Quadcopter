#include <sys/types.h>

#ifdef WIN32
	#include <winsock.h>
#else
	#include <sys/socket.h>
#endif

int init_net() {
	// File descriptors to indentify client and server sockets
	int client_socket;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in address;
	 /*
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(1337);
	bind(server_socket, (struct sockaddr *)&address, sizeof(address));
	listen(server_socket, 1);
	clientsock = accept(server_socket, (struct sockaddr *)&address, sizeof(address));
	return clientsock;
	*/
}


