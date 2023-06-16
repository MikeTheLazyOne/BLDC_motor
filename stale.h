/*
 * stale.h
 *
 *  Created on: 05.04.2018
 *      Author: tomek
 */

#ifndef STALE_H_
#define STALE_H_

#define SYSCLK_FREQUENCY_HZ (90e6)
#define PWM_BASE_FREQ   (10e3)
#define TB_PRD (SYSCLK_FREQUENCY_HZ/(2*PWM_BASE_FREQ))


#define CLK_ENABLE GpioDataRegs.GPBSET.bit.GPIO40 = 1
#define CLK_DISABLE GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1
#define CLK_HIGH GpioDataRegs.GPBSET.bit.GPIO41 = 1
#define CLK_LOW GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1
#define DATA_RX_ENABLE GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1
#define DATA_RX_DISABLE GpioDataRegs.GPBSET.bit.GPIO43 = 1
#define DATA_RX GpioDataRegs.GPBDAT.bit.GPIO42
#define DATA_TX_ENABLE GpioDataRegs.GPASET.bit.GPIO11 = 1
#define DATA_TX_DISABLE GpioDataRegs.GPACLEAR.bit.GPIO11 = 1
#define DATA_TX_HIGH GpioDataRegs.GPASET.bit.GPIO10 = 1
#define DATA_TX_LOW GpioDataRegs.GPACLEAR.bit.GPIO10 = 1

#define  PI_2 1.5707963267949
#define  PI  3.14159265358979
#define  PI2  6.28318530717958


#define RS      2.55                  // Stator resistance (ohm)
#define LS      0.01                  // Stator inductance (H)
#define POLES   8                     // Number of poles
#define POLES_PAIRS   4                // Number of poles pairs

// Define the base quantites
#define BASE_VOLTAGE    258.8        // Base peak phase voltage (volt)
#define BASE_CURRENT    2.4            // Base peak phase current (amp)
#define BASE_TORQUE                    // Base torque (N.m)
#define BASE_FLUX                      // Base flux linkage (volt.sec/rad)
#define BASE_FREQ       400            // Base electrical frequency (Hz)
#define BASE_W        628            // Base omega[rad/s]

#define Tsampling 100e-6
//#define Ts Tsampling

#endif /* STALE_H_ */
