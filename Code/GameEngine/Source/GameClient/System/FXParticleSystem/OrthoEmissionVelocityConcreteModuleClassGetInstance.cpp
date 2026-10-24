// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

struct OrthoEmissionVelocityModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef OrthoEmissionVelocityModuleTag OrthoEmissionVelocityTag;

template <>
class ConcreteModuleClass<OrthoEmissionVelocityTag>
{
private:
	ConcreteModuleClass();

public:
	~ConcreteModuleClass();
	static const ConcreteModuleClass<OrthoEmissionVelocityTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<OrthoEmissionVelocityTag> &
ConcreteModuleClass<OrthoEmissionVelocityTag>::getInstance()
{
	static ConcreteModuleClass<OrthoEmissionVelocityTag> instance;
	return instance;
}

}
