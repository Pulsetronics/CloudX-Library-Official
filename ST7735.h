/**************************************************************************

ST7735 DRIVER TFT LIBRARY
for writing on tft display
Version: 	2.0 BETA
Release date:	

Author:
(C)2017 Ayinde Olayiwola

Modified:
(C)2018 None


FileName:     	ST7735.h
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


#ifndef _ST7735_H_
#define _ST7735_H_

/*
char TFT_CSSS, TFT_CLKKK, TFT_DATAAA, TFT_DCCC;


void ST7735_INIT(char TFT_CSS,char TFT_DCC,char TFT_CLKK,char TFT_DATAA)
{
    pinMode(TFT_CSS,OUTPUT); pinMode(TFT_DCC,OUTPUT); pinMode(TFT_CLKK,OUTPUT); pinMode(TFT_DATAA,OUTPUT); 
    TFT_CSSS = TFT_CSS; TFT_CLKKK = TFT_CLKK;  TFT_DCCC = TFT_DCC; TFT_DATAAA = TFT_DATAA;
    
   }



#define  TFT_CS    TFT_CSSS
#define  TFT_DC    TFT_DCCC
#define  TFT_CLK   TFT_CLKKK
#define  TFT_DATA  TFT_DATAAA
//#define TFT_SPI_HARDWARE
*/

bool wrap = TRUE;
unsigned char colstart = 0, rowstart = 0, _tft_type;
#define _swap(a, b) { signed int t; t = a; a = b; b = t;}
#define _width         128
#define _height        160
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_PTLAR   0x30
#define ST7735_VSCRDEF 0x33
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_VSCRSADD 0x37
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF



const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x5F, 0x00, 0x00,
0x00, 0x07, 0x00, 0x07, 0x00,
0x14, 0x7F, 0x14, 0x7F, 0x14,
0x24, 0x2A, 0x7F, 0x2A, 0x12,
0x23, 0x13, 0x08, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x00, 0x08, 0x07, 0x03, 0x00,
0x00, 0x1C, 0x22, 0x41, 0x00,
0x00, 0x41, 0x22, 0x1C, 0x00,
0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
0x08, 0x08, 0x3E, 0x08, 0x08,
0x00, 0x80, 0x70, 0x30, 0x00,
0x08, 0x08, 0x08, 0x08, 0x08,
0x00, 0x00, 0x60, 0x60, 0x00,
0x20, 0x10, 0x08, 0x04, 0x02,
0x3E, 0x51, 0x49, 0x45, 0x3E,
0x00, 0x42, 0x7F, 0x40, 0x00,
0x72, 0x49, 0x49, 0x49, 0x46,
0x21, 0x41, 0x49, 0x4D, 0x33,
0x18, 0x14, 0x12, 0x7F, 0x10,
0x27, 0x45, 0x45, 0x45, 0x39,
0x3C, 0x4A, 0x49, 0x49, 0x31,
0x41, 0x21, 0x11, 0x09, 0x07,
0x36, 0x49, 0x49, 0x49, 0x36,
0x46, 0x49, 0x49, 0x29, 0x1E,
0x00, 0x00, 0x14, 0x00, 0x00,
0x00, 0x40, 0x34, 0x00, 0x00,
0x00, 0x08, 0x14, 0x22, 0x41,
0x14, 0x14, 0x14, 0x14, 0x14,
0x00, 0x41, 0x22, 0x14, 0x08,
0x02, 0x01, 0x59, 0x09, 0x06,
0x3E, 0x41, 0x5D, 0x59, 0x4E,
0x7C, 0x12, 0x11, 0x12, 0x7C,
0x7F, 0x49, 0x49, 0x49, 0x36,
0x3E, 0x41, 0x41, 0x41, 0x22,
0x7F, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x49, 0x49, 0x49, 0x41,
0x7F, 0x09, 0x09, 0x09, 0x01,
0x3E, 0x41, 0x41, 0x51, 0x73,
0x7F, 0x08, 0x08, 0x08, 0x7F,
0x00, 0x41, 0x7F, 0x41, 0x00,
0x20, 0x40, 0x41, 0x3F, 0x01,
0x7F, 0x08, 0x14, 0x22, 0x41,
0x7F, 0x40, 0x40, 0x40, 0x40,
0x7F, 0x02, 0x1C, 0x02, 0x7F,
0x7F, 0x04, 0x08, 0x10, 0x7F,
0x3E, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x09, 0x09, 0x09, 0x06,
0x3E, 0x41, 0x51, 0x21, 0x5E,
0x7F, 0x09, 0x19, 0x29, 0x46
};

