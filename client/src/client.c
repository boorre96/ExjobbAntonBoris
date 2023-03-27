// Client side C/C++ program to demonstrate Socket
// programming
#include "client.h"

#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"
#include "../includes/bmi_160/register.h"

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

int clientSend(Client* client, const int value){
    /*Sending a protobuf to server*/
    SimpleMessage message = SimpleMessage_init_zero;
    uint8_t buffer[1024];

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    message.val = value;

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
        printf("Recieved protobuf from server! \n");
        
        /*Decode the protobuf*/

        SimpleMessage fromServerMessage = {0};
		pb_istream_t stream = pb_istream_from_buffer(buffer, bytesReceived);
        printf("Register to read from: %d \n", fromServerMessage.regNum);
        printf("Value from server: %d \n", fromServerMessage.val);
        if(pb_decode(&stream, SimpleMessage_fields, &fromServerMessage)){

			printf("Decoding worked! \n");
            printf("Your value is: %d, the registernumber is %d, the read value is %d \n", fromServerMessage.val, fromServerMessage.regNum, fromServerMessage.read);
            if (fromServerMessage.val == 100)
            {
                return -1;
            }
            
            else if(fromServerMessage.read == 1){
                printf("FROM REG_READ \n");
                printf("Sending value from register: %d back to server... \n", fromServerMessage.regNum);
                printf("Test: %d\n", BMI160_REG_ERR);
                clientSend(client, 10);
            }
            else if(fromServerMessage.read == 0){
                printf("FROM REG_WRITE \n");
                printf("Writing the value: %d into the register number: %d \n", fromServerMessage.val, fromServerMessage.regNum);
            }
            else{
                printf("Wrong value in fromServerMessage... \n");
            }
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

    while(true){

        if(clientReceive(&client, buffer, sizeof(buffer)) == -1){
		    clientCleanup(&client);
		    return false;
	    }
    }


	clientCleanup(&client);

	return 0;
}