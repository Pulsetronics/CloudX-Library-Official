/**************************************************************************

DOT MATRIX 8x8 LIBRARY
for scrolling text display and effects
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Fidel

Modified:
(C)2018 None


FileName:     	DotMatrix_8x8.h
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



/*************************************************************************

Example:

#include <CloudX\M633.h>
#include <CloudX\DotMatrix_8x8.h>

setup(){
           //setup here
           
           DotMatrix_setting(1, 2, 3, 32);  //DAT, CLK, LAT, displaySize

           
    loop(){
           //Program here

               DotMatrix_scrollInverseDisplay(5,"Display 8x32    ");
               DotMatrix_scrollDisplay(5,"ByteHub Embedded's LAB  ");
               DotMatrix_standMatrix(20,"Make");
               DotMatrix_clearDisplay();
			   DotMatrix_standMatrix(20,"Byte");
               DotMatrix_scrollUp(100);
			   DotMatrix_standMatrix(20,"Hub ");
               DotMatrix_clearDisplay();
           }
   }   

**********************************************************************/


#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif
	 
#ifndef _DotMatrix_8x8_H_		 
#define _DotMatrix_8x8_H_

#define  DAT  _Dat
#define  CLK  _Clk
#define  LAT  _Lat


//
//colSizes      (eg. 8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184)
//displaySpeed  (eg. 10 )
//
       unsigned char size, count0, colCount=0;
       unsigned char _Dat, _Clk, _Lat;

       unsigned char mainData[95], character;
       char row[]= {1,2,4,8,16,32,64,128};     //row scanning
       unsigned char i,j;
       char displayColor = 0;


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
 { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00 }, // '1' 31C
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

 
 unsigned char count, dispCharacter, colSize;
 
void DotMatrix_settings(char Dat, char Clk, char Lat)  {
    pinMode(Clk, OUTPUT); 
    pinMode(Dat, OUTPUT);
    pinMode(Lat, OUTPUT);
   _Dat = Dat;  _Clk = Clk; _Lat = Lat;
  }

void DotMatrix_setting(char DAT, char CLK, char LAT, char columnSize) {
     DotMatrix_settings(DAT, CLK, LAT);
     colSize = columnSize;
     size    = colSize + 8;  
 }

display(char vall){
                                char rows, scan=0;
                                rows          = row[vall] ;
                                dispCharacter = ~mainData[vall];

                                for(count=0; count<(size-8)/8; count++){
                          for(j=0; j<8; j++){
                                    digitalWrite(DAT, (dispCharacter & 0x01));
                                    digitalWrite(CLK, HIGH); 
                                    digitalWrite(CLK, LOW);
                                    dispCharacter = dispCharacter >> 1;
                                       }
                                scan          = scan + 8;
                                dispCharacter = ~mainData[scan + vall];
                               }
                          for(j=0; j<8; j++) {
                                    digitalWrite(DAT, (rows & 0x01));
                                    digitalWrite(CLK, HIGH); 
                                    digitalWrite(CLK, LOW);
                                    rows = rows >> 1;
                                   }

                          digitalWrite(LAT, HIGH);
                          digitalWrite(LAT, LOW);
                          delayUs(10);

             }

display1(char vall){
                                char rows, scan = 0;
                                rows          = row[vall] ;
                                dispCharacter = mainData[vall];

                                for(count=0; count<(size-8)/8; count++){
                          for(j=0; j<8; j++){
                                    digitalWrite(DAT, (dispCharacter & 0x01));
                                    digitalWrite(CLK, HIGH); 
                                    digitalWrite(CLK, LOW);
                                    dispCharacter = dispCharacter >> 1;
                                   }
                                scan          = scan + 8;
                                dispCharacter = mainData[scan+vall];
                               }
                          for(j=0; j<8; j++) {
                                    digitalWrite(DAT, (rows & 0x01));
                                    digitalWrite(CLK, HIGH); 
                                    digitalWrite(CLK, LOW);
                                    rows = rows >> 1;
                                    }

                          digitalWrite(LAT, HIGH); 
                          digitalWrite(LAT, LOW);
                          delayUs(10);
             }
                               
