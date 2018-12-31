/**************************************************************************

I2C LCD LIBRARY
for writing on the display
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Adeyemi Adekorede

Modified:
(C)2018 None

FileName:     	LCD_I2C.h
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

//EXAMPLE:
/*************************************************************
#include <CloudX/M633.h>
#include <CloudX/LCD_I2C.h>

const char customCharacter[] = {0x1F, 0x11, 0x1B, 0x11, 0x04, 0x11, 0x0E, 0x00};


 setup(){

LCDSerial_setting(16, 2, 0x3F); //column numbers,row numbers, address of i2c serial LCD
LCDSerial_cmd(backLightOn);
LCDSerial_writeText(1, 1, "CloudX");

LCDSerial_cmd(shiftDisplayRight); //SHIFT DISPLAY RIGHT BY ONE POSITION
LCDSerial_write(2, 1, 'A');

LCDSerial_cmd(cursorNoBlink);

//-------------------------------------------------------------------------------
//This function-call writes the custom-character, stored at memory 0, to the LCDs
//row2 col4.
//--------------------------------------------------------------------------------
LCDSerial_writecustomChar(0, 2, 4, customCharacter);
					//custom-char memory position, row, column, custom-char array

loop(){
     
  }
 }
 **********************************************************************/

 
 
 #ifndef _LCD_I2C_H_
 #define _LCD_I2C_H_
 
#include <CloudX/I2C.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSOR_DISPLAYSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00 // screen shifts to the right when the i/d = 1 and left when i/d =0;;;
#define LCD_ENTRYLEFT  0x02
#define LCD_ENTRYSHIFTON 0x01
#define LCD_ENTRYSHIFTOFF 0x00


// flags for display on/off control
#define LCD_DISPLAY_ON_OFF 0x80
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define Bk 0b00001000 
#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit

#define LCD_PCF8574_WEAK_PU      0b11110000 
#define LCD_INIT (0x30|En);
#define LCD_8BIT_INIT 0b00110000 // Used to initialise the interface at the LCD
#define LCD_4BIT_INIT 0b00100000 // Used to initialise the interface at the LCD


#define BUSY_FLAG_MASK          0b10000000 // Used to mask off the status of the busy flag
#define ADDRESS_COUNTER_MASK    0b01111111
#define DD_RAM_ADDRESS          0x80        // Mode : Enables the setting of the Display Data (DD) Ram Address, to be or'ed with require address
#define DD_RAM_ADDRESS_MASK     0b01111111    // Used to mask off the lower 6 bits of valid DD Ram Addresses
#define CGRAM_ADDRESS           0x40
#define CGRAM_ADDRESS_MASK      0b00111111

enum LCDcommands{clear,returnHome,shiftDisplayRight,shiftDisplayLeft, cursorBlink, cursorNoBlink, cursorOff,cursorOn,backLightOn,backLightOff,displayOn,displayOff};

#define I2C_WRITE   0b11111110
#define I2C_READ    0b00000001

unsigned char row;
unsigned char col;
unsigned char addr;

unsigned char func=0;
byte DISPSETTING=0;
byte ENTRYMODE= 0;
byte DISPCONTROL =0;

char busy;

unsigned char char_size1;
unsigned char backlight=0;

void Write_byte(unsigned char addr1, unsigned char data);

unsigned char readbyte(unsigned char addr1);
void Serial_writePEn(unsigned char data);
void Serial_writeNEn(unsigned char data);
unsigned char readbyte(unsigned char addr1);

void LCD_command(unsigned char data);
unsigned char LCD_commandRead();

void LCD4bitswrite(char dataEnrs);
unsigned char LCD4bitsread(char rsEn);

void LCDwritebyte(char value,char Rspinval);
unsigned char LCDreadbyte(char Rspinval);

void LCD_datawrite(unsigned char data);
unsigned char LCD_dataread();

unsigned char LCD_busy();
unsigned char LCD_addrcounterRead();


unsigned char LCD_readDDRAM(unsigned char address);
unsigned char LCD_readCGRAM(unsigned char address);

void LCDSerial_customChar(unsigned char address, unsigned char charArray[]);
void LCDSerial_cmd(byte i);

void Setcursor(byte _row, byte _col);
void LCDSerial_write(byte rows,byte cols,char data);
void LCDSerial_writeCP(char data);
void LCDSerial_writeText(byte rows, byte cols, char *text);
void LCDSerial_writeTextCP(char *text);


void LCD_begin();

void LCDSerial_setting(unsigned char column, unsigned char rows, unsigned char address){

    row = rows;
    col = column;
    addr = address;
    char_size1 = LCD_5x8DOTS;
    LCD_begin();
}

