/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include "app_version.h"

#include <zephyr/toolchain.h>
#include <stddef.h>
#include <stdarg.h>
#include <inttypes.h>
 
#include <stdio.h>
#include "../includes/bmi_160/bmi_160.c"

Server server;

int main(void)
{

	reg_read(0);

	int num;
	reg_write(1 ,3);

	scanf("%d", num);

	if(startWebsocket(&server)){

		/*Recieving a protobuf message from client*/

		size_t bytes = read(server.new_socket, server.buffer, sizeof(server.buffer));
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

		/*Sending a protobuf message to client*/

		memset(server.buffer, 0, bytes);
		SimpleMessage toClientMessage = {0};

		/*
		pb_ostream_t creates a object which is a structure that representa a nonopb output stream from a
		given memory buffer. The output stream is used to store the encoded protocol buffer.

		server.buffer is where the encoded protocol buffer will be stored.
		*/
		pb_ostream_t stream = pb_ostream_from_buffer(server.buffer, 1024);
		toClientMessage.lucky_number = 25;
		
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
		bool status = pb_encode(&stream, SimpleMessage_fields, &toClientMessage);

		if(!status){
			printk("failed to encode... \n");
		}
		else{
			if(send(server.new_socket, server.buffer, stream.bytes_written, 0) == -1){
				printk("Failed to send to client! \n");
			}
			else{
				printk("Protobuf sent to client! \n");
			}
		}

		close(server.new_socket);
		shutdown(server.server_fd, SHUT_RDWR);
	}
	else{
		printk("Socket didn't start... \n");
		close(server.new_socket);
		shutdown(server.server_fd, SHUT_RDWR);
	}
	
	return 0;
}
	
	