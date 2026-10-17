 



























#include "cycfg_routing.h"
#include "cy_trigmux.h"
#include "stdbool.h"
#include "cy_device_headers.h"

void init_cycfg_routing(void)
{
    Cy_TrigMux_Connect(PERI_0_TRIG_IN_MUX_0_PERI1_HSIOM_TR_OUT1, PERI_0_TRIG_OUT_MUX_0_PDMA0_TR_IN0, false, TRIGGER_TYPE_LEVEL);
    Cy_TrigMux_Connect(PERI_1_TRIG_IN_MUX_0_PDMA0_TR_OUT0, PERI_1_TRIG_OUT_MUX_0_AXIDMAC_TR_IN0, false, TRIGGER_TYPE_EDGE);
}
