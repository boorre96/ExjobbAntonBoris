// Client side C/C++ program to demonstrate Socket
// programming
#include "client.h"

void clientInit(Client* client){
    client->clientFd = -1;
    memset(&client->serverAddress, 0, sizeof(client->serverAddress));
    client->serverAddress.sin_family = AF_INET;
    client->serverAddress.sin_port = htons(PORT);
}

void clientCleanup(Client* client){
    if(client->clientFd != -1){
        close(client->clientFd);
        client->clientFd = -1;
    }
}

int clientConnect(Client* client, const char* serverIp){
    if(client->clientFd != -1){
        printf("Socket already created\n");
        return -1;
    }

    if(inet_pton(AF_INET, serverIp, &client->serverAddress.sin_addr) <= 0){
        printf("Invalid address \n");
        return -1;
    }

    if((client->clientFd=socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Socket creation errror \n");
        return -1;
    }

    if(connect(client->clientFd, (struct sockaddr*)&client->serverAddress, sizeof(client->serverAddress)) < 0 ){
        printf("Connection failed \n");
        return -1;
    }
    return 0;
}

int clientSend(Client* client, const char* msg){
    if(send(client->clientFd, msg, strlen(msg),0) == -1){
        printf("Send failed \n");
        return -1;
    }
}

int clientReceive(Client* client, char* buffer, int size){
    int bytesReceived = 0;

    if((bytesReceived = read(client->clientFd, buffer, size)) == -1){
        printf("Receive failed \n");
    }

    return 0;
}


int main (void) {
    Client client;
	char buffer[1024] = {0};

	clientInit(&client);
	if(clientConnect(&client, "127.0.0.1") == -1){
		clientCleanup(&client);
		return -1;
	}

	if(clientSend(&client, "Hello from client") == -1){
		clientCleanup(&client);
		return -1;
	}

	printf("Hello message sent \n");

	if(clientReceive(&client, buffer, sizeof(buffer)) == -1){
		clientCleanup(&client);
		return -1;
	}

	printf("$s \n",buffer);

	clientCleanup(&client);

	return 0;
}