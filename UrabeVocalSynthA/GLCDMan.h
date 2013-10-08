#ifndef GLCDMAN_H
#define GLCDMAN_H

#include <U8glib.h>
#include "hiragana.cpp"

class GLCDManager
{
  private:
    
  public:
    static const int GLCD_WIDTH;
    static const int GLCD_HEIGHT;
    static U8GLIB_ST7920_128X64_1X u8g;
    GLCDManager();
    void draw();
};

#endif
