// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<3> DefaultModuleTag3Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag3Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag3Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag3Tag> &
ConcreteModuleClass<DefaultModuleTag3Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag3Tag> instance;
	return instance;
}

}
