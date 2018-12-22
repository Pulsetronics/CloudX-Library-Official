
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:  DS1307.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the DS1307 RTC. 

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


#ifndef _DS1307_H_
#define _DS1307_H_

#include <CloudX\I2C.h>
#include <CloudX\stdlib.h>

#define frequency      0x10
#define startOscilator 0x00
#define ds_second      0
#define ds_minute      1
#define ds_hour        2
#define ds_day         3
#define ds_date        4
#define ds_month       5
#define ds_year        6
#define ds_SQWE        7

DS1307_init(){
    I2C_begin(100000);
}

unsigned char DS1307_read(unsigned char address)
{
  unsigned char r_data;
  I2C_start();
  I2C_write(0xD0);
  I2C_write(address);
  I2C_repeatedStart();
  I2C_write(0xD1);
  r_data=I2C_read();
  I2C_stop();
  return(r_data);
}


void DS1307_write(unsigned char address, unsigned char w_data)
{
  I2C_start();
  I2C_write(0xD0);
  I2C_write(address);
  I2C_write(w_data);
  I2C_stop();
}

#endif  //#ifndef _DS1307_H_