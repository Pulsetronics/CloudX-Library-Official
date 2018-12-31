/**************************************************************************

LCD LIBRARY
for writing on the display
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 None

FileName:     	LCD.h
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