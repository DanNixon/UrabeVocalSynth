#include "KeypadHandler.h"

using namespace Keypad;

KeypadHandler::KeypadHandler(GUIManager *gm, JpSynthManager *jpsm)
{
  this->gui_man = gm;
  this->jps_man = jpsm;
  this->set_up_pins();
  for(int i=0; i < PHYSICAL_BUTTON_COUNT; i++)
  {
    this->button_last[i] = digitalRead(i);
  }
}

void KeypadHandler::set_up_pins()
{
  this->button_pins[F1] = 30;
  this->button_pins[F2] = 31;
  this->button_pins[F3] = 32;
  this->button_pins[F4] = 32;

  this->button_pins[A] = 32;
  this->button_pins[I] = 32;
  this->button_pins[U] = 32;
  this->button_pins[E] = 32;
  this->button_pins[O] = 32;

  this->button_pins[K] = 32;
  this->button_pins[S] = 32;
  this->button_pins[T] = 32;
  this->button_pins[N] = 32;
  this->button_pins[H] = 32;
  this->button_pins[M] = 32;
  this->button_pins[Y] = 32;
  this->button_pins[R] = 32;
  this->button_pins[W] = 32;

  this->button_pins[NN] = 32;
  this->button_pins[YA] = 32;
  this->button_pins[YU] = 32;
  this->button_pins[YO] = 32;

  for(int i=0; i<PHYSICAL_BUTTON_COUNT; i++)
  {
    pinMode(this->button_pins[i], INPUT);
    digitalWrite(this->button_pins[i], HIGH);
  }
}

GUIMan::ButtonValue KeypadHandler::scan_menu()
{
  int limit = (int) O;
  for(int i=0; i<limit; i++)
  {
    GUIMan::ButtonValue b_val = (GUIMan::ButtonValue) i;
    if(digitalRead(this->button_pins[i]))
    {
      return b_val;
    }
  }
}

KanaTable::Kana KeypadHandler::scan_kana()
{

}
