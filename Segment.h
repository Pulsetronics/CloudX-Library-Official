
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   Segment.h
 * Version: 1.01
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the segment. 

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
  Programmer: AYINDE OLAYIWOLA
  Date:       24 / 5 / 2017
  Time:       09 : 36 AM
  Lab:        Mbed Studio 
  Version:    1.01


Example 1:

#include <CloudX/M633.h>
#include <CloudX/Segment.h>

         int NumberOfDigit = 4;
         char segmentDataPins[] = {1, 2, 3, 4, 5, 6, 7, 8};
         char segmentScanPins[] = {9, 10, 11, 12};

 
 setup(){
           //setup here
 
         Segment_setting(CCathode,NumberOfDigit,segmentScanPins,segmentDataPins);
         
    loop(){
           //Program here 
           
           Segment_writeText("4567", 100);  // (text to display, time)
         
      }
} 
   
   

Example 2:  For A Single Segment Display
*** NB:
     The Common Anode or Common Cathode pin should be pulled up or pulled down accordingly. ***
     
     
     
#include <CloudX/M633.h>
#include <CloudX/Segment.h>
#include <stdlib.h>
 

         int NumberOfDigit = 1;
         char segmentDataPins[]= {1, 2, 3, 4, 5, 6, 7, NULL};
         char segmentScanPins[]= 0;

         
  setup(){
           //setup here
 
         Segment_setting(CCathode, NumberOfDigit, segmentScanPins, segmentDataPins);
         
   loop(){
           //Program here  
           
           Segment_write('4', 100);  // (character to display, time)
           
        }
}

*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _Segment_H_
#define _Segment_H_

////////////////////////////////////////////////////////////
//Segment Configuration defined libary
////////////////////////////////////////////////////////////
#define  CCathode  0
#define  CAnode  1

char segScan[9], segData[9], _SC;
void Segment_setting(char segType,unsigned char segNoDigit, unsigned char *segScanA,unsigned char *segDataA){

#define Ten 0x3A
                 _SC= segType; char segLoader;
                 
                     for(segLoader=0; segLoader<9; segLoader++) {
                         segData[segLoader]= segDataA[segLoader];
                       }
                 for(segLoader=0; segLoader<segNoDigit; segLoader++) segScan[segLoader]= segScanA[segLoader];

                 segLoader=0;
                while(segLoader < 8)
                          pinMode(segData[segLoader++],OUTPUT);
                 segLoader=0;
                   while(segScan[segLoader]!=0)
                          pinMode(segScan[segLoader++],OUTPUT);

}

