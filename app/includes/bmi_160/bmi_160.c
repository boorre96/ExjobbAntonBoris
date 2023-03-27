#include "bmi_160.h"
#include "register.h"
#include <zephyr/sys/printk.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "src/simple.pb.h"


#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bmi160_log);

int encode(SimpleMessage *message, Server *server){

	/*
	pb_ostream_t creates a object which is a structure that representa a nonopb output stream from a
	given memory buffer. The output stream is used to store the encoded protocol buffer.

	server.buffer is where the encoded protocol buffer will be stored.
	*/

	pb_ostream_t stream = pb_ostream_from_buffer(server->buffer, 1024);

	/*
		pb_encode encodes the protobuf message into a binary format that can be sent over a network or
		stored in a file.
		three arguments:
		&stream - a pointer to a pb_ostream_t object which will represent the output stream where the 
				  encoded message will be stored.
		SimpleMessageFields - -||-
		&toClientMessage - A pointer to the message that you want to encode. This object should be of
						   the same type as the one described by SimpleMessage_fields (SimpleMessage). 
		*/

	if(!pb_encode(&stream, SimpleMessage_fields, message)){
		printk("failed to encode... \n");
		return -1;
	}
	else{
		printk("Encoding worked.. \n");
		return stream.bytes_written;;
	}


}
int decode(SimpleMessage *message, Server *server, int bytesFromClient){

	/*
	Pb_istream_t creates a object which is a structure that represents a nanopb input stream.
	It initializes the input stream to read data from the server.buffer and bytes tells the stream
	how many bytes it can read from the given buffer.  
	*/

	pb_istream_t stream = pb_istream_from_buffer(server->buffer, bytesFromClient);

	/*
	pb_decode decodes the protobuf message from a serialized binary format.
	Three arguments:
	&stream - A pointer to a pb_istream_f structure which represent the input stream that
				contains the serialized binary data.
	SimpleMessage_fields - An array of file descriptors for the protocolbuffer message structure
							you wnat to decode. It refers to your .proto file.
	&fromClientMessage - A pointer to the target message structure where the decoded data should
							be stored.  
	*/

	if(pb_decode(&stream, SimpleMessage_fields, message)){
		printk("Decoding worked... \n");
		return 1;
	}
	else{
		printk("Failed to decode the message... \n");
		return 0;
	}

}
static void reg_write(Server *server, int reg, int val){
	printk("REG_WRITE \n");

	SimpleMessage message = {0};
	message.val = val;
	message.regNum = reg;
	message.read = 1;

	memset(server->buffer, 0, 1024);

	if((bytesToSend = encode(&message, server)) == -1){
		printk("Error in encode function... \n");
	}
	else{
		if(send(server->new_socket, server->buffer, bytesToSend, 0) == -1){
			printk("Send to client failed... \n");
		}
		else{
			printk("Protobuf sent to client! \n");
		}
	}
		
    printk("write %x = %x \n", reg, val);

    switch(reg){
        case BMI160_REG_ACC_CONF:
            LOG_INF("   * acc conf");
            break;
        case BMI160_REG_ACC_RANGE:
            LOG_INF("   * acc range");
            break;
        case BMI160_REG_GYR_CONF:
            LOG_INF("   * gyr conf");
            break;
        case BMI160_REG_GYR_RANGE:
            LOG_INF("   * gyr range");
            break;
        case BMI160_REG_CMD:
            switch(val){
            case BMI160_CMD_SOFT_RESET:
                LOG_INF("   * soft reset");
                break;
            default:
                if((val & BMI160_CMD_PMU_BIT) == BMI160_CMD_PMU_BIT){
                    int which = (val & BMI160_CMD_PMU_MASK) >> BMI160_CMD_PMU_SHIFT;
                    int shift;
                    int pmu_val = val & BMI160_CMD_PMU_VAL_MASK;

                    switch(which){
                        case 0:
                            shift = BMI160_PMU_STATUS_ACC_POS;
                            break;
                        case 1:
                            shift = BMI160_PMU_STATUS_GYR_POS;
                            break;
                        case 2:
                        default:
                            shift = BMI160_PMU_STATUS_MAG_POS;
                            break;
                        }
                        /*
                        *write over
                        */
                    }
            }
    }
}

// Register read
static int reg_read(Server *server, int reg){
	
	//
	SimpleMessage message = {0};
	message.regNum = reg;
	message.read = 2;

	SimpleMessage messageFromClient = {0};
	
	if((bytesToSend = encode(&message, server)) == -1){
		printk("Error in encode function... \n");
	}
	else{
		if(send(server->new_socket, server->buffer, bytesToSend, 0) == -1){
			printk("Send to client failed... \n");
		}
		else{
			printk("Protobuf sent to client! \n");
		}
	}
	
    size_t bytes = read(server->new_socket, server->buffer, sizeof(server->buffer));
		if(bytes == -1){
			printk("Error read function \n");
		}
		else{
			printk("Message from client read successfully... \n");
			
			

			if(!decode(&messageFromClient, server, bytes)){
				printk("Error in decode function... \n");
			}
			else{
				printk("Value is: %d!", messageFromClient.val);
			}
		}
	
	printk("Read %x = \n", reg);
    int val = messageFromClient.val;
    switch(reg){
        case BMI160_REG_CHIPID:
            LOG_INF("   * get chipid");
            break;
        case BMI160_REG_PMU_STATUS:
            LOG_INF("   * get pmu");
            break;
        case BMI160_REG_STATUS:
            LOG_INF("   * status");
            break;
        case BMI160_REG_ACC_CONF:
            LOG_INF("   * acc conf");
            break;
        case BMI160_REG_GYR_CONF:
            LOG_INF("   * gyr conf");
            break;
        case BMI160_SPI_START:
            LOG_INF("   * Bus start");
            break;
        case BMI160_REG_ACC_RANGE:
            LOG_INF("   * acc range");
            break;
        case BMI160_REG_GYR_RANGE:
            LOG_INF("   * gyr range");
            break;
        default:
            LOG_INF("Unknown read %x", reg);
    }
    LOG_INF("       = %x", val);

    return val;
}
