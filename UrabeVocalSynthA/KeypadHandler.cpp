#include "KeypadHandler.h"

using namespace Keypad;

KeypadHandler::KeypadHandler(GUIManager *gm, JpSynthManager *jpsm)
{
  this->gui_man = gm;
  this->jps_man = jpsm;
  this->set_up_pins();
  for(int i=0; i < PHYSICAL_BUTTON_COUNT; i++)
    this->button_last[i] = digitalRead(i);
}

void KeypadHandler::set_up_pins()
{
  this->button_pins[F1] = 16; //GLCD Top Left
  this->button_pins[F2] = 17; //GLCD Top Right
  this->button_pins[F3] = 18; //GLCD Bottom Left
  this->button_pins[F4] = 19; //GLCD Bottom Right

  this->button_pins[A] = 23;
  this->button_pins[I] = 24;
  this->button_pins[U] = 25;
  this->button_pins[E] = 26;
  this->button_pins[O] = 27;

  this->button_pins[K] = 32;
  this->button_pins[S] = 33;
  this->button_pins[T] = 34;
  this->button_pins[N] = 35;
  this->button_pins[H] = 36;
  this->button_pins[M] = 37;
  this->button_pins[Y] = 38;
  this->button_pins[R] = 39;
  this->button_pins[W] = 40;

  this->button_pins[NN] = 28;
  this->button_pins[YA] = 29;
  this->button_pins[YU] = 30;
  this->button_pins[YO] = 31;

  for(int i=0; i<PHYSICAL_BUTTON_COUNT; i++)
  {
    pinMode(this->button_pins[i], INPUT);
    digitalWrite(this->button_pins[i], HIGH);
  }
}

GUIMan::ButtonValue KeypadHandler::scan_menu()
{
  int limit = (int) O;
  for(int i=0; i<=limit; i++)
  {
    GUIMan::ButtonValue b_val = (GUIMan::ButtonValue) i;
    int current_state = digitalRead(this->button_pins[i]);
//    Serial.print("i:");
//    Serial.print(i);
//    Serial.print(", last:");
//    Serial.print(this->button_last[i]);
//    Serial.print(", current:");
//    Serial.println(current_state);
    if(current_state != this->button_last[i])
    {
      this->button_last[i] = current_state;
      if(current_state == LOW)
        return b_val;
    }
  }
  return _NULL;
}

KanaTable::Kana KeypadHandler::scan_kana()
{

}
