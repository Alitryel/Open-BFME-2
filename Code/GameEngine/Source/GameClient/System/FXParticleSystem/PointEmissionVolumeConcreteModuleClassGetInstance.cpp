// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

struct PointEmissionVolumeModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef PointEmissionVolumeModuleTag PointEmissionVolumeTag;

template <>
class ConcreteModuleClass<PointEmissionVolumeTag>
{
private:
	ConcreteModuleClass();

public:
	~ConcreteModuleClass();
	static const ConcreteModuleClass<PointEmissionVolumeTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<PointEmissionVolumeTag> &
ConcreteModuleClass<PointEmissionVolumeTag>::getInstance()
{
	static ConcreteModuleClass<PointEmissionVolumeTag> instance;
	return instance;
}

}
