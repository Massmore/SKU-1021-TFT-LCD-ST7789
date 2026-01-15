#ifndef _CST816_H_
#define _CST816_H_

#include "bsp_iic.h"

/* 从机地址 */
#define CST816_Write_Addr 0x2A
#define CST816_Read_Addr 0x2B

/* 端口定义 */
#define CST816_RES_PIN 6
#define CST816_INT_PIN 7

/* 定义端口电平状态 */
#define CST816_RES_Set() digitalWrite(CST816_RES_PIN, HIGH)
#define CST816_RES_Clr() digitalWrite(CST816_RES_PIN, LOW)

#define CST816_INT_Set() digitalWrite(CST816_INT_PIN, HIGH)
#define CST816_INT_Clr() digitalWrite(CST816_INT_PIN, LOW)

/* 中断配置 */
#define CST816_INT digitalRead(CST816_INT_PIN)

/* 定义支持触摸点个数 */
#define TOUCH_MAX 1

/* 定义触摸信息结构体 */
typedef struct
{
  uint8_t flag;          /* 触摸状态标志位 */
  uint8_t num;           /* 触摸点个数 */
  uint16_t x[TOUCH_MAX]; /* 触摸坐标点信息 */
  uint16_t y[TOUCH_MAX]; /* 触摸坐标点信息 */
} TouchStructure;

extern TouchStructure TouchInfo;

/* 触摸相关寄存器 */
#define CST816_ID_ADDR 0xA7
#define CST816_CFG_ADDR 0xA9
#define CST816_Touch_ADDR 0x02

/* 函数声明 */
void CST816_GPIOInit(void);
void CST816_SendByte(uint8_t reg, uint8_t dat);
void CST816_SendData(uint8_t reg, uint32_t len, uint8_t *buf);
uint8_t CST816_ReadByte(uint8_t reg);
void CST816_ReadData(uint8_t reg, uint32_t len, uint8_t *buf);
void CST816_Scan(void);
void CST816_EXTIEnable(void);
void CST816_INT_ISR_Handler(void *arg);
void CST816_Init(void);
void LCD_DrawBLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color, uint8_t sizey);
void CST816_Test(void);

#endif
