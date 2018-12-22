
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   Stepper.h
 * Author: Ogboye Godwin G.
 * Created on April 10, 2018, 4:48 PM
 * Website: http://www.makeelectronics.ng or http://www.bytehubembed.com
 * Description: This file contains the program to demonstrate the stepper motor.
 *
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


#ifndef _Stepper_H_
#define _Stepper_H_

int p1,p2,p3,p4, currentPos=0;
int oneStepFoward=0 , oneStepBackward=1, forward=2, backward=3;
int Fstep[8][4]={
                {0,0,0,1},
                {0,0,1,1},
                {0,0,1,0},
                {0,1,1,0},
                {0,1,0,0},
                {1,1,0,0},
                {1,0,0,0},
                {1,0,0,1}
                };
int Hstep[4][4]={
                {0,1,0,1},
                {0,1,1,0},
                {1,0,1,0},
                {1,0,0,1}
                };

Stepper_init(int AA,int BB,int CC, int DD)
{
    pinMode(AA,OUTPUT);pinSelect(AA,HIGH); p1=AA;
    pinMode(BB,OUTPUT);pinSelect(BB,HIGH); p2=BB; 
    pinMode(CC,OUTPUT);pinSelect(CC,HIGH); p3=CC;
    pinMode(DD,OUTPUT);pinSelect(DD,HIGH); p4=DD;
}
Stepper_move(int AA,int BB,int CC, int DD){
    pinSelect(p1,AA);
    pinSelect(p2,BB);
    pinSelect(p3,CC);
    pinSelect(p4,DD);
    delayms(100);
}
fullUpdateP(){
    currentPos++;
    if(currentPos==8)
        currentPos=0;
}
fullUpdateN(){
    currentPos--;
    if(currentPos==-1)
        currentPos=7;
}
halfUpdateP(){
    currentPos++;
    if(currentPos>=4)
        currentPos=0;
}
halfUpdateN(){
    if(currentPos>4)
        currentPos=4;
    currentPos--;
    if(currentPos==-1)
        currentPos=3;
}


Stepper_fullMove(int stp){
    if(stp==oneStepFoward){
        Stepper_move(Fstep[currentPos][0],Fstep[currentPos][1],Fstep[currentPos][2],Fstep[currentPos][3]);
        fullUpdateP();
    }
    if(stp==oneStepBackward){
        Stepper_move(Fstep[currentPos][0],Fstep[currentPos][1],Fstep[currentPos][2],Fstep[currentPos][3]);
        fullUpdateN();
    }
    if(stp==forward){
        int doit;
        for(doit=0;doit<8;doit++){
        Stepper_move(Fstep[currentPos][0],Fstep[currentPos][1],Fstep[currentPos][2],Fstep[currentPos][3]);
        fullUpdateP();}
    }
    if(stp==backward){
        int doit;
        for(doit=0;doit<8;doit++){
        Stepper_move(Fstep[currentPos][0],Fstep[currentPos][1],Fstep[currentPos][2],Fstep[currentPos][3]);
        fullUpdateN();
        }
    }
}
Stepper_halfMove(int stp){
    if(stp==oneStepFoward){
        Stepper_move(Hstep[currentPos][0],Hstep[currentPos][1],Hstep[currentPos][2],Hstep[currentPos][3]);
        halfUpdateP();
    }
    if(stp==oneStepBackward){
        Stepper_move(Hstep[currentPos][0],Hstep[currentPos][1],Hstep[currentPos][2],Hstep[currentPos][3]);
        halfUpdateN();
    }
    if(stp==forward){
        int doit;
        for(doit=0;doit<4;doit++){
        Stepper_move(Hstep[currentPos][0],Hstep[currentPos][1],Hstep[currentPos][2],Hstep[currentPos][3]);
        halfUpdateP();}
    }
    if(stp==backward){
        int doit;
        for(doit=0;doit<4;doit++){
        Stepper_move(Hstep[currentPos][0],Hstep[currentPos][1],Hstep[currentPos][2],Hstep[currentPos][3]);
        halfUpdateN();
        }
    }
}

#endif  //#ifndef _Stepper_H_