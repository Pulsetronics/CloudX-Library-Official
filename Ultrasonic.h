/**************************************************************************

ULTRSONIC LIBRARY
for effective and easy use of ultrasonic sensors
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 Ogboye Godwin & Fidel


FileName:     	Ultrasonic.h
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

/*************************************************************************
 //  EXAMPLE
 
#include <CloudX/M633.h>
#include <CloudX/Ultrasonic.h>

 
int trigg1=5;
int echoo1=6;
int trigg2=7;
int echoo2=8;

float Ldistance,Rdistance;
setup(){
    Ultrasonic_init(1, trigg1, echoo1);
    Ultrasonic_init(2, trigg2, echoo2);
    loop(){
            Ldistance=Ultrasonic_read(1);
            Rdistance=Ultrasonic_read(2);
    }

}*******************************************************************************/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif



#ifndef _Ultrasonic_H_	
#define _Ultrasonic_H_	

unsigned char stre[8][2] = 0;
unsigned char trig, echo;

void Ultrasonic_init(unsigned char num, unsigned char trigger, unsigned char Echo){
        --num;
        T1CON = 0x10;
        pinMode(trigger,OUTPUT);
        pinMode(Echo,INPUT);
        stre[num][0] = trigger;
        stre[num][1] = Echo;
}


float Ultrasonic_read(unsigned char num){
    trig      = stre[num][0];
    echo      = stre[num][1];
    float val = 0;
         
             TMR1H = 0;
             TMR1L = 0;
             PinSelect(trig, HIGH);
             delayUs(10);
             PinSelect(trig, LOW);
 
             while(!readPin(echo));
             T1CONbits.TMR1ON = 1;
             while(readPin(echo));
             T1CONbits.TMR1ON = 0;
             val = ((TMR1L | (TMR1H<<8))*0.0068);
             if(val>=2 && val<=400)
                 return val;
             else 
                 return 401;
         }
		 
#endif   //#ifndef _Ultrasonic_H_		 