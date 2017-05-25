#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//#include <bcm2835.h>
#include "ili9225.h"

#define XMAX    174
#define YMAX    220

#define XMAX2   173
#define YMAX2   219

FontxFile fxG24[2];
FontxFile fxM24[2];
FontxFile fxG16[2];
FontxFile fxM16[2];

#define _DEBUG_ 1

void inputKey() {
  char ch;
  printf("Hit any key");
  scanf("%c",&ch);
}

int main()
{
  int i,j;
  uint16_t Y1,Y2;
  uint16_t X1,X2;
  uint16_t xpos,ypos;
  uint16_t color;
  uint16_t size;
  uint8_t utf[10];

  // You can change font file
  // 16Dot Gothic
  Fontx_init(fxG16,"./fontx/ILGH16XB.FNT","./fontx/ILGZ16XB.FNT");
  // 16Dot Mincho
  Fontx_init(fxM16,"./fontx/ILMH16XB.FNT","./fontx/ILMZ16XF.FNT");
  // 24Dot Gothic
  Fontx_init(fxG24,"./fontx/ILGH24XB.FNT","./fontx/ILGZ24XB.FNT");
  // 24Dot Mincho
  Fontx_init(fxM24,"./fontx/ILMH24XF.FNT","./fontx/ILMZ24XF.FNT");

  lcdInit();
  lcdReset();
  lcdSetup();

  //color bar
  X1=XMAX/3;
  X2=(XMAX/3)*2;
  Y1=YMAX/3;
  Y2=(YMAX/3)*2;
  for(i=0;i<XMAX;i++){
    for(j=0;j<YMAX;j++){
    if(j<Y1){
      lcdDrawPixel(i,j,RED);
    } else if(j<Y2) {
      lcdDrawPixel(i,j,GREEN);
    } else {
      lcdDrawPixel(i,j,BLUE);
    }
   }
  }
if(_DEBUG_)inputKey();

  //coner angle
  lcdFillScreen(WHITE);
  color = RED;
  lcdDrawFillRect(0,0,20,20,color);
  lcdDrawFillArrow(30,30,20,20,10,color);
  xpos = 30;
  ypos = 30;
  strcpy(utf,"0,0");
  lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  color = GRAY;
  lcdDrawFillRect(XMAX-20,0,XMAX,20,color);
  lcdDrawFillArrow(XMAX-30,30,XMAX-20,20,10,color);
  xpos = 120;
  ypos = 30;
  strcpy(utf,"173,0");
  lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  color = BLUE;
  lcdDrawFillRect(0,YMAX-20,20,YMAX,color);
  lcdDrawFillArrow(30,YMAX-30,20,YMAX-20,10,color);
  xpos = 30;
  ypos = 170;
  strcpy(utf,"0,219");
  lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  color = PURPLE;
  lcdDrawFillRect(XMAX-20,YMAX-20,XMAX,YMAX,color);
  lcdDrawFillArrow(XMAX-30,YMAX-30,XMAX-20,YMAX-20,10,color);
  xpos = 120;
  ypos = 170;
  strcpy(utf,"173,219");
  lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
if(_DEBUG_)inputKey();

  //drawLine
  lcdFillScreen(WHITE);
  color=RED;
  for(ypos=0;ypos<YMAX;ypos=ypos+10) {
    lcdDrawLine(0,ypos,XMAX,ypos,color);
  }

  for(xpos=0;xpos<XMAX;xpos=xpos+10) {
    lcdDrawLine(xpos,0,xpos,YMAX,color);
  }
if(_DEBUG_)inputKey();

  //drawRect
  lcdFillScreen(WHITE);
  color=BLUE;
  for(i=10;i<90;i=i+10) {
    lcdDrawRect(i,i,XMAX-i,YMAX-i,color);
  }
if(_DEBUG_)inputKey();

  //drawCircle
  lcdFillScreen(WHITE);
  color=GRAY;
  xpos=XMAX/2;
  ypos=YMAX/2;
  for(i=10;i<220;i=i+10) {
    lcdDrawCircle(xpos,ypos,i,color);
  }
if(_DEBUG_)inputKey();

  //drawRoundRect
  lcdFillScreen(WHITE);
  color=BLUE;
  for(i=10;i<90;i=i+10) {
    lcdDrawRoundRect(i,i,XMAX-i,YMAX-i,10,color);
  }
if(_DEBUG_)inputKey();

  //drawString
  lcdFillScreen(WHITE);
  xpos = 0;
  ypos = YMAX2-(16*1);
  color = BLACK;
  strcpy(utf,"ILI9225");
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = 0;
  ypos = YMAX2-(16*2);
  lcdSetFontFill(CYAN);
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontFill();

  xpos = 0;
  ypos = YMAX2-(16*3);
  lcdSetFontUnderLine(BLACK);
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontUnderLine();

  lcdSetFontDirection(DIRECTION180);
  xpos = XMAX2;
  ypos = 16*1;
  color = BLUE;
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2;
  ypos = 16*2;
  lcdSetFontFill(YELLOW);
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontFill();

  xpos = XMAX2;
  ypos = 16*3;
  lcdSetFontUnderLine(BLUE);
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontUnderLine();

  lcdSetFontDirection(DIRECTION90);
  xpos = XMAX2-(16*1);
  ypos = YMAX2;
  color = RED;
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2-(16*2);
  ypos = YMAX2;
  lcdSetFontFill(GREEN);
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontFill();

  xpos = XMAX2-(16*3);
  ypos = YMAX2;
  lcdSetFontUnderLine(RED);
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontUnderLine();

  lcdSetFontDirection(DIRECTION270);
  xpos = (16*1);
  ypos = 0;
  color = GRAY;
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = (16*2);
  ypos = 0;
  lcdSetFontFill(CYAN);
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontFill();

  xpos = (16*3);
  ypos = 0;
  lcdSetFontUnderLine(GRAY);
  ypos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);
  lcdUnsetFontUnderLine();
