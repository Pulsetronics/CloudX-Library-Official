
/**************************************************************************

STEPPER LIBRARY
for controlling stepper motors
Version: 	2.0 BETA
Release date:	April 10, 2018, 4:48 PM

Author:
(C)2018 Ogboye Godwin

Modified:
(C)2018 None


FileName:     	Stepper.h
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