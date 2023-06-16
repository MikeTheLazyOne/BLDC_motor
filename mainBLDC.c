


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "funkcje.h"
#include "stale.h"
#define __BSD_VISIBLE
#include "math.h"
#include "modulator.h"
#include "transABC.h"
#include "PI.h"

// Prototype statements for functions found within this file.
__interrupt void adc_isr(void);

int praca = 0;  //0-STOP NAPED; 1-ZEZWOLENIE NA PRACE


int run =0;
int skip =0;
int skipVal = 10;
int i = 0;

float d1=0;
float d2=0;
float d3=0;

float iB=0.0;
float iC=0.0;
float iA=0.0;

float inA=0.0;
float inB=0.0;
float inC=0.0;
float alpha=0.0;
float amplituda = 0.2;
float offset = 2.22350526;

float PhiMech=0.0;

float D = 0.0;
float Q = 0.5;

float DzABC;
float QzABC;

float Ts = 10e-4;
float T = 2*10e-2;

float kont = 0;
float kontprev = 0;
float deltakont =0;
float prendkosc = 0;
float prendkoscprev = 0;
float prendkoscpo = 0;
float prendkoscpoprev = 0;
float prendkoscwlasciwa = 0;
float uchybD,uchybQ,uchybW;
float W = 4;

unsigned long long int AdcIntCounter=0;

//modulator

struct PWM pwm1;

//do trasformacji

struct TRANS_AB ab1;
struct TRANS_ABC abc1;
struct TRANS_DQ dq1;
struct TRANS_DQ_AB dqab1;

//PI

struct PROPORTION_STRUCT propD,propQ,propW;
struct INTEGRAL_STRUCT inteD,inteQ,inteW;
struct PI_STRUCT piD,piQ,piW;

int zero =0;

//graphy
float graphD [200];
float graphQ [200];
float graphW [200];
float nastawy = 0.0065;


void main(void){
   // Step 1. Initialize System Control:
   InitSysCtrl();
   // Step 2. Initialize GPIO:
   InitPWMGpio();
   EPwm_Control123(0);
   InitEncGpio();

   // Step 3. Clear all interrupts and initialize PIE vector table:
   // Disable CPU interrupts
   DINT;

   // Initialize the PIE control registers to their default state.
   InitPieCtrl();

   // Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

   // Initialize the PIE vector table with pointers to the shell Interrupt
   // Service Routines (ISR).
   InitPieVectTable();

   // Interrupts that are used in this example are re-mapped to
   EALLOW;  // This is needed to write to EALLOW protected register
   PieVectTable.ADCINT1 = &adc_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

   // Step 4. Initialize all the Device Peripherals:
   InitAdc();  // For this example, init the ADC
   AdcOffsetSelfCal();

   // Step 5. User specific code, enable interrupts:
   PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // Enable INT 1.1 in the PIE
   IER |= M_INT1;                       // Enable CPU Interrupt 1
   EINT;                                // Enable Global interrupt INTM
   ERTM;                                // Enable Global realtime interrupt DBGM

   InitADCConv();
   InitPWM();
   // Wait for ADC interrupt


   //inicialization of PWM
   PWM_Init(&pwm1);

   //inicjalizacja PID
   PROPORTION_STRUCT_InIt(&propD,2);
   INTEGRAL_STRUCT_InIt(&inteD,Ts,nastawy);
   PI_STRUCT_InIt(&piD,&propD,35,-35,1);

   //PIQ
   PROPORTION_STRUCT_InIt(&propQ,2);
   INTEGRAL_STRUCT_InIt(&inteQ,Ts,nastawy);
   PI_STRUCT_InIt(&piQ,&propQ,35,-35,1);

   //PIW
   PROPORTION_STRUCT_InIt(&propW,0.0061905);
   INTEGRAL_STRUCT_InIt(&inteW,Ts,1);
   PI_STRUCT_InIt(&piW,&propW,1.7,-1.7,1);


   while(1){
	   __asm(" NOP");
   }

}

