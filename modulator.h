/*
 * modulator.h
 *
 *  Created on: 18 maj 2023
 *      Author: student
 */

#ifndef MODULATOR_H_
#define MODULATOR_H_
#include "DSP28x_Project.h"
#include "math.h"

struct PWM {

    float suma;

    float A;
    float B;
    float C;

    float A_out;
    float B_out;
    float C_out;
};
void PWM_Init(struct PWM *pwm);
float Min(struct PWM *pwm);
float Max(struct PWM *pwm);
void PWM_calc(struct PWM *pwm, float A,float B,float C);



#endif /* MODULATOR_H_ */
