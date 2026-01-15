#include "cst816.h"
#include "stdio.h"
#include "lcd.h"

/* 触摸信息结构体 */
TouchStructure TouchInfo;

/**
 * @brief       触摸IC端口初始化
 * @param       无
 * @retval      无
 * @note        配置为推挽输出
 */
void CST816_GPIOInit(void)
{
    pinMode(CST816_RES_PIN, OUTPUT);
    pinMode(CST816_INT_PIN, OUTPUT);
}

/**
 * @brief       向触摸IC对应寄存器写入一个字节数据
 * @param       reg:寄存器地址
 * @param       dat:字节数据
 * @retval      无
 */
void CST816_SendByte(uint8_t reg, uint8_t dat)
{
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Write_Addr);
    BSP_IIC_WaitAck();
    BSP_IIC_SendByte(reg);
    BSP_IIC_WaitAck();
    BSP_IIC_SendByte(dat);
    BSP_IIC_WaitAck();
    BSP_IIC_Stop();
}

/**
 * @brief       向触摸IC对应寄存器连续写入len个字节数据
 * @param       reg:寄存器地址
 * @param       len:数据长度
 * @param       *buf:数据地址指针
 * @retval      无
 */
void CST816_SendData(uint8_t reg, uint32_t len, uint8_t *buf)
{
    uint32_t i;
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Write_Addr);
    BSP_IIC_WaitAck();
    BSP_IIC_SendByte(reg);
    BSP_IIC_WaitAck();
    for (i = 0; i < len; i++)
    {
        BSP_IIC_SendByte(buf[i]);
        BSP_IIC_WaitAck();
    }
    BSP_IIC_Stop();
}

/**
 * @brief       读取触摸IC对应寄存器下的数据
 * @param       reg:寄存器地址
 * @retval      寄存器对应数据
 */
uint8_t CST816_ReadByte(uint8_t reg)
{
    uint32_t receive_dat = 0;
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Write_Addr);
    BSP_IIC_WaitAck();
    BSP_IIC_SendByte(reg);
    BSP_IIC_WaitAck();
    BSP_IIC_Stop();
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Read_Addr);
    BSP_IIC_WaitAck();
    receive_dat = BSP_IIC_ReceiveByte(0x00);
    BSP_IIC_Stop();
    return receive_dat;
}

/**
 * @brief       连续读取len个触摸IC对应寄存器下的数据
 * @param       reg:寄存器地址
 * @param       len:数据长度
 * @param       *buf:返回数据地址指针
 * @retval      无
 */
void CST816_ReadData(uint8_t reg, uint32_t len, uint8_t *buf)
{
    uint32_t i = 0;
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Write_Addr);
    BSP_IIC_WaitAck();
    BSP_IIC_SendByte(reg);
    BSP_IIC_WaitAck();
    BSP_IIC_Stop();
    BSP_IIC_Start();
    BSP_IIC_SendByte(CST816_Read_Addr);
    BSP_IIC_WaitAck();
    for (i = 0; i < len; i++)
    {
        if (i == (len - 1)) /* 判断是否为要读取的最后一个字节数据 */
        {
            buf[i] = BSP_IIC_ReceiveByte(0x00);
        }
        else
        {
            buf[i] = BSP_IIC_ReceiveByte(0x01);
        }
    }
    BSP_IIC_Stop();
}

/**
 * @brief       触摸IC扫描函数
 * @param       无
 * @retval      无
 */
void CST816_Scan(void)
{
    uint8_t TouchData[1 + 4 * TOUCH_MAX];                             /* 存储触摸数据 */
    CST816_ReadData(CST816_Touch_ADDR, 1 + 4 * TOUCH_MAX, TouchData); /* 读取触摸数据 */
    CST816_SendByte(CST816_Touch_ADDR, 0x00);                         /* 清除触摸标志位 */
    TouchInfo.num = TouchData[0];                                     /* 获取触摸点的个数 */
    if (TouchInfo.num != 0)
    {
        if (display_direction == 0)
        {
            TouchInfo.x[0] = LCD_H - (((TouchData[1] & 0x0F) << 8) | TouchData[2]); /* 获取触摸点的坐标 */
            TouchInfo.y[0] = (((TouchData[3] & 0x0F) << 8) | TouchData[4]);         /* 获取触摸点的坐标 */
        }
        else if (display_direction == 1)
        {
            TouchInfo.x[0] = (((TouchData[1] & 0x0F) << 8) | TouchData[2]);         /* 获取触摸点的坐标 */
            TouchInfo.y[0] = LCD_V - (((TouchData[3] & 0x0F) << 8) | TouchData[4]); /* 获取触摸点的坐标 */
        }
        else if (display_direction == 2)
        {
            TouchInfo.x[0] = (((TouchData[3] & 0x0F) << 8) | TouchData[4]); /* 获取触摸点的坐标 */
            TouchInfo.y[0] = (((TouchData[1] & 0x0F) << 8) | TouchData[2]); /* 获取触摸点的坐标 */
        }
        else
        {
            TouchInfo.x[0] = LCD_H - (((TouchData[3] & 0x0F) << 8) | TouchData[4]); /* 获取触摸点的坐标 */
            TouchInfo.y[0] = LCD_V - (((TouchData[1] & 0x0F) << 8) | TouchData[2]); /* 获取触摸点的坐标 */
        }

        // printf("x[0]:%d,y[0]:%d\r\n", TouchInfo.x[0], TouchInfo.y[0]); /* 打印触摸点坐标信息 */
    }
    else
    {
        TouchInfo.flag = 0; /* 无触摸动作 */
    }
}

/**
 * @brief       外部中断服务函数
 * @param       arg：中断引脚号
 * @retval      无
 */
void exit_gpio_isr_handler(void)
{
    if (CST816_INT == 0)
    {
        TouchInfo.flag = 1;
    }
}

/**
 * @brief       INT管脚中断使能函数
 * @param       无
 * @retval      无
 * @note        没有触摸按下时 INT电平为高
 */
void CST816_EXTIEnable(void)
{
  pinMode(CST816_INT_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CST816_INT_PIN),exit_gpio_isr_handler,FALLING); /* 设置CST816_INT 下降沿触发中断 */
}

/**
 * @brief       初始化触摸IC
 * @param       无
 * @retval      无
 */
void CST816_Init(void)
{
    uint8_t TouchID, TouchConfig;
    BSP_IIC_GPIOInit();
    CST816_GPIOInit();
    CST816_RES_Clr();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    CST816_RES_Set();
    vTaskDelay(120 / portTICK_PERIOD_MS);
    CST816_SendByte(0xFE, 0x01);         /* 禁止进入低功耗模式 */
    TouchID = CST816_ReadByte(0xA7);     /* 读取触摸芯片ID */
    TouchConfig = CST816_ReadByte(0xA9); /* 读取触摸固件信息 */
    if (TouchID == 0xB6)
    {
        printf("Touch ID:CST816D\r\n");
        printf("TP Config:0X%x\r\n", TouchConfig);
    }
    else
    {
        printf("Touch error\r\n");
    }
    CST816_EXTIEnable(); /* 使能中断 */
}
