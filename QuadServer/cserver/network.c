// Computer-Beaglebone networking

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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