// ili9225.c
// Used by bcm2835 library.(Mike McCauley)
//
//
// [Pin connection]
// ILI9225-SPI     Rpi(pin)
// ------------------------
// CS--------------CS0 (24)  LOW = 0 = Chip Select
// RST-------------IO03( 5)  LOW = 0 = RESET
// RS(DC)----------IO02( 3)  LOW = 0 = COMMAND
// SDA-------------MOSI(19)
// CLK-------------SCLK(23)
// GND-------------0V  ( 6)
// VCC-------------3.3V( 1)
// ------------------------
//  
// [SPI settings]
// ORDER  : MSB First
// MODE   : Mode0
// CLOCK  : 31.25MHz on Rpi/Rpi2, 50MHz on RPI3 
// CS     : CS0
// CS_POL : LOW
//
//

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#ifdef WPI
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#ifndef WPI
#include <bcm2835.h>
#endif
#include "ili9225.h"

#define D_C  2  // GPIO2=D/C
#define RES  3  // GPIO3=RESET
#define C_S  8  // GPIO8

#define _DEBUG_ 0

uint16_t _FONT_DIRECTION_;
uint16_t _FONT_FILL_;
uint16_t _FONT_FILL_COLOR_;
uint16_t _FONT_UNDER_LINE_;
uint16_t _FONT_UNDER_LINE_COLOR_;

uint16_t _model;
uint16_t _width;
uint16_t _height;

#ifdef WPI
// SPI Write Command 8Bit
// D/C=LOW then,write command(8bit)
void lcdWriteCommandByte(uint8_t c){
//  digitalWrite(C_S,LOW);
  digitalWrite(D_C,LOW);
  wiringPiSPIDataRW(0, &c, 1);
//  digitalWrite(C_S,HIGH);
}

// SPI Write Data 8Bit
// D/C=HIGH then,write data(8bit)
void lcdWriteDataByte(uint8_t c){
//  digitalWrite(C_S,LOW);
  digitalWrite(D_C,HIGH);
  wiringPiSPIDataRW(0, &c, 1);
//  digitalWrite(C_S,HIGH);
}
#endif

#ifndef WPI
// SPI Write Command 8Bit
// D/C=LOW then,write command(8bit)
void lcdWriteCommandByte(uint8_t c){
  int data;
  bcm2835_gpio_write(D_C,LOW);
  data = bcm2835_spi_transfer(c);
}

// SPI Write Data 8Bit
// D/C=HIGH then,write data(8bit)
void lcdWriteDataByte(uint8_t c){
  int data;
  bcm2835_gpio_write(D_C,HIGH);
  data = bcm2835_spi_transfer(c);
}
#endif

// SPI Write Data 16Bit
void lcdWriteDataWord(uint16_t w){
  uint8_t hi,lo;
  hi = (char) (w >> 8);
  lo = (char) (w & 0x00FF);
  lcdWriteDataByte(hi);
  lcdWriteDataByte(lo);
}

// SPI Write Command & Data
void lcdWrite9225(uint8_t c, uint16_t d){
  uint8_t lo,hi;
  lcdWriteCommandByte(c);

  hi = (char) (d >> 8);
  lo = (char) (d & 0x00FF);
  lcdWriteDataByte(hi);
  lcdWriteDataByte(lo);
}


#ifdef WPI
// SPI interfase initialize
// MSB,mode0,clock=8,cs0=low
void lcdInit(uint16_t model, uint16_t width, uint16_t height){
  _model = model;
  _width = width;
  _height = height;

  if (wiringPiSetupGpio() == -1) {
    printf("wiringPiSetup Error\n");
    return;
  }
//  wiringPiSPISetup(0, 16000000);
  wiringPiSPISetup(0, 32000000);

  _FONT_DIRECTION_ = DIRECTION0;
  _FONT_FILL_ = false;
  _FONT_UNDER_LINE_ = false;

}
void lcdReset(void){
  pinMode(D_C,OUTPUT);
  pinMode(RES,OUTPUT);
  pinMode(C_S,OUTPUT);
  digitalWrite(D_C,HIGH);   // D/C = H
  digitalWrite(C_S,LOW);

  digitalWrite(RES, LOW);    // Reset low
  delay(100);
  digitalWrite(RES, HIGH);   // Reset high
  delay(100);
}
#endif

