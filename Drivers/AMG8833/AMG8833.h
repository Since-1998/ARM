/**
 * @brief       AMG8833.h
 * @details     Infrared Array Sensor "Grid-EYE".
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/December/2018
 * @version     19/December/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include <math.h>
#include "i2c.h"


#ifndef AMG8833_H_
#define AMG8833_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    AMG8833_ADDRESS_AD_SELECT_VDD   =   0b1101001,    /*!<   AMG8833 I2C Address: AD_SELECT to VDD                */
    AMG8833_ADDRESS_AD_SELECT_GND   =   0b1101000     /*!<   AMG8833 I2C Address: AD_SELECT to GND                */
} AMG8833_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
    AMG8833_PCTL  =   0x00,                           /*!<  Power Control Register              ( Read/Write )      */
    AMG8833_RST   =   0x01,                           /*!<  Reset Register                      ( Write Only )      */
    AMG8833_FPSC  =   0x02,                           /*!<  Frame Rate Register                 ( Read/Write )      */
    AMG8833_INTC  =   0x03,                           /*!<  Interrupt Control Register          ( Read/Write )      */
    AMG8833_STAT  =   0x04,                           /*!<  Status Register                     ( Read Only  )      */
    AMG8833_SCLR  =   0x05,                           /*!<  Status Clear Register               ( Write Only )      */
    AMG8833_AVE   =   0x07,                           /*!<  Average Register                    ( Read/Write )      */
    AMG8833_INTHL =   0x08,                           /*!<  Interrupt Level upper limit [7:0]   ( Read/Write )      */
    AMG8833_INTHH =   0x09,                           /*!<  Interrupt Level upper limit [11:8]  ( Read/Write )      */
    AMG8833_INTLL =   0x0A,                           /*!<  Interrupt Level lower limit [7:0]   ( Read/Write )      */
    AMG8833_INTLH =   0x0B,                           /*!<  Interrupt Level lower limit [11:8]  ( Read/Write )      */
    AMG8833_IHYSL =   0x0C,                           /*!<  Interrupt Hysteresis Level  [7:0]   ( Read/Write )      */
    AMG8833_IHYSH =   0x0D,                           /*!<  Interrupt Hysteresis Level  [11:8]  ( Read/Write )      */
    AMG8833_TTHL  =   0x0E,                           /*!<  Thermistor Register lower  [7:0]    ( Read Only  )      */
    AMG8833_TTHH  =   0x0F,                           /*!<  Thermistor Register upper  [11:8]   ( Read Only  )      */
    AMG8833_INT0  =   0x10,                           /*!<  Interrupt Table Register 0          ( Read Only  )      */
    AMG8833_INT1  =   0x11,                           /*!<  Interrupt Table Register 1          ( Read Only  )      */
    AMG8833_INT2  =   0x12,                           /*!<  Interrupt Table Register 2          ( Read Only  )      */
    AMG8833_INT3  =   0x13,                           /*!<  Interrupt Table Register 3          ( Read Only  )      */
    AMG8833_INT4  =   0x14,                           /*!<  Interrupt Table Register 4          ( Read Only  )      */
    AMG8833_INT5  =   0x15,                           /*!<  Interrupt Table Register 5          ( Read Only  )      */
    AMG8833_INT6  =   0x16,                           /*!<  Interrupt Table Register 6          ( Read Only  )      */
    AMG8833_INT7  =   0x17,                           /*!<  Interrupt Table Register 7          ( Read Only  )      */
    AMG8833_T01L  =   0x80,                           /*!<  Pixel 1 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T01H  =   0x81,                           /*!<  Pixel 1 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T02L  =   0x82,                           /*!<  Pixel 2 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T02H  =   0x83,                           /*!<  Pixel 2 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T03L  =   0x84,                           /*!<  Pixel 3 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T03H  =   0x85,                           /*!<  Pixel 3 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T04L  =   0x86,                           /*!<  Pixel 4 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T04H  =   0x87,                           /*!<  Pixel 4 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T05L  =   0x88,                           /*!<  Pixel 5 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T05H  =   0x89,                           /*!<  Pixel 5 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T06L  =   0x8A,                           /*!<  Pixel 6 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T06H  =   0x8B,                           /*!<  Pixel 6 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T07L  =   0x8C,                           /*!<  Pixel 7 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T07H  =   0x8D,                           /*!<  Pixel 7 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T08L  =   0x8E,                           /*!<  Pixel 8 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T08H  =   0x8F,                           /*!<  Pixel 8 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T09L  =   0x90,                           /*!<  Pixel 9 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T09H  =   0x91,                           /*!<  Pixel 9 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T10L  =   0x92,                           /*!<  Pixel 10 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T10H  =   0x93,                           /*!<  Pixel 10 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T11L  =   0x94,                           /*!<  Pixel 11 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T11H  =   0x95,                           /*!<  Pixel 11 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T12L  =   0x96,                           /*!<  Pixel 12 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T12H  =   0x97,                           /*!<  Pixel 12 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T13L  =   0x98,                           /*!<  Pixel 13 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T13H  =   0x99,                           /*!<  Pixel 13 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T14L  =   0x9A,                           /*!<  Pixel 14 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T14H  =   0x9B,                           /*!<  Pixel 14 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T15L  =   0x9C,                           /*!<  Pixel 15 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T15H  =   0x9D,                           /*!<  Pixel 15 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T16L  =   0x9E,                           /*!<  Pixel 16 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T16H  =   0x9F,                           /*!<  Pixel 16 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T17L  =   0xA0,                           /*!<  Pixel 17 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T17H  =   0xA1,                           /*!<  Pixel 17 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T18L  =   0xA2,                           /*!<  Pixel 18 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T18H  =   0xA3,                           /*!<  Pixel 18 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T19L  =   0xA4,                           /*!<  Pixel 19 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T19H  =   0xA5,                           /*!<  Pixel 19 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T20L  =   0xA6,                           /*!<  Pixel 20 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T20H  =   0xA7,                           /*!<  Pixel 20 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T21L  =   0xA8,                           /*!<  Pixel 21 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T21H  =   0xA9,                           /*!<  Pixel 21 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T22L  =   0xAA,                           /*!<  Pixel 22 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T22H  =   0xAB,                           /*!<  Pixel 22 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T23L  =   0xAC,                           /*!<  Pixel 23 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T23H  =   0xAD,                           /*!<  Pixel 23 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T24L  =   0xAE,                           /*!<  Pixel 24 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T24H  =   0xAF,                           /*!<  Pixel 24 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T25L  =   0xB0,                           /*!<  Pixel 25 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T25H  =   0xB1,                           /*!<  Pixel 25 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T26L  =   0xB2,                           /*!<  Pixel 26 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T26H  =   0xB3,                           /*!<  Pixel 26 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T27L  =   0xB4,                           /*!<  Pixel 27 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T27H  =   0xB5,                           /*!<  Pixel 27 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T28L  =   0xB6,                           /*!<  Pixel 28 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T28H  =   0xB7,                           /*!<  Pixel 28 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T29L  =   0xB8,                           /*!<  Pixel 29 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T29H  =   0xB9,                           /*!<  Pixel 29 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T30L  =   0xBA,                           /*!<  Pixel 30 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T30H  =   0xBB,                           /*!<  Pixel 30 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T31L  =   0xBC,                           /*!<  Pixel 31 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T31H  =   0xBD,                           /*!<  Pixel 31 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T32L  =   0xBE,                           /*!<  Pixel 32 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T32H  =   0xBF,                           /*!<  Pixel 32 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T33L  =   0xC0,                           /*!<  Pixel 33 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T33H  =   0xC1,                           /*!<  Pixel 33 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T34L  =   0xC2,                           /*!<  Pixel 34 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T34H  =   0xC3,                           /*!<  Pixel 34 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T35L  =   0xC4,                           /*!<  Pixel 35 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T35H  =   0xC5,                           /*!<  Pixel 35 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T36L  =   0xC6,                           /*!<  Pixel 36 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T36H  =   0xC7,                           /*!<  Pixel 36 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T37L  =   0xC8,                           /*!<  Pixel 37 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T37H  =   0xC9,                           /*!<  Pixel 37 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T38L  =   0xCA,                           /*!<  Pixel 38 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T38H  =   0xCB,                           /*!<  Pixel 38 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T39L  =   0xCC,                           /*!<  Pixel 39 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T39H  =   0xCD,                           /*!<  Pixel 39 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T40L  =   0xCE,                           /*!<  Pixel 40 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T40H  =   0xCF,                           /*!<  Pixel 40 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T41L  =   0xD0,                           /*!<  Pixel 41 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T41H  =   0xD1,                           /*!<  Pixel 41 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T42L  =   0xD2,                           /*!<  Pixel 42 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T42H  =   0xD3,                           /*!<  Pixel 42 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T43L  =   0xD4,                           /*!<  Pixel 43 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T43H  =   0xD5,                           /*!<  Pixel 43 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T44L  =   0xD6,                           /*!<  Pixel 44 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T44H  =   0xD7,                           /*!<  Pixel 44 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T45L  =   0xD8,                           /*!<  Pixel 45 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T45H  =   0xD9,                           /*!<  Pixel 45 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T46L  =   0xDA,                           /*!<  Pixel 46 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T46H  =   0xDB,                           /*!<  Pixel 46 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T47L  =   0xDC,                           /*!<  Pixel 47 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T47H  =   0xDD,                           /*!<  Pixel 47 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T48L  =   0xDE,                           /*!<  Pixel 48 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T48H  =   0xDF,                           /*!<  Pixel 48 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T49L  =   0xE0,                           /*!<  Pixel 49 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T49H  =   0xE1,                           /*!<  Pixel 49 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T50L  =   0xE2,                           /*!<  Pixel 50 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T50H  =   0xE3,                           /*!<  Pixel 50 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T51L  =   0xE4,                           /*!<  Pixel 51 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T51H  =   0xE5,                           /*!<  Pixel 51 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T52L  =   0xE6,                           /*!<  Pixel 52 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T52H  =   0xE7,                           /*!<  Pixel 52 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T53L  =   0xE8,                           /*!<  Pixel 53 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T53H  =   0xE9,                           /*!<  Pixel 53 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T54L  =   0xEA,                           /*!<  Pixel 54 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T54H  =   0xEB,                           /*!<  Pixel 54 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T55L  =   0xEC,                           /*!<  Pixel 55 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T55H  =   0xED,                           /*!<  Pixel 55 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T56L  =   0xEE,                           /*!<  Pixel 56 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T56H  =   0xEF,                           /*!<  Pixel 56 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T57L  =   0xF0,                           /*!<  Pixel 57 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T57H  =   0xF1,                           /*!<  Pixel 57 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T58L  =   0xF2,                           /*!<  Pixel 58 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T58H  =   0xF3,                           /*!<  Pixel 58 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T59L  =   0xF4,                           /*!<  Pixel 59 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T59H  =   0xF5,                           /*!<  Pixel 59 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T60L  =   0xF6,                           /*!<  Pixel 60 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T60H  =   0xF7,                           /*!<  Pixel 60 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T61L  =   0xF8,                           /*!<  Pixel 61 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T61H  =   0xF9,                           /*!<  Pixel 61 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T62L  =   0xFA,                           /*!<  Pixel 62 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T62H  =   0xFB,                           /*!<  Pixel 62 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T63L  =   0xFC,                           /*!<  Pixel 63 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T63H  =   0xFD,                           /*!<  Pixel 63 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T64L  =   0xFE,                           /*!<  Pixel 64 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T64H  =   0xFF                            /*!<  Pixel 64 Output Value (Upper Level)  ( Read Only  )     */
} AMG8833_register_map_t;



