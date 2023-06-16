/*
 * PI.h
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */

#ifndef PI_H_
#define PI_H_

#include "DSP28x_Project.h"
#include "math.h"

struct UCHYB_STRUCT{

    float U;
    float Uref;
    float Y;

};

struct PROPORTION_STRUCT{

    float Y;
    float Kp;

};

struct INTEGRAL_STRUCT{

    float U;
    float U_prev;
    float Y;
    float Y_prev;
    float Ki;
    float Ts;

};

struct PI_STRUCT{

    float U;
    float Y;
    float Prop_wynik;
    float Inte_wynik;
    float Suma;
    float Ka;
    float Po_Ka;
    float Max;
    float Min;
    float Gain;

};
// Inicialization--------------------------

void  PROPORTION_STRUCT_InIt(struct  PROPORTION_STRUCT *prop,float Kp);

void INTEGRAL_STRUCT_InIt(struct INTEGRAL_STRUCT *inte, float Ts, float Ki);

void PI_STRUCT_InIt(struct PI_STRUCT *pi,struct  PROPORTION_STRUCT *prop,float Max,float Min,float Gain);

//------------------Calculation---------------------------------------------

void UCHYB_calc(struct UCHYB_STRUCT *uch,float U,float Uref);

void Proportion_calc(struct PROPORTION_STRUCT *prop,float uch);

void Integral_calc(struct INTEGRAL_STRUCT *inte,float uch,struct PI_STRUCT *pi);

void PI_calc(struct PI_STRUCT *pi,struct PROPORTION_STRUCT *prop,struct INTEGRAL_STRUCT *inte);

#endif /* PI_H_ */
