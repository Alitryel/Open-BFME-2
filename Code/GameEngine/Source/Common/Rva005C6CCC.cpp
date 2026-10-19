// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

#include <math.h>
#include <mmsystem.h>
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()

struct TargetRef00217D4C {
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::pair<const int, TreeHintRef00217D4C> TreeHintPair;
typedef _STL::map<int, TreeHintRef00217D4C> TreeHintMap;

template TreeHintRef00217D4C &TreeHintMap::operator[](const int &);

// Native 0x003596AD is the same signed-key lookup/default-handle pattern.
// Its pair copy 0x00217607 retains the pointee at +4 and its miss-path
// cleanup calls the rowed reference release 0x0007DEEF. The application's
// action type is unresolved; keep this separate address-derived handle view.
struct TreeHintRef003596AD {
 TargetRef00217D4C *m_ptr;
 TreeHintRef003596AD() : m_ptr(0) {}
 TreeHintRef003596AD(const TreeHintRef003596AD &other) : m_ptr(other.m_ptr) {
  if (m_ptr) ++m_ptr->references;
 }
 __forceinline ~TreeHintRef003596AD() {
  if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
 }
};
typedef _STL::map<int, TreeHintRef003596AD> TreeHintMap003596AD;
typedef _STL::map<int, float> TreeHintInsert003596AD;
namespace _STL {
template<> TreeHintInsert003596AD::iterator TreeHintInsert003596AD::insert(TreeHintInsert003596AD::iterator, const TreeHintInsert003596AD::value_type &);
}
// The target's insertion forwarder is independently rowed at 0x0035926E
// with a float spelling. It forwards the iterator and eight-byte pair to
// its tree unchanged; use that proven ABI without making its inferred
// mapped type a target identity or spending another address pin.
template<> TreeHintRef003596AD &TreeHintMap003596AD::operator[](const int &key)
{
 iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  it = iterator(reinterpret_cast<iterator::_Link_type>(
   reinterpret_cast<TreeHintInsert003596AD *>(this)->insert(
    TreeHintInsert003596AD::iterator(reinterpret_cast<TreeHintInsert003596AD::iterator::_Link_type>(it._M_node)),
    reinterpret_cast<const TreeHintInsert003596AD::value_type &>(value_type(key, TreeHintRef003596AD())))._M_node));
 }
 return (*it).second;
}
template class _STL::map<int, TreeHintRef003596AD>;

// Native 0x00218787 has the same signed lookup and counted-handle lifetime
// as newly verified 0x003596AD; all four call targets agree. Earlier banked
// float-map reconstruction lost the temporary destructor and its stack slot.
// The handle layout is now established by the native retain/release pair.
struct TreeHintRef00218787 {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00218787() : m_ptr(0) {}
 TreeHintRef00218787(const TreeHintRef00218787 &other) : m_ptr(other.m_ptr) {
  if (m_ptr) ++m_ptr->references;
 }
 __forceinline ~TreeHintRef00218787() {
  if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
 }
};
typedef _STL::map<int, TreeHintRef00218787> TreeHintMap00218787;
// Reuse the same established insertion ABI as the first specialization.
template<> TreeHintRef00218787 &TreeHintMap00218787::operator[](const int &key)
{
 iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  it = iterator(reinterpret_cast<iterator::_Link_type>(
   reinterpret_cast<TreeHintInsert003596AD *>(this)->insert(
    TreeHintInsert003596AD::iterator(reinterpret_cast<TreeHintInsert003596AD::iterator::_Link_type>(it._M_node)),
    reinterpret_cast<const TreeHintInsert003596AD::value_type &>(value_type(key, TreeHintRef00218787())))._M_node));
 }
 return (*it).second;
}
template class _STL::map<int, TreeHintRef00218787>;

void *__cdecl operator new(unsigned int) throw();
class Display;
extern Display *TheDisplay;
class DisplayView005C6D9C {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual unsigned width(); virtual unsigned height();
};
struct PauseView005C6D9C { char pad[0x5c]; bool paused; };
class Shell;
extern Shell *TheShell;
extern float g_00E065C4;
static const float kFlashMaxScale = 1.1f;
static const float kFlashStart = 0.0f;
static const float kFlashDuration = 0.0f;
struct Rva002BED91 { void set(TargetRef00217D4C *); };
// The existing clear/erase providers use the same native tree prefix.
// Erase reads only the signed integer key prefix; its legacy set name is unproven.
class SubTree005C6B83 { public: void clear(); };
struct Rva0027EA49 { ~Rva0027EA49(); int key; TargetRef00217D4C *pointer; };
inline bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b) { return a.key < b.key; }
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > EraseTree;
class Rva005C663C {
public:
    Rva005C663C();
private:
    char unknown[20];
};
class Rva005C6D4D {
public:
    virtual void v0();
    virtual bool visit(int);
    void rva005C6D9C();
private:
    bool flag;
    char pad[3];
    int count;
    int unknown0c, unknown10;
    int width, height;
    unsigned radius;
    unsigned lastTime, elapsed;
    float scale, angle;
    TreeHintMap tree;
};
void Rva005C6D4D::rva005C6D9C()
{
    if (count <= 0) {
        ((SubTree005C6B83 *)&tree)->clear();
        return;
    }
    unsigned now = timeGetTime();
    if (radius == 0) {
        width = (int)(((DisplayView005C6D9C *)TheDisplay)->width() * (48.0f / 1024.0f));
        height = (int)(((DisplayView005C6D9C *)TheDisplay)->height() * (48.0f / 768.0f));
        if (count > 2) {
            float half = width * 0.5f;
            radius = (unsigned)((half * 1.175f) / sin(3.1415927f / count));
            radius = (unsigned)(((float)radius > width * 2.0f / 3.0f) ? (float)radius : width * 2.0f / 3.0f);
        } else {
            radius = (unsigned)(width * 2.0f / 3.0f);
        }
        angle = 6.2831855f / count;
        lastTime = now;
        elapsed = 0;
    }
    if (!((PauseView005C6D9C *)TheShell)->paused)
        elapsed += now - lastTime;
    lastTime = now;
    if (count > 1) {
        if ((float)elapsed < kFlashStart) {
            if (kFlashStart != 0.0f)
                scale = (float)elapsed * (kFlashMaxScale / kFlashStart);
            else
                scale = 1.0f;
        } else if ((float)elapsed < g_00E065C4) {
            float t;
            if (kFlashStart != 0.0f)
                t = ((float)elapsed - kFlashStart) / kFlashDuration;
            else
                t = 1.0f;
            scale = (1.0f - t) * (kFlashMaxScale - 1.0f) + 1.0f;
        } else {
            scale = 1.0f;
        }
    } else {
        if (kFlashStart != 0.0f) {
            float s = (float)elapsed * (kFlashMaxScale / kFlashStart);
            scale = s > 1.0f ? 1.0f : s;
        } else {
            scale = 1.0f;
        }
    }
    for (int i = 0; i < count; ++i) {
        if (visit(i)) {
            if (((_STL::map<int,int> *)&tree)->find(i) == ((_STL::map<int,int> *)&tree)->end()) {
                Rva005C663C *p = new Rva005C663C;
                ((Rva002BED91 *)&tree[i])->set((TargetRef00217D4C *)p);
                flag = true;
            }
        } else {
            ((EraseTree *)&tree)->erase((const Rva0027EA49 &)i);
        }
    }
}
