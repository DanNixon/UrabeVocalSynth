#include "SynthMan.h"

using namespace SynthMan;

SynthManager::SynthManager()
{
  this->option_count = 20;
  this->options[VOLUME_SOURCE] = {"Volume Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[VOLUME_PRESET] = {"Volume Preset", ConfigData::ENUM, 800, {"0", "1000"}, 25};

  this->options[SYNTH_WAVEFORM]   = {"Waveform", ConfigData::ENUM, 0, {"Sine", "Triangle", "Sawtooth", "Ramp", "Pulse", "Noise"}, 6};
  this->options[FREQ_DISTORT_SRC] = {"Freq. Distort. Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[FREQ_DISTORT_VAL] = {"Freq. Distort. Preset", ConfigData::INT, 0, {"0", "1000"}, 50};

  this->options[BIAS]         = {"Waveform Bias", ConfigData::ENUM, 0, {"Symmetrical", "Positive"}, 2};
  this->options[OVERFLOW]     = {"Overflow", ConfigData::ENUM, 0, {"Enable", "Disable"}, 2};
  this->options[P_DUTY_CYCLE] = {"Pulse Duty Cycle", ConfigData::INT, 0, {"-1000", "1000"}, 50};


  this->options[ATK_DUR_SRC] = {"Attack Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[ATK_DUR_VAL] = {"Attack Dur. Preset", ConfigData::ENUM, 0, {"2", "8", "16", "24", "38", "56", "68", "80", "100", "250", "500", "800", "1000", "2800", "5600", "11200"}, 16};
  this->options[ATK_AMP_SRC] = {"Attack Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[ATK_AMP_VAL] = {"Attack Amp. Preset", ConfigData::INT, 1000, {"0", "1000"}, 25};

  this->options[DEC_DUR_SRC] = {"Decay Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[DEC_DUR_VAL] = {"Decay Dur. Preset", ConfigData::ENUM, 0, {"2", "6", "10", "15", "23", "34", "40", "48", "59", "145", "292", "455", "575", "1500", "2785", "4873"}, 16};
  this->options[DEC_AMP_SRC] = {"Decay Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[DEC_AMP_VAL] = {"Decay Amp. Preset", ConfigData::INT, 800, {"0", "1000"}, 25};

  this->options[REL_DUR_SRC] = {"Release Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[REL_DUR_VAL] = {"Release Dur. Preset", ConfigData::ENUM, 0, {"2", "6", "10", "15", "23", "34", "40", "48", "59", "145", "292", "455", "575", "1500", "2785", "4873"}, 16};
  this->options[REL_AMP_SRC] = {"Release Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[REL_AMP_VAL] = {"Release Amp. Preset", ConfigData::INT, 0, {"0", "1000"}, 25};
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
