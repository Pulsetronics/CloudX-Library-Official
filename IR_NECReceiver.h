
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:     IR_NECReceiver.h
 * Version:  1.0
 * Author:   Oyemade Tumi
 * Created:  July 27, 2018, 2:20 PM
 * Website:  http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the NEC Infra-Red Receiver. 

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
******************************************************************************************************/

 
/*

Example:


#include <CloudX/M633.h>
#include <CloudX/IR_NECReceiver.h>
#include <CloudX/Serial.h>
#include <CloudX/stdlib.h>


char dDatta[40];
long buttonPress;

SpecialChaserB(){
    portWrite(1, 0b10000001);
    delayMs(200);
    portWrite(1, 0b01000010);
    delayMs(200);
    portWrite(1, 0b00100100);
    delayMs(200);
    portWrite(1, 0b00011000);
    delayMs(200);
}
SpecialChaserF(){
    portWrite(1, 0b00011000);
    delayMs(200);
    portWrite(1, 0b00100100);
    delayMs(200);
    portWrite(1, 0b01000010);
    delayMs(200);
    portWrite(1, 0b10000001);
    delayMs(200);

}



setup(){
        //setup here
        
        Serial_begin(9600);
        IR_init(16);
        
        pin1Mode=OUTPUT; pin1 = OFF;
        pin2Mode=OUTPUT; pin2 = OFF;
        pin3Mode=OUTPUT; pin3 = OFF;
        pin4Mode=OUTPUT; pin4 = OFF;
        pin5Mode=OUTPUT; pin5 = OFF;
        pin6Mode=OUTPUT; pin6 = OFF;
        pin7Mode=OUTPUT; pin7 = OFF;
        pin8Mode=OUTPUT; pin8 = OFF;



    loop(){
        //Program here

        while(pin16);
        buttonPress = IR_read();
        ultoa(dDatta, buttonPress, HEX);


        if (buttonPress is 0xFFA25D) 
            SpecialChaserF();                  //CH-
        else if (buttonPress is 0xFF629D) 
            SpecialChaserB();                  //CH
        else if (buttonPress is 0xFFE21D) 
            Serial_writeText("CH+");           //CH+
        else if (buttonPress is 0xFF22DD) 
            Serial_writeText("PREV");          //PREV
        else if (buttonPress is 0xFF02FD) 
            Serial_writeText("NEXT");          //NEXT
        else if (buttonPress is 0xFFC23D) 
            Serial_writeText("PLAY/PAUSE");    //PLAY/PAUSE
        else if (buttonPress is 0xFFE01F) 
            Serial_writeText("VOL-");          //VOL-
        else if (buttonPress is 0xFFA857) 
            Serial_writeText("VOL+");          //VOL+
        else if (buttonPress is 0xFF906F) 
            Serial_writeText("EQ");            //EQ
        else if (buttonPress is 0xFF6897) 
            Serial_write('0');                 //0
        else if (buttonPress is 0xFF9867) 
            Serial_writeText("100+");          //100+
        else if (buttonPress is 0xFFB04F) 
            Serial_writeText("200+");          //200+
        else if (buttonPress is 0xFF30CF) 
            pin1 = ~pin1;                      //1
        else if (buttonPress is 0xFF18E7) 
            pin2 = ~pin2;                      //2
        else if (buttonPress is 0xFF7A85) 
            pin3 = ~pin3;                      //3
        else if (buttonPress is 0xFF10EF) 
            pin4 = ~pin4;                      //4
        else if (buttonPress is 0xFF38C7) 
            pin5 = ~pin5;                      //5
        else if (buttonPress is 0xFF5AA5) 
            pin6 = ~pin6;                      //6
        else if (buttonPress is 0xFF42BD) 
            pin7 = ~pin7;                      //7
        else if (buttonPress is 0xFF4AB5) 
            pin8 = ~pin8;                      //8
        else if (buttonPress is 0xFF52AD) 
            PORTB = ~PORTB;                    //9


        Serial_write('\r');
        Serial_write('\n');

        delayMs(300);

    }

}


*/


#ifndef _NECReceiver_H_
#define _NECReceiver_H_

char _pin;

IR_init(char pin){
    pinMode(pin , INPUT);
    _pin = pin;
}

long IR_read(){
  unsigned int timer = 0, i;
  unsigned long IR_code;

  while((readPin(_pin) == LOW) && (timer < 200)){
    timer++;
    delayus(50);
  }

  timer = 0;

  while((readPin(_pin)==HIGH) && (timer < 100)){
    timer++;
    delayus(50);
  }
  
  for(i = 0; i < 32; i++){
    timer = 0;
    while((readPin(_pin) == LOW) && (timer < 14)){
      timer++;
      delayus(50);
    }

    timer = 0;
    while((readPin(_pin)==HIGH) && (timer < 40)){
      timer++;
      delayus(50);
    }

    if( timer > 20)
        IR_code=(IR_code<<1)|1;              
    else
        IR_code=IR_code<<1;                        
  }
  return IR_code;
}

#endif  //#ifndef _NECReceiver_H_