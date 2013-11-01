#ifndef SYNTHMAN_H
#define SYNTHMAN_H

#include <GinSing.h>
#include "ConfigDataDef.h"

namespace SynthMan
{
  enum ConfigOptionsMenu
  {
    VOLUME_SOURCE = 0,
    VOLUME_PRESET,

    SYNTH_WAVEFORM,
    FREQ_DISTORT_SRC,
    FREQ_DISTORT_VAL,

    BIAS,
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
      GinSingSynth *synth;
      GinSingMaster *master;
      int notes_on;
      int osc_pitch[6];
      int option_count;
      int master_volume;

    public:
      ConfigData::ConfigOption options[20];
      SynthManager();
      void init(GinSing);
      void update_config();
      int get_option_count();
      void handle_midi_note(byte, byte);
      void end_notes();
  };

};

#endif
