// cl: /O1 /G7 /arch:SSE /MD
// ?tossEmitters@W3DTankDraw@@IAEXXZ, retail 0x000CE7B4, 131 bytes (pinned callee of loadPostProcess 0x000CEA39).
// Twin guide: the verified W3DTankTruckDraw tossEmitters (W3DTankTruckDrawTossEmitters.cpp, three handles); the
// W3DTankDraw view has two handles at +0x2E8/+0x2F4 observed in the ctor/createEmitters. Handle teardown is the inline
// null test around the rowed unlink 0x0004CBC0; the volatile m_system keeps retail's redundant null-or-Make chases.
// Structural inference (not target evidence): the first handle test is written as the constant-true equal-arm
// conditional (1 ? E : E); it changes cl's expression tree and puts the frame/register roles on retail's.
class Rva001F384AByteZeroSetter {
public:
    void disable();
};
class Rva001F3852ByteOneSetter {
public:
    void enable();
};
struct Rva001F3C43Arg {
    char m_pad[0x74];
    int m_value;
};
class Rva001F3C43Slot {
public:
    void set(const Rva001F3C43Arg *arg);
};
class ParticleSystem : public Rva001F3C43Slot {
public:
    void destroy();
};
ParticleSystem *Make001FCBD7();
// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle {
    ~BfmeParticleSystemHandle();
    ParticleSystem *volatile m_system;
    void *m_prev;
    void *m_next;
    __forceinline ParticleSystem *getRaw()const{return m_system;} ParticleSystem *get() const {
        ParticleSystem *p = m_system;
        if (!p)
            p = Make001FCBD7();
        return p;
    }
};
class W3DTankDraw {
protected:
    void tossEmitters();
    void createEmitters();
    void enableEmitters(bool enable);
    char m_pad0[0x2e8];
    BfmeParticleSystemHandle m_dust;
    BfmeParticleSystemHandle m_dirt;
};
void W3DTankDraw::tossEmitters()
{
    if ((1 ? (m_dust.getRaw()) : (m_dust.getRaw()))) {
        m_dust.get()->set(0);
        m_dust.get()->destroy();
        if (m_dust.getRaw()) {
            reinterpret_cast<RvaSmartPtr12 *>(&m_dust)->rva0004CBC0();
            m_dust.m_system = 0;
        }
    }
    if (m_dirt.getRaw()) {
        m_dirt.get()->set(0);
        m_dirt.get()->destroy();
        if (m_dirt.getRaw()) {
            reinterpret_cast<RvaSmartPtr12 *>(&m_dirt)->rva0004CBC0();
            m_dirt.m_system = 0;
        }
    }
}
