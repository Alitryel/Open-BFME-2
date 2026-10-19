// cl: /MD /EHsc /DNDEBUG
// Split from Snow.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour/BFME1 Snow.cpp donor, adapted to target layout and initialization.
// Donor field names are retained through visibility; later fields are offset views.
// Unidentified virtual slots retain neutral names in this target ABI view.
class SubsystemInterface {
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    // Target vtables place loadIniFilesFromLegend at slot 2 (0x001B5384).
    // The existing SubsystemInterface provider implements this bool method.
    virtual bool loadIniFilesFromLegend();
private:
    unsigned int m_targetBaseWords[2]; // Offset evidence: SnowManager begins at +0x0C.
};

// Two adjacent floats that retail copies with one override lookup.
struct SnowFloatPair {
    float a;
    float b;
};

class SnowManager : public SubsystemInterface {
public:
    SnowManager();
    virtual ~SnowManager();
    virtual void init();
    virtual void targetSlot3();
    virtual void targetSlot4();
    virtual void targetSlot5();
    virtual void targetSlot6();
    virtual void targetSlot7();
    virtual void targetSlot8();
    virtual void reset();
    virtual void targetSlot10() = 0;
    virtual void targetSlot11();
    virtual void targetSlot12();
    virtual void targetSlot13();
    virtual void updateIniSettings();
    virtual void targetSlot15();
    virtual void targetSlot16();
    virtual void targetSlot17();
    virtual void targetSlot18();
    virtual void targetSlot19();
    virtual void targetSlot20();
    virtual void targetSlot21();
    virtual class WeatherSetting *rva00201153();	// slot 22 (+0x58)
    virtual void rva00201085();	// slot 23 (+0x5C), right after init
private:
    float *m_startingHeights;
    float m_time;
    float m_velocity;
    float m_fullTimePeriod;
    float m_frequencyScaleX;
    float m_frequencyScaleY;
    float m_amplitude;
    float m_pointSize;
    float m_maxPointSize;
    float m_minPointSize;
    float m_quadSize;
    float m_boxDimensions;
    float m_emitterSpacing;
    bool m_isVisible;
    // Target-only state below +0x40 keeps offset-derived names until independently identified.
    unsigned char m_targetFlag41;
    unsigned char m_targetPad42[2];
    unsigned int m_targetDword44;
    SnowFloatPair m_targetPair48;
    unsigned char m_targetFlag50;
    unsigned int m_targetDword54;
    unsigned int m_targetDword58;
    float m_targetFloat5C;
    float m_targetFloat60;
    float m_targetFloat64;
    float m_targetFloat68;
    float m_targetFloat6C;
    float m_targetFloat70;
};

typedef char SnowManagerSizeCheck[sizeof(SnowManager) == 0x74 ? 1 : -1];

extern SnowManager *TheSnowManager;

SnowManager::SnowManager()
    : SubsystemInterface(),
      m_startingHeights(0), m_time(0.0f), m_velocity(1.0f),
      m_fullTimePeriod(0.0f), m_frequencyScaleX(0.0f),
      m_frequencyScaleY(0.0f), m_amplitude(0.0f), m_pointSize(0.0f),
      m_maxPointSize(0.0f), m_minPointSize(0.0f), m_quadSize(0.0f),
      m_boxDimensions(0.0f), m_emitterSpacing(0.0f), m_isVisible(1),
      m_targetFlag41(0), m_targetDword44(0),
      m_targetFlag50(0), m_targetDword54(0),
      m_targetDword58(0)
{
    m_targetFloat5C = 0.0f;
    m_targetFloat60 = 0.0f;
    m_targetFloat64 = 0.0f;
    m_targetFloat68 = 0.0f;
    m_targetFloat6C = 0.0f;
    m_targetFloat70 = 0.0f;
    m_targetPair48.a = 0.0f;
    m_targetPair48.b = 0.0f;
}

extern void * __cdecl operator new[](unsigned int);


class MemoryPoolObject {
public:
    virtual ~MemoryPoolObject();
};

class Overridable : public MemoryPoolObject {
public:
    Overridable *m_nextOverride;
    bool m_isOverride;
    Overridable *deleteOverrides();
    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }
};

// Field offsets read from retail's compiler-generated WeatherSetting
// copy assignment (0x00201412, 0xB4 bytes). +0x1C..+0x44 follow Zero Hour's
// snow fields in order; the rest keep offset names.
class WeatherSetting : public Overridable {
public:
    unsigned int m_target0C;
    unsigned int m_targetBase10[2];
    unsigned int m_snowTexture;
    float m_snowFrequencyScaleX;
    float m_snowFrequencyScaleY;
    float m_snowAmplitude;
    float m_snowPointSize;
    float m_snowMaxPointSize;
    float m_snowMinPointSize;
    float m_snowQuadSize;
    float m_snowBoxDimensions;
    float m_snowBoxDensity;
    float m_snowVelocity;
    bool m_usePointSprites;
    bool m_snowEnabled;
    bool m_target46;
    unsigned int m_target48;
    SnowFloatPair m_target4C;
    bool m_target54;
    float m_target58[3];
    unsigned int m_target64;
    unsigned int m_target68;
    bool m_target6C;
    unsigned int m_target70;
    float m_target74;
    float m_target78;
    float m_target7C;
    float m_target80;
    float m_target84;
    float m_target88;
};

template <class T> class OVERRIDE {
public:
    const T *m_overridable;
    operator const T *() const
    {
        if (!m_overridable) return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
    OVERRIDE &operator=(const T *value)
    {
        m_overridable = value;
        return *this;
    }
    const T *operator->() const
    {
        if (!m_overridable) return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
    const T *getNonOverloadedPointer() const { return m_overridable; }
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;
// Owned here: the weather override readers use; retail .data starts it at 0.
// (TU view and ZH agree the object is one pointer; the ledger's provisional
// 12B span has no +4/+8 reader behind it.)
OVERRIDE<WeatherSetting> TheWeatherSetting;
extern void __cdecl operator delete[](void *);


SnowManager::~SnowManager()
{
    delete [] m_startingHeights;
    m_startingHeights = 0;
    if (TheWeatherSetting) {
        ::delete TheWeatherSetting;
        TheWeatherSetting = static_cast<const WeatherSetting *>(0);
    }
}
#pragma comment(linker, "/alternatename:?targetSlot3@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?targetSlot4@SnowManager@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?targetSlot5@SnowManager@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?targetSlot6@SnowManager@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?targetSlot8@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?targetSlot11@SnowManager@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?targetSlot12@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?targetSlot7@SnowManager@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?targetSlot13@SnowManager@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