__interrupt void  adc_isr(void)
{
	EPwm_Control123(praca);

	iB = AdcResult.ADCRESULT0 * (-0.008684) + 23.706664;
	iC = AdcResult.ADCRESULT9 * (-0.00865)  + 23.479994;
	PhiMech = M_PI*2*(float)EncPos()/8192.0-offset;
	//sum of currents
	iA = -iB-iC;

	//offset of Phi
	if(PhiMech>2*M_PI){
	    PhiMech-=2*M_PI;
	}
	if(PhiMech<0){
	    PhiMech+=2*M_PI;
	}


	//Zabezpieczenie nadpradowe

	if(praca){
		if((fabs(iB)>3.0) || (fabs(iC)>3.0)){
			praca=0;
			EPwm_Control123(praca);
	    }
	}



	alpha = alpha + 10*2*M_PI*1e-4;

	    if(alpha>2*M_PI){
	        alpha-=2*M_PI;
	    }
	//transformacje abc z DQ

	    //Z ABC na DQ
	    //TRANS_CALC(struct TRANS *przek, float a,float b,float c)
	TRANS_CALC(&ab1,iA,iB,iC);


	//DQ_CALC(struct TRANS *ab,struct TRANS_DQ *dq,float ang)
	DQ_CALC(&ab1,&dq1,PhiMech*4);
	DzABC = dq1.tab[0];
	QzABC = dq1.tab[1];


	//Uchyb do pr¹dów
	uchybD = D - DzABC;
	uchybQ = piW.Y - QzABC;


	//regulator PI
	Proportion_calc(&propD, uchybD);
	Integral_calc(&inteD, uchybD, &piD);
	PI_calc(&piD, &propD, &inteD);

	Proportion_calc(&propQ, uchybQ);
	Integral_calc(&inteQ, uchybQ, &piQ);
	PI_calc(&piQ, &propQ, &inteQ);



	// transformacje na ABC
	DQ_AB_CALC(&dqab1, piD.Y, piQ.Y, PhiMech*4);
	ABC_calc2(&abc1,&dqab1);



	/*
	inA = sin(alpha)*amplituda;
	inB = sin(alpha+(2.0/3.0)*M_PI)*amplituda;
	inC = sin(alpha+(4.0/3.0)*M_PI)*amplituda;

	*/
	PWM_calc(&pwm1,abc1.tab[0],abc1.tab[1],abc1.tab[2]);



	d1 = pwm1.A_out*0.4;
	d2 = pwm1.B_out*0.4;
	d3 = pwm1.C_out*0.4;

	//konty aby ne by³o pily
	deltakont = (PhiMech - kontprev);
	kontprev = PhiMech;

	if (deltakont < -M_PI){
	    deltakont = deltakont + (2 * M_PI);
	}
	if(deltakont >  M_PI){
	    deltakont = deltakont -(2*M_PI);
	}
	prendkosc = deltakont*10000;


	//filtr dolnoprzepustowy

	prendkoscpo = prendkosc*(Ts/(2*T+Ts))+(prendkoscprev*(Ts/(2*T+Ts)))+prendkoscpoprev*((2*T-Ts)/(2*T+Ts));

	prendkoscprev = prendkosc;
	prendkoscpoprev = prendkoscpo;
	prendkoscwlasciwa = prendkoscpo *0.25;


	if (d1>1){
	    d1=1;
	}else if(d1<-1){
	    d1=-1;
	}

	if (d2>1){
	        d2=1;
	    }else if(d2<-1){
	        d2=-1;
	    }
	if (d3>1){
	        d3=1;
	    }else if(d3<-1){
	        d3=-1;
	    }

	uchybW = W - prendkoscwlasciwa;


	//regulator PIW
	Proportion_calc(&propW, uchybW);
	Integral_calc(&inteW, uchybW, &piW);
	PI_calc(&piW, &propW, &inteW);

	//graph
	if(run == 1){
	    if(skip == 0){
	    graphD[i] = DzABC;
	    graphQ[i] = QzABC;
	    graphW[i] = piW.Y;
	    i++;
	    if(i>199){

	        i=0;
	        run =0;

	        }
	    skip=skipVal;
	    }
	    skip--;


	}
	if(praca == 0){

	    inteD.U_prev = 0;
	    inteD.Y_prev = 0;

	    inteQ.U_prev = 0;
	    inteQ.Y_prev = 0;

	    inteQ.U_prev = 0;
	    inteQ.Y_prev = 0;

	}
/*
	if (zero == 1){
	    inteD.Y_prev = 0;
	    inteQ.Y_prev = 0;
	    zero = 0;
	}
*/

	EPwm1Regs.CMPA.half.CMPA = d1 * (TB_PRD/2) + (TB_PRD/2);
	EPwm2Regs.CMPA.half.CMPA = d2 * (TB_PRD/2) + (TB_PRD/2);
	EPwm3Regs.CMPA.half.CMPA = d3 * (TB_PRD/2) + (TB_PRD/2);


	AdcIntCounter++;

	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //Clear ADCINT1 flag reinitialize for next SOC
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

