#include "fontx.h"

#define RED             0xf800
#define GREEN           0x07e0
#define BLUE            0x001f
#define BLACK           0x0000
#define WHITE           0xffff
#define GRAY            0x8c51
#define YELLOW          0xFFE0
#define CYAN            0x07FF
#define PURPLE          0xF81F

#define DIRECTION0      0
#define DIRECTION90     1
#define DIRECTION180    2
#define DIRECTION270    3

void lcdWriteCommandByte(uint8_t c);
void lcdWriteDataByte(uint8_t c);
void lcdWriteDataWord(uint16_t w);
void lcdWriteRegisterWord(uint8_t addr, uint16_t data);
void lcdWriteColor(uint16_t color, uint16_t size);
void lcdInit(int width, int height, int offsetx, int offsety);
void lcdReset(void);
void lcdSetup(void);
void lcdRotCoord(uint16_t *x, uint16_t *y);
void lcdRotSqCoord(uint16_t *x1, uint16_t *y1, uint16_t *x2, uint16_t *y2);
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void lcdDrawFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcdDisplayOff(void);
void lcdDisplayOn(void);
void lcdFillScreen(uint16_t color);
void lcdDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcdDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcdDrawRectAngle(uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);
void lcdDrawFillRectAngle(uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);
void lcdDrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void lcdDrawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void lcdDrawRoundRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, uint16_t color);
void lcdDrawArrow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color);
void lcdDrawFillArrow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color);
uint16_t rgb565_conv(uint16_t r,uint16_t g,uint16_t b);
int lcdDrawSJISChar(FontxFile *fx, uint16_t x,uint16_t y,uint16_t sjis,uint16_t color);
int lcdDrawUTF8Char(FontxFile *fx, uint16_t x,uint16_t y,uint8_t *utf8,uint16_t color);
int lcdDrawUTF8String(FontxFile *fx, uint16_t x,uint16_t y,uint8_t *utfs,uint16_t color);
void lcdSetFontDirection(uint16_t);
void lcdSetScreenDirection(uint16_t dir);
void lcdSetFontFill(uint16_t color);
void lcdUnsetFontFill(void);
void lcdSetFontUnderLine(uint16_t color);
void lcdUnsetFontUnderLine(void);

uint16_t _width;
uint16_t _height;
uint16_t _FONT_DIRECTION_;
uint16_t _SCREEN_DIRECTION_;
