
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:    SPI.h
 * Version: 1.0
 * Author:  Ogboye Godwin
 * Improved On by: Adeyemi Adekorede
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the SPI functions. 

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


/* the following examples demonstrates master read from slave 1 and send valueread to slave2 
//EXAMPLE: (MASTER)

#include <CloudX/M633.h>
#include <CloudX/SPI.h>

unsigned char Readstring[5];
unsigned char readvalue=0;

#define slave2 1
#define slave1 2

setup(){
SPI_init(master);
//DISABLE BOTH SLAVES
 pinMode(slave2,OUTPUT);
 pinMode(slave1,OUTPUT);
 digitalWrite(slave1, HIGH);
digitalWrite(slave2, HIGH);
loop(){
//enable slave1  disable slave2
    digitalWrite(slave1, LOW); 
    digitalWrite(slave2, HIGH);
    readvalue =SPI_read() ;
  
  //disable slave1 enable slave2 
   
    digitalWrite(slave1, HIGH); 
    digitalWrite(slave2, LOW);
     SPI_write(readvalue);
    delayMs(1000);
}
}

//EXAMPLE:SLAVE1
#include <CloudX/M633.h>
#include <CloudX/SPI.h>

 
setup(){
    SPI_init(slave);
    loop(){
        for(int g=0; g<=127; g++) {
            SPI_write(g);
            delayMs(1000);
        }
        }
        }
//  EXAMPLE: SLAVE2

#include <CloudX/M633.h>
#include <CloudX/SPI.h>

  int valuereceived;
setup(){
    SPI_init(slave);
    portMode(2,0x00); //all port2 pins as output
    portWrite(2,OFF_ALL);
    loop(){
    valuereceived =  SPI_read();
    portWrite(2,valuereceived);
      }
}


*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _SPI_H_
#define _SPI_H_

#include <stdio.h>
#include <stdlib.h>

#define master 0
#define slave 1 
enum SPIMode{mastermode, slavemode };
void SPI_init(byte i){

switch(i){

    case mastermode:                         //master mode
     TRISCbits.TRISC5 = 0;                   //SDO AS OUTPUT
     TRISAbits.TRISA5 = 0;                  // SS OUTPUTS IN MASTER MODE
     SSPSTAT = 0b00000000;
     SSPCON = 0b00100000; 
     TRISCbits.TRISC3 = 0;                   //SCK AS OUTPUT
     ADCON1 =0x04;
     break;
    case slavemode:         //slave mode
     TRISC5 = 0;  
    TRISC4=1;
     SSPSTAT = 0x00; 
     SSPCON = 0x24; 
     TRISC3 = 1;
     ADCON1 =0x04;
     break;
    
}

    
}


unsigned char SPI_write(char data) 
{
    SSPCONbits.WCOL = 0;
    PIR1bits.SSPIF = 0;
    SSPBUF = data; //Write the user given data into buffer
    if(SSPCON & 0x80) return (0); //if WCOL bit is not set return 0
    else
        while(!PIR1bits.SSPIF); //wait until bus cycle completes
            return(1);    
}



unsigned char SPI_read() //Read the received data
{
    unsigned char temporaryVar;
    temporaryVar = SSPBUF;   //CLEAR BF
    PIR1bits.SSPIF = 0;      //CLEAR INTERRUPT FLAG
    SSPBUF = 0x00;          //INITIATE BUS CYCLE 
    while(!PIR1bits.SSPIF); // WAIT UNTIL CYCLE COMPLETES
    return(SSPBUF); // RETURN BYTE READ
    while ( !SSPSTATbits.BF );// Hold till BF bit is set, to make sure the complete data is read
    
    
    return(SSPBUF); // return the read data
}

unsigned char Ready2read(){
    if (SSPSTATbits.BF) return (1);
    else return(0);
}

#endif  //#ifndef _SPI_H_
