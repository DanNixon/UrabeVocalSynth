#ifndef JPSYNTHMAN_H
#define JPSYNTHMAN_H

#define KANA_BUFFER_SIZE 512

#include <GinSing.h>
#include "KanaTable.h"
#include "GSMidiMap.h"
#include "ConfigDataDef.h"
#include "GLCDMan.h"

namespace JpSynthMan
{
  static GSAllophone kana_map[KanaTable::KANA_COUNT][4] =
    {
      {_SPEEDDN, _A}, {_SPEEDDN, _I}, {_SPEEDDN, _U}, {_SPEEDDN, _E}, {_SPEEDDN, _OE},

      {_KE, _A},  {_KE, _I},  {_KE, _UE}, {_KE, _E},  {_KO, _OE},
      {_SE, _A},  {_SH, _I},  {_SE, _U},  {_SE, _E},  {_SE, _OE},
      {_T, _A},   {_CH, _I},  {_TS, _UE}, {_T, _E},   {_T, _OE},
      {_NE, _A},  {_NE, _I},  {_NE, _U},  {_NE, _E},  {_NO, _OE},
      {_HE, _A},  {_HE, _I},  {_HE, _U},  {_HE, _E},  {_HO, _OE},
      {_M, _A},   {_M, _I},   {_M, _U},   {_M, _E},   {_M, _OE},
      {_Y, _A},   {_Y, _U},   {_Y, _OE},
      {_R, _A},   {_R, _I},   {_R, _UE},  {_R, _E},   {_R, _OE},
      {_W, _A},   {_W, _OE},
      {_NE},

      {_GE, _A},  {_GE, _I},  {_GE, _UE}, {_GE, _E},  {_GO, _OE},
      {_Z, _A},   {_Z, _I},   {_Z, _U},   {_Z, _E},   {_Z, _OE},
      {_DE, _A},  {_Z, _I},   {_Z, _U},   {_DE, _E},  {_DO, _OE},
      {_BE, _A},  {_BE, _I},  {_BE, _U},  {_BE, _E},  {_BO, _OE},
      {_PE, _A},  {_PE, _I},  {_PE, _U},  {_PE, _E},  {_PO, _OE},

      {_KE, _Y, _A},  {_KE, _Y, _U},  {_KE, _Y, _OE},
      {_SH, _A},      {_SH, _UE},     {_SH, _OE},
      {_CH, _A},      {_CH, _U},      {_CH, _OE},
      {_NE, _Y, _A},  {_NE, _Y, _U},  {_NE, _Y, _OE},
      {_HE, _Y, _A},  {_HE, _Y, _U},  {_HE, _Y, _OE},
      {_M, _Y, _A},   {_M, _Y, _U},   {_M, _Y, _OE},
      {_R, _Y, _A},   {_R, _Y, _U},   {_R, _Y, _OE},
      {_GE, _Y, _A},  {_GE, _Y, _U},  {_GE, _Y, _OE},
      {_Z, _Y, _A},   {_Z, _Y, _U},   {_Z, _Y, _OE},
      {_BE, _Y, _A},  {_BE, _Y, _U},  {_BE, _Y, _OE},
      {_PE, _Y, _A},  {_PE, _Y, _U},  {_PE, _Y, _OE},

      {_KE}, {_SE}, {_T}, {_HE}, {_M}, {_Y}, {_R}, {_W},
      {_GE}, {_Z}, {_DE}, {_BE}, {_PE}
    };
  
  enum ConfigOptionsMenu
  {
    VOLUME_SOURCE = 0,
    VOLUME_PRESET,
    KANA_SOURCE,

    BLEND_SPEED_SOURCE,
    BLEND_SPEED_PRESET,
    DELAY_SOURCE,
    DELAY_PRESET,
  };

  class JpSynthManager
  {
    private:
      GinSingVoice *voice;
      GinSingMaster *master;
      GLCDManager *glcd_man;
      int notes_on;
      int buffer_position;
      int option_count;
      int buffer_add_position;
      int master_volume;
      int blend_speed;
      int phoneame_delay;
      void speak_kana(KanaTable::Kana, GSNote);
  
    public:
      KanaTable::Kana kana_buffer[KANA_BUFFER_SIZE];
      ConfigData::ConfigOption options[7];
      JpSynthManager();
      void init(GinSing);
      void panic();
      void update_config();
      void end_speak();
      void handle_midi_note(byte, byte);
      int get_option_count();
      int get_buffer_source();
      int get_notes_on();
      int get_buffer_position();
      int get_buffer_add_position();
      void kana_buffer_clear();
      void kana_buffer_add(KanaTable::Kana);
      void kana_buffer_rm_last();
  };

};

#endif
