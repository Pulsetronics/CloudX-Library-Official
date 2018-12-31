/**************************************************************************

R30x FINGERPRINT MODULE LIBRARY
for fingerprint detection
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Ayinde Olayiwola


Modified:
(C)2018 None

FileName:     	Fingerprint_R30X.h
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


#ifndef _R30X_H_
#define _R30X_H_

#include <CloudX\Serial.h>

////*********************** Fingerprint Code ***************************//
////     RED     -  VCC
////     BLACK   -  GND
////     YELLOW  -  TX
////     BLUE    -  RX
////*********************** FingerPrint PREDEFINE **********************//

#define FINGERPRINT_OK 0x00
#define FINGERPRINT_PACKETRECIEVEERR 0x01
#define FINGERPRINT_NOFINGER 0x02
#define FINGERPRINT_IMAGEFAIL 0x03
#define FINGERPRINT_IMAGEMESS 0x06
#define FINGERPRINT_FEATUREFAIL 0x07
#define FINGERPRINT_NOMATCH 0x08
#define FINGERPRINT_NOTFOUND 0x09
#define FINGERPRINT_ENROLLMISMATCH 0x0A
#define FINGERPRINT_BADLOCATION 0x0B
#define FINGERPRINT_DBRANGEFAIL 0x0C
#define FINGERPRINT_UPLOADFEATUREFAIL 0x0D
#define FINGERPRINT_PACKETRESPONSEFAIL 0x0E
#define FINGERPRINT_UPLOADFAIL 0x0F
#define FINGERPRINT_DELETEFAIL 0x10
#define FINGERPRINT_DBCLEARFAIL 0x11
#define FINGERPRINT_PASSFAIL 0x13
#define FINGERPRINT_INVALIDIMAGE 0x15
#define FINGERPRINT_FLASHERR 0x18
#define FINGERPRINT_INVALIDREG 0x1A
#define FINGERPRINT_ADDRCODE 0x20
#define FINGERPRINT_PASSVERIFY 0x21

#define FINGERPRINT_STARTCODE 0xEF01

#define FINGERPRINT_COMMANDPACKET 0x1
#define FINGERPRINT_DATAPACKET 0x2
#define FINGERPRINT_ACKPACKET 0x7
#define FINGERPRINT_ENDDATAPACKET 0x8

#define FINGERPRINT_TIMEOUT 0xFF
#define FINGERPRINT_BADPACKET 0xFE

#define FINGERPRINT_GETIMAGE 0x01

#define FINGERPRINT_IMAGE2TZ 0x02
#define FINGERPRINT_REGMODEL 0x05
#define FINGERPRINT_STORE 0x06
#define FINGERPRINT_LOAD 0x07
#define FINGERPRINT_UPLOAD 0x08
#define FINGERPRINT_DELETE 0x0C
#define FINGERPRINT_EMPTY 0x0D
#define FINGERPRINT_VERIFYPASSWORD 0x13
#define FINGERPRINT_HISPEEDSEARCH 0x1B
#define FINGERPRINT_TEMPLATECOUNT 0x1D

const char verifyPassword[] =    {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1B};
const char captureFinger[]=      {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01,0x00,0x05};
const char searchFinger[]=       {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x08,0x1B,0x01,0x00,0x00,0x00,0xA3,0x00,0xC8};
const char registerTemplate[]=   {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x05,0x00,0x09};
const char storeFinger[]=        {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x06,0x06,0x02,0x00};
const char Img2Char1[]=          {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x01,0x00,0x08};
const char Img2Char2[]=          {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x02,0x00,0x09};
const char deleteFinger[]=       {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x0C,0x00};
const char emptyFinger[]=        {0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x0D,0x00,0x11} ;

char fingerprintStore[20];

#include <stdbool.h>
     char tempStore;

R30X_timeOut(){   
       float timeOutCount = 0; char recCount=0;
          while(recCount<12){
              if (PIR1bits.RCIF){
                   fingerprintStore[recCount]   = RCREG;
                   PIR1bits.RCIF = 0;
                   recCount++;
                   timeOutCount = 0;
               }
               if(timeOutCount++ > 10000) { PIR1bits.RCIF = 0; RCSTAbits.CREN = 0; RCSTAbits.CREN = 1; fingerprintStore[9]= FINGERPRINT_TIMEOUT; recCount= 12; break;}  
           }
   }   
fingerprintClear(){
    for(char clears=0; clears<20; clears++) fingerprintStore[clears]=0xFF;
}
 

char R30X_capture(){
    char R305Result = -1; char tempCount;
                    fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);
                    delay(5);
                    Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                    delay(5);
                    for(tempCount=0; tempCount<10; tempCount++){
                        Serial_write(captureFinger[tempCount]); 
                        delay(5);
                        }
                    tempCount = 0; 
                    R30X_timeOut();   
                               if(fingerprintStore[9]== FINGERPRINT_TIMEOUT) R305Result = FINGERPRINT_TIMEOUT; 
                         else  if(fingerprintStore[9]== FINGERPRINT_OK) R305Result = FINGERPRINT_OK;
                         else  if(fingerprintStore[9]== FINGERPRINT_VERIFYPASSWORD) R305Result= FINGERPRINT_VERIFYPASSWORD;
                         else  if(fingerprintStore[9]== FINGERPRINT_PACKETRECIEVEERR) R305Result= FINGERPRINT_PACKETRECIEVEERR;
                         else  if(fingerprintStore[9]== FINGERPRINT_NOFINGER) R305Result= FINGERPRINT_NOFINGER;
                
                    return R305Result; 
}

