/**************************************************************************

EEPROM LIBRARY
for internal ROM storage
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Ayinde Olayiwola


Modified:
(C)2018 None

FileName:     	EEPROM.h
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

#ifndef _InternalMemory_H_
#define _InternalMemory_H_

EEPROM_read(unsigned char RIM){
    EEADR = RIM;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDATA ;
}

EEPROM_write(unsigned char WIMADDR, unsigned char WIMDATA){
    while(EECON1bits.WR == 1);
    EEADR = WIMADDR;
    EEDATA = WIMDATA;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    EECON1bits.WREN = 0;
}

#endif   //#ifndef _InternalMemory_H_