#ifndef WPI
// SPI interfase initialize
// MSB,mode0,clock=8,cs0=low
void lcdInit(uint16_t model, uint16_t width, uint16_t height){
  _model = model;
  _width = width;
  _height = height;

  if (bcm2835_init() == -1) {
    printf("bmc2835_init Error\n");
    return;
  }

  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
  // Send a byte to the slave and simultaneously read a byte back from the slave
  // If you tie MISO to MOSI, you should read back what was sent

  _FONT_DIRECTION_ = DIRECTION0;
  _FONT_FILL_ = false;
  _FONT_UNDER_LINE_ = false;

}

// TFT Reset
void lcdReset(void){
  bcm2835_gpio_fsel(D_C,BCM2835_GPIO_FSEL_OUTP); // D/C
  bcm2835_gpio_fsel(RES,BCM2835_GPIO_FSEL_OUTP); // Reset
//  bcm2835_gpio_write(D_C, HIGH);   // D/C = H

  bcm2835_gpio_write(RES, LOW);   // Reset
  bcm2835_delay(100);
  bcm2835_gpio_write(RES, HIGH);   // Reset off
  bcm2835_delay(100); 
}
#endif

// TFT initialize
void lcdSetup(void){
//************* Start Initial Sequence **********//
//  lcdWrite9225(0x01, 0x011C); // set SS and NL bit
  lcdWrite9225(0x01, 0x031C); // set SS and NL bit
  lcdWrite9225(0x02, 0x0100); // set 1 line inversion
  lcdWrite9225(0x03, 0x1030); // set GRAM write direction and BGR=1.
  lcdWrite9225(0x08, 0x0808); // set BP and FP
  lcdWrite9225(0x0C, 0x0000); // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
  lcdWrite9225(0x0F, 0x0801); // Set frame rate
  lcdWrite9225(0x20, 0x0000); // Set GRAM Address
  lcdWrite9225(0x21, 0x0000); // Set GRAM Address
//*************Power On sequence ****************//
  delay(50); // Delay 50ms
  lcdWrite9225(0x10, 0x0A00); // Set SAP,DSTB,STB
  lcdWrite9225(0x11, 0x1038); // Set APON,PON,AON,VCI1EN,VC
  delay(50); // Delay 50ms
  lcdWrite9225(0x12, 0x1121); // Internal reference voltage= Vci;
  lcdWrite9225(0x13, 0x0066); // Set GVDD
  lcdWrite9225(0x14, 0x5F60); // Set VCOMH/VCOML voltage
//------------------------ Set GRAM area --------------------------------//
  lcdWrite9225(0x30, 0x0000);
  lcdWrite9225(0x31, 0x00DB);
  lcdWrite9225(0x32, 0x0000);
  lcdWrite9225(0x33, 0x0000);
  lcdWrite9225(0x34, 0x00DB);
  lcdWrite9225(0x35, 0x0000);
  lcdWrite9225(0x36, 0x00AF);
  lcdWrite9225(0x37, 0x0000);
  lcdWrite9225(0x38, 0x00DB);
  lcdWrite9225(0x39, 0x0000);
// ----------- Adjust the Gamma Curve ----------//
  lcdWrite9225(0x50, 0x0400);
  lcdWrite9225(0x51, 0x060B);
  lcdWrite9225(0x52, 0x0C0A);
  lcdWrite9225(0x53, 0x0105);
  lcdWrite9225(0x54, 0x0A0C);
  lcdWrite9225(0x55, 0x0B06);
  lcdWrite9225(0x56, 0x0004);
  lcdWrite9225(0x57, 0x0501);
  lcdWrite9225(0x58, 0x0E00);
  lcdWrite9225(0x59, 0x000E);
  delay(50); // Delay 50ms
  lcdWrite9225(0x07, 0x1017);
}

// Draw pixel
// x:X coordinate
// y:Y coordinate
// color:color
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color){
  if (x < 0 || x >= _width) return;
  if (y < 0 || y >= _height) return;
  lcdWrite9225(0x20,x); // set column(x) address
  lcdWrite9225(0x21,y); // set column(y) address
  lcdWrite9225(0x22,color); // Memory Write
}

// Draw rectangule of filing
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End X coordinate
// y2:End Y coordinate
// color:color
void lcdDrawFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
  int i,j;
  if (x1 >= _width) return;
  if (x1 < 0) x1=0;
  if (x2 < 0) return;
  if (x2 >= _width) x2=_width-1;
  if (y1 >= _height) return;
  if (y1 < 0) y1=0;
  if (y2 < 0) return;
  if (y2 >= _height) y2=_height-1;

  for(j=y1;j<=y2;j++){
    lcdWrite9225(0x20,x1); // set column(x) address
    lcdWrite9225(0x21,j); // set column(y) address
    lcdWriteCommandByte(0x22); // Memory Write
    for(i=x1;i<=x2;i++) {
      lcdWriteDataWord(color);
    }
  }
}

