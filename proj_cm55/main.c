 




































/*******************************************************************************
* Header File
*******************************************************************************/

#include "cybsp.h"

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM55 application. 
* 
* CM33 application enables the CM55 CPU and then the CM55 CPU enters 
* deep sleep.
* 
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals. */
    result = cybsp_init();

    /* Board init failed. Stop program execution. */
    if (CY_RSLT_SUCCESS != result)
    {
        /* Disable all interrupts. */
        __disable_irq();

        CY_ASSERT(0);

        /* Infinite loop */
        while(true);
    }

    /* Enable global interrupts. */
    __enable_irq();

    /* Put the CPU to Deep Sleep. */
    for (;;)
    {
        Cy_SysPm_CpuEnterDeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
