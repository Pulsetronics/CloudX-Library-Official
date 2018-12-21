
/*************************************************************
*       The New CloudX Standardization for Libraries         *
*            For Proper Documentation and Users              *
**************************************************************
* Author:      Ayinde Olayiwola                              *
* Date:        28 - 05 - 2018                                *
* Topic:       Code Standardization Library                  *
* Processor:   Currently Compatible with CloudX 8-bit        *
**************************************************************/


#ifndef _LIBRARY_H
#define _LIBRARY_H

#define _XTAL_FREQ 20000000
#include <xc.h>
//**************** Analog Library ***********************
#define Analog_setting       	  analogSetting         
#define Analog_read  	    	  analogRead            

//****************** Two Wire or I2C Library **************
#define I2C_start 	        I2C_Start             
#define I2C_repeatedStart       I2C_Repeated_Start   
#define I2C_stop                I2C_Stop              
#define I2C_write               I2C_Wr   	              
#define I2C_read                I2C_Read              
#define I2C_init                I2C_Init              

//****************** 128x64 Glcd Library ******************
#define GLCD_extraWrite         xglcdWrite            
#define GLCD_extraWriteText     xglcdWriteText        
#define GLCD_write              GLCD_WRITE_CHAR       
#define glcdWriteText           glcdWriteText         
#define GLCD_writeText          GLCD_WRITE_DATA_TEXT  
#define GLCD_fillScreen         glcdFill_Screen       
#define GLCD_fill               glcdFill              
#define GLCD_drawRectangle      glcdDrawRectangle     
#define GLCD_image              glcd_Image            
#define GLCD_setting            glcdSetting           
#define GLCD_imageWrite         Glcd_Image_Write   
   
//******************** Joystick Library *******************
#define Joystick_upDown         JOYSTICK_Y            
#define Joystick_leftRight      JOYSTICK_X           
#define Joystick_centre         JOYSTICK_CENTRE 
#define Keypad_setting          KeypadSetting
#define Keypad_getKey           getKey

//******************* LCD Library ************************* 
#define LCD_setting             lcdSetting 
#define LCD_writeText           lcdWriteText
#define LCD_writeTextCP         lcdWriteTextCP
#define LCD_write               lcdWrite
#define LCD_writeCP             lcdWriteCP
#define LCD_cmd                 lcdCmd
#define clear                   lcd_clear
#define returnHome              return_home
#define moveCursorRight         move_cursor_right
#define moveCursorLeft          move_cursor_left
#define shiftDisplayRight       shift_display_right    
#define cursorBlink             cursor_blink
#define cursorOn                cursor_on        
#define cursorOff               cursor_off     

#define LCD_setting       Lcd_setting
#define LCD_writeText     Lcd_writeText
#define LCD_write         Lcd_write
#define LCD_writeCP       Lcd_writeCP
#define LCD_writeTextCP   Lcd_writeTextCP
#define LCD_cmd           Lcd_cmd



//********************* DS1307 ******************
#define DS1307_read             read_ds1307
#define DS1307_write            write_ds1307

//********************* Internal Memory ******************
#define Memory_read             readMemory
#define Memory_write            writeMemory

#define EEPROM_write  Memory_write
#define EEPROM_read   Memory_read

//****************** LM35 Temperature Library ************
#define Read_temperature        readTemperature

//*************** Pulse Width Modulation Library *********
#define PWM1_init 		PWM1_Init
#define PWM2_init		PWM2_Init
#define PWM1_duty		PWM1_Duty
#define PWM2_duty		PWM2_Duty
#define PWM1_start		PWM1_Start
#define PWM1_stop		PWM1_Stop
#define PWM2_start		PWM2_Start
#define PWM2_stop		PWM2_Stop

//***************** Random Number Genartor ***************
#define Rand_numGen	       randNumGen

//***************** Segment Library **********************
#define Segment_setting        segmentSetting 
#define Segment_write          segmentWrite

//***************** Serial Library ***********************
#define Serial_begin  	       serialBegin
#define Serial_writeText       serialWriteText
#define Serial_write           serialWrite
#define Serial_read            serialRead

//*************** Software Serial Library ****************
#define Software_serialWriteText    Software_SerialWriteText  
#define Software_serialWrite        Software_SerialWrite
#define Software_serialRead         Software_SerialRead

//**************** Ultrasonic sensor Library *************
#define Ultrasonic_readDistance     readDistance

