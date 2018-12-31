
/**************************************************************************

DHT11 LIBRARY
for digital temperature and humidity sensor
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Fidel


Modified:
(C)2018 None


FileName:     	DHT11.h
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
 
****************************************************************************************************/


#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _DHT11_H
#define _DHT11_H


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

#endif