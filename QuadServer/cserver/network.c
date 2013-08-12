#include <sys/types.h>
#include <sys/socket.h>

int init_net() {
  int clientsock;
  int sock = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(1337);
  bind(sock,(struct sockaddr *)&address,sizeof(address));
  listen(sock,1);
  clientsock = accept(sock,(struct sockaddr *)&address,sizeof(address));+
  return clientsock;
}


