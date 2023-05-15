#include <zephyr/ztest.h>
#include <zephyr/sys/printk.h>
#include <zephyr/zephyr.h>
/* #include <zephyr/logging/log.h>
#include "../../../includes/server/server.c" */

#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(test_log, LOG_LEVEL_DBG);

//#include "../../../includes/server/server.c"

#include "../../../includes/bmi_160/bmi_160.c"

Server server;


void main(void);

static int setup_websocket_server(Server *server){

    if(!startWebsocket(server))
        return 0;
    
    return 1;
}

static void websocket_test(void){

   // Initiate websocket server
   int ws = setup_websocket_server(&server);
   zassert_true(ws, "Failed to Initiate WebSocket.");

}

static void test_reg_write(void){    

    // Test case 1 - BMI160_REG_ACC_CONF
    zassert(reg_write(&server, BMI160_REG_ACC_CONF, 10), "Test case 1 - Failed to write to BMI160_REG_ACC_CONF");

    // Test case 2 - BMI160_REG_ACC_RANGE  
    zassert(reg_write(&server, BMI160_REG_ACC_RANGE, 10), "Test case 2 - Failed to write to BMI160_REG_ACC_RANGE"); 

    // Test case 3 - BMI160_REG_GYR_CONF
    zassert(reg_write(&server, BMI160_REG_GYR_CONF, 10), "Test case 3 - Failed to write to BMI160_REG_GYR_CONF");

    // Test case 4 - BMI160_REG_GYR_RANGE
    zassert(reg_write(&server, BMI160_REG_GYR_RANGE, 10), "Test case 4 - Failed to write to BMI160_REG_GYR_RANGE");

    // Test case 5 - BMI160_REG_CMD
    zassert(reg_write(&server, BMI160_REG_CMD, 10), "Test case 5 - Failed to write to BMI160_REG_CMD");


}

static void test_reg_read(void){

    uint8_t r = reg_read(&server, 0);
    zassert_true(r>=0, "Failed to read register 0x00. ");

}

static void test_reg_read_write_consistency(void){
    uint8_t write_val;
    uint8_t read_val;

      write_val = 78;
    zassert_true(reg_write(&server, BMI160_REG_CHIPID, write_val), "Failed to write to BMI160_REG_CHIPID");
    read_val = reg_read(&server, BMI160_REG_CHIPID);
    zassert_equal(write_val, read_val, "Test case 1 - Register read-write consistency error for BMI160_REG_CHIPID");

    // Test case 2 - BMI160_REG_PMU_STATUS
    write_val = 90;
    zassert_true(reg_write(&server, BMI160_REG_PMU_STATUS, write_val), "Failed to write to BMI160_REG_PMU_STATUS");
    read_val = reg_read(&server, BMI160_REG_PMU_STATUS);
    zassert_equal(write_val, read_val, "Test case 2 - Register read-write consistency error for BMI160_REG_PMU_STATUS");

    // Test case 3 - BMI160_REG_STATUS
    write_val = 55;
    zassert_true(reg_write(&server, BMI160_REG_STATUS, write_val), "Failed to write to BMI160_REG_STATUS");
    read_val = reg_read(&server, BMI160_REG_STATUS);
    zassert_equal(write_val, read_val, "Test case 3 - Register read-write consistency error for BMI160_REG_STATUS");

    // Test case 4 - BMI160_REG_ACC_CONF
    write_val = 120;
    zassert_true(reg_write(&server, BMI160_REG_ACC_CONF, write_val), "Failed to write to BMI160_REG_ACC_CONF");
    read_val = reg_read(&server, BMI160_REG_ACC_CONF);
    zassert_equal(write_val, read_val, "Test case 4 - Register read-write consistency error for BMI160_REG_ACC_CONF");

    // Test case 5 - BMI160_REG_GYR_CONF
    write_val = 45;
    zassert_true(reg_write(&server, BMI160_REG_GYR_CONF, write_val), "Failed to write to BMI160_REG_GYR_CONF");
    read_val = reg_read(&server, BMI160_REG_GYR_CONF);
    zassert_equal(write_val, read_val, "Test case 5 - Register read-write consistency error for BMI160_REG_GYR_CONF");


    // Test case 6 - BMI160_REG_ACC_RANGE
    write_val = 88;
    zassert_true(reg_write(&server, BMI160_REG_ACC_RANGE, write_val), "Failed to write to BMI160_REG_ACC_RANGE");
    read_val = reg_read(&server, BMI160_REG_ACC_RANGE);
    zassert_equal(write_val, read_val, "Test case 7 - Register read-write consistency error for BMI160_REG_ACC_RANGE");

    // Test case 7 - BMI160_REG_GYR_RANGE
    write_val = 66;
    zassert_true(reg_write(&server, BMI160_REG_GYR_RANGE, write_val), "Failed to write to BMI160_REG_GYR_RANGE");
    read_val = reg_read(&server, BMI160_REG_GYR_RANGE);
    zassert_equal(write_val, read_val, "Test case 8 - Register read-write consistency error for BMI160_REG_ACC_RANGE");
}

ztest_test_suite(bmi160_simple_tests, 
                ztest_unit_test(websocket_test),
                ztest_unit_test(test_reg_write),
                ztest_unit_test(test_reg_read),
                ztest_unit_test(test_reg_read_write_consistency));

void test_main(void){    
    ztest_run_test_suite(bmi160_simple_tests);
}