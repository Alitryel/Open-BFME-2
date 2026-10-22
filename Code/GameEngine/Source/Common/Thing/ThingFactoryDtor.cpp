// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1ThingFactory@@UAE@XZ, retail 0x002D0588 (71 bytes, EH): the destructor
// of the subsystem whose vtable 0x00C0233C its constructor 0x002D0E14 and
// deleting destructor 0x002D09F5 install (opaque pin ??1Rva002D0588). As in
// Zero Hour's ThingFactory::~ThingFactory it frees the template database
// (rowed ThingFactory::freeDatabase 0x002D0469, called on the same object),
// then the template hash map at +0x14 is destroyed (its own EH copy of the
// AsciiString-keyed table destructor at 0x002CFF2D, pinned under an
// address-named member class) and the SubsystemInterface base destructor
// 0x001B4E74 runs.
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva002CFF2D
{
public:
	~Rva002CFF2D();
private:
	char m_data[0x14];
};

// Native normal teardown reaches57B2CFF2D while unwind reaches the
// separate5B forwarder2D0583. This lifetime view models the unadjusted
// receiver; original wrapper type and inheritance identity remain unknown.
class Rva002D0583Member : public Rva002CFF2D
{
public:
	~Rva002D0583Member() {}
};

class ThingFactory : public SubsystemInterface
{
public:
	// Native deleting destructor2D09F5 calls this71B body out of line.
	__declspec(noinline) virtual ~ThingFactory();
private:
	void freeDatabase();
	void *m_firstTemplate;	// +0x0C
	unsigned int m_nextTemplateID;	// +0x10
	Rva002D0583Member m_templateHashMap;	// +0x14
};

ThingFactory::~ThingFactory()
{
	freeDatabase();
}