unsigned char segDispData(unsigned char segByte){
    if(_SC==CCathode){
        switch(segByte){
            case 0    :   return 0x3F;
            case 1    :   return 0x06;
            case 2    :   return 0x5B;
            case 3    :   return 0x4F;
            case 4    :   return 0x66;
            case 5    :   return 0x6D;
            case 6    :   return 0x7D;
            case 7    :   return 0x07;
            case 8    :   return 0x7F;
            case 9    :   return 0x6F;
            case 'A'  :   return 0x77;
            case 'a'  :   return 0x57;
            case 'b'  :   return 0x7C;
            case 'C'  :   return 0x39;
            case 'c'  :   return 0x58;
            case 'd'  :   return 0x5E;
            case 'E'  :   return 0x79;
            case 'e'  :   return 0x7B;
            case 'F'  :   return 0x71;
            case 'f'  :   return 0x71;
            case 'G'  :   return 0x3D;
            case 'g'  :   return 0x6F;
            case 'H'  :   return 0x76;
            case 'h'  :   return 0x74;
            case 'I'  :   return 0x06;
            case 'i'  :   return 0x06;
            case 'J'  :   return 0x1E;
            case 'j'  :   return 0x1E;
            case 'L'  :   return 0x38;
            case 'l'  :   return 0x3C;
            case 'n'  :   return 0x54;
            case 'O'  :   return 0x3F;
            case 'o'  :   return 0x5C;
            case 'P'  :   return 0x73;
            case 'p'  :   return 0x73;
            case 'q'  :   return 0x67;
            case 'r'  :   return 0x50;
            case 'S'  :   return 0x6D;
            case 's'  :   return 0x6D;
            case 't'  :   return 0x78;
            case 'U'  :   return 0x3E;
            case 'u'  :   return 0x1C;
            case 'Y'  :   return 0x66;
            case 'y'  :   return 0x6E;
            case 'Z'  :   return 0x5B;
            case 'z'  :   return 0x5B;
            case ' '  :   return 0x00;
            case ','  :   return 0x0C;
            case ';'  :   return 0x0D;
            case ':'  :   return 0x09;
            case '?'  :   return 0x53;
            case '_'  :   return 0x08;
            case '-'  :   return 0x40;
            case '='  :   return 0x41;
            case '\'' :   return 0x02;
            case '\"' :   return 0x22;
            case '/'  :   return 0x52;
            case '|'  :   return 0x30;
            case '^'  :   return 0x23;
            case '('  :   return 0x39;
            case ')'  :   return 0x0F;
            case '['  :   return 0x39;
            case ']'  :   return 0x0F;
            default:    return 0x3F;
        }
    }
    
    if(_SC==CAnode){
        switch(segByte){
            case 0    :   return 0xC0;
            case 1    :   return 0xF9;
            case 2    :   return 0xA4;
            case 3    :   return 0xB0;
            case 4    :   return 0x99;
            case 5    :   return 0x92;
            case 6    :   return 0x82;
            case 7    :   return 0xF8;
            case 8    :   return 0x80;
            case 9    :   return 0x90;
            case 'A'  :   return 0x88;
            case 'a'  :   return 0xA0;
            case 'b'  :   return 0x83;
            case 'C'  :   return 0xC6;
            case 'c'  :   return 0xA7;
            case 'd'  :   return 0xA1;
            case 'E'  :   return 0x86;
            case 'e'  :   return 0x84;
            case 'F'  :   return 0x8E;
            case 'f'  :   return 0x8E;
            case 'G'  :   return 0xC2;
            case 'g'  :   return 0x90;
            case 'H'  :   return 0x89;
            case 'h'  :   return 0x8B;
            case 'I'  :   return 0xF9;
            case 'i'  :   return 0xF9;
            case 'J'  :   return 0xE1;
            case 'j'  :   return 0xE1;
            case 'L'  :   return 0xC7;
            case 'l'  :   return 0xC3;
            case 'n'  :   return 0xAB;
            case 'O'  :   return 0xC0;
            case 'o'  :   return 0xA3;
            case 'P'  :   return 0x8C;
            case 'p'  :   return 0x8C;
            case 'q'  :   return 0x98;
            case 'r'  :   return 0xAF;
            case 'S'  :   return 0x92;
            case 's'  :   return 0x92;
            case 't'  :   return 0x87;
            case 'U'  :   return 0xC1;
            case 'u'  :   return 0xE3;
            case 'Y'  :   return 0x99;
            case 'y'  :   return 0x91;
            case 'Z'  :   return 0xA4;
            case 'z'  :   return 0xA4;
            case ' '  :   return 0xFF;
            case ','  :   return 0xF3;
            case ';'  :   return 0xF2;
            case ':'  :   return 0xF6;
            case '?'  :   return 0xAC;
            case '_'  :   return 0xF7;
            case '-'  :   return 0xBF;
            case '='  :   return 0xBE;
            case '\'' :   return 0xFD;
            case '\"' :   return 0xDD;
            case '/'  :   return 0xAD;
            case '|'  :   return 0xCF;
            case '^'  :   return 0xDC;
            case '('  :   return 0xC6;
            case ')'  :   return 0xF0;
            case '['  :   return 0xC6;
            case ']'  :   return 0xF0;
            default:  return 0xC0;
        }
    }
}


void segClear(){
    char segClrCounter=0;
    while(segScan[segClrCounter] != 0){
        if(_SC==CCathode)PinSelect(segScan[segClrCounter++], HIGH);
        if(_SC==CAnode)PinSelect(segScan[segClrCounter++], LOW);
    }
             while(segClrCounter<8)
                 PinSelect(segScan[segClrCounter++], (0x00 & 0x01));

}

void Segment_write(unsigned char charSegDisp, unsigned long segDel){
       char segDatapnter=0, segStore;
       while(segDel-- !=0){
            segStore = charSegDisp;
            if((segStore >= '0') && (segStore <= '9'))
               segStore = segStore - 0x30;
            segStore = segDispData(segStore);
            
            while(segDatapnter < 8) {
                PinSelect(segData[segDatapnter++], (segStore & 0x01));
                segStore = segStore>>1;
              }
            delayMs(2);
          }
    }



    void Segment_writeText(unsigned char *segDisp, unsigned long segDel){
    unsigned char count=0;
    unsigned  char *pointar;
    pointar = segDisp;  
    while(*segDisp++ != '.')  {
       if(*segDisp is '\0') {
           count = 0;
           break; }
       count++; }
    segDisp  = pointar;  
    while(segDel-- !=0){
    char segScanpnter=0, segDatapnter=0, stringPointer=0, segStore;
        while(segScan[segScanpnter] != 0) {
            segClear();
            segDatapnter=0;
                              
            segStore = segDisp[stringPointer];
            stringPointer++;
            if((segStore >= '0') && (segStore <= '9'))
               segStore = segStore - 0x30;
            else if(segStore is '.') 
               continue;
              
            if((count) && (stringPointer-1) is (count-1)) {
                  if(_SC==CCathode) segStore = segDispData(segStore) | 0x80;
                  else if(_SC==CAnode) segStore = segDispData(segStore) - 0x80;
                }
           else
               segStore = segDispData(segStore);
           while(segDatapnter < 8) {
                PinSelect(segData[segDatapnter++],(segStore&0x01));
                segStore = segStore>>1;}
            
            if(_SC==CCathode) PinSelect(segScan[segScanpnter++],LOW);
            if(_SC==CAnode) PinSelect(segScan[segScanpnter++],HIGH);

            delayMs(2);
          }
    }
    segClear();
    }
	
	#endif  //#ifndef _Segment_H_