
/******************************************************************************************************
                                   ByteHub Embedded
*******************************************************************************************************
 * File:  HC595.h
 * Version: 1.0
 * Author: Mbed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the second method to demonstrate the 74HC595 Shift Register. 

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
*********************************************************************************************************/

/*
Example:

#include <CloudX\M633.h>
#include <CloudX\HC595_v1.h>

#define RegSize 4
#define Lsb1st 0
#define Msb1st 1

setup(){
           //setup here

           HC595_setting(1, 2, 3); //Dat, Clk, Lat

loop(){
           //Program here

           HC595_shiftOut(0x8143257B, RegSize, Msb1st);  //bytes, byteSize, bitOrder
           delayMs(5000);

      }
}
*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif



#ifndef _HC595_H_
#define _HC595_H_

char CLKK1,LATT1,DATT1;

void HC595_setting(char DATT, char CLKK, char LATT){
    pinMode(CLKK, OUTPUT);  
    pinMode(LATT, OUTPUT);  
    pinMode(DATT, OUTPUT);

    digitalWrite(CLKK, LOW);
    digitalWrite(DATT, LOW);
    digitalWrite(LATT, LOW);
          
    CLKK1 = CLKK; LATT1=LATT; DATT1=DATT;
}

#define CLK CLKK1
#define LAT LATT1
#define DAT DATT1

#define LSB1st 0
#define MSB1st 1


void HC595_shiftOut(unsigned long bytes, unsigned char byteSize, unsigned char bitOrder){
   unsigned char iterator;
    
     if(bitOrder is LSB1st)  {
        for(iterator=0; iterator<byteSize; iterator++)  {
           for(short cnterr=0; cnterr<8; cnterr++) {
             digitalWrite(DAT, (bytes & 0x01));
             digitalWrite(CLK, HIGH); 
             digitalWrite(CLK, LOW);
             bytes = bytes>>1;
           }
         }
        }
    
     else if(bitOrder is MSB1st)  {
       if(byteSize is 1) {  
        for(iterator=0; iterator<byteSize; iterator++)  {
            for(short cnterr=0; cnterr<8; cnterr++) {
             digitalWrite(DAT, ((bytes & 0x80)>>7));
             digitalWrite(CLK, HIGH); 
             digitalWrite(CLK, LOW);
             bytes = bytes<<1;
            }
           }
         }
       else if(byteSize is 2) {  
        for(iterator=0; iterator<byteSize; iterator++)  {
            for(short cnterr=0; cnterr<8; cnterr++) {
             digitalWrite(DAT, ((bytes & 0x8000)>>15));
             digitalWrite(CLK, HIGH); 
             digitalWrite(CLK, LOW);
             bytes = bytes<<1;
            }
           }
         }
       else if(byteSize is 3) {  
        for(iterator=0; iterator<byteSize; iterator++)  {
            for(short cnterr=0; cnterr<8; cnterr++) {
             digitalWrite(DAT, ((bytes & 0x800000)>>23));
             digitalWrite(CLK, HIGH); 
             digitalWrite(CLK, LOW);
             bytes = bytes<<1;
            }
           }
         }
       else if(byteSize is 4) {  
        for(iterator=0; iterator<byteSize; iterator++)  {
            for(short cnterr=0; cnterr<8; cnterr++) {
             digitalWrite(DAT, ((bytes & 0x80000000)>>31));
             digitalWrite(CLK, HIGH); 
             digitalWrite(CLK, LOW);
             bytes = bytes<<1;
            }
           }
         }
      }

     digitalWrite(LAT, HIGH);
     digitalWrite(LAT, LOW);
     delayUs(10);
}

#endif  //#ifndef _HC595_H_