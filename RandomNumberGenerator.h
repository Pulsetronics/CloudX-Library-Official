
/**************************************************************************

RANDOM NUMBER GENERATOR LIBRARY
for gaming purpose
Version: 	2.0 BETA
Release date:	

Author:
(C)2018 Fidel

Modified:
(C)2019 None

FileName:     	RandomNumberGenerator.h
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

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _RandNum_H_
#define _RandNum_H_

#include <stdlib.h>

int minimum, maximum, Divisor;

void RandNumber_limit(int min, int max){
    minimum=min;
    maximum=max;
}
int RandNumber_gen(){
    int generated;
    Divisor=32767/(maximum);             //32767 => max value returned by rand()
    generated = rand()/Divisor + minimum;
    return generated;
}

#endif  //#ifndef _RandNum_H_