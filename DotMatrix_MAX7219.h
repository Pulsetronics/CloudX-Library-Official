
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:  DotMatrix_MAX7219.h
 * Version: 1.01
 * Author: Mbed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the MAX7219 DotMatrix Display. 

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
#include <CloudX\DotMatrix_MAX7219.h>

setup(){
           //setup here
           
           MAX7219_setting(1, 2, 32, 3);   //DIN, CLK, CS, colSize, brightness (0 -> Dim : 15 -> Brightest)
 
loop(){
           //Program here
           
           MAX7219_scrollDisplay("Hello, World! ", 6);   //speeder, string

      }
} 

*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _MAX7219_H_
#define _MAX7219_H_

#define  _0percentCharging   0
#define  _25percentCharging  1
#define  _50percentCharging  2
#define  _75percentCharging  3
#define  _100percentCharging 4

#define  _0percentBar   0
#define  _25percentBar  1
#define  _50percentBar  2
#define  _75percentBar  3
#define  _100percentBar 4

 const char font[][8] = {
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ' ' 20h
 { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00 }, // '!' 21h
 { 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '"' 22h
 { 0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00 }, // '#' 23h
 { 0x30, 0x7C, 0xC0, 0x78, 0x0C, 0xF8, 0x30, 0x00 }, // '$' 24h
 { 0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00 }, // '%' 25h
 { 0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00 }, // '&' 26h
 { 0x60, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ''' 27h
 { 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00 }, // '(' 28h
 { 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00 }, // ')' 29h
 { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00 }, // '*' 2Ah
 { 0x00, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x00, 0x00 }, // '+' 2Bh
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60 }, // ',' 2Ch
 { 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00 }, // '-' 2Dh
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00 }, // '.' 2Eh
 { 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00 }, // '/' 2Fh
 { 0x7C, 0xC6, 0xCE, 0xDE, 0xF6, 0xE6, 0x7C, 0x00 }, // '0' 30h
 { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00 }, // '1' 31h
 { 0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00 }, // '2' 32h
 { 0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00 }, // '3' 33h
 { 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00 }, // '4' 34h
 { 0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00 }, // '5' 35h
 { 0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00 }, // '6' 36h
 { 0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00 }, // '7' 37h
 { 0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00 }, // '8' 38h
 { 0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00 }, // '9' 39h
 { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00 }, // ':' 3Ah
 { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60 }, // ';' 3Bh
 { 0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00 }, // '<' 3Ch
 { 0x00, 0x00, 0xFC, 0x00, 0x00, 0xFC, 0x00, 0x00 }, // '=' 3Dh
 { 0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00 }, // '>' 3Eh
 { 0x78, 0xCC, 0x0C, 0x18, 0x30, 0x00, 0x30, 0x00 }, // '?' 3Fh
 { 0x7C, 0xC6, 0xDE, 0xDE, 0xDE, 0xC0, 0x78, 0x00 }, // '@' 40h
 { 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00 }, // 'A' 41h
 { 0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00 }, // 'B' 42h
 { 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00 }, // 'C' 43h
 { 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00 }, // 'D' 44h
 { 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00 }, // 'E' 45h
 { 0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00 }, // 'F' 46h
 { 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00 }, // 'G' 47h
 { 0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00 }, // 'H' 48h
 { 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 }, // 'I' 49h
 { 0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00 }, // 'J' 4Ah
 { 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00 }, // 'K' 4Bh
 { 0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00 }, // 'L' 4Ch
 { 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00 }, // 'M' 4Dh
 { 0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00 }, // 'N' 4Eh
 { 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00 }, // 'O' 4Fh
 { 0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00 }, // 'P' 50h
 { 0x78, 0xCC, 0xCC, 0xCC, 0xDC, 0x78, 0x1C, 0x00 }, // 'Q' 51h
 { 0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00 }, // 'R' 52h
 { 0x78, 0xCC, 0xE0, 0x70, 0x1C, 0xCC, 0x78, 0x00 }, // 'S' 53h
 { 0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 }, // 'T' 54h
 { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00 }, // 'U' 55h
 { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00 }, // 'V' 56h
 { 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0xC6, 0x00 }, // 'W' 57h
 { 0xC6, 0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0x00 }, // 'X' 58h
 { 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00 }, // 'Y' 59h
 { 0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00 }, // 'Z' 5Ah
 { 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00 }, // '[' 5Bh
 { 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00 }, // '\' 5Ch
 { 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00 }, // ']' 5Dh
 { 0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00 }, // '^' 5Eh
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF }, // '_' 5Fh
 { 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '`' 60h
 { 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00 }, // 'a' 61h
 { 0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00 }, // 'b' 62h
 { 0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00 }, // 'c' 63h
 { 0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00 }, // 'd' 64h
 { 0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00 }, // 'e' 65h
 { 0x38, 0x6C, 0x60, 0xF0, 0x60, 0x60, 0xF0, 0x00 }, // 'f' 66h
 { 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8 }, // 'g' 67h
 { 0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00 }, // 'h' 68h
 { 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 }, // 'i' 69h
 { 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78 }, // 'j' 6Ah
 { 0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00 }, // 'k' 6Bh
 { 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 }, // 'l' 6Ch
 { 0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xC6, 0x00 }, // 'm' 6Dh
 { 0x00, 0x00, 0xF8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00 }, // 'n' 6Eh
 { 0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00 }, // 'o' 6Fh
 { 0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0 }, // 'p' 70h
 { 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E }, // 'q' 71h
 { 0x00, 0x00, 0xDC, 0x76, 0x66, 0x60, 0xF0, 0x00 }, // 'r' 72h
 { 0x00, 0x00, 0x7C, 0xC0, 0x78, 0x0C, 0xF8, 0x00 }, // 's' 73h
 { 0x10, 0x30, 0x7C, 0x30, 0x30, 0x34, 0x18, 0x00 }, // 't' 74h
 { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00 }, // 'u' 75h
 { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00 }, // 'v' 76h
 { 0x00, 0x00, 0xC6, 0xD6, 0xFE, 0xFE, 0x6C, 0x00 }, // 'w' 77h
 { 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00 }, // 'x' 78h
 { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8 }, // 'y' 79h
 { 0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00 }, // 'z' 7Ah
 { 0x1C, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x1C, 0x00 }, // '{' 7Bh
 { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00 }, // '|' 7Ch
 { 0xE0, 0x30, 0x30, 0x1C, 0x30, 0x30, 0xE0, 0x00 }, // '}' 7Dh
 { 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '~' 7Eh
 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  // ' ' 7Fh
};


const char battLevel[][8] = {
 { 0x18, 0x3C, 0x24, 0x24, 0x24, 0x24, 0x3C, 0x00 }, // empty
 { 0x18, 0x3C, 0x24, 0x24, 0x24, 0x3C, 0x3C, 0x00 }, // 25% full
 { 0x18, 0x3C, 0x24, 0x24, 0x3C, 0x3C, 0x3C, 0x00 }, // 50% full
 { 0x18, 0x3C, 0x24, 0x3C, 0x3C, 0x3C, 0x3C, 0x00 }, // 75% full
 { 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x00 }  // full
};

const char chargingBatt[][8] = {
 { 0x18, 0x3C, 0x24, 0x24, 0x24, 0x24, 0x3C, 0xE0 }, // charging from empty
 { 0x18, 0x3C, 0x24, 0x24, 0x24, 0x3C, 0x3C, 0xE0 }, // 25% full
 { 0x18, 0x3C, 0x24, 0x24, 0x3C, 0x3C, 0x3C, 0xE0 }, // 50% full
 { 0x18, 0x3C, 0x24, 0x3C, 0x3C, 0x3C, 0x3C, 0xE0 }, // 75% full
 { 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xE0 }  // full
};




byte mAX7219_regNoop        = 0x00;
byte mAX7219_regDigit0      = 0x01;
byte mAX7219_regDigit1      = 0x02;
byte mAX7219_regDigit2      = 0x03;
byte mAX7219_regDigit3      = 0x04;
byte mAX7219_regDigit4      = 0x05;
byte mAX7219_regDigit5      = 0x06;
byte mAX7219_regDigit6      = 0x07;
byte mAX7219_regDigit7      = 0x08;
byte mAX7219_regDecodeMode  = 0x09;
byte mAX7219_regIntensity   = 0x0A;
byte mAX7219_regScanLimit   = 0x0B;
byte mAX7219_regShutdown    = 0x0C;
byte mAX7219_regDisplayTest = 0x0F;


unsigned char chipSize, size, count, count0, colCount = 0, shiftByte = 0;
unsigned char  _Clk, _Cs, _DIn;
char displayColor = 0, scrollCheck = 0;
char dataa[9], mainData[95];
char column[] = {1, 2, 3, 4, 5, 6, 7, 8};




void byteWrite(byte _data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);     
    digitalWrite(_Clk, LOW);   
    if (_data & mask){            
      digitalWrite(_DIn, HIGH);
    }else{
      digitalWrite(_DIn, LOW); 
    }
    digitalWrite(_Clk, HIGH);   
    --i;                         
  }
}

void mAXInitialize (byte reg, byte colData) {    
  digitalWrite(_Cs, LOW);  
  for (byte c =1; c<= chipSize; c++) {
          byteWrite(reg);
          byteWrite(colData);
    }
  digitalWrite(_Cs, LOW);
  digitalWrite(_Cs,HIGH);
}

MAX7219_Init(unsigned char colSize, unsigned char _brightness) {
  chipSize = colSize / 8;
  mAXInitialize(mAX7219_regScanLimit, 0x07);      
  mAXInitialize(mAX7219_regDecodeMode, 0x00);  
  mAXInitialize(mAX7219_regShutdown, 0x01);    
  mAXInitialize(mAX7219_regDisplayTest, 0x00);
  mAXInitialize(mAX7219_regIntensity, _brightness);  //brightness (0 -> Dim : 15 -> Brightest)
  for (byte bh = 1; bh <= 8; bh++) {
        mAXInitialize(bh, 0);
   }    
  size = colSize + 8;                                                
  }
  
void MAX7219_settings(char DIn, char Clk,  char Cs)  {
        pinMode(Clk, OUTPUT);
        pinMode(Cs, OUTPUT);
        pinMode(DIn, OUTPUT);
        _DIn = DIn; _Clk = Clk; _Cs = Cs;
  }

void MAX7219_setting(char DIN, char CLK, char CS, char columnSize, char brightness)  // brightness (0 -> Dim : 15 -> Brightest)
{    
     MAX7219_settings(DIN, CLK, CS);
     MAX7219_Init(columnSize, brightness);
 }


display(char vall){
             byte colReg, _data, scan=0;
                colReg = column[vall] ;
                _data  = mainData[vall];

                if(!scrollCheck)
                {
                for(count=0; count<(size-8)/8; count++) {
                    digitalWrite(_Cs, LOW);       
                    byteWrite(colReg);                  
                    byteWrite(_data);             
                    scan           = scan+8;
                    _data = mainData[scan+vall];
                  }
                }
                else
                {
                    for(count=0; count<(size-8)/8; count++) {
                        digitalWrite(_Cs, LOW);
                        byteWrite(colReg);
                        byteWrite(_data);
                        scan           = scan+8;
                        _data = mainData[scan+vall];
                     }
                }

               digitalWrite(_Cs, LOW);       
               digitalWrite(_Cs,HIGH);
     }

display1(char vall){
                char colReg, _data, scan = 0;
                colReg = column[vall] ;
                _data  = ~mainData[vall];

                if(!scrollCheck)
                {
                    for(count=0; count<(size-8)/8; count++) {
                        digitalWrite(_Cs, LOW);
                        byteWrite(colReg);
                        byteWrite(_data);
                        scan  = scan+8;
                        _data = ~mainData[scan+vall];
                    }
                }

                else
                {
                 for(count=0; count<1; count++){

                        digitalWrite(_Cs, LOW);
                        byteWrite(colReg);
                        byteWrite(_data);
                        scan  = scan+8;
                        _data = ~mainData[scan+vall];
                    }
                }

               digitalWrite(_Cs, LOW);       
               digitalWrite(_Cs,HIGH);
     }
                
Scroll_scrollLeft(){
               unsigned char k;
               for(k=0; k<size; k++)
                  mainData[k] = mainData[k+1];
   }

scrollUp_scrollLeft(){
               unsigned int k, kk, sel=0;
               byte countStore;
               countStore = ((size-8)/8);
               for(k=0; k<8; k++) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                          if(kk == countStore-1) {
                               mainData[k+sel] = mainData[k+sel] >> 1;
                               mainData[k+sel] =  mainData[k+sel]|((mainData[k+sel+8] & 0x01) << 7);
                          }
                          else
                              mainData[k+sel] = 0;
                       sel=sel+8;
                      }
                     mainData[(size-8)+k] = mainData[(size-8)+k] >> 1;
               }
         }

scrollDown_scrollLeft(){
               unsigned int k, kk, sel=0;
               byte countStore;
               countStore = ((size-8)/8);
               for(k=0; k<8; k++) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                          if(kk == countStore-1) {
                               mainData[k+sel] = mainData[k+sel] << 1;
                               mainData[k+sel] =  mainData[k+sel]|((mainData[k+sel+8] & 0x80) >> 7);
                          }
                          else
                              mainData[k+sel] = 0;
                       sel=sel+8;
                      }
                     mainData[(size-8)+k] = mainData[(size-8)+k] << 1;
                     }
         }

displays() {             
       unsigned int k;
       for(k=0; k<8; k++) {
                if(displayColor==0) display(k);
                else display1(k);
                }
        }      

 unsigned char rightTrim() {  
                 unsigned char dat0, dat1, dat2, dat3, dat4, dat5, dat6, dat7;
                 dat0=dat1=dat2=dat3=dat4=dat5=dat6=dat7=1;
              for(byte i=0;i<=5;i++){
                  dat0 = dataa[0]&(0x20>>i);
                  if(dat0==0) {
                      dat1 = dataa[1]&(0x20>>i);
                    if(dat1==0) {
                        dat2 = dataa[2]&(0x20>>i);
                       if(dat2==0) {
                           dat3 = dataa[3]&(0x20>>i);
                           if(dat3==0) {
                               dat4 = dataa[4]&(0x20>>i);
                               if(dat4==0) {
                                   dat5 = dataa[5]&(0x20>>i);
                                   if(dat5==0) {
                                       dat6 = dataa[6]&(0x20>>i);
                                       if(dat6==0) {
                                           dat7 = dataa[7]&(0x20>>i);
                                           if(dat7==0) {
                                               colCount = i+3; return colCount;
                                           }
                                        }
                                    }
                                 }
                             }
                          }
                       }
                    }
                }
     }

unsigned char leftTrim() {  
                 dataa[0] = dataa[0]<<(count0);
                 dataa[1] = dataa[1]<<(count0);
                 dataa[2] = dataa[2]<<(count0);
                 dataa[3] = dataa[3]<<(count0);
                 dataa[4] = dataa[4]<<(count0);
                 dataa[5] = dataa[5]<<(count0);
                 dataa[6] = dataa[6]<<(count0);
                 dataa[7] = dataa[7]<<(count0);
                 rightTrim(); 
             }
             
unsigned char trimCheck() {   
                 unsigned char datt0, datt1, datt2, datt3, datt4, datt5, datt6, datt7;
                 datt0 = datt1=datt2=datt3=datt4=datt5=datt6=datt7=1; count0 = 0;
                 for(byte i=0; i<5; i++) {
                   datt0 = dataa[0] & (0x80>>i);
                   if(datt0==0) datt1 = dataa[1] & (0x80>>i); else return count0;
                   if(datt1==0) datt2 = dataa[2] & (0x80>>i); else return count0;
                   if(datt2==0) datt3 = dataa[3] & (0x80>>i); else return count0;
                   if(datt3==0) datt4 = dataa[4] & (0x80>>i); else return count0;
                   if(datt4==0) datt5 = dataa[5] & (0x80>>i); else return count0;
                   if(datt5==0) datt6 = dataa[6] & (0x80>>i); else return count0;
                   if(datt6==0) datt7 = dataa[7] & (0x80>>i); else return count0;
                   if(datt7==0) count0++; else return count0; } }          

        
scrollText(unsigned char col, unsigned int speedFactor ){
                     unsigned int scan;
                  for(byte i=0; i<col; i++) {
                       for(scan=0; scan<speedFactor; scan++) {
                        displays();
                  }
                  if(scrollCheck == 0)
                      Scroll_scrollLeft();
                  else if(scrollCheck == 1)
                      scrollUp_scrollLeft();
                  else
                      scrollDown_scrollLeft();
                }
       }

 screenText(unsigned char col, unsigned int speedFactor) {
                  unsigned int scan;
                  for(byte i = 0; i < col; i++) {
                       for(scan = 0; scan < speedFactor; scan++);
                       Scroll_scrollLeft();
                }
             }
 
 moveDisplay(const char *charDisp, unsigned char scrollSpeed){
           byte dat, index = 0, mask = 0x80;
           char character;
           byte buffer[9];
           while(charDisp[index] != '\0'){   
                   character = charDisp[index++];          
                   
                  for (byte i=0; i<8; i++)          
                       dataa[i] = font[character - 0x20][i];   
                                    
                  trimCheck();
                  if(count0==0) rightTrim(); else leftTrim();
                  
                  for (byte k=0; k<8; k++) {
                      for(signed char i=7; i>=0; i--) {
                          dat = dataa[i] & (mask>>k);  
                          dat = dat >> (7-k);   
                          buffer[k] = (buffer[k]<<1) | dat; 
                      }
                   }
                                  
                  if(!scrollCheck)
                  {
                      for(byte i=0; i<8; i++)
                         mainData[(size-8)+i] = buffer[i];
                      scrollText(colCount, scrollSpeed);
                  }
                  else
                  {
                      for(byte i=0; i<8; i++)
                         mainData[(size-8)+i] = buffer[i];
                      scrollText(8, scrollSpeed);
                  }
              }
           }      
       
          
void MAX7219_scrollDisplay(const char *characters, unsigned char scrollSpeed)   //speeder, string
 {
                      unsigned char spaceBar;
                      displayColor = 0;
                      moveDisplay(characters, scrollSpeed);
                      for(spaceBar=0; spaceBar<(size-8)/8; spaceBar++)
                          moveDisplay(" ", scrollSpeed);
   }  



void MAX7219_scrollUpDisplay(const char *characters, unsigned char scrollSpeed)   //speeder, string
 {

                      unsigned char spaceBar;
                      scrollCheck = 1;
                      displayColor = 0;
                      moveDisplay(characters, scrollSpeed);
                      for(spaceBar=0; spaceBar<(size-8)/8; spaceBar++)
                         moveDisplay(" ", scrollSpeed);
                      scrollCheck = 0;
   }

void MAX7219_scrollDownDisplay(const char *characters, unsigned char scrollSpeed)   //speeder, string
 {

                      unsigned char spaceBar;
                      scrollCheck = 2;
                      displayColor = 0;
                      moveDisplay(characters, scrollSpeed);
                      for(spaceBar=0; spaceBar< (size-8)/8 ; spaceBar++)
                         moveDisplay(" ", scrollSpeed);
                      scrollCheck = 0;
   }


void MAX7219_scrollInverseDisplay(const char *characters, unsigned char scrollSpeed){
                      unsigned char spaceBar;
                      displayColor = 1;
                      moveDisplay(characters, scrollSpeed);
                      for(spaceBar=0; spaceBar< (size-8)/8 ; spaceBar++)
                          moveDisplay(" ", scrollSpeed);
     }

void MAX7219_write(const char character, int stayFactor)  {
           byte countStore, dat, mask = 0x80;
           byte buffer[9];
           countStore = ((size-8)/8);

           for(byte j=0; j<((size-8)/8); j++)
           {
                   if(j == (countStore-1))
                   {
                      for (byte i=0; i<8; i++)
                           dataa[i] = font[character - 0x20][i];

                      for (byte k=0; k<8; k++) {
                          for(signed char i=7; i>=0; i--) {
                              dat = dataa[i] & (mask>>k);
                              dat = dat >> (7-k);
                              buffer[k] = (buffer[k]<<1) | dat;
                          }
                       }

                      for (byte i=0; i<8; i++)
                          mainData[(size-8)+i] = buffer[i];
                    }
                   else
                       for (byte i=0; i<8; i++)
                           mainData[(size-8)+i] = 0;

                   screenText(8, 3);
             }
                   for(int duration = 0; duration < stayFactor; duration++) displays();
}

void MAX7219_writeText(const char *characters, int stayFactor)  {
    byte count = 0, countStore, dat, index = 0, mask = 0x80;
           char character;
           byte buffer[9];
           const char *pointar;
           pointar = characters;
           while(*characters++ != '\0')
               count++;
           characters = pointar;
           if(count < ((size-8)/8))
           {
               countStore = (((size-8)/8) - count);
               for(byte j=0; j<((size-8)/8); j++)
               {
                   if(j>=countStore)
                   {
                       character = characters[index++];

                      for (byte i=0; i<8; i++)
                           dataa[i] = font[character - 0x20][i];

                      for (byte k=0; k<8; k++) {
                          for(signed char i=7; i>=0; i--) {
                              dat = dataa[i] & (mask>>k);
                              dat = dat >> (7-k);
                              buffer[k] = (buffer[k]<<1) | dat;
                          }
                       }

                      for (byte i=0; i<8; i++)
                          mainData[(size-8)+i] = buffer[i];
                    }
                   else
                       for (byte i=0; i<8; i++)
                           mainData[(size-8)+i] = 0;

                   screenText(8, 3);
                  }
                  for(int duration = 0; duration < stayFactor; duration++) displays() ;
               }

           else
           {
               while(characters[index] != '\0'){   
                character = characters[index++];          
                   
                  for (byte i=0; i<8; i++)          
                       dataa[i] = font[character - 0x20][i];   
                                    
                  for (byte k=0; k<8; k++) {
                      for(signed char i=7; i>=0; i--) {
                          dat = dataa[i] & (mask>>k);  
                          dat = dat >> (7-k);   
                          buffer[k] = (buffer[k]<<1) | dat; 
                      }
                   }
                  
                  for (byte i=0; i<8; i++)          
                      mainData[(size-8)+i] = buffer[i];

                 screenText(8, 3);
              }
              for(int duration = 0; duration < stayFactor; duration++) displays() ;
           }
}

void MAX7219_scrollUpEffect(unsigned int speedFactor){
     unsigned int monitor, monitor1;
     unsigned char k, kk, sel;
     for(monitor1=0; monitor1<8; monitor1++)
     {
         for(monitor=0; monitor<speedFactor; monitor++)
              displays();
              for(k=0; k<8; k++)
              {
                   sel=0;
                   for(kk=0; kk<((size-8)/8); kk++)
                   {
                      mainData[k+sel] = mainData[k+sel] >> 1;
                      sel = sel+8;
                  }
              }
      }
}

void MAX7219_scrollDownEffect(unsigned int speedFactor){
     unsigned int monitor, monitor1;
     unsigned char kk, sel;
     for(monitor1=0; monitor1<8; monitor1++){
         for(monitor=0; monitor<speedFactor; monitor++)
                  displays();
                  for(signed char k=7; k>=0; k--) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                           mainData[k+sel] = mainData[k+sel] << 1;
                           sel = sel+8;
                      }

                   }
         }
}

void MAX7219_majDiagonalUpScroll(int speedFactor){
          unsigned int monitor, monitor1;
          unsigned char k;
          for(monitor1=0; monitor1<8; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k = 0; k < (size-8); k++)
                      mainData[k] = mainData[k + 1] >> 1;
          }
  }

void MAX7219_minDiagonalUpScroll(int speedFactor){
          unsigned int monitor, monitor1;
          signed char k;
          for(monitor1=0; monitor1<8; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k = (size-8); k >=0 ; k--)
                      mainData[k] = mainData[k - 1] >> 1;
          }
  }

void MAX7219_majDiagonalDownScroll(int speedFactor){
          unsigned int monitor, monitor1;
          signed char k;
          for(monitor1=0; monitor1<8; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k = (size-8); k >=0 ; k--)
                      mainData[k] = mainData[k - 1] << 1;
          }
  }

void MAX7219_minDiagonalDownScroll(int speedFactor){
          unsigned int monitor, monitor1;
          unsigned char k;
          for(monitor1=0; monitor1<8; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k = 0; k < (size-8); k++)
                      mainData[k] = mainData[k + 1] << 1;
          }
  }

void MAX7219_batteryLevel(byte percentLevel, int stayFactor) {
           byte countStore, dat, mask = 0x80;
           byte buffer[9];
           countStore = ((size-8)/8);

           for(byte j=0; j<((size-8)/8); j++)
           {
                   if(j == (countStore-1))
                   {
                      for (byte i=0; i<8; i++)
                           dataa[i] = battLevel[percentLevel][i];

                      for (byte k=0; k<8; k++) {
                          for(signed char i=7; i>=0; i--) {
                              dat = dataa[i] & (mask>>k);
                              dat = dat >> (7-k);
                              buffer[k] = (buffer[k]<<1) | dat;
                          }
                       }

                      for (byte i=0; i<8; i++)
                          mainData[(size-8)+i] = buffer[i];
                    }
                   else
                       for (byte i=0; i<8; i++)
                           mainData[(size-8)+i] = 0;

                   screenText(8, 3);
             }
                   for(int duration = 0; duration < stayFactor; duration++) displays();
}

void MAX7219_chargingBattery(byte percentCharging, int speedFactor){
      unsigned char flag = 0, countStore, pntt = 0, shiftByte;

      byte dat, mask = 0x80;
      byte buffer[9];

      countStore = ((size-8)/8);

      while(pntt <= 9)  {
           for(byte j=0; j<((size-8)/8); j++)
           {
                   if(j == (countStore-1))
                   {
                      for (byte i=0; i<8; i++)
                           dataa[i] = chargingBatt[percentCharging][i];
                      if(!flag) {
                          shiftByte = dataa[7];
                          flag = 1; }
                      if(flag)  {
                          if(pntt >= 5)
                              shiftByte = shiftByte<<1;
                          else
                              shiftByte = shiftByte>>1;
                          pntt++;
                          dataa[7] = shiftByte;
                       }

                         for (byte k=0; k<8; k++) {
                            for(signed char i=7; i>=0; i--) {
                              dat = dataa[i] & (mask>>k);
                              dat = dat >> (7-k);
                              buffer[k] = (buffer[k]<<1) | dat;
                              }
                           }

                           for (byte i=0; i<8; i++)
                              mainData[(size-8)+i] = buffer[i];
                   }

                  else
                      for (byte i=0; i<8; i++)
                          mainData[(size-8)+i] = 0;

                 screenText(8, 3);
                 }
              for(int time = 0; time < speedFactor; time++) displays();
          }
}


#endif   //#ifndef _MAX7219_H_