//***************** ST7735 TFT Display *******************
	        
#define  ST7735_init         	     ST7735_INIT
#define  ST7735_drawPixel     	     drawPixel
#define  ST7735_fillRectangle        fillRectangle
#define	 ST7735_fillScreen	     fillScreen
#define	 ST7735_drawFastVLine        drawFastVLine
#define  ST7735_drawFastHLine        drawFastHLine
#define  ST7735_drawCircle           drawCircle
#define  ST7735_drawCircleHelper     drawCircleHelper
#define  ST7735_fillCircleHelper     fillCircleHelper
#define  ST7735_fillCircle           fillCircle
#define  ST7735_drawRect             drawRect
#define  ST7735_drawLine             drawLine
#define  ST7735_fillRect             fillRect
#define  ST7735_drawRoundRect        drawRoundRect
#define  ST7735_fillRoundRect        fillRoundRect
#define  ST7735_drawTriangle         drawTriangle
#define  ST7735_fillTriangle         fillTriangle
#define  ST7735_drawChar             drawChar
#define  ST7735_setTextWrap          setTextWrap
#define  ST7735_drawText             drawtext
#define  ST7735_invertDisplay        invertDisplay
#define  ST7735_setScrollDefinition  setScrollDefinition  
#define  ST7735_verticalScroll       VerticalScroll
#define  ST7735_normalDisplay        NormalDisplay
#define  ST7735_greenTabInitialize   TFT_GreenTab_Initialize
#define  ST7735_redTabInitialize     TFT_RedTab_Initialize
#define  ST7735_blackTabInitialize   TFT_BlackTab_Initialize
#define  ST7735_testLines            testlines
#define  ST7735_testFastLines        testfastlines
#define  ST7735_testDrawRects        testdrawrects
#define  ST7735_testFillRects        testfillrects
#define  ST7735_testFillCircles      testfillcircles
#define  ST7735_testDrawCircles      testdrawcircles
#define  ST7735_testRoundRects       testroundrects
#define  ST7735_testTriangles        testtriangles

//********************************************************


////////////////////////////////////////////////////////////
//Logic state Configuration defined libary
///////////////////////////////////////////////////////////
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
#define BIN 2
#define HEX 16
#define DEC 10
#define HIGH 1
#define LOW  0
#define INPUT 1
#define OUTPUT 0
#define ON 1
#define OFF 0
#define ON_ALL 0xFF
#define OFF_ALL 0x00




////////////////////////////////////////////////////////////
//Delay loop defined library
////////////////////////////////////////////////////////////
#define delayMs __delay_ms
#define delayUs __delay_us
#define DelayMs __delay_ms
#define DelayUs __delay_us
#define delayms __delay_ms
#define delayus __delay_us

void delay(unsigned int dell){
              while(dell-- != 0) __delay_ms(1);
}


////////////////////////////////////////////////////////////
//Program Configuration loops defined libary
///////////////////////////////////////////////////////////
#define loop()   while(1)
#define setup()     main()


////////////////////////////////////////////////////////////
//ANSI C defined libary
///////////////////////////////////////////////////////////
#define  intTostr itoa
#define  floattostr ftoa
#define  digitalWrite PinSelect
#define  pinSelect PinSelect
#define  digitalRead readPin


////////////////////////////////////////////////////////////
//Operator library
///////////////////////////////////////////////////////////
#define is  ==
#define and &&
#define or ||
#define isNot !=
#define invert ~

/////////////////////////////////////////////////////////////////
//Variable
/////////////////////////////////////////////////////////////////
#define integer int
#define  byte   char

////////////////////////////////////////////////////////////
//Pin Configuration defined libary
///////////////////////////////////////////////////////////
#define pin1 RB0
#define pin2 RB1
#define pin3 RB2
#define pin4 RB3
#define pin5 RB4
#define pin6 RB5
#define pin7 RB6
#define pin8 RB7

#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
#define pin9 RD0
#define pin10 RD1
#define pin11 RD2
#define pin12 RD3
#define pin13 RD4
#define pin14 RD5
#define pin15 RD6
#define pin16 RD7
#endif


////////////////////////////////////////////////////////////
//Analog pin defined libary
///////////////////////////////////////////////////////////
#define A0 17
#define A1 18
#define A2 19
#define A3 20
#define A4 21
#define A5 22


