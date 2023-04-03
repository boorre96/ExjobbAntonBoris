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
   zassert_true(ws, "Could not start socket.");

}

static void test_reg_write(void){
    // Test case 1 - BMI160_REG_ACC_CONF
    zassert(reg_write(&server, BMI160_REG_ACC_CONF, 10), "Test case 1");

    // Test case 2 - BMI160_REG_ACC_RANGE  
    zassert(reg_write(&server, BMI160_REG_ACC_RANGE, 10), "Test case 2"); 

    // Test case 3 - BMI160_REG_GYR_CONF
    zassert(reg_write(&server, BMI160_REG_GYR_CONF, 10), "Test case 3");

    // Test case 4 - BMI160_REG_GYR_RANGE
    zassert(reg_write(&server, BMI160_REG_GYR_RANGE, 10), "Test case 4");

    // Test case 5 - BMI160_REG_CMD
    zassert(reg_write(&server, BMI160_REG_CMD, 10), "Test case 5");


}

static void test_reg_read(void){
    uint8_t r = reg_read(&server, 0);
    zassert_true(r, "Register write error. ");
}

ztest_test_suite(bmi160_simple_tests, 
                ztest_unit_test(websocket_test),
                ztest_unit_test(test_reg_write),
                ztest_unit_test(test_reg_read));

void test_main(void){
    ztest_run_test_suite(bmi160_simple_tests);
}