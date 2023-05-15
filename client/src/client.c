// Client side C/C++ program to demonstrate Socket
// programming
#include "client.h"

#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"
#include "../includes/bmi_160/register.h"


#define NUMBEROFREGISTERS 82


struct BMIRegister {
    int registerNumber;
    char registerName[50];
    int registerValue;
};


struct BMIRegister bmiRegisters[NUMBEROFREGISTERS] = {
    {0x00, "BMI160_REG_CHIPID",0},
    {0x02, "BMI160_REG_ERR",2},
    {0x03, "BMI160_REG_PMU_STATUS",0},
    {0x04, "BMI160_REG_DATA_MAG_X",0},
    {0x06, "BMI160_REG_DATA_MAG_Y",0},
    {0x08, "BMI160_REG_DATA_MAG_Z",0},
    {0x0A, "BMI160_REG_DATA_RHALL",0},
    {0x0C, "BMI160_REG_DATA_GYR_X",0},
    {0x0E, "BMI160_REG_DATA_GYR_Y",0},
    {0x10, "BMI160_REG_DATA_GYR_Z",0},
    {0x12, "BMI160_REG_DATA_ACC_X",0},
    {0x14, "BMI160_REG_DATA_ACC_Y",0},
    {0x16, "BMI160_REG_DATA_ACC_Z",0},
    {0x18, "BMI160_REG_SENSORTIME0",0},
    {0x19, "BMI160_REG_SENSORTIME1",0},
    {0x1A, "BMI160_REG_SENSORTIME2",0},
    {0x1B, "BMI160_REG_STATUS",0},
    {0x1C, "BMI160_REG_INT_STATUS0",0},
    {0x1D, "BMI160_REG_INT_STATUS1",0},
    {0x1E, "BMI160_REG_INT_STATUS2",0},
    {0x1F, "BMI160_REG_INT_STATUS3",0},
    {0x20, "BMI160_REG_TEMPERATURE0",0},
    {0x21, "BMI160_REG_TEMPERATURE1",0},
    {0x22, "BMI160_REG_FIFO_LENGTH0",0},
    {0x23, "BMI160_REG_FIFO_LENGTH1",0},
    {0x24, "BMI160_REG_FIFO_DATA",0},
    {0x40, "BMI160_REG_ACC_CONF",0},
    {0x41, "BMI160_REG_ACC_RANGE",0},
    {0x42, "BMI160_REG_GYR_CONF",0},
    {0x43, "BMI160_REG_GYR_RANGE",0},
    {0x44, "BMI160_REG_MAG_CONF",0},
    {0x45, "BMI160_REG_FIFO_DOWNS",0},
    {0x46, "BMI160_REG_FIFO_CONFIG0",0},
    {0x47, "BMI160_REG_FIFO_CONFIG1",0},
    {0x4B, "BMI160_REG_MAG_IF0",0},
    {0x4C, "BMI160_REG_MAG_IF1",0},
    {0x4D, "BMI160_REG_MAG_IF2",0},
    {0x4E, "BMI160_REG_MAG_IF3",0},
    {0x4F, "BMI160_REG_MAG_IF4",0},
    {0x50, "BMI160_REG_INT_EN0",0},
    {0x51, "BMI160_REG_INT_EN1",0},
    {0x52, "BMI160_REG_INT_EN2",0},
    {0x53, "BMI160_REG_INT_OUT_CTRL",0},
    {0x54, "BMI160_REG_INT_LATCH",0},
    {0x55, "BMI160_REG_INT_MAP0",0},
    {0x56, "BMI160_REG_INT_MAP1",0},
    {0x57, "BMI160_REG_INT_MAP2",0},
    {0x58, "BMI160_REG_INT_DATA0",0},
    {0x59, "BMI160_REG_INT_DATA1", 0},
    {0x5A, "BMI160_REG_INT_LOWHIGH0",0},
    {0x5B, "BMI160_REG_INT_LOWHIGH1",0},
    {0x5C, "BMI160_REG_INT_LOWHIGH2",0},
    {0x5D, "BMI160_REG_INT_LOWHIGH3",0},
    {0x5E, "BMI160_REG_INT_LOWHIGH4",0},
    {0x5F, "BMI160_REG_INT_MOTION0",0},
    {0x60, "BMI160_REG_INT_MOTION1",0},
    {0x61, "BMI160_REG_INT_MOTION2",0},
    {0x62, "BMI160_REG_INT_MOTION3",0},
    {0x63, "BMI160_REG_INT_TAP0",0},
    {0x64, "BMI160_REG_INT_TAP1",0},
    {0x65, "BMI160_REG_INT_ORIENT0",0},
    {0x66, "BMI160_REG_INT_ORIENT1",0},
    {0x67, "BMI160_REG_INT_FLAT0",0},
    {0x68, "BMI160_REG_INT_FLAT1",0},
    {0x69, "BMI160_REG_FOC_CONF",0},
    {0x6A, "BMI160_REG_CONF",0},
    {0x6B, "BMI160_REG_IF_CONF",0},
    {0x6C, "BMI160_REG_PMU_TRIGGER",0},
    {0x6D, "BMI160_REG_SELF_TEST",0},
    {0x70, "BMI160_REG_NV_CONF",0},
    {0x71, "BMI160_REG_OFFSET_ACC_X",0},
    {0x72, "BMI160_REG_OFFSET_ACC_Y",0},
    {0x73, "BMI160_REG_OFFSET_ACC_Z",0},
    {0x74, "BMI160_REG_OFFSET_GYR_X",0},
    {0x75, "BMI160_REG_OFFSET_GYR_Y",0},
    {0x76, "BMI160_REG_OFFSET_GYR_Z",0},
    {0x77, "BMI160_REG_OFFSET_EN",0},
    {0x78, "BMI160_REG_STEP_CNT0",0},
    {0x79, "BMI160_REG_STEP_CNT1",0},
    {0x7A, "BMI160_REG_STEP_CONF0",0},
    {0x7B, "BMI160_REG_STEP_CONF1",0},
    {0x7E, "BMI160_REG_CMD",0}
    };

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

