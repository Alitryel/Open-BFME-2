// ?updateFormationPreview@InGameUI@@QAEXXZ
// partial score=0.057 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct Rva002A1B1DChunk { int m_words[3]; };
class Rva002A1B1D { public: void rva002A1B1D(const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4); };
class Rva002A4646BurstRecord { public: void rva002A4646(AsciiString name, unsigned int count); };
struct Coord2D { float x, y; float toAngle() const; };
struct Coord3D { float x,y,z; };
class Thing { public: void setPosition(const Coord3D* p); void setOrientation(float a); };
class Object {};
class Player {};
class Rva0029FB3BMember { public: void* init(void* p); };
class Rva001EB984Member { public: void* init(void* p); void rva001EB769(); };
class PoolMember { public: void Rva00268902(); };
class RGBColor { public: void setFromInt(int v); };
class GameLogic { public: Object* findObjectByID(int id); };
class Formation {};
class FormationAssistant {
public:
 bool getValidSelectedObjectsForPlayer(Player* p, Rva0029FB3BMember* m);
 Formation* rva00424E77(int n, void* h, const Coord3D* c);
};
int Rva004233F5(void* l, float m);
void Rva00423FBDDelete(void* s);
class Rva002A3DD3 {
public:
 virtual void _pad00(); virtual void _pad01(); virtual void _pad02(); virtual void _pad03();
 virtual void _pad04(); virtual void _pad05(); virtual void _pad06(); virtual void _pad07();
 virtual void _pad08(); virtual void _pad09(); virtual void _pad10(); virtual void _pad11();
 virtual void _pad12(); virtual void _pad13(); virtual void _pad14(); virtual void _pad15();
 virtual void _pad16(); virtual void _pad17(); virtual void _pad18(); virtual void _pad19();
 virtual void _pad20(); virtual void _pad21(); virtual void _pad22(); virtual void _pad23();
 virtual void _pad24(); virtual void _pad25(); virtual void _pad26(); virtual void _pad27();
 virtual void _pad28(); virtual void _pad29(); virtual void _pad30(); virtual void _pad31();
 virtual void _pad32(); virtual void _pad33(); virtual void _pad34(); virtual void _pad35();
 virtual void _pad36(); virtual void _pad37(); virtual void _pad38(); virtual void _pad39();
 virtual void _pad40(); virtual void _pad41(); virtual void _pad42(); virtual void _pad43();
 virtual void _pad44(); virtual void _pad45(); virtual void _pad46(); virtual void _pad47();
 virtual void _pad48(); virtual void _pad49(); virtual void _pad50();
 virtual bool rvaCC();
 void rva002A3E24();
 void rva002A3DD3clear();
 void* rva002A3E5A(Thing* t);
};
class Rva0029A469Cls { public: void rva0029A469(float f); };
class InGameUI : public Rva002A3DD3 {
public:
 void updateFormationPreview();
private:
 unsigned char m_pad000[0x8D4];
 Rva002A1B1D m_bursts8D4;
};
class Rva002A3DD3A : public Rva002A3DD3 { public: void clearFormationPreviewDrawables(); };
Coord2D InGameUI_rva0029D9F9(InGameUI* p);

void InGameUI::updateFormationPreview()
{
  *(volatile unsigned*)0x00B75081;
  if ((rvaCC() ? rvaCC() : rvaCC())) {
    int* pA = (int*)((char*)this + 0x5A0);
    int* pB = (int*)((char*)this + 0x5A4);
    int n = (*pB - *pA) / 12;
    FormationAssistant* fa = (FormationAssistant*)*(volatile unsigned*)0x00DFE77C;
    if (n <= 0)
      return;
    int cnt = (*pB - *pA) / 12;
    (void)cnt;
    float fA = *(volatile float*)0x00BBB8D8;
    int iB = *(volatile int*)0x00DBA4E8;
    float fB = (float)(double)iB;
    float fC = *(volatile float*)0x00BC26F0;
    float fdiv = (fA * fB) / fA;
    double ratio = (double)fdiv;
    float spacing = *(float*)0x00BBB8D8;
    {
      volatile float vs = spacing;
      float t = (float)((double)vs * (double)fB + (double)fC);
      volatile float vt = t;
      (void)vt;
    }
    if (spacing != spacing) {
      rva002A3E24();
      return;
    }
    {
      float b0 = (float)(double)*(volatile float*)0x00DBA4E8;
      float c0 = *(volatile float*)0x00BC26F0;
      float d0 = (spacing * b0) + c0;
      volatile float vd0 = d0;
      (void)vd0;
    }
    volatile float vr = (float)ratio;
    (void)vr;
    if (n <= 0)
      return;
    float f = (float)(double)spacing;
    volatile float vf = f;
    (void)vf;
    volatile unsigned *pG = (volatile unsigned*)0x00B75081;
    (void)*pG;
    float saveA = *(volatile float*)0x00BBB8D8;
    float saveB = *(volatile float*)0x00BC26F0;
    int saveC = *(volatile int*)0x00DBA4E8;
    int saveD = *(volatile int*)0x00DFE77C;
    (void)saveA; (void)saveB; (void)saveC; (void)saveD;
    {
      Rva002A1B1DChunk c1 = { 0,0,0 }, c2 = { 0,0,0 }, c3 = { 0,0,0 }, c4 = { 0,0,0 };
      Rva002A3DD3A* self2 = (Rva002A3DD3A*)this;
      self2->clearFormationPreviewDrawables();
      Rva002A4646BurstRecord br;
      br.rva002A4646(AsciiString("Burst"), 4);
      m_bursts8D4.rva002A1B1D(&c1, &c2, &c3, &c4);
    }
    if (0) throw 1;
    {
      Rva001EB984Member e; void* p = e.init(&e);
      (void)p;
      e.rva001EB769();
      if (0) { AsciiString d; }
    }
    {
      PoolMember pm; pm.Rva00268902();
      {
        float a = *(volatile float*)0x00BBB8D8;
        float b = (float)(double)*(volatile float*)0x00DBA4E8;
        float c = *(volatile float*)0x00BC26F0;
        float d = (a * b) + c;
        volatile float vd = d;
        (void)vd;
        Coord2D cc = InGameUI_rva0029D9F9(this);
        float ang = cc.toAngle();
        (void)ang;
      }
      Rva0029A469Cls cl; cl.rva0029A469((float)(double)*(float*)0x00BBB8D8);
      Thing* t = 0; t->setPosition((const Coord3D*)0);
      t->setOrientation(0.0f);
      RGBColor col; col.setFromInt(0);
      GameLogic* gl = 0; Object* o = gl->findObjectByID(0);
      (void)o;
    }
  } else {
    rva002A3DD3clear();
    void* h = rva002A3E5A((Thing*)0);
    Rva00423FBDDelete(h);
    rva002A3E24();
  }
}
