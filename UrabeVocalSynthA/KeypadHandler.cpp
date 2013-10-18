#include "KeypadHandler.h"

using namespace Keypad;

KeypadHandler::KeypadHandler(GUIManager *gm, JpSynthManager *jpsm)
{
  this->gui_man = gm;
  this->jps_man = jpsm;
  this->set_up_pins();
  this->last_button = _NULL;
  this->last_kana = KanaTable::_NULL;
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

void KeypadHandler::scan_menu()
{

}

void KeypadHandler::scan_kana()
{

}

ButtonValue KeypadHandler::get_last_button() { return this->last_button; }
KanaTable::Kana KeypadHandler::get_last_kana() { return this->last_kana; }
