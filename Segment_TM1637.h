
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:    Segment_TM1637.h
 * Version: 1.0
 * Author:  Embed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the TM1637 Segment Display. 

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
**************************************************************************************************************/


/*

Example:

#include <CloudX\M633.h>
#include <CloudX\Segment_TM1637>

setup(){
           //setup here
           
          SegmentTM1637_setting(1, 2, 5);  //DIO, CLK, brightness
                                           //brightness range: (0 =>Dim    7 =>Bright)

    loop(){
           //Program here

           SegmentTM1637_write(1234); //displays the numerical value 1234
           delayMs(1000);             //delay duration of the display
           
        }
    }
      
*/   

#ifndef _TM1637_H_
#define _TM1637_H_

#include <stdbool.h>

unsigned char segDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40};
unsigned char segBrightness[] = {0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F};  //brightness range: (0x88-Dim     0x8F-Bright)
unsigned char Clk, Dat, flag=0;
int vall=0;


void SegmentTM1637_start() {
    digitalWrite(Clk, HIGH);
    digitalWrite(Dat, HIGH);
    delayUs(5);
    digitalWrite(Dat, LOW);
    digitalWrite(Clk, LOW);
    delayUs(5);
}

void SegmentTM1637_stop() {
    digitalWrite(Clk, LOW);
    digitalWrite(Dat, LOW);
    delayUs(5);
    digitalWrite(Clk, HIGH);
    digitalWrite(Dat, HIGH);
    delayUs(5);
}

bool SegmentTM1637_internalWrite(unsigned char bytes) {
  bool Ack;
   for(unsigned char inc = 0; inc < 8; inc++) {
        digitalWrite(Clk, LOW);
        delayUs(5);
        digitalWrite(Dat, (bytes & (1 << inc)) >> inc);
        delayUs(5);
        digitalWrite(Clk, HIGH);
        delayUs(5);
    }

// wait for ACK

        digitalWrite(Clk, LOW);
        delayUs(5);
        pinMode(Dat, INPUT);
        digitalWrite(Clk, HIGH);
        delayUs(5);
        Ack = !readPin(Dat);
        pinMode(Dat, OUTPUT);
        return Ack;
}
   

    void SegmentTM1637_writes(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4) {
                SegmentTM1637_start();
                SegmentTM1637_internalWrite(0x40);
                SegmentTM1637_stop();
                SegmentTM1637_start();
                SegmentTM1637_internalWrite(0xC0);

                if(byte1 is 0X3F)
                    SegmentTM1637_internalWrite(0);
                else if((flag) && (vall >= 100 && vall <= 999)) {
                    SegmentTM1637_internalWrite(0x40);
                    flag = 0;
                 }
                else
                    SegmentTM1637_internalWrite(byte1);

                if((byte1 is 0x3F) && (byte2 is 0x3F))
                    SegmentTM1637_internalWrite(0);
                else if((flag) && (vall >= 10 && vall <= 99)) {
                    SegmentTM1637_internalWrite(0x40);
                    flag = 0;
                 }
                else
                    SegmentTM1637_internalWrite(byte2);

                if((byte1 is 0x3F) && (byte2 is 0x3F) && (byte3 is 0x3F))
                    SegmentTM1637_internalWrite(0);
                else if((flag) && (vall >= 1 && vall <= 9)) {
                    SegmentTM1637_internalWrite(0x40);
                    flag = 0;
                 }
                else
                    SegmentTM1637_internalWrite(byte3);
                    //SegmentTM1637_internalWrite(0xE6);

                SegmentTM1637_internalWrite(byte4);
                //SegmentTM1637_internalWrite(0xED);

                SegmentTM1637_stop();
    }

SegmentTM1637_clearDisplay() {
   SegmentTM1637_writes(0x00, 0x00, 0x00, 0x00);
}

SegmentTM1637_write(signed int val)  {
    if(val < 0) {
        flag = 1;
        val *= -1;
        vall = val;
    }

         SegmentTM1637_writes(segDigit[val/1000], segDigit[(val%1000)/100], segDigit[((val%1000)%100)/10], segDigit[val%10]);
}

SegmentTM1637_setting(unsigned char DIO, unsigned char CLK, unsigned char Brightness)  {
            Dat = DIO;
            Clk = CLK;
            pinMode(Clk, OUTPUT);
            pinMode(Dat, OUTPUT);
            SegmentTM1637_start();
            
            //brightness range: (0 =>Dim     7 =>Bright)
            SegmentTM1637_internalWrite(segBrightness[Brightness]);
            SegmentTM1637_stop();
 }
#endif   //#ifndef _TM1637_H_