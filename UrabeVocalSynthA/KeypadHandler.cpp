#include "KeypadHandler.h"

using namespace Keypad;

//dak, vowel/y, const
// K S T N H M Y R W
KanaTable::Kana kana_button_mapping[][9][9] =
{
  { //none
    {KanaTable::_K, KanaTable::_S, KanaTable::_T, KanaTable::_Ns, KanaTable::_H, KanaTable::_M, KanaTable::_Y, KanaTable::_R, KanaTable::_W},                     //small tsu
    {KanaTable::_KA, KanaTable::_SA, KanaTable::_TA, KanaTable::_NA, KanaTable::_HA, KanaTable::_MA, KanaTable::_YA, KanaTable::_RA, KanaTable::_WA},             //a
    {KanaTable::_KI, KanaTable::_SHI, KanaTable::_CHI, KanaTable::_NI, KanaTable::_HI, KanaTable::_MI, KanaTable::_NULL, KanaTable::_RI, KanaTable::_NULL},       //i
    {KanaTable::_KU, KanaTable::_SU, KanaTable::_TSU, KanaTable::_NU, KanaTable::_HU, KanaTable::_MU, KanaTable::_YU, KanaTable::_RU, KanaTable::_NULL},          //u
    {KanaTable::_KE, KanaTable::_SE, KanaTable::_TE, KanaTable::_NE, KanaTable::_HE, KanaTable::_ME, KanaTable::_NULL, KanaTable::_RE, KanaTable::_NULL},         //e
    {KanaTable::_KO, KanaTable::_SO, KanaTable::_TO, KanaTable::_NO, KanaTable::_HO, KanaTable::_MO, KanaTable::_YO, KanaTable::_RO, KanaTable::_WO},             //o
    {KanaTable::_KYA, KanaTable::_SHA, KanaTable::_CHA, KanaTable::_NYA, KanaTable::_HYA, KanaTable::_MYA, KanaTable::_NULL, KanaTable::_RYA, KanaTable::_NULL},  //ya
    {KanaTable::_KYU, KanaTable::_SHU, KanaTable::_CHU, KanaTable::_NYU, KanaTable::_HYU, KanaTable::_MYU, KanaTable::_NULL, KanaTable::_RYU, KanaTable::_NULL},  //yu
    {KanaTable::_KYO, KanaTable::_SHO, KanaTable::_CHO, KanaTable::_NYO, KanaTable::_HYO, KanaTable::_MYO, KanaTable::_NULL, KanaTable::_RYO, KanaTable::_NULL}   //yo
  },
  { //dak
    {KanaTable::_G, KanaTable::_Z, KanaTable::_D, KanaTable::_NULL, KanaTable::_B, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},        //small tsu
    {KanaTable::_GA, KanaTable::_ZA, KanaTable::_DA, KanaTable::_NULL, KanaTable::_BA, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //a
    {KanaTable::_GI, KanaTable::_JI, KanaTable::_DI, KanaTable::_NULL, KanaTable::_BI, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //i
    {KanaTable::_GU, KanaTable::_ZU, KanaTable::_DU, KanaTable::_NULL, KanaTable::_BU, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //u
    {KanaTable::_GE, KanaTable::_ZE, KanaTable::_DE, KanaTable::_NULL, KanaTable::_BE, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //e
    {KanaTable::_GO, KanaTable::_ZO, KanaTable::_DO, KanaTable::_NULL, KanaTable::_BO, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //o
    {KanaTable::_GYA, KanaTable::_JA, KanaTable::_JA, KanaTable::_NULL, KanaTable::_BYA, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},  //ya
    {KanaTable::_GYU, KanaTable::_JU, KanaTable::_JU, KanaTable::_NULL, KanaTable::_BYU, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},  //yu
    {KanaTable::_GYO, KanaTable::_JO, KanaTable::_JO, KanaTable::_NULL, KanaTable::_BYO, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL}   //yo
  },
  { //handak
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_P, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},    //small tsu
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PA, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},   //a
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PI, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},   //i
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PU, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},   //u
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PE, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},   //e
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PO, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},   //o
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PYA, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},  //ya
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PYU, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL},  //yu
    {KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_PYO, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL, KanaTable::_NULL}   //yo
  }
};

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

  this->button_pins[A] = 23;  //Select
  this->button_pins[I] = 24;  //Left
  this->button_pins[U] = 25;  //Up
  this->button_pins[E] = 26;  //Right
  this->button_pins[O] = 27;  //Down

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

  this->button_pins[DAK] = 14;
  this->button_pins[HANDAK] = 15;

  for(int i=0; i<PHYSICAL_BUTTON_COUNT; i++)
  {
    pinMode(this->button_pins[i], INPUT);
    digitalWrite(this->button_pins[i], HIGH);
  }
}

PhysicalButton KeypadHandler::get_button(int timeout, int button_lower_limit, int button_upper_limit)
{
  long start_time = millis();
  long delta_time = 0;
  do
  {
    for(int i = button_lower_limit; i < button_upper_limit; i++)
    {
      PhysicalButton b_val = (PhysicalButton) i;
      int current_state = digitalRead(this->button_pins[i]);
      if(current_state != this->button_last[i])
      {
        this->button_last[i] = current_state;
        if(current_state == LOW)
          return b_val;
      }
    }
    delta_time = millis() - start_time;
  } while(delta_time < timeout);
  return _NONE;
}

GUIMan::ButtonValue KeypadHandler::scan_menu()
{
  int limit = ((int) O) + 1;
  return (GUIMan::ButtonValue) this->get_button(10, 0, limit);
}

GUIMan::ButtonValue KeypadHandler::scan_funct_keys()
{
  int limit = ((int) F4) + 1;
  return (GUIMan::ButtonValue) this->get_button(10, 0, limit);
}

KanaTable::Kana KeypadHandler::scan_kana()
{
  PhysicalButton button = this->get_button(0, 4, PHYSICAL_BUTTON_COUNT);
  if(button == _NONE) return KanaTable::_NULL;
  if(button == NN) return KanaTable::_N;
  int button_val = (int) button;
  if((button_val >= (int) A) && (button_val <= (int) O))
  {
    int vowel_value = button_val - ((int) A);
    return (KanaTable::Kana) vowel_value;
  }
  if((button_val >= (int) K) && (button_val <= (int) W))
  {
    PhysicalButton second_button = this->get_button(500, 4, PHYSICAL_BUTTON_COUNT);
    int second_val = (int) second_button;
    PhysicalButton third_button = this->get_button(500, 4, PHYSICAL_BUTTON_COUNT);
    int third_val = (int) third_button;
 
    PhysicalButton handak_button;
    int second_index = 0;

    if((second_val >= (int) A) && (second_val <= (int) O))
    {
      second_index = second_val - ((int) A) + 1;
      handak_button = third_button;
    }
    if((second_val >= (int) YA) && (second_val <= (int) YO))
    {
      second_index = second_val - ((int) YA) + 5;
      handak_button = third_button;
    }

    if((third_val >= (int) A) && (third_val <= (int) O))
    {
      second_index = third_val - ((int) A) + 1;
      handak_button = second_button;
    }
    if((third_val >= (int) YA) && (third_val <= (int) YO))
    {
      second_index = third_val - ((int) YA) + 5;
      handak_button = second_button;
    }

    int handak_index;
    switch(handak_button)
    {
      case DAK:
        handak_index = 1;
        break;
      case HANDAK:
        handak_index = 2;
        break;
      default:
        handak_index = 0;
        break;
    }
    int const_index = button_val - ((int) K);

    return kana_button_mapping[handak_index][second_index][const_index];
  }
}
