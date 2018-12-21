
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   DHT11.h
 * Version: 1.0
 * Website: HTtp://www.makeelectronics.ng or HTtp://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the DHT11 Temperature Humdity Sensor. 

This code has been developed and tested on CloudX microcontroller boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link HTtp://www.makeelectronics.ng for awesome tutorials on CloudX,ARM,Robotics,RTOS,IOT.
ByteHub Embedded invests substantial time and effort developing open source HW and SW tools,
to support consider buying the CloudX microcontroller boards.
 
The ByteHub Embedded libraries and examples are licensed under the terms of the new-bsd license
(two-clause bsd license). See also: HTtp://www.opensource.org/licenses/bsd-license.php

BYTEHUB EMEBEDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE 
INFORMATION RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyrigHT notices appear in all copies 
and that both those copyrigHT notices and this permission notice appear in supporting documentation.
************************************************************************************************************/


/*

Example:


#include <CloudX/M633.h>
#include <CloudX/DHT11.h>
#include <CloudX/LCD.h>

char temperature[] = "Temp = 00.0 C";
char humidity[]    = "RH   = 00.0 %";

unsigned int tempByte1, tempByte2, RhByte1, RhByte2, sumCheck;

setup(){
           //setup here
           
            DHT11_init(7);           //sets up pin7 for the DHT data signal
            
            LCD_setting(1, 2, 3, 4, 5, 6);  //RS, EN, D4, D5, D6, D7
            LCD_cmd(clear);
            LCD_writeText(1, 3, "DHT11 Sensor");
            delayMs(1000);
 

loop(){
           //Program here          
           
           
          if(DHT11_write()){
               RhByte1   = DHT11_read(); //reads in integer value of the Relative Humidity
               
               RhByte2   = DHT11_read(); //reads in mantissa value of the Relative Humidity
               
               tempByte1 = DHT11_read(); //reads in integer value of the Temperature
               
               tempByte2 = DHT11_read(); //reads in mantissa value of the Temperature
               
               sumCheck  = DHT11_read(); //reads in the error-check value 
               
         
               
            //-----------------------------------------------------------------------------
            //The below routine checks for data error by comparing the sum of the data off 
            //the preceding four reads with that coming from sumCheck.
            //
            //The sensor data are finally displayed, if everything turns out error-free.
            //-----------------------------------------------------------------------------  
             if (sumCheck == ((RhByte1 + RhByte2 + tempByte1 + tempByte2) & 0xFF)) {
                 temperature[7]  = (tempByte1 / 10)  + 48; 
                 temperature[8]  = (tempByte1 % 10)  + 48;
                 temperature[10] = (tempByte2 / 10)  + 48;
                 humidity[7]  = (RhByte1 / 10) + 48;
                 humidity[8]  = (RhByte1 % 10) + 48;
                 humidity[10] = (RhByte2 / 10) + 48;
                 temperature[11] = 223;                   //degree symbol
                 LCD_cmd(clear);
                 LCD_writeText(1, 1, temperature);
                 LCD_writeText(2, 1, humidity);
              }
             else { 
                LCD_cmd(clear);
                LCD_writeText(1, 1, "Sum-Check Error!");
                LCD_writeText(2, 1, "Trying Again ...");
              }
           }
   
            else 
            {
                LCD_cmd(clear);
                LCD_writeText(1, 1, "Response Error!");
            }
   
     delayMs(1000);
     
    }
 }
 
*/



#define ok 1
#define error 0

char _dataPin;

void DHT11_init(char DHTPin){
    pinMode(DHTPin, INPUT);
    _dataPin = DHTPin;
}
 
void signalStart(){
     pinMode(_dataPin, OUTPUT);     
     digitalWrite(_dataPin, LOW);     
     delayMs(18);
     digitalWrite(_dataPin, HIGH);          
     delayUs(30);
     pinMode(_dataPin, INPUT);    
  } 

 unsigned char DHT11_write() {
     unsigned char _test = 0;
     signalStart(); 
        delayUs(40);
        if (readPin(_dataPin) == 0)
        {
            delayUs(80);
            if (readPin(_dataPin) == 1)   
                _test = 1;   
            delayUs(40);
         }
          if(_test) return ok;
}

 unsigned int DHT11_read(){
    unsigned int _data = 0;
        pinMode(_dataPin, INPUT);
        for(byte ii=0; ii<8; ii++)
        {
            while(!readPin(_dataPin));               
              delayUs(30);
              if(readPin(_dataPin) == 0)    
                  _data = _data & ~(1<<(7-ii));   
              else
                {
                    _data = _data | (1<<(7-ii));   
                    while(readPin(_dataPin));        
                }  
        }
         return _data;
 }

