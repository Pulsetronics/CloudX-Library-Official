
/******************************************************************************************************
                                   ByteHub Embedded
*******************************************************************************************************
 * File:  I2C.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the I2C Serial Protocol. 

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
*********************************************************************************************************/

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