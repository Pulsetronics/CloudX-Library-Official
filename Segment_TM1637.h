
/**************************************************************************

 TM1637 SEGMENT LIBRARY
for writing on seven segment display
Version: 	2.0 BETA
Release date:	

Author:
(C)2018 Fidel

Modified:
(C)2019 None


FileName:     	Segment_TM1637.h
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

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

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