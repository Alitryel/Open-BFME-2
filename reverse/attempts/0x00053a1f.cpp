// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// partial score=0.9 date=2026-10-16
// cl: /O1 /G7 /arch:SSE /EHsc /MD /ICode/Libraries/Include
#include "Lib/Coord3D.h"
struct BfmeEventPositionView : public Coord3D {};
struct BfmeAudioEventPrefix136 { BfmeEventPositionView rva002DA1CC(bool &valid); };
struct AudioSettings { char pad00[0x70]; int m_at70, m_at74; };
class AudioEventInfo {
public:
    char pad00[0x48]; unsigned m_type;
    char pad4c[0x94-0x4c]; float m_maxDistance, m_minDistance;
    bool isGlobal() const { return (m_type & 8) != 0; }
};
class AudioEventRTS {
public:
    const AudioEventInfo *getAudioEventInfo() const { return m_info; }
private:
    char pad00[8]; const AudioEventInfo *m_info;
};
struct DeltaView { float x, y, z; __forceinline void set(float ax, float ay, float az) { x = ax; y = ay; z = az; } float length() const { return ((const Coord3D *)this)->length(); } };
__forceinline void sub(Coord3D &d, const Coord3D *p) { d.x -= p->x; d.y -= p->y; d.z -= p->z; }
class MilesAudioManager {
public:
    float rva00053A1F(AudioEventRTS *event);
private:
    char pad00[0x10]; AudioSettings *m_audioSettings; int at14;
    Coord3D m_micPos;
};
float MilesAudioManager::rva00053A1F(AudioEventRTS *event)
{
    bool valid;
    BfmeEventPositionView pos = reinterpret_cast<BfmeAudioEventPrefix136 *>(event)->rva002DA1CC(valid);
    if (valid) {
        const AudioEventInfo *info = event->getAudioEventInfo();
        DeltaView delta;
        delta.set(m_micPos.x - pos.x, m_micPos.y - pos.y, m_micPos.z - pos.z);
        float nearDistance, farDistance;
        if (info->m_type & 8) {
            nearDistance = (float)m_audioSettings->m_at70;
            farDistance = (float)m_audioSettings->m_at74;
        } else {
            nearDistance = info->m_maxDistance;
            farDistance = info->m_minDistance;
        }
        float length = delta.length();
        if (!(length >= farDistance)) {
            if (length > nearDistance && farDistance > nearDistance)
                return (farDistance - length) / (farDistance - nearDistance);
            return 1.0f;
        }
    }
    return 0.0f;
}