const char Font2[] = {
0x26, 0x49, 0x49, 0x49, 0x32,
0x03, 0x01, 0x7F, 0x01, 0x03,
0x3F, 0x40, 0x40, 0x40, 0x3F,
0x1F, 0x20, 0x40, 0x20, 0x1F,
0x3F, 0x40, 0x38, 0x40, 0x3F,
0x63, 0x14, 0x08, 0x14, 0x63,
0x03, 0x04, 0x78, 0x04, 0x03,
0x61, 0x59, 0x49, 0x4D, 0x43,
0x00, 0x7F, 0x41, 0x41, 0x41,
0x02, 0x04, 0x08, 0x10, 0x20,
0x00, 0x41, 0x41, 0x41, 0x7F,
0x04, 0x02, 0x01, 0x02, 0x04,
0x40, 0x40, 0x40, 0x40, 0x40,
0x00, 0x03, 0x07, 0x08, 0x00,
0x20, 0x54, 0x54, 0x78, 0x40,
0x7F, 0x28, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x28,
0x38, 0x44, 0x44, 0x28, 0x7F,
0x38, 0x54, 0x54, 0x54, 0x18,
0x00, 0x08, 0x7E, 0x09, 0x02,
0x18, 0xA4, 0xA4, 0x9C, 0x78,
0x7F, 0x08, 0x04, 0x04, 0x78,
0x00, 0x44, 0x7D, 0x40, 0x00,
0x20, 0x40, 0x40, 0x3D, 0x00,
0x7F, 0x10, 0x28, 0x44, 0x00,
0x00, 0x41, 0x7F, 0x40, 0x00,
0x7C, 0x04, 0x78, 0x04, 0x78,
0x7C, 0x08, 0x04, 0x04, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xFC, 0x18, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x18, 0xFC,
0x7C, 0x08, 0x04, 0x04, 0x08,
0x48, 0x54, 0x54, 0x54, 0x24,
0x04, 0x04, 0x3F, 0x44, 0x24,
0x3C, 0x40, 0x40, 0x20, 0x7C,
0x1C, 0x20, 0x40, 0x20, 0x1C,
0x3C, 0x40, 0x30, 0x40, 0x3C,
0x44, 0x28, 0x10, 0x28, 0x44,
0x4C, 0x90, 0x90, 0x90, 0x7C,
0x44, 0x64, 0x54, 0x4C, 0x44,
0x00, 0x08, 0x36, 0x41, 0x00,
0x00, 0x00, 0x77, 0x00, 0x00,
0x00, 0x41, 0x36, 0x08, 0x00,
0x02, 0x01, 0x02, 0x04, 0x02
};

