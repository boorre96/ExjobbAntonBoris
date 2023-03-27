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
	
	if(startWebsocket(&server)){
		printk("Press 'y' when wanting to start websocket... \n");
		char s;
		while (true) 
		{
			scanf(" %c", &s);
			if(s == 'w'){
				reg_write(&server, 5, 6);
			}
			else if(s == 'r'){
				reg_read(&server, 0);
			}
			else{
				reg_write(&server, 5, 100);
				printk("Ending socket... \n");
				break;
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
	
	