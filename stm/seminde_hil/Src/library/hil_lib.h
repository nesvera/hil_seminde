#ifndef __hil_lib_H
#define __hil_lib_H
#ifdef __cplusplus
 extern "C" {
#endif

//(CONTROLE)
// Includes from the code genarated with matlab
#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "sistema.h"                   /* Model's header file */
#include "rtwtypes.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
	 
/* Input sentence example:
		$c6f3927d;c3940595;c74ef5d6;00000000;b87c0bbe;00000000;387a9a7d;00000000;00000000;3effcc3e;3c0a2d11;416cb74d;0000REFX;0000REFY;0000REFZ;0000REFH;*
*/
	 
/* Output sentece example:
		$acelx;acely;acelz;gyrox;gyroy;gyroz;*
*/	 
	 
#define NUM_FIELD_IN	 	16									// Number of data fields on the input message
#define NUM_FIELD_OUT 	4									// Number of data fields on the output message
	 
#define BUFSIZE 				146

#define DATA_IN_SIZE 					82

#define BUFFER_IN_SIZE 				256
#define BUFFER_OUT_SIZE 			256

void HIL_Read( void );
uint8_t HIL_CheckString( uint8_t *str );
void HIL_Calculate( uint8_t *strHilIn, uint8_t *strOut );

#ifdef __cplusplus
}
#endif
#endif /*__hil_lib_H */