void spiwrite(unsigned char spidata){
  #ifndef TFT_SPI_HARDWARE
    char ss;
    for(ss = 0x80; ss; ss >>= 1) {
    if (spidata & ss)  TFT_DATA=HIGH;
    else               TFT_DATA=LOW;
    TFT_CLK=HIGH;
    TFT_CLK=LOW;}
 // #else
 //   SPI_WRITE(spidata);
  #endif
}
void write_command(unsigned char cmd_){
  TFT_CS=LOW;
  TFT_DC=LOW;
  spiwrite(cmd_);
  TFT_CS=HIGH;
}
void write_data(unsigned char data_){
  TFT_CS=LOW;
  TFT_DC=HIGH;
  spiwrite(data_);
  TFT_CS=HIGH;
}
void Bcmd(){
  write_command(ST7735_SWRESET);
  delayms(50);
  write_command(ST7735_SLPOUT);
  delayms(500);
  write_command(ST7735_COLMOD);
  write_data(0x05);
  delayms(10);
  write_command(ST7735_FRMCTR1);
  write_data(0x00);
  write_data(0x06);
  write_data(0x03);
  delayms(10);
  write_command(ST7735_MADCTL);
  write_data(0x08);
  write_command(ST7735_DISSET5);
  write_data(0x15);
  write_data(0x02);
  write_command(ST7735_INVCTR);
  write_data(0x00);
  write_command(ST7735_PWCTR1);
  write_data(0x02);
  write_data(0x70);
  delayms(10);
  write_command(ST7735_PWCTR2);
  write_data(0x05);
  write_command(ST7735_PWCTR3);
  write_data(0x01);
  write_data(0x02);
  write_command(ST7735_VMCTR1);
  write_data(0x3C);
  write_data(0x38);
  delayms(10);
  write_command(ST7735_PWCTR6);
  write_data(0x11);
  write_data(0x15);
  write_command(ST7735_GMCTRP1);
  write_data(0x09); write_data(0x16); write_data(0x09); write_data(0x20);
  write_data(0x21); write_data(0x1B); write_data(0x13); write_data(0x19);
  write_data(0x17); write_data(0x15); write_data(0x1E); write_data(0x2B);
  write_data(0x04); write_data(0x05); write_data(0x02); write_data(0x0E);
  write_command(ST7735_GMCTRN1);
  write_data(0x0B); write_data(0x14); write_data(0x08); write_data(0x1E);
  write_data(0x22); write_data(0x1D); write_data(0x18); write_data(0x1E);
  write_data(0x1B); write_data(0x1A); write_data(0x24); write_data(0x2B);
  write_data(0x06); write_data(0x06); write_data(0x02); write_data(0x0F);
  delayms(10);
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x02); write_data(0x08); write_data(0x81);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x01); write_data(0x08); write_data(0xA0);
  write_command(ST7735_NORON);
  delayms(10);
  write_command(ST7735_DISPON);
  delayms(500);
}
void Rcmd1(){
  write_command(ST7735_SWRESET);
  delayms(150);
  write_command(ST7735_SLPOUT);
  delayms(500);
  write_command(ST7735_FRMCTR1);
  write_data(0x01);
  write_data(0x2C);
  write_data(0x2D);
  write_command(ST7735_FRMCTR2);
  write_data(0x01);
  write_data(0x2C);
  write_data(0x2D);
  write_command(ST7735_FRMCTR3);
  write_data(0x01); write_data(0x2C); write_data(0x2D);
  write_data(0x01); write_data(0x2C); write_data(0x2D);
  write_command(ST7735_INVCTR);
  write_data(0x07);
  write_command(ST7735_PWCTR1);
  write_data(0xA2);
  write_data(0x02);
  write_data(0x84);
  write_command(ST7735_PWCTR2);
  write_data(0xC5);
  write_command(ST7735_PWCTR3);
  write_data(0x0A);
  write_data(0x00);
  write_command(ST7735_PWCTR4);
  write_data(0x8A);
  write_data(0x2A);
  write_command(ST7735_PWCTR5);
  write_data(0x8A);
  write_data(0xEE);
  write_command(ST7735_VMCTR1);
  write_data(0x0E);
  write_command(ST7735_INVOFF);
  write_command(ST7735_MADCTL);
  write_data(0xC8);
  write_command(ST7735_COLMOD);
  write_data(0x05);
}
void Rcmd2green(){
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x02);
  write_data(0x00); write_data(0x7F + 0x02);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x01);
  write_data(0x00); write_data(0x9F + 0x01);
}
void Rcmd2red(){
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x00);
  write_data(0x00); write_data(0x7F);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x00);
  write_data(0x00); write_data(0x9F);
}
void Rcmd3(){
  write_command(ST7735_GMCTRP1);
  write_data(0x02); write_data(0x1C); write_data(0x07); write_data(0x12);
  write_data(0x37); write_data(0x32); write_data(0x29); write_data(0x2D);
  write_data(0x29); write_data(0x25); write_data(0x2B); write_data(0x39);
  write_data(0x00); write_data(0x01); write_data(0x03); write_data(0x10);
  write_command(ST7735_GMCTRN1);
  write_data(0x03); write_data(0x1D); write_data(0x07); write_data(0x06);
  write_data(0x2E); write_data(0x2C); write_data(0x29); write_data(0x2D);
  write_data(0x2E); write_data(0x2E); write_data(0x37); write_data(0x3F);
  write_data(0x00); write_data(0x00); write_data(0x02); write_data(0x10);
  write_command(ST7735_NORON);
  delayms(10);
  write_command(ST7735_DISPON);
  delayms(100);
}
void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1){
  write_command(ST7735_CASET);
  write_data(0);
  write_data(x0 + colstart);
  write_data(0);
  write_data(x1 + colstart);
  write_command(ST7735_RASET);
  write_data(0);
  write_data(y0 + rowstart);
  write_data(0);
  write_data(y1 + rowstart);
  write_command(ST7735_RAMWR); // Write to RAM
}
void drawPixel(unsigned char x, unsigned char y, unsigned int color){
  if((x >= _width) || (y >= _height))
    return;
  setAddrWindow(x,y,x+1,y+1);
  write_data(color >> 8);
  write_data(color & 0xFF);
}
void fillRectangle(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color){
  unsigned char hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)
    w = _width  - x;
  if((y + h - 1) >= _height)
    h = _height - y;
  setAddrWindow(x, y, x+w-1, y+h-1);
  hi = color >> 8; lo = color;
  TFT_DC=HIGH;
  TFT_CS=LOW;
  for(y=h; y>0; y--) {
    for(x = w; x > 0; x--) {
      spiwrite(hi);
      spiwrite(lo);
    }
  }
  TFT_CS=HIGH;
}
void fillScreen(unsigned int color) {
  fillRectangle(0, 0, _width, _height, color);
}
void drawFastVLine(unsigned char x, unsigned char y, unsigned char h, unsigned int color){
  unsigned char hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((y + h - 1) >= _height)
    h = _height - y;
  hi = color >> 8; lo = color;
  setAddrWindow(x, y, x, y + h - 1);
  TFT_DC=HIGH;
  TFT_CS=LOW;
  while (h--) {
    spiwrite(hi);
    spiwrite(lo);
  }
  TFT_CS=HIGH;
}
void drawFastHLine(unsigned char x, unsigned char y, unsigned char w, unsigned int color){
  unsigned char hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)
    w = _width - x;
  hi = color >> 8; lo = color;
  setAddrWindow(x, y, x + w - 1, y);
  TFT_DC=HIGH;
  TFT_CS=LOW;
  while (w--) {
    spiwrite(hi);
    spiwrite(lo);
  }
   TFT_CS=HIGH;
}
void drawCircle(signed int x0, signed int y0, signed int r, unsigned int color) {
  signed int f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  drawPixel(x0  , y0 + r, color);
  drawPixel(x0  , y0 - r, color);
  drawPixel(x0+r, y0    , color);
  drawPixel(x0-r, y0    , color);
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}
void drawCircleHelper(signed int x0, signed int y0, signed int r, unsigned char cornername, unsigned int color) {
  signed int f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}
