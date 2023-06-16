/*
 * transABC.c
 *
 *  Created on: 29 maj 2023
 *      Author: student
 */


/*
 * transABC.c
 *
 *  Created on: 22 maj 2023
 *      Author: student
 */
#include "transABC.h"
#include "math.h"
// z ABC na AB
void TRANS_CALC(struct TRANS_AB *przek, float a,float b,float c){

    przek->tab[0] = twothird*a-onethird*(b+c);
    przek->tab[1] = onesqrt*(b-c);
};
//Z AB na DQ
void DQ_CALC(struct TRANS_AB *ab,struct TRANS_DQ *dq,float ang){
    dq->tab[0]=ab->tab[0]*cos(ang)+ab->tab[1]*sin(ang);
    dq->tab[1] = -ab->tab[0]*sin(ang)+ab->tab[1]*cos(ang);
};

//Z AB na ABC
void ABC_calc(struct TRANS_ABC *abc,struct TRANS_AB *ab){
    abc->tab[0]=ab->tab[0];
    abc->tab[1]=-onetwo*ab->tab[0]+twotwo*ab->tab[1];
    abc->tab[2]=-onetwo*ab->tab[0]-twotwo*ab->tab[1];
};
//Z AB na ABC  druga wersja na inn¹ strukture
void ABC_calc2(struct TRANS_ABC *abc,struct  TRANS_DQ_AB *ab){
    abc->tab[0]= ab->tab[0];
    abc->tab[1]=-onetwo*ab->tab[0]+twotwo*ab->tab[1];
    abc->tab[2]=-onetwo*ab->tab[0]-twotwo*ab->tab[1];
};

// z DQ na AB
void DQ_AB_CALC(struct TRANS_DQ_AB *ab,float D,float Q,float ang){

    ab->tab[0] = D*cos(ang)-Q*sin(ang);
    ab->tab[1] = D*sin(ang)+Q*cos(ang);

};
