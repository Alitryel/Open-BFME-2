// Coord2D with retail's user-written constructors: opt-in companion to Coord2D.h.
//
// Retail's Coord2D is a class with an empty user default constructor (0x0047A6A9), a member-wise user copy
// constructor (0x005CFBC2, exported as ??0Coord2D@@QAE@ABV0@@Z), a (float, float) constructor (0x00003F3A) and an
// empty user destructor (0x000B3FD0) (reverse/exports.csv). The canonical Coord2D.h stays plain (POD) like
// Coord3D.h: matched rows of its dependents byte-match against it. A unit whose bytes need the non-POD type
// (a member or by-value Coord2D copied through the constructor, whose scalar loads and stores then schedule as
// inlined constructor statements) includes this header INSTEAD of Coord2D.h, before anything else that includes
// it: it takes Coord2D.h's include guard. See Coord3DCtorView.h for the same view of Coord3D.
#ifndef CANONICAL_COORD2D_H
#define CANONICAL_COORD2D_H

class Coord2D {
public:
    float x;
    float y;
    Coord2D() {}
    Coord2D(const Coord2D &o) : x(o.x), y(o.y) {}
    Coord2D(float ax, float ay) : x(ax), y(ay) {}
    void normalize();
    float length() const;
    float toAngle() const;
};

#endif // CANONICAL_COORD2D_H
