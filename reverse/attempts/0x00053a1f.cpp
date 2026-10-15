// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// partial score=0.95 date=2026-10-15
// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z 0x53A1F 219B: lines added to Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// (AudioSettings +0x70 int before m_at74, class decl after Rva0005160FGet, then the tail below).
// Size-exact 219B; only diff: retail hoists mov eax,[edi+8]/test [eax+0x48],8 above an all-loads-then-subss delta block.
#if 0
    char at6C[0x70 - 0x6C];
    int m_at70;                          // +0x70, near distance of global sounds (0x53A1F)
    float rva00053A1F(AudioEventRTS *event);

// Native owner position query (0x002DA1CC, rowed under the event prefix name).
class BfmeAudioEventPrefix136 { public: BfmeEventPositionView rva002DA1CC(bool &valid); };

// WorldBuilder twin 0x007A3EE0 copies the listener (+0x18) and subtracts the
// event position through a Coord3D member before reading the info.
static inline void rva00053A1FSet(Coord3D &a, float x, float y, float z)
{
    a.x = x;
    a.y = y;
    a.z = z;
}

// Retail 0x00053A1F (address-derived): linear distance falloff of an event
// from the Miles listener (+0x18): 0 when it has no position or lies at or past
// the far distance, 1 inside the near distance, else the linear ramp. Global
// infos (type bit 3) use the settings' +0x70/+0x74 distances.
float MilesAudioManager::rva00053A1F(AudioEventRTS *event)
{
    bool valid;
    BfmeEventPositionView pos = reinterpret_cast<BfmeAudioEventPrefix136 *>(event)->rva002DA1CC(valid);
    if (valid) {
        Coord3D delta;
        rva00053A1FSet(delta, m_micPos.x - pos.x, m_micPos.y - pos.y, m_micPos.z - pos.z);
        const AudioEventInfo *info = event->getAudioEventInfo();
        float nearDistance;
        float farDistance;
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
#endif
