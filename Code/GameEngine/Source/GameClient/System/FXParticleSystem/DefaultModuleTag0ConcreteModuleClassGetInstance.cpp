// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<0> DefaultModuleTag0Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag0Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag0Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag0Tag> &
ConcreteModuleClass<DefaultModuleTag0Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag0Tag> instance;
	return instance;
}

}
