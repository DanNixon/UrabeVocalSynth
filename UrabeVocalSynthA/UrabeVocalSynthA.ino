#include <MIDI.h>
#include <GinSing.h>
#include <U8glib.h>

#include "Defenitions.h"
#include "KanaTable.h"
#include "GLCDMan.h"
#include "GUIMan.h"

#define rcvPin 4
#define sndPin 3
#define ovfPin 2

using namespace GUIMan;

GinSing GS;
GinSingVoice *voice = 0x0;

GLCDManager glcd_man;
GUIManager gui_man(&glcd_man);

KanaTable::Kana phrase[] =
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

void setup ()
{
  pinMode(22, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(midi_note_handle);
  GS.begin(rcvPin , sndPin , ovfPin);
  voice = GS.getVoice();
  voice->begin();
  redraw();
}

int phrase_pos = 0;
int notes_on = 0;

void redraw()
{
  gui_man.current_window = JP_RUN;
  for(int i=0; i<7; i++)
  {
    int index = phrase_pos + i;
    if(notes_on) index--;
    gui_man.display_kana[i] = phrase[index];
  }
  gui_man.notes_on = notes_on;
  gui_man.draw();
}

void jpSpeakKana(KanaTable::Kana kana, GSNote note)
{
//  voice->setBlendSpeed(0.2f);
//  voice->setDelay(0.02f);
  voice->setNote(note);
  voice->speak(GSKanaMap::KanaMap[kana]);
}

void endSpeak()
{
  GSAllophone phrase[] = {_PA1, _ENDPHRASE};
  voice->speak(phrase);
}

void midi_note_handle(byte channel, byte pitch, byte velocity)
{
  if(velocity == 0)
  {
    notes_on--;
    if(notes_on == 0)
      endSpeak();
  }
  else
  {
    notes_on++;
    KanaTable::Kana kana = phrase[phrase_pos];
    phrase_pos++;
    if(phrase[phrase_pos] == KanaTable::_NULL)
      phrase_pos = 0;
    GSNote note = GS_MIDIMap::GS_MIDINotes[pitch];
    jpSpeakKana(kana, note);
  }
  redraw();
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
  heartbeat();
  MIDI.read();
}