void LCD_begin(){
    I2c_begin(100000);
    func = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    if (row > 1) func =  func | LCD_2LINE ;
    if((row==1) && (char_size1 !=0)) func = func | LCD_5x10DOTS ;
    backlight |= Bk;
    __delay_ms(50);
    LCD4bitswrite(0x30);
    __delay_ms(5);
      LCD4bitswrite(0x30);
        __delay_us(100);
    LCD4bitswrite(0x30);
      __delay_us(100);
    
    LCD4bitswrite(LCD_4BIT_INIT);
    __delay_us(150);

    DISPSETTING = LCD_BLINKOFF | LCD_CURSOROFF |LCD_DISPLAYON | LCD_DISPLAYCONTROL ;
    func = func | LCD_FUNCTIONSET;
    ENTRYMODE = LCD_ENTRYLEFT | LCD_ENTRYSHIFTOFF;
    DISPCONTROL = LCD_CURSOR_DISPLAYSHIFT ; 
    
  
   LCD_command(func);  //func
   
   LCDSerial_cmd(displayOff);
   
   LCDSerial_cmd(displayOn);
   
   LCD_command(ENTRYMODE | LCD_ENTRYMODESET );
   
   LCD_command(DISPSETTING);             
   
   LCDSerial_cmd(clear);

   LCDSerial_cmd(returnHome);
   
}




void Write_byte(unsigned char addr1,unsigned char data){
    data |= backlight;
I2c_start();
addr1 = (addr1<<1)|0;
I2c_write(addr1);
I2c_write(data);
I2c_stop();

}


void Serial_writeNEn(unsigned char data){
Write_byte(addr,data|En); //En high
__delay_us(1);
Write_byte(addr,data & ~En);//En low
__delay_us(50);
}


void Serial_writePEn(unsigned char data){
  Write_byte(addr,data & ~En);  //low
__delay_us(1); //enable pulse must be >450ns
Write_byte(addr,data|En);  //high
__delay_us(50);

}

unsigned char readbyte(unsigned char addr1){
I2c_start();
addr1 = (addr1<<1)|1;
I2c_write(addr1);
unsigned char read;
read = I2c_read(0);// master reads send NACK and then stop bit..
I2c_stop();
return read;
}


unsigned char LCD4bitsread(char rsEn){

    unsigned char read;
 
Write_byte(addr,rsEn|En); //En high
__delay_us(1);
Write_byte(addr,rsEn & ~En);//En low
__delay_us(50);
    
    read = readbyte(addr);
     
Write_byte(addr,rsEn & ~En);  //low
__delay_us(1); //enable pulse must be >450ns
Write_byte(addr,rsEn|En);  //high
__delay_us(50);
     return read;
}
/*
 here is a small sketch that checks if your i2c lcd is working
 setup(){
    unsigned char bool;
LCD_setting(16,2,0x38);
    loop(){

    Write_byte(0x38,0xF0);
    delayMs(10);
    bool = readbyte(0x38);
    }
}
 */
void LCDwritebyte(byte value,byte Rspinval){
    
   byte highnibble;
   byte lownibble;

    highnibble = (value & 0b11110000);
    lownibble = (value & 0b00001111);
    lownibble = (lownibble<<4);
LCD4bitswrite(highnibble|En|Rspinval);
LCD4bitswrite(lownibble|En|Rspinval);        

}
unsigned char LCDreadbyte(char Rspinval){
    char highnibble1;
    char lownibble1;
    LCD4bitswrite((0x00)| En | Rspinval); 
    highnibble1 =LCD4bitsread(LCD_PCF8574_WEAK_PU |(En & ~En)|Rspinval);
    lownibble1= LCD4bitsread(LCD_PCF8574_WEAK_PU | En | Rspinval);
    LCD4bitswrite((0x00)| En | Rspinval);   
    return (highnibble1 & 0xF0)|((lownibble1 & 0x0F)>> 4);

}


/************************mid level commands************/


void LCD_command(unsigned char value){
  __delay_ms(50);
   byte highnibble;
   byte lownibble;
   byte Rspinval = 0x00;
    highnibble = (value & 0b11110000);
    lownibble = (value & 0b00001111);
    lownibble = (lownibble<<4);
LCD4bitswrite(highnibble|En|Rspinval);
LCD4bitswrite(lownibble|En|Rspinval);  
}

unsigned char LCD_commandRead(){
  return LCDreadbyte(0x00);
     
}
void LCD_datawrite(unsigned char data){
    LCDwritebyte(data,Rs);
    

}
unsigned char LCD_dataread(){
    unsigned char read; 
    read = LCDreadbyte(Rs);
    return read;
}

