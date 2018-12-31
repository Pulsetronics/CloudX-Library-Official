/**************************************************************************

EEPROM I2C LIBRARY
for external ROM storage
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Fidel


Modified:
(C)2018 None

FileName:     	EEPROM_I2C.h
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
#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


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
 