// Display Off
void lcdDisplayOff(void){
  lcdWrite9225(0x07, 0x1014);
}
 
// Display On
void lcdDisplayOn(void){
  lcdWrite9225(0x07, 0x1017);
}

// Fill screen
// color:color
void lcdFillScreen(uint16_t color) {
  lcdDrawFillRect(0, 0, _width-1, _height-1, color);
}

// Draw line
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End X coordinate
// y2:End Y coordinate
// color:color 
void lcdDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  int i;
  int dx,dy;
  int sx,sy;
  int E;

  /* distance between two points */
  dx = ( x2 > x1 ) ? x2 - x1 : x1 - x2;
  dy = ( y2 > y1 ) ? y2 - y1 : y1 - y2;

  /* direction of two point */
  sx = ( x2 > x1 ) ? 1 : -1;
  sy = ( y2 > y1 ) ? 1 : -1;

  /* inclination < 1 */
  if ( dx > dy ) {
    E = -dx;
    for ( i = 0 ; i <= dx ; i++ ) {
      lcdDrawPixel( x1, y1, color );
      x1 += sx;
      E += 2 * dy;
      if ( E >= 0 ) {
        y1 += sy;
        E -= 2 * dx;
      }
    }
  /* inclination >= 1 */
  } else {
    E = -dy;
    for ( i = 0 ; i <= dy ; i++ ) {
      lcdDrawPixel( x1, y1, color );
      y1 += sy;
      E += 2 * dx;
      if ( E >= 0 ) {
        x1 += sx;
        E -= 2 * dy;
      }
    }
  }
}

// Draw rectangule
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// color:color
void lcdDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  lcdDrawLine(x1,y1,x2,y1,color);
  lcdDrawLine(x2,y1,x2,y2,color);
  lcdDrawLine(x2,y2,x1,y2,color);
  lcdDrawLine(x1,y2,x1,y1,color);
}

// Draw round
// x0:Central X coordinate
// y0:Central Y coordinate
// r:radius
// color:color
void lcdDrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
  int x;
  int y;
  int err;
  int old_err;
  
  x=0;
  y=-r;
  err=2-2*r;
  do{
    lcdDrawPixel(x0-x,y0+y,color); 
    lcdDrawPixel(x0-y,y0-x,color); 
    lcdDrawPixel(x0+x,y0-y,color); 
    lcdDrawPixel(x0+y,y0+x,color); 
    if ((old_err=err)<=x)   err+=++x*2+1;
    if (old_err>y || err>x) err+=++y*2+1;    
  } while(y<0);
  
}

// Draw round of filling
// x0:Central X coordinate
// y0:Central Y coordinate
// r:radius
// color:color
void lcdDrawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
  int x;
  int y;
  int err;
  int old_err;
  int ChangeX;
  
  x=0;
  y=-r;
  err=2-2*r;
  ChangeX=1;
  do{
    if(ChangeX) {
      lcdDrawLine(x0-x,y0-y,x0-x,y0+y,color);
      lcdDrawLine(x0+x,y0-y,x0+x,y0+y,color);
    } // if
    ChangeX=(old_err=err)<=x;
    if (ChangeX)            err+=++x*2+1;
    if (old_err>y || err>x) err+=++y*2+1;
  } while(y<=0);
    
} 

// Draw rectangule with round corner
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// r:radius
// color:color
void lcdDrawRoundRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, uint16_t color)
{
  int x;
  int y;
  int err;
  int old_err;
  unsigned char temp;

  if(x1>x2) {
    temp=x1; x1=x2; x2=temp;
  } // if
  
  if(y1>y2) {
    temp=y1; y1=y2; y2=temp;
  } // if
  
  
  x=0;
  y=-r;
  err=2-2*r;

  do{
    if(x) {
      lcdDrawPixel(x1+r-x,y1+r+y,color); 
      lcdDrawPixel(x2-r+x,y1+r+y,color); 
      lcdDrawPixel(x1+r-x,y2-r-y,color); 
      lcdDrawPixel(x2-r+x,y2-r-y,color);
    } // if 
    if ((old_err=err)<=x)   err+=++x*2+1;
    if (old_err>y || err>x) err+=++y*2+1;    
  } while(y<0);
   
  lcdDrawLine(x1+r,y1  ,x2-r,y1  ,color);
  lcdDrawLine(x1+r,y2  ,x2-r,y2  ,color);
  lcdDrawLine(x1  ,y1+r,x1  ,y2-r,color);
  lcdDrawLine(x2  ,y1+r,x2  ,y2-r,color);  
} 

