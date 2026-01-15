#ifndef _BSP_IIC_H_
#define _BSP_IIC_H_

#include "Arduino.h"

#define BSP_IIC_SCL_PIN 4
#define BSP_IIC_SDA_PIN 5

/* 定义端口电平状态 */
#define BSP_IIC_SCL_Set() digitalWrite(BSP_IIC_SCL_PIN, HIGH)
#define BSP_IIC_SCL_Clr() digitalWrite(BSP_IIC_SCL_PIN, LOW)

#define BSP_IIC_SDA_Set() digitalWrite(BSP_IIC_SDA_PIN, HIGH)
#define BSP_IIC_SDA_Clr() digitalWrite(BSP_IIC_SDA_PIN, LOW)

#define BSP_IIC_ReadSDA digitalRead(BSP_IIC_SDA_PIN)

/* 函数声明 */
void BSP_IIC_SDAIn(void);
void BSP_IIC_SDAOut(void);
void BSP_IIC_GPIOInit(void);
void BSP_IIC_delay(void);
void BSP_IIC_Start(void);
void BSP_IIC_Stop(void);
void BSP_IIC_Ack(void);
void BSP_IIC_Nack(void);
uint8_t BSP_IIC_WaitAck(void);
void BSP_IIC_SendByte(uint8_t dat);
uint8_t BSP_IIC_ReceiveByte(uint8_t ack);

#endif
