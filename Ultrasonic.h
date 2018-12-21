
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:        Ultrasonic.h
 * Author:      Olayiwola Ayinde
 * Modified:    Ogboye Godwin G.(and calibrated by Fidel)
 * Created on May 3, 2018, 12:19 PM
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the Ultrasonic Sensor. 

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


/*
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

}*/
    


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