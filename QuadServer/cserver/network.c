<<<<<<< HEAD
// Computer-Beaglebone networking

=======
#include "network.h"
#include <sys/types.h>
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

<<<<<<< HEAD
#define TRUE 1
#define FALSE 0

// Host network socket IP and Port
#define HOST_ADDR_IP INADDR_ANY // Host machine IP
#define HOST_ADDR_PORT 1337

int init_net(int log_onoff) {
	// Need to do errorchecking for net functions
	// Those that return 0 and -1
	
	int log_onoff = log_onoff;
	
	int server_sock, client_sock; // Server and client socket file descriptors
	struct sockaddr_in server_addr; // Server address
	struct sockaddr_in client_addr; // Client address
	
	// Create server socket
	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "%s", "Failed to create server socket");
		exit(1);
	}
	
	// Set server socket linger rule
	struct linger server_sock_linger;
	server_sock_linger.l_onoff = TRUE;
	server_sock_linger.l_linger = 10; // Seconds
	if (setsockopt(server_sock, SOL_SOCKET, SO_LINGER, &server_sock_linger, sizeof(linger)) == -1) {
		fprint(stderr, "%s", "Failed to set SO_LINGER for server socket");
	}

	// Settup server socket address
	serverAddress.sin_family = AF_INET; // Internet protocol address family
	serverAddress.sin_addr.s_addr = htons(HOST_ADDR_IP);
	serverAddress.sin_port = htons(HOST_ADDR_PORT);
	memset(&(serverAddress.sin_zero), '\0', 8); // Pad server address to length of a sockaddr struct
	// socklen_t addressSize;
	int addressSize = sizeof(serverAddress);
	
	// Bind server socket
	bind(serverSock, (struct sockaddr *)&serverAddress, addressSize);
	
	// Listen on newly bound server socket
	listen(serverSock, 1); // Only one connection allowed on incoming queue
	printf("Listening on server socket at %s:%s)\n", serverAddress.sin_addr, serverAddress.sin_port);
	
	// Accept new client socket
	addressSize = sizeof(struct sockaddr_in);
	clientSock = accept(serverSock, (struct sockaddr *)&clientAddress, &addressSize);
	printf("Connected to client at %s\n", clientAddress.sin_addr);
	
	return clientSock;
=======
int init_net() {
	// File descriptors to indentify client and server sockets
	int client_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t size;
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(1337);
	if(bind(server_socket, (struct sockaddr *)&address, sizeof(address))<0) {
		printf("net fail\n");
	}
	listen(server_socket, 1);
	size=sizeof(address);
	printf("%s\n","listening");
	client_socket = accept(server_socket, (struct sockaddr *)&address, &size);
	printf("connected\n");
	return client_socket;
}

int update_axis(int sock,int *axes) {
  int buff[2];
  if(recv(sock,buff,8,0)!=8) {
    return 0;
  }
  axes[buff[0]]=buff[1];
  return 1;
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
}

const int messageLengthMax = 8;

// Byte structure of packet to recieve?
int update_axis(int readSock, int *axes) {
	int buffer[2];
	// Recieve message from connected socket
	int recvReturn = recv(readSock, buffer, axesPacketLength, 0);
	
	// Interpret recv() return value
	if (recvReturn == axesPacketLength) {
		// Message recieved with correct byte length
		axes[buffer[0]] = buffer[1];
		return 1;
	} else if (recvReturn == 0) {
		// Client socket shutdown gracefully
		return 0;
	} else {
		// Error, "errno" set to indicate error type
		return -1;
	}
}
