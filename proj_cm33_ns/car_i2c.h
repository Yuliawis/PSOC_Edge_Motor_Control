 
#ifndef CAR_I2C_H
#define CAR_I2C_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
bool car_i2c_init(void);
bool car_i2c_write(uint8_t address, const uint8_t *data, size_t length);
#endif
