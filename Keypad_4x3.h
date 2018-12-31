/**************************************************************************

KEYPAD LIBRARY
for keypad input controls
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 None

FileName:     	keypad_4x3.h
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

#ifndef _KeyPad4x3_H_
#define _KeyPad4x3_H_

         char Roww1,Roww2,Roww3,Coll1,Coll2,Coll3,Coll4,stats;

void keypad4x3_Setting(char Row1,char Row2,char Row3,char Col1,char Col2,char Col3, char Col4, char statess)
{
    pinMode(Row1,OUTPUT); pinMode(Row2,OUTPUT); pinMode(Row3,OUTPUT); 
    pinMode(Col1,INPUT); pinMode(Col2,INPUT); pinMode(Col3,INPUT);  pinMode(Col4,INPUT);
    
   Roww1 = Row1; Roww2= Row2; Roww3 = Row3; Coll1=Col1; Coll2=Col2;  Coll3=Col3; Coll4=Col4;
   stats = statess;
    
   }
#define Row1 Roww1
#define Row2 Roww2
#define Row3 Roww3
#define Col1 Coll1
#define Col2 Coll2
#define Col3 Coll3
#define Col4 Coll4
#define states stats


Get_keypad4x3(){
            char kkey = 0;

                      if(states is HIGH){
            PinSelect(Row1 ,LOW);
            PinSelect(Row2 ,HIGH);
            PinSelect(Row3,HIGH);

            if(readPin(Col1)  is LOW){ delayMs(200);   kkey = '1';}
            if(readPin(Col2)  is LOW){ delayMs(200);  kkey = '4';}
            if(readPin(Col3)  is LOW){ delayMs(200);  kkey = '7';}
            if(readPin(Col4)  is LOW){ delayMs(200);  kkey = '*';}
            delayMs(1);

             PinSelect(Row1 ,HIGH);
            PinSelect(Row2 ,LOW);
            PinSelect(Row3,HIGH);

            if(readPin(Col1) is LOW){ delayMs(200);   kkey = '2';}
            if(readPin(Col2) is LOW){ delayMs(200);  kkey = '5';}
            if(readPin(Col3)  is LOW){ delayMs(200);  kkey = '8';}
            if(readPin(Col4)  is LOW){ delayMs(200);  kkey = '0';}
             delayMs(1);


             PinSelect(Row1 ,HIGH);
            PinSelect(Row2 ,HIGH);
            PinSelect(Row3,LOW);

            if(readPin(Col1) is LOW){ delayMs(200);   kkey = '3';}
            if(readPin(Col2) is LOW){ delayMs(200);  kkey = '6';}
            if(readPin(Col3) is LOW){ delayMs(200);  kkey = '9';}
            if(readPin(Col4) is LOW){ delayMs(200);  kkey = '#';}
             delayMs(1);
              PinSelect(Row1 ,HIGH);
            PinSelect(Row2 ,HIGH);
            PinSelect(Row3,HIGH);
            }

        if(states is LOW){
            PinSelect(Row1, HIGH);
            PinSelect(Row2, LOW);
            PinSelect(Row3 , LOW);
            
            if(readPin(Col1)  is HIGH){ delayMs(200);   kkey = '1';}
            if(readPin(Col2)  is HIGH){ delayMs(200);  kkey = '4';}
            if(readPin(Col3)  is HIGH){ delayMs(200);  kkey = '7';}
            if(readPin(Col4)  is HIGH){ delayMs(200);  kkey = '*';}
            delayMs(1);
             
            PinSelect(Row1 ,LOW);
            PinSelect(Row2 ,HIGH);
            PinSelect(Row3 , LOW);
            
            if(readPin(Col1) is HIGH){ delayMs(200);   kkey = '2';}
            if(readPin(Col2) is HIGH){ delayMs(200);  kkey = '5';}
            if(readPin(Col3)  is HIGH){ delayMs(200);  kkey = '8';}
            if(readPin(Col4)  is HIGH){ delayMs(200);  kkey = '0';}
             delayMs(1);
             
            PinSelect(Row1 , LOW);
            PinSelect(Row2 , LOW);
            PinSelect(Row3 , HIGH);
            
            if(readPin(Col1) is HIGH){delayMs(200);   kkey = '3';}
            if(readPin(Col2) is HIGH){ delayMs(200);  kkey = '6';}
            if(readPin(Col3) is HIGH){ delayMs(200);  kkey = '9';}
            if(readPin(Col4) is HIGH){ delayMs(200);  kkey = '#';}
             delayMs(1);
            PinSelect(Row1 , LOW);
            PinSelect(Row2 , LOW);
            PinSelect(Row3 , LOW);
            }
            if(kkey !=0) return kkey;
            else return  kkey;            
}

#endif    //#ifndef _KeyPad4x3_H_