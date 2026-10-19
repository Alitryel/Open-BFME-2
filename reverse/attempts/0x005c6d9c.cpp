// ?rva005C6D9C@Rva005C6D4D@@QAEXXZ
// partial score=0.9622641509433962 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva005C6D9C@Rva005C6D9C@@QAEHH@Z
// partial score=0.283 date=2026-10-17
// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B14: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// beyond the thunk-proven secondary bases noted where they are declared
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0059E736  0x0059E5AE  0x00C71094#0
//   0x0059EAA3  0x0059EA42  0x00C71138#0
//   0x005A0B62  0x005A0009  0x00C71414#0
//   0x005AE38A  0x005AE30A  0x00C726A0#0
//   0x005AE76E  0x005AE66B  0x00C72760#0
//   0x005B1A50  0x005B190D  0x00C72A80#0
//   0x005B4541  0x005B3D94  0x00C72F3C#0
//   0x005B576B  0x005B5420  0x00C73450#0
//   0x005B6166  0x005B5CF4  0x00C735C0#0
//   0x005BA272  0x005BA23A  0x00C73D34#0
//   0x005BA303  0x005BA2CB  0x00C73DCC#0
//   0x005BA92E  0x005BA593  0x00C73E24#0
//   0x005C4336  0x005C4230  0x00C744E8#0
//   0x005C43E7  0x005C47A3  0x00C63398#0, 0x00C745A0#0, 0x00C74698#0, 0x00C7475C#0
//   0x005C49B8  0x005C48E5  0x00C7477C#0
//   0x005C4A75  0x005C4A91  0x00C747A8#0
//   0x005C6D80  0x005C6C7B  0x00C74918#0
//   0x005C9753  0x005C9659  0x00C74B70#0
//   0x005CC44C  0x005CC37C  0x00C74E38#0
//   0x005CC63A  0x005CC656  0x00C74E70#0
// Sub-objects whose members this routine touches.
// Minimal stand-ins for the STL map / rb-tree nodes used by the disassembly.
// The object modelled by this translation unit: only the members the
// disassembly reads/writes are declared, at their retail offsets.
// +0x00  vptr
// +0x04
// +0x05
// +0x08
// +0x0C
// +0x14
// +0x18
// +0x1c
// +0x20
// +0x24
// +0x28
// +0x2c
// +0x30
// 0x00DFE9D8
// 0x00E01E48
// 0x022644BC
// 0x022644C0
// 0x022644C8
// Native 005C6D9C..005C6F9D: no-argument thiscall with 20-byte flash allocation.
// The retained comments above describe the earlier bank's scaffolding.
// stlport
#include <math.h>
#include <mmsystem.h>
#include <map>

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
struct TargetRef00217D4C;
struct Rva002BED91 { void set(TargetRef00217D4C *); };
struct TreeHintRef00217D4C { TargetRef00217D4C *m_ptr; };
typedef _STL::map<int, TreeHintRef00217D4C> TreeHintMap;
namespace _STL { template<> TreeHintRef00217D4C &TreeHintMap::operator[](const int &); }
// The existing clear/erase providers use the same native tree prefix.
// Erase reads only the signed integer key prefix; its legacy set name is unproven.
class SubTree005C6B83 { public: void clear(); };
struct Rva0027EA49 { int key; TargetRef00217D4C *pointer; };
bool operator<(const Rva0027EA49 &, const Rva0027EA49 &);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > EraseTree;
namespace _STL { template<> unsigned int EraseTree::erase(const Rva0027EA49 &); }
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
    // Retail retains these comparisons after folding the animation scale to 1.
    if (count > 1) {
        if ((float)elapsed < 0.0f) {
            scale = 1.0f;
        } else if ((float)elapsed <= g_00E065C4) {
            scale = 1.0f;
        } else {
            scale = 1.0f;
        }
    } else {
        scale = 1.0f;
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
