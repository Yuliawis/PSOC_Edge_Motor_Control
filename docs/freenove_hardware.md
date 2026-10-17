# Freenove FNK0053 migration to PSoC Edge E84 AI

## Current scope and constraint

The firmware replaces the ESP32 for four DC motors using the existing Freenove
shield's PCA9685. No ESP32 firmware, Arduino libraries, or extra motor driver is
required. Light sensing is **not enabled**: with the ESP32 removed and no added
components or board rework, the stock light circuit has no verified compatible
analog connection to this AI kit. There is no simulated sensor input.

The Freenove pair of photoresistors produces one 0–3.3 V balance signal at the
ESP32 GPIO33 socket contact, rather than two independent ADC signals. Equal
illumination gives approximately half supply. The AI kit analog domain and J17
are 1.8 V, and J17 is unpopulated by default. Do not connect GPIO33 to J17 or
another 1.8 V pin. Firmware configuration cannot resolve this voltage mismatch.
Future sensing requires a suitable interface, or isolating and repowering the
sensor divider plus providing an accessible analog connection; neither is part
of this no-added-hardware configuration.

## Motor connections

Remove all power before wiring. Remove the ESP32 from the Freenove shield.
Keep the motors plugged into the shield. Use signal names on the shield/socket,
not the ESP32 module's physical pin numbers. The following mapping matches the
included `APP_KIT_PSE84_AI` BSP.

| PSoC AI kit connection | Freenove shield connection |
| --- | --- |
| J7 pin 1, GND | GND |
| J7 pin 3, P17.1, SDA 3.3 V | ESP32 GPIO13 socket contact, PCA9685 SDA |
| J7 pin 4, P17.0, SCL 3.3 V | ESP32 GPIO14 socket contact, PCA9685 SCL |
| J7 pin 2, 3.3 V | Shield 3V3 logic rail, only if not already powered |
| No connection | GPIO33 light-sensor signal |

J7 is also unpopulated on the default AI kit described in the kit guide. If it
is absent on your board, these signals are available at its solder pads, but
attaching wires requires soldering. If neither added connectors nor soldering
is possible, even motor wiring is physically blocked. This is an electrical
connection map, not a claim that a stock QWIIC cable can plug into both boards.

Power the PSoC through its normal USB supply. Keep the car battery connected
only through the original shield power circuitry for the motors. Never power
motors from J7, USB GPIO rails, or a PSoC output. Do not connect the car battery
or shield 5 V to J7.2. Check how the shield's 3.3 V rail is supplied after ESP32
removal: avoid joining two independently powered 3.3 V regulators. The shield
logic must have power; I2C wires alone do not supply it. Confirm SDA/SCL idle
near 3.3 V and existing pull-ups are present before operation. Do not use the
BSP generic `CYBSP_I2C_SDA/SCL` aliases: these select the 1.8 V bus.

## Bring-up

1. Lift all wheels off the ground and keep motor power off while programming.
2. Build and program from the application root with `make build -j8` and
   `make program`. This retains the original three-image secure boot packaging.
3. Open KitProg3 UART at 115200 baud, 8N1, no flow control. Use a terminal that
   sends each keystroke immediately. The board reports either ready/stopped or
   an I2C fault. `i` retries initialization without starting motion.
4. Apply shield power. If necessary press `i`. Briefly press `w` and check each
   wheel. Adjust `CAR_MOTOR_DIRECTIONS` in `proj_cm33_ns/car_config.h` if a
   motor is reversed. M1/M2 and M3/M4 form the two sides as in Freenove's example;
   verify your motor plugs match that arrangement.
5. Test `s`, `a`, `d`, and `x`, then verify motion stops after releasing a key.
   Repeat a direction key less than 500 ms apart to continue motion. Terminal
   key-repeat startup delay can cause an initial pause; this is expected.

| Key | Action |
| --- | --- |
| w / s | Forward / reverse |
| a / d | Turn left / right in place |
| 1 / 2 / 3 / 4 | Select M1 / M2 / M3 / M4; stop all motors |
| 0 | Select whole-car control; stop all motors |
| x or space | Stop |
| + / - | Adjust speed for the next direction command |
| i | Retry controller initialization, stopped |
| ? | Show help and hardware limitation |

Initial duty is 1000/4096; maximum is 2000/4096. The PCA9685 operates at nominal
50 Hz, matching the original kit. Every direction command first switches all
motor inputs off and waits 2 ms. A SysTick timer measures the 500 ms command
timeout. Unknown input and help/speed commands do not renew that timeout.

The timeout is a firmware control feature, not an independent power cutoff.
PCA9685 outputs can continue through CPU reset, debug halt, or loss of the I2C
connection. Stop writes are attempted on communication errors, but cannot be
guaranteed on a broken bus. Keep the car power switch accessible; switch motor
power off before reset/debugging or when a stop fails.

## Implementation

CM33 non-secure owns the console, GPIO I2C, and motor driver. Secure startup is
retained. CM55's image remains in the build, but CM33 does not launch it because
the base CM55 application reinitializes shared BSP pins. No ML model is needed
for motor commands, and no AI inference has been added.

Software I2C uses open-drain P17.0/P17.1 with bounded clock-stretch waits and
startup bus recovery. Hardware PWM remains on the shield; the CPU does not
generate motor pulses. PCA9685 address is 0x5F. Channel pairs are M1 15/14,
M2 9/8, M3 12/13, M4 10/11. Generated BSP configuration files are unchanged.

## Sources

- [Freenove motor implementation](https://github.com/Freenove/Freenove_4WD_Car_Kit_for_ESP32/blob/master/Sketches/01.1_Car_Move_and_Turn/Freenove_4WD_Car_For_ESP32.cpp)
- [Freenove light-sensor circuit and behavior](https://docs.freenove.com/projects/fnk0053/en/latest/fnk0053/codes/tutorial/4_Light_Tracing_Car.html)
- [Infineon AI kit guide: J7, J17, and power domains](https://documentation.infineon.com/psocedge/docs/cci1762693051052)

The build can be checked locally. Physical wiring, wheel direction, timing on
the bus, and power integrity still require testing on the actual car.
