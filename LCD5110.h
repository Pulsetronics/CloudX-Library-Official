
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:    LCD5110.h
 * Version: 1.0
 * Author:  Mbed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the 5110-GLCD. 

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
#include <CloudX\LCD5110.h>
 
#define _font_5x7_
#define _font_3x5_
#include <CloudX\Font.h> 


const unsigned char ASCIIfont[][5] = {
 {0x00, 0x00, 0x00, 0x00, 0x00}, // 20
 {0x00, 0x00, 0x5f, 0x00, 0x00}, // 21 !
 {0x00, 0x07, 0x00, 0x07, 0x00}, // 22" ////
 {0x14, 0x7f, 0x14, 0x7f, 0x14}, // 23 #
 {0x24, 0x2a, 0x7f, 0x2a, 0x12}, // 24 $
 {0x23, 0x13, 0x08, 0x64, 0x62}, // 25 %
 {0x36, 0x49, 0x55, 0x22, 0x50}, // 26 &
 {0x00, 0x05, 0x03, 0x00, 0x00}, // 27 ' ////
 {0x00, 0x1c, 0x22, 0x41, 0x00}, // 28 (
 {0x00, 0x41, 0x22, 0x1c, 0x00}, // 29 )
 {0x14, 0x08, 0x3e, 0x08, 0x14}, // 2a *
 {0x08, 0x08, 0x3e, 0x08, 0x08}, // 2b +
 {0x00, 0x50, 0x30, 0x00, 0x00}, //  , 2c
 {0x08, 0x08, 0x08, 0x08, 0x08}, // 2d -
 {0x00, 0x60, 0x60, 0x00, 0x00}, // 2e .
 {0x20, 0x10, 0x08, 0x04, 0x02}, // / 2f 
 {0x3e, 0x51, 0x49, 0x45, 0x3e}, // 30 0
 {0x00, 0x42, 0x7f, 0x40, 0x00}, // 31 1
 {0x42, 0x61, 0x51, 0x49, 0x46}, // 32 2
 {0x21, 0x41, 0x45, 0x4b, 0x31}, // 33 3
 {0x18, 0x14, 0x12, 0x7f, 0x10}, // 34 4
 {0x27, 0x45, 0x45, 0x45, 0x39}, // 35 5
 {0x3c, 0x4a, 0x49, 0x49, 0x30}, // 36 6
 {0x01, 0x71, 0x09, 0x05, 0x03}, // 37 7
 {0x36, 0x49, 0x49, 0x49, 0x36}, // 38 8
 {0x06, 0x49, 0x49, 0x29, 0x1e}, // 39 9
 {0x00, 0x36, 0x36, 0x00, 0x00}, // 3a :
 {0x00, 0x56, 0x36, 0x00, 0x00}, //  ;  3b
 {0x08, 0x14, 0x22, 0x41, 0x00}, // 3c <
 {0x14, 0x14, 0x14, 0x14, 0x14}, // 3d =
 {0x00, 0x41, 0x22, 0x14, 0x08}, // 3e >
 {0x02, 0x01, 0x51, 0x09, 0x06}, // 3f ?
 {0x32, 0x49, 0x79, 0x41, 0x3e}, // 40 @
 {0x7e, 0x11, 0x11, 0x11, 0x7e}, // 41 A
 {0x7f, 0x49, 0x49, 0x49, 0x36}, // 42 B
 {0x3e, 0x41, 0x41, 0x41, 0x22}, // 43 C
 {0x7f, 0x41, 0x41, 0x22, 0x1c}, // 44 D
 {0x7f, 0x49, 0x49, 0x49, 0x41}, // 45 E
 {0x7f, 0x09, 0x09, 0x09, 0x01}, // 46 F
 {0x3e, 0x41, 0x49, 0x49, 0x7a}, // 47 G
 {0x7f, 0x08, 0x08, 0x08, 0x7f}, // 48 H
 {0x00, 0x41, 0x7f, 0x41, 0x00}, // 49 I
 {0x20, 0x40, 0x41, 0x3f, 0x01}, // 4a J
 {0x7f, 0x08, 0x14, 0x22, 0x41}, // 4b K
 {0x7f, 0x40, 0x40, 0x40, 0x40}, // 4c L
 {0x7f, 0x02, 0x0c, 0x02, 0x7f}, // 4d M
 {0x7f, 0x04, 0x08, 0x10, 0x7f}, // 4e N
 {0x3e, 0x41, 0x41, 0x41, 0x3e}, // 4f O
 {0x7f, 0x09, 0x09, 0x09, 0x06}, // 50 P
 {0x3e, 0x41, 0x51, 0x21, 0x5e}, // 51 Q
 {0x7f, 0x09, 0x19, 0x29, 0x46}, // 52 R
 {0x46, 0x49, 0x49, 0x49, 0x31}, // 53 S
 {0x01, 0x01, 0x7f, 0x01, 0x01}, // 54 T
 {0x3f, 0x40, 0x40, 0x40, 0x3f}, // 55 U
 {0x1f, 0x20, 0x40, 0x20, 0x1f}, // 56 V
 {0x3f, 0x40, 0x38, 0x40, 0x3f}, // 57 W
 {0x63, 0x14, 0x08, 0x14, 0x63}, // 58 X
 {0x07, 0x08, 0x70, 0x08, 0x07}, // 59 Y
 {0x61, 0x51, 0x49, 0x45, 0x43}, // 5a Z
 {0x00, 0x7f, 0x41, 0x41, 0x00}, // 5b [
 {0x02, 0x04, 0x08, 0x10, 0x20}, // 5c 
 {0x00, 0x41, 0x41, 0x7f, 0x00}, // 5d ]
 {0x04, 0x02, 0x01, 0x02, 0x04}, // 5e ^
 {0x40, 0x40, 0x40, 0x40, 0x40}, // 5f _
 {0x00, 0x01, 0x02, 0x04, 0x00}, // 60 `
 {0x20, 0x54, 0x54, 0x54, 0x78}, // 61 a
 {0x7f, 0x48, 0x44, 0x44, 0x38}, // 62 b
 {0x38, 0x44, 0x44, 0x44, 0x20}, // 63 c
 {0x38, 0x44, 0x44, 0x48, 0x7f}, // 64 d
 {0x38, 0x54, 0x54, 0x54, 0x18}, // 65 e
 {0x08, 0x7e, 0x09, 0x01, 0x02}, // 66 f
 {0x0c, 0x52, 0x52, 0x52, 0x3e}, // 67 g
 {0x7f, 0x08, 0x04, 0x04, 0x78}, // 68 h
 {0x00, 0x44, 0x7d, 0x40, 0x00}, // 69 i
 {0x20, 0x40, 0x44, 0x3d, 0x00}, // 6a j
 {0x7f, 0x10, 0x28, 0x44, 0x00}, // 6b k
 {0x00, 0x41, 0x7f, 0x40, 0x00}, // 6c l
 {0x7c, 0x04, 0x18, 0x04, 0x78}, // 6d m
 {0x7c, 0x08, 0x04, 0x04, 0x78}, // 6e n
 {0x38, 0x44, 0x44, 0x44, 0x38}, // 6f o
 {0x7c, 0x14, 0x14, 0x14, 0x08}, // 70 p
 {0x08, 0x14, 0x14, 0x18, 0x7c}, // 71 q
 {0x7c, 0x08, 0x04, 0x04, 0x08}, // 72 r
 {0x48, 0x54, 0x54, 0x54, 0x20}, // 73 s
 {0x04, 0x3f, 0x44, 0x40, 0x20}, // 74 t
 {0x3c, 0x40, 0x40, 0x20, 0x7c}, // 75 u
 {0x1c, 0x20, 0x40, 0x20, 0x1c}, // 76 v
 {0x3c, 0x40, 0x30, 0x40, 0x3c}, // 77 w
 {0x44, 0x28, 0x10, 0x28, 0x44}, // 78 x
 {0x0c, 0x50, 0x50, 0x50, 0x3c}, // 79 y
 {0x44, 0x64, 0x54, 0x4c, 0x44}, // 7a z
 {0x00, 0x08, 0x36, 0x41, 0x00}, // 7b {
 {0x00, 0x00, 0x7f, 0x00, 0x00}, // 7c |
 {0x00, 0x41, 0x36, 0x08, 0x00}, // 7d }
 {0x10, 0x08, 0x08, 0x10, 0x08}, // 7e ~
 {0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
};

// ------------------------------------------------------  
// Picture name: BBme_bmp            
// GLCD Model: Nokia 3310, 5110, and the likes
// ------------------------------------------------------  

unsigned char const BBme_bmp[504] = {
255,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 129, 
193, 225, 225, 225,  65, 225, 225, 161, 225, 225,   1, 225, 
225, 161, 225, 193, 225, 225, 225, 129, 129, 225, 225, 225, 
193, 193,  65, 193, 193, 193, 193,   1, 193, 193, 193, 193, 
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 255, 
255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 240, 240, 
 51, 243, 243, 241, 240, 243,  51, 243, 243, 241, 224, 227, 
227, 227, 115, 113,   3,   3,   0,   3, 243, 240, 227, 227, 
227,   3, 240, 243,  51, 240, 243, 242, 241, 243, 243,  51, 
240, 240,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255, 
255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 247, 247, 
116, 245, 245, 117, 245, 231, 116, 247, 247, 223, 223, 207, 
255, 243, 207, 223,  24, 199, 247, 251, 247, 246, 195, 199, 
  5, 240, 247, 247, 244, 245, 213, 245, 245,  53, 117, 116, 
247, 247,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255, 
255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 238, 239, 
 47, 255, 247, 235, 255, 247,  40, 235, 239, 235, 189, 183, 
247, 231, 247, 247, 214, 123, 255, 247, 247, 247, 145, 251, 
251, 203, 235, 239, 201, 249, 248, 255, 175, 104, 111, 103, 
 63,  63,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255, 
255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 207, 207, 
204, 207, 207, 207, 207,  79, 204,  15,  15,  15,  15,  15, 
 15,  15,  15,  15,  64, 207,  79, 207, 207, 193, 193, 207, 
207,  67, 207, 204, 205, 207, 143, 207, 143, 195, 207, 204, 
207, 207,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255, 
255, 128, 176, 240, 176, 240, 240, 176, 176, 160, 176, 176, 
224, 176, 240, 160, 240, 176, 176, 176, 176, 176, 129, 128, 
128, 129, 129, 128, 129, 129, 129, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 129, 129, 128, 129, 129, 128, 129, 129, 
129, 129, 128, 128, 129, 128, 129, 128, 129, 129, 129, 128, 
129, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 188, 252, 188, 188, 188, 188, 252, 252, 184, 128, 255
}; 


setup(){
           //setup here

           LCD5110_setting(1, 2, 3, 4, 5 );  //Rset,CE,DC,DIn,Clk

   loop(){
           //Program here

           LCD5110_clear();
           LCD5110_image(BBme_bmp, White);
           delayMs(3000);
           LCD5110_clear();
           LCD5110_fillScreen(Black);
           delayMs(1000);
           LCD5110_clear();
           LCD5110_writeText(FONT_3x5, 3, 32, 1, 1, "Hello, World! ", White);  //userFont,fontWidth,fontOffset,row,col,Text
                                                                        //rows range: 1 -> 6
                                                                        //cols range: 1 -> 12
           LCD5110_writeText(ASCIIfont, 5, 32, 3, 1, "Bytehub ", White);
           LCD5110_writeText(ASCIIfont, 5, 32, 4, 5, "Embedde", White);
           LCD5110_writeCP(FONT_5x7, 5, 32, 'd');                      //userFont,fontWidth,fontOffset,character
           delayMs(3000);
           LCD5110_fillScreen(White);
           delayMs(1000);
           LCD5110_write(ASCIIfont, 5, 32, 4, 3, 'B', Black);                //userFont,fontWidth,fontOffset,row,col,character
           LCD5110_writeCP(FONT_5x7, 5, 32, 'H');                     //userFont,fontWidth,fontOffset,character
           LCD5110_writeTextCP(FONT_3x5, 3, 32, " Embedded");         //userFont,fontWidth,fontOffset,Text
           delayMs(3000);
    }
 }

*/


#ifndef _LCD5110_H_
#define _LCD5110_H_

#define Clear 0x00
#define Black 0xFF
#define White Clear


unsigned char colCheck, rowCheck;

char _Clk, _DIn, _DC, _CE, _Rset;

#define LCD_Clk    _Clk
#define LCD_DIn    _DIn
#define LCD_DC     _DC
#define LCD_CE     _CE
#define LCD_Rset   _Rset

#define LCDCommand 0
#define LCDData 1

#define LCDX 84
#define LCDY 48

byte fontWidth, fontOffset;
void LCD5110_clear();


 LCD5110_internalWrite(unsigned char Data__Command, unsigned char dataByte) {
    unsigned char _data, i;
    _data = dataByte;
    if(Data__Command is 0)  
        digitalWrite(LCD_DC, LOW);
    else 
        digitalWrite(LCD_DC, HIGH);
    
    digitalWrite(LCD_CE, LOW);  
   for(i=0;i<8;i++)  {
        digitalWrite(LCD_Clk, LOW);
        if(_data & 0x80) 
            digitalWrite(LCD_DIn, HIGH);
        else
            digitalWrite(LCD_DIn, LOW);
        digitalWrite(LCD_Clk, HIGH);
        _data = _data << 1;
        digitalWrite(LCD_Clk, LOW); 
    }
    
   digitalWrite(LCD_CE, HIGH);   
}

startCommand() {
    LCD5110_internalWrite(LCDCommand, 0x21); 
    LCD5110_internalWrite(LCDCommand, 0xB5);
    LCD5110_internalWrite(LCDCommand, 0x04); 
    LCD5110_internalWrite(LCDCommand, 0x14); 
    LCD5110_internalWrite(LCDCommand, 0x20);
    LCD5110_internalWrite(LCDCommand, 0x0C);
   }


gotoXY(byte Y, byte X) {
    X*= 7;
    colCheck = X;
    LCD5110_internalWrite(0, (0x40 | Y)); 
    LCD5110_internalWrite(0, (0x80 | X)); 
   }
   
void LCD5110_startRow(unsigned char row){
     LCD5110_internalWrite(0, (0x40 | row));
}

void LCD5110_startCol(unsigned char col){
    LCD5110_internalWrite(0, (0x80 | col));
   }  
LCD5110_image(char *userArray, char dispType){
     LCD5110_clear();
     for (int pointer = 0; pointer < (LCDX * LCDY / 8); pointer++)
        LCD5110_internalWrite(LCDData, 0x00);
     gotoXY(0, 0); 
    switch(dispType){
            case White: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0C);
                         break;
                           }
            case Black: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0D);
                         break;
                           }
        }
     for (int pointer = 0; pointer < (LCDX * LCDY / 8); pointer++)
          LCD5110_internalWrite(LCDData, userArray[pointer]);  
 }

