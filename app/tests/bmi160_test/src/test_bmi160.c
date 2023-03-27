#include <zephyr/ztest.h>
#include <zephyr/sys/printk.h>

static void test_print_message(void){
    printk("This is a simple test message. \n");
}

ztest_test_suite(bmi160_simple_tests, 
                ztest_unit_test(test_print_message));

void test_main(void){
    ztest_run_test_suite(bmi160_simple_tests);
}