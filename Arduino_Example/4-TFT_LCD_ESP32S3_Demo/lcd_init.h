#ifndef _LCD_INIT_H_
#define _LCD_INIT_H_

#include "bsp_spi.h"

/* 定义液晶显示方向以及分辨率参数 */
/* 0 正向显示  1 旋转180度显示  2 旋转90度显示  3 旋转270度显示 */
#define display_direction 0

#if display_direction == 0 || display_direction == 1
#define LCD_H 240
#define LCD_V 320
#else
#define LCD_H 320
#define LCD_V 240
#endif

/* 端口定义 */
#define LCD_RES_PIN 12
#define LCD_DC_PIN 13
#define LCD_BLK_PIN 38

/* 定义端口电平状态 */
#define LCD_RES_Set() digitalWrite(LCD_RES_PIN, HIGH);
#define LCD_RES_Clr() digitalWrite(LCD_RES_PIN, LOW);

#define LCD_DC_Set() digitalWrite(LCD_DC_PIN, HIGH);
#define LCD_DC_Clr() digitalWrite(LCD_DC_PIN, LOW);

#define LCD_BLK_Set() digitalWrite(LCD_BLK_PIN, HIGH);
#define LCD_BLK_Clr() digitalWrite(LCD_BLK_PIN, LOW);

/* 函数声明 */
void LCD_GPIOInit(void);
void LCD_WR_REG(uint8_t reg);
void LCD_WR_Byte(uint8_t dat);
void LCD_WR_HalfWord(uint16_t dat);
void LCD_Enter_Sleep(void);
void LCD_Exit_Sleep(void);
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void LCD_FastFill(uint16_t color);
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);
void LCD_ColorFill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color);
void LCD_Init(void);

/* 颜色参数 */
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40      /* 棕色 */
#define BRRED 0XFC07      /* 棕红色 */
#define GRAY 0X8430       /* 灰色 */
#define DARKBLUE 0X01CF   /* 深蓝色 */
#define LIGHTBLUE 0X7D7C  /* 浅蓝色 */
#define GRAYBLUE 0X5458   /* 灰蓝色 */
#define LIGHTGREEN 0X841F /* 浅绿色 */
#define LGRAY 0XC618      /* 浅灰色(PANNEL),窗体背景色 */
#define LGRAYBLUE 0XA651  /* 浅灰蓝色(中间层颜色) */
#define LBBLUE 0X2B12     /* 浅棕蓝色(选择条目的反色) */

#endif
