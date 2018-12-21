
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:  DS1302.h
 * Version: 1.0
 * Author: Adeyemi Adekorede
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the DS1302 RTC. 

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


/*
//EXAMPLE:


#include <CloudX/M633.h>
#include <CloudX/LCD.h>
#include <CloudX/DS1302.h>

   byte minutes = 0, seconds = 0, hours = 0;
   byte day     = 0, month = 0, year = 0, date = 0;
   portMode(3, 0x00);
   
   char time[9] = {'0', '0', ':', '0', '0', ':', '0', '0', '\0'};
   char Date[9] = {'0', '0', '/', '0', '0', '/', '0', '0', '\0'};

setup(){
   
   DS1302_init(14, 15, 16);       //DAT, CLK, CE
   LCD_setting(1, 2, 3, 4, 5, 6); //RS, EN, D4, D5, D6, D7
   LCD_cmd(clear);
   
   LCD_writeText(1, 1, "Time:");
   LCD_writeText(2, 1, "Date:");
   
   DateTime_write(6, 7, 18, 30, 9, 30, 0); //day(1-7),month(1-12),year(0-99),date(1-31),hr(0-23),min(0-59),sec(0-59)
   //Date_write(27, 9, 18); //date(1-31), month(1-12), year(0-99)
   //Time_write(9, 30, 15); //hr,min,seconds
   
   //write and read from DS1302RAM
   DS1302RAM_write(0, 7);
   minutes = DS1302RAM_read(0);
   
   loop(){
  
       Time_read(&hours, &minutes, &seconds);   
       Date_read(&day, &month, &year, &date);

        time[0]= BCD2UpperChar(hours);
        time[1]= BCD2LowerChar(hours);
        time[3]= BCD2UpperChar(minutes);
        time[4]= BCD2LowerChar(minutes);
        time[6]= BCD2UpperChar(seconds);
        time[7]= BCD2LowerChar(seconds);

        Date[0]= BCD2UpperChar(date);
        Date[1]= BCD2LowerChar(date);
        Date[3]= BCD2UpperChar(month);
        Date[4]= BCD2LowerChar(month);
        Date[6]= BCD2UpperChar(year);
        Date[7]= BCD2LowerChar(year);


        LCD_writeText(1, 7, time);
        LCD_writeText(2, 7, Date);


   }
    

}



*/


#ifndef _DS1302_H_
#define _DS1302_H_

#include <CloudX/stdlib.h>
#include <math.h>

/*Definitions for backward-compatibility*/
#define RAM_write DS1302RAM_write
#define RAM_read  DS1302RAM_read

#define secondsWrite 0x80
#define minuteWrite  0x82
#define hourWrite    0x84
#define dateWrite    0x86
#define monthWrite   0x88
#define dayWrite     0x8A
#define yearWrite    0x8C


#define secondsRead   0x81
#define minuteRead    0x83
#define hourRead      0x85
#define dateRead      0x87
#define monthRead     0x89
#define dayRead       0x8B
#define yearRead      0x8D

byte Clock;
byte Data;
byte RST;

void Shift_out_byte_right(byte data);
byte shift_in_byte();
void Write_ds1302_byte(byte cmd);
void DS1302_write(byte cmd, byte data); 
byte DS1302_read(byte cmd );
void DS1302_init(byte DAT, byte CLK, byte CE);
 
 
 // THESE ARE THE FUNCTIONS THAT CONCERN THE USER...
void Time_read(byte *hr,byte *min,byte *sec);
void Date_read(byte *day, byte *month, byte *year, byte *date);
void DS1302RAM_write(byte address, byte data);
byte DS1302RAM_read(byte address);
void DateTime_write(byte day, byte month,byte year,byte date,byte hr,byte min,byte seconds);
void Time_write(byte hr,byte min,byte seconds);
void Date_write(byte date,byte month,byte year);



char IntToChar(byte x);
/*byte shift_in_byte(){
unsigned char temp, data=0x00;
    for(byte i=0;i<8;i++){
        digitalWrite(Clock, HIGH);  
        __delay_us(2);
        digitalWrite(Clock, LOW);
          __delay_us(2);
        temp = digitalRead(Data);
        temp= (temp<<7);
        data=(data>>1);
        data = (temp | data);
        
}
PORTCbits.RC0 = 1;
return data;
}
 * */



