/**************************************************************************

I2C LIBRARY
for serial communication
Version: 		2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 Fidel

FileName:     	I2C.h
Dependencies:	None
Compiler:       CloudX C Compiler
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


#ifndef _I2C_H_
#define _I2C_H_

#define I2C_begin I2C_init


MSSPWait(){
    while(!PIR1bits.SSPIF);
           PIR1bits.SSPIF=0;
}

void I2C_start(){
   SSPCON2bits.SEN =1; //Generate START Condition
   MSSPWait();
}

void I2C_repeatedStart(){
    SSPCON2bits.RSEN=1;
    while(SSPSTATbits.S==0);
    MSSPWait();
}

void I2C_stop(){
    SSPCON2bits.PEN=1;
    while(SSPSTATbits.P==0);
    MSSPWait();
}

void I2C_write(unsigned char addressbyte){
                   SSPBUF = addressbyte;
                   MSSPWait();
                   while(SSPCON2bits.ACKSTAT);
}

I2C_init(const unsigned long I2C_BAUD){
    TRISCbits.TRISC3 =1;
    TRISCbits.TRISC4 =1;
    SSPCON =  0b00101000;
    SSPSTAT = 0b10000000;
    SSPADD =  (20000000 / (4 * I2C_BAUD)) - 1;
	}
	

unsigned char I2C_read(unsigned char ack)
{
  SSPCON2bits.RCEN = 1;
  MSSPWait();
  ACKDT = (ack)? 0:1;    //Acknowledge bit  //0->Ack 1=>Nack
  ACKEN = 1;             //Acknowledge sequence
  SSPCON2bits.PEN =1;
  MSSPWait();
  return SSPBUF;
}

#endif   //#ifndef _I2C_H_