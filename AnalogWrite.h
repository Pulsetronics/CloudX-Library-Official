
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 
 * File:   AnalogWrite.h
 * Version: 1.0
 * Author: Mbed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: This file contains the program to demonstrate the Software PWM.
 
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
************************************************************************************************************/



/*

Example:


#include <CloudX\M633.h>
#include <CloudX\AnalogWrite.h>

setup(){
           //setup here
    
           analogWrite_setting();
           
 loop(){
           //Program here

          analogWrite(1, 50);   //pwm pin, duty cycle
          delayMs(2000);
          analogWrite(1, 90);
          delayMs(2000);
          analogWrite(2, 25);
          delayMs(2000);
          analogWrite(2, 25);
          delayMs(2000);
          analogWrite(1, 25);
          delayMs(2000);
          analogWrite_stop();  //stops analogWrite function

      }
} 

*/



#ifndef _AnalogWrite_H_
#define _AnalogWrite_H_

unsigned short timer1H01, timer1L01, timer1H02, timer1L02;
unsigned char pwmPin, ppin=0, toggle=0, xEnd=1, check0=101,check1=101;
 
analogWrite_setting() {
                
                    T1CONbits.TMR1ON  = 0;                                    // Timer OFF
                    T1CONbits.T1OSCEN = 1;
                    T1CONbits.TMR1CS  = 0;                                    // Use internal clock
                    T1CONbits.T1CKPS0 = 0;                                    // Prescaler = 1
                    T1CONbits.T1CKPS1 = 0;                                    // Prescaler = 1

                    T1CONbits.TMR1ON = HIGH;
                    PIR1bits.TMR1IF  = LOW;
                    PIE1bits.TMR1IE  = HIGH;                                // enables timer1 interrupt
                    INTCON           = 0xC0;                                // enables global and peripheral interrupts
       }


analogWrite_start() {
     if(check1 is 0)
         digitalWrite(pwmPin, LOW);
     else
         digitalWrite(pwmPin, HIGH);
     T1CONbits.TMR1ON = HIGH;
        }

 analogWrite_stop() {
            T1CONbits.TMR1ON = LOW;
            digitalWrite(ppin, LOW);
        }

 analogWrites(unsigned char val ) {
                      
             float dutyCycle1, dutyCycle2;
             dutyCycle1 = val  * 1000000;
             dutyCycle1 = (float)dutyCycle1 / 100;
             dutyCycle2 = (100 - val)  * 1000000;
             dutyCycle2 = (float)dutyCycle2 / 100;


                          float oscPeriod;
                          oscPeriod        = (dutyCycle1 * 5) / 1000;  
                          oscPeriod        = 65536 - oscPeriod;
                          timer1H01        = (byte)(oscPeriod / 256);
                          timer1L01        = (byte)(oscPeriod - (256*timer1H01));  
                          oscPeriod        = (dutyCycle2 * 5) / 1000;  
                          oscPeriod        = 65536 - oscPeriod;
                          timer1H02        = (byte)(oscPeriod / 256);
                          timer1L02        = (byte)(oscPeriod - (256*timer1H02));  //(byte)oscPeriod % 256
                          TMR1H            = timer1H01;
                          TMR1L            = timer1L01;
                          analogWrite_start();
      }


interrupt _analogWrite_() {

         if(PIR1bits.TMR1IF) {
             PIR1bits.TMR1IF = LOW;
             if(check1 is 100) {
                TMR1H           = timer1H01;
                TMR1L           = timer1L01;
                digitalWrite(pwmPin, HIGH);
             } 

             else if(check1 is 0) {
                TMR1H           = timer1H02;
                TMR1L           = timer1L02;
                digitalWrite(pwmPin, LOW);
             }
             else {
               if(toggle is 0) {
                TMR1H           = timer1H02;
                TMR1L           = timer1L02;
                digitalWrite(pwmPin, LOW);
                toggle =  1;
               }

              else if(toggle is 1) {
                TMR1H           = timer1H01;
                TMR1L           = timer1L01;
                digitalWrite(pwmPin, HIGH);
                toggle = 0;
                }
            }
   }
}


analogWrite(unsigned char pinn, unsigned char dutyCycle )  {
                if(!((dutyCycle is check0) && (pinn is ppin ))) {
                     check0 = dutyCycle;
					 digitalWrite(ppin, LOW);  //clears the previous pin
                     ppin = pinn;
                     pinMode(pinn, OUTPUT);
					 pwmPin = pinn;
                     analogWrites(dutyCycle);
                }
         }


 #endif   //#ifndef _AnalogWrite_H_              