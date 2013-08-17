#include <sys/types.h>
#include <stdio.h>
#ifdef WIN32
	#include <winsock.h>
#else
	#include <sys/socket.h>
#endif
#include <netinet/in.h>

int init_net() {
	// File descriptors to indentify client and server sockets
	int client_socket;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t size;
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(1337);
	bind(server_socket, (struct sockaddr *)&address, sizeof(address));
	listen(server_socket, 1);
	size=sizeof(address);
	printf("%s\n","listening");
	client_socket = accept(server_socket, (struct sockaddr *)&address, &size);
	printf("connected\n");
	return client_socket;
}

void update_axis(int sock,int *axes) {
  int buff[2];
  recv(sock,buff,8,0);
  axes[buff[0]]=buff[1];
}
