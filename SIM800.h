
/**************************************************************************

SIM800L MODULE LIBRARY
for communicating and interfacing with GSM module
Version: 	2.0 BETA
Release date:	March 5, 2018 (11:45 AM)

Author:
(C)2018 Ogboye Godwin

Modified:
(C)2018 None


FileName:     	SIM800.h
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

Example:


#include <CloudX/M633.h>
#include <CloudX/Serial.h>
#include <CloudX/SIM800.h>
#include <CloudX/LCD.h>

int fireSensor=16;
char pressed;


setup(){
    
    // initialise LCD
    LCD_setting(10, 11, 12, 13, 14, 15); //RS, EN, D4, D5, D6, D7
    LCD_cmd(clear);
    
    LCD_writeText(1,1,"Home Security");
    LCD_writeText(2,1,"Home Assistance");
    delayms(700);
    
    //Initialise SIM MODULE
    Serial_begin(9600);
    LCD_cmd(clear);
    LCD_writeText(1,1,"initialising....");
   
    //initialize SMS 
    SIM800_initSMS();
    delayms(500);
    LCD_writeText(2,1,"    SIM Ready     ");
    
    pinMode(fireSensor,INPUT);
    loop(){
        if(readPin(fireSensor)){
        SIM800_sendSMS("081PHONE_NO","FIRE!!! PLEASE HELP");
        delayms(500);
        }
    
    }

}


*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _SIM800_H_
#define _SIM800_H_

#include <string.h>

// GENERAL

    const char lastCommand = 'A';               //void          ();
    const char verify[] = "AT";                 //void          ();
    const char  echoOff[] = "ATE0";             //void          ();
    const char  echoOn[] = "ATE1";              //void          ();
    const char  powerOff[] = "AT+CPOWD";        //void          ();
    
    // below only has test( =?) and read/execute(empty)
    //command        read, test
    const char reqMakerID[] = "AT+CGMI" ;       //SIM800_command(char * ,cmd);
    const char reqDeviceModelID[] = "AT+CGMM" ; //SIM800_command(char * ,cmd);
    const char reqSoftwareID[] = "AT+CGMR" ;    //SIM800_command(char * ,cmd);
    const char reqIMEI[] = "AT+CGSN" ;          //SIM800_command(char * ,cmd);
    const char reqIMSI[] = "AT+CIMI" ;          //SIM800_command(char * ,cmd);
    const char activity[] = "AT+CPAS" ;         //SIM800_command(char * ,cmd);
    const char signalQuality[] = "AT+CSQ" ;     //SIM800_command(char * ,cmd);
    const char getSelfAddr[] = "AT+CNUM" ;      //SIM800_command(char *,cmd);
    const char listAllOperators[] = "AT+COPN" ; //SIM800_command(char *,cmd);
    const char battery[] = "AT+CBC" ;           //SIM800_command(char *,cmd);
    

    // below only has test(=?) , read/execute(?)  and write (=<parameter>)
    //command       read, test or write           value
    const char callMeter[] = "AT+CACM" ;        //SIM800_commands(char *,cmd,  char * );
    const char callMeterMax[] = "AT+CAMM" ;     //SIM800_commands(char *,cmd,  char * );
    const char chargeAdvice[] = "AT+CAOC" ;     //SIM800_commands(char *,cmd,  char * );
    const char dataCallService[] = "AT+CBST" ;  //SIM800_commands(char *,cmd,  char * );
    const char callForward[] = "AT+CCFC" ;      //SIM800_commands(char *,cmd,  char * );
    const char callWait[] = "AT+CCWA" ;         //SIM800_commands(char *,cmd,  char * );
    const char errorReport[] = "AT+CEER" ;      //SIM800_commands(char *,cmd,  char * );
    const char charset[] = "AT+CSCS" ;          //SIM800_commands(char *,cmd,  char * );
    const char addressType[] = "AT+CSTA" ;      //SIM800_commands(char *,cmd,  char * );
    const char callHold[] = "AT+CHLD" ;         //SIM800_commands(char *,cmd,  char * );
    const char activeCalls[] = "AT+CLCC" ;      //SIM800_commands(char *,cmd,  char * );
    const char facilityLock[] = "AT+CLCK" ;     //SIM800_commands(char *,cmd,  char * );
    const char showCallerID[] = "AT+CLIP" ;     //SIM800_commands(char *,cmd,  char * );
    const char hideSelfID[] = "AT+CLIR" ;       //SIM800_commands(char *,cmd,  char * );
    const char deviceError[] = "AT+CMEE" ;      //SIM800_commands(char *,cmd,  char * );
    const char callerID[] = "AT+COLP" ;         //SIM800_commands(char *,cmd,  char * );
    const char netOps[] = "AT+COPS" ;           //SIM800_commands(char *,cmd,  char * );
    const char pbFind[] = "AT+CPBF" ;           //SIM800_commands(char *,cmd,  char * );
    const char pbRead[] = "AT+CPBR" ;           //SIM800_commands(char *,cmd,  char * );
    const char pbStorage[] = "AT+CPBS" ;        //SIM800_commands(char *,cmd,  char * );
    const char pbWrite[] = "AT+CPBW" ;          //SIM800_commands(char *,cmd,  char * );
    const char pinCode[] = "AT+CPIN" ;          //SIM800_commands(char *,cmd,  char * );
    const char changePwd[] = "AT+CPWD" ;        //SIM800_commands(char *,cmd,  char * );
    const char serviceReport[] = "AT+CR" ;      //SIM800_commands(char *,cmd,  char * );
    const char ringCodeMode[] = "AT+CRC" ;      //SIM800_commands(char *,cmd,  char * );
    const char netReg[] = "AT+CREG" ;           //SIM800_commands(char *,cmd,  char * );
    const char radioLinkParams[] = "AT+CRLP" ;  //SIM800_commands(char *,cmd,  char * );
    const char SIMRawAccess[] = "AT+CRSM" ;     //SIM800_commands(char *,cmd,  char * );
    const char dtmfDuration[] = "AT+VTD" ;      //SIM800_commands(char *,cmd,  char * );
    const char dtmfPlay[] = "AT+VTS" ;          //SIM800_commands(char *,cmd,  char * );
    const char muxControl[] = "AT+CMUX" ;       //SIM800_commands(char *,cmd,  char * );
    const char prefOperators[] = "AT+CPOL" ;    //SIM800_commands(char *,cmd,  char * );
    const char deviceMode[] = "AT+CFUN" ;       //SIM800_commands(char *,cmd,  char * );
    const char clock[] = "AT+CCLK" ;            //SIM800_commands(char *,cmd,  char * );
    const char SIMStrAccess[] = "AT+CSIM" ;     //SIM800_commands(char *,cmd,  char * );
    const char alertMode[] = "AT+CALM" ;        //SIM800_commands(char *,cmd,  char * );
    const char alertSound[] = "AT+CALS" ;       //SIM800_commands(char *,cmd,  char * );
    const char ringerVolume[] = "AT+CRSL" ;     //SIM800_commands(char *,cmd,  char * );
    const char loudSpeakerVol[] = "AT+CLVL" ;   //SIM800_commands(char *,cmd,  char * );
    const char mute[] = "AT+CMUT" ;             //SIM800_commands(char *,cmd,  char * );
    const char pricePerUnit[] = "AT+CPUC" ;     //SIM800_commands(char *,cmd,  char * );
    const char callMeterMaxEvent[] = "AT+CCWE" ;//SIM800_commands(char *,cmd,  char * );
    const char usd[] = "AT+CUSD" ;              //SIM800_commands(char *,cmd,  char * );
    const char ssn[] = "AT+CSSN" ;              //SIM800_commands(char *,cmd,  char * );
    const char dtmfDetect[] = "AT+DDET" ;       //SIM800_commands(char *,cmd,  char * );


const char ok[] = "OK";
const char error[] = "ERROR";
const char all[] = "ALL"; // for message deleting
const int write=2,yes=1,read=1, no = 0, test=0;

const char  deleteMessage[] = "AT+CMGD";        //   SIM800_commands(char *,cmd,  char * );
const char  MessageFormat[] = "AT+CMGF";        //   SIM800_commands(char *,cmd,  char * );
const char  listSMS[] = "AT+CMGL";              //   SIM800_commands(char *,cmd,  char * ); from prefered storage
const char  ReadSMS[] = "AT+CMGR";              //   SIM800_commands(char *,cmd,  char * );
const char sendMessage[] = "AT+CMGS";           //   SMS_verifyResponse(char *cmd ,Val, char *,char*)
const char WriteSMSTomemeory[] = "AT+CMGW";     //   SMS_verifyResponse(char *cmd ,Val, char *,char*)
const char SMSSendFromStore[] = "AT+CMSS";      //   SIM800_commands(char *,cmd,  char * );
const char  newSMSIndications[] = "AT+CNMI";    //   SIM800_commands(char *,cmd,  char * );
const char  PreferedStorade[] = "AT+CPMS";      //   SIM800_commands(char *,cmd,  char * );
const char RestoreSMSConfig[] = "AT+CRES";      //   SIM800_commands(char *,cmd,  char * );
const char  saveSMSSettings[] = "AT+CSAS";      //   SIM800_commands(char *,cmd,  char * );
const char  SMSCenterAddress[] = "AT+CSCA";     //   SIM800_commands(char *,cmd,  char * );
const char  SMSCellCast[] = "AT+CSCB";          //   SIM800_commands(char *,cmd,  char * );
const char  SMSGetParams[] = "AT+CSDH";         //   SIM800_commands(char *,cmd,  char * );
const char  SMSSetParams[] = "AT+CSMP";         //   SIM800_commands(char *,cmd,  char * );
const char  SMSService[] = "AT+CSMS";           //   SIM800_commands(char *,cmd,  char * );
const char textSendDone[] = "+CMGF=1"; //sending Successful for Text mode
const char PSUSendDone[] = "+CMGF=0"; //sending Successful for PSU mode

const char TxtMode = '1',PduMode ='0';


char ex1;
int i;



/* 
 
timerInit(){
    OPTION_REG = 0X87; //9.984ms
    TMR0 = 61;
    INTCON=0XA0;
}
timerRESET(){
    TMR0IF = 0;
    TMR0 = 61;
}
timeUp(int tmStart){

}*/

