
/**************************************************************************

L298 MOTOR DRIVER LIBRARY
IC library for driver motors
Version: 	2.0 BETA
Release date:	

Author:
(C)2018 Ogboye Godwin

Modified:
(C)2019 None

FileName:     	L298.h
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
