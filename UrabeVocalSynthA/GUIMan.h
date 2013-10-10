#ifndef GUIMAN_H
#define GUIMAN_H

#include "GLCDMan.h"
#include "KanaTable.h"

namespace GUIMan
{  
  enum MenuWindow
  {
    W_NULL = 255,
    MAIN = 0,
    SYNTH_MENU,
    SYNTH_SETTINGS,
    SYNTH_RUN,
    JP_MENU,
    JP_SETTINGS,
    JP_RUN
  };
  
  enum ButtonValue
  {
    F1, //GLCD Top Left
    F2, //GLCD Top Right
    F3, //GLCD Bottom Left
    F4, //GLCD Bottom Right
    SELECT,
    BACK,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
  
  class GUIManager
  {
    private:
      GLCDManager *glcd_man;
      void do_draw();
      
    public:
      KanaTable::Kana display_kana[7];
      int notes_on;
      MenuWindow current_window;
      GUIManager(GLCDManager *);
      void draw();
      void handle_menu_input(ButtonValue);
  };
  
};

#endif
