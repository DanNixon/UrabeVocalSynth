#include "JpSynthMan.h"

JpSynthManager::JpSynthManager()
{
  this->buffer_position = 0;
  this->option_count = 5;
  this->options[1] = {"Blend Speed Value", ConfigData::INT, 500, {"-1", "1000"}, -1};
  this->options[0] = {"Blend Speed Source", ConfigData::ENUM, 0, {"Preset", "MIDI",}, 2};
  this->options[3] = {"Delay Value", ConfigData::INT, 1000, {"-1", "1000"}, -1};
  this->options[2] = {"Delay Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[4] = {"Kana Source", ConfigData::ENUM, 0, {"Keyboard", "File"}, 2};
}

void JpSynthManager::init(GinSing gs)
{
  this->voice = gs.getVoice();
  this->voice->begin();
}

void JpSynthManager::speak_kana(KanaTable::Kana kana, GSNote note)
{
  int blend_speed = this->options[1].value;
  int delay = this->options[3].value;
  if(blend_speed != -1)
  {
    float f_blend_speed = (float) blend_speed / 100.0f;
    this->voice->setBlendSpeed(f_blend_speed);
  }
  if(delay != -1)
  {
    float f_delay = (float) delay / 100.0f;
    this->voice->setDelay(f_delay);
  }
  this->voice->setNote(note);
  this->voice->speak(kana_map[kana]);
}

void JpSynthManager::end_speak()
{
  GSAllophone phrase[] = {_PA1, _ENDPHRASE};
  voice->speak(phrase);
}

void JpSynthManager::handle_midi_note(byte pitch, byte velocity)
{
  if(velocity == 0)
  {
    if(this->notes_on > 0)
      this->notes_on--;
    if(this->notes_on == 0)
      this->end_speak();
  }
  else
  {
    this->notes_on++;
    KanaTable::Kana kana = this->kana_buffer[this->buffer_position];
    this->buffer_position++;
    if(this->kana_buffer[this->buffer_position] == KanaTable::_NULL)
      this->buffer_position = 0;
    GSNote note = GS_MIDINotes[pitch];
    this->speak_kana(kana, note);
  }
}

void JpSynthManager::kana_buffer_clear()
{
  this->end_speak();
  this->notes_on = 0;
  for(int i=0; i<100; i++)
    this->kana_buffer[i] = KanaTable::_NULL;
}

void JpSynthManager::kana_buffer_add(KanaTable::Kana kana)
{
  //TODO
}

void JpSynthManager::kana_buffer_rm_last()
{
  //TODO
}

int JpSynthManager::get_notes_on() { return this->notes_on; }
int JpSynthManager::get_buffer_position() { return this->buffer_position; }

void JpSynthManager::set_phoneame_delay(int pd)
{
  if(pd > 1000) pd = 1000;
  if((pd < 0) && (pd != -1)) pd = 0;
  this->phoneame_delay = pd;
}

void JpSynthManager::set_blend_speed(int bs)
{
  if(bs > 1000) bs = 1000;
  if((bs < 0) && (bs != -1)) bs = 0;
  this->blend_speed = bs;
}
