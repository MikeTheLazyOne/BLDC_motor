/*
 * funkcje.h
 *
 *  Created on: 05.04.2018
 *      Author: tomek
 */

#ifndef FUNKCJE_H_
#define FUNKCJE_H_


void InitADCConv(void);

void InitPWMGpio(void);
void InitPWM(void);

void InitEncGpio(void);
long EncPos(void);

void EPwm_Control123(int mode);


#endif /* FUNKCJE_H_ */
