// cl: /O1 /MD /arch:SSE /G7
// APT geometry element copy constructor, native A9851..A987D (44B).
// The rowed guarded construction at A9DF8 calls this constructor; its
// uninitialized-copy consumer A9E1C advances by 24 bytes. The native loop
// has three 8-byte elements and returns its receiver in EAX.
// AptAnimData::createRenderData parses the three points using six %f
// conversions before appending this element. The local point view keeps
// those two float fields; original point and enclosing type names are
// unresolved, so the existing address-derived element identity is retained.
#include <new>

struct AptGeometryCopyPoint
{
    float x;
    float y;
    AptGeometryCopyPoint(const AptGeometryCopyPoint &other)
        : x(other.x), y(other.y) {}
};

class Rva000AB3E2Element
{
public:
    AptGeometryCopyPoint points[3];
};

typedef char AptTriangleExtent[(sizeof(Rva000AB3E2Element) == 24) ? 1 : -1];

// Force emission of the implicit array copy constructor. This helper has no
// claimed retail address; the guarded retail caller remains in its own TU.
// ?AptGeometryTriangleCopyEmissionAnchor absent-from-retail
void *AptGeometryTriangleCopyEmissionAnchor(void *storage,
    const Rva000AB3E2Element &source)
{
    return new (storage) Rva000AB3E2Element(source);
}
// The rowed A9E0A guarded construction calls the two-point sibling at
// A987D..A98A9. Its uninitialized-copy caller advances by 16 bytes, and
// the geometry parser reads four %f coordinates for the line segment.
class Rva000AB419Element
{
public:
    AptGeometryCopyPoint points[2];
};

typedef char AptSegmentExtent[(sizeof(Rva000AB419Element) == 16) ? 1 : -1];

// ?AptGeometrySegmentCopyEmissionAnchor absent-from-retail
void *AptGeometrySegmentCopyEmissionAnchor(void *storage,
    const Rva000AB419Element &source)
{
    return new (storage) Rva000AB419Element(source);
}
