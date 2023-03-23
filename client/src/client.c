// Client side C/C++ program to demonstrate Socket
// programming
#include "client.h"

#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

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

int clientSend(Client* client, const int number){
    /*Sending a protobuf to server*/
    printf("clientSend function \n");

    SimpleMessage message = SimpleMessage_init_zero;
    uint8_t buffer[1024];

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    message.val = number;

    bool status = pb_encode(&stream, SimpleMessage_fields, &message);

    if(!status){
        printf("The encoding didn't work! \n");
        return 0;
    }
    if(send(client->clientFd, buffer, stream.bytes_written, 0) == -1){
        printf("Send failed \n");
        return -1;
    }

    printf("Protobuf message sent \n");

    return 1;
}

// Registret som det vill läsa ifrån här
// Returnera data-värde på det register

int clientReceive(Client* client, char* buffer, int size){
    
    /*Recieving a protobuf from server*/
    int bytesReceived = 0;

    if((bytesReceived = read(client->clientFd, buffer, size)) == -1){
        printf("Receive failed \n");
    }
    else{
        printf("Recieved protobuf %d bytes.\n", bytesReceived);
        /*Decode the protobuf*/
        SimpleMessage fromServerMessage = SimpleMessage_init_zero;
		pb_istream_t stream = pb_istream_from_buffer(buffer, bytesReceived);
        printf("Register to read from: %d \n", fromServerMessage.reg);
        printf("Value from server: %d \n", fromServerMessage.val);
        if(pb_decode(&stream, SimpleMessage_fields, &fromServerMessage)){
                printf(".......Accepted........\n");
				printf("Register to read from: %d \n", fromServerMessage.reg);
                printf("Value from server: %d \n", fromServerMessage.val);
		}
		else{
				printf("Failed to decode the message... \n");
		}
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

	if(clientSend(&client, 2) == -1){
		clientCleanup(&client);
		return -1;
	}


	if(clientReceive(&client, buffer, sizeof(buffer)) == -1){
		clientCleanup(&client);
		return -1;
	}

	printf("%s \n",buffer);

	clientCleanup(&client);

	return 0;
}