#include <MIDI.h>
#include <GinSing.h>
#include <U8glib.h>

#include "KanaTable.h"
#include "GLCDMan.h"
#include "GUIMan.h"
#include "JpSynthMan.h"
#include "KeypadHandler.h"

#define rcvPin 4
#define sndPin 3
#define ovfPin 2

using namespace GUIMan;

GinSing GS;

GLCDManager glcd_man;
JpSynthManager jp_synth_man;
GUIManager gui_man(&glcd_man, &jp_synth_man);
Keypad::KeypadHandler key_man(&gui_man, &jp_synth_man);

KanaTable::Kana p[] =
  {
    KanaTable::_NA,
    KanaTable::_GA,
    KanaTable::_RE,
    KanaTable::_TE,
    KanaTable::_KU,
    KanaTable::_TO,
    KanaTable::_KI,
    KanaTable::_NO,
    KanaTable::_NA,
    KanaTable::_KA,
    KanaTable::_DE,
    KanaTable::_DE,
    KanaTable::_MO,
    KanaTable::_KE,
    KanaTable::_DA,
    KanaTable::_RU,
    KanaTable::_SA,
    KanaTable::_GA,
    KanaTable::_HO,
    KanaTable::_RA,
    KanaTable::_GU,
    KanaTable::_RU,
    KanaTable::_GU,
    KanaTable::_RU,
    KanaTable::_MA,
    KanaTable::_WA,
    KanaTable::_TE,
    KanaTable::_WA,
    KanaTable::_TA,
    KanaTable::_SHI,
    KanaTable::_KA,
    KanaTable::_RA,
    KanaTable::_HA,
    KanaTable::_NA,
    KanaTable::_RE,
    KanaTable::_RU,
    KanaTable::_KO,
    KanaTable::_KO,
    KanaTable::_RO,
    KanaTable::_MO,
    KanaTable::_MI,
    KanaTable::_E,
    KanaTable::_NA,
    KanaTable::_I,
    KanaTable::_WA,
    KanaTable::_SO,
    KanaTable::_U,
    KanaTable::_SHI,
    KanaTable::_RA,
    KanaTable::_NA,
    KanaTable::_I,
    KanaTable::_JI,
    KanaTable::_BU,
    KanaTable::_N,
    KanaTable::_KA,
    KanaTable::_RA,
    KanaTable::_U,
    KanaTable::_GO,
    KanaTable::_KU,
    KanaTable::_KO,
    KanaTable::_TO,
    KanaTable::_MO,
    KanaTable::_NA,
    KanaTable::_KU,
    KanaTable::_TO,
    KanaTable::_KI,
    KanaTable::_NO,
    KanaTable::_SU,
    KanaTable::_KI,
    KanaTable::_MA,
    KanaTable::_NI,
    KanaTable::_NA,
    KanaTable::_GA,
    KanaTable::_SA,
    KanaTable::_RE,
    KanaTable::_TSU,
    KanaTable::_ZU,
    KanaTable::_KE,
    KanaTable::_TE,
    KanaTable::_SHI,
    KanaTable::_RA,
    KanaTable::_NA,
    KanaTable::_I,
    KanaTable::_WA,
    KanaTable::_MA,
    KanaTable::_WA,
    KanaTable::_RI,
    KanaTable::_NO,
    KanaTable::_KO,
    KanaTable::_TO,
    KanaTable::_NA,
    KanaTable::_DO,
    KanaTable::_WA,
    KanaTable::_TA,
    KanaTable::_SHI,
    KanaTable::_WA,
    KanaTable::_WA,
    KanaTable::_TA,
    KanaTable::_SHI,
    KanaTable::_SO,
    KanaTable::_RE,
    KanaTable::_DA,
    KanaTable::_KE,
    KanaTable::_NULL
  };

void setup()
{
  pinMode(22, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(midi_note_handle);
  GS.begin(rcvPin, sndPin, ovfPin);
  jp_synth_man.init(GS);
  for(int i=0; i<100; i++)
    jp_synth_man.kana_buffer_add(p[i]);
  gui_man.draw();
//  Serial.begin(115200);
}

void midi_note_handle(byte channel, byte pitch, byte velocity)
{
  switch(gui_man.get_system_mode())
  {
    case MENU:
      break;
    case WAVEFORM:
      //Parse waveform synth MIDI here
      break;
    case VOCAL:
      jp_synth_man.handle_midi_note(pitch, velocity);
      break;
  }
  gui_man.draw();
}

long last_hb = 0;
boolean hb_state = false;

void heartbeat()
{
  int heartbeat_delay = 100;
  long current_time = millis();
  long delta_t = current_time - last_hb;
  if(delta_t > heartbeat_delay)
  {
    hb_state = !hb_state;
    int led_state = 0;
    if(hb_state) led_state = 1;
    digitalWrite(22, led_state);
    last_hb = current_time;
  }
}

void loop()
{
//  Keypad::PhysicalButton b = key_man.get_button(50, 0, Keypad::PHYSICAL_BUTTON_COUNT);
//  if(b != Keypad::_NONE)
//    Serial.println(b);

//  return;

  heartbeat();
  ButtonValue key_result;
  KanaTable::Kana k;
  switch(gui_man.get_system_mode())
  {
    case MENU:
      key_result = key_man.scan_menu();
      break;
    case VOCAL:
      MIDI.read();
      if(jp_synth_man.get_buffer_source() == 0)
      {
        k = key_man.scan_kana();
        jp_synth_man.kana_buffer_add(k);
        if(k != KanaTable::_NULL)
          gui_man.draw();
      }
      key_result = key_man.scan_funct_keys();
      break;
    case WAVEFORM:
      MIDI.read();
      key_result = key_man.scan_funct_keys();
      break;
  }
  if(key_result != _NULL)
    gui_man.handle_menu_input(key_result);
}
