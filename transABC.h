/*
 * transABC.h
 *
 *  Created on: 22 maj 2023
 *      Author: student
 */

#ifndef TRANSABC_H_
#define TRANSABC_H_

#include "DSP28x_Project.h"
#include "math.h"

#define onethird (1.0/3.0)
#define onesqrt (1.0/sqrt(3.0))
#define twothird (2.0/3.0)
#define onetwo (1.0/2.0)
#define twotwo (sqrt(3)/2.0)

// z ABC na ab
struct TRANS_AB{
    float tab[2];
};
struct TRANS_ABC{
    float tab[3];
};
struct TRANS_DQ{
    float tab[2];
};
struct TRANS_DQ_AB{
    float tab[2];

};
void TRANS_CALC(struct TRANS_AB *przek, float a,float b,float c);
//Z AB na DQ
void DQ_CALC(struct TRANS_AB *ab,struct TRANS_DQ *dq,float ang);

//Z AB na ABC
void ABC_calc(struct TRANS_ABC *abc,struct TRANS_AB *ab);
//Z AB na ABC  druga wersja na inn¹ strukture
void ABC_calc2(struct TRANS_ABC *abc,struct  TRANS_DQ_AB *ab);

// z DQ na AB
void DQ_AB_CALC(struct TRANS_DQ_AB *ab,float D,float Q,float ang);



#endif /* TRANSABC_H_ */