////////////////////////////////////////////////////////////
//PinMode Configuration defined libary
///////////////////////////////////////////////////////////
#define pin1Mode  TRISB0
#define pin2Mode  TRISB1
#define pin3Mode  TRISB2
#define pin4Mode  TRISB3
#define pin5Mode  TRISB4
#define pin6Mode  TRISB5
#define pin7Mode  TRISB6
#define pin8Mode  TRISB7

#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
#define pin9Mode   TRISD0
#define pin10Mode  TRISD1
#define pin11Mode  TRISD2
#define pin12Mode  TRISD3
#define pin13Mode  TRISD4
#define pin14Mode  TRISD5
#define pin15Mode  TRISD6
#define pin16Mode  TRISD7
#endif

/////////////////////////////////////////////////////////////
// PWM PIN CONFIGURATION
/////////////////////////////////////////////////////////////
#define PWM1 RC2
#define PWM2 RC1
#define PWM3 RC0
#define PWM4 RA4



portMode(unsigned char ports, unsigned char bits){
            if(ports is 1) TRISB= bits;
			#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
            if(ports is 2) TRISD= bits;
			#endif
            if(ports is 3) TRISC= bits;
}

portWrite(unsigned char ports, unsigned char bits){
            if(ports is 1) PORTB= bits;
			#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
            if(ports is 2) PORTD= bits;
			#endif
            if(ports is 3) PORTC= bits;
}

PinSelect(char selPins, char segState){
    switch(selPins){
        case 1:     if (segState) pin1=HIGH; else pin1=LOW; break;
        case 2:     if (segState) pin2=HIGH; else pin2=LOW; break;
        case 3:     if (segState) pin3=HIGH; else pin3=LOW; break;
        case 4:     if (segState) pin4=HIGH; else pin4=LOW; break;
        case 5:     if (segState) pin5=HIGH; else pin5=LOW; break;
        case 6:     if (segState) pin6=HIGH; else pin6=LOW; break;
        case 7:     if (segState) pin7=HIGH; else pin7=LOW; break;
        case 8:     if (segState) pin8=HIGH; else pin8=LOW; break;
		
		#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
        case 9:     if (segState) pin9=HIGH; else pin9=LOW; break;
        case 10:     if (segState) pin10=HIGH; else pin10=LOW; break;
        case 11:     if (segState) pin11=HIGH; else pin11=LOW; break;
        case 12:     if (segState) pin12=HIGH; else pin12=LOW; break;
        case 13:     if (segState) pin13=HIGH; else pin13=LOW; break;
        case 14:     if (segState) pin14=HIGH; else pin14=LOW; break;
        case 15:     if (segState) pin15=HIGH; else pin15=LOW; break;
        case 16:     if (segState) pin16=HIGH; else pin16=LOW; break;
	    #endif
		
		case 17:     if (segState) PORTAbits.RA0 = HIGH; else PORTAbits.RA0 = LOW; break;
		case 18:     if (segState) PORTAbits.RA1 = HIGH; else PORTAbits.RA1 = LOW; break;
		case 19:     if (segState) PORTAbits.RA2 = HIGH; else PORTAbits.RA2 = LOW; break;
		case 20:     if (segState) PORTAbits.RA3 = HIGH; else PORTAbits.RA3 = LOW; break;
		case 21:     if (segState) PORTAbits.RA5 = HIGH; else PORTAbits.RA5 = LOW; break;
		
        default: break;
    }

}


