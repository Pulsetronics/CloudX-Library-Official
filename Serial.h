
/**************************************************************************

SERIAL LIBRARY
for UART communication
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 Ogboye Godwin


FileName:     	Serial.h
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


#ifndef _Serial_H_
#define _Serial_H_

#define   OK 0 


void Serial_begin(const unsigned long baudd){
    SPBRG = (_XTAL_FREQ - (baudd*16)) / (baudd*16);
    TXSTA = 0x24;
    RCSTA = 0x90;
   
}

void Serial_write(unsigned char SerTx)
{
    TXSTAbits.TXEN =1;
    TXREG = SerTx;
    delayMs(5);
}

void Serial_writeText(unsigned char *Sertxxt){
    unsigned char pnttter=0;
    while(Sertxxt[pnttter] != 0)
        serialWrite(Sertxxt[pnttter++]);
}

unsigned char Serial_read(){
     RCSTAbits.CREN =1;
     PIR1bits.RCIF=0;
     RCSTAbits.CREN = 1;
    return RCREG;
}


unsigned char Serial_available(){
    RCSTAbits.CREN =1;
	if(RCSTAbits.OERR) {RCSTAbits.CREN = 0; RCSTAbits.CREN =1;}
    return PIR1bits.RCIF;
}

#endif    //#ifndef _Serial_H_