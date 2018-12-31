/**************************************************************************

JOYSTICK LIBRARY
for analog button controls
Version: 		2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 None

FileName:     	Joystick.h
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


#ifndef _JoyStick_H_
#define _JoyStick_H_

#define JOYSTICK_UP 0
#define JOYSTICK_DOWN 5
#define JOYSTICK_LEFT 0
#define JOYSTICK_RIGHT 5

Joystick_upDown(unsigned char y){
	               if(analogRead(y) < 200) return JOYSTICK_UP;
				   else if(Analog_read(y) >1000) return JOYSTICK_DOWN;
				   else return 0xFF;

}

Joystick_leftRight(unsigned char x){
	               if(analogRead(x) < 200) return JOYSTICK_LEFT;
				   else if(Analog_read(x) >1000) return JOYSTICK_RIGHT;
				   else return 0xFF;
}

Joystick_centre(unsigned char cntre){
	   if(readPin(cntre) == LOW) return LOW;
	   else return HIGH;
}

#endif   //#define _JoyStick_H_