/*Sending a protobuf to server*/
int clientSend(Client* client, int value){

    if (value == 0){
        value = 99999999;
    }        

    /* Instantiates an empty protobuf and insert "value" into the protobuf */
    SimpleMessage message = {0};
    message.val = value;
    
    /* Create a buffer which will store the encoded message */
    uint8_t buffer[1024];

    /* Creates a Protocol Buffers output stream object, named 'stream', by initializing it with a given buffer and its corresponding size */
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    if(!pb_encode(&stream, SimpleMessage_fields, &message)){
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


int clientReceive(Client* client, char* buffer, int size){
    
    /*Recieving a protobuf from server*/
    int bytesReceived = 0;

    if((bytesReceived = read(client->clientFd, buffer, size)) == -1){
        printf("Receive failed \n");
    }
    else{
        printf("Recieved protobuf from server! \n");
        
        /*Decode the protobuf*/

        /* Instantiates an empty protobuf */
        SimpleMessage fromServerMessage = {0};

		pb_istream_t stream = pb_istream_from_buffer(buffer, bytesReceived);
        
        if(pb_decode(&stream, SimpleMessage_fields, &fromServerMessage)){
            if(fromServerMessage.val == 99999999){
                fromServerMessage.val = 0;
            }

			printf("Decoding worked! \n");
            
            if(fromServerMessage.read == 2){
                printf("FROM REG_READ \n");
                for(int i=0; i<NUMBEROFREGISTERS; i++){
                    if(bmiRegisters[i].registerNumber == fromServerMessage.regNum){
                        printf("bmiRegisters[%d].registerNumber: %d fromServerMessage.regNum: %d \n", i ,bmiRegisters[i].registerNumber, fromServerMessage.regNum);
                        printf("Sending value from register: %d back to server... \n", fromServerMessage.regNum);
                        clientSend(client, bmiRegisters[i].registerValue);
                        break;
                    }
                }
                // printf("Sending value from register: %d back to server... \n", fromServerMessage.regNum);
                // clientSend(client, 10);
            }
            else if(fromServerMessage.read == 1){
                printf("FROM REG_WRITE \n");
                for(int i=0; i<NUMBEROFREGISTERS; i++){
                    if(bmiRegisters[i].registerNumber == fromServerMessage.regNum){
                        printf("bmiRegisters[%d].registerNumber: fromServerMessage.regNum: %d \n", bmiRegisters[i].registerNumber, fromServerMessage.regNum);
                        printf("Writing the value: %d into the register number: %d \n", fromServerMessage.val, fromServerMessage.regNum);
                        bmiRegisters[i].registerValue = fromServerMessage.val;
                        break;
                    }
                }
                // printf("Writing the value: %d into the register number: %d \n", fromServerMessage.val, fromServerMessage.regNum);
            }
            else{
                printf("Wrong value in fromServerMessage... \n");
                return -1;
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