/**
 * @brief       SX128X.c
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/January/2019
 * @version     29/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "SX128X.h"


/**
 * @brief       SX128X_Init ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:       SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX128X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t SX128X_Init ( SPI_parameters_t mySPI_parameters )
{
    spi_status_t aux;

    aux  =   spi_init ( mySPI_parameters );



    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       GetStatus ( SPI_parameters_t, SX128X_data_t* )
 *
 * @details     It gets the transceiver status.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   myStatus:          Status of the transceiver.
 *
 *
 * @return       Status of GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        07/February/2019
 * @version     07/February/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t GetStatus ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myStatus )
{
    uint8_t      cmd   =    0U;
    spi_status_t aux;

    /* Send command  */
    cmd     =   SX128X_GET_STATUS;
    aux     =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

    /* Parse the data    */
    myStatus->status     =   cmd;




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetSleep ( SPI_parameters_t , SX128X_set_sleep_sleep_config0_t , SX128X_set_sleep_sleep_config1_t , SX128X_set_sleep_sleep_config2_t )
 *
 * @details     It sets the transceiver to Sleep mode with the lowest current consumption possible.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myDataRAM:         Data RAM behavior.
 * @param[in]    myDataBuffer:      Data Buffer behavior.
 * @param[in]    myInstructionRAM:  Instruction RAM behavior.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetSleep.
 *
 *
 * @author      Manuel Caballero
 * @date        10/February/2019
 * @version     10/February/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t SetSleep ( SPI_parameters_t mySPI_parameters, SX128X_set_sleep_sleep_config0_t myDataRAM, SX128X_set_sleep_sleep_config1_t myDataBuffer, SX128X_set_sleep_sleep_config2_t myInstructionRAM )
{
    uint8_t      cmd[2]   =    { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]  =   SX128X_SET_SLEEP;
    cmd[1]  =   ( myDataRAM | myDataBuffer | myInstructionRAM );
    aux     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetStandby ( SPI_parameters_t , SX128X_set_standby_standbyconfig_t )
 *
 * @details     It sets the transceiver to Stand-by mode.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myDataRAM:         Data RAM behavior.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetStandby.
 *
 *
 * @author      Manuel Caballero
 * @date        11/February/2019
 * @version     11/February/2019   The ORIGIN
 * @pre         After power on or application of a reset, the transceiver will enter in STDBY_RC mode running with a 13 MHz RC clock.
 * @warning     N/A.
 */
SX128X_status_t SetStandby ( SPI_parameters_t mySPI_parameters, SX128X_set_standby_standbyconfig_t myStandbyConfig )
{
    uint8_t      cmd[2]   =    { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]  =   SX128X_SET_STANDBY;
    cmd[1]  =   myStandbyConfig;
    aux     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetFs ( SPI_parameters_t )
 *
 * @details     It sets the device in Frequency Synthesizer mode where the PLL is locked to the carrier frequency.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetFs.
 *
 *
 * @author      Manuel Caballero
 * @date        11/February/2019
 * @version     11/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetFs ( SPI_parameters_t mySPI_parameters )
{
    uint8_t      cmd   =    0U;
    spi_status_t aux;

    /* Send command  */
    cmd  =   SX128X_SET_FS;
    aux  =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetTx ( SPI_parameters_t , SX128X_set_tx_rx_timeout_definition_t, uint16_t )
 *
 * @details     It sets the device in Transmit mode.
 *
 *                  Time-out duration = periodBase * periodBaseCount
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myTimeoutStep:     periodBase.
 * @param[in]    myperiodBaseCount: periodBaseCount.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetTx.
 *
 *
 * @author      Manuel Caballero
 * @date        12/February/2019
 * @version     12/February/2019   The ORIGIN
 * @pre         If myperiodBaseCount = 0x0000, No time-out, Tx Single mode, the device will stay in Tx Mode until the packet is
 *              transmitted and returns in STDBY_RC mode upon completion.
 * @pre         If myperiodBaseCount = Others, Time-out active. The device remains in Rx mode, it returns automatically to STDBY_RC mode
 *              on timer end-of-count or when a packet has been received. As soon as a packet is detected, the timer is automatically
 *              disabled to allow complete reception of the packet.
 * @warning     Clear IRQ status before using this command.
 */
SX128X_status_t SetTx ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myTimeoutStep, uint16_t myperiodBaseCount )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_TX;
    cmd[1]   =   myTimeoutStep;
    cmd[2]   =   (uint8_t)( ( myperiodBaseCount & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myperiodBaseCount & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetRx ( SPI_parameters_t , SX128X_set_tx_rx_timeout_definition_t, uint16_t )
 *
 * @details     It sets the device in Receiver mode.
 *
 *                  Time-out duration = periodBase * periodBaseCount
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myTimeoutStep:     periodBase.
 * @param[in]    myperiodBaseCount: periodBaseCount.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetRx.
 *
 *
 * @author      Manuel Caballero
 * @date        12/February/2019
 * @version     12/February/2019   The ORIGIN
 * @pre         If myperiodBaseCount = 0x0000, No time-out. Rx Single mode. The device will stay in Rx mode until a
 *              reception occurs and the devices return in STDBY_RC mode upon completion.
 * @pre         If myperiodBaseCount = 0xFFFF, Rx Continuous mode. The device remains in Rx mode until the host sends
 *              a command to change the operation mode. The device can receive several packets. Each time a packet is
 *              received, a 'packet received' indication is given to the host and the device will continue to search for a new packet.
 * @pre         If myperiodBaseCount = Others, Time-out active. The device remains in Rx mode, it returns automatically to STDBY_RC mode
 *              on timer end-of-count or when a packet has been received. As soon as a packet is detected, the timer is automatically
 *              disabled to allow complete reception of the packet.
 * @warning     The IRQ status should be cleared prior to using this command.
 */
SX128X_status_t SetRx ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myTimeoutStep, uint16_t myperiodBaseCount )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_RX;
    cmd[1]   =   myTimeoutStep;
    cmd[2]   =   (uint8_t)( ( myperiodBaseCount & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myperiodBaseCount & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}
