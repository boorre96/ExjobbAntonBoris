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

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main_log, LOG_LEVEL_DBG);

#include "../includes/bmi_160/bmi_160.c"

Server server;
int main(void)
{
	
	if(startWebsocket(&server)){
		LOG_WRN("Press 'y to start websocket ");
		char s;
		while (true) 
		{
			scanf(" %c", &s);
			if(s == 'w'){
				reg_write(&server, 4, 6);
			}
			else if(s == 'r'){
				reg_read(&server, 2);
			}
			else{
				reg_write(&server, 5, 100);
				LOG_ERR("Socket closing");
				break;
			}
			
		}
		close(server.new_socket);
		shutdown(server.server_fd, SHUT_RDWR);
	}
	else{
		LOG_ERR("Could not start socket." );
		close(server.new_socket);
		shutdown(server.server_fd, SHUT_RDWR);
	}
	
	return 0;
}
	
	