// ?GetAssetList@GenericObjectCreationNugget@@UBEXAAVAssetList@@PAX@Z
// partial score=0.99 date=2026-10-19
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// 0x001F131F bank 2026-10-19 (claude-opus-5-5): hack-free 407/407, nd 4 (same wall as before) with cleaner
// source: the real callee ThingTemplate::GetAssetList 0x33CF34, assets << (prefix + it->m_x) through an
// inline operator+ building AsciiStringPlusString in place. WB twin 0xB044D0 builds a struct r and copies
// it (load both, store both); that form gives retail's register shape but 417 B because cl keeps
// &it->m_flying in EBX across isEmpty and spills the loop pointer. Lead: compile in the real unit with
// STLport vector<AnimSet> iterators and the real AnimSet (ObjectCreationList.cpp, BFME2 layout:
// names +4, putInContainer +0x10, anim vector +0x14, FX +0x20, particle +0x24). Scratch: build/nbr/r5/1f131f/.
#include "ascii_string.h"

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &s);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int assets, int context);
};

class ThingTemplate
{
public:
	void GetAssetList(int assets, int context);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &s);
};
extern ThingFactory *TheThingFactory;

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &s) const;
};
extern ParticleSystemManager *TheParticleSystemManager;

struct AsciiStringPlusString
{
	AsciiStringPlusString(const AsciiString &a, const AsciiString &b) : m_a(a), m_b(b) {}
	operator AsciiString();
	const AsciiString &m_a;
	const AsciiString &m_b;
};
inline AsciiStringPlusString operator+(const AsciiString &a, const AsciiString &b) { return AsciiStringPlusString(a, b); }


class GenericObjectCreationNugget
{
public:
	virtual ~GenericObjectCreationNugget();
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void GetAssetList(AssetList &assets, void *context) const;
private:
	AsciiString *m_namesBegin;
	AsciiString *m_namesEnd;
	AsciiString *m_namesCap;
	AsciiString m_putInContainer;
	struct AnimSet
	{
		AsciiString m_initial;
		AsciiString m_flying;
		AsciiString m_final;
	};
	AnimSet *m_animBegin;
	AnimSet *m_animEnd;
	AnimSet *m_animCap;
	Rva001E11F8 *m_fxFinal;
	AsciiString m_particleSysName;
};

void GenericObjectCreationNugget::GetAssetList(AssetList &assets, void *context) const
{
	if (m_fxFinal)
		m_fxFinal->rva001E11F8((int)&assets, (int)context);
	if (!((const StringBase<char> &)m_putInContainer).isEmpty()) {
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_putInContainer);
		if (tmpl)
			const_cast<ThingTemplate *>(tmpl)->GetAssetList((int)&assets, (int)context);
	}
	for (const AsciiString *name = m_namesBegin; name != m_namesEnd; ++name) {
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(*name);
		if (tmpl)
			const_cast<ThingTemplate *>(tmpl)->GetAssetList((int)&assets, (int)context);
	}
	if (!((const StringBase<char> &)m_particleSysName).isEmpty())
		TheParticleSystemManager->findTemplate(m_particleSysName);
	for (const AnimSet *it = m_animBegin; it != m_animEnd; ++it) {
		AsciiString prefix("a*");
		if (!((const StringBase<char> &)it->m_initial).isEmpty())
			assets << (prefix + it->m_initial);
		if (!((const StringBase<char> &)it->m_flying).isEmpty())
			assets << (prefix + it->m_flying);
		if (!((const StringBase<char> &)it->m_final).isEmpty())
			assets << (prefix + it->m_final);
	}
}