LCD5110_inWrite(char roww, char coll, char dat) {
    colCheck = coll;
    rowCheck = roww;
    if(coll > 84);
    else {
	LCD5110_startCol(coll);
        LCD5110_internalWrite(LCDData, dat);
     }
  }  

LCD5110_writeCP(const unsigned char *userFont, byte fontWidth, byte fontOffset, char character) //, char dispTyper)
{
    byte pos_x = 0, _data;
    LCD5110_internalWrite(LCDData, 0x00);
    colCheck++;
     while(pos_x < fontWidth) {
	    _data = userFont[((character - fontOffset) * fontWidth) + pos_x++];
	    LCD5110_inWrite(rowCheck, colCheck++, _data);
		}
     LCD5110_internalWrite(LCDData, 0x00);
     colCheck++;
 }

LCD5110_write(const unsigned char *userFont, byte fontWidth, byte fontOffset, byte row, byte col, char character, char dispType)
{
    switch(dispType){
            case White: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0C);
                         break;
                           }
            case Black: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0D);
                         break;
                           }
        }
    gotoXY((row-1), (col-1));  
    byte pos_x = 0, _data;
    LCD5110_internalWrite(LCDData, 0x00);
    colCheck++;
     while(pos_x < fontWidth) {
	    _data = userFont[((character - fontOffset) * fontWidth) + pos_x++];
	    LCD5110_inWrite(row, colCheck++, _data);
		}
     LCD5110_internalWrite(LCDData, 0x00);
     colCheck++;	 
 }
 