/**
  * @brief   CONFIGURATION REGISTER
  */
/* SOFTWARE RESET BIT <15>
*/
typedef enum
{
    RST_BIT_MASK                      =   ( 1U << 15U ),      /*!<  Software reset bit mask                                                 */
    RST_NORMAL_OPERATION              =   ( 0U << 15U ),      /*!<  Software reset bit: Normal operation                          ( RESET ) */
    RST_SOFTWARE_RESET                =   ( 1U << 15U )       /*!<  Software reset bit: Software reset                                      */
} AMG8833_rst_t;


/* MODE OF OPERATION <14:12>
*/
typedef enum
{
    MOD_MASK                           =   ( 0b111 << 12U ),   /*!<  Mode of operation mask                                                  */
    MOD_POWER_DOWN                     =   ( 0b000 << 12U ),   /*!<  Mode of operation: Power-down                                           */
    MOD_SENSOR_AND_DIE_CONT_CONVERSION =   ( 0b111 << 12U )    /*!<  Mode of operation: Sensor and die continuous conversion (MOD) ( RESET ) */
} AMG8833_mod_t;


/* ADC CONVERSION RATE <11:9>
*/
typedef enum
{
    CR_MASK                           =   ( 0b111 << 9U ),    /*!<  ADC Conversion rate mask                                                */
    CR_1_AVERAGED_SAMPLES             =   ( 0b000 << 9U ),    /*!<  ADC Conversion rate:  1 number of averaged sample                       */
    CR_2_AVERAGED_SAMPLES             =   ( 0b001 << 9U ),    /*!<  ADC Conversion rate:  2 number of averaged sample                       */
    CR_4_AVERAGED_SAMPLES             =   ( 0b010 << 9U ),    /*!<  ADC Conversion rate:  4 number of averaged sample             ( RESET ) */
    CR_8_AVERAGED_SAMPLES             =   ( 0b011 << 9U ),    /*!<  ADC Conversion rate:  8 number of averaged sample                       */
    CR_16_AVERAGED_SAMPLES            =   ( 0b100 << 9U )     /*!<  ADC Conversion rate: 16 number of averaged sample                       */
} AMG8833_cr_t;


