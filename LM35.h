
/**************************************************************************

LM35 TEMPERATURE LIBRARY
for temperature readings
Version: 	2.0 BETA
Release date:	

Author:
(C)2018 Ogboye Godwin

Modified:
(C)2018 None

FileName:     	LM35.h
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
 
/*

Example:


#include <CloudX/M633.h>
#include <CloudX/LCD.h>
#include <CloudX/LM35.h>
#include <CloudX/stdlib.h>


char *txt;
float measuredTemp;

setup(){
    LCD_setting(1, 2, 3, 4, 5, 6); //RS, EN, D4, D5, D6, D7
   
    loop(){
        measuredTemp = Read_temperature(0);             //reads temperature off channel A0
        txt          = floatTostr((measuredTemp + 2));  //+2 => LM35 hardware configuration offset
        txt[5] = '\0';
        LCD_cmd(clear);
        LCD_writeText(1, 3, "Temp Sensor");
        LCD_writeText(2, 1, "Temp: ");
        LCD_writeTextCP(txt);
        LCD_writeCP(223);     //writes degree symbol
        LCD_writeCP('C');     //writes the Celsius character
        
    }
}
 
 */
 
#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _LM35_H_
#define _LM35_H_

#include <CloudX/ADC.h>


//----------------------------------------------------------------------------------
//oneDegRise = ((10*1023)/5000) => 2.046
//LM35Data = (LM35Data / oneDegRise) => (LM35Data / 2.046) or (LM35Data * 0.488759) 
//----------------------------------------------------------------------------------

 
int LM35Data;
float temparature;

LM35_read(char analogPin){
        Analog_setting();
        LM35Data = Analog_read(analogPin);
        temparature = (LM35Data * 0.488759);
        return temparature;
}

#endif  //#ifndef _LM35_H_