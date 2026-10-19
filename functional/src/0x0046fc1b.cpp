// ?rva0046FC1B@Rva0046FC1B@@QAEHXZ
// partial score=0.246 date=2026-10-17
// ?rva0046FC1B@Rva0046FC1B@@QAEHXZ
// Native 0x0046FC1B..0x0046FE99 (638B), RET4.
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Lib/Coord3D.h"
#include <map>

namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// Forward declarations of the classes whose data members are referenced by
// this function's retail accesses.
class WeaponTemplateSetHead;
class Pathfinder;
class Object;
class AIUpdateInterface;
class ModuleData;
class Rva0046E7C2;
class Rva0046D738;
class Rva0046AA85;
class Rva0046247D;
class Rva0046E740;
class Rva0046AB7D;

namespace _STL {
template <class T> class vector;
}

// The receiver. Retail accesses touch members at these offsets relative to ECX:
//   [-0xc]  -> producer container pointer
//   [-0x8]  -> owner Object*
//   [+0x110]..[+0x111]  -> condition/latch bytes
//   [+0x114] -> embedded WeaponTemplateSetHead (0x4c bytes = 0x13 dwords)
//   [+0x190] -> sub-object (Rva0046AB7D::rva0046AB7D called on it)
//   [+0x194] -> pointer/int member
//   [+0x19c] -> int member
//   [+0x1a0] -> map header
//   [+0x23c] -> map tree
//   [+0x290] -> int member
//   [+0x294] -> byte flag
//   [+0x2a0] -> int member
//   [+0x2bc] -> vector<ModuleData const*> begin
//   [+0x2c0] -> vector<ModuleData const*> end
//   [+0x2c8] -> vector cursor (int)
class HordeContain;

// Helper: per-instance push_back of a ModuleData pointer into the vector at
// [+0x2bc]. Defined by the game; only the ABI matters here.
struct ModuleData;

class Rva0046FC1B {
public:
    int rva0046FC1B();
};

int Rva0046FC1B::rva0046FC1B()
{
    char *self = (char *)this;
    int n = *(int *)(*(char **)(self - 0xc) + 0x260);
    if (n <= 0)
        return 0;
    int *base;
    int *end;
    {
        char *v = self + 0x2bc;
        end = *(int **)(1 ? v + 4 : v + 4);
        base = *(int **)(1 ? v : v);
    }
    if ((unsigned)(end - base) < (unsigned)n) {
        char *owner = *(char **)(self - 8);
        float f = *(float *)(owner + 0x44);
        float tmp = f;
        {
            extern void __stdcall Rva0046PushTmp(float *p);
            float *p = &tmp;
            tmp = f;
            Rva0046PushTmp(p);
        }
        int *cur = *(int **)(self + 0x2c8);
        (void)(*cur);
        return 0;
    }
    int *cur = *(int **)(self + 0x2c8);
    int i = *(volatile int*)cur;
    *(volatile int*)cur = i + 1;
    char *owner = *(char **)(self - 8);
    double fd = *(float *)(owner + 0x44);
    base[i] = (float)fd;
    if (*cur >= n)
        *cur = 0;
    if ((1 ? *(unsigned char *)(self + 0x294) : *(unsigned char *)(self + 0x294)) == 1) {
        extern int __fastcall Rva0046247D_Helper(char *ec);
        char *ec = self - 0x10;
        int hr = Rva0046247D_Helper((1 ? ec : ec));
        (void)hr;
        extern int g_ObscureCounter;
        int v = g_ObscureCounter;
        return v + v;
    }
    {
        char *own2 = *(char **)(self - 8);
        WeaponTemplateSetHead *dst = (WeaponTemplateSetHead*)(self + 0x114);
        char tmpHead[0x4c + 0x10];
        if (0) throw 1;
        extern unsigned char Rva0046EHState;
        extern int __stdcall Rva0046E7C2_Helper2(char *out, char *ec);
        extern int __stdcall Rva0046D738_Helper2(WeaponTemplateSetHead *d, char *s);
        char *ec2 = own2 + 0x10c;
        *(volatile unsigned char*)(tmpHead + 0x5b) = 0;
        int hr2 = Rva0046E7C2_Helper2(tmpHead, (1 ? ec2 : ec2));
        (void)hr2;
        *(volatile unsigned char*)(tmpHead + 0x5b) = 1;
        if (Rva0046D738_Helper2((1 ? dst : dst), tmpHead)) {
            for (int k = 0; k < 0x13; k++)
                ((int*)dst)[k] = ((int*)tmpHead)[k];
        }
        extern int __fastcall Rva0046AB7D_Helper(char *s);
        Rva0046AB7D_Helper((1 ? self + 0x190 : self + 0x190));
    }
    char *own2 = *(char **)(self - 8);
    int v258 = *(int *)(own2 + 0x258);
    if (v258 == 0)
        return 0;
    if (*(int *)(self + 0x290) == 0)
        return 0;
    char *mp = self + 0x1a0;
    if (*(char **)(mp + 0x8) == *(char **)(mp + 0x4))
        return 0;
    *(unsigned char *)(self + 0x110) = 1;
    return 0;
}
