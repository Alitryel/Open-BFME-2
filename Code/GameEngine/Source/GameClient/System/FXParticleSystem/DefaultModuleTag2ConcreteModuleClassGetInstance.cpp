// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<2> DefaultModuleTag2Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag2Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag2Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag2Tag> &
ConcreteModuleClass<DefaultModuleTag2Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag2Tag> instance;
	return instance;
}

}
