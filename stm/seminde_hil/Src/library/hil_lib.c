#include "hil_lib.h"
#include "math.h"
#include "stm32f1xx_hal.h"

// Problemas.... entrada precisam ser menores que 64 caracters

// Declare private functions
void 		HIL_BreakString(void);
void 		HIL_Double2String( uint8_t *strOut );
void 		HIL_PidInit( void );
double 	HIL_PidController( double dValue, double mValue );
uint8_t HIL_CheckString( uint8_t *str );
char 		HIL_Int2Hex(unsigned n);

void rt_OneStep(void);


// Declare some variables
float dataFieldIn[ NUM_FIELD_IN ];										// Array dos campos de entrada e saida			
float dataFieldOut[ NUM_FIELD_OUT ];
	 
static 	uint8_t strHilIn[BUFFER_IN_SIZE];
uint8_t strHilOut[BUFFER_OUT_SIZE];
		
float campo[16];
int indexCampo = 0;

// Campo usado para receber e posteriormente converter para valor float, apenas serão alterados os bytes de 2 a 9
char tempCampoBytes[11] = {'0', 'x', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n'};        //"0xc6f3927d\n"

// Indice do byte dentro do campo atual - Cada campo tem 11 bytes sendo que 8 bytes sao do dado e os outros sao necessarios para representar um valor em hexadecimal
int indexTemp = 2;			

int pacoteValido = 0;

/**
*			Separa os dados pertencentes a string recebida
*			
*			Ex:
*				$c6f3927d;c3940595;c74ef5d6;00000000;b87c0bbe;00000000;387a9a7d;00000000;00000000;3effcc3e;3c0a2d11;416cb74d;0000REFX;0000REFY;0000REFZ;0000REFH;*
*			Campo 1: c6f3927d
*			Campo 2: c74ef5d6
*/
void HIL_BreakString(void){
	
	unsigned char atualCharString;
	int charCampoCont = 0;				// Indice do caracter dentro do campo a ser prenchido atualmente - Cada campo tem 4 caracteres (entre 0 e 255)
	
	indexCampo = 0;
	
	tempCampoBytes[0] = '0';
	tempCampoBytes[1] = 'x';
	tempCampoBytes[2] = '\n';
	tempCampoBytes[3] = '\n';
	tempCampoBytes[4] = '\n';
	tempCampoBytes[5] = '\n';
	tempCampoBytes[6] = '\n';
	tempCampoBytes[7] = '\n';
	tempCampoBytes[8] = '\n';
	tempCampoBytes[9] = '\n';
	tempCampoBytes[10] = '\n';
	
	indexTemp = 2;
	
	int i = 0;
  while(1){
		atualCharString = (char)strHilIn[i];

		if( i == 0 ){
			i++;
			continue;
			
		}else if( charCampoCont == 4 ){					// Troca de campo
			
			charCampoCont = 0;		// Reinicia o indice pro proximo campo 
      indexTemp = 2;				// Reinicia indice do campo tempCampoBytes
      i++;
	
			// Utiliza a string momtada (e.g "0xc6f3927d\n") e transforma de HEXADECIMAL para FLOAT salvando no campo de entrada float
      uint32_t num;
      sscanf(tempCampoBytes, "%x", &num);                   			// assuming you checked input
      dataFieldIn[indexCampo] = *((float*)&num);
			indexCampo += 1;
			
      continue;

		// Quando chegar ao final do string recebida 
		}
		
		if( i == DATA_IN_SIZE ) {							
			break;
		}

		// Transforma o CARACTER atual (e.g 255) em dois numeros HEXADECIMAL (e.g FF), salvando nas devidas posicoes da String HEXADECIMAL
    tempCampoBytes[indexTemp++] = HIL_Int2Hex(atualCharString / 0x10);
    tempCampoBytes[indexTemp++] = HIL_Int2Hex(atualCharString % 0x10);

    charCampoCont++;
    i++;
		
	}
}

/*	Retorna caracter referente ao valor inteiro 
*
*/
char HIL_Int2Hex(unsigned n)
{
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

/* Confere se a string esta fechada. 
* 	Primeiro character $
*		Ultimo character *
*
*/
uint8_t HIL_CheckString( uint8_t *str )
{
	// Como o pacote é fixo, apenas olhar o primeiro e ultimo byte
	if( str[0] == '$' && str[DATA_IN_SIZE-1] == '*' ){
		return 1;
	
	}
	
	return 0;
}


/**
*
*
*/
void HIL_Double2String( uint8_t *strOut ){ 
		uint8_t 	indParam = 0;
		uint8_t		strField[32];
		
    //"$12.52;15;1;123456.12;987.654321;*"
		//strcpy( (char *)strOut, "$");																													// Inicialize OUTPUT string
		strcat( (char *)strOut, "$");
	
		float a;
	
	
    while( indParam < NUM_FIELD_OUT ){																										// Add output data fields to the output string
    			
			a = dataFieldOut[indParam];
			
			memset( strField, '\0', sizeof((char *)strField) );																	// Clear auxiliary array
			snprintf( (char *)strField, sizeof(strField), "%.4lf;", dataFieldOut[indParam] );		// Double to string							//(VOLTAR)
			
			strcat( (char *)strOut, (char *)strField );																					// Append the value
			
			indParam++;
			a++;
    }

		strcat( (char *)strOut, "*\n");				// Finish OUTPUT string
				
		return;
}


void HIL_Calculate( uint8_t *strIn, uint8_t *strOut ){
	// Divide a string recebida nos campos da planta
	memset( strHilIn, '\0', sizeof(strHilIn) );
	memcpy( strHilIn, strIn, DATA_IN_SIZE );
	
	// Quebra a string recebida em campos referentes ao sistema
	HIL_BreakString();		
	
	
	int i;
	for( i=0 ; i<16 ; i++ ){
		printf("%.4f ", dataFieldIn[i]);
	}
	printf("\n");

	// (CONTROLE)
	// Valroes de entrada do controle recebem as entradas do HIL
	sistema_U.X_XPlane = dataFieldIn[0];
	sistema_U.Y_XPlane = dataFieldIn[1];
	sistema_U.Z_XPlane = dataFieldIn[2];
	sistema_U.Vx_XPlane = dataFieldIn[3];
	sistema_U.Vy_XPlane = dataFieldIn[4];
	sistema_U.Vz_XPlane = dataFieldIn[5];
	sistema_U.q_XPlane = dataFieldIn[6];
	sistema_U.p_XPlane = dataFieldIn[7];
	sistema_U.r_XPlane = dataFieldIn[8];
	sistema_U.pitch_XPlane = dataFieldIn[9];
	sistema_U.roll_XPlane = dataFieldIn[10];
	sistema_U.heading_XPlane = dataFieldIn[11];
	sistema_U.referencias[0] = dataFieldIn[12];		// z
	sistema_U.referencias[1] = dataFieldIn[13];		// x
	sistema_U.referencias[2] = dataFieldIn[14];		// y
	sistema_U.referencias[3] = dataFieldIn[15];		// yaw

	// Executa a malha de controle sobre os dados recebidos
	rt_OneStep();
		
	// Array de saida recebe resultados do controle
	dataFieldOut[0] = sistema_Y.t1;
	dataFieldOut[1] = sistema_Y.t2;
	dataFieldOut[2] = sistema_Y.t3;
	dataFieldOut[3] = sistema_Y.t4;

	//printf("%.4f %.4f %.4f %.4f \n", sistema_Y.t1, sistema_Y.t2, sistema_Y.t3, sistema_Y.t4 );
	
	memset(strOut, '\0', sizeof(strOut));
	HIL_Double2String( strOut );
	
}

/*
*

void HIL_Read( void )
{
	static uint32_t buffsize;
			
	// Check if there is data available on RX buffer
	if( bufLengOut != bufLengIn ){
		
		if( bufLengOut > bufLengIn ){
			buffsize = bufLengIn;
		
		}else{
			buffsize = bufLengIn - bufLengOut;
		
		}
		
		if( buffsize > 2 ){			
			// Clear the auxiliar IN buffer and copy on this the data that arrived	
			memset( strHilIn, '\0', sizeof(strHilIn) );
			memcpy( strHilIn, (UserTxBufferFS + bufLengOut), buffsize );
			memset( UserTxBufferFS, '\0', sizeof(UserTxBufferFS));

			// Chech if the arrived data is like you expect
			if( HIL_CheckString( strHilIn ) ){
				HIL_BreakString( strHilIn );												// Break the CSV string					(ALTERAR) usar ponteiros			
				
				//obs: os campos de dataFieldIn serão alterados corretamente quando uma frase completa chegar, senão os valores anteriores serão mantidos para os campos que não chegaram
				
				if( pacoteValido == 2 ){
					
					// Apos todos valores do xplane chegarem, o controle e executado
					
					// (CONTROLE)
					// Valroes de entrada do controle recebem as entradas do HIL
					sistema_U.X_XPlane = dataFieldIn[0];
					sistema_U.Y_XPlane = dataFieldIn[1];
					sistema_U.Z_XPlane = dataFieldIn[2];
					sistema_U.Vx_XPlane = dataFieldIn[3];
					sistema_U.Vy_XPlane = dataFieldIn[4];
					sistema_U.Vz_XPlane = dataFieldIn[5];
					sistema_U.q_XPlane = dataFieldIn[6];
					sistema_U.p_XPlane = dataFieldIn[7];
					sistema_U.r_XPlane = dataFieldIn[8];
					sistema_U.pitch_XPlane = dataFieldIn[9];
					sistema_U.roll_XPlane = dataFieldIn[10];
					sistema_U.heading_XPlane = dataFieldIn[11];
					sistema_U.referencias[0] = dataFieldIn[12];
					sistema_U.referencias[1] = dataFieldIn[13];
					sistema_U.referencias[2] = dataFieldIn[14];
					sistema_U.referencias[3] = dataFieldIn[15];			
									
					//HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_9 );
					
					//HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, SET );				// Liga o led antes do calculo 

					// chama controle
					rt_OneStep();

					//HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, RESET );			// Desliga apos o calculo

					// Array de saida recebe resultados do controle
					dataFieldOut[0] = sistema_Y.t1;
					dataFieldOut[1] = sistema_Y.t2;
					dataFieldOut[2] = sistema_Y.t3;
					dataFieldOut[3] = sistema_Y.t4;
									
					// pack output from control in a string
					memset(strHilOut, '\0', sizeof(strHilOut));
					HIL_Double2String( strHilOut );
									
					// Send message to PC
					CDC_Transmit_FS( (uint8_t*)strHilOut, strlen( (char *)strHilOut) );	
						
					pacoteValido = 0;
				}			
			}
		}
		
		bufLengOut += buffsize;	
	}
}
*/


//(CONTROLE)
// Code form ert_main generated from matlab
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(sistema_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  sistema_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