scrollLeft(){
               unsigned char k, kk, sel=0;                         //shifting and scrolling left
               for(k=0; k<8; k++) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                           mainData[k+sel] = mainData[k+sel] << 1;
                           mainData[k+sel] =  mainData[k+sel]|((mainData[k+sel+8] & 0x80) >> 7);
                           sel = sel+8;
                      }
                       mainData[(size-8) + k] = mainData[(size-8) + k] << 1;
                     }
     }
            
displays(){             //data out one after the other as the row comes out).display output function . col before row
           unsigned char k;
           for(k=0; k<8; k++) {
                    if(displayColor==0) display(k);
                    else display1(k);
              }
         }
                    
unsigned char rightTrim() {  //checks for trailing zeroes
                 unsigned char dat0, dat1, dat2, dat3, dat4, dat5, dat6, dat7;
                 dat0=dat1=dat2=dat3=dat4=dat5=dat6=dat7=1;
              for(i=0;i<=5;i++){
                  dat0 = mainData[(size-8)+ 0]&(0x20>>i);
                  if(dat0==0) {
                      dat1 = mainData[(size-8)+ 1]&(0x20>>i);
                    if(dat1==0) {
                        dat2 = mainData[(size-8)+ 2]&(0x20>>i);
                       if(dat2==0) {
                           dat3 = mainData[(size-8)+ 3]&(0x20>>i);
                           if(dat3==0) {
                               dat4 = mainData[(size-8)+ 4]&(0x20>>i);
                               if(dat4==0) {
                                   dat5 = mainData[(size-8)+ 5]&(0x20>>i);
                                   if(dat5==0) {
                                       dat6 = mainData[(size-8)+ 6]&(0x20>>i);
                                       if(dat6==0) {
                                           dat7 = mainData[(size-8)+ 7]&(0x20>>i);
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

unsigned char leftTrim() {  //Takes care of leading zeroes
                 mainData[(size-8)+ 0] = mainData[(size-8)+ 0]<<(count0);
                 mainData[(size-8)+ 1] = mainData[(size-8)+ 1]<<(count0);
                 mainData[(size-8)+ 2] = mainData[(size-8)+ 2]<<(count0);
                 mainData[(size-8)+ 3] = mainData[(size-8)+ 3]<<(count0);
                 mainData[(size-8)+ 4] = mainData[(size-8)+ 4]<<(count0);
                 mainData[(size-8)+ 5] = mainData[(size-8)+ 5]<<(count0);
                 mainData[(size-8)+ 6] = mainData[(size-8)+ 6]<<(count0);
                 mainData[(size-8)+ 7] = mainData[(size-8)+ 7]<<(count0);
                 rightTrim(); 
             }

unsigned char trim() {   //checks for leading zeroes
                 unsigned char datt0, datt1, datt2, datt3, datt4, datt5, datt6, datt7;
                 datt0 = datt1=datt2=datt3=datt4=datt5=datt6=datt7=1; count0 = 0;
                 for(i=0; i<5; i++) {
                   datt0 = mainData[(size-8)+ 0] & (0x80>>i);
                   if(datt0==0) datt1 = mainData[(size-8)+ 1] & (0x80>>i); else return count0;
                   if(datt1==0) datt2 = mainData[(size-8)+ 2] & (0x80>>i); else return count0;
                   if(datt2==0) datt3 = mainData[(size-8)+ 3] & (0x80>>i); else return count0;
                   if(datt3==0) datt4 = mainData[(size-8)+ 4] & (0x80>>i); else return count0;
                   if(datt4==0) datt5 = mainData[(size-8)+ 5] & (0x80>>i); else return count0;
                   if(datt5==0) datt6 = mainData[(size-8)+ 6] & (0x80>>i); else return count0;
                   if(datt6==0) datt7 = mainData[(size-8)+ 7] & (0x80>>i); else return count0;
                   if(datt7==0) count0++; else return count0; 
               } 
           }          

scrollText(unsigned char col, unsigned int speed ){
                  unsigned int scan;
                  for(i=0; i<col; i++) {
                       for(scan=0; scan<speed; scan++) {
                        displays();
                  }
                  scrollLeft();
                }
             }

screenText(unsigned char col, unsigned int speed ){
                     unsigned int scan;
                  for(i=0; i<col; i++) {
                       for(scan=0; scan<speed; scan++);
                       scrollLeft();
                }
             }

void DotMatrix_fillScreen(unsigned char val){
                              int monitor,monitor1;
                              for(monitor1=0; monitor1<10; monitor1++){
                                  for(monitor=0; monitor<8; monitor++)
                                      mainData[(size-8) + monitor] = val;
                                  scrollText(8,3);
                        }
      }

void DotMatrix_clearDisplay() {
           unsigned char count=0;
             while(count <= colSize){

               for (i=0; i<8; i++)
                   mainData[(size-8)+i] = font[0][i];

               count += 8;
               screenText(8,3);
              }
              displays() ;
         }
      
moveDisplay(const char *charDisp, unsigned char scrollSpeed){
                   unsigned char index = 0;
                   while(charDisp[index] != '\0'){   
                   character = charDisp[index++];          
                   
                  for (i=0; i<8; i++)          
                      mainData[(size-8)+i] = font[character - 0x20][i];                     
                  trim();
                  if(count0==0) rightTrim(); else leftTrim();
                  scrollText(colCount, scrollSpeed);  
              }
           }
          
void DotMatrix_scrollDisplay(const char *charDisp, unsigned char scrollSpeed){
                      unsigned char spaceBar;
                      displayColor=0;
                      moveDisplay(scrollSpeed,charDisp);
                      for(spaceBar=0; spaceBar< (size-8)/8 ; spaceBar++)
                          moveDisplay(scrollSpeed," ");
                         }

void DotMatrix_scrollInverseDisplay(const char *charDisp, unsigned char scrollSpeed){
                      unsigned char spaceBar;
                      displayColor=1;
                      moveDisplay(scrollSpeed, charDisp);
                      for(spaceBar=0; spaceBar< (size-8)/8 ; spaceBar++)
                          moveDisplay(scrollSpeed," ");

     }

void DotMatrix_writeText(char *messages, int time){
             int duration;
             unsigned char index= 0;
             while(messages[index] != '\0'){
             character = messages[index];
               for (i=0; i<8; i++){
                   mainData[(size-8)+i] = font[character - 0x20][i];
                }
               index++;
               screenText(8,3);
              }
              for(duration =0; duration< time; duration++) displays() ;
         }

void DotMatrix_scrollUpEffect(unsigned int speed){
     unsigned int monitor, monitor1;
     unsigned char k, kk, sel;
     for(monitor1=0; monitor1<10; monitor1++){
         for(monitor=0; monitor<speed; monitor++)
                  displays();
                  for(k=0; k<8; k++) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                           if(k == 7)
                               mainData[k+sel] = 0;
                           else
                               mainData[k+sel] = mainData[(k+1) + sel];
                           sel = sel+8;
                      }
                  }
         }
}

void DotMatrix_scrollDownEffect(unsigned int speedFactor){
     unsigned int monitor, monitor1;
     unsigned char kk, sel;
     for(monitor1=0; monitor1<10; monitor1++){
         for(monitor=0; monitor<speedFactor; monitor++)
                  displays();
                  for(signed char k=7; k>=0; k--) {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++){
                           if(k == 0)
                               mainData[k+sel] = 0;
                           else
                               mainData[k+sel] = mainData[(k-1) + sel];
                           sel = sel+8;
                      }

                   }
         }
}

/*DotMatrix_scrollSlantLeft0(int speed){
            unsigned int count, count1;
             unsigned char k;
             for(count1=0; count1<speed; count1++){
                for(count=0; count<10; count++)
                                    displays();
               for(k=0; k<8; k++) {
                      data1[k] = data1[k+1] << 1;   data1[k] = (data1[k] | ((data2[k] & 0x80)>>7));
                      data2[k] = data2[k+1] << 1;   data2[k] = (data2[k] | ((data3[k] & 0x80)>>7));
                      data3[k] = data3[k+1] << 1;   data3[k] = (data3[k] | ((data3[k] & 0x80)>>7));
                      data4[k] = data4[k+1] << 1;   data4[k] = (data4[k] | ((data5[k] & 0x80)>>7));
                      data5[k] = data5[k+1] << 1;   data5[k] = (data5[k] | ((data6[k] & 0x80)>>7));
                      data6[k] = data6[k+1] << 1;   data6[k] = (data6[k] | ((data7[k] & 0x80)>>7));
                      data7[k] = data7[k+1] << 1;   data7[k] = (data7[k] | ((data8[k] & 0x80)>>7));
                      data8[k] = data8[k+1] << 1;   data8[k] = (data8[k] | ((data9[k] & 0x80)>>7));
                      data9[k] = data9[k+1] << 1;   data9[k] = (data9[k] | ((data10[k] & 0x80)>>7));
                      data10[k] = data10[k+1] << 1; data10[k] = (data10[k] | ((data11[k] & 0x80)>>7));
                      data11[k] = data11[k+1] << 1;

                     }
         }
}
 */

void DotMatrix_majDiagonalUpScroll(int speedFactor){
          unsigned int monitor, monitor1;
          unsigned char k, kk, sel;
          for(monitor1=0; monitor1<10; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k=0; k<8; k++)
                  {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++)
                       {
                           if(k == 7)
                               mainData[k+sel] = 0;
                           else {
                               mainData[k+sel] = mainData[(k+1) + sel] << 1;
                               mainData[k+sel] = mainData[k+sel] | ((mainData[(k+8) + sel] & 0x80)>>7);
                           }
                         sel = sel+8;
                        }
                 }
           }
  }

/*DotMatrix_scrollSlantRight0(int speed){
              unsigned int count, count1;
              unsigned char k;
              for(count1=0; count1<speed; count1++){
                     for(count=0; count<10; count++)
                                    displays();
                for(k=0; k<8; k++) {
                      data1[k] = data1[k+1] << 1;   data1[k]= (data1[k] | ((data2[k] & 0x01)<<7));
                      data2[k] = data2[k+1] << 1;   data2[k]= (data2[k] | ((data3[k] & 0x01)<<7));
                      data3[k] = data3[k+1] << 1;   data3[k]= (data3[k] | ((data4[k] & 0x01)<<7));
                      data4[k] = data4[k+1] << 1;   data4[k]= (data4[k] | ((data5[k] & 0x01)<<7));
                      data5[k] = data5[k+1] << 1;
                      data5[k] = data5[k+1] >> 1;   data5[k] = (data5[k] | ((data6[k] & 0x01)<<7));
                      data6[k] = data6[k+1] >> 1;   data6[k] = (data6[k] | ((data7[k] & 0x01)<<7));
                      data7[k] = data7[k+1] >> 1;   data7[k] = (data7[k] | ((data8[k] & 0x01)<<7));
                      data8[k] = data8[k+1] >> 1;   data8[k] = (data8[k] | ((data9[k] & 0x01)<<7));
                      data9[k] = data9[k+1] >> 1;   data9[k] = (data9[k] | ((data10[k] & 0x01)<<7));
                      data10[k] = data10[k+1] >> 1;   data10[k] = (data10[k] | ((data11[k] & 0x01)<<7));
                      data11[k] = data11[k+1] >> 1;
                    }
         }
}
 */
void DotMatrix_minDiagonalUpScroll(int speedFactor){
          unsigned int monitor, monitor1;
          unsigned char k, kk, sel;
          for(monitor1=0; monitor1<10; monitor1++){
                  for(monitor=0; monitor<speedFactor; monitor++)
                       displays();
                  for(k=0; k<8; k++)
                  {
                       sel=0;
                       for(kk=0; kk<((size-8)/8); kk++)
                       {
                           if(k == 7)
                               mainData[k+sel] = 0;
                           else {
                               mainData[k+sel] = mainData[(k+1) + sel] >> 1;
                               mainData[k+sel] = mainData[k+sel] | ((mainData[(k+8) + sel] & 0x01)<<7);
                           }
                         sel = sel+8;
                        }
                 }
           }
  }

#endif  //#ifndef _DotMatrix_8x8_H_	