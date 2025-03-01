#ifndef I2C_H
#define I2C_H
#define I2C_PORT I2C_NUM_0
#define I2C_SDA 21
#define I2C_SCL 22
#include "main.h"
#include <M5Unified.h>
#endif

bool i2c_check(uint8_t addr);