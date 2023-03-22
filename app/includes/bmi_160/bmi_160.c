#include "bmi_160.h"
#include "register.h"
#include <zephyr/sys/printk.h>
#include "../server.c"
#include <pb_encode.h>
#include <pb_decode.h>
#include "src/simple.pb.h"


#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bmi160_log);


// Register write
static void reg_write(int reg, int val){


    switch(reg){
        case BMI160_REG_ACC_CONF:
            LOG_INF("   * acc conf");
            break;
        case BMI160_REG_ACC_RANGE:
            LOG_INF("   * acc range");
            break;
        case BMI160_REG_GYR_CONF:
            LOG_INF("   * gyr conf");
            break;
        case BMI160_REG_GYR_RANGE:
            LOG_INF("   * gyr range");
            break;
        case BMI160_REG_CMD:
            switch(val){
            case BMI160_CMD_SOFT_RESET:
                LOG_INF("   * soft reset");
                break;
            default:
                if((val & BMI160_CMD_PMU_BIT) == BMI160_CMD_PMU_BIT){
                    int which = (val & BMI160_CMD_PMU_MASK) >> BMI160_CMD_PMU_SHIFT;
                    int shift;
                    int pmu_val = val & BMI160_CMD_PMU_VAL_MASK;

                    switch(which){
                        case 0:
                            shift = BMI160_PMU_STATUS_ACC_POS;
                            break;
                        case 1:
                            shift = BMI160_PMU_STATUS_GYR_POS;
                            break;
                        case 2:
                        default:
                            shift = BMI160_PMU_STATUS_MAG_POS;
                            break;
                        }
                        /*
                        *write over
                        */
                    }
            }
    }
}

// Register read
static int reg_read(int reg){
    int val = 1337;
    printk("Read: %x && Value: %x \n",reg, val);

    LOG_INF("read %x=",reg);
    switch(reg){
        case BMI160_REG_CHIPID:
            LOG_INF("   * get chipid");
            break;
        case BMI160_REG_PMU_STATUS:
            LOG_INF("   * get pmu");
            break;
        case BMI160_REG_STATUS:
            LOG_INF("   * status");
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
            LOG_INF("Unknown read %x", reg);
    }
    LOG_INF("       = %x", val);

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