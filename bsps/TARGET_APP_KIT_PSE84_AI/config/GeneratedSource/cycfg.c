 




























#include "cycfg.h"

/* This function is provided for compatibility with older 2.X style projects. */
void init_cycfg_all(void)
{
    cycfg_config_init();
    cycfg_config_reservations();
}
void cycfg_config_init(void)
{
    init_cycfg_clocks();
    init_cycfg_peripheral_clocks();
    init_cycfg_system();
    init_cycfg_peripherals();
    init_cycfg_routing();
    init_cycfg_pins();
    init_cycfg_protection();
}
