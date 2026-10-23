// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<7> DefaultModuleTag7Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag7Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag7Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag7Tag> &
ConcreteModuleClass<DefaultModuleTag7Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag7Tag> instance;
	return instance;
}

}
