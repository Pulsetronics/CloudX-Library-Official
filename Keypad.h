/**************************************************************************

KEYPAD LIBRARY
for keypad input controls
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Oyemade Tumi

Modified:
(C)2018 None

FileName:     	keypad.h
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

/***********************************************************************

Example:

#define NumberOfRows  4            // set display to four rows
#define NumberOfColumns  4            // set display to three columns
char  KeypadCharacters[NumberOfRows][NumberOfColumns] = {
    '1','2','3','A',
    '4','5','6','B',
    '7','8','9','C',
    '*','0','#','D'
};
char RowPins[NumberOfRows] = {1, 2, 3, 4};
char ColumnsPins[NumberOfColumns] = {5, 6, 7, 8};

char Keys;

                   ***********Main COde**************
setup(){
KeypadSetting (PULLUPROW, RowPins, ColumnsPins, NumberOfRows, NumberOfColumns, KeypadCharacters, indicatorPin);
 loop(){
            while(Keys == 0)Keys = getKey();
            Lcd_writeCP(Keys);
            Keys = 0;
  }
 }
                   OR ***********Main COde**************
 * setup(){
KeypadSetting (PULLDOWNCOL, RowPins, ColumnsPins, NumberOfRows, NumberOfColumns, KeypadCharacters, indicatorPin);
 loop(){
            Keys = getKey();
            if(Keys != 0) Lcd_writeCP(Keys);
  }
 }

 ******************************************************************/

#ifndef _KeyPad_H_
#define  _KeyPad_H_

#define PULLUPCOL 0
#define PULLDOWNCOL 1
#define PULLUPROW 2
#define PULLDOWNROW 3


char *KRowPins, *KColPins, *KMap, KIT, KRows, KCols;
byte Indicator;

void Keypad_setting(unsigned char InputType, unsigned char *KRowPinsA, unsigned char *KColPinsA,unsigned char KRowss, unsigned char KColss, char *KMapA, byte indicatorPin)
{
    char KeyLoad;
    KIT       = InputType;
    KRows     = KRowss;
    KCols     = KColss;
    KRowPins  = KRowPinsA;
    KColPins  = KColPinsA;
    KMap      = KMapA;
    Indicator = indicatorPin;
    
    for(KeyLoad=0; KeyLoad<KRowss; KeyLoad++) KRowPins[KeyLoad] = KRowPinsA[KeyLoad]; //Still Consider
    for(KeyLoad=0; KeyLoad<KColss; KeyLoad++) KColPins[KeyLoad] = KColPinsA[KeyLoad]; //Still Consider

    if(KIT==PULLUPCOL || KIT==PULLDOWNCOL )
    {
      for(KeyLoad=0; KeyLoad<KRowss; KeyLoad++) pinMode(KRowPins[KeyLoad], OUTPUT);
      for(KeyLoad=0; KeyLoad<KColss; KeyLoad++) pinMode(KColPins[KeyLoad], INPUT);
    }
    if(KIT==PULLUPROW || KIT==PULLDOWNROW)
    {
    for(KeyLoad=0; KeyLoad<KRowss; KeyLoad++) pinMode(KRowPins[KeyLoad], INPUT);
    for(KeyLoad=0; KeyLoad<KColss; KeyLoad++) pinMode(KColPins[KeyLoad], OUTPUT);
    }
	
	if(indicatorPin) pinMode(indicatorPin, OUTPUT);
}


char getKey(){
    char i, Row, Col, Map=0, KeyTell=0, KeyPress;


        if(KIT==PULLUPCOL){
            for(Row=0; Row<KRows; Row++ ){
                Map = Row;
            for(i=0; i<KRows; i++){
                PinSelect(KRowPins[i], HIGH);
                PinSelect(KRowPins[Map], LOW);
            }
            for(Col =0; Col<KCols; Col++ ){
                if(readPin(KColPins[Col]) == LOW){ 
                   if(Indicator) {
                      digitalWrite(Indicator, ON); delayMs(300); digitalWrite(Indicator, OFF); KeyTell=1; KeyPress = KMap[(Row*KCols)+Col]; }
                   else  {
                      delayMs(300); KeyTell=1; KeyPress = KMap[(Row*KCols)+Col];}
                      } 
                   delayMs(5);
            }
            }
            for(i=0; i<KRows; i++) PinSelect(KRowPins[i], HIGH);
         }

        if(KIT==PULLDOWNCOL){
            for(Row=0; Row<KRows; Row++ ){
                Map = Row;
            for(i=0; i<KRows; i++){
                PinSelect(KRowPins[i], LOW);
                PinSelect(KRowPins[Map], HIGH);
            }
            for(Col =0; Col<KCols; Col++ ){
                if(readPin(KColPins[Col]) == HIGH){ 
                   if(Indicator) {
                      digitalWrite(Indicator, ON); delayMs(300); digitalWrite(Indicator, OFF); KeyTell=1; KeyPress = KMap[(Row*KCols)+Col];}
                   else  {
                      delayMs(300); KeyTell=1; KeyPress = KMap[(Row*KCols)+Col];}
                      }
                   delayMs(5);
            }
            }
            for(i=0; i<KRows; i++) PinSelect(KRowPins[i], LOW);
         }


     
        if(KIT==PULLUPROW){
            for(Row=0; Row<KCols; Row++ ){
                Map = Row;
            for(i=0; i<KRows; i++){
                PinSelect(KColPins[i], HIGH);
                PinSelect(KColPins[Map], LOW);
            }
            for(Col =0; Col<KRows; Col++ ){
                if(readPin(KRowPins[Col]) == LOW){ 
                   if(Indicator) {
                      digitalWrite(Indicator, ON); delayMs(300); digitalWrite(Indicator, OFF); KeyTell=1; KeyPress = KMap[(Col*KCols)+Row];}
                   else  {
                      delayMs(300); KeyTell=1; KeyPress = KMap[(Col*KCols)+Row];}
                      }  
                   delayMs(5);
            }
            }
           for(i=0; i<KCols; i++) PinSelect(KColPins[i] , HIGH);
         }
         
        if(KIT==PULLDOWNROW){
            for(Row=0; Row<KCols; Row++ ){
                Map = Row;
            for(i=0; i<KRows; i++){
                PinSelect(KColPins[i] ,LOW);
                PinSelect(KColPins[Map] ,HIGH);
            }
            for(Col =0; Col<KRows; Col++ ){
                if(readPin(KRowPins[Col]) == HIGH){ 
                   if(Indicator) {
                      digitalWrite(Indicator, ON); delayMs(300); digitalWrite(Indicator, OFF); KeyTell=1; KeyPress = KMap[(Col*KCols)+Row];}
                   else  {
                      delayMs(300); KeyTell=1; KeyPress = KMap[(Col*KCols)+Row];}
                      } 
                   delayMs(5);
            }
            }
            for(i=0; i<KCols; i++) PinSelect(KColPins[i], LOW);
         }

            if(KeyTell) return KeyPress;
            else return  0;
}

#endif    //#ifndef _KeyPad_H_
