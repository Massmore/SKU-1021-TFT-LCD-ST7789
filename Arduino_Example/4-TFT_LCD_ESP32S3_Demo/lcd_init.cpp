#include "lcd_init.h"

/**
 * @brief   LCD端口初始化
 * @param   无
 * @return  无
 */
void LCD_GPIOInit(void) {
  pinMode(LCD_RES_PIN, OUTPUT);
  pinMode(LCD_DC_PIN, OUTPUT);
  pinMode(LCD_BLK_PIN, OUTPUT);
}

/**
 * @brief   写指令函数
 * @param   reg:寄存器地址
 * @return  无
 */
void LCD_WR_REG(uint8_t reg) {
  LCD_DC_Clr();
  BSP_SPI_CS_Clr();
  BSP_SPI_SendByte(reg);
  BSP_SPI_CS_Set();
  LCD_DC_Set();
}

/**
 * @brief   写数据函数
 * @param   dat:数据字节
 * @return  无
 */
void LCD_WR_Byte(uint8_t dat) {
  BSP_SPI_CS_Clr();
  BSP_SPI_SendByte(dat);
  BSP_SPI_CS_Set();
}

/**
 * @brief   写数据函数
 * @param   dat:数据半字
 * @return  无
 */
void LCD_WR_HalfWord(uint16_t dat) {
  BSP_SPI_CS_Clr();
  BSP_SPI_SendHalfWord(dat);
  BSP_SPI_CS_Set();
}

/**
 * @brief   设置显示窗口
 * @param   xs:窗口起始列地址
 * @param   ys:窗口起始行地址
 * @param   xe:窗口结束列地址
 * @param   ye:窗口结束行地址
 * @return  无
 */
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) {
  LCD_WR_REG(0x2A);
  LCD_WR_HalfWord(xs);
  LCD_WR_HalfWord(xe);
  LCD_WR_REG(0x2B);
  LCD_WR_HalfWord(ys);
  LCD_WR_HalfWord(ye);
  LCD_WR_REG(0x2C);
}

/**
 * @brief       液晶进入休眠
 * @param       无
 * @retval      无
 */
void LCD_Enter_Sleep(void) {
  LCD_WR_REG(0x28);
  delay(120);
  LCD_WR_REG(0x10);
  delay(50);
}

/**
 * @brief       液晶退出休眠
 * @param       无
 * @retval      无
 */
void LCD_Exit_Sleep(void) {
  LCD_WR_REG(0x11);
  delay(120);
  LCD_WR_REG(0x29);
}

/**
 * @brief   纯色填充函数
 * @param   xs:窗口起始列地址
 * @param   ys:窗口起始行地址
 * @param   xe:窗口结束列地址
 * @param   ye:窗口结束行地址
 * @param   color:需要填充的颜色
 * @return  无
 * @note    可以用于清屏
 */
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color) {
  uint16_t i, j;
  LCD_Address_Set(xs, ys, xe - 1, ye - 1);
  for (i = ys; i < ye; i++) {
    for (j = xs; j < xe; j++) {
      LCD_WR_HalfWord(color);
    }
  }
}

/**
 * @brief   指定区域进行数据填充
 * @param   xs:起始列地址
 * @param   ys:起始行地址
 * @param   xe:结束列地址
 * @param   ye:结束行地址
 * @param   color:填充数据
 * @retval  无
 */
void LCD_ColorFill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color) {
  uint32_t k = 0, num;
  num = (xe - xs) * (ye - ys);
  LCD_Address_Set(xs, ys, xe - 1, ye - 1);
  for (k = 0; k < num; k++) {
    LCD_WR_HalfWord(color[k]);
  }
}

/**
 * @brief   初始化液晶
 * @param   无
 * @return  无
 */
void LCD_Init(void) {
  BSP_SPIInit();
  LCD_GPIOInit();
  LCD_RES_Set();
  delay(50);
  LCD_RES_Clr();
  delay(50);
  LCD_RES_Set();
  delay(120);
  LCD_BLK_Set();

  LCD_WR_REG(0x11);
  delay(120);

  LCD_WR_REG(0x3a);
  LCD_WR_Byte(0x05);

  LCD_WR_REG(0x36);
#if display_direction == 0
  LCD_WR_Byte(0x00);
#elif display_direction == 1
  LCD_WR_Byte(0xC0);
#elif display_direction == 2
  LCD_WR_Byte(0x70);
#else
  LCD_WR_Byte(0xA0);
#endif
  LCD_WR_REG(0xB2);
  LCD_WR_Byte(0x0C);
  LCD_WR_Byte(0x0C);
  LCD_WR_Byte(0x00);
  LCD_WR_Byte(0x33);
  LCD_WR_Byte(0x33);

  LCD_WR_REG(0xB7);
  LCD_WR_Byte(0x35);

  LCD_WR_REG(0xBB);
  LCD_WR_Byte(0x32);

  LCD_WR_REG(0xC2);
  LCD_WR_Byte(0x01);

  LCD_WR_REG(0xC3);
  LCD_WR_Byte(0x15);

  LCD_WR_REG(0xC4);
  LCD_WR_Byte(0x20);

  LCD_WR_REG(0xC6);
  LCD_WR_Byte(0x0F);

  LCD_WR_REG(0xD0);
  LCD_WR_Byte(0xA4);
  LCD_WR_Byte(0xA1);

  LCD_WR_REG(0xE0);
  LCD_WR_Byte(0xD0);
  LCD_WR_Byte(0x08);
  LCD_WR_Byte(0x0E);
  LCD_WR_Byte(0x09);
  LCD_WR_Byte(0x09);
  LCD_WR_Byte(0x05);
  LCD_WR_Byte(0x31);
  LCD_WR_Byte(0x33);
  LCD_WR_Byte(0x48);
  LCD_WR_Byte(0x17);
  LCD_WR_Byte(0x14);
  LCD_WR_Byte(0x15);
  LCD_WR_Byte(0x31);
  LCD_WR_Byte(0x34);

  LCD_WR_REG(0xE1);
  LCD_WR_Byte(0xD0);
  LCD_WR_Byte(0x08);
  LCD_WR_Byte(0x0E);
  LCD_WR_Byte(0x09);
  LCD_WR_Byte(0x09);
  LCD_WR_Byte(0x15);
  LCD_WR_Byte(0x31);
  LCD_WR_Byte(0x33);
  LCD_WR_Byte(0x48);
  LCD_WR_Byte(0x17);
  LCD_WR_Byte(0x14);
  LCD_WR_Byte(0x15);
  LCD_WR_Byte(0x31);
  LCD_WR_Byte(0x34);

  LCD_WR_REG(0x21);

  LCD_WR_REG(0x11);
  delay(120);

  LCD_WR_REG(0x29);
}
