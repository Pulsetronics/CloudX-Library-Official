
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   PWM.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: This file contains the program to demonstrate the PWM. 

This code has been developed and tested on CloudX microcontroller boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.makeelectronics.ng for awesome tutorials on CloudX,ARM,Robotics,RTOS,IOT.
ByteHub Embedded invests substantial time and effort developing open source HW and SW tools,
to support consider buying the CloudX microcontroller boards.
 
The ByteHub Embedded libraries and examples are licensed under the terms of the new-bsd license
(two-clause bsd license). See also: http://www.opensource.org/licenses/bsd-license.php

BYTEHUB EMEBEDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE 
INFORMATION RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/




/* PWM.h code 04/02/2018

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

*/

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