unsigned int compareStrings( char *iinMsg ,  char *iexpd){
    int xc=0;
    while(iinMsg[xc]!='\0'){
        if(iinMsg[xc]!=iexpd[xc])
                return 0;
        xc++;
    }
    return 1;
}

enter(){
    Serial_write('\r');
    serialWrite('\n');
}

clearBuffer(){
    char waste;
    while (Serial_available()){
        waste = Serial_read();
    }
    CREN = 0;  //OERR=0;
    CREN = 1;
}
wasteAgain(){
    ex1=0;
    while(ex1!=0X0A){
        while(!Serial_available());
        ex1 = Serial_read();
    }
}

catchIncoming(){
    wasteAgain();
     i = ex1 = 0;
    char inMsgg[8];
    while (!Serial_available()); //or while (PIR1bits.RCIF==0);
    ex1 = Serial_read();
    do{
        inMsgg[i]=ex1; //
        while (!Serial_available());// or while (PIR1bits.RCIF==0); //
        ex1 = Serial_read();
        i++;
    }
    while(ex1!='\r'); //0x0d;
    return inMsgg;
    
}

               //command       yes=read no=test
SIM800_command(char *valU , int cmd     ){
    if(cmd==read) //1 is read
        Serial_writeText("valU");
    else{ //test
        Serial_writeText("valU");
        Serial_writeText("=?");
    }
    enter();
}
               
