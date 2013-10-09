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
  
  class GUIManager
  {
    private:
      GLCDManager *glcd_man;
      void do_draw();
      
    public:
      MenuWindow current_window;
      GUIManager(GLCDManager *);
      void draw();
      KanaTable::Kana display_kana[7];
      int notes_on;
  };
  
};

#endif
