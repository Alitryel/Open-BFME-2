// ?rva0052DD75@PathfindCell@@QAEMMHM@Z
// partial score=0.93256 date=2026-10-14
// ?rva0052DD75@PathfindCell@@QAEMMHM@Z
// cl: /ICode/Libraries/Include /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// Native 0x0052DD75..0x0052DE5B, RET 12; WB 0x012D7220..0x012D77D4.
// PathfindCell receiver is established by the existing pin and three native callers.
// Normalize, scale, and accumulation sequence follows the WB MathCoord2D operations.
// Still partial: accumulator SSE allocation differs; compiled 222 versus native 230 bytes.
#include <math.h>

#include "Lib/Coord2D.h"
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
    acc.x = 0.0f;
    acc.y = 0.0f;
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
