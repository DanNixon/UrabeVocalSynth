#ifndef SYNTHMAN_H
#define SYNTHMAN_H

#include <GinSing.h>
#include "ConfigDataDef.h"
#include "GSMidiMap.h"

#define WSYNTH_CC_VOLUME 18
#define WSYNTH_CC_WAVE 17
#define WSYNTH_CC_FDIST 13
#define WSYNTH_CC_ATKDUR 10
#define WSYNTH_CC_ATKAMP 14
#define WSYNTH_CC_DECDUR 11
#define WSYNTH_CC_DECAMP 15
#define WSYNTH_CC_RELDUR 12
#define WSYNTH_CC_RELAMP 16

namespace SynthMan
{
  enum ConfigOptionsMenu
  {
    VOLUME_SOURCE = 0,
    VOLUME_PRESET,

    SYNTH_WAVEFORM_SRC,
    SYNTH_WAVEFORM,
    FREQ_DISTORT_SRC,
    FREQ_DISTORT_VAL,

    OVERFLOW,
    P_DUTY_CYCLE,

    ATK_DUR_SRC,
    ATK_DUR_VAL,
    ATK_AMP_SRC,
    ATK_AMP_VAL,

    DEC_DUR_SRC,
    DEC_DUR_VAL,
    DEC_AMP_SRC,
    DEC_AMP_VAL,

    REL_DUR_SRC,
    REL_DUR_VAL,
    REL_AMP_SRC,
    REL_AMP_VAL
  };

  class SynthManager
  {
    private:
      void update_config_worker();
      GinSingSynth *synth;
      GinSingMaster *master;
      int notes_on;
      int osc_pitch[6];
      int option_count;
      int master_volume;
      int waveform;
      int freq_distortion;
      int attack_duration;
      int attack_volume;
      int decay_duration;
      int decay_volume;
      int release_duration;
      int release_volume;

    public:
      ConfigData::ConfigOption options[20];
      SynthManager();
      void init(GinSing);
      void panic();
      void update_config();
      int get_option_count();
      int get_notes_on();
      void handle_midi_note(byte, byte);
      void handle_midi_cc(byte, byte);
      void end_notes();
      char *get_waveform_name();
      int get_volume();
      int get_freq_distortion();
      int get_attack_amp();
      char *get_attack_duration();
      int get_decay_amp();
      char * get_decay_duration();
      int get_release_amp();
      char *get_release_duration();
  };

};

#endif