// Draw arrow
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// w:Width of the botom
// color:color
// Thanks http://k-hiura.cocolog-nifty.com/blog/2010/11/post-2a62.html
void lcdDrawArrow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color){

   double Vx= x1 - x0;
   double Vy= y1 - y0;
   double v = sqrt(Vx*Vx+Vy*Vy);
//   printf("v=%f\n",v);
   double Ux= Vx/v;
   double Uy= Vy/v;

   uint16_t L[2],R[2];
   L[0]= x1 - Uy*w - Ux*v;
   L[1]= y1 + Ux*w - Uy*v;
   R[0]= x1 + Uy*w - Ux*v;
   R[1]= y1 - Ux*w - Uy*v;
//   printf("L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);

//   lcdDrawLine(x0,y0,x1,y1,color);
   lcdDrawLine(x1,y1,L[0],L[1],color);
   lcdDrawLine(x1,y1,R[0],R[1],color);
   lcdDrawLine(L[0],L[1],R[0],R[1],color);
}


// Draw arrow of filling
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// w:Width of the botom
// color:color
void lcdDrawFillArrow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color){

   double Vx= x1 - x0;
   double Vy= y1 - y0;
   double v = sqrt(Vx*Vx+Vy*Vy);
//   printf("v=%f\n",v);
   double Ux= Vx/v;
   double Uy= Vy/v;

   uint16_t L[2],R[2];
   L[0]= x1 - Uy*w - Ux*v;
   L[1]= y1 + Ux*w - Uy*v;
   R[0]= x1 + Uy*w - Ux*v;
   R[1]= y1 - Ux*w - Uy*v;
//   printf("L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);

   lcdDrawLine(x0,y0,x1,y1,color);
   lcdDrawLine(x1,y1,L[0],L[1],color);
   lcdDrawLine(x1,y1,R[0],R[1],color);
   lcdDrawLine(L[0],L[1],R[0],R[1],color);

   int ww;
   for(ww=w-1;ww>0;ww--) {
     L[0]= x1 - Uy*ww - Ux*v;
     L[1]= y1 + Ux*ww - Uy*v;
     R[0]= x1 + Uy*ww - Ux*v;
     R[1]= y1 - Ux*ww - Uy*v;
//     printf("Fill>L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);
     lcdDrawLine(x1,y1,L[0],L[1],color);
     lcdDrawLine(x1,y1,R[0],R[1],color);
   }
}


// RGB565 conversion
// RGB565 is R(5)+G(6)+B(5)=16bit color format.
// Bit image "RRRRRGGGGGGBBBBB"
uint16_t rgb565_conv(uint16_t r,uint16_t g,uint16_t b)
{
   unsigned int RR,GG,BB;
   RR = (r * 31 / 255) << 11;
   GG = (g * 63 / 255) << 5;
   BB = (b * 31 / 255);
   return(RR | GG | BB);
}


