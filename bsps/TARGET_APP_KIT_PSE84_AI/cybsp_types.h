/***********************************************************************************************/ 



















#pragma once

#include "cybsp_hw_config.h"
#include "cybsp_doc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * \cond INTERNAL
 */
/* WIFI interface types */
#define CYBSP_SDIO_INTERFACE             (0)
#define CYBSP_SPI_INTERFACE              (1)
#define CYBSP_M2M_INTERFACE              (2)

/* Map from the new components to the old interface names for
 * compatibility with code that still depends on those defines */
#if defined(COMPONENT_WIFI_INTERFACE_SDIO)
#define CYBSP_WIFI_INTERFACE_TYPE (CYBSP_SDIO_INTERFACE)
#elif defined(COMPONENT_WIFI_INTERFACE_SPI)
#define CYBSP_WIFI_INTERFACE_TYPE (CYBSP_SPI_INTERFACE)
#elif defined(COMPONENT_WIFI_INTERFACE_M2M)
#define CYBSP_WIFI_INTERFACE_TYPE (CYBSP_M2M_INTERFACE)
#endif
/** \endcond */

/**
 * \addtogroup group_bsp_pin_state Pin States
 * \{
 * Macros to abstract out whether the LEDs & Buttons are wired high or active low.
 */
/** Pin state for the LED on. */
#ifndef CYBSP_LED_STATE_ON
#define CYBSP_LED_STATE_ON          (1U)
#endif
/** Pin state for the LED off. */
#ifndef CYBSP_LED_STATE_OFF
#define CYBSP_LED_STATE_OFF         (0U)
#endif
/** Pin state for when a button is pressed. */
#ifndef CYBSP_BTN_PRESSED
#define CYBSP_BTN_PRESSED           (0U)
#endif
/** Pin state for when a button is released. */
#ifndef CYBSP_BTN_OFF
#define CYBSP_BTN_OFF               (1U)
#endif
/** \} group_bsp_pin_state */

#if defined(__cplusplus)
}
#endif
