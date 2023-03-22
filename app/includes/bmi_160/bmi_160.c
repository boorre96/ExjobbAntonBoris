#include "bmi_160.h"
#include "register.h"
#include <zephyr/sys/printk.h>
#include "../server.c"
#include <pb_encode.h>
#include <pb_decode.h>
#include "src/simple.pb.h"


#define I2C bosch_bmi160
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(bosch_bmi160);

// Register write
static void reg_write(int reg, int val){
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
static int reg_read(int reg){
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