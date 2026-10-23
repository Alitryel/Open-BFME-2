// ICoord3D with retail's (int, int, int) constructor: opt-in companion to ICoord3D.h.
//
// Retail's ICoord3D has a component constructor (0x005CC49A, ??0ICoord3D@@QAE@HHH@Z, Code/Libraries/Source/
// WWVegas/WWMath/icoord.cpp) that callers reach through a call. The canonical ICoord3D.h stays plain: a unit whose
// bytes call that constructor includes this header INSTEAD of ICoord3D.h, before anything else that includes it:
// it takes ICoord3D.h's include guard. Same layout as the canonical header (sizeof 12, x/y/z at 0/4/8).
#ifndef CANONICAL_ICOORD3D_H
#define CANONICAL_ICOORD3D_H

struct ICoord3D {
    int x;
    int y;
    int z;
    ICoord3D() {}
    ICoord3D(int ax, int ay, int az);
};

#endif // CANONICAL_ICOORD3D_H
