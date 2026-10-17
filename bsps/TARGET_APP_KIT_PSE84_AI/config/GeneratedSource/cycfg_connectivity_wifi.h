 



























#if !defined(CYCFG_CONNECTIVITY_WIFI_H)
#define CYCFG_CONNECTIVITY_WIFI_H

#include "cycfg_notices.h"
#include "cycfg_pins.h"

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define wifi_0_power_0_ENABLED 1U
#define CYCFG_WIFI_HOST_WAKE_ENABLED (1u)
#define CYCFG_WIFI_HOST_WAKE_GPIO CYBSP_WIFI_HOST_WAKE_HAL_PORT_PIN
#define CYCFG_WIFI_HOST_WAKE_IRQ_EVENT CYBSP_WIFI_HOST_WAKE_HAL_IRQ

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_CONNECTIVITY_WIFI_H */
