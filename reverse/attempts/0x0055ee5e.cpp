// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.995 date=2026-10-14
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $02 / N=3) default constructor.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };

    GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
    void setRange(float low, float high, DistributionType type);

    DistributionType m_type;
    float m_low, m_high;
};

namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
    ModuleTemplate() {}
    virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    virtual void unusedVirtual();

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplateBase() {}
    __declspec(dllimport) __forceinline virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplate() {}
    virtual ~CategoryModuleTemplate() {}
};

class Snapshot
{
public:
    virtual ~Snapshot() {}
};

class DefaultPhysicsModuleInfo : public Snapshot
{
public:
    DefaultPhysicsModuleInfo();
    virtual ~DefaultPhysicsModuleInfo();

private:
    float m_float04;
    float m_float08;
    float m_float0C;
    float m_float10;
    GameClientRandomVariable m_var14;
    bool m_flag20;
    bool m_flag21;
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>,
    public DefaultPhysicsModuleInfo
{
public:
    DefaultModuleTemplate();
};

// MSVC mangles DefaultModuleTemplate<3> as @$02
// ??0?$DefaultModuleTemplate@$02@FXParticleSystem@@QAE@XZ
template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
    : CategoryModuleTemplate<Category>(), DefaultPhysicsModuleInfo()
{
}

template DefaultModuleTemplate<3>::DefaultModuleTemplate();

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ @0x0055EE5E 109B: the
// retail body has an EH prolog (base with virtual dtor + setRange call), so it
// is compiled here where the TU carries /EHsc; the owner file is /GX-. The
// dtor row 0x49B47C stores the Snapshot vtable 0xBBB554, which is the base.
__declspec(noinline) DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
{
    m_float10 = 0.0f;
    m_float04 = 0.0f;
    m_float08 = 0.0f;
    m_float0C = 0.0f;
    m_var14.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_flag20 = false;
    m_flag21 = false;
}

}