/* #DRDY ENABLE BIT <8>
*/
typedef enum
{
    EN_MASK                           =   ( 1U << 8U ),       /*!<  #DRDY enable bit mask                                                   */
    EN_nDRDY_PIN_DISABLED             =   ( 0U << 8U ),       /*!<  #DRDY enable bit: Pin disabled                                ( RESET ) */
    EN_nDRDY_PIN_ENABLED              =   ( 1U << 8U )        /*!<  #DRDY enable bit: Pin enabled                                           */
} AMG8833_en_t;


/* DATA READY BIT <7>
*/
typedef enum
{
    nDRDY_MASK                        =   ( 1U << 7U ),       /*!<  Data ready bit mask                                                     */
    nDRDY_CONVERSION_IN_PROGRESS      =   ( 0U << 7U ),       /*!<  Data ready bit: Conversion in progress                        ( RESET ) */
    nDRDY_CONVERSION_COMPLETED        =   ( 1U << 7U )        /*!<  Data ready bit: Conversion completed                                    */
} AMG8833_ndrdy_t;




/**
  * @brief   MANUFACTURER ID REGISTER
  */
typedef enum
{
    MANUFACTURER_ID_MASK              =   0xFFFF,             /*!<  Manufacturer ID mask                                                    */
    MANUFACTURER_ID_VALUE             =   0x5449              /*!<  Manufacturer ID value                                         ( RESET ) */
} AMG8833_manufacturer_id_register_t;



