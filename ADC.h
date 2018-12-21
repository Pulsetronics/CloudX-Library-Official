/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   ADC.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the Analog-Digital Converter. 

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
**************************************************************************************************/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif

#ifndef _ADC_H_
#define _ADC_H_



void Analog_setting(){
    ADCON0 = 0x81;
    ADCON1 = 0x02;
}

unsigned int Analog_read(unsigned char channel){
    int aadc,bbdc, ccdc;
	channel = channel - 17;
    if(channel>7)return 0;
    ADCON0 = ADCON0 & 0xC5;
    ADCON0 = ADCON0 | (channel << 3);
    __delay_ms(2);
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE);
    aadc = ADRESH;
    aadc = aadc<<2;
    bbdc = ADRESL;
    bbdc = bbdc >>6;
    ccdc = aadc|bbdc;
    return ccdc;

}

#endif   //#ifndef _ADC_H_