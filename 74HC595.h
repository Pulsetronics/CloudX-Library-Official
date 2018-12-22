
/*************************************************************************************************************
                                   ByteHub Embedded
**************************************************************************************************************
 
 * File:   74HC595.h
 * Version: 1.0
 * Author: 2mee McAlmighty (Oyemade Tumi)
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: This file contains the first method to demonstrate the 74HC595 Shift Register.
 
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
*******************************************************************************************************************/


/*

Example

HC595_Setting(DATAPin, CLOCKPin, LATCHPin); //Select The Pins You want as your DATA,CLOCK and LATCH.
 
HC595_shiftOut(ByteOfData , MSBFIRST );
//////      COMMENT FOR HC595_shiftOut(ByteOfData , MSBFIRST )      //////
//We send the ByteOfData (for example, 0b00001111)
//we then tell the function from which direction to interpret the ByteOfData. If you select
//MSBFIRST, then LEDs 1 to 4 would turn on and the others would turn off. If you choose
//LSBFIRST, then LEDs 5 to 8 would turn on and the others would turn off.
////////////////////////////////////////////////////////////////////////////////////////
 
 
 HC595_LATCH(); //This tells the shift register that all the bits in the ByteOfData are shifted in and ready.
                //The 74HC595 Shift Register now changes its output to the data received.
                                  
								  //Main COde//
setup(){
        HC595_setting(1,2,3);

    loop(){
        HC595_shiftOut(0b10101010 , MSBFIRST);
        HC595_latch();
        delayMs(1000);
        HC595_shiftOut(0b10101010 , LSBFIRST);
        HC595_latch();
        delayMs(1000);
    }
}

*/


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