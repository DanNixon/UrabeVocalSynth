#include "JpSynthMan.h"

JpSynthManager::JpSynthManager()
{
  this->buffer_position = 0;
  ConfigData::ConfigOption opt = {"test", ConfigData::ENUM, 0, {"A", "B", "C"}, 3};
  //todo: init menu options
}

void JpSynthManager::init(GinSing gs)
{
  this->voice = gs.getVoice();
  this->voice->begin();
}

void JpSynthManager::speak_kana(KanaTable::Kana kana, GSNote note)
{
//  voice->setBlendSpeed(0.2f);
//  voice->setDelay(0.02f);
  voice->setNote(note);
  voice->speak(kana_map[kana]);
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

int JpSynthManager::get_notes_on()
{
  return this->notes_on;
}

int JpSynthManager::get_buffer_position()
{
  return this->buffer_position;
}