void fillCircleHelper(signed int x0, signed int y0, signed int r, unsigned char cornername, signed int delta, unsigned int color) {
  signed int f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}
void fillCircle(signed int x0, signed int y0, signed int r, unsigned int color) {
  drawFastVLine(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
void drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color){
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y + h - 1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x + w - 1, y, h, color);
}
void drawLine(signed int x0, signed int y0, signed int x1, signed int y1, unsigned int color){
  signed int steep, dx, dy, err, ystep;
  steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap(x0,y0);
    _swap(x1,y1);
  }
  if (x0 > x1) {
    _swap(x0,x1);
    _swap(y0,y1);
  }
  dx = x1 - x0;
  dy = abs(y1-y0);

  err = dx / 2;
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
void fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color) {
  signed int i;
  // Update in subclasses if desired!
  for (i = x; i < x + w; i++) {
    drawFastVLine(i, y, h, color);
  }
}
void drawRoundRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char r, unsigned int color) {
  drawFastHLine(x+r  , y    , w-2*r, color);
  drawFastHLine(x+r  , y+h-1, w-2*r, color);
  drawFastVLine(x    , y+r  , h-2*r, color);
  drawFastVLine(x+w-1, y+r  , h-2*r, color);
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}
void fillRoundRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char r, unsigned int color) {
  fillRect(x+r, y, w-2*r, h, color);
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
void drawTriangle(signed int x0, signed int y0, signed int x1, signed int y1, signed int x2, signed int y2, unsigned int color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
void fillTriangle(signed int x0, signed int y0, signed int x1, signed int y1, signed int x2, signed int y2, unsigned int color) {
  signed int a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12, sa, sb;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if (y1 > y2) {
    _swap(y2, y1); _swap(x2, x1);
  }
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;
    sa   = 0;
    sb   = 0;
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it
  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b - a + 1, color);
  }
  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}
