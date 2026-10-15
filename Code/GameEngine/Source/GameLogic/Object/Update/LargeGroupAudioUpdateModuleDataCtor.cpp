// cl: /G7 /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata
#include "Common/Snapshot.h"
extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern float g_parseDurationMsecScale;
// Keep a real four-byte readonly multiplier. The textual volatile read prevents
// promotion to an eight-byte folded literal while the product narrows to float.
static const float LargeGroupAudioDurationMsec = 500.0f;
struct Rva001408C0Target;
struct Rva00E03CE0 { void Rva004ABEAE(Rva001408C0Target *); };
extern Rva00E03CE0 g_00E03CE0;
// Native +0x08 is the 12-byte key-map holder. Reuse its already rowed
// destructor/19-byte folded constructor spelling, not the unrelated OCL type.
class Rva003ED94FDtor {
public:
    Rva003ED94FDtor();
    ~Rva003ED94FDtor();
private:
    void *m_words[2];
    unsigned int m_count;
};
class LargeGroupAudioUpdateModuleData : public Snapshot {
public:
    LargeGroupAudioUpdateModuleData(); virtual ~LargeGroupAudioUpdateModuleData();
protected:
    virtual void loadPostProcess(); virtual void crc(Xfer *); virtual void xfer(Xfer *);
private:
    unsigned int m_04;
    Rva003ED94FDtor m_keys;
    int m_min; int m_variance; unsigned short m_weight;
};
// Native 0x004ABED8..0x004ABF47, 111B. Identity: factory 0x0024F362,
// TimeBetweenUpdates-led parse table 0x00C54868 and vtable 0x00C549F8.
// BFME1 a7c38d3b2 LargeGroupAudioUpdateModuleDataCtorThunk is the semantic
// donor; target measures all field offsets, 500ms multiplier and registration.
LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData() :
    m_keys(),
    m_min((int)ceil((double)(float)((double)g_parseDurationMsecScale *
        (double)*(const volatile float *)&LargeGroupAudioDurationMsec))),
    m_variance(1), m_weight(1)
{
    g_00E03CE0.Rva004ABEAE((Rva001408C0Target *)this);
}
