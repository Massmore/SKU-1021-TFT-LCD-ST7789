///////////////////////////////////////////////////////////////////////////////////////
// (ESP32S3 Arduino)
//----------------------------------------------------------------------
//               GND        
//               VCC        3.3v
//               SCL        48（SCLK）
//               SDA        47（MOSI）
//               RES        12
//               DC         13
//               CS         14
//               BLK        38
//               CTP_SCL    4
//               CTP_SDA    5
//               CTP_RES    6
//               CTP_INT    7
//***********************************************************************************/

#include "lcd.h"
#include "pic.h"
#include "cst816.h"

void setup() {
  Serial.begin(115200);
  LCD_Init();
  CST816_Init();
  LCD_Fill(0, 0, LCD_H, LCD_V, WHITE);
  LCD_ShowPicture(20, 30, 200, 107, gImage_1);
  LCD_StrCenter(0, 150, "2.00 Inch IPS LCD", RED, WHITE, 24, 0);
  LCD_StrCenter(0, 180, "RESOLUTION:240x320", RED, WHITE, 24, 0);
  LCD_StrCenter(0, 210, "DRIVER IC:ST7789", RED, WHITE, 24, 0);
  LCD_StrCenter(0, 240, "Support for rotation", RED, WHITE, 24, 0);
  LCD_StrCenter(0, 270, "in 4 dierctions", RED, WHITE, 24, 0);
  LCD_Fill(0, 0, LCD_H, LCD_V, WHITE);
  LCD_StrCenter((LCD_H - 144) / 2, 0, "Touch Test", BLACK, WHITE, 24, 0);
  LCD_ShowString(LCD_H - 36, 0, "Clr", BLACK, WHITE, 24, 0);
}

void loop() {
  if (TouchInfo.flag == 1) {
    CST816_Scan();
    if (TouchInfo.x[0] > (LCD_H - 36) && TouchInfo.y[0] < 24) {
      LCD_Fill(0, 0, LCD_H, LCD_V, WHITE);
      LCD_StrCenter((LCD_H - 144) / 2, 0, "Touch Test", BLACK, WHITE, 24, 0);
      LCD_ShowString(LCD_H - 36, 0, "Clr", BLACK, WHITE, 24, 0);
      TouchInfo.flag = 0;
    } else {
      LCD_DrawCircle(TouchInfo.x[0], TouchInfo.y[0], 1, BLACK, 1);
      LCD_ShowString(10, LCD_V - 40, "x:", BLACK, WHITE, 16, 0);
      LCD_ShowNum(28, LCD_V - 40, TouchInfo.x[0], 3, BLACK, WHITE, 16, 0);
      LCD_ShowString(10, LCD_V - 20, "y:", BLACK, WHITE, 16, 0);
      LCD_ShowNum(28, LCD_V - 20, TouchInfo.y[0], 3, BLACK, WHITE, 16, 0);
    }
  }
  delay(10);
}
