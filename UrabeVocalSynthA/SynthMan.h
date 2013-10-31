#ifndef SYNTHMAN_H
#define SYNTHMAN_H

#include <GinSing.h>
#include "ConfigDataDef.h"

namespace SynthMan
{
  enum ConfigOptionsMenu
  {
    VOLUME_SOURCE = 0,
    VOLUME_PRESET
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
