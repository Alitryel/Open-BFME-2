// cl: /ICode/Libraries/Include /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
//
// PathfindCell::rva0052DD75, retail 0x0052DD75..0x0052DE5B (230 B, RET 0xC): the facing
// angle of a cell's chain of at most n neighbour records, as the sum of the unit
// vectors from the cell's record to each linked record, scaled by a factor that
// is multiplied by c every step, and converted with Coord2D::toAngle. WorldBuilder
// 0x012D7220 (MathCoord2D normalise / scale / accumulate) is the structural guide.
// The zero accumulator is written through volatile stores: retail materialises both
// components before the first record is read, and the plain stores let cl keep one
// XMM register for the pair.
#include <math.h>

#include "Lib/Coord2D.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
inline float facingSqr(float x)
{
    return x * x;
}
class FacingCoord : public Coord2D
{
  public:
    FacingCoord()
    {
    }
    FacingCoord(float a, float b)
    {
        x = a;
        y = b;
    }
    ~FacingCoord()
    {
    }
    __forceinline float GetLength() const
    {
        return (float)sqrt(x * x + facingSqr(y));
    }
    __forceinline void Normalize()
    {
        float len = GetLength();
        float inv = 1.0f / len;
        x *= inv;
        y *= inv;
    }
    __forceinline FacingCoord &operator*=(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }
    __forceinline FacingCoord &operator+=(const FacingCoord &p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }
};

struct Rva0052DD75Inner
{
    int x;
    int y;
};

struct Rva0052DD75Mid
{
    int x;
    int y;
    Rva0052DD75Inner *m_8;
};

class PathfindCell
{
  public:
    float rva0052DD75(float a, int n, float c);
    Rva0052DD75Mid *m_0;
};

float PathfindCell::rva0052DD75(float a, int n, float c)
{
    Rva0052DD75Mid *mid = m_0;
    if (mid == 0)
        return a;
    if (mid->m_8 == 0)
        return a;
    FacingCoord acc;
    __vref(acc.x) = 0.0f;
    __vref(acc.y) = 0.0f;
    float factor = 1.0f;
    while (n > 0)
    {
        Rva0052DD75Inner *inner = m_0->m_8;
        --n;
        if (inner == 0)
            break;
        FacingCoord delta;
        delta.x = (float)(mid->x - inner->x);
        delta.y = (float)(mid->y - inner->y);
        delta.Normalize();
        delta *= factor;
        acc += delta;
        factor *= c;
    }
    return acc.toAngle();
}
