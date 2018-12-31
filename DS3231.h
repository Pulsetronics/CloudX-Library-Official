/**************************************************************************

DS3231 DIGITAL CLOCK LIBRARY
for real time digital clock 
Version: 		2.0 BETA
Release date:	

Author:
(C)2018 Ayinde Olayiwola


Modified:
(C)2018 None


FileName:     	DS3231.h
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


#ifndef _DS3231_H_
#define _DS3231_H_


#include <CloudX\I2C.h>
#include <CloudX\stdlib.h>

#define frequency      0x10
#define startOscilator 0x00
#define second         0
#define minute         1
#define hour           2
#define day            3
#define date           4
#define month          5
#define year           6
#define SQWE           7

DS3231_init(){
    I2C_begin(100000);
}

unsigned char DS3231_read(unsigned char address)
{
  unsigned char r_data;
  I2C_start();
  I2C_write(0xD0);
  I2C_write(address);
  I2C_repeatedStart();
  I2C_write(0xD1);
  r_data = I2C_read();
  I2C_stop();
  return(r_data);
}


void DS3231_write(unsigned char address, unsigned char w_data)
{
  I2C_start();
  I2C_write(0xD0);
  I2C_write(address);
  I2C_write(w_data);
  I2C_stop();
}

#endif  //#ifndef _DS3231_H_