/***********************************************************************************************/ 

























#pragma once

#include "cy_result.h"
#include "cybsp_types.h"
#include "cycfg_pins.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef CYBSP_USER_BTN_DRIVE
#define CYBSP_USER_BTN_DRIVE          (CYHAL_GPIO_DRIVE_PULLUP)
#endif

#ifndef CYBSP_DEBUG_UART_CTS
#define CYBSP_DEBUG_UART_CTS (NC)
#endif
#ifndef CYBSP_DEBUG_UART_RTS
#define CYBSP_DEBUG_UART_RTS (NC)
#endif

// On CY_IP_MXSMIF version 4 CYBSP_QSPI_SCK is dedicated pin, not a GPIO, and therefore has no
// location in the
// device configurator to which an alias can be assigned. The QSPI HAL and serial-flash drivers
// require that a
// value of "NC" be provided for this pin. Provide this alias by default in the BSP so that this
// difference in
// pin behavior is transparent to applications.
#ifndef CYBSP_QSPI_SCK
#define CYBSP_QSPI_SCK (NC)
#endif

#if defined(__cplusplus)
}
#endif
