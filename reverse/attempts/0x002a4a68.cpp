// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.995 date=2026-10-18
// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.927 date=2026-10-15
// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.91 date=2026-10-13
// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.8952 date=2026-10-13
// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.8952 date=2026-10-13
// ?rva002A4A68@InGameUI@@QAEXXZ
// partial score=0.8919 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /arch:SSE
// stlport
// ?rva002A4A68@InGameUI@@QAEXXZ @0x002A4A68 404B
// evidence: unlock lane, caller 0x0004A462, callees all rowed, globals TheGameLogic TheGameClient TheWritableGlobalData
#include <list>

template<typename T> class StringBase
{
	friend class InGameUI;
	void validate() const;
};

class InGameUI;

class GameLogic {
public:
    unsigned char isGamePaused();
};
extern GameLogic *TheGameLogic;

class ClientFrameSubsystem {
public:
    virtual int _v00();
    virtual int _v01();
    virtual int _v02();
    virtual int _v03();
    virtual int _v04();
    virtual int _v05();
    virtual int _v06();
    virtual int _v07();
    virtual int _v08();
    virtual int _v09();
    virtual int _v10();
    virtual int _v11();
    virtual int _v12();
    virtual int _v13();
    virtual int _v14();
    virtual int _v15();
    virtual int _v16();
    virtual int _v17();
    virtual int _v18();
    virtual int _v19();
    virtual int _v20();
    virtual int _v21();
    virtual int _v22();
    virtual int _v23();
    virtual int _v24();
    virtual int _v25();
    virtual int _v26();
    virtual int _v27();
    virtual int _v28();
    virtual int _v29();
    virtual int _v30();
    virtual int getFrame();
};
extern ClientFrameSubsystem *TheGameClient;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern unsigned int g_00DFEE08;

class GameClientRandomVariable {
public:
    float getValue() const;
    int _u[3];
};

class GlobalData {
public:
    char _pad0[0xda4];
    GameClientRandomVariable m_rand;
    unsigned char m_db0;
    char _pad1[3];
    int m_db4;
};

class Rva002D7127 {
public:
    virtual void *first(int a);
    void rva002D6F80(float a, float b, int c);
    char _pad0[0x10 - 4];
    unsigned char m_flag10;
    char _pad1[0x1c - 0x10 - 1];
    float m_1c;
    char _pad2[0x2c - 0x1c - 4];
    int m_2c;
    int m_30;
};

struct Payload {
    Rva002D7127 *m_obj;
    float m_4;
    float m_8;
    int m_c;
    unsigned char m_10;
    char _p[3];
    float m_14;
    float m_18;
    float m_1c;
    int m_20;
};

class InGameUI {
public:
    void rva002A4A68();
    char _pad[0x910];
};

template<> __declspec(noinline) void StringBase<unsigned short>::validate() const { (void)*(volatile char *)this; }
// ?rva002A4A68@InGameUI@@QAEXXZ present-unmatched
void InGameUI::rva002A4A68()
{
    ((const StringBase<unsigned short> *)((const char *)this + 0x8d4))->validate();
    _STL::list<int> &lst = *(_STL::list<int> *)((char *)this + 0x8d0);
    _STL::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        Payload *p = (Payload *)*it;
        if (!TheGameLogic->isGamePaused()) {
            unsigned frame = TheGameClient->getFrame();
            if (frame >= (unsigned)p->m_c || ((p->m_10 & 2) && (p->m_obj->m_flag10 & 4))) {
                Rva002D7127 *o = p->m_obj;
                ::operator delete(o ? o->first(0) : 0);
                ::operator delete(p);
                it = (p ? lst.erase(it) : lst.erase(it));
                continue;
            }
        }
        p->m_4 += p->m_14;
        p->m_14 *= p->m_1c;
        p->m_8 += p->m_18;
        p->m_18 *= p->m_1c;
        if (p->m_10 & 1) {
            unsigned remaining = p->m_c - TheGameClient->getFrame();
            if (remaining < g_00DFEE08) {
                p->m_obj->m_1c = (float)remaining / (float)g_00DFEE08;
            }
        }
        int v;
        if (TheWritableGlobalData->m_db0)
            v = (int)(TheWritableGlobalData->m_rand.getValue() + 0.5f);
        else
            v = p->m_20;
        Rva002D7127 *o2 = p->m_obj;
        o2->m_2c = v;
        o2->m_30 = v;
        p->m_obj->rva002D6F80(p->m_4, p->m_8, TheWritableGlobalData->m_db4);
        ++it;
    }
    if (lst.size() == 0) {
        *(int *)((char *)this + 0x908) = -1;
        *(int *)((char *)this + 0x90c) = -1;
    }
}
