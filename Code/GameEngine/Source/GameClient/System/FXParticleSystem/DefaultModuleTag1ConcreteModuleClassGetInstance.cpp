// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<1> DefaultModuleTag1Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag1Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag1Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag1Tag> &
ConcreteModuleClass<DefaultModuleTag1Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag1Tag> instance;
	return instance;
}

}
