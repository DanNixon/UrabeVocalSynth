#ifndef KEYPADHANDLER_H
#define KEYPADHANDLER_H

#include "KanaTable.h"
#include "GUIMan.h"
#include "JpSynthMan.h"

using namespace GUIMan;

namespace Keypad
{
  enum PhysicalButtons
  {
    F1 = 0,
    F2,
    F3,
    F4,
    A, I, U, E, O,
    K, S, T, N, H, M, Y, R, W,
    NN,
    YA, YU, YO
  };
  
  static const int PHYSICAL_BUTTON_COUNT = 22;

  class KeypadHandler
  {
    private:
      void set_up_pins();
      int button_pins[PHYSICAL_BUTTON_COUNT];
      int button_last[PHYSICAL_BUTTON_COUNT];
      GUIManager *gui_man;
      JpSynthManager *jps_man;
   
    public:
      KeypadHandler(GUIManager *, JpSynthManager *);
      GUIMan::ButtonValue scan_menu();
      KanaTable::Kana scan_kana();
  };

};

#endif