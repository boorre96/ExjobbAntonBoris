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
#include "../includes/client.c"


Server server;

int main(void)
{
	
	
	printk("test \n");
	//fflush(stdout);
	
	
	if(createSocket(&server)){
		printf("Creating server.... \n");
		//fflush(stdout);

		if(bindSocket(&server)){
			printk("Binding socket... \n");
			//fflush(stdout);
		}
		else{
			printk("couldent bind socket.... \n");
			//fflush(stdout);
		}
		startListening(&server);
		acceptConnection(&server);
		handleMessages(&server);
	}
	else{
		printk("didn't work");
		fflush(stdout);
	}
	return 0;
}
	
	