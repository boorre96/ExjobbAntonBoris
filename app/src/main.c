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

// #include <zephyr/logging/log.h>

// // LOG_MODULE_REGISTER(debug_log);
// LOG_MODULE_DECLARE(main_log);

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main_log, LOG_LEVEL_DBG);

#include "../includes/bmi_160/bmi_160.c"

Server server;

int main(void)
{

	LOG_INF("Hello from main.c");

	if(startWebsocket(&server)){
		// reg_read(&server, 0);
		reg_write(&server, 0, 2);
		

		/*Recieving a protobuf message from client*/

		size_t bytes = read(server.new_socket, server.buffer, sizeof(server.buffer));
		if(bytes == -1){
			printk("Error read function \n");
			LOG_ERR("Error : %d", bytes);
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
				// LOG_INF("pb_istream_t:	%s", &stream);
				// LOG_INF("SimpleMessage_fields:	%s", SimpleMessage_fields);
				// LOG_INF("fromClientMessage: 	%s", &fromClientMessage);
				LOG_INF("Decode return: 	%d", pb_decode(&stream, SimpleMessage_fields, &fromClientMessage));
				LOG_INF("Value : 	%d", fromClientMessage.val);
			
			}
			else{
				LOG_ERR("Decode failed");
			}

			// fromClientMessage.val = 26;
			// int data = fromClientMessage.val;

			// fromClientMessage.reg = 0x20;
			// int regn = fromClientMessage.reg;

			// LOG_INF("fromClientMessage.val:	%d", data);
			// LOG_INF("fromClientMessage.reg:	%d", regn);
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
		toClientMessage.val = 25;

		toClientMessage.val = 27;
		toClientMessage.reg = 0x02;
		int data = (int)toClientMessage.val;
		int regn = (int)toClientMessage.reg;

		// LOG_INF("toClientMessage.val:	%d", data);
		// LOG_INF("toClientMessage.reg:	%d", regn);
		
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
		
		/*#
		#
		#
		#	Go into bmi_160 and check the recived protobuf message
		#
		#*/
		if(!pb_encode(&stream, SimpleMessage_fields, &toClientMessage)){
			LOG_ERR("Error Encode: %d", !pb_encode(&stream, SimpleMessage_fields, &toClientMessage));
		}
		else{
			if(send(server.new_socket, server.buffer, stream.bytes_written, 0) == -1){
				LOG_ERR("Error sending protobuf");
			}
			else{
				LOG_INF("Protobuf reg %d sent.", regn);
				// reg_read(&server, regn);
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
	
	