#ifndef BMI_160_H_
#define BMI_160_H_

#include "../server/server.c"


static void reg_write(Server *server, int reg, int val);
static int reg_read(Server *server, int reg);

#endif /*BMI_160_H_*/