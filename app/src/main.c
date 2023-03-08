/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#include "app_version.h"

#include <zephyr/logging/log.h>


#include <stdio.h>
#include "../includes/client.c"
/* #include "../includes/client.h" */
int main(void)
{
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
	
	