// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?insertPoint@AreaPolygonBase@@QAEXHABUBfmeE8@@@Z
// WorldBuilder 0x00BF5AA0 identifies AreaPolygonBase::insertPoint in
// AreaPolygon.cpp (line 109). Retail 0x0030BAD8..0x0030BAF8 is its
// assertion-free body: insert at begin()+index, then invalidate the bounds.
// The vector at +0 and dirty flag at +24 agree with the rowed parse/delete
// siblings. BfmeE8 preserves the existing provisional two-float point view;
// its original type name is not established by this recovery.
// Keep the established address-derived linker name used by the vtable caller.
// WorldBuilder establishes the original method identity independently above.
// The original STLport algorithm header preserves the out-of-line
// four-argument copy wrapper called at retail 0x0030BA58. The local
// bfmealloc algorithm shim force-inlines it and adds a fifth argument.
// Keep the allocator shim for allocation; select only this original header.
#include "../../../../vendor/stlport/stl/_algobase.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct BfmeE8 {
    float x, y;
    BfmeE8() {}
    BfmeE8(const BfmeE8& value): x(value.x), y(value.y) {}
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<BfmeE8,allocator<BfmeE8> >::vector(vector<BfmeE8,allocator<BfmeE8> > const &); }
// Retail's growth path is the no-EH provider 0x00057C80; spell its
// algorithm out so this TU's copy is that provider instead of an EH copy.
namespace _STL {
template<> inline void vector<BfmeE8>::_M_insert_overflow(
    pointer position, const BfmeE8 &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}

// Retail 0x0030B9F3..0x0030BA8C is the STLport insertion provider called
// below: the explicit float copy constructor reproduces its movss temporary
// copies. Pointer stride and the point caller establish the eight-byte ABI;
// the original point type name remains unknown.

// Retail 0x0030B8E4..0x0030B92C copies the same 0x0C..0x1C block and the
// two floats at 0x1C/0x20 under the same dirty-flag gate as the rowed
// operator= at 0x0030B92C; the bounds block's member names are unknown.
struct AreaPolygonBounds { int v[4]; };

struct AreaPolygonBase {
    _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
    AreaPolygonBounds m_bounds;
    float m_1c;
    float m_20;
    bool m_dirty;
    AreaPolygonBase(const AreaPolygonBase& that);
    void insertPoint(int index, const BfmeE8& point);
};

// ??0AreaPolygonBase@@QAE@ABU0@@Z @0x0030B8E4 72B: copy the point vector
// through the rowed BfmeE8 vector copy constructor 0x004334D7, clear the two
// floats, then copy the cached bounds only when the source is not dirty.
AreaPolygonBase::AreaPolygonBase(const AreaPolygonBase& that)
    : m_points(that.m_points)
{
    m_1c = 0.0f;
    m_20 = 0.0f;
    m_dirty = that.m_dirty;
    if (!that.m_dirty) {
        m_bounds = that.m_bounds;
        m_1c = that.m_1c;
        m_20 = that.m_20;
    }
}

void AreaPolygonBase::insertPoint(int index, const BfmeE8& point)
{
    m_points.insert(m_points.begin() + index, point);
    m_dirty = true;
}