SIM800_commands(char *valU ,int cmd,  char *valU2 ){
    if(cmd==test) {//test
        Serial_writeText(valU);
        Serial_writeText("=?");
    }
    else if(cmd==read){ // read
        Serial_writeText(valU);
        Serial_write('?');
    }
    else if(cmd==write){//write
        Serial_writeText(valU);
        Serial_writeText('=');
        Serial_writeText(valU2);
    }
    enter();
}


SIM800_verifyResponse(char *cmd , char expd[]){
    i = ex1 = 0;
    char inMsg[5]={'\0','\0','\0','\0','\0'};
    clearBuffer();

Serial_writeText(cmd);
enter();
    wasteAgain();
    while (!Serial_available());//or while (PIR1bits.RCIF==0);
    ex1 = Serial_read();
    do{
        inMsg[i]=ex1;
        while (!Serial_available());// or while (PIR1bits.RCIF==0); //
        ex1 = Serial_read();
        i++;
    }
    while(ex1!='\r');

    if(compareStrings(inMsg , expd)!=0) //STRING COMPARISM
                return 0;
    else
                return 1;
}


int SMS_verifyResponse(char *cmd ,int QuestionVal, char valU[],  char *expd){
    int rre;
    rre=strlen(valU);
    ex1,i=0;
    char inMsg[5]={'\0','\0','\0','\0','\0'};
    clearBuffer();
    if(QuestionVal==yes){
        serialWriteText(cmd);
        serialWriteText("=");
        if(!compareStrings(valU , TxtMode)){//
            Serial_writeText("\"");
            Serial_writeText(valU);
            Serial_writeText("\"");
        }
        else
            Serial_write(valU);
    }
    else
        Serial_writeText(cmd);
enter();
wasteAgain();
    while (!Serial_available());//or while (PIR1bits.RCIF==0);
    ex1 = Serial_read();
    do{
        inMsg[i]=ex1;
        while (!Serial_available());// or while (PIR1bits.RCIF==0); //
        ex1 = Serial_read();
        i++;
        if(ex1==0x20)  //for message
            return 1;
    }
    while(ex1!=0x0D );//

    if(compareStrings(inMsg , expd)!=0) //STRING COMPARISM
                return 0;
    else
                return 1;
}


SIM800_sendSMS(char numbs[],char messTsend[]){
    int rsse;
    rsse=SMS_verifyResponse(sendMessage,yes,numbs,'>');
    if(rsse==1){
        Serial_writeText(messTsend);
        Serial_write(0x1A);
        return 1;
    }
    else
        return 0;
}


wait(){delayms(200);}

SIM800_initSMS(){
    while(SIM800_verifyResponse(verify,ok)); 
    wait();
    while(SIM800_verifyResponse(echoOff,ok));
    wait();
    while(SMS_verifyResponse(MessageFormat,yes,TxtMode,ok));  //PduMode//SIM800_commands(MessageFormat,write,(1+48))//PduMode
    wait();   
}

#endif   //#ifndef _SIM800_H_