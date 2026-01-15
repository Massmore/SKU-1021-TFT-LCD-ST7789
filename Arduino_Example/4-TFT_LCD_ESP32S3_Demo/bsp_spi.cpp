#include "bsp_spi.h"
#include <SPI.h>

SPIClass* bsp_spi = NULL; /* 定义一个未初始化指向SPI对象的指针 */

/**
 * @brief       SPI发送一个字节数据
 * @param       TxData: 需要发送的字节数据
 * @retval      无
 */
void BSP_SPI_SendByte(uint8_t TxData) {
  bsp_spi->transfer(TxData);
}

/**
 * @brief       SPI发送一个半字数据
 * @param       TxData: 需要发送的半字数据
 * @retval      无
 */
void BSP_SPI_SendHalfWord(uint16_t TxData) {
  bsp_spi->transfer16(TxData);
}

/**
 * @brief       SPI连续发送len个字节的数据
 * @param       dat:数据指针
 * @param       len:数据长度
 * @retval      无
 */
void BSP_SPI_SendData(uint8_t* dat, uint16_t len) {
  bsp_spi->transfer(dat, len);
}

/**
 * @brief       初始化SPI
 * @param       无
 * @retval      无
 */
void BSP_SPIInit(void) {
  // pinMode(BSP_SPI_CS_PIN, OUTPUT); /* 初始化CS端口 */
  // /* arduino uno板卡用的ATmega328P 主频(F_CPU)为16Mhz
  //    SPI总线工作在8Mhz下 高位在前 工作在模式3
  //  */
  // SPI.begin(BSP_SPI_SCK_PIN, -1, BSP_SPI_MOSI_PIN, BSP_SPI_CS_PIN);
  // SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3));
  // SPI.begin();

  bsp_spi = new SPIClass(HSPI);
  bsp_spi->begin(BSP_SPI_SCK_PIN, -1, BSP_SPI_MOSI_PIN, BSP_SPI_CS_PIN);
  pinMode(BSP_SPI_CS_PIN, OUTPUT);
  BSP_SPI_CS_Set();
  bsp_spi->beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3));
}
