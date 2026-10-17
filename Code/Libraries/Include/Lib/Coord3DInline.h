// Coord3D with Zero Hour's header-inline arithmetic: opt-in companion to Coord3D.h.
//
// In Zero Hour's Coord3D the small mutators (zero, set, add, sub, scale) are defined in the class,
// so retail units that call them carry the stores in place. The canonical Coord3D.h declares them
// out of line (their owner rows live in coord3d.cpp) and its dependents match against that, so a
// unit whose bytes show the inline stores includes this header INSTEAD of Coord3D.h, before
// anything else that includes it: it takes Coord3D.h's include guard. The type stays a POD triple;
// only the bodies below differ from the canonical declaration set. `#define COORD3D_INLINE_ASSIGN` first
// adds the member-wise operator= (retail copies through three scalar moves instead of a block move). Inline members that a unit
// never calls are not emitted. `#define COORD3D_INLINE_NOTHROW_ESTIMATE` first declares GetLengthEstimate2D throw(): for units
// whose retail EH tables register no unwind state for a local live across the call (the estimate's body was visible there).
#ifndef CANONICAL_COORD3D_H
#define CANONICAL_COORD3D_H

struct Coord3D {
    float x;
    float y;
    float z;
    float length() const;
    void normalize();
    bool operator==(const Coord3D &r);
    float GetLengthSqrd() const;
    float GetLength() const;
#ifdef COORD3D_INLINE_NOTHROW_ESTIMATE
    float GetLengthEstimate2D() const throw();
#else
    float GetLengthEstimate2D() const;
#endif
    float GetLength2D() const;
    float Normalize();
    float Normalize2D();
    float operator*(const struct Coord3DBase &r) const;
    void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
    void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    void set(const struct Coord3DBase *p);
    void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
    void add(const Coord3D *p) { x += p->x; y += p->y; z += p->z; }
    void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
#ifdef BFME_COORD3D_INLINE_SCALE_LINK
    __declspec(dllimport) __forceinline
#endif
    void scale(float s) { x *= s; y *= s; z *= s; }
#ifdef COORD3D_INLINE_ASSIGN
    Coord3D &operator=(const Coord3D &o) { x = o.x; y = o.y; z = o.z; return *this; }
#endif
    void scaleInlined(float s) { x *= s; y *= s; z *= s; }
    void add(Coord3D a) { x += a.x; y += a.y; z += a.z; }
    Coord3D &operator-=(const Coord3D &o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Coord3D &operator+=(const Coord3D &o) { x += o.x; y += o.y; z += o.z; return *this; }
    Coord3D &operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    float lengthSqr() const { return x * x + y * y + z * z; }
    bool equals(const struct Coord3DBase &that) const;
    float GetLengthEstimate() const;
};

#endif // CANONICAL_COORD3D_H