void pinMode(char segPortSel, char stater){
    switch(segPortSel){
        case 1:    if(stater==OUTPUT) pin1Mode=OUTPUT;   else pin1Mode=INPUT ; pin1=LOW;break;
        case 2:    if(stater==OUTPUT) pin2Mode=OUTPUT;   else pin2Mode=INPUT ; pin2=LOW;break;
        case 3:    if(stater==OUTPUT)  pin3Mode=OUTPUT;  else pin3Mode=INPUT;  pin3=LOW;break;
        case 4:    if(stater==OUTPUT)  pin4Mode=OUTPUT;  else pin4Mode=INPUT;  pin4=LOW;break;
        case 5:    if(stater==OUTPUT)  pin5Mode=OUTPUT;  else pin5Mode=INPUT;  pin5=LOW;break;
        case 6:    if(stater==OUTPUT)  pin6Mode=OUTPUT;  else pin6Mode=INPUT;  pin6=LOW;break;
        case 7:    if(stater==OUTPUT)   pin7Mode=OUTPUT;  else pin7Mode=INPUT; pin7=LOW;break;
        case 8:    if(stater==OUTPUT)   pin8Mode=OUTPUT;  else pin8Mode=INPUT; pin8=LOW;break;
		
		#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
        case 9:    if(stater==OUTPUT)  pin9Mode=OUTPUT;  else pin9Mode=INPUT;   pin9=LOW;break;
        case 10:   if(stater==OUTPUT)  pin10Mode=OUTPUT;  else pin10Mode=INPUT; pin10=LOW;break;
        case 11:   if(stater==OUTPUT)  pin11Mode=OUTPUT;  else pin11Mode=INPUT; pin11=LOW;break;
        case 12:   if(stater==OUTPUT)  pin12Mode=OUTPUT;  else pin12Mode=INPUT; pin12=LOW;break;
        case 13:   if(stater==OUTPUT)  pin13Mode=OUTPUT;  else pin13Mode=INPUT; pin13=LOW;break;
        case 14:   if(stater==OUTPUT)  pin14Mode=OUTPUT;  else pin14Mode=INPUT; pin14=LOW;break;
        case 15:   if(stater==OUTPUT)  pin15Mode=OUTPUT;  else pin15Mode=INPUT; pin15=LOW;break;
        case 16:   if(stater==OUTPUT)  pin16Mode=OUTPUT;  else pin16Mode=INPUT; pin16=LOW;break;
		#endif
		
		case 17:   if(stater==OUTPUT)  TRISAbits.TRISA0=OUTPUT;  else TRISAbits.TRISA0=INPUT; PORTAbits.RA0=LOW;break;
		case 18:   if(stater==OUTPUT)  TRISAbits.TRISA1=OUTPUT;  else TRISAbits.TRISA1=INPUT; PORTAbits.RA1=LOW;break;
		case 19:   if(stater==OUTPUT)  TRISAbits.TRISA2=OUTPUT;  else TRISAbits.TRISA2=INPUT; PORTAbits.RA2=LOW;break;
		case 20:   if(stater==OUTPUT)  TRISAbits.TRISA3=OUTPUT;  else TRISAbits.TRISA3=INPUT; PORTAbits.RA3=LOW;break;
		case 21:   if(stater==OUTPUT)  TRISAbits.TRISA5=OUTPUT;  else TRISAbits.TRISA5=INPUT; PORTAbits.RA5=LOW;break;
        default: break;
    }
}
 unsigned char readPin(unsigned char stater){
	            switch (stater){
	    case 1:     if (pin1 == HIGH) return HIGH; else return LOW; 
        case 2:     if (pin2 == HIGH) return HIGH; else return LOW; 
        case 3:     if (pin3 == HIGH) return HIGH; else return LOW; 
        case 4:     if (pin4 == HIGH) return HIGH; else return LOW; 
        case 5:     if (pin5 == HIGH) return HIGH; else return LOW; 
        case 6:     if (pin6 == HIGH) return HIGH; else return LOW; 
        case 7:     if (pin7 == HIGH) return HIGH; else return LOW; 
        case 8:     if (pin8 == HIGH) return HIGH; else return LOW; 
		
		#if	defined(_M633_H) || defined(_PRISCILLA_4620_H)
        case 9:      if (pin9 == HIGH) return HIGH; else return LOW; 
        case 10:     if (pin10 == HIGH) return HIGH; else return LOW; 
        case 11:     if (pin11 == HIGH) return HIGH; else return LOW; 
        case 12:     if (pin12 == HIGH) return HIGH; else return LOW; 
        case 13:     if (pin13 == HIGH) return HIGH; else return LOW; 
        case 14:     if (pin14 == HIGH) return HIGH; else return LOW; 
        case 15:     if (pin15 == HIGH) return HIGH; else return LOW; 
        case 16:     if (pin16 == HIGH) return HIGH; else return LOW; 
		#endif
		

	    case 17:     if (PORTAbits.RA0 == HIGH) return HIGH; else return LOW; 
		case 18:     if (PORTAbits.RA1 == HIGH) return HIGH; else return LOW; 
		case 19:     if (PORTAbits.RA2 == HIGH) return HIGH; else return LOW; 
		case 20:     if (PORTAbits.RA3 == HIGH) return HIGH; else return LOW; 
		case 21:     if (PORTAbits.RA5 == HIGH) return HIGH; else return LOW; 

				}
 }
 
#ifdef _M633_H
 ADCON1 = 0x07;
#endif


#endif
//#include<stdlib.h>