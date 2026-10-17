 
#include "car_config.h"
#include "car_i2c.h"
#include "car_motor.h"

static const uint8_t forward_channel[4] = {15U, 9U, 12U, 10U};
static const uint8_t reverse_channel[4] = {14U, 8U, 13U, 11U};
static const int8_t direction[4] = CAR_MOTOR_DIRECTIONS;
static bool write_register(uint8_t reg, uint8_t value)
{
    const uint8_t bytes[] = {reg, value};
    return car_i2c_write(CAR_PCA9685_ADDRESS, bytes, sizeof(bytes));
}
static bool channel(uint8_t ch, uint16_t duty)
{
    /* Full-off bit explicitly disables zero duty. MODE1 auto-increment on. */
    const uint8_t bytes[] = {(uint8_t)(0x06U + 4U * ch), 0U, 0U,
        (uint8_t)duty, (uint8_t)(duty ? (duty >> 8) : 0x10U)};
    return car_i2c_write(CAR_PCA9685_ADDRESS, bytes, sizeof(bytes));
}
bool car_motor_stop(void)
{
    bool ok = true;
    /* Attempt every output even if one transfer fails. */
    for (unsigned i = 0; i < 4U; ++i)
    {
        if (!channel(forward_channel[i], 0U)) ok = false;
        if (!channel(reverse_channel[i], 0U)) ok = false;
    }
    return ok;
}
bool car_motor_init(void)
{
    if (!car_i2c_init()) return false;
    /* Sleep, disable broadcast addresses, enable auto-increment. */
    if (!write_register(0x00U, 0x30U)) return false;
    if (!car_motor_stop()) return false;
    /* Clear ALL_LED override, then use 50 Hz as in the stock kit (25 MHz osc). */
    if (!write_register(0xFDU, 0U) || !write_register(0xFAU, 0U) ||
        !write_register(0xFBU, 0U) || !write_register(0xFCU, 0U) ||
        !write_register(0xFEU, 121U) || !write_register(0x01U, 0x04U) ||
        !write_register(0x00U, 0x20U)) return false;
    Cy_SysLib_DelayUs(500U);
    return write_register(0x00U, 0xA0U);
}
bool car_motor_drive(int16_t left, int16_t right)
{
    return car_motor_drive_all(left, left, right, right);
}
bool car_motor_drive_all(int16_t m1, int16_t m2, int16_t m3, int16_t m4)
{
    const int16_t requested[4] = {m1, m2, m3, m4};
    /* Break before make on ALL motors, including direction changes. */
    if (!car_motor_stop()) return false;
    Cy_SysLib_Delay(2U);
    for (unsigned i = 0; i < 4U; ++i)
    {
        int32_t speed = requested[i];
        if (speed > CAR_MAX_SPEED) speed = CAR_MAX_SPEED;
        if (speed < -CAR_MAX_SPEED) speed = -CAR_MAX_SPEED;
        speed *= direction[i];
        if (!channel(speed >= 0 ? forward_channel[i] : reverse_channel[i],
                     (uint16_t)(speed >= 0 ? speed : -speed)))
        {
            (void)car_motor_stop();
            return false;
        }
    }
    return true;
}
