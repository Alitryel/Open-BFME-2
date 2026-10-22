// cl: /DNDEBUG /MD /EHsc
// ?rva00042036@Rva00042036@@QAEPAVRva000647B5@@XZ @0x00042036 50B: factory news 16B Rva then calls rowed ctor 0x000647B5. Evidence: calls rowed new 0x0002FDA0 and rowed ctor; chain from 0x000647B5; between GameLogic and ModuleFactory name getters.
class BfmeSnapshotBase
{
public:
	virtual void bfmeSlot0(void);
	~BfmeSnapshotBase();
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class GODupBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	GODupBase();
	~GODupBase();
};

// Retail's factory allocates 16 B: the 4 B snapshot base plus the canonical
// 12 B SubsystemInterface. The old 8 B subsystem view needed 4 B padding here.
class Rva000647B5 : public GODupBase
{
public:
	Rva000647B5();
	~Rva000647B5();
};

void *__cdecl operator new(unsigned int size);

class Rva00042036
{
public:
	Rva000647B5 *rva00042036();
};

Rva000647B5 *Rva00042036::rva00042036()
{
	return new Rva000647B5();
}
