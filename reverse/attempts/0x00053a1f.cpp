// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// partial score=0.9836486192650575 date=2026-10-15
// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /ICode/Libraries/Include
// Native53A1F..53AFA RET4; WB7A3EE0 positional attenuation helper.
// These are non-owning access views of measured fields in MilesAudioManager.cpp;
// the complete engine-class layouts and original method name remain unasserted.
#include "Lib/Coord3D.h"
struct BfmeEventPositionView : public Coord3D {};
struct BfmeAudioEventPrefix136 { BfmeEventPositionView rva002DA1CC(bool &valid); };
struct AudioSettings { char pad00[0x70]; int m_at70, m_at74; };
class AudioEventInfo {
public:
    char pad00[0x48]; unsigned m_type;
    char pad4c[0x94-0x4c]; float m_maxDistance, m_minDistance;
};
class AudioEventRTS {
public:
    const AudioEventInfo *getAudioEventInfo() const { return m_info; }
private:
    char pad00[8]; const AudioEventInfo *m_info;
};
class MilesAudioManager {
public:
    float rva00053A1F(AudioEventRTS *event);
private:
    char pad00[0x10]; AudioSettings *m_audioSettings; int at14;
    Coord3D m_micPos;
};
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
float MilesAudioManager::rva00053A1F(AudioEventRTS *event)
{
    bool valid;
    BfmeEventPositionView pos = reinterpret_cast<BfmeAudioEventPrefix136 *>(event)->rva002DA1CC(valid);
    if (valid) {
        const AudioEventInfo *info = event->getAudioEventInfo();
        _ReadWriteBarrier();
        Coord3D delta;
        float dx = m_micPos.x - pos.x;
        float dy = m_micPos.y - pos.y;
        float dz = m_micPos.z - pos.z;
        _ReadWriteBarrier();
        delta.x = dx; delta.y = dy; delta.z = dz;
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
