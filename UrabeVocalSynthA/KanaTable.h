#ifndef KANATABLE_H
#define KANATABLE_H

namespace KanaTable
{
  static const int KANA_COUNT = 128; //Old val = 71

  enum Kana
  {
    _A=0, _I,   _U,   _E,   _O,
    _KA,  _KI,  _KU,  _KE,  _KO,
    _SA,  _SHI, _SU,  _SE,  _SO,
    _TA,  _CHI, _TSU, _TE,  _TO,
    _NA,  _NI,  _NU,  _NE,  _NO,
    _HA,  _HI,  _HU,  _HE,  _HO,
    _MA,  _MI,  _MU,  _ME,  _MO,
    _YA,  _YU,  _YO,
    _RA,  _RI,  _RU,  _RE,  _RO,
    _WA,  _WO,
    _N,

    _GA,  _GI,  _GU,  _GE,  _GO,
    _ZA,  _JI,  _ZU,  _ZE,  _ZO,
    _DA,  _DI,  _DU,  _DE,  _DO,
    _BA,  _BI,  _BU,  _BE,  _BO,
    _PA,  _PI,  _PU,  _PE,  _PO,

    _KYA, _KYU, _KYO,
    _SHA, _SHU, _SHO,
    _CHA, _CHU, _CHO,
    _NYA, _NYU, _NYO,
    _HYA, _HYU, _HYO,
    _MYA, _MYU, _MYO,
    _RYA, _RYU, _RYO,

    _GYA, _GYU, _GYO,
    _JA,  _JU,  _JO,
    _BYA, _BYU, _BYO,
    _PYA, _PYU, _PYO,

    _K, _S, _T, _Ns, _H, _M, _Y, _R, _W, _G, _Z, _D, _B, _P,

    _NULL = 255
  };
};

#endif
