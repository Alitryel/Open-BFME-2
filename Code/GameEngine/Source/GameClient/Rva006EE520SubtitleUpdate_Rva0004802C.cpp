// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient -Ireference/shims/bfme2_ascii
// BFME subtitle update body at retail RVA 0x006EE520.
// The address-qualified class keeps the unresolved original method name
// explicit while the manager and sink access views preserve unresolved callee
// identities at their retail addresses.

// stlport
#include <vector>

class Rva006EE520;

#include "unicode_string.h"

class SubtitleEntry;

// The rowed SubTitleManager accessors (0x000468AD, 0x00046973, 0x000469CB,
// 0x00046906) on the same object.
class SubTitleManager
{
public:
	bool HasBeenDisplayed(int index);
	void SetDisplayedStats(int index);
	unsigned int GetColor(int index);
	UnicodeString GetText(int index);
};

class SubtitleManager
{
public:
	int getStartFrame(int index) const;
	SubTitleManager *subTitles() { return (SubTitleManager *)this; }

	char m_pad00[0x14];
	_STL::vector<SubtitleEntry *> m_entries;
};

class SubTitleWindow
{
public:
	void rva00260BBF(const StringBase<unsigned short> &text, unsigned int color);
};

class Rva006EE520
{
public:
	void update(int frame);

private:
	char m_pad00[0x184];
	SubtitleManager *m_manager;
	SubTitleWindow *m_sink;
};

void Rva006EE520::update(int frame)
{
	Rva006EE520 *self = this;
	SubtitleManager *manager = self->m_manager;
	if (!manager || !self->m_sink)
		return;

	unsigned int color;
	const int count = (int)manager->m_entries.size();
	for (int i = 0; i < count; ++i)
	{
		int startFrame = self->m_manager->getStartFrame(i);
		if (self->m_manager->subTitles()->HasBeenDisplayed(i) || frame < startFrame)
			continue;

		self->m_sink->rva00260BBF(self->m_manager->subTitles()->GetText(i),
			self->m_manager->subTitles()->GetColor(i));
		self->m_manager->subTitles()->SetDisplayedStats(i);
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00036E70 -> ?releaseBuffer@?$StringBase@G@@AAEXXZ
#pragma comment(linker, "/alternatename:??1?$StringBase@G@@IAE@XZ=?releaseBuffer@?$StringBase@G@@AAEXXZ")
//   0x000469CB -> ?GetColor@SubTitleManager@@QAEIH@Z
#pragma comment(linker, "/alternatename:?getColor@SubtitleManager@@QBEIH@Z=?GetColor@SubTitleManager@@QAEIH@Z")
//   0x00046906 -> ?GetText@SubTitleManager@@QAE?AVUnicodeString@@H@Z
#pragma comment(linker, "/alternatename:?getText@Rva006ED3D0TextAccess@@QBE?AV?$StringBase@G@@H@Z=?GetText@SubTitleManager@@QAE?AVUnicodeString@@H@Z")
//   0x000468AD -> ?HasBeenDisplayed@SubTitleManager@@QAE_NH@Z
#pragma comment(linker, "/alternatename:?hasBeenDisplayed@SubtitleManager@@QBE_NH@Z=?HasBeenDisplayed@SubTitleManager@@QAE_NH@Z")
//   0x00260BBF -> ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z (defined by Code/Libraries/Source/WWVegas/WWLib/rva00260BBFRva00260BBFFarm.cpp)
#pragma comment(linker, "/alternatename:?publish@Rva00435A40Sink@@QAEXABV?$StringBase@G@@I@Z=?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z")
//   0x00046973 -> ?SetDisplayedStats@SubTitleManager@@QAEXH@Z
#pragma comment(linker, "/alternatename:?setDisplayedStats@SubtitleManager@@QAEXH@Z=?SetDisplayedStats@SubTitleManager@@QAEXH@Z")