unsigned char LCD_busy(){
  
    busy=(LCDreadbyte(0x00));
    busy=(busy & BUSY_FLAG_MASK  );
    return busy;
}

unsigned char LCD_addrcounterRead(){
   return (LCD_commandRead() & ADDRESS_COUNTER_MASK );
}
unsigned char LCD_readDDRAM(unsigned char address){
    LCD_command(DD_RAM_ADDRESS|(address & DD_RAM_ADDRESS_MASK));
    return LCD_dataread();
}

unsigned char LCD_readCGRAM(unsigned char address){

    LCD_command(CGRAM_ADDRESS |(address & CGRAM_ADDRESS_MASK));
    return LCD_dataread();
}


void Setcursor(byte _row, byte _col){
byte row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
if(_row <= row) _row = _row -1;
if(_col <= col) _col = _col -1;
 LCD_command(DD_RAM_ADDRESS | (_col + row_offsets[_row]));
}


void LCDSerial_write(byte rows,byte cols,char data){
Setcursor(rows,cols);
LCDSerial_writeCP(data);
    }

void LCDSerial_writeCP(char data){
 
   byte highnibble;
   byte lownibble;

    highnibble = (data & 0b11110000);
    lownibble = (data & 0b00001111);
    lownibble = (lownibble<<4);
LCD4bitswrite(highnibble|En|Rs);
LCD4bitswrite(lownibble|En|Rs);
}

void LCDSerial_writeTextCP(char *text){

     unsigned char pnt=0;

                              while(text[pnt] != '\0'){
                                  LCDSerial_writeCP(text[pnt]);
                                  pnt++;
                                 __delay_ms(2);
                                  }
}

void LCDSerial_writeText(byte rows, byte cols, char *text){
Setcursor(rows,cols);
LCDSerial_writeTextCP(text);
}



void LCD4bitswrite(unsigned char dataEnrs){
Write_byte(addr,dataEnrs & ~Rw);
dataEnrs = dataEnrs & ~Rw; 
Write_byte(addr,dataEnrs|En); //En high
__delay_us(1);
Write_byte(addr,dataEnrs & ~En);//En low
__delay_us(50);
}

// this loads a single custom char into the CGRAM OF HD4470

void LCDSerial_createChar(unsigned char address, unsigned char charArray[]) {
    address &= 0x7; 
    LCD_command(0x40 | (address << 3));
    for (int g=0; g<8; g++)LCD_datawrite(charArray[g]);
}

void LCDSerial_cmd(byte i){
    switch(i){
        case clear:
        LCD_command(LCD_CLEARDISPLAY);
        LCD_command(LCD_RETURNHOME);
        break;
        case returnHome:
        LCD_command(LCD_RETURNHOME);
        break;
        case shiftDisplayRight:
        DISPCONTROL = DISPCONTROL | LCD_DISPLAYMOVE |LCD_MOVERIGHT ;
        LCD_command(DISPCONTROL);  
        break;
        case shiftDisplayLeft:
        DISPCONTROL = DISPCONTROL | LCD_DISPLAYMOVE |LCD_MOVELEFT ;
        LCD_command(DISPCONTROL);
        break;
        case cursorBlink:
        LCD_command(DISPSETTING  | LCD_BLINKON);
        break;
        case cursorNoBlink:
        LCD_command(DISPSETTING |LCD_BLINKOFF);
        break;
        case cursorOff:
        LCD_command(DISPSETTING | LCD_CURSOROFF);
        break;
        case cursorOn:
        LCD_command(DISPSETTING | LCD_CURSORON);
        break;
        case backLightOn:
        backlight |= Bk;
        Write_byte(addr,readbyte(addr));
        break;
        case backLightOff:
        backlight |= ~Bk;
        Write_byte(addr,readbyte(addr));
        break;
        case displayOn:
         LCD_command(DISPSETTING |LCD_DISPLAYON);
        break;
        case displayOff:
        LCD_command(DISPSETTING |LCD_DISPLAYOFF);
        break;
    
    }
}

void LCDSerial_writeCustomChar(unsigned char addressCGRAM, unsigned char row, unsigned char col, const char *customCharArray) {
    unsigned char i;
    LCDSerial_cmd(64 + (addressCGRAM *  8));
    for (i = 0; i <= 7; i++) 
        LCDSerial_writeCP(customCharArray[i]);
    LCDSerial_cmd(returnHome);
    
    if((!row) && (!col))
        LCDSerial_writeCP(addressCGRAM);
    else
        LCDSerial_write(row, col, addressCGRAM);
 }   

 #endif   //#ifndef _LCD_I2C_H_