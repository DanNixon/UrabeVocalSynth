#include "GLCDMan.h"

const int GLCDManager::GLCD_WIDTH = 128;
const int GLCDManager::GLCD_HEIGHT = 64;
const int GLCDManager::HEADER_HEIGHT = 14;
const int GLCDManager::FOOTER_HEIGHT = 15;
const int GLCDManager::UPPER_BUTTON_WIDTH = 32;

//D0, D1, D2, D3, D4, D5, D6, D7, EN, DI RS, RW R/W
U8GLIB_ST7920_128X64_1X GLCDManager::u8g(40, 41, 42, 43, 44, 45, 46, 47, 30, 31, 32);

GLCDManager::GLCDManager()
{
  this->u8g.setColorIndex(1);
}

void GLCDManager::draw_title(char *title)
{
  this->u8g.setFont(u8g_font_unifont);
  this->u8g.drawStr(30 + 4, 12, title);
}

void GLCDManager::draw_title_large(char *title)
{
  this->u8g.setFont(u8g_font_unifont);
  this->u8g.drawStr(0, 12, title);
}

void GLCDManager::draw_buttons_upper(char *left, char *right)
{
  this->u8g.setFont(u8g_font_unifont);
  this->u8g.drawVLine(this->UPPER_BUTTON_WIDTH, 0, this->HEADER_HEIGHT);
  this->u8g.drawVLine(this->GLCD_WIDTH - this->UPPER_BUTTON_WIDTH - 1, 0, this->HEADER_HEIGHT);
  this->u8g.drawStr(0, 12, left);
  this->u8g.drawStr(this->GLCD_WIDTH - this->UPPER_BUTTON_WIDTH, 12, right);
}

void GLCDManager::draw_buttons_lower(char *left, char *right)
{
  this->u8g.setFont(u8g_font_unifont);
  int centre = this->GLCD_WIDTH / 2;
  this->u8g.drawVLine(centre, this->GLCD_HEIGHT - this->FOOTER_HEIGHT, this->GLCD_HEIGHT);
  this->u8g.drawStr(0, this->GLCD_HEIGHT - 2, left);
  this->u8g.drawStr(this->GLCD_WIDTH - centre + 1, this->GLCD_HEIGHT - 2, right);
}

void GLCDManager::draw_kana_buffer(KanaTable::Kana displayKana[], int synth_on)
{
  int px_h = 45;
  this->u8g.setFont(hira1);
  this->u8g.setScale2x2();
  if(synth_on)
    this->u8g.drawHLine(0, (px_h / 2) + 1, 15);
  this->u8g.drawStr(0, (px_h / 2), hiragana[displayKana[0]]);
  this->u8g.undoScale();
  for(int i=1; i<7; i++)
  {
    int px_x = 32 + (16 * (i - 1));
    if(displayKana[i] != KanaTable::_NULL)
      this->u8g.drawStr(px_x, px_h, hiragana[displayKana[i]]);
  }
}

void GLCDManager::draw_option(ConfigData::ConfigOption option)
{
  this->u8g.setFont(u8g_font_helvR08);
  this->u8g.drawStr(0, this->HEADER_HEIGHT + 12, option.name);
  this->u8g.setFont(u8g_font_unifont);
  char value_str[30];
  if(option.type == ConfigData::ENUM)
  {
    sprintf(value_str, "%s", option.values[option.value]);
  }
  else
  {
    sprintf(value_str, "%d", option.value);
  }
  this->u8g.drawStr(0, this->HEADER_HEIGHT + 30, value_str); 
}

void GLCDManager::draw_base()
{
  this->u8g.drawHLine(0, this->HEADER_HEIGHT, 128);
  this->u8g.drawHLine(0, this->GLCD_HEIGHT - this->FOOTER_HEIGHT, 128);
}

