 
#include <stdio.h>
#include "car_config.h"
#include "car_motor.h"
#include "car_app.h"

static volatile uint32_t milliseconds;
static void tick(void) { ++milliseconds; }
static void help(void)
{
    printf("\r\nFreenove FNK0053 / PSoC Edge E84 AI\r\n"
           "w forward | s reverse | a left | d right | x/SPACE stop\r\n"
           "1-4 select one motor (others stopped) | 0 select whole car\r\n"
           "In single-motor mode use w/s; a/d are disabled.\r\n"
           "+/- speed | ? help | i retry motor initialization (stopped)\r\n"
           "Repeat motion keys within 500 ms to keep moving.\r\n"
           "Light sensing unavailable: stock 3.3 V signal cannot connect\r\n"
           "to the kit's 1.8 V analog input without hardware changes.\r\n");
}
void car_app_run(void)
{
    int16_t speed = CAR_INITIAL_SPEED;
    unsigned selected_motor = 0U; /* 0: whole car, 1-4: one motor */
    bool moving = false;
    bool ready = car_motor_init();
    uint32_t last_command = 0U;
    uint32_t last_led = 0U;
    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU, SystemCoreClock / 1000U);
    (void)Cy_SysTick_SetCallback(0U, tick);
    help();
    printf("Motor controller: %s\r\n", ready ? "ready, stopped" : "FAULT: check power/I2C, then press i");
    for (;;)
    {
        /* Direct nonblocking RX avoids stdio line buffering. */
        uint32_t input = Cy_SCB_UART_Get(CYBSP_DEBUG_UART_HW);
        if (input != CY_SCB_UART_RX_NO_DATA)
        {
            int16_t left = 0, right = 0;
            bool motion = false;
            switch ((char)input)
            {
                case 'w': left = -speed; right = -speed; motion = true; break;
                case 's': left = speed; right = speed; motion = true; break;
                case 'a': if (selected_motor == 0U)
                          { left = -speed; right = speed; motion = true; } break;
                case 'd': if (selected_motor == 0U)
                          { left = speed; right = -speed; motion = true; } break;
                case '0': case '1': case '2': case '3': case '4':
                          moving = false;
                          ready = car_motor_stop() && ready;
                          selected_motor = (unsigned)(input - '0');
                          if (selected_motor == 0U) printf("Selected: whole car, stopped\r\n");
                          else printf("Selected: M%u, others stopped\r\n", selected_motor);
                          if (!ready) printf("Motor fault; cut power if stop failed, then press i.\r\n");
                          break;
                case 'x': case ' ': moving = false; ready = car_motor_stop() && ready; break;
                case '+': if (speed < CAR_MAX_SPEED) speed += 100;
                          printf("Speed: %d\r\n", speed); break;
                case '-': if (speed > 100) speed -= 100;
                          printf("Speed: %d\r\n", speed); break;
                case 'i': moving = false; ready = car_motor_init();
                          printf("Motor init: %s\r\n", ready ? "ready, stopped" : "FAULT"); break;
                case '?': help(); break;
                default: break; /* Unknown input never renews the motion timeout. */
            }
            if (motion && ready)
            {
                if (selected_motor == 0U)
                {
                    ready = car_motor_drive(left, right);
                }
                else
                {
                    int16_t duty[4] = {0, 0, 0, 0};
                    duty[selected_motor - 1U] = left;
                    ready = car_motor_drive_all(duty[0], duty[1], duty[2], duty[3]);
                }
                moving = ready;
                last_command = milliseconds;
                if (!ready) printf("Motor I2C fault; stop attempted. Cut motor power if still moving.\r\n");
            }
        }
        uint32_t now = milliseconds;
        if (moving && (uint32_t)(now - last_command) >= CAR_COMMAND_TIMEOUT_MS)
        {
            moving = false;
            ready = car_motor_stop();
            printf("Command timeout: %s\r\n", ready ? "stopped" : "STOP FAILED; cut motor power");
        }
        if ((uint32_t)(now - last_led) >= 500U)
        {
            last_led = now;
            Cy_GPIO_Inv(CYBSP_USER_LED1_PORT, CYBSP_USER_LED1_PIN);
        }
        Cy_SysLib_Delay(1U);
    }
}
