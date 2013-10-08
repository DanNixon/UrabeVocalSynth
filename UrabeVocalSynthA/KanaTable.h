#ifndef KANATABLE_H
#define KANATABLE_H

namespace KanaTable
{
  static const int KANA_COUNT = 71;

  enum Kana
  {
    _A = 0,  _I,  _U,  _E,  _O,
    _KA,  _KI,  _KU,  _KE,  _KO,
    _SA,  _SHI,  _SU,  _SE,  _SO,
    _TA,  _CHI,  _TSU,  _TE,  _TO,
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
    
    _NULL = 255
  };
};

#endif