char R30X_verify(){
                    char R305Result = -1; char tempCount;
                    fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);
                    
                    delay(5);
                    Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                    delay(5);
                    for(tempCount=0; tempCount < 14; tempCount++){
                        Serial_write(verifyPassword[tempCount]); 
                        delay(5);
                        }
                    tempCount = 0;     
                    R30X_timeOut();     
                               if(fingerprintStore[9]==     FINGERPRINT_TIMEOUT) R305Result = FINGERPRINT_TIMEOUT; 
                          else if(fingerprintStore[9]== FINGERPRINT_OK) R305Result = FINGERPRINT_OK;
                         else  if(fingerprintStore[9]==FINGERPRINT_VERIFYPASSWORD) R305Result= FINGERPRINT_VERIFYPASSWORD;
                         else  if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR) R305Result= FINGERPRINT_PACKETRECIEVEERR;
                         else  if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                
                    return R305Result; 
}
   //conflicting declarations for variable "Collect_Finger_Image" 
    //can't return functions
      
char R30X_search(){
                    char R305Result = -1; char tempCount;
                    fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                      Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                    for(tempCount=0; tempCount<15; tempCount++){
                        Serial_write(searchFinger[tempCount]); 
                       }
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_NOTFOUND) R305Result =  FINGERPRINT_NOTFOUND;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                     if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    
                    return R305Result;
                 }            
 
              
char R30X_enrolTemplateOne(){
                    fingerprintClear();
                   
                    while(R30X_capture() != FINGERPRINT_OK);
                   char R305Result = -1; char tempCount;
                  fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                      Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                      for(tempCount=0; tempCount<11; tempCount++){
                          Serial_write(Img2Char1[tempCount]); 
                       }
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_NOTFOUND) R305Result =  FINGERPRINT_NOTFOUND;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                    if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    
                    return R305Result;
}
              
char R30X_enrolTemplateTwo(){
                    fingerprintClear();
                    while(R30X_capture() != FINGERPRINT_OK);
                    char R305Result = -1; char tempCount;
                    fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                      Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                      for(tempCount=0; tempCount<11; tempCount++){
                          Serial_write(Img2Char2[tempCount]); 
                       }
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_NOTFOUND) R305Result =  FINGERPRINT_NOTFOUND;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                     if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    
                    return R305Result;
}
              

char R30X_registerTemplate(){
                    char R305Result = -1; char tempCount;
                    fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                    Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                     for(tempCount=0; tempCount<10; tempCount++){
                          Serial_write(registerTemplate[tempCount]); 
                       }
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_ENROLLMISMATCH) R305Result =  FINGERPRINT_ENROLLMISMATCH;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                    if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                   return R305Result; 
}
                
char R30X_store(unsigned int r305Address){
                                char R305Result = -1; char tempCount;
                                R30X_registerTemplate();
                               fingerprintClear();
                               Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                               Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                     for(tempCount=0; tempCount<10; tempCount++){
                          Serial_write(storeFinger[tempCount]); 
                       }
                      Serial_write(r305Address);
                      Serial_write(0x00);
                      Serial_write(0x0F + r305Address);
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_BADLOCATION) R305Result =  FINGERPRINT_BADLOCATION;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                    if(fingerprintStore[9]==FINGERPRINT_FLASHERR ) R305Result= FINGERPRINT_FLASHERR ;
                    if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    return R305Result;
}
                
char R30X_delete(unsigned char deleteLocation){
                   char R305Result = -1; char tempCount;
                  fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                      Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                      for(tempCount=0; tempCount<9; tempCount++){
                          Serial_write(deleteFinger[tempCount]); 
                       }
                      Serial_write(deleteLocation);
                      Serial_write(0x00);
                      Serial_write(0x01);
                      Serial_write(0x00);
                      Serial_write(0x14+1+deleteLocation);
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_DELETEFAIL) R305Result =  FINGERPRINT_DELETEFAIL;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                    if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    
                    return R305Result;
}
                
char R30X_empty(){
                   char R305Result = -1; char tempCount;
                   fingerprintClear();
                    Serial_write((FINGERPRINT_STARTCODE & 0xFF00)>>8);  
                      Serial_write(FINGERPRINT_STARTCODE & 0x00FF);
                      for(tempCount=0; tempCount<10; tempCount++){
                          Serial_write(emptyFinger[tempCount]); 
                       }
                    tempCount = 0;    
                    R30X_timeOut();    
                    if(fingerprintStore[9]==FINGERPRINT_OK) R305Result= FINGERPRINT_OK;
                    if(fingerprintStore[9]==FINGERPRINT_DBCLEARFAIL) R305Result =  FINGERPRINT_DBCLEARFAIL;
                    if(fingerprintStore[9]==FINGERPRINT_PACKETRECIEVEERR ) R305Result= FINGERPRINT_PACKETRECIEVEERR ;
                    if(fingerprintStore[9]==FINGERPRINT_TIMEOUT) R305Result= FINGERPRINT_TIMEOUT;
                    
                    return R305Result;
}

#endif   //#ifndef _R30X_H_