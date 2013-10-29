#ifndef JPSYNTHMAN_H
#define JPSYNTHMAN_H

#define KANA_BUFFER_SIZE 128

#include <GinSing.h>
#include "KanaTable.h"
#include "GSMidiMap.h"
#include "ConfigDataDef.h"
#include "GLCDMan.h"

static GSAllophone kana_map[KanaTable::KANA_COUNT][3] =
  {
    {_SPEEDDN, _A}, {_SPEEDDN, _I}, {_SPEEDDN, _U}, {_SPEEDDN, _E}, {_SPEEDDN, _OE},
    {_KE, _A}, {_KE, _I}, {_KE, _UE}, {_KE, _E}, {_KO, _OE},
    {_SE, _A}, {_SH, _I}, {_SE, _U}, {_SE, _E}, {_SE, _OE},
    {_T, _A}, {_CH, _I}, {_TS, _UE}, {_T, _E}, {_T, _OE},
    {_NE, _A}, {_NE, _I}, {_NE, _U}, {_NE, _E}, {_NO, _OE},
    {_HE, _A}, {_HE, _I}, {_HE, _U}, {_HE, _E}, {_HO, _OE},
    {_M, _A}, {_M, _I}, {_M, _U}, {_M, _E}, {_M, _OE},
    {_Y, _A}, {_Y, _U}, {_Y, _OE},
    {_R, _A}, {_R, _I}, {_R, _UE}, {_R, _E}, {_R, _OE},
    {_W, _A}, {_W, _OE},
    {_NE},
    {_GE, _A}, {_GE, _I}, {_GE, _UE}, {_GE, _E}, {_GO, _OE},
    {_Z, _A}, {_Z, _I}, {_Z, _U}, {_Z, _E}, {_Z, _OE},
    {_DE, _A}, {_Z, _I}, {_Z, _U}, {_DE, _E}, {_DO, _OE},
    {_BE, _A}, {_BE, _I}, {_BE, _U}, {_BE, _E}, {_BO, _OE},
    {_PE, _A}, {_PE, _I}, {_PE, _U}, {_PE, _E}, {_PO, _OE}
  }; //TODO: Expand for additional KanaTable::Kana

class JpSynthManager
{
  private:
    GinSingVoice *voice;
    int notes_on;
    int buffer_position;
    int buffer_add_position;
    int blend_speed;
    int phoneame_delay;
    int option_count;
    GLCDManager *glcd_man;
    void speak_kana(KanaTable::Kana, GSNote);
  
  public:
    KanaTable::Kana kana_buffer[KANA_BUFFER_SIZE];
    ConfigData::ConfigOption options[20];
    JpSynthManager();
    void init(GinSing GS);
    void end_speak();
    void handle_midi_note(byte, byte);
    int get_option_count();
    int get_buffer_source();
    int get_notes_on();
    int get_buffer_position();
    void kana_buffer_clear();
    void kana_buffer_add(KanaTable::Kana);
    void kana_buffer_rm_last();
};

#endif
