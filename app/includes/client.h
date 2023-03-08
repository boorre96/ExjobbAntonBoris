#ifndef CLIENT_H_
#define CLIENT_H_
#define PORT 8080

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    int clientFd;
    struct sockaddr_in serverAddress;
} Client;

void clientInit(Client* client);
void clientCleanup(Client* client);
int clientConnect(Client* client, const char* serverIp);
int clientSend(Client* client, const char* msg);
int clientReceive(Client* client, char* buffer, int size);


#endif /*CLIENT_H_*/