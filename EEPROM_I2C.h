

/******************************************************************************************************
                                   ByteHub Embedded
*******************************************************************************************************
 * File:  EEPROM_I2C.h
 * Version: 1.0
 * Author: Mbed Studio
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the I2C External-EEPROM Functions. 

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



/*
#include <CloudX\M633.h>
#include <CloudX\EEPROM_I2C.h>
#include <CloudX\LCD.h>

#define LedIO pin7Mode
#define Led   pin7



unsigned char rxbyte = 0;
unsigned char txByte = 'a';

unsigned char txArray[] = {'a', 'b', 'c', 'd', 'e', 'f'};
unsigned char rxArray[6] = 0;

setup(){
           //setup here
           
           EEPROMI2C_init(100000);
           
           LCD_setting(1, 2, 3, 4, 5, 6);
           LedIO = OUTPUT;
           Led   = LOW;
           LCD_cmd(clear);
           

 loop(){
           //Program here
           
  
  EEPROMI2C_write(0, 0x0001, txByte);
  rxbyte = EEPROMI2C_read(0, 0x0001);
  if(rxbyte ==  txByte)
    {
        LCD_write(1, 1, rxbyte);
        Led = 1;         
        delayMs(2000);
        Led = 0;          
        delayMs(2000);
        LCD_cmd(clear);
    }
    
    EEPROMI2C_writePage(0, 0x0020, cSendArray, 6);
    EEPROMI2C_readPage(0, 0x0020, rxArray, 6);
    rxArray[6] = '\0';
    LCD_writeText(2, 1, rxArray);
    delayMs(1000);
    LCD_cmd(clear);
    
  }
}
*/


 #ifndef _EEPROM_I2C_H_
 #define _EEPROM_I2C_H_

#include <CloudX\I2C.h>

#define EEPROMI2C_init I2C_init

void EEPROMI2C_write(unsigned char chipSelect, unsigned int addr, unsigned char _data)
{ 
    chipSelect = chipSelect << 1;
    I2C_start();
    I2C_write(0xA0 | (chipSelect | 0));
    I2C_write(addr >>8);
    I2C_write((unsigned char)addr);
    I2C_write(_data);
    I2C_stop();
    delayMs(100);
}

unsigned char EEPROMI2C_read(unsigned char chipSelect, unsigned int addr)
{
    chipSelect = chipSelect << 1;
	unsigned char dataRX = 0;
    I2C_start();
    I2C_write(0xA0 | (chipSelect | 0));
    I2C_write(addr >>8);
    I2C_write((unsigned char)addr);
    I2C_repeatedStart();
    I2C_write(0xA0 | (chipSelect | 1));
    dataRX = I2C_read(0);
    I2C_stop();
    return dataRX;
}

//pageAddress can only have chosen values as say for 24LC64 EEPROM device: 0, 32, 64, 96, ... 1FFF
//byteSize can only range from say for 24LC64 EEPROM device: 1 to 32
//Refer to your datasheet to confirm the page details of your device.
void EEPROMI2C_writePage(unsigned char chipSelect, unsigned int pageAddress, unsigned char* dataArray, unsigned char byteSize)
{
    chipSelect = chipSelect << 1;
    I2C_start();
    I2C_write(0xA0 | (chipSelect | 0));
    I2C_write(pageAddress >>8);                            //MSB of the address
    I2C_write((unsigned char)pageAddress);                 //LSB of byte address(data word address)
    for(byte iterator=0; iterator<byteSize; iterator++)
        I2C_write(dataArray[iterator]);                    //inputs data to EEPROM
    I2C_stop();
    delayMs(100);                                          //Delay for internal write cycle of EEPROM
}

unsigned char EEPROMI2C_readPage(unsigned char chipSelect, unsigned int pageAddress,  unsigned char* dataArray, unsigned char byteSize)
{   
    chipSelect = chipSelect << 1;
	byte iterator;
    I2C_start();
    I2C_write(0xA0 | (chipSelect | 0));                        //Access in write-mode
    I2C_write(pageAddress >>8);                                //MSB of the address
    I2C_write((unsigned char)pageAddress);                     //LSB of byte address(data word address)
    I2C_repeatedStart();
    I2C_write(0xA0 | (chipSelect | 1));                                       //Access in read-mode
    for(iterator=0; iterator<(byteSize-1); iterator++)
        dataArray[iterator] = I2C_read(1);                     //reads with ACK (Acknowledge)
    dataArray[iterator] = I2C_read(0);                         //reads with NACK (Not Acknowledge)
    I2C_stop();
}

 #endif   //#ifndef _EEPROM_I2C_H_
 