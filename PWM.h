
/**************************************************************************

PWM LIBRARY
for generating pulse width modulation
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 Fidel


FileName:     	PWM.h
Dependencies:	None
Compiler:  	CloudX C Compiler
Company:        www.cloudx.ng | www.bytehubembed.com 
Product:        CloudX microcontrollers

You may NOT distribute or sell this code without explicit authorization

* Warranty
* 
* THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
* WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
* LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
* WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
* CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
* PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
* BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
* THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
* SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
* (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
*
**************************************************************************/

/*****************************************************************
 PWM.h code 04/02/2018

  Example:

#include <CloudX/M633.h>
#include <CloudX/PWM.h>

setup(){
           //setup here
           
          PWM1_init(5000);
          PWM2_init(5000);
          PWM1_duty(0);
          PWM2_duty(0);
          PWM1_start();
          PWM2_start();
 

  loop(){
           //Program here
           
           PWM1_duty(50) // 50% Duty cycle
           PWM2_duty(75) // 50% Duty cycle

      }
} 

*************************************************************************/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _PWM_H
#define _PWM_H

#if (TMR2PRESCALAR == 1) || (TMR2PRESCALAR == 4) || (TMR2PRESCALAR == 16)
#define TMR2PRESCALAR 4
#endif

long frequency;

int PWM_Max_Duty()
{
  return(_XTAL_FREQ/(frequency*TMR2PRESCALAR);
}

PWM1_init(long freq)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALAR)) - 1;
  frequency = freq;
}

PWM2_init(long freq)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALAR)) - 1;
  frequency = freq;
}

PWM1_duty(unsigned int duty)
{
    duty = ((float)duty/100) * 1023; //percentage;
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1X = duty & 0x02;
    CCP1Y = duty & 0x01;
    CCPR1L = duty>>0x02;
  }

  }

PWM2_duty(unsigned int duty)
{
    duty = ((float)duty/100) * 1023; //percentage;
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2X = duty & 0x02;
    CCP2Y = duty & 0x01;
    CCPR2L = duty>>0x02;
  }
}

PWM1_start()
{
  CCP1M3 = 1;
  CCP1M2 = 1;
  
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  
  TMR2ON = 1;
  TRISC2 = 0;
} 

PWM1_stop()
{
  CCP1M3 = 0;
  CCP1M2 = 0;
}

PWM2_start()
{
  CCP2M3 = 1;
  CCP2M2 = 1;
  
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  
    TMR2ON = 1;
    TRISC1 = 0;
}

PWM2_stop()
{
  CCP2M3 = 0;
  CCP2M2 = 0;
}

#endif