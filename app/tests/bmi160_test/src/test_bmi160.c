#include <zephyr/ztest.h>
#include <zephyr/sys/printk.h>
/* #include <zephyr/logging/log.h>
#include "../../../includes/server/server.c" */


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
    zassert_true(r, "Failed to read register 0x00. ");
}

static void test_reg_read_write_consistency(void){
    uint8_t write_val = 10;
    uint8_t read_val;

    zassert_true(reg_write(&server, BMI160_REG_ACC_CONF, write_val), "Failed to wrtie to BMI160_REG_ACC_CONF");
    read_val = reg_read(&server, BMI160_REG_ACC_CONF);
    zassert_equal(write_val, read_val, "Register read-write consistency error");
}

ztest_test_suite(bmi160_simple_tests, 
                ztest_unit_test(websocket_test),
                ztest_unit_test(test_reg_write),
                ztest_unit_test(test_reg_read),
                ztest_unit_test(test_reg_read_write_consistency));

void test_main(void){
    ztest_run_test_suite(bmi160_simple_tests);
}