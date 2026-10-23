// Opt-in companion to ICoord2D.h for units that pass ICoord2D values as retail's two-int
// base value (ICoord2D::operator==). Kept out of ICoord2D.h like Coord3DBase.h.
#ifndef CANONICAL_ICOORD2DBASE_H
#define CANONICAL_ICOORD2DBASE_H

#include "ICoord2D.h"

struct ICoord2DBase {
    int x;
    int y;
};

// The canonical ICoord2D and ICoord2DBase share one 8-byte int pair.
inline ICoord2DBase &asBase(ICoord2D &c) { return *reinterpret_cast<ICoord2DBase *>(&c); }
inline const ICoord2DBase &asBase(const ICoord2D &c) { return *reinterpret_cast<const ICoord2DBase *>(&c); }

#endif // CANONICAL_ICOORD2DBASE_H
