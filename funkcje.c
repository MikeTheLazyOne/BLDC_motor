/*
 * funkcje.c
 *
 *  Created on: 05.04.2018
 *      Author: tomek
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "funkcje.h"
#include "stale.h"

void InitADCConv(void){

    // Configure ADC
    EALLOW;
        AdcRegs.ADCCTL2.bit.CLKDIV4EN = 1;
        AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;  // Enable non-overlap mode
        AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    // ADCINT1 trips after AdcResults latch
        AdcRegs.INTSEL1N2.bit.INT1E     = 1;    // Enabled ADCINT1
        AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;    // Disable ADCINT1 Continuous mode
        AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;    // setup EOC1 to trigger ADCINT1 to fire

        AdcRegs.ADCSOC0CTL.bit.CHSEL=0x0;
        AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
        AdcRegs.ADCSOC1CTL.bit.CHSEL=0x1;
        AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
        AdcRegs.ADCSOC2CTL.bit.CHSEL=0x2;
        AdcRegs.ADCSOC3CTL.bit.CHSEL=0x3;
        AdcRegs.ADCSOC4CTL.bit.CHSEL=0x4;
        AdcRegs.ADCSOC5CTL.bit.CHSEL=0x5;
        AdcRegs.ADCSOC6CTL.bit.CHSEL=0x6;
        AdcRegs.ADCSOC7CTL.bit.CHSEL=0x7;
        AdcRegs.ADCSOC8CTL.bit.CHSEL=0x8;
        AdcRegs.ADCSOC9CTL.bit.CHSEL=0x9;
        AdcRegs.ADCSOC9CTL.bit.TRIGSEL = 5;
        AdcRegs.ADCSOC10CTL.bit.CHSEL=0xA;
        AdcRegs.ADCSOC11CTL.bit.CHSEL=0xB;
        AdcRegs.ADCSOC12CTL.bit.CHSEL=0xC;
        AdcRegs.ADCSOC13CTL.bit.CHSEL=0xD;
        AdcRegs.ADCSOC14CTL.bit.CHSEL=0xE;
        AdcRegs.ADCSOC15CTL.bit.CHSEL=0xF;

        AdcRegs.ADCSOC0CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC1CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC2CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC3CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC4CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC5CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC6CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC7CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC8CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC9CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC10CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC11CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC12CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC13CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC14CTL.bit.ACQPS=22;
        AdcRegs.ADCSOC15CTL.bit.ACQPS=22;

    EDIS;
}

void InitPWM(void){

    //EPWM Module 1 config
    EPwm1Regs.TBPRD = TB_PRD;
    EPwm1Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM1A
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    EPwm1Regs.DBFED = 25; // FED = 50 TBCLKs
    EPwm1Regs.DBRED = 25; // RED = 50 TBCLKs

    // EPWM Module 2 config
    EPwm2Regs.TBPRD = TB_PRD;
    EPwm2Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; // Slave module
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM2A
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    EPwm2Regs.DBFED = 25; // FED = 50 TBCLKs
    EPwm2Regs.DBRED = 25; // RED = 50 TBCLKs

    // EPWM Module 3 config
    EPwm3Regs.TBPRD = TB_PRD;
    EPwm3Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; // Slave module
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM3A
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    EPwm3Regs.DBFED = 25; // FED = 50 TBCLKs
    EPwm3Regs.DBRED = 25; // RED = 50 TBCLKs

    /* Set up Event Trigger with period enable for Time-base of EPWM1 */
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;    /* Enable period event for SOCA */
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */
    EPwm1Regs.ETCLR.bit.SOCA = 1;

    EALLOW;
            EPwm1Regs.TZCTL.all = 0x000A;
            EPwm2Regs.TZCTL.all = 0x000A;
            EPwm3Regs.TZCTL.all = 0x000A;
    EDIS;

}

void InitPWMGpio(void){
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM9B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO4 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO5 as EPWM5B

    EDIS;
}

void EPwm_Control123(int mode)
{
    switch (mode) {
        case 0: {
        EALLOW;
            EPwm1Regs.TZFRC.bit.OST = 1;
            EPwm2Regs.TZFRC.bit.OST = 1;
            EPwm3Regs.TZFRC.bit.OST = 1;
        EDIS;
        } break;
        case 1: {
        EALLOW;
            EPwm1Regs.TZCLR.bit.OST = 1;
            EPwm2Regs.TZCLR.bit.OST = 1;
            EPwm3Regs.TZCLR.bit.OST = 1;
        EDIS;
        } break;
    }
}

void InitEncGpio(void){

    EALLOW;
       GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
       GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
       GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;
       GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;
       GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;
       GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;
       GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
       GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
       GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;
       GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
       GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;     // DATA-RX
       GpioCtrlRegs.GPBQSEL1.bit.GPIO42 = 1;
       GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;
   EDIS;
}

long EncPos(void){

    long EncoderData2=0;
    int i=0;
    int Command_Mode = 224;

    CLK_ENABLE;
    DATA_TX_ENABLE;
    DATA_TX_LOW;

    for (i=0;i<10;i++) {
              CLK_LOW;
              if (Command_Mode & 1<<i) DATA_TX_HIGH;
              else DATA_TX_LOW;
              asm(" RPT #50|| NOP");
              CLK_HIGH;
              asm(" RPT #50|| NOP");
    }
    DATA_TX_DISABLE;
    DATA_RX_ENABLE;

    asm(" RPT #1000 || NOP");
          //asm(" RPT #1000 || NOP");


    for (i=-5;i<13;i++) {
              CLK_LOW;
              if (i>=0) EncoderData2 |= (long)DATA_RX << (i);
              asm(" RPT #3|| NOP");
              CLK_HIGH;
              asm(" RPT #3 || NOP");
    }

    DATA_RX_DISABLE;
    CLK_DISABLE;

    return EncoderData2;

}
