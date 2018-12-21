/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:    LCDAdvanced.h
 * Version: 1.0
 * Author:  Ogboye Godwin G.
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

/*

EXAMPLE:


#include <CloudX/M633.h>
#include <CloudX/LCDAdvanced.h>


int lcd1 = 2;
int lcd2 = 3;
int lcd3 = 4;
int i;

setup(){
           //setup here
    LCDAdvanced_setting(1,lcd1,5,6,7,8);
    LCDAdvanced_setting(1,lcd2,5,6,7,8);
    LCDAdvanced_setting(1,lcd3,5,6,7,8);

    LCDAdvanced_cmd(lcd1,clear);//
    LCDAdvanced_cmd(lcd2,clear);
    LCDAdvanced_cmd(lcd3,clear);
    LCDAdvanced_cmd(lcd1,cursorOff);//
    LCDAdvanced_cmd(lcd2,cursorOn);//
    LCDAdvanced_cmd(lcd3,cursorOff);//
    delayms(1000);


    // LCD3 IS 16X1
    LCDAdvanced_writeText(lcd2, 1,1," THIS IS MULTI-LCD INTERFACE. ");

    // LCD3 IS 16X2
    LCDAdvanced_writeText(lcd3, 1,2," ONLY ON CLOUDX");
    LCDAdvanced_writeText(lcd3, 2,1,"SAY HI TO CLOUDX");

    // LCD1 IS 16X4
    LCDAdvanced_writeText(lcd1, 1,1,"LCD 16X4. TRY");
    LCDAdvanced_writeText(lcd1, 2,1,"THIS AT HOME!!!");


    delayms(4000);


loop(){
    for(i=0;i<=16; i++){
    LCDAdvanced_cmd(lcd1, shiftDisplayLeft);
    LCDAdvanced_cmd(lcd2,shiftDisplayLeft);
    delayms(350);
      }

    for(i=0;i<=16; i++){
    LCDAdvanced_cmd(lcd1, shiftDisplayRight);
    LCDAdvanced_cmd(lcd2,shiftDisplayRight);
    delayms(350);
      }
  }
 }
 
 */


#ifndef _LCDAdvanced_H_
#define _LCDAdvanced_H_
 
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

void LCDAdvanced_settings(char RSS1,char ENN1,char D441,char D551,char D661,char D771)
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



LCD_DISP(unsigned char Dlcd,unsigned char MSB1,unsigned char LSB1){

                           pinSelect(D4, (MSB1 & 1));
                           MSB1 = MSB1 >> 1;  pinSelect(D5, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; pinSelect(D6, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; pinSelect(D7, (MSB1 & 1));
                           pinSelect(Dlcd, 1); __delay_ms(2);  pinSelect(Dlcd, 0);


                           pinSelect(D4, (LSB1 & 1));
                           LSB1 = LSB1 >> 1;  pinSelect(D5, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; pinSelect(D6, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; pinSelect(D7, (LSB1 & 1));
                           pinSelect(Dlcd, 1); __delay_ms(2);  pinSelect(Dlcd, 0);

                           }

LCDAdvanced_cmd(unsigned int Dlcd,unsigned char comd){
                unsigned char MSB2 , LSB2 ;
                          pinSelect(RS, 0);
                           MSB2 = (comd & 0xF0) >> 4; LSB2 = comd & 0x0F ;
                           LCD_DISP(Dlcd,MSB2,LSB2);
                    }

LCDAdvanced_writeCP(unsigned int Dlcd,unsigned char chr){
                         unsigned char MSB,LSB;
                        pinSelect(RS, 1);
                         MSB = (chr & 0xF0) >> 4; LSB = chr& 0x0F ;
                          LCD_DISP(Dlcd,MSB,LSB);
                          }

LCDAdvanced_write(unsigned int Dlcd,unsigned char row,unsigned char col,unsigned char chr){
                   unsigned char MSB , LSB ;
                  if(row==1) LCDAdvanced_cmd(Dlcd,(0x80 + (col-1)));
                  if(row==2) LCDAdvanced_cmd(Dlcd,(0xC0 + (col-1)));
                    if(row==3) LCDAdvanced_cmd(Dlcd,(0x94 + (col-1)));
                  if(row==4) LCDAdvanced_cmd(Dlcd,(0xD4 + (col-1)));
                  LCDAdvanced_writeCP(Dlcd,chr);

                     }
LCDAdvanced_writeTextCP(unsigned int Dlcd,unsigned char *s){
                           unsigned char pnt=0;

                              while(s[pnt] != '\0'){
                                  LCDAdvanced_writeCP(Dlcd,s[pnt]);
                                  pnt++;
                                 __delay_ms(2);
                                  }
                     }


LCDAdvanced_writeText(unsigned int Dlcd,unsigned char row, unsigned char col, char *s){
                        unsigned char MSB , LSB ,chr;  char pnt;
                          if(row==1) LCDAdvanced_cmd(Dlcd,(0x80 + (col-1)));
                          if(row==2) LCDAdvanced_cmd(Dlcd,(0xC0 + (col-1)));
                          if(row==3) LCDAdvanced_cmd(Dlcd,(0x94 +(col-1)));
                          if(row==4) LCDAdvanced_cmd(Dlcd,(0xD4 + (col-1)));
                                      pnt =0;
                            while(s[pnt] != '\0'){
                                  LCDAdvanced_writeCP(Dlcd,s[pnt]);
                                  pnt++;
                          __delay_ms(2);
                                  }

}

Start_cmd(unsigned int Dlcd){
            LCDAdvanced_cmd(Dlcd,0x33);
            __delay_ms(1);
            LCDAdvanced_cmd(Dlcd,0x32);
            __delay_ms(1);
            LCDAdvanced_cmd(Dlcd,0x28);
            __delay_ms(1);
            LCDAdvanced_cmd(Dlcd,0x08);
            __delay_ms(1);
            LCDAdvanced_cmd(Dlcd,0x0C);
            __delay_ms(1);
            LCDAdvanced_cmd(Dlcd,0x06);
            __delay_ms(1);
}

void LCDAdvanced_setting(char RSS1,char Dlcd,char D441,char D551,char D661,char D771){
    LCDAdvanced_settings(RSS1,Dlcd,D441,D551,D661,D771);
    Start_cmd(Dlcd);
     }

void LCDAdvanced_writeCustomChar(unsigned char Dlcd, unsigned char addressCGRAM, unsigned char row, unsigned char col, const char *customCharArray) {
    unsigned char i;
    LCDAdvanced_cmd(Dlcd, 64 + (addressCGRAM * 8));
    for (i = 0; i <= 7; i++) 
        LCDAdvanced_writeCP(Dlcd, customCharArray[i]);
    LCDAdvanced_cmd(Dlcd, returnHome);
    
    if((!row) && (!col))
        LCDAdvanced_writeCP(Dlcd, addressCGRAM);
    else
        LCDAdvanced_write(Dlcd, row, col, addressCGRAM);
 }   

	 
#endif  //#ifndef _LCDAdvanced_H_

