// Computer-Beaglebone networking

<<<<<<< HEAD
// int main();
int init_net();
int update_axis(int readSocketFD, int *axes);
=======
// File descriptors to indentify client and server sockets
// int client_socket;
int server_socket;

// struct sockaddr_in;
int init_net();
int update_axis(int sock,int *axes);
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