void DS1302_init(byte DAT, byte CLK, byte CE){
Clock = CLK;
Data = DAT;
RST = CE;
byte x;
pinMode(Clock, OUTPUT);
pinMode(RST, OUTPUT);
digitalWrite(Clock, LOW);
digitalWrite(RST, LOW);
//for debugging
//TRISC=0x00;


//basic house keeping 
//Write protect disable bit must be disabled.
 DS1302_write(0x8E,0);
 //enable trickle charger
 // enable one diode mode
 // enable 2k charging resistor and charging current calculated is 2.2mA PG 7.
 DS1302_write(0x90,0xA5);
 //we read clock disable bit and ensure the clock is enabled
 x = DS1302_read(0x81);
 if((x & 0x80)!=0){
     DS1302_write(0x80, 0);
 }
}



byte DS1302_read(byte cmd ){
     pinMode(Data, INPUT);
     byte dataRead=0x00;
     digitalWrite(RST,HIGH);  //reset high
     Write_ds1302_byte(cmd);
     dataRead = shift_in_byte();
     pinMode(Data,OUTPUT);
     digitalWrite(RST,LOW);
     PORTC = dataRead;
     return dataRead;
     }

void Write_ds1302_byte(byte cmd){
    pinMode(Data, OUTPUT);
    digitalWrite(Data, LOW);
    Shift_out_byte_right(cmd);
    pinMode(Data,INPUT);
   
}


void DS1302_write(byte cmd, byte data){
    digitalWrite(RST, HIGH);
    Write_ds1302_byte(cmd);
    Write_ds1302_byte(data);
    digitalWrite(RST, LOW); 
    digitalWrite(Clock, LOW);
}


// ADDRESS IS THE BITS PLUS INITIAL START ADDRESS OF THE RAM.  
//RAM IS 31BIT WIDE  ADDRESS WOULD RANGE FROM 0-31;
void DS1302RAM_write(byte address, byte data){
    data = Binary2BCD(data);
    DS1302_write( (address|0xC0), data);
}

byte DS1302RAM_read(byte address){
    byte data = 0x00;
    data = DS1302_read(address|0xC1);
    data = BCD2Binary(data);
    return data;
    
}



byte shift_in_byte(){
byte temp, data=0x00;
    for(byte i=1;i<=8;i++){
        temp = digitalRead(Data);
        temp= (temp<<7);
        data=(data>>1);
        data = (temp | data);
         digitalWrite(Clock, HIGH);  
        digitalWrite(Clock, LOW);
    }
return data;
}



void Shift_out_byte_right(byte data){
    char i;
    for (i=0; i<8; i++){
        if(data & 0x01){
        digitalWrite(Data,HIGH);
        }else{
        digitalWrite(Data,LOW);
        }
         digitalWrite(Clock, HIGH);
          digitalWrite(Clock, LOW);
          data = data>>1;    
    }

}


void DateTime_write(byte day, byte month,byte year,byte date,byte hr,byte min,byte seconds){  
min = Binary2BCD(min);
hr =   Binary2BCD(hr);
seconds = Binary2BCD(seconds);
day = Binary2BCD(day);
month = Binary2BCD(month);
year = Binary2BCD(year);
date = Binary2BCD(date);

DS1302_write( minuteWrite,min);
DS1302_write(hourWrite, hr);
DS1302_write(dayWrite,day);
DS1302_write(monthWrite,month);
DS1302_write(dateWrite,date);
DS1302_write(yearWrite ,year);
DS1302_write(secondsWrite,seconds);

}

void Time_write(byte hr,byte min,byte seconds){
min = Binary2BCD(min);
hr =   Binary2BCD(hr);
seconds = Binary2BCD(seconds);


DS1302_write(minuteWrite,min);
DS1302_write(hourWrite, hr);
DS1302_write(secondsWrite,seconds);
}


void Date_write(byte date,byte month,byte year){
date = Binary2BCD(date);
month =   Binary2BCD(month);
year = Binary2BCD(year);


DS1302_write(dateWrite,date);
DS1302_write(monthWrite,month);
DS1302_write(yearWrite,year);
}


void Time_read( byte *hr,byte *min,byte *sec){

*sec =DS1302_read(secondsRead );
*min = DS1302_read(minuteRead);
*hr = DS1302_read(hourRead);
}
 
void Date_read(byte *day, byte *month, byte *year, byte *date){
     
    *day= DS1302_read(dayRead );
    *month = DS1302_read(monthRead);
    *year =  DS1302_read(yearRead);
    *date = DS1302_read(dateRead);
      
}



// reason for this is cause my output is in form of binary 
//which is an integer..
 char IntToChar(byte x){
 x = Binary2BCD(x);
}

#endif  //#ifndef _DS1302_H_





/*example to write and read from the RAM*/

  /*
   char *time;
   byte minutes =0; 
   DS1302RAM_write(0,7);
   minutes = DS1302RAM_read(0);


   
   //  
    intTostr(time,minutes,DEC);
 Lcd_writeText(1,1,time);
*/