/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral RTC using the
 * 				periodic wake-up timer. The LED will change its state every 1 second.
 *
 * 				The microcontroller will remain in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with Atollic TrueSTUDIO for STM32
 *              ( v9.0.1 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */


#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Constants.
 */



/**@brief Variables.
 */
volatile uint32_t myLEDstate	 =	 0;				/*!<   LED state                         */




/**@brief Function for application main entry.
 */
int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_RTC     ();



	while ( 1 )
	{
		HAL_PWR_EnterSTOPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
	}
}
