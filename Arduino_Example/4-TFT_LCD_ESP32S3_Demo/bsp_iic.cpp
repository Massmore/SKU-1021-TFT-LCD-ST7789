#include "bsp_iic.h"

/**
 @brief     配置IIC总线 SDA信号线为上拉输入模式
 @param     无
 @retval    无
*/
void BSP_IIC_SDAIn(void) {
  pinMode(BSP_IIC_SDA_PIN, INPUT_PULLUP);
}

/**
 @brief     配置IIC总线 SDA信号线为开漏输出模式
 @param     无
 @retval    无
*/
void BSP_IIC_SDAOut(void) {
  pinMode(BSP_IIC_SDA_PIN, OUTPUT_OPEN_DRAIN);
}

/**
 @brief     初始化IIC端口
 @param     无
 @retval    无
*/
void BSP_IIC_GPIOInit(void) {
  pinMode(BSP_IIC_SCL_PIN, OUTPUT);
  pinMode(BSP_IIC_SDA_PIN, OUTPUT_OPEN_DRAIN);
}

/**
 @brief     IIC通信内部延时
 @param     无
 @retval    无
*/
void BSP_IIC_delay(void) {
  delayMicroseconds(10);
}

/**
 @brief     IIC起始信号
 @param     无
 @retval    无
*/
void BSP_IIC_Start(void) {
  BSP_IIC_SDAOut();
  BSP_IIC_SCL_Set();
  BSP_IIC_SDA_Set();
  BSP_IIC_delay();
  BSP_IIC_SDA_Clr(); /* 起始信号 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Clr(); /* 钳住IIC总线准备收发数据 */
  BSP_IIC_delay();
}

/**
 @brief     IIC结束信号
 @param     无
 @retval    无
*/
void BSP_IIC_Stop(void) {
  BSP_IIC_SDAOut();
  BSP_IIC_SDA_Clr();
  BSP_IIC_SCL_Set();
  BSP_IIC_delay();
  BSP_IIC_SDA_Set(); /* 结束信号 */
  BSP_IIC_delay();
}

/**
 @brief     IIC应答信号
 @param     无
 @retval    无
*/
void BSP_IIC_Ack(void) {
  BSP_IIC_SDAOut();
  BSP_IIC_SDA_Clr(); /* 应答信号 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Set(); /* 产生一个时钟 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Clr();
  BSP_IIC_delay();
  BSP_IIC_SDA_Set(); /* 释放SDA控制权 */
  BSP_IIC_delay();
}

/**
 @brief     IIC非应答信号
 @param     无
 @retval    无
*/
void BSP_IIC_Nack(void) {
  BSP_IIC_SDAOut();
  BSP_IIC_SDA_Set(); /* 非应答信号 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Set(); /* 产生一个时钟 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Clr();
  BSP_IIC_delay();
}

/**
 @brief     IIC等待应答函数
 @param     无
 @retval    1:接收应答失败
            0:接收应答成功
*/
uint8_t BSP_IIC_WaitAck(void) {
  uint8_t receive_status = 0;
  BSP_IIC_SDAIn();
  BSP_IIC_SDA_Set(); /* 主机释放SDA线 */
  BSP_IIC_delay();
  BSP_IIC_SCL_Set(); /* 主机等待响应信号 */
  BSP_IIC_delay();

  while (BSP_IIC_ReadSDA) {
    receive_status = 1;
    BSP_IIC_Stop();
  }
  BSP_IIC_SCL_Clr(); /* 等待结束结束ACK检查 */
  BSP_IIC_delay();
  return receive_status;
}

/**
 @brief     IIC发送一个字节数据
 @param     dat：需要发送的数据
 @retval    无
*/
void BSP_IIC_SendByte(uint8_t dat) {
  uint8_t i;
  BSP_IIC_SDAOut();
  for (i = 0; i < 8; i++) {
    if (dat & 0x80) {
      BSP_IIC_SDA_Set();
    } else {
      BSP_IIC_SDA_Clr();
    }
    BSP_IIC_delay();
    BSP_IIC_SCL_Set(); /* SCL高电平 SDA的数据有效 */
    BSP_IIC_delay();
    BSP_IIC_SCL_Clr();
    dat <<= 1;
  }
  BSP_IIC_SDA_Set(); /* 发送完成释放SDA总线 */
}

/**
 @brief     IIC读取一个字节数据
 @param     ack：0发送非应答 1发送应答
 @retval    接收到的响应信号
*/
uint8_t BSP_IIC_ReceiveByte(uint8_t ack) {
  uint8_t i, receive = 0;
  BSP_IIC_SDAIn();
  for (i = 0; i < 8; i++) {
    receive <<= 1; /* 先发高位所以数据左移 */
    BSP_IIC_SCL_Set();
    BSP_IIC_delay();
    if (BSP_IIC_ReadSDA) {
      receive++;
    }
    BSP_IIC_SCL_Clr();
    BSP_IIC_delay();
  }
  if (!ack) {
    BSP_IIC_Nack();
  } else {
    BSP_IIC_Ack();
  }
  return receive;
}
