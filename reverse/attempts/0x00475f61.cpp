// ?rva00475F61@HordeContain@@UAEXXZ
// partial score=0.017 date=2026-10-17
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// STLport 4.5.3 vector<T>::push_back for element types whose push_back sits
// unclaimed in retail: the 55-byte body that copy-constructs at _M_finish
// through an out-of-line _Construct and otherwise calls _M_insert_overflow
// with __false_type.  Element types are code-generation views sized from the
// stride push_back adds to _M_finish (the stlport_pod_vector_bodies.cpp
// convention).  Where retail's _Construct callee is already rowed under a
// plain type name, that name is reused; otherwise the element is named after
// the push_back address and both callees are pinned at the addresses the
// retail REL32s prove.  No element layout beyond its size is claimed.
//
//   push_back   stride  _Construct  _M_insert_overflow  element
//   0x000475F2A   4     0x004740AD  0x00475BE8          Rva00475F2AElement
#include <stl/_algobase.h>
namespace _STL {

// ---------------------------------------------------------------------------
// Minimal views of the types this body walks across.  Only the members the
// disassembly proves are declared, at the exact offsets it uses.
// ---------------------------------------------------------------------------

class Coord3D;
class Object;
class ThingTemplate;
class Team;
class Player;
class Matrix3D;
class AsciiString;
class ObjectID;

// STLport vector<Object*> receiver of the trailing push_back.
template <class T> class vector {
public:
    T* _M_start;
    T* _M_finish;
    T* _M_end_of_storage;
    void push_back(const T&);
};

template <class T> class list {
public:
    struct _Node;
    _Node* _M_node;   // sentinel with ->next / ->prev at +0 / +4
    class iterator {
    public:
        _Node* _M_node;
    };
    void push_back(const T&);
    iterator erase(iterator);
};

// The 4-byte element appended by vector<Rva00475F2AElement>::push_back.
struct Rva00475F2AElement {
    void* p;
};

// Per-rank record: first word is a list<Object*> node chain, second the
// ThingTemplate used by isEquivalentTo.
struct Rva00475F61RankEntry {
    list<Object*>::_Node* first;   // it->first used as {list head at +0}
    ThingTemplate* tmpl;           // [rank->first->[+8]] -> Thing::[+4]
};

// Interaction class at owner-0x11c: the replacement recorder.
class Rva0046E6EAObject;
struct Rva0046E6EACoord;
class Rva0046E6EA {
public:
    bool rva0046E6EA(Rva0046E6EAObject*, const Rva0046E6EACoord*, void*, bool);
};

// Minimal Object/Thing view for the slots the body touches.
class Thing {
public:
    const Coord3D* getUnitDirectionVector2D() const;
    void setPosition(const Coord3D*);
    void setTransformMatrix(const Matrix3D*);
    void bfmeTransferReplacementState(Object*);
};

} // namespace _STL

// ---------------------------------------------------------------------------
// Out-of-line stubs pinned to retail addresses.  Only declarations: these are
// defined in their own translation units.
// ---------------------------------------------------------------------------

class HordeContain {
public:
    virtual void rva00475F61();
};

void HordeContain::rva00475F61()
{
    (1 ? ((void(*)(HordeContain*))((*(void***)this)[0x1e8/4])) : ((void(*)(HordeContain*))((*(void***)this)[0x1e8/4])))(this);
    _STL::Matrix3D* pm = (_STL::Matrix3D*)((char*)this - 0x114);
    char pad[80];
    float dst[12];
    *(volatile char*)&pad[0] = 0;
    dst[0] = *(volatile float*)((char*)pm + 8);
    dst[1] = *(volatile float*)((char*)pm + 12);
    dst[2] = *(volatile float*)((char*)pm + 16);
    dst[3] = *(volatile float*)((char*)pm + 20);
    dst[4] = *(volatile float*)((char*)pm + 24);
    dst[5] = *(volatile float*)((char*)pm + 28);
    dst[6] = *(volatile float*)((char*)pm + 32);
    dst[7] = *(volatile float*)((char*)pm + 36);
    dst[8] = *(volatile float*)((char*)pm + 40);
    dst[9] = *(volatile float*)((char*)pm + 44);
    dst[10] = *(volatile float*)((char*)pm + 48);
    dst[11] = *(volatile float*)((char*)pm + 52);
    _STL::vector<_STL::Rva00475F61RankEntry>* ranks = (_STL::vector<_STL::Rva00475F61RankEntry>*)((char*)this + 0x60);
    unsigned rn = (unsigned)(ranks->_M_finish - ranks->_M_start);
    for (unsigned r = 0; r < rn; ++r) {
        _STL::list<_STL::Object*>::_Node* nd = ranks->_M_start[r].first;
        _STL::ThingTemplate* tt = ranks->_M_start[r].tmpl;
        (void)tt;
        for (_STL::list<_STL::Object*>::_Node* p = nd; p; p = *(_STL::list<_STL::Object*>::_Node**)p) {
            _STL::Object* o = *(_STL::Object**)((char*)p + 8);
            _STL::Thing* th = (_STL::Thing*)o;
            const _STL::Coord3D* d = th->getUnitDirectionVector2D();
            th->setPosition(d);
            th->setTransformMatrix((_STL::Matrix3D*)dst);
            _STL::Rva0046E6EA* rec = (_STL::Rva0046E6EA*)((char*)this - 0x11C);
            rec->rva0046E6EA((_STL::Rva0046E6EAObject*)o, (_STL::Rva0046E6EACoord*)d, (void*)dst, true);
            th->bfmeTransferReplacementState(o);
        }
    }
    _STL::Object** vstart = *(_STL::Object***)((char*)this - 0x118);
    _STL::Object** vfinish = *(_STL::Object***)((char*)this - 0x114);
    unsigned n = (unsigned)(vfinish - vstart);
    for (unsigned i = 0; i < n; ++i) {
        _STL::Object* o = vstart[i];
        _STL::Thing* th = (_STL::Thing*)o;
        const _STL::Coord3D* d = th->getUnitDirectionVector2D();
        th->setPosition(d);
    }
}
