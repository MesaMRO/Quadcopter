// Computer-Beaglebone networking
#include "network.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0

// Host network socket IP and Port
#define HOST_ADDR_IP INADDR_ANY // Host machine IP
#define HOST_ADDR_PORT 1337

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
}

