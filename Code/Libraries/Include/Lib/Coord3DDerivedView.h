// Coord3D as retail declares it: a class derived from the three-float base value Coord3DBase.
// Opt-in companion to Coord3D.h / Coord3DBase.h for units whose bytes show the base subobject
// (Xfer::operator==(Coord3DBase&), equals(const Coord3DBase&)) or Coord3D's out-of-line
// constructor/destructor rows (0x0047A6A9, 0x000B3FD0). Include it INSTEAD of Coord3D.h /
// Coord3DBase.h, before anything else that includes them: it takes both include guards.
// The members a unit's bytes need are selected with macros defined before the include:
//   COORD3D_DV_CTOR_INLINE | COORD3D_DV_CTOR_EXTERN       default constructor {} / out of line
//   COORD3D_DV_COPY_INLINE | COORD3D_DV_COPY_EXTERN       member-wise copy constructor / out of line
//   COORD3D_DV_DTOR_INLINE | COORD3D_DV_DTOR_EXTERN       empty destructor / out of line
//   COORD3D_DV_BASE_SET inline Coord3DBase::set(x, y, z)   COORD3D_DV_ZERO     inline zero()   COORD3D_DV_EQUALS   equals(const Coord3DBase &) (out of line)
#ifndef CANONICAL_COORD3D_H
#define CANONICAL_COORD3D_H
#ifndef CANONICAL_COORD3DBASE_H
#define CANONICAL_COORD3DBASE_H

struct Coord3DBase {
    float x;
    float y;
    float z;
#ifdef COORD3D_DV_BASE_SET
    void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
#endif
};

#endif // CANONICAL_COORD3DBASE_H

struct Coord3D : public Coord3DBase {
#if defined(COORD3D_DV_CTOR_EXTERN)
    Coord3D();
#elif defined(COORD3D_DV_CTOR_INLINE)
    Coord3D() {}
#endif
#if defined(COORD3D_DV_COPY_EXTERN)
    Coord3D(const Coord3D &);
#elif defined(COORD3D_DV_COPY_INLINE)
    Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
#endif
#if defined(COORD3D_DV_DTOR_EXTERN)
    ~Coord3D();
#elif defined(COORD3D_DV_DTOR_INLINE)
    ~Coord3D() {}
#endif
#ifdef COORD3D_DV_ZERO
    void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
#endif
#ifdef COORD3D_DV_EQUALS
    bool equals(const Coord3DBase &that) const;
#endif
};

#endif // CANONICAL_COORD3D_H
