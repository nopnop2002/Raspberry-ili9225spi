#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ili9225.h"

#define XMAX    174
#define YMAX    220

#define XMAX2   173
#define YMAX2   219

FontxFile fxG32[2];
FontxFile fxM32[2];
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
  uint16_t xpos,ypos;
  uint16_t color;
  uint8_t utf[64];

  // You can change font file
  // 32Dot Gothic
  Fontx_init(fxG32,"./fontx/ILGH32XB.FNT","./fontx/ILGZ32XB.FNT");
  // 32Dot Mincho
  Fontx_init(fxM32,"./fontx/ILMH32XF.FNT","./fontx/ILMZ32XF.FNT");
  // 24Dot Gothic
  Fontx_init(fxG24,"./fontx/ILGH24XB.FNT","./fontx/ILGZ24XB.FNT");
  // 24Dot Mincho
  Fontx_init(fxM24,"./fontx/ILMH24XF.FNT","./fontx/ILMZ24XF.FNT");
  // 16Dot Gothic
  Fontx_init(fxG16,"./fontx/ILGH16XB.FNT","./fontx/ILGZ16XB.FNT");
  // 16Dot Mincho
  Fontx_init(fxM16,"./fontx/ILMH16XB.FNT","./fontx/ILMZ16XF.FNT");

  lcdInit(0x9225,174,220);
  lcdReset();
  lcdSetup();

  //drawString
  lcdFillScreen(WHITE);
  xpos = 0;
  ypos = YMAX2-(16*1);
  color = BLACK;
  strcpy((char *)utf,"漢字TEST");
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

  //draw multiple font
  lcdFillScreen(WHITE);
  lcdSetFontDirection(DIRECTION90);

  xpos = XMAX2-(24*1);
  ypos = YMAX2;
  color = BLACK;
  strcpy((char *)utf,"24ドットゴシック");
  xpos = lcdDrawUTF8String(fxG24, xpos, ypos, utf, color);

  xpos = XMAX2-(24*2);
  strcpy((char *)utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxG24, xpos, ypos, utf, color);

  xpos = XMAX2-(24*3);
  ypos = YMAX2;
  strcpy((char *)utf,"24ドット明朝");
  xpos = lcdDrawUTF8String(fxM24, xpos, ypos, utf, color);

  xpos = XMAX2-(24*4);
  strcpy((char *)utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxM24, xpos, ypos, utf, color);

  xpos = XMAX2-(24*5)-(16*0);
  ypos = YMAX2;
  strcpy((char *)utf,"16ドットゴシック");
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2-(24*5)-(16*1);
  strcpy((char *)utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxG16, xpos, ypos, utf, color);

  xpos = XMAX2-(24*5)-(16*2);
  ypos = YMAX2;
  strcpy((char *)utf,"16ドット明朝");
  xpos = lcdDrawUTF8String(fxM16, xpos, ypos, utf, color);

  xpos = XMAX2-(24*5)-(16*3);
  strcpy((char *)utf,"ABCDEFGabcdefg");
  xpos = lcdDrawUTF8String(fxM16, xpos, ypos, utf, color);

  return 0;
}
