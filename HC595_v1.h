/**************************************************************************

74HC595 SHIFT REGISTER V1 LIBRARY
for IO Port expander
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Fidel


Modified:
(C)2018 None


FileName:     	HC595_v1.h
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