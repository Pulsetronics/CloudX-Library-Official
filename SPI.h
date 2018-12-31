
/**************************************************************************

SPI LIBRARY
for serial communication
Version: 	2.0 BETA
Release date:	

Author:
(C)2018 Ogboye Godwin

Modified:
(C)2018 Adeyemi Adekorede


FileName:     	SPI.h
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
