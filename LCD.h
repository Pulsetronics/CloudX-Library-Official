/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   LCD.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the LCD. 

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


#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _LCD_H_
#define _LCD_H_

#define clear               0x01
#define returnHome          0x02
#define moveCursorRight     0x14
#define moveCursorLeft      0x10
#define shiftDisplayRight   0x1C
#define shiftDisplayLeft    0x18
#define cursorBlink         0x0F
#define cursorOff           0x0C
#define cursorOn            0x0E
#define Function_set_4bit   0x28
#define Function_set_8bit   0x38
#define Entry_mode          0x06
#define Function_8_bit      0x32

char ENN, RSS, D44, D55, D66, D77;

void lcdSettings(char RSS1,char ENN1,char D441,char D551,char D661,char D771)
{
    pinMode(RSS1,OUTPUT); pinMode(ENN1,OUTPUT); pinMode(D441,OUTPUT); pinMode(D551,OUTPUT); pinMode(D661,OUTPUT); pinMode(D771,OUTPUT);
  
   RSS = RSS1; ENN= ENN1;  D44= D441; D55=D551; D66=D661; D77=D771;
    
   }
#define RS RSS
#define EN ENN
#define D4 D44
#define D5 D55
#define D6 D66
#define D7 D77



LCD_DISP(unsigned char MSB1,unsigned char LSB1){

                           PinSelect(D4, (MSB1 & 1));
                           MSB1 = MSB1 >> 1;  PinSelect(D5, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; PinSelect(D6, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; PinSelect(D7, (MSB1 & 1));
                           PinSelect(EN, 1); __delay_ms(2);  PinSelect(EN, 0);


                           PinSelect(D4, (LSB1 & 1));
                           LSB1 = LSB1 >> 1;  PinSelect(D5, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; PinSelect(D6, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; PinSelect(D7, (LSB1 & 1));
                           PinSelect(EN, 1); __delay_ms(2);  PinSelect(EN, 0);

                           }

LCD_cmd(unsigned char comd){
                unsigned char MSB2 , LSB2 ;
                          PinSelect(RS, 0);
                           MSB2 = (comd & 0xF0) >> 4; LSB2 = comd & 0x0F ;
                           LCD_DISP(MSB2,LSB2);
                    }

LCD_writeCP(unsigned char chr){
                         unsigned char MSB,LSB;
                        PinSelect(RS, 1);
                         MSB = (chr & 0xF0) >> 4; LSB = chr& 0x0F ;
                          LCD_DISP(MSB,LSB);
                          }

LCD_write(unsigned char row,unsigned char col,unsigned char chr){
                   unsigned char MSB , LSB ;
                  if(row==1) lcdCmd(0x80 + (col-1));
                  if(row==2) lcdCmd(0xC0 + (col-1));
                    if(row==3) lcdCmd(0x94 + (col-1));
                  if(row==4) lcdCmd(0xD4 + (col-1));
                  lcdWriteCP(chr);

                     }
LCD_writeTextCP(unsigned char *s){
                           unsigned char pnt=0;

                              while(s[pnt] != '\0'){
                                  lcdWriteCP(s[pnt]);
                                  pnt++;
                                 __delay_ms(2);
                                  }
                     }


LCD_writeText(unsigned char row, unsigned char col, char *s){
                        unsigned char MSB , LSB ,chr;  char pnt;
                          if(row==1) lcdCmd(0x80 + (col-1));
                          if(row==2) lcdCmd(0xC0 + (col-1));
                          if(row==3) lcdCmd(0x94 +(col-1));
                          if(row==4) lcdCmd(0xD4 + (col-1));
                                      pnt =0;
                            while(s[pnt] != '\0'){
                                  lcdWriteCP(s[pnt]);
                                  pnt++;
                          __delay_ms(2);
                                  }

}

Start_cmd(){
            lcdCmd(0x33);
            __delay_ms(1);
             lcdCmd(0x32);
            __delay_ms(1);
             lcdCmd(0x28);
            __delay_ms(1);
             lcdCmd(0x08);
            __delay_ms(1);
            lcdCmd(0x0C);
            __delay_ms(1);
            lcdCmd(0x06);
            __delay_ms(1);
}



void LCD_setting(char RSS1,char ENN1,char D441,char D551,char D661,char D771){
    lcdSettings(RSS1,ENN1,D441,D551,D661,D771);
    Start_cmd();
     }

void LCD_writeCustomChar(unsigned char addressCGRAM, unsigned char row, unsigned char col, const char *customCharArray) {
    unsigned char i;
    LCD_cmd(64 + (addressCGRAM *  8));
    for (i = 0; i <= 7; i++) 
        LCD_writeCP(customCharArray[i]);
    LCD_cmd(returnHome);
    
    if((!row) && (!col))
        LCD_writeCP(addressCGRAM);
    else
        LCD_write(row, col, addressCGRAM);
 }   

 #endif   //#ifndef _LCD_H_