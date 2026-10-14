// Coord3D with retail's user-written constructors: opt-in companion to Coord3D.h.
//
// Retail's Coord3D is a class with an empty user default constructor (0x0047A6A9) and a member-wise
// user copy constructor (0x004216D3, three dword moves); coord3d.cpp carries that private view for
// the library bodies. The canonical Coord3D.h stays plain (POD) because the matched rows of ~1,250
// dependents byte-match against it: with these constructors 324 of 5,252 of them stop matching
// (33 units no longer compile: Coord3D union members, `Coord3D p = {x, y, z}`; 37 rows change bytes).
// A unit whose bytes need the non-POD type (by-value Coord3D arguments built through the copy
// constructor, expression temporaries with an ESP save) includes this header INSTEAD of Coord3D.h,
// before anything else that includes it: it takes Coord3D.h's include guard.
#ifndef CANONICAL_COORD3D_H
#define CANONICAL_COORD3D_H

struct Coord3D {
    float x;
    float y;
    float z;
    Coord3D() {}
    Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
    float length() const;
    void normalize();
    bool operator==(const Coord3D &r);
    float GetLengthSqrd() const;
    float GetLength() const;
    float GetLengthEstimate2D() const;
    float GetLength2D() const;
    float Normalize();
    float operator*(const struct Coord3DBase &r) const;
    void zero();
    void set(float x, float y, float z);
    void set(const struct Coord3DBase *p);
    void scale(float s);
    bool equals(const struct Coord3DBase &that) const;
    float GetLengthEstimate() const;
};

#endif // CANONICAL_COORD3D_H
