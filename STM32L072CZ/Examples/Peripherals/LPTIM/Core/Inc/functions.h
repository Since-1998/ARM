/**
 * @brief       functions.h
 * @details     Functions' header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/October/2019
 * @version     03/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "board.h"


/**@brief Functions prototypes.
 */
void Conf_CLK 	( void 			 );
void Conf_GPIO 	( void 			 );
void Conf_LPTIM ( uint32_t myCLK );


#endif /* FUNCTIONS_H_ */
