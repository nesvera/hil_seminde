#ifndef __hil_lib_H
#define __hil_lib_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_cdc_if.h"

//(CONTROLE)
// Includes from the code genarated with matlab
#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "sistema.h"                   /* Model's header file */
#include "rtwtypes.h"

/* Sentece example:
	 $acelx;acely;acelz;gyrox;gyroy;gyroz;*
*/	 
#define NUM_FIELD_IN	 	16									// Number of data fields on the input message
#define NUM_FIELD_OUT 	4									// Number of data fields on the output message
	 
#define BUFSIZE 				1024
		
void HIL_Read( void );

#ifdef __cplusplus
}
#endif
#endif /*__hil_lib_H */
