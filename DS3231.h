
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:  DS3231.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the DS3231 RTC. 

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