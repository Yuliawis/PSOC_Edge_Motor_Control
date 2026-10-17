 





































#ifndef _RETARGET_IO_INIT_H_
#define _RETARGET_IO_INIT_H_

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cybsp.h"
#include "mtb_hal.h"
#include "cy_retarget_io.h"
#include "mtb_syspm_callbacks.h"

/*******************************************************************************
* Macros
*******************************************************************************/

/* retarget-io deepsleep callback macros */
#define DEBUG_UART_RTS_PORT     (NULL)
#define DEBUG_UART_RTS_PIN      (0U)

/* Default syspm callback configuration elements */
#define SYSPM_SKIP_MODE         (0U)
#define SYSPM_CALLBACK_ORDER    (1U)


/*******************************************************************************
* Function prototypes
*******************************************************************************/
void init_retarget_io(void);

/*******************************************************************************
* Function Name: handle_app_error
********************************************************************************
* Summary:
* User defined error handling function
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
__STATIC_INLINE void handle_app_error(void)
{
    /* Disable all interrupts. */
    __disable_irq();

    CY_ASSERT(0);

    /* Infinite loop */
    while(true);
}

#endif /* _RETARGET_IO_INIT_H_ */

/* [] END OF FILE */
