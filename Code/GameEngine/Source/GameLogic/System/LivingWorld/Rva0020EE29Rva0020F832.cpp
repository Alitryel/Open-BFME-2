// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0020F832@Rva0020EE29@@QAE_NPAX0@Z retail 0x0020F832..0x0020F91D (235 bytes,
// EH frame, RET 8): the living-world region manager's entry handler. Target
// facts: the entry's rowed 0x003F2A8C takes the state's +0x14 word; the first
// node of the +0x14 pointer vector whose +0x24 entry is the argument notifies
// TheLivingWorldManager (rowed 0x00212655 with the node's +0x30), moves into
// the +0x20 vector (ICF-shared push_back 0x004DFCB0) and is erased (rowed
// 0x001FF51F); then 0x0020F309 and 0x0020ED8E run with ECX=this, the rowed
// SetActiveBattleID(0, 0), and a non-empty copy of the entry's +0x6C script
// string is run through CallActSubroutine (returning false), else true.
// Structural: the two vectors are real STLport vectors (size()/operator[]
// re-derived per use); owner and field names are role-derived. The
// push_back/erase calls name the ICF-shared rows they reach (vector<const
// ModuleData *>::push_back 0x004DFCB0, vector<void *>::erase 0x001FF51F),
// declared only so this unit emits no copy.
#include <vector>
#include "ascii_string.h"

class ModuleData;
namespace _STL {
template <> void vector<const ModuleData *>::push_back(const ModuleData *const &x);
template <> void **vector<void *>::erase(void **pos);
}

class Rva003F2A8C { public: void rva003F2A8C(int value); };
struct Rva0020F832Entry { char pad[0x6c]; AsciiString script; };
struct Rva0020F832State { char pad[0x14]; int value; };
struct Rva0020F832Node { char pad[0x24]; void *entry; char pad28[8]; int key; };
class Rva00DFE1C8Host { public: void rva00212655(int key); };
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
class LivingWorldCampaignManager { public: void CallActSubroutine(const AsciiString &script); };
class LivingWorldRegionManager { public: void SetActiveBattleID(int key, int field3c); };

class Rva0020EE29
{
public:
	bool rva0020F832(void *entry, void *state);
	void rva0020F309(void *entry, int state);
	void rva0020ED8E(void *entry, void *state);
private:
	char m_pad[0x14];
	_STL::vector<Rva0020F832Node *> m_14;
	_STL::vector<Rva0020F832Node *> m_20;
};

bool Rva0020EE29::rva0020F832(void *entry, void *state)
{
	((Rva003F2A8C *)entry)->rva003F2A8C(((Rva0020F832State *)state)->value);
	for (unsigned i = 0; i < m_14.size(); ++i) {
		if (m_14[i]->entry == entry) {
			((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_14[i]->key);
			((_STL::vector<const ModuleData *> *)&m_20)->push_back((const ModuleData *const &)m_14[i]);
			((_STL::vector<void *> *)&m_14)->erase((void **)&m_14[i]);
			break;
		}
	}
	rva0020F309(entry, (int)state);
	rva0020ED8E(entry, state);
	((LivingWorldRegionManager *)this)->SetActiveBattleID(0, 0);
	AsciiString script(((Rva0020F832Entry *)entry)->script);
	if (!script.isEmpty()) {
		((LivingWorldCampaignManager *)TheCampaignManager)->CallActSubroutine(script);
		return false;
	}
	return true;
}
