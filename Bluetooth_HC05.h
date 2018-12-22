
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 
 * File:   Bluetooth_HC05.h
 * Version: 1.0
 * Author: 2mee McAlmighty (Oyemade Tumi)
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: Bluetooth Library For HC-05 Bluetooth Transceiver Module.
 
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
************************************************************************************************************/


/*

Example:


#include <CloudX\M633.h>
#include <CloudX\Bluetooth_HC05.h>

setup(){
           //setup here
           
            Bluetooth_begin(9600);
            pin1Mode = OUTPUT;
            pin1 = LOW;
            Bluetooth_writeText("CloudX With\r");
            Bluetooth_writeText("HC-05 Bluetooth Module\r");

 loop(){
           //Program here
           
         char dataByte;
            
         dataByte = Bluetooth_read();
         Bluetooth_write('\r');            //enters a new line
            
    //-------------------------------------------------------------------------------------------
    //The routine below simply toggles an LED on and off depending on the character data sent in
    //-------------------------------------------------------------------------------------------
        if((dataByte is '1') or (dataByte is 'A') or (dataByte is 'a'))
        {
            pin1 = HIGH;
            Bluetooth_writeText("LED: ON");
        }
        if((dataByte is '2') or (dataByte is 'B') or (dataByte is 'b'))
        {
            pin1 = LOW;
            Bluetooth_writeText("LED: OFF");
        }
            Bluetooth_write('\r');
      }
 }

*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _Bluetooth_HC05_H_
#define _Bluetooth_HC05_H_

#include <CloudX/Serial.h>


#define Bluetooth_begin     Serial_begin
#define Bluetooth_write     Serial_write
#define Bluetooth_available Serial_available
#define Bluetooth_read      Serial_read

#endif   //#ifndef _Bluetooth_HC05_H_