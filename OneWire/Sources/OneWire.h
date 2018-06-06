/*
 * OneWire.h
 *
 *  Created on: May 16, 2017
 *      Author: Franco
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include "derivative.h" /* include peripheral declarations */

unsigned int availableFlag=0;

extern void oneWire_reset(void);
extern void oneWire_write(char Dato);
extern void oneWire_read(void);
extern void oneWire_setIOWire(char configuration);
extern void oneWire_delayUs(unsigned int timeoutReceived);
extern void oneWire_setLOW(void);
extern void oneWire_setHIGH(void);
extern void delay(unsigned int a);




#endif /* ONEWIRE_H_ */
