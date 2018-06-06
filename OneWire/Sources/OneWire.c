/*
 * oneWire.c
 *
 *  Created on: May 16, 2017
 *      Author: Franco
 */

#include "OneWire.h"

#define INPUT 0
#define OUTPUT 1
#define wirePin PTXD_PTXD
#define _wirePin PTXDD_PTXDX



void oneWire_reset(void)
{
    unsigned char presence_detect = 0;
        
    oneWire_setLOW();                 // Drive the bus low
        
    delay(480);
    
    oneWire_setHIGH ();                  // Release the bus
        
    delayReset(70);
    
    presence_detect = oneWire_read();    //Sample for presence pulse from slave
   
    delayReset(410);
    
    
    return presence_detect;   
}

void oneWire_write(char Dato)
{
   switch(Dato){
   	   case High:
   		   wirePin=1;
   		   delay(8);
   		   wirePin=0;
   	   case Low:
   		   wirePin=1;
   		   delay(60);
   		   
   }
}

void oneWire_read(void)
{
    setIOWire(INPUT);
    oneWire_delayUs(2);
    while(!avalailableFlag);
    return wirePin;    
    setIOWire(OUTPUT);
}
void oneWire_setIOWire(char configuration)
{
    switch (configuration)
    {
        case INPUT:
            _wirePin=0;
            break;
        case OUTPUT:
            _wirePin=1;
            break;
            
        default:
            _wirePin=0;
            break;            
    }
}
void oneWire_delayUs(unsigned int timeoutReceived)
 {
    TPM2SC= 0b0101011;//Enable TPM1 1uS
    TPM2MOD=timeoutReceived; // 
 }

__interrupt 14 setFlag(void)
{
    TPM2SC_TOF=0;
   // TPM2=0;    
   // availableFlag=1;
    availableFlag=1;
}

void oneWire_setLOW(void)
{    
    wirePin=0;
}

void oneWire_setHIGH(void)
{
    wirePin=1;
}
void delay(unsigned int a)
{
    oneWire_delayUs(a);    
    while(!availableFlag);
    availableFlag=0;
    TPM2SC=0;
}
