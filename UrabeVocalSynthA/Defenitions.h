#ifndef DEFS_H
#define DEFS_H

#include <GinSing.h>
#include "KanaTable.h"


namespace GS_MIDIMap
{
  GSNote GS_MIDINotes[] =
    {
      C_0, CS_0, D_0, DS_0, E_0, F_0, FS_0, G_0, GS_0, A_0, AS_0, B_0,
      C_1, CS_1, D_1, DS_1, E_1, F_1, FS_1, G_1, GS_1, A_1, AS_1, B_1,
      C_2, CS_2, D_2, DS_2, E_2, F_2, FS_2, G_2, GS_2, A_2, AS_2, B_2,
      C_3, CS_3, D_3, DS_3, E_3, F_3, FS_3, G_3, GS_3, A_3, AS_3, B_3,
      C_4, CS_4, D_4, DS_4, E_4, F_4, FS_4, G_4, GS_4, A_4, AS_4, B_4,
      C_5, CS_5, D_5, DS_5, E_5, F_5, FS_5, G_5, GS_5, A_5, AS_5, B_5,
      C_6, CS_6, D_6, DS_6, E_6, F_6, FS_6, G_6, GS_6, A_6, AS_6, B_6,
      C_7, CS_7, D_7, DS_7, E_7, F_7, FS_7, G_7, GS_7, A_7, AS_7, B_7,
    };
};

namespace GSKanaMap
{
  static GSAllophone KanaMap [KanaTable::KANA_COUNT][3] =
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
    };
};

#endif
