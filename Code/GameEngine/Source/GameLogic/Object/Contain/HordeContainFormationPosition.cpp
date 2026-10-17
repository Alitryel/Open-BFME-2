// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// stlport
// Native472620..4726DD RET12,189B. Existing caller474B51 supplies the
// output Coord3D, Object and one ABI word, and adjusts its receiver by-11C.
// Retain that established symbol; target dereferences the last word as float*.
// Native accesses establish Object key74, owner8/position38, index map17C,
// vector188 with28B records and float output at record14. Original field
// names remain unknown. Same-ECX rotate468E98 has its existing value ABI.
// Copy/assignment semantics follow the bank's BF1 ba7ddda7e8 Vector2 lead;
// target instruction and relocation checks establish this caller's layout.
// Assign rotate's returned point to an existing local, then copy it by value:
// that lifetime reproduces the native ESP-save and cached record index.
// Canonical Coord3D plus field-wise input and output copies preserve
// native SSE values until return. No new pin or alternative callee spelling.
#include <functional>
#include <utility>
// less<int>::operator() and pair<const int,int>'s ctor: this /O1 unit inlines both but,
// imported, emits no copies of its own (the census keeps other units' copies).
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &x, const int &y) const { return x < y; }
template <> __declspec(dllimport) __forceinline pair<const int, int>::pair(const int &a, const int &b) : first(a), second(b) {}
}
#include <map>
#include <vector>
// Keep template bodies visible for nonescape analysis; use existing providers
// for their out-of-line copies. Declaration-only operator[] changes ESP homes.
// These four unchanged STLport accessor bodies must stay inline-only.
namespace _STL {
template <> __declspec(dllimport) __forceinline less<int> _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::key_comp() const {return _M_key_compare;}
template <> __declspec(dllimport) __forceinline _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::iterator _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::end() {return iterator(this->_M_header._M_data);}
template <> __declspec(dllimport) __forceinline less<int> map<int,int>::key_comp() const {return _M_t.key_comp();}
template <> __declspec(dllimport) __forceinline map<int,int>::iterator map<int,int>::end() {return _M_t.end();}
}
extern template class _STL::map<int,int>;
extern template class _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > >;

class Rva00468E98Point
{
public:
    float x, y;
    __forceinline Rva00468E98Point(const Rva00468E98Point &, float);
    Rva00468E98Point() {}
    ~Rva00468E98Point() {}
    Rva00468E98Point(const Rva00468E98Point &other) { x = other.x; y = other.y; }
    Rva00468E98Point &operator=(const Rva00468E98Point &other)
    { x = other.x; y = other.y; return *this; }
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
struct Rva00472620Object
{
    char unknown00[0x74];
    int key;
    int getKey() const { return key; }
};
struct Rva00472620Owner
{
    char unknown00[0x38];
    Coord3D position;
};
struct Rva00472620Offset
{
    int unknown00;
    Rva00468E98Point offset;
    char unknown0C[8];
    float auxiliary;
    int unknown18;
};
class Rva00468E98 {public:Rva00468E98Point rotate(Rva00468E98Point);};
class Rva00472620
{
public:
    Coord3D *rva00472620(Coord3D *output, Object *object, int word);
private:
    char unknown00[8];
    Rva00472620Owner *owner;
    char unknown0C[0x17C - 0x0C];
    std::map<int, int> indexByKey;
    std::vector<Rva00472620Offset> offsets;
};

Coord3D *Rva00472620::rva00472620(Coord3D *output, Object *object, int word)
{
    int index = indexByKey[reinterpret_cast<Rva00472620Object *>(object)->getKey()];
    const Coord3D *base = &owner->position;
    Coord3D result; result.x=base->x; result.y=base->y; result.z=base->z;
    if (index >= 0 && static_cast<unsigned int>(index) < offsets.size())
    {
        Rva00468E98Point storage; storage=reinterpret_cast<Rva00468E98 *>(this)->rotate(offsets[index].offset);
 const Rva00468E98Point rotated = storage;
        result.x = base->x + rotated.x;
        result.y = base->y + rotated.y;
        result.z = base->z;
        *reinterpret_cast<float *>(word) = offsets[index].auxiliary;
    }
    output->x=result.x; output->y=result.y; output->z=result.z; return output;
}
