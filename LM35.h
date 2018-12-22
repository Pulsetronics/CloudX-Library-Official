
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:         LM35.h
 * Version:      1.1
 * Author:       Ogboye Godwin
 * Improved-On:  Bytehub Embed-Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the LM35 Temparature Sensor. 

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