// Draw SJIS character
// x:X coordinate
// y:Y coordinate
// sjis: SJIS code
// color:color
int lcdDrawSJISChar(FontxFile *fx, uint16_t x,uint16_t y,uint16_t sjis,uint16_t color) {
  uint16_t xx,yy,bit,ofs;
  unsigned char fonts[128]; // font pattern
  unsigned char pw, ph;
  int h,w;
  uint16_t mask;
  bool rc;
  
if(_DEBUG_)printf("_FONT_DIRECTION_=%d\n",_FONT_DIRECTION_);
//  sjis = UTF2SJIS(utf8);
//if(_DEBUG_)printf("sjis=%04x\n",sjis);

  rc = GetFontx(fx, sjis, fonts, &pw, &ph); // SJIS -> Font pattern
if(_DEBUG_)printf("GetFontx rc=%d pw=%d ph=%d\n",rc,pw,ph);
  if (!rc) return -1;

  uint16_t xd1, yd1;
  uint16_t xd2, yd2;
  uint16_t xss, yss;
  uint16_t xsd, ysd;
  int next;
  if (_FONT_DIRECTION_ == 0) {
    xd1 = +1;
    yd1 = -1;
    xd2 =  0;
    yd2 =  0;
    xss =  x;
    yss =  y + ph - 1;
    xsd =  1;
    ysd =  0;
    next = x + pw;
  } else if (_FONT_DIRECTION_ == 2) {
    xd1 = -1;
    yd1 = +1;
    xd2 =  0;
    yd2 =  0;
    xss =  x;
    yss =  y - ph + 1;
    xsd =  1;
    ysd =  0;
    next = x - pw;
  } else if (_FONT_DIRECTION_ == 1) {
    xd1 =  0;
    yd1 =  0;
    xd2 = -1;
    yd2 = -1;
    xss =  x + ph;
    yss =  y;
    xsd =  0;
    ysd =  1;
    next = y - pw;
  } else if (_FONT_DIRECTION_ == 3) {
    xd1 =  0;
    yd1 =  0;
    xd2 = +1;
    yd2 = +1;
    xss =  x - ph - 1;
    yss =  y;
    xsd =  0;
    ysd =  1;
    next = y + pw;
  }

  int bits;
if(_DEBUG_)printf("xss=%d yss=%d\n",xss,yss);
  ofs = 0;
  yy = yss;
  xx = xss;
  for(h=0;h<ph;h++) {
    if(xsd) xx = xss;
    if(ysd) yy = yss;
//    for(w=0;w<(pw/8);w++) {
    bits = pw;
    for(w=0;w<((pw+4)/8);w++) {
      mask = 0x80;
      for(bit=0;bit<8;bit++) {
        bits--;
        if (bits < 0) continue;
//if(_DEBUG_)printf("xx=%d yy=%d mask=%02x fonts[%d]=%02x\n",xx,yy,mask,ofs,fonts[ofs]);
        if (fonts[ofs] & mask) {
          lcdDrawPixel(xx,yy,color);
        } else {
          if (_FONT_FILL_) lcdDrawPixel(xx,yy,_FONT_FILL_COLOR_);
        }
        if (h == (ph-2) & _FONT_UNDER_LINE_)
          lcdDrawPixel(xx,yy,_FONT_UNDER_LINE_COLOR_);
        if (h == (ph-1) & _FONT_UNDER_LINE_)
          lcdDrawPixel(xx,yy,_FONT_UNDER_LINE_COLOR_);

        xx = xx + xd1;
        yy = yy + yd2;
        mask = mask >> 1;
      }
      ofs++;
    }
    yy = yy + yd1;
    xx = xx + xd2;

  }
  
  if (next < 0) next = 0;
  return next;
}

// Draw UTF8 character
// x:X coordinate
// y:Y coordinate
// utf8: UTF8 code
// color:color
int lcdDrawUTF8Char(FontxFile *fx, uint16_t x,uint16_t y,uint8_t *utf8,uint16_t color) {
  uint16_t sjis[1];
  
  sjis[0] = UTF2SJIS(utf8);
if(_DEBUG_)printf("sjis=%04x\n",sjis[0]);
  return lcdDrawSJISChar(fx,x,y,sjis[0],color);
}

// Draw UTF8 string
// x:X coordinate
// y:Y coordinate
// utfs: UTF8 string
// color:color
int lcdDrawUTF8String(FontxFile *fx, uint16_t x,uint16_t y,uint8_t *utfs,uint16_t color) {

  int i;
  int spos;
  uint16_t sjis[64];
  spos = String2SJIS(utfs, strlen(utfs), sjis, 64);
if(_DEBUG_)printf("spos=%d\n",spos);
  for(i=0;i<spos;i++) {
if(_DEBUG_)printf("sjis[%d]=%x y=%d\n",i,sjis[i],y);
    if (_FONT_DIRECTION_ == 0)
      x=lcdDrawSJISChar(fx,x,y,sjis[i],color);
    if (_FONT_DIRECTION_ == 1)
      y=lcdDrawSJISChar(fx,x,y,sjis[i],color);
    if (_FONT_DIRECTION_ == 2)
      x=lcdDrawSJISChar(fx,x,y,sjis[i],color);
    if (_FONT_DIRECTION_ == 3)
      y=lcdDrawSJISChar(fx,x,y,sjis[i],color);
  }
  if (_FONT_DIRECTION_ == 0) return x;
  if (_FONT_DIRECTION_ == 2) return x;
  if (_FONT_DIRECTION_ == 1) return y;
  if (_FONT_DIRECTION_ == 3) return y;
}

// Set font direction
// dir:Direction
void lcdSetFontDirection(uint16_t dir) {
  _FONT_DIRECTION_ = dir;
}

// Set font filling
// color:fill color
void lcdSetFontFill(uint16_t color) {
  _FONT_FILL_ = true;
  _FONT_FILL_COLOR_ = color;
}

// UnSet font filling
void lcdUnsetFontFill(void) {
  _FONT_FILL_ = false;
}

// Set font underline
// color:frame color
void lcdSetFontUnderLine(uint16_t color) {
  _FONT_UNDER_LINE_ = true;
  _FONT_UNDER_LINE_COLOR_ = color;
}

// UnSet font filling
void lcdUnsetFontUnderLine(void) {
  _FONT_UNDER_LINE_ = false;
}



