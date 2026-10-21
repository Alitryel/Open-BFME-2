// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <algorithm>

class CreateAHeroData;
struct BfmeE12 { float x, y, z; };
#include "../../../Libraries/Include/Lib/BfmeE16.h"

// begin(), end() and empty() are only ever expanded inline here; their unreferenced
// copies differed from retail's. Declared imported and force-inlined, they are
// not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
bool vector<void *>::empty() const { return this->_M_start == this->_M_finish; }
}

class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
private:
    _STL::vector<void *> m_vec;
    unsigned int m_selected;
};

void Rva002B7250::rva002B7250(CreateAHeroData *createAHeroData)
{
    CreateAHeroData *key = createAHeroData;
    CreateAHeroData **b = (CreateAHeroData **)m_vec.begin();
    CreateAHeroData **e = (CreateAHeroData **)m_vec.end();
    CreateAHeroData **it = _STL::find(b, e, key);
    if (it != e) {
        if (m_selected != (unsigned int)-1) {
            unsigned int idx = (unsigned int)(it - b);
            if (idx < m_selected)
                --m_selected;
        }
        m_vec.erase((void **)it);
        if (m_vec.empty()) {
            _STL::vector<BfmeE16> tmp((_STL::allocator<BfmeE16>()));
            (( _STL::vector<BfmeE12> &)*( _STL::vector<BfmeE12> *)&tmp).swap(( _STL::vector<BfmeE12> &)m_vec);
        }
    }
}
