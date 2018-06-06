#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>
#include <stdlib.h>

#define INICIO 0
#define JUEGO 1
#define PULSADOR1 PTAD_PTAD0
#define PULSADOR2 PTAD_PTAD1
#define resetButton PTAD_PTAD2
#define shotButton PTAD_PTAD3
#define MPLEX1 PTCD_PTCD3
#define MPLEX2 PTCD_PTCD2
#define MPLEX3 PTBD_PTBD7

#define data PTBD_PTBD0
#define data_clock PTBD_PTBD1


#define JUG1 0
#define JUG2 1

#define PRESIONADO 0

void reset(void);
char shotDado(void);
void MCU_init(void);
void GPIO_init(void);
void move_action(void);
void displayPlayer(void);
void delay(unsigned int delay);
void setPosition(char J1, char J2);

static char PRET1[9]={0,1,1,0,0,0,0,0}; // JUGADOR 1
static char PRET2[9]={1,1,0,1,1,0,1,0}; // JUGADOR 2
static char PRET3[9]={0,0,0,0,0,0,1,0}; // ESPERA NUMERO
static char 	J[9]={0,1,1,1,0,0,0,0};

char fase=0;
unsigned int rebote=0;



typedef struct REGISTER{
			unsigned char current_PLAYER	   :1;
			unsigned char just_begin   		   :1;
			unsigned char count_end    		   :1;
			unsigned char large_rope   	 	   :1;
			unsigned char data_enabled 	       :1;
			unsigned char aux_needed   		   :1;
			unsigned char vertical_position	   :1;
			unsigned char mode   	   	  	   :1;  
			}registro;
	   
	registro registros; 
	
void main(void) {
		
	MCU_init();
	GPIO_init();  

  for(;;) 
  {
	  if (resetButton==PRESIONADO) reset();
	  
	  switch (fase)
	  {
		  case INICIO:
			  
			  if (PULSADOR1==PRESIONADO && PULSADOR2==PRESIONADO)
			  {		  
				  delay(30); // 30 mS
				  while (PULSADOR1==PRESIONADO && PULSADOR2==PRESIONADO);
			  }
			  
			  fase=JUEGO;
			  registros.just_begin=1;
			  break;
			  
		  case JUEGO:
			  if (registros.just_begin)
			  {
				  registros.current_PLAYER=JUG1;
			  	  setPosition(0,0);
				  registros.just_begin=0;
			  }
			  displayPlayer();
			  
			  if (shotButton==PRESIONADO){ 
				  move_action();			  	   
			  }
			  			  
			  break;
			  
		  
		  
	  
	  
	  }
	  
    
  } 
  
  
}


void move_action()
{	
	registros.current_PLAYER=~registros.current_PLAYER;
	shotDado(); 
	
}

char shotDado()
{	
	char numero = rand() % 11 + 1;
	return numero;
}

void delay(unsigned int delay)
{	
	while (delay==0)
	{
	 TPM2SC=0b00001011; //1uS
	 TPM2MOD=999;
	 if (TPM2SC_TOF==1)delay--;
	} 
	 TPM2SC=0; //1uS
	
		 
}

void GPIO_init()
{
	/* 
	 	 	 |------|
	 	 	 |		| PATA0 PULSADOR JG1
	 	 	 |		| PATA1 PULSADOR JG2
	 	 	 |		| PATA2 PULSADOR RESET
	  	  	 |		| PATA3 PULSADOR DADO
	  	  	 |		| PATA4 DISPLAY 	
	 	 	 |		| PATA5 DISPLAY
	  	  	 |		| 
	 	 	 |		| 
MPLEX3	 	 |		| PATA8 LEDJG1
MPLEX2	  	 |		| PATA9 LEDJG1
MPLEX1	 	 |		|	  	  	 
	  	  	 --------
	 
	 */
	
	
}

void MCU_init()
{
	EnableInterrupts;
	SOPT1 &= 0x3F;
	
}

void reset()
{
	fase=INICIO;
	setPosition(0,0);
	
}

void setPosition(char J1, char J2)
{
	
}

void displayWrite(char num)
{	
	char n=0;
	
	for (n=1;n!=4;n++)
	{
		if (n==1) // J
		{
			for (n=8;n>=0;n--)
			{
				data=J[n];
				data_clock=1;
				data_clock=0;
			}
			MPLEX1=1;
			delay(20);
		}
		
		if (n==2)
		{
			if (registros.current_PLAYER==JUG1)
			{		
				for (n=8;n>=0;n--)
				{
					data=PRET1[n];
					data_clock=1;
					data_clock=0;
				}
				MPLEX2=1;
				delay(20);	
			}
		
			if (registros.current_PLAYER==JUG2)
			{		
				for (n=8;n>=0;n--)
				{
					data=PRET2[n];
					data_clock=1;
					data_clock=0;
				}
				MPLEX2=1;
				delay(20);	
			}			
		}
	
	}
}

void displayPlayer()
{
	;
}
