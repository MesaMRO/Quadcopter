#include <sys/types.h>
#include <sys/socket.h>

// File descriptors to indentify client and server sockets
// int client_socket;
int server_socket;

// struct sockaddr_in;
int init_net();
int update_axis(int sock,int *axes);
