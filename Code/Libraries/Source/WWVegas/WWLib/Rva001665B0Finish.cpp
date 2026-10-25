// ?insert@?$vector@UElem36@@V?$allocator@UElem36@@@_STL@@@_STL@@QAEPAUElem36@@PAU3@ABU3@@Z
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$vector@UElem36@@V?$allocator@UElem36@@@_STL@@@_STL@@QAEPAUElem36@@PAU3@ABU3@@Z @0x001665B0 288B:
// STLport vector<Elem36> single insert. Same 0x24 stride stand-in as
// stlport_vector_elem36_push_back.cpp (dword + 16-byte block + three dwords +
// byte); callees rowed/pinned (_Construct 0x001610F0 copy-ctor 0x00161050
// copy_backward 0x001611B0 overflow 0x001663F0); called from 0x00166A1B.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// Same target-decoded record fields as the HTree seed. Let the normal
// copy algorithm instantiate this assignment instead of redeclaring a
// specialization after the seed has already instantiated it.
struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W; BfmeCapturedBoneRotation &operator=(const BfmeCapturedBoneRotation &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation &operator=(const BfmeCapturedBoneTranslation &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct CapturedTransform{BfmeCapturedBoneRotation Rotation;BfmeCapturedBoneTranslation Translation;};

struct Elem36{int Index;CapturedTransform Transform;bool WorldSpace;};

typedef _STL::vector<Elem36, _STL::allocator<Elem36> > Elem36Vector;
// _Construct<Elem36> is the pinned copy construct at 0x001610F0: declare it so this unit calls it
// rather than emitting the only other copy of that name.
namespace _STL { template <> void _Construct<Elem36, Elem36>(Elem36 *__p, const Elem36 &__val); }

template _STL::vector<Elem36>::iterator _STL::vector<Elem36>::insert(Elem36 *, const Elem36 &);