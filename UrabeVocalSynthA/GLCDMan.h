#ifndef GLCDMAN_H
#define GLCDMAN_H

#include <U8glib.h>
#include "hiragana.cpp"
#include "KanaTable.h"
#include "ConfigDataDef.h"

static const char *hiragana[KanaTable::KANA_COUNT] =
  {
    "\x42", "\x44", "\x46", "\x48", "\x4a", //0
    "\x4b", "\x4d", "\x4f", "\x51", "\x53", //K
    "\x55", "\x57", "\x59", "\x5b", "\x5d", //S
    "\x5f", "\x61", "\x64", "\x66", "\x68", //T
    "\x6a", "\x6b", "\x6c", "\x6d", "\x6e", //N
    "\x6f", "\x72", "\x75", "\x78", "\x7b", //H
    "\x7e", "\x7f", "\x80", "\x81", "\x82", //M
    "\x84", "\x86", "\x88",                 //Y
    "\x89", "\x8a", "\x8b", "\x8c", "\x8d", //R
    "\x8f", "\x92",                         //W
    "\x93",                                 //N
    "\x4c", "\x4e", "\x50", "\x52", "\x54", //G
    "\x56", "\x58", "\x5a", "\x5c", "\x5e", //Z
    "\x60", "\x62", "\x65", "\x67", "\x69", //D
    "\x70", "\x73", "\x76", "\x79", "\x7c", //B
    "\x71", "\x74", "\x77", "\x7a", "\x7d"  //P
  };

class GLCDManager
{
  public:
    static const int GLCD_WIDTH;
    static const int GLCD_HEIGHT;
    static const int HEADER_HEIGHT;
    static const int FOOTER_HEIGHT;
    static const int UPPER_BUTTON_WIDTH;
    static U8GLIB_ST7920_128X64_1X u8g;
    GLCDManager();
    void draw_base();
    void draw_title(char *);
    void draw_title_large(char *);
    void draw_buttons_upper(char *, char *);
    void draw_buttons_lower(char *, char *);
    void draw_kana_buffer(KanaTable::Kana[], int);
    void draw_option(ConfigData::ConfigOption);
};

#endif
