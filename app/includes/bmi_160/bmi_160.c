#include "bmi_160.h"
#include "register.h"
#include <zephyr/sys/printk.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "src/simple.pb.h"


#define I2C bosch_bmi160
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(bosch_bmi160);

// Register write
static void reg_write(Server *server, int reg, int val){
	printk("REG_WRITE \n");

	/* 
	1. Enter the values into the protobuf
	2. Encode the protobuf into the server buffer
	3. Send the encoded protobuf through websocket
	*/
	SimpleMessage message = {0};
	message.lucky_number = val;

	memset(server->buffer, 0, 1024);
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
	bool status = pb_encode(&stream, SimpleMessage_fields, &message);

	if(!status){
			printk("failed to encode... \n");
	}
	else{
		if(send(server->new_socket, server->buffer, stream.bytes_written, 0) == -1){
				printk("Failed to send to client! \n");
		}
		else{
				printk("Protobuf sent to client! \n");
		}
	}
		
    printk("write %x = %x", reg, val);

    switch(reg){
        case BMI160_REG_ACC_CONF:
            printk("Register number %d: ",reg);
            break;
        case BMI160_REG_ACC_RANGE:
            printk("Register number %d: ", reg);
            break;
    }
}

// Register read
static int reg_read(Server *server, int reg){
	
	/*
	1. Enter the register number into protobuf
	2. Encode the data
	3. Send a protobuf through websocket
	4. Wait until you have got something
	5. Print what you got
	*/
	SimpleMessage message = {0};
	message.lucky_number = reg;
	
	reg_write(server, )
    size_t bytes = read(server->new_socket, server->buffer, sizeof(server.buffer));
		if(bytes == -1){
			printk("Error read function \n");
		}
		else{
			
			SimpleMessage fromClientMessage = SimpleMessage_init_zero;
			/*
			Pb_istream_t creates a object which is a structure that represents a nanopb input stream.
			It initializes the input stream to read data from the server.buffer and bytes tells the stream
			how many bytes it can read from the given buffer.  
			*/
			pb_istream_t stream = pb_istream_from_buffer(server.buffer, bytes);

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
			if(pb_decode(&stream, SimpleMessage_fields, &fromClientMessage)){
				printk("Recieved protobuf from client and the decoding worked \n");
				printk("Your lucky number is: %d! \n", (int)fromClientMessage.lucky_number);
			}
			else{
				printk("Failed to decode the message... \n");
			}
		}
	
	printk("Read %x = \n", reg);
    int val;
    switch(reg){
        case BMI160_REG_CHIPID:
            /* printk("Register number %x: , Value: %d \n", reg); */
            LOG_INF("   * get chipid");
            break;
        case BMI160_REG_PMU_STATUS:
            printk(" * get pmu \n");
            LOG_INF("   * get pmu");
            break;
        case BMI160_REG_STATUS:
            printk(" * status \n");
            LOG_INF("   * status");
            break;
    }
    return val;
}

/* 	switch (regn) {
	case BMI160_REG_CHIPID:
		LOG_INF("   * get chipid");
		break;
	case BMI160_REG_PMU_STATUS:
		LOG_INF("   * get pmu");
		val = data->pmu_status;
		break;
	case BMI160_REG_STATUS:
		LOG_INF("   * status");
		val |= BMI160_DATA_READY_BIT_MASK;
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
		LOG_INF("Unknown read %x", regn);
	}
	LOG_INF("       = %x", val); */