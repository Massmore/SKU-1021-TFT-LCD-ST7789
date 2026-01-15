#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "Arduino.h"

/* 端口定义 */
#define BSP_SPI_SCK_PIN 48
#define BSP_SPI_MOSI_PIN 47
#define BSP_SPI_CS_PIN 14

/* 定义端口电平状态 */
#define BSP_SPI_SCK_Set() digitalWrite(BSP_SPI_SCK_PIN, HIGH)
#define BSP_SPI_SCK_Clr() digitalWrite(BSP_SPI_SCK_PIN, LOW)

#define BSP_SPI_MOSI_Set() digitalWrite(BSP_SPI_MOSI_PIN, HIGH)
#define BSP_SPI_MOSI_Clr() digitalWrite(BSP_SPI_MOSI_PIN, LOW)

#define BSP_SPI_CS_Set() digitalWrite(BSP_SPI_CS_PIN, HIGH)
#define BSP_SPI_CS_Clr() digitalWrite(BSP_SPI_CS_PIN, LOW)

/* 函数声明 */
void BSP_SPI_SendByte(uint8_t TxData);
void BSP_SPI_SendHalfWord(uint16_t TxData);
void BSP_SPI_SendData(uint8_t *dat, uint16_t len);
void BSP_SPIInit(void);
#endif
