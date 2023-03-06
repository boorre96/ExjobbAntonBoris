/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#include "app_version.h"

#include <zephyr/logging/log.h>


void main(void)
{
	printk("Zephyr Example Application %s\n", APP_VERSION_STR);
}

