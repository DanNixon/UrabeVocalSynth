#include "SynthMan.h"

using namespace SynthMan;

GSAttackDur attackdur_arr[16] = {
  AT_2MS,     AT_8MS,     AT_16MS,    AT_24MS,    AT_38MS,    AT_56MS,
  AT_68MS,    AT_80MS,    AT_100MS,   AT_250MS,   AT_500MS,   AT_800MS,
  AT_1000MS,  AT_2800MS,  AT_5600MS,  AT_11200MS
};

GSDecRelDur decreldur_arr[16] = {
  DR_2MS,     DR_6MS,     DR_10MS,    DR_15MS,    DR_23MS,    DR_34MS,
  DR_40MS,    DR_48MS,    DR_59MS,    DR_145MS,   DR_292MS,   DR_455MS,
  DR_575MS,   DR_1500MS,  DR_2785MS,  DR_4873MS
};


SynthManager::SynthManager()
{
  this->option_count = 18;

  this->options[SYNTH_WAVEFORM_SRC] = (ConfigData::ConfigOption) {"Waveform Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[SYNTH_WAVEFORM]     = (ConfigData::ConfigOption) {"Waveform", ConfigData::ENUM, 0, {"Sine", "Triangle", "Sawtooth", "Ramp", "Pulse", "Noise"}, 6};
  this->options[FREQ_DISTORT_SRC]   = (ConfigData::ConfigOption) {"Freq. Distort. Source", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[FREQ_DISTORT_VAL]   = (ConfigData::ConfigOption) {"Freq. Distort. Preset", ConfigData::INT, 0, {"0", "1000"}, 50};

  this->options[OVERFLOW]     = (ConfigData::ConfigOption) {"Overflow", ConfigData::ENUM, 0, {"Disable", "Enable"}, 2};
  this->options[P_DUTY_CYCLE] = (ConfigData::ConfigOption) {"Pulse Duty Cycle", ConfigData::INT, 0, {"-1000", "1000"}, 50};

  this->options[ATK_DUR_SRC] = (ConfigData::ConfigOption) {"Attack Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[ATK_DUR_VAL] = (ConfigData::ConfigOption) {"Attack Dur. Preset", ConfigData::ENUM, 0, {"2", "8", "16", "24", "38", "56", "68", "80", "100", "250", "500", "800", "1000", "2800", "5600", "11200"}, 16};
  this->options[ATK_AMP_SRC] = (ConfigData::ConfigOption) {"Attack Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[ATK_AMP_VAL] = (ConfigData::ConfigOption) {"Attack Amp. Preset", ConfigData::INT, 1000, {"0", "1000"}, 25};

  this->options[DEC_DUR_SRC] = (ConfigData::ConfigOption) {"Decay Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[DEC_DUR_VAL] = (ConfigData::ConfigOption) {"Decay Dur. Preset", ConfigData::ENUM, 0, {"2", "6", "10", "15", "23", "34", "40", "48", "59", "145", "292", "455", "575", "1500", "2785", "4873"}, 16};
  this->options[DEC_AMP_SRC] = (ConfigData::ConfigOption) {"Decay Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[DEC_AMP_VAL] = (ConfigData::ConfigOption) {"Decay Amp. Preset", ConfigData::INT, 800, {"0", "1000"}, 25};

  this->options[REL_DUR_SRC] = (ConfigData::ConfigOption) {"Release Dur. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[REL_DUR_VAL] = (ConfigData::ConfigOption) {"Release Dur. Preset", ConfigData::ENUM, 0, {"2", "6", "10", "15", "23", "34", "40", "48", "59", "145", "292", "455", "575", "1500", "2785", "4873"}, 16};
  this->options[REL_AMP_SRC] = (ConfigData::ConfigOption) {"Release Amp. Src", ConfigData::ENUM, 0, {"Preset", "MIDI"}, 2};
  this->options[REL_AMP_VAL] = (ConfigData::ConfigOption) {"Release Amp. Preset", ConfigData::INT, 0, {"0", "1000"}, 25};
}

void SynthManager::init(GinSing GS)
{
  this->synth = GS.getSynth();
  this->synth->begin();
  this->update_config();
}

void SynthManager::panic()
{
  this->end_notes();
  this->synth->begin();
  this->update_config();
}

void SynthManager::update_config()
{
  synth->selectBank(BANK_A);
  this->update_config_worker();

  synth->selectBank(BANK_B);
  this->update_config_worker();
}

void SynthManager::update_config_worker()
{
  synth->setPatch(OSC_1_TO_MIXER | OSC_2_TO_MIXER | OSC_3_TO_MIXER);
  
  int overflow_en = this->options[OVERFLOW].value;

  if(this->options[SYNTH_WAVEFORM_SRC].value == 0)
    this->waveform = this->options[SYNTH_WAVEFORM].value;

  if(this->options[FREQ_DISTORT_SRC].value == 0)
    this->freq_distortion = this->options[FREQ_DISTORT_VAL].value;
  float f_freq_dist = (float) this->freq_distortion / 100.0f;

  int duty_cycle = this->options[P_DUTY_CYCLE].value;
  float f_duty_cycle = (float) duty_cycle / 100.0f;

  if(this->options[ATK_DUR_SRC].value == 0)
    this->attack_duration = this->options[ATK_DUR_VAL].value;

  if(this->options[ATK_AMP_SRC].value == 0)
    this->attack_volume = this->options[ATK_AMP_VAL].value;
  float f_attack_volume = (float) this->attack_volume / 100.0f;

  if(this->options[DEC_DUR_SRC].value == 0)
    this->decay_duration = this->options[DEC_DUR_VAL].value;

  if(this->options[DEC_AMP_SRC].value == 0)
    this->decay_volume = this->options[DEC_AMP_VAL].value;
  float f_decay_volume = (float) this->decay_volume / 100.0f;

  if(this->options[REL_DUR_SRC].value == 0)
    this->release_duration = this->options[REL_DUR_VAL].value;

  if(this->options[REL_AMP_SRC].value == 0)
    this->release_volume = this->options[REL_AMP_VAL].value;
  float f_release_volume = (float) this->release_volume / 100.0f;

  synth->setFreqDist(OSC_1, f_freq_dist);
  synth->setFreqDist(OSC_2, f_freq_dist);
  synth->setFreqDist(OSC_3, f_freq_dist);

  synth->setDutyCycle(OSC_1, f_duty_cycle);
  synth->setDutyCycle(OSC_2, f_duty_cycle);
  synth->setDutyCycle(OSC_3, f_duty_cycle);

  synth->setEnvelope(OSC_1,
      attackdur_arr[this->attack_duration], f_attack_volume,
      decreldur_arr[this->decay_duration], f_decay_volume,
      decreldur_arr[this->release_duration], f_release_volume);
  synth->setEnvelope(OSC_2,
      attackdur_arr[this->attack_duration], f_attack_volume,
      decreldur_arr[this->decay_duration], f_decay_volume,
      decreldur_arr[this->release_duration], f_release_volume);
  synth->setEnvelope(OSC_3,
      attackdur_arr[this->attack_duration], f_attack_volume,
      decreldur_arr[this->decay_duration], f_decay_volume,
      decreldur_arr[this->release_duration], f_release_volume);

  switch(waveform)
  {
    case 0:
      synth->setWaveform(OSC_1, SINE);
      synth->setWaveform(OSC_2, SINE);
      synth->setWaveform(OSC_3, SINE);
      break;
    case 1:
      synth->setWaveform(OSC_1, TRIANGLE);
      synth->setWaveform(OSC_2, TRIANGLE);
      synth->setWaveform(OSC_3, TRIANGLE);
      break;
    case 2:
      synth->setWaveform(OSC_1, SAWTOOTH);
      synth->setWaveform(OSC_2, SAWTOOTH);
      synth->setWaveform(OSC_3, SAWTOOTH);
      break;
    case 3:
      synth->setWaveform(OSC_1, RAMP);
      synth->setWaveform(OSC_2, RAMP);
      synth->setWaveform(OSC_3, RAMP);
      break;
    case 4:
      synth->setWaveform(OSC_1, PULSE);
      synth->setWaveform(OSC_2, PULSE);
      synth->setWaveform(OSC_3, PULSE);
      break;
    case 5:
      synth->setWaveform(OSC_1, NOISE);
      synth->setWaveform(OSC_2, NOISE);
      synth->setWaveform(OSC_3, NOISE);
      break;
  }

  if(overflow_en)
  {
    synth->enableOverflow(OSC_1, true);
    synth->enableOverflow(OSC_2, true);
    synth->enableOverflow(OSC_3, true);
  }
  else
  {
    synth->enableOverflow(OSC_1, false);
    synth->enableOverflow(OSC_2, false);
    synth->enableOverflow(OSC_3, false);
  }
}

int SynthManager::get_option_count() { return this->option_count; }
int SynthManager::get_notes_on() { return this->notes_on; }

void SynthManager::handle_midi_cc(byte number, byte value)
{
  if((this->options[SYNTH_WAVEFORM_SRC].value == 1) && (number == WSYNTH_CC_WAVE))
    this->waveform = map(value, 0, 127, 0, 5);
  if((this->options[FREQ_DISTORT_SRC].value == 1) && (number == WSYNTH_CC_FDIST))
    this->freq_distortion = map(value, 0, 127, 0, 1000);
  if((this->options[ATK_DUR_SRC].value == 1) && (number == WSYNTH_CC_ATKDUR))
    this->attack_duration = attackdur_arr[map(value, 0, 127, 0, 15)];
  if((this->options[ATK_AMP_SRC].value == 1) && (number == WSYNTH_CC_ATKAMP))
    this->attack_volume = map(value, 0, 127, 0, 1000);
  if((this->options[DEC_DUR_SRC].value == 1) && (number == WSYNTH_CC_DECDUR))
    this->decay_duration = decreldur_arr[map(value, 0, 127, 0, 15)];
  if((this->options[DEC_AMP_SRC].value == 1) && (number == WSYNTH_CC_DECAMP))
    this->decay_volume = map(value, 0, 127, 0, 1000);
  if((this->options[REL_DUR_SRC].value == 1) && (number == WSYNTH_CC_RELDUR))
    this->release_duration = decreldur_arr[map(value, 0, 127, 0, 15)];
  if((this->options[REL_AMP_SRC].value == 1) && (number == WSYNTH_CC_RELAMP))
    this->release_volume = map(value, 0, 127, 0, 1000);
}

void SynthManager::handle_midi_note(byte pitch, byte velocity)
{
  GSNote note = GS_MIDINotes[pitch];

  if(velocity == 0)
  {
    for(int i = 0; i < 6; i++)
    {
      if(this->osc_pitch[i] == pitch)
      {
        if(i < 3)
          synth->selectBank(BANK_A);
        else
          synth->selectBank(BANK_B);
        switch(i)
        {
          case 0:
          case 3:
            synth->release(OSC_1);
            break;
          case 1:
          case 4:
            synth->release(OSC_2);
            break;
          case 2:
          case 5:
            synth->release(OSC_3);
            break;
        }
        this->osc_pitch[i] = 0;
        this->notes_on--;
        return;
      }
    }
  }
  else
  {
    if(this->notes_on < 6)
    {
      int vol_int = map(velocity, 0, 256, 0, 1000);
      float volume = ((float) vol_int) / 1000.0f;
      
      for(int i = 0; i < 6; i++)
      {
        if(this->osc_pitch[i] == 0)
        {
          if(i < 3)
            synth->selectBank(BANK_A);
          else
            synth->selectBank(BANK_B);
          switch(i)
          {
            case 0:
            case 3:
              synth->setNote(OSC_1, note);
              synth->setAmplitude(OSC_1, volume);
              synth->trigger(OSC_1);
              break;
            case 1:
            case 4:
              synth->setNote(OSC_2, note);
              synth->setAmplitude(OSC_2, volume);
              synth->trigger(OSC_2);
              break;
            case 2:
            case 5:
              synth->setNote(OSC_3, note);
              synth->setAmplitude(OSC_3, volume);
              synth->trigger(OSC_3);
              break;
          }
          this->osc_pitch[i] = pitch;
          this->notes_on++;
          return;
        }
      }
    }
  }
}

void SynthManager::end_notes()
{
  synth->selectBank(BANK_A);
  synth->setAmplitude(OSC_1, 0);
  synth->setAmplitude(OSC_2, 0);
  synth->setAmplitude(OSC_3, 0);
  synth->release(OSC_1);
  synth->release(OSC_2);
  synth->release(OSC_3);
  synth->selectBank(BANK_B);
  synth->setAmplitude(OSC_1, 0);
  synth->setAmplitude(OSC_2, 0);
  synth->setAmplitude(OSC_3, 0);
  synth->release(OSC_1);
  synth->release(OSC_2);
  synth->release(OSC_3);
  this->notes_on = 0;
}

int SynthManager::get_freq_distortion() { return this->freq_distortion; }

int SynthManager::get_attack_amp() { return this->attack_volume; }
int SynthManager::get_decay_amp() { return this->decay_volume; }
int SynthManager::get_release_amp() { return this->release_volume; }

char* SynthManager::get_attack_duration() { return this->options[ATK_DUR_VAL].values[this->attack_duration]; }
char* SynthManager::get_decay_duration() { return this->options[DEC_DUR_VAL].values[this->decay_duration]; }
char* SynthManager::get_release_duration() { return this->options[REL_DUR_VAL].values[this->release_duration]; }
char* SynthManager::get_waveform_name() { return this->options[SYNTH_WAVEFORM].values[this->waveform]; }
