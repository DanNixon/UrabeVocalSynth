#include "JpSynthMan.h"

using namespace JpSynthMan;

JpSynthManager::JpSynthManager()
{
  this->buffer_position = 0;
  this->buffer_add_position = 0;
  for(int i=0; i<KANA_BUFFER_SIZE; i++)
    this->kana_buffer[i] = KanaTable::_NULL;

  this->option_count = 5;

  this->options[KANA_SOURCE]        = {"Kana Source", ConfigData::ENUM, 0, {"Keyboard", "File"}, 2};
  this->options[BLEND_SPEED_SOURCE] = {"Blend Speed Source", ConfigData::ENUM, 0, {"Preset", "MIDI",}, 2};
  this->options[BLEND_SPEED_PRESET] = {"Blend Speed Preset", ConfigData::INT, -1, {"-1", "1000"}, -1};
  this->options[DELAY_SOURCE]       = {"Delay Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[DELAY_PRESET]       = {"Delay Preset", ConfigData::INT, -1, {"-1", "1000"}, -1};
}

void JpSynthManager::init(GinSing gs)
{
  this->voice = gs.getVoice();
  this->voice->begin();
  this->update_config();
}

void JpSynthManager::panic()
{
  this->end_speak();
  this->update_config();
  this->voice->begin();
}

void JpSynthManager::update_config()
{
  if(this->options[BLEND_SPEED_SOURCE].value == 0)
    this->blend_speed = this->options[BLEND_SPEED_PRESET].value;
  if(this->options[DELAY_SOURCE].value == 0)
    this->phoneame_delay = this->options[DELAY_PRESET].value;
}

void JpSynthManager::handle_midi_cc(byte number, byte value)
{
  if((this->options[BLEND_SPEED_SOURCE].value == 1) && (number == JPSYNTH_CC_BLENDSPEED))
    this->blend_speed = map(value, 0, 127, -1, 1000);
  if((this->options[DELAY_SOURCE].value == 1) && (number == JPSYNTH_CC_DELAY))
    this->phoneame_delay = map(value, 0, 127, -1, 1000);
}

void JpSynthManager::speak_kana(KanaTable::Kana kana, GSNote note)
{
  this->update_config();
  if(this->blend_speed != -1)
  {
    float f_blend_speed = (float) this->blend_speed / 100.0f;
    this->voice->setBlendSpeed(f_blend_speed);
  }
  if(this->phoneame_delay != -1)
  {
    float f_delay = (float) this->phoneame_delay / 100.0f;
    this->voice->setDelay(f_delay);
  }
  this->voice->setNote(note);
  if((kana >= 0) && (kana < KanaTable::KANA_COUNT))
    this->voice->speak(kana_map[kana]);
}

void JpSynthManager::end_speak()
{
  GSAllophone phrase[] = {_PA1, _ENDPHRASE};
  voice->speak(phrase);
  this->notes_on = 0;
  this->kana_buffer[this->buffer_position - 1] = KanaTable::_NULL;
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
    if(kana != KanaTable::_NULL)
    {
      GSNote note = GS_MIDINotes[pitch];
      this->speak_kana(kana, note);

      this->buffer_position++;
      int rm_position;
      switch(this->buffer_position)
      {
        case KANA_BUFFER_SIZE - 1:
          rm_position = KANA_BUFFER_SIZE - 3;
          this->buffer_position = 0;
          break;
        case 0:
          rm_position = KANA_BUFFER_SIZE - 2;
          break;
        default:
          rm_position = this->buffer_position - 2;
          break;
      }
      this->kana_buffer[rm_position] = KanaTable::_NULL;
    }
  }
}

void JpSynthManager::kana_buffer_clear()
{
  this->end_speak();
  this->notes_on = 0;
  this->buffer_position = 0;
  this->buffer_add_position = 0;
  for(int i=0; i<KANA_BUFFER_SIZE; i++)
    this->kana_buffer[i] = KanaTable::_NULL;
}

void JpSynthManager::kana_buffer_add(KanaTable::Kana kana)
{
  if(kana != KanaTable::_NULL)
  {
    if(this->buffer_add_position >= KANA_BUFFER_SIZE)
      this->buffer_add_position = 0;
    if(this->kana_buffer[this->buffer_add_position] == KanaTable::_NULL)
    {
      this->kana_buffer[buffer_add_position] = kana;
      this->buffer_add_position++;
    }
  }
}

void JpSynthManager::kana_buffer_rm_last()
{
  if(this->buffer_add_position == 0)
    this->buffer_add_position = KANA_BUFFER_SIZE - 1;
  this->kana_buffer[this->buffer_add_position] = KanaTable::_NULL;
}

int JpSynthManager::get_buffer_source() { return this->options[KANA_SOURCE].value; }
int JpSynthManager::get_notes_on() { return this->notes_on; }
int JpSynthManager::get_buffer_position() { return this->buffer_position; }
int JpSynthManager::get_buffer_add_position() { return this->buffer_add_position; }
int JpSynthManager::get_option_count() { return this->option_count; }
