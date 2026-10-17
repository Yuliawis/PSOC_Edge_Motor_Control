 




























#if !defined(CYCFG_H)
#define CYCFG_H

#include "cycfg_notices.h"
#include "cycfg_memory.h"
#include "cymem_memory_types.h"
#include "cymem_memory_locations.h"
#include "cymem_CM33_0.h"
#include "cymem_CM33_0_S.h"
#include "cymem_CM55_0.h"
#include "cycfg_clocks.h"
#include "cycfg_clock_types.h"
#include "cycfg_peripheral_clocks.h"
#include "cycfg_system.h"
#include "cycfg_ppc.h"
#include "cycfg_dmas.h"
#include "cycfg_peripherals.h"
#include "cycfg_routing.h"
#include "cycfg_pins.h"
#include "cycfg_protection.h"
#include "cycfg_connectivity_wifi.h"
#include "cycfg_connectivity_bt.h"

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

void init_cycfg_all(void);
void cycfg_config_init(void);
static inline void cycfg_config_reservations(void) {}

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_H */
