#include "GLCDMan.h"
#include "Arduino.h"

const int GLCDManager::GLCD_WIDTH = 128;
const int GLCDManager::GLCD_HEIGHT = 64;

//D0, D1, D2, D3, D4, D5, D6, D7, EN, DI RS, RW R/W
U8GLIB_ST7920_128X64_1X GLCDManager::u8g(40, 41, 42, 43, 44, 45, 46, 47, 30, 31, 32);

GLCDManager::GLCDManager()
{
  this->u8g.setColorIndex(1);
}

void GLCDManager::draw()
{
  this->u8g.setFont(u8g_font_unifont);
  this->u8g.drawHLine(0, 14, 128);
  this->u8g.drawHLine(0, this->GLCD_HEIGHT - 14, 128);
  this->u8g.drawStr(0, 12, "Mg");
}

