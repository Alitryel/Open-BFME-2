// cl: /EHs-c-

// The singleton calls the rowed private constructor and registers its destructor.

namespace FXParticleSystem
{

template <int N> class DefaultModuleTag
{
};

template <class Tag>
class ConcreteModuleClass;

typedef DefaultModuleTag<6> DefaultModuleTag6Tag;

template <>
class ConcreteModuleClass<DefaultModuleTag6Tag>
{
private:
	ConcreteModuleClass();

public:

	~ConcreteModuleClass();
	static const ConcreteModuleClass<DefaultModuleTag6Tag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<DefaultModuleTag6Tag> &
ConcreteModuleClass<DefaultModuleTag6Tag>::getInstance()
{
	static ConcreteModuleClass<DefaultModuleTag6Tag> instance;
	return instance;
}

}
