
/**************************************************************************

BLUETOOTH LIBRARY
for serial bluetooth communications
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 2mee McAlmighty (Oyemade Tumi)


Modified:
(C)2018 None

FileName:     	Bluetooth_HC05.h
Dependencies:	None
Compiler:  	CloudX C Compiler
Company:        cloudx.ng | www.bytehubembed.com
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

***********************************************************************************/

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