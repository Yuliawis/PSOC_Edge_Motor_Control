# PSoC Edge E84 AI — Freenove FNK0053 motor control

This project adapts the existing Infineon Hello World application for the
`APP_KIT_PSE84_AI` board. It controls the Freenove shield's four DC motors
through its PCA9685, with the ESP32 removed.

**Status:** motor firmware builds successfully. Light sensing is blocked by the
hardware constraints: the stock sensor output is 0–3.3 V, while the AI kit's
analog expansion is 1.8 V and unpopulated. No external ADC, voltage divider,
or ESP32 sensor bridge has been added. Do not connect that signal directly.

See [wiring, power, commands, and bring-up](docs/freenove_hardware.md) before
connecting the boards. The AI kit's J7 connector is also unpopulated by default;
using its I2C pads requires a physical wiring/soldering connection.

## Build and program

Use the installed ModusToolbox environment, from the application root:

```sh
make build -j8
make program
```

The build uses GCC_ARM and the existing secure boot/signing setup. The combined
image is `build/app_combined.hex`. Programming has not been performed as part
of this change. Firmware has not been tested on the physical car.

Open KitProg3 UART at **115200, 8N1**, with immediate keystroke transmission:

| Command | Action |
| --- | --- |
| `w`, `s` | Forward, reverse |
| `a`, `d` | Left, right turn |
| `1` / `2` / `3` / `4` | Select one motor; stop all motors on selection |
| `0` | Select whole-car control; stop all motors on selection |
| `x` or space | Stop |
| `+`, `-` | Adjust speed for next motion command |
| `i` | Retry motor initialization, stopped |
| `?` | Help |

Starts stopped. Repeat direction keys within 500 ms to keep moving. Switch
motor power off before resetting or debugging: PCA9685 can retain its outputs
when the CPU stops, and an I2C failure can prevent a stop command reaching it.

## Source layout

To test M1 alone, press `1`, then `w` or `s`. M2-M4 stay stopped. Press `0`
to return to whole-car driving. Turning keys `a`/`d` are disabled when a single
motor is selected. The 500 ms timeout and global stop apply in both modes.

Code can set four independent duties with
`car_motor_drive_all(m1, m2, m3, m4)`. Direct driver calls do not implement
a timeout; the caller must stop the motors.

- `proj_cm33_ns/car_app.c`: console, command timeout, heartbeat.
- `proj_cm33_ns/car_motor.c`: four-motor PCA9685 control.
- `proj_cm33_ns/car_i2c.c`: open-drain GPIO I2C on P17.0/P17.1.
- `proj_cm33_ns/car_config.h`: pins, motor polarity, speed limits, address.
- `proj_cm33_s`: original secure startup.
- `proj_cm55`: original image retained for packaging; not launched by CM33.

CM55 is not launched because the base application reinitializes shared BSP
pins. BSP peripheral settings are unchanged.