/**************************************************************************

74HC595 SHIFT REGISTERLIBRARY
for Port IO Expanders
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 2mee McAlmighty (Oyemade Tumi)

Modified:
(C)2018 None

FileName:     	74HC595.h
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

#ifndef _74HC595_H_
#define _74HC595_H_


#define MSBFIRST 0
#define LSBFIRST 1

char DATA, CLOCK, LATCH;
HC595_setting(char DAT, char CLK, char LAT){
          pinMode(DAT,OUTPUT);
          pinMode(CLK,OUTPUT);
          pinMode(LAT,OUTPUT);
          DATA=DAT; CLOCK=CLK; LATCH=LAT;
}

HC595_latch(){
       PinSelect(LATCH,HIGH); delayUs(500); PinSelect(LATCH,LOW);
}

HC595_shiftOut(unsigned char dataByte , char OutType ){
    char i;
    if(OutType == MSBFIRST){
     for(i=0; i<8; i++){
       PinSelect(DATA,((dataByte&0x80)>>7));
       dataByte = dataByte << 1;
       PinSelect(CLOCK,HIGH); delayUs(1);  PinSelect(CLOCK,LOW);
    }
    }
    
    if(OutType == LSBFIRST){
     for(i=0; i<8; i++){
       PinSelect(DATA,(dataByte&0x01));;
       dataByte = dataByte >> 1;
       PinSelect(CLOCK,HIGH); delayUs(1);  PinSelect(CLOCK,LOW);
    }
    }
}

#endif   //#ifndef _74HC595_H_