if(_DEBUG_)inputKey();

  //draw malti font
  lcdFillScreen(WHITE);
  lcdSetFontDirection(DIRECTION90);

  xpos = XMAX2-(16*1);
  ypos = YMAX2;
  color = BLACK;
  strcpy(utf,"16Dot Gothic");
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2-(16*2);
  strcpy(utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2-(16*3);
  ypos = YMAX2;
  strcpy(utf,"16Dot Mincho");
  xpos = lcdDrawUTF8String(fxM16, xpos, ypos, utf, color);

  xpos = XMAX2-(16*4);
  strcpy(utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxM16, xpos, ypos, utf, color);

  xpos = XMAX2-(16*6)-(24*0);
  ypos = YMAX2;
  strcpy(utf,"24Dot Gothic");
  xpos = lcdDrawUTF8String(fxG24, xpos, ypos, utf, color);

  xpos = XMAX2-(16*6)-(24*1);
  strcpy(utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxG24, xpos, ypos, utf, color);

  xpos = XMAX2-(16*6)-(24*2);
  ypos = YMAX2;
  strcpy(utf,"24Dot Mincho");
  xpos = lcdDrawUTF8String(fxM24, xpos, ypos, utf, color);

  xpos = XMAX2-(16*6)-(24*3);
  strcpy(utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxM24, xpos, ypos, utf, color);
if(_DEBUG_)inputKey();

  //drawFillRect
  lcdFillScreen(WHITE);
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  srand( (unsigned int)time( NULL ) );
  for(i=1;i<100;i++) {
    red=rand()%255;
    green=rand()%255;
    blue=rand()%255;
    color=rgb565_conv(red,green,blue);
    xpos=rand()%XMAX;
    ypos=rand()%YMAX;
    size=rand()%30;
    lcdDrawFillRect(xpos,ypos,xpos+size,ypos+size,color);
  }
}