void drawChar(unsigned char x, unsigned char y, unsigned char c, unsigned int color, unsigned int bg,  unsigned char size){
  char i, j;
  if((x >= _width) || (y >= _height))
    return;
  if(size < 1) size = 1;
  if((c < ' ') || (c > '~'))
    c = '?';
  for(i=0; i<5; i++ ) {
    unsigned char line;
    if(c < 'S')
      line = Font[(c - 32)*5 + i];
    else
      line = Font2[(c - 'S')*5 + i];
    for(j=0; j<7; j++, line >>= 1) {
      if(line & 0x01) {
        if(size == 1) drawPixel(x+i, y+j, color);
        else          fillRect(x+(i*size), y+(j*size), size, size, color);
      }
      else if(bg != color) {
           if(size == 1) drawPixel(x+i, y+j, bg);
           else          fillRect(x+i*size, y+j*size, size, size, bg);
        }
    }
  }
}
void setTextWrap(bool w){
  wrap = w;
}
void drawtext(unsigned char x, unsigned char y, char *_text, unsigned int color, unsigned int bg, unsigned char size){
  unsigned char cursor_x, cursor_y;
  unsigned int textsize, i;
  cursor_x = x, cursor_y = y;
  textsize = strlen(_text);
  for(i = 0; i < textsize; i++){
    if(wrap && ((cursor_x + size * 5) > _width)){
      cursor_x = 0;
      cursor_y = cursor_y + size * 7 + 3 ;
      if(cursor_y > _height) cursor_y = _height;
      if(_text[i] == 0x20) goto _skip; }
    drawChar(cursor_x, cursor_y, _text[i], color, bg, size);
    cursor_x = cursor_x + size * 6;
    if(cursor_x > _width) cursor_x = _width;
    _skip:;}
}
void invertDisplay(bool i) {
  if(i)
    write_command(ST7735_INVON);
  else
    write_command(ST7735_INVOFF);
}
void setScrollDefinition(unsigned char top_fix_height, unsigned char bottom_fix_height, bool _scroll_direction){
  unsigned char scroll_height;
  scroll_height = _height - top_fix_height - bottom_fix_height;
  write_command(ST7735_VSCRDEF);
  write_data(0x00);
  write_data(top_fix_height);
  write_data(0x00);
  write_data(scroll_height);
  write_data(0x00);
  write_data(bottom_fix_height);
  write_command(ST7735_MADCTL);
  if(_scroll_direction){
    if(_tft_type == 0){
      write_data(0xD8);
    }
    if(_tft_type == 1){
      write_data(0xD0);
    }
    if(_tft_type == 2){
      write_data(0x18);
    }
  }
  else{
    if(_tft_type == 0){
      write_data(0xC8);
    }
    if(_tft_type == 1){
      write_data(0xC0);
    }
    if(_tft_type == 2){
      write_data(0x08);
    }
  }
}
void VerticalScroll(unsigned char _vsp) {
  write_command(ST7735_VSCRSADD);
  write_data(0x00);
  write_data(_vsp);
}
void NormalDisplay(){
  write_command(ST7735_NORON);
}
int Color565(int r, int g, int b){           // Convert 24-bit color to 16-bit color
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void TFT_GreenTab_Initialize(){
  TFT_CS=HIGH;
  TFT_DC=LOW;

  #ifndef TFT_SPI_HARDWARE
    TFT_CLK=LOW;
    TFT_DATA=LOW;
   
 // #else
 //   SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Rcmd1();
  Rcmd2green();
  Rcmd3();
  colstart = 2;
  rowstart = 1;
  _tft_type = 0;
}
void TFT_RedTab_Initialize(){
  TFT_CS=HIGH;
  TFT_DC=LOW;
  pinMode(TFT_CS,OUTPUT);
  pinMode(TFT_DC,OUTPUT);
 #ifndef TFT_SPI_HARDWARE
    TFT_CLK=LOW;
    TFT_DATA=LOW;
 // #else
 //   SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Rcmd1();
  Rcmd2red();
  Rcmd3();
  _tft_type = 0;
}
void TFT_BlackTab_Initialize(){
  TFT_CS=HIGH;
  TFT_DC=LOW;
    TFT_CLK=LOW;
    TFT_DATA=LOW;
   

 Rcmd1();
  Rcmd2red();
 Rcmd3();
  write_command(ST7735_MADCTL);
  write_data(0xC0);
  _tft_type = 1;
}
void TFT_ST7735B_Initialize(){
  TFT_CS=HIGH;
  TFT_DC=LOW;
  
  #ifndef TFT_SPI_HARDWARE
    TFT_CLK=LOW;
    TFT_DATA=LOW;
   
 // #else
 //   SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Bcmd();
  _tft_type = 2;
}


void testlines(unsigned int color) {
  unsigned char x, y;
  fillScreen(ST7735_BLACK);
  for (x=0; x < _width; x+=6) {
    drawLine(0, 0, x, _height-1, color);
  }
  for (y=0; y < _height; y+=6) {
    drawLine(0, 0, _width-1, y, color);
  }

  fillScreen(ST7735_BLACK);
  for (x=0; x < _width; x+=6) {
    drawLine(_width-1, 0, x, _height-1, color);
  }
  for (y=0; y < _height; y+=6) {
    drawLine(_width-1, 0, 0, y, color);
  }

  fillScreen(ST7735_BLACK);
  for (x=0; x < _width; x+=6) {
    drawLine(0, _height-1, x, 0, color);
  }
  for (y=0; y < _height; y+=6) {
    drawLine(0, _height-1, _width-1, y, color);
  }

  fillScreen(ST7735_BLACK);
  for (x=0; x < _width; x+=6) {
    drawLine(_width-1, _height-1, x, 0, color);
  }
  for (y=0; y < _height; y+=6) {
    drawLine(_width-1, _height-1, 0, y, color);
  }

}

void testfastlines(unsigned int color1, unsigned int color2) {
  int x, y;
  fillScreen(ST7735_BLACK);
  for (y = 0; y < _height; y += 5) {
    drawFastHLine(0, y, _width, color1);
  }
  for (x = 0; x < _width; x += 5) {
    drawFastVLine(x, 0, _height, color2);
  }
}
void testdrawrects(unsigned int color) {
  int x;
  fillScreen(ST7735_BLACK);
  for (x = 0; x < _width; x+=6) {
    drawRect(_width/2 -x/2, _height/2 -x/2 , x, x, color);
  }
}
void testfillrects(unsigned char color1, unsigned int color2) {
  int x;
  fillScreen(ST7735_BLACK);
  for (x = _width - 1; x > 6; x -= 6) {
    fillRect(_width/2 -x/2, _height/2 -x/2 , x, x, color1);
    drawRect(_width/2 -x/2, _height/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(unsigned char radius, unsigned int color) {
  int x, y;
  for (x = radius; x < _width; x += radius * 2) {
    for (y = radius; y < _height; y += radius * 2) {
      fillCircle(x, y, radius, color);
    }
  }
}
void testdrawcircles(unsigned char radius, unsigned int color) {
  int x, y;
  for (x = 0; x < _width + radius; x += radius * 2) {
    for (y = 0; y < _height + radius; y += radius * 2) {
      drawCircle(x, y, radius, color);
    }
  }
}
 
void testroundrects() {
  char i, t;
  unsigned int color = 100;
  fillScreen(ST7735_BLACK);
  for(t = 0 ; t <= 4; t += 1) {
    unsigned char x = 0, y = 0, w = _width - 2, h = _height - 2;
    for(i = 0 ; i <= 16; i++) {
      drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}
void testtriangles() {
  unsigned char t, w, x, y, z;
  unsigned int color = 0xF800;
  fillScreen(ST7735_BLACK);
  w = _width/2, x = _height - 1, y = 0, z = _width;
  for(t = 0 ; t <= 15; t++) {
    drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

#endif   //#ifndef _ST7735_H_