LCD5110_writeTextCP(const unsigned char *userFont, byte fontWidth, byte fontOffset, char *characters)  {
    while (*characters)
        LCD5110_writeCP(userFont, fontWidth, fontOffset, *characters++); 
} 

LCD5110_writeText(const unsigned char *userFont, byte fontWidth, byte fontOffset, byte row, byte col, char *characters, char dispType) {
    switch(dispType){
            case White: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0C);
                         break;
                           }
            case Black: {LCD5110_internalWrite(LCDCommand, 0x20);
                         LCD5110_internalWrite(LCDCommand, 0x0D);
                         break;
                           }
        }
    gotoXY((row-1), (col-1));
    while (*characters) {
        LCD5110_writeCP(userFont, fontWidth, fontOffset, *characters++);
      }
} 

void LCD5110_fillScreen(unsigned char bytez){
     for (int pointer = 0; pointer < (LCDX * LCDY / 8); pointer++)
        LCD5110_internalWrite(LCDData, bytez);
   }

void LCD5110_clear() {
     for (int pointer = 0; pointer < (LCDX * LCDY / 8); pointer++)
        LCD5110_internalWrite(LCDData, 0x00);
     gotoXY(0, 0); 
  }

void LCD5110_settings(char Clk, char DIn, char DC, char CE, char Rset)  {
    pinMode(Clk, OUTPUT); 
    pinMode(DIn, OUTPUT); 
    pinMode(DC, OUTPUT); 
    pinMode(CE, OUTPUT); 
    pinMode(Rset, OUTPUT);
    
    digitalWrite(Rset, LOW);
    digitalWrite(Rset, HIGH);

    _Clk = Clk; _DIn = DIn; _DC = DC; _CE = CE; _Rset = Rset; 
}

void LCD5110_setting(char Rset, char CE, char DC, char DIn, char Clk) //Rset,CE,DC,DIn,Clk
{
   
    LCD5110_settings(Clk, DIn, DC, CE, Rset);
    startCommand();
   } 

   #endif   //#ifndef _LCD5110_H_