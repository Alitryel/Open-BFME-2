// cl: /DNDEBUG /MD /EHsc /Ob2

namespace FXParticleSystem
{

class LifeEventModuleInfo
{
public:
    LifeEventModuleInfo(const LifeEventModuleInfo &);
    virtual ~LifeEventModuleInfo();
};

class LifeEventCategoryBaseA
{
public:
    virtual ~LifeEventCategoryBaseA();
};

class LifeEventCategoryBaseB
{
public:
    virtual ~LifeEventCategoryBaseB();
};

class LifeEventCategoryBase
    : public LifeEventCategoryBaseA,
      public LifeEventCategoryBaseB
{
public:
    LifeEventCategoryBase(const LifeEventCategoryBase &) {}
    virtual ~LifeEventCategoryBase();
};

// The category base is retail's CategoryModuleTemplate<8>: its copy
// constructor at 0x00001F30 is rowed in FXParticleSystem.cpp, so it is
// declared, never defined here.
template <int N>
class CategoryModuleTemplate : public LifeEventCategoryBase
{
public:
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ~CategoryModuleTemplate();

private:
    volatile unsigned short m_word;
};

class LifeEventModuleTemplate : public CategoryModuleTemplate<8>,
                                       public LifeEventModuleInfo
{
public:
    LifeEventModuleTemplate(const LifeEventModuleTemplate &that);
    virtual ~LifeEventModuleTemplate();
};

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LifeEventModuleTemplate::LifeEventModuleTemplate(const LifeEventModuleTemplate &that)
    : CategoryModuleTemplate<8>(that),
      LifeEventModuleInfo(that)
{
}

}
