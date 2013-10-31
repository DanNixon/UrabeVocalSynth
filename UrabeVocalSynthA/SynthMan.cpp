#include "SynthMan.h"

using namespace SynthMan;

SynthManager::SynthManager()
{
  this->option_count = 2;
  this->options[VOLUME_SOURCE] = {"Volume Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[VOLUME_PRESET] = {"Volume Preset", ConfigData::ENUM, 800, {"0", "1000"}, 25};
}

void SynthManager::init(GinSing GS)
{
  this->synth = GS.getSynth();
  this->master = GS.getMaster();
  this->synth->begin();
  this->update_config();
}

void SynthManager::update_config()
{
}

int SynthManager::get_option_count() { return this->option_count; }

void SynthManager::handle_midi_note(byte pitch, byte velocity)
{
}

void SynthManager::end_notes()
{
}
