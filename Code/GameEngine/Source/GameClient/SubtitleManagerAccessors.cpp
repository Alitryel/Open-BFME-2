// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?addSubtitle@SubtitleManager@@QAEXABVAsciiString@@IHHHHH@Z, retail 0x00688AA0 (105B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/SubtitleManagerAccessors.cpp
// (BFME1 0x0081DDD0). Creates the entry through the manager's factory hook and
// pushes it on the entry vector. The donor defines 7 further siblings the sweep
// did not place, so only the placed body is defined here; the rest stay
// declared-only.

#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "ascii_string.h"
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}


union SubtitleEntryBulk
{
	int words[10];
	struct
	{
		unsigned int color;
		char middle[0x14];
		bool displayed;
		char rest[0x0B];
	} fields;
};

class SubtitleEntry
{
public:
	SubtitleEntry(const SubtitleEntry &that);
	AsciiString getText() const;
	SubtitleEntry &operator=(const SubtitleEntry &that)
	{
		m_text = that.m_text;
		m_label = that.m_label;
		m_bulk = that.m_bulk;
		m_tailFirst = that.m_tailFirst;
		m_tailSecond = that.m_tailSecond;
		return *this;
	}

	AsciiString m_text;
	AsciiString m_label;
	SubtitleEntryBulk m_bulk;
	int m_tailFirst;
	int m_tailSecond;
};

typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
	const AsciiString &, unsigned int, int, int, int, int, int);

class SubtitleManager
{
public:
	SubtitleManager(CreateSubtitleEntry createEntry, int second, const AsciiString &name);
	void addSubtitle(const AsciiString &label, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);
	bool hasBeenDisplayed(int index) const;
	AsciiString getText(int index) const;
	void setDisplayedStats(int index);
	unsigned int getColor(int index) const;
	int getStartFrame(int index) const;
private:
	CreateSubtitleEntry m_createEntry;
	int m_second;
	AsciiString m_name;
	AsciiString m_secondaryName;
	int m_count;
	_STL::vector<SubtitleEntry *> m_entries;
	int m_startFrame;
	int m_state[15];
	bool m_enabled;
};

void SubtitleManager::addSubtitle(const AsciiString &label, unsigned int color,
	int style, int alignment, int line, int startFrame, int endFrame)
{
	SubtitleEntry *entry = m_createEntry(&m_secondaryName, m_count, label, color,
		style, alignment, line, startFrame, endFrame);
	m_entries.push_back(entry);
}

// ??0SubtitleManager@@QAE@P6APAVSubtitleEntry@@PAVAsciiString@@HABV2@IHHHHH@ZH1@Z
// retail 0x00688750 (107B). Placed by masked whole-.text search of the compiled
// donor body (single hit on unclaimed ground).
SubtitleManager::SubtitleManager(CreateSubtitleEntry createEntry, int second,
	const AsciiString &name) :
	m_createEntry(createEntry),
	m_second(second),
	m_name(name),
	m_secondaryName(),
	m_count(0),
	m_entries(),
	m_enabled(false)
{
	m_startFrame = 0x7FFFFFFF;
	// Keep the sentinel visible before the remaining state is cleared, as retail does.
	_ReadWriteBarrier();
	m_state[0] = 0;
	m_state[1] = 0;
	m_state[2] = 0;
	m_state[3] = 0;
	m_state[4] = 0;
	m_state[5] = 0;
	m_state[6] = 0;
	m_state[7] = 0;
	m_state[8] = 0;
	m_state[9] = 0;
	m_state[10] = 0;
	m_state[11] = 0;
	m_state[12] = 0;
	m_state[13] = 0;
	m_state[14] = 0;
}
