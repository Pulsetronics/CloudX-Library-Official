
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:    L298.h
 * Version: 1.0
 * Author:  Ogboye Godwin
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the L298 Motor Driver using PWM.
                Although it is labeled L298 but can be used for all types of H-BRIDGE driving/drivers
                such as L293 or transistor transistor H-BRIDGE's.
                PWM pins should be connected to the enable pins of the driver for speed control for motors
                and control pulses.

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

EXAMPLE:


#include <CloudX/M633.h>
#include <CloudX/L298.h>

setup(){
    
    L298_setting(1, 2, 3, 4);        //IN1, IN2, IN3, IN4
    L298_write(left, forward, 50);   //side, direction, speed (le. 50% speed)
    L298_write(right, backward, 75);  //side, direction, speed (le. 75% speed)
    
    loop(){

    }
}

*/


#ifndef _L298_H_
#define _L298_H_

#include <CloudX/PWM.h>

#define backward            0  //direction
#define forward             1  
#define counterClockwise    0  //direction
#define clockwise           1  
#define stop                2  //command
#define start               3  
#define left                1  //side
#define sideA               1 
#define right               2  
#define sideB               2  

// pin definition from CloudX controller
char _leftPin1, _leftPin2, _rightPin1, _rightPin2;

L298_setting(char leftPin1,char leftPin2,char rightPin1,char rightPin2) //IN1, IN2, IN3, IN4
{
    pinMode(leftPin1, OUTPUT);
    pinMode(leftPin2, OUTPUT);
    pinMode(rightPin1, OUTPUT);
    pinMode(rightPin2, OUTPUT);

	_leftPin1 = leftPin1;
	_leftPin2 = leftPin2;
	_rightPin1 = rightPin1;
	_rightPin2 = rightPin2;
	
	PWM1_init(5000);//rc2
	PWM2_init(5000);//rc1
	PWM1_start();
	PWM2_start();
	PWM1_duty(0);
	PWM2_duty(0);
	RC2 = 0;
	RC1 = 0;
}

L298_write(char side,char direction,unsigned int speed){
  PWM1_start();
  PWM2_start();
  RC2 = 0;
  RC1 = 0;
  
if( (side == left) && (direction == forward)){
	pinSelect(_leftPin1, HIGH);
	pinSelect(_leftPin2, LOW);
    PWM1_duty(speed);
}
if((side == left) && (direction == backward)){
    pinSelect(_leftPin1, LOW);
    pinSelect(_leftPin2, HIGH);
    PWM1_duty(speed);
}


if((side == right) && (direction == forward)){
    pinSelect(_rightPin1, HIGH);
    pinSelect(_rightPin2, LOW);
    PWM2_duty(speed);
}
if((side == right) && (direction == backward)){
    pinSelect(_rightPin1, LOW);
    pinSelect(_rightPin2, HIGH);
    PWM2_duty(speed);
   }
 }

L298_stop(char side){
    if(side == left ){
        pinSelect(_leftPin1, LOW);
        pinSelect(_leftPin2, LOW);
        PWM1_stop();
        PWM1_duty(0);
        RC2 = 0;
}
if(side==right ){
	pinSelect(_rightPin1, LOW);
	pinSelect(_rightPin2, LOW);
	PWM2_stop();
	PWM2_duty(0);
	RC1 = 0;
  }
}

#endif   //#ifndef _L298_H_
