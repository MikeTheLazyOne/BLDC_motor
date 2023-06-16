/*
 * PI.c
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */


#include "PI.h"
#include "math.h"
// Inicialization--------------------------

void  PROPORTION_STRUCT_InIt(struct  PROPORTION_STRUCT *prop,float Kp){

    prop->Y=0;
    prop->Kp=Kp;

}

void INTEGRAL_STRUCT_InIt(struct INTEGRAL_STRUCT *inte,float Ts,float Ki){

    inte->Ts = Ts;
    inte->Ki = Ki;
    inte->Y = 0;
    inte->Y_prev = 0;
    inte->U = 0;
    inte->U_prev = 0;

}

void PI_STRUCT_InIt(struct PI_STRUCT *pi,struct  PROPORTION_STRUCT *prop,float Max,float Min,float Gain){

    pi->Ka = 1/prop->Kp;
    pi->U = 0;
    pi->Y = 0;
    pi->Prop_wynik = 0;
    pi->Inte_wynik = 0;
    pi->Po_Ka = 0;
    pi->Suma = 0;
    pi->Max = Max;
    pi->Min = Min;
    pi->Gain = Gain;

}

//------------------Calculation---------------------------------------------

void UCHYB_calc(struct UCHYB_STRUCT *uch,float U,float Uref){

    uch->U = U;
    uch->Uref = Uref;
    uch->Y = uch->U - uch->Uref;

}

void Proportion_calc(struct PROPORTION_STRUCT *prop,float uch){

    prop->Y = uch*prop->Kp;

}

void    Integral_calc(struct INTEGRAL_STRUCT *inte,float uch,struct PI_STRUCT *pi){

    inte->U = uch - pi->Po_Ka;
    inte->Y = (( inte->U * inte->Ts * inte->Ki) / 2) + (( inte->U_prev * inte->Ts * inte->Ki) / 2) + inte->Y_prev;
    inte->U_prev = inte->U;
    inte->Y_prev = inte->Y;

}

void PI_calc(struct PI_STRUCT *pi,struct PROPORTION_STRUCT *prop,struct INTEGRAL_STRUCT *inte){


    pi->Prop_wynik = prop->Y;
    pi->Inte_wynik = inte->Y;
    pi->Suma = pi->Prop_wynik + pi->Inte_wynik;

    //anti-windup
    if(pi->Suma >= pi->Max){
    pi->Y = pi->Max;
    }
    else if(pi->Suma <= pi->Min){
    pi->Y = pi->Min;
    }
    else{
    pi->Y = pi->Suma;
    };




    pi->Po_Ka = (pi->Suma - pi->Y) * pi->Ka;

        //Gain in row
    pi->Y=pi->Y * pi->Gain;
}