/**
  * @brief   DEVICE ID REGISTER
  */
typedef enum
{
    DEVICE_ID_MASK                    =   0xFFFF,             /*!<  Device ID mask                                                          */
    DEVICE_ID_VALUE                   =   0x0067              /*!<  Device ID value                                               ( RESET ) */
} AMG8833_device_id_register_t;




/**
  * @brief   CONSTANS TO BE USED IN THE FORMULAS
  *           NOTE: User Guide ( sbou107.pdf ) 5.1 Equations for Calculating Target Object Temperatures, p10.
  */
#define A1        0.00175                                         /*!<  A1                                                                */
#define A2        -0.00001678                                     /*!<  A2                                                                */
#define T_REF     298.15                                          /*!<  T_REF, Kelvin                                                     */
#define B0        -0.0000294                                      /*!<  B0                                                                */
#define B1        -0.00000057                                     /*!<  B1                                                                */
#define B2        -0.00000000463                                  /*!<  B2                                                                */
#define C2        13.4                                            /*!<  C2                                                                */
#define S0        ( 0.00000000000005 + 0.00000000000007 ) / 2.0   /*!<  Primary calibration sensitivity factor ( mean of typical values ) */
#define TEMP_1LSB 0.03125                                         /*!<  Temperature: 1 LSB = 1 / 32�C = 0.03125                           */
#define SVOL_1LSB 156.25                                          /*!<  Sensor voltage: 1 LSB = 156.25 nV                                 */



