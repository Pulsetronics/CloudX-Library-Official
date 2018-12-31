/**************************************************************************

ANALOG WRITE LIBRARY
for Software Pulse Width Modulations 
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Fidel


Modified:
(C)2018 None

FileName:     	AnalogWrite.h
Dependencies:	None
Compiler:  	CloudX C Compiler
Company:        cloudx.ng | www.bytehubembed.com
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


#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

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