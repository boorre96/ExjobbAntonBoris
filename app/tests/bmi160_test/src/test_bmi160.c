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
    Server test_server;

    // Test case 1: Writing to BMI160_REG_ACC_CONF
    int reg1 = BMI160_REG_ACC_CONF;
    int val1 = 0x1234;

    //SimpleMessage - check that these messages is equal to reg1 and val1
/* 
    reg_write(&test_server, , val1);
 */
   // zassert_equal(&test_server)

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

/* static bool log_contains(const char *str){
    const struct log_output *output = log_output_list_head_get();
    const struct log_output *output_end = log_output_list_tail_get();

    while(output != output_end){
        struct log_msg *msg;
        msg = log_msg_get(output, true);

        while(msg)
    }
} */