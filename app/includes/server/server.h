#ifndef SERVER_H
#define SERVER_H

/* #include <netinet/in.h> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include <sys/socket.h> */
//#include <unistd.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/socket.h>


#define PORT 8080
const int port = 8080;

typedef struct Server
{
    int server_fd;
    int new_socket;
    int valread;
	struct sockaddr_in address;
	int opt;
	socklen_t addrlen;
	char buffer[1024];
    
} Server;


int startWebsocket(Server *server);

int createSocket(Server *server);
void startListening(Server *server);
void initiateSocket(Server *server);
int bindSocket(Server *server);
int acceptConnection(Server *server);
void handleMessages(Server *Server);


#endif