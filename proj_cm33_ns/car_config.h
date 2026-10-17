 
#ifndef CAR_CONFIG_H
#define CAR_CONFIG_H

#include "cybsp.h"

/* J7 QWIIC, 3.3 V. Do not use the BSP's generic 1.8 V I2C aliases. */
#define CAR_SCL_PORT CYBSP_I2C_SCL_3V3_PORT
#define CAR_SCL_PIN  CYBSP_I2C_SCL_3V3_PIN
#define CAR_SDA_PORT CYBSP_I2C_SDA_3V3_PORT
#define CAR_SDA_PIN  CYBSP_I2C_SDA_3V3_PIN
#define CAR_PCA9685_ADDRESS 0x5FU
#define CAR_INITIAL_SPEED  1000
#define CAR_MAX_SPEED      2000
#define CAR_COMMAND_TIMEOUT_MS 500U
/* Change individual signs after a wheels-raised direction check. */
#define CAR_MOTOR_DIRECTIONS { 1, 1, 1, 1 }

#endif
