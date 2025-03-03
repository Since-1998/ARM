/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     23/May/2017     All the LEDs OFF at the beginning.
 *              5/May/2017      The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ ){
            NRF_GPIO->OUTSET        =   ( 1 << i );

            NRF_GPIO->PIN_CNF[i]    =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                        GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                        GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                        GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                        GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;
    }

}


/**
 * @brief       void conf_Timer0  ( void )
 * @details     Two channels will create an interrupt. Channel zero at 0.125s and channel two at 0.5s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.125s.
 *
 *                 --- Channel 1:
 *                  * Overflow:             ( 4*125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.5s.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_Timer0  ( void )
{
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;                   // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   125000;                                                                     // ( 125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.125s
    NRF_TIMER0->CC[1]       =   4*125000;                                                                   // ( 4*125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.5s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos ) |
                                ( TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos );

    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos );// |
    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos );     // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] and COMPARE[1] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


/**
 * @brief       void conf_Timer1  ( void )
 * @details     One channels will create an interrupt. Channel zero at 0.125s and channel two at 0.5s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 65535 * (f_Timer0)^(-1) ) = ( 65535 * (1MHz)^(-1) ) ~ 65.535ms.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_Timer1  ( void )
{
    NRF_TIMER1->TASKS_STOP  =   1;
    NRF_TIMER1->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER1->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER1->BITMODE     =   TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;                   // 16 bit mode.
    NRF_TIMER1->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER1->CC[0]       =   25000;                                                                      // ( 25000 * (f_Timer0)^(-1) ) = ( 25000 * (1MHz)^(-1) ) = 25ms
    NRF_TIMER1->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER1 on COMPARE[0] event.
}




/**
 * @brief       void conf_Timer2  ( void )
 * @details     Interrupt on Channel zero at 255us.
 *
 *              Timer2:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 8-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 255 * (f_Timer2)^(-1) ) = ( 255 * (1MHz)^(-1) ) ~ 255us
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        23/May/2017
 * @version     23/May/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */

void conf_Timer2  ( void )
{
    NRF_TIMER2->TASKS_STOP  =   1;
    NRF_TIMER2->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER2->PRESCALER   =   5U;                                                                         // f_Timer2 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER2->BITMODE     =   TIMER_BITMODE_BITMODE_08Bit << TIMER_BITMODE_BITMODE_Pos;                   // 8 bit mode.
    NRF_TIMER2->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER2->CC[0]       =   255;                                                                        // ( 255 * (f_Timer2)^(-1) ) = ( 255 * (1MHz)^(-1) ) ~ 255us

    NRF_TIMER2->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER2->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER2 on COMPARE[0] event.


    NVIC_EnableIRQ ( TIMER2_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}




/**
 * @brief       void delay  ( void )
 * @details     Delay based on Timer1 ( channel 0 ). The time delay is about 10 * 25ms = 0.25s
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        23/May/2017
 * @version     23/May/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void delay  ( void )
{
    uint32_t i = 0;

    NRF_TIMER1->TASKS_START = 1;    // Start Timer1

    for ( i = 0; i < 10; i++ ){
            while ( NRF_TIMER1->EVENTS_COMPARE[0] == 0 );
            NRF_TIMER1->EVENTS_COMPARE[0]    =   0;
        }

    NRF_TIMER1->TASKS_STOP = 1;    // Stop Timer1
}
