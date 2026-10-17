 
#include "car_config.h"
#include "car_i2c.h"

/* Single-master, open-drain software I2C. PCA9685 generates PWM in hardware.
 * No interrupt masking, no SCB/clock reassignment, bounded clock-stretch wait.
 * Both pins must have external pull-ups to 3.3 V (check the stock boards).
 */
static void pause_bus(void) { Cy_SysLib_DelayUs(5U); }
static void sda(uint32_t high) { Cy_GPIO_Write(CAR_SDA_PORT, CAR_SDA_PIN, high); }
static void scl_low(void) { Cy_GPIO_Clr(CAR_SCL_PORT, CAR_SCL_PIN); pause_bus(); }
static bool scl_high(void)
{
    Cy_GPIO_Set(CAR_SCL_PORT, CAR_SCL_PIN);
    for (unsigned i = 0; i < 100U; ++i)
    {
        if (Cy_GPIO_Read(CAR_SCL_PORT, CAR_SCL_PIN))
        {
            pause_bus();
            return true;
        }
        Cy_SysLib_DelayUs(10U);
    }
    return false;
}
static bool stop_bus(void)
{
    scl_low();
    sda(0U);
    pause_bus();
    bool ok = scl_high();
    sda(1U);
    pause_bus();
    return ok && (Cy_GPIO_Read(CAR_SDA_PORT, CAR_SDA_PIN) != 0U);
}
bool car_i2c_init(void)
{
    Cy_GPIO_Pin_FastInit(CAR_SCL_PORT, CAR_SCL_PIN,
                        CY_GPIO_DM_OD_DRIVESLOW, 1U, HSIOM_SEL_GPIO);
    Cy_GPIO_Pin_FastInit(CAR_SDA_PORT, CAR_SDA_PIN,
                        CY_GPIO_DM_OD_DRIVESLOW, 1U, HSIOM_SEL_GPIO);
    /* Recover a slave left mid-byte after an MCU reset. */
    sda(1U);
    for (unsigned i = 0; i < 9U; ++i)
    {
        scl_low();
        if (!scl_high()) return false;
    }
    return stop_bus();
}
static bool send_byte(uint8_t value)
{
    for (unsigned i = 0; i < 8U; ++i)
    {
        scl_low();
        sda((value & 0x80U) != 0U);
        pause_bus();
        if (!scl_high()) return false;
        value <<= 1;
    }
    scl_low();
    sda(1U);
    pause_bus();
    if (!scl_high()) return false;
    bool ack = (Cy_GPIO_Read(CAR_SDA_PORT, CAR_SDA_PIN) == 0U);
    scl_low();
    return ack;
}
bool car_i2c_write(uint8_t address, const uint8_t *data, size_t length)
{
    sda(1U);
    if (!scl_high() || !Cy_GPIO_Read(CAR_SDA_PORT, CAR_SDA_PIN)) return false;
    sda(0U);
    pause_bus();
    bool ok = send_byte((uint8_t)(address << 1));
    for (size_t i = 0; ok && i < length; ++i) ok = send_byte(data[i]);
    bool stopped = stop_bus();
    return ok && stopped;
}
