/**************************************************************************

ANALOG - DIGITAL CONVERSION LIBRARY
for analog reading and mesurement
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Ayinde Olayiwola

Modified:
(C)2018 None


FileName:     	ADC.h
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