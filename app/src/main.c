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
#include "../includes/server.c"
#include <pb_encode.h>
#include <pb_decode.h>
#include "src/simple.pb.h"

Server server;
bool encode_message(uint8_t *buffer, size_t buffer_size, size_t *message_length)
{
	bool status;

	/* Allocate space on the stack to store the message data.
	 *
	 * Nanopb generates simple struct definitions for all the messages.
	 * - check out the contents of simple.pb.h!
	 * It is a good idea to always initialize your structures
	 * so that you do not have garbage data from RAM in there.
	 */
	SimpleMessage message = SimpleMessage_init_zero;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

	/* Fill in the lucky number */
	message.lucky_number = 13;

	/* Now we are ready to encode the message! */
	status = pb_encode(&stream, SimpleMessage_fields, &message);
	*message_length = stream.bytes_written;

	if (!status) {
		printk("Encoding failed: %s\n", PB_GET_ERROR(&stream));
	}

	return status;
}

bool decode_message(uint8_t *buffer, size_t message_length)
{
	bool status;

	/* Allocate space for the decoded message. */
	SimpleMessage message = SimpleMessage_init_zero;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, SimpleMessage_fields, &message);

	/* Check for errors... */
	if (status) {
		/* Print the data contained in the message. */
		printk("Your lucky number was %d!\n", (int)message.lucky_number);
	} else {
		printk("Decoding failed: %s\n", PB_GET_ERROR(&stream));
	}

	return status;
}


int main(void)
{
	
	/* This is the buffer where we will store our message. */
	uint8_t buffer[SimpleMessage_size];
	size_t message_length;

	/* Encode our message */
	if (!encode_message(buffer, sizeof(buffer), &message_length)) {
		return;
	}

	/* Now we could transmit the message over network, store it in a file or
	 * wrap it to a pigeon's leg.
	 */

	/* But because we are lazy, we will just decode it immediately. */
	decode_message(buffer, message_length);
	
	// printk("test \n");
	// //fflush(stdout);
	
	
	// if(createSocket(&server)){
	// 	printf("Creating server.... \n");
	// 	//fflush(stdout);

	// 	initiateSocket(&server);

	// 	if(bindSocket(&server)){
	// 		printk("Binding socket... \n");
	// 		startListening(&server);
	// 		acceptConnection(&server);
	// 		printk("After acceptConnection \n");
	// 	}
	// 	else{
	// 		printk("couldent bind socket.... \n");
	// 		//fflush(stdout);
	// 	}
		
		
	// 	handleMessages(&server);
	// }
	// else{
	// 	printk("didn't work");
	// 	fflush(stdout);
	// }
	return 0;
}
	
	