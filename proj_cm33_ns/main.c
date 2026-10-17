 





































/*******************************************************************************
* Header Files
*******************************************************************************/

#include "cybsp.h"
#include "retarget_io_init.h"
#include "car_app.h"

int main(void)
{
    if (cybsp_init() != CY_RSLT_SUCCESS)
    {
        handle_app_error();
    }
    __enable_irq();
    init_retarget_io();
    /* CM33 owns car I/O. Do not launch CM55: its BSP init would reconfigure
     * shared pins. Secure boot and the CM55 image stay in the base project. */
    car_app_run();
}
