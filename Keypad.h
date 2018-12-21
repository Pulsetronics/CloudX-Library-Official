
/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   Keypad.h
 * Version: 1.01
 * Author: 2mee McAlmighty (Oyemade Tumi)
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: KeyPad Library For Any Number of Rows and Columns.
 
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
**********************************************************************************************************/


/*

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

 */

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
