/*
 * modulator.c
 *
 *  Created on: 18 maj 2023
 *      Author: student
 */
#include "modulator.h"

void PWM_Init(struct PWM *pwm){

    pwm->suma =0;

    pwm->A_out=0;
    pwm->B_out=0;
    pwm->C_out=0;

};
float Min(struct PWM *pwm){
  if(pwm->A <= pwm->B && pwm->A <= pwm->C){
      return pwm->A;
  }
  else if (pwm->B <= pwm->A && pwm->B <= pwm->C){
      return pwm->B;
  }else{
      return pwm->C;
  }
};

float Max(struct PWM *pwm){
  if(pwm->A >= pwm->B && pwm->A >=pwm->C){
      return pwm->A;
  }else if(pwm->B >= pwm-> A && pwm->B >= pwm->C){
      return pwm->B;
  }else{
      return pwm->C;
  }
};

void PWM_calc(struct PWM *pwm, float A,float B,float C){
  pwm->A = A;
  pwm->B = B;
  pwm->C = C;

  pwm->suma = (Max(pwm)+Min(pwm))*(-0.5);

  pwm->A_out=pwm->A+pwm->suma;
  pwm->B_out=pwm->B+pwm->suma;
  pwm->C_out=pwm->C+pwm->suma;
};