#ifndef AMG8833_VECTOR_STRUCT_H
#define AMG8833_VECTOR_STRUCT_H
typedef struct
{
    float    ObjectTemperatureC;             /*!<  Temperature of the target object in Celsius degrees                              */
    float    ObjectTemperatureK;             /*!<  Temperature of the target object in Kelvins degrees                              */

    float    TemperatureK;                  /*!<  T_DIE in Kelvins degrees                                                          */
    float    TemperatureC;                  /*!<  T_DIE in Celsius degrees                                                          */
    float    V_Sensor;                      /*!<  Sensor voltage result                                                             */
    float    s0;                            /*!<  Primary calibration sensitivity factor ( typical values: 5�10^�14 and 7�10^�14 )  */

    uint16_t SensorVoltageResultRegister;   /*!<  V_sensor                                                                          */
    uint16_t TemperatureRegister;           /*!<  T_DIE                                                                             */
    uint16_t ConfigurationRegister;         /*!<  Configuration register                                                            */
    
    uint16_t ManufacturerID;                /*!<  Manufacturer ID                                                                   */
    uint16_t DeviceID;                      /*!<  Device ID                                                                         */
} AMG8833_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AMG8833_SUCCESS     =       0,
    AMG8833_FAILURE     =       1
} AMG8833_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
AMG8833_status_t  AMG8833_Init                      ( I2C_parameters_t myI2Cparameters                                  );

/** It gets the manufacturer ID.
  */
AMG8833_status_t  AMG8833_GetManufacturerID         ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myManufacturerID );

/** It gets the device ID.
  */
AMG8833_status_t  AMG8833_GetDeviceID               ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myDeviceID       );

/** It reads the configuration register.
  */
AMG8833_status_t  AMG8833_ReadConfigurationRegister ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myConfReg        );

/** It performs a software reset.
  */
AMG8833_status_t  AMG8833_SoftwareReset             ( I2C_parameters_t myI2Cparameters                                  );

/** It sets mode of operation.
  */
AMG8833_status_t  AMG8833_SetModeOperation          ( I2C_parameters_t myI2Cparameters, AMG8833_mod_t myModeOpreation    );

/** It sets conversion rate.
  */
AMG8833_status_t  AMG8833_SetConversionRate         ( I2C_parameters_t myI2Cparameters, AMG8833_cr_t myConversionRate    );

/** It sets #DRDY control.
  */
AMG8833_status_t  AMG8833_SetnDRDY_EnableBit        ( I2C_parameters_t myI2Cparameters, AMG8833_en_t myEnableBit         );

/** It reads raw temperature ( T_DIE ) register.
  */
AMG8833_status_t  AMG8833_GetRawTemperature         ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myRawTemperature );

/** It reads raw sensor voltage result ( V_SENSOR ) register.
  */
AMG8833_status_t  AMG8833_GetRawSensorVoltage       ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myRawVoltage     );

/** It calculates the real temperature ( T_DIE ) value.
  */
AMG8833_status_t  AMG8833_CalculateTemperature      ( AMG8833_data_t* myTemperature                                      );

/** It calculates the real sensor voltage ( V_SENSOR ) value.
  */
AMG8833_status_t  AMG8833_CalculateSensorVoltage    ( AMG8833_data_t* myV_sensor                                         );

/** It calculates the object temperature ( T_OBJ ) value.
  */
AMG8833_status_t  AMG8833_CalculateObjectTemperature( AMG8833_data_t* myObjTemperature                                   );



#ifdef __cplusplus
}
#endif

#endif /* AMG8833_H */
