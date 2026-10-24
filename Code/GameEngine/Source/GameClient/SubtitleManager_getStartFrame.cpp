// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?getStartFrame@SubtitleManager@@QBEHH@Z retail 0x00688680 (98B).
// Evidence: the assert string at VA 0x00CE4558 reads "Index out of range in
// SubTitleManager::GetStartFrame."; the class layout (m_entries vector at
// +0x14) and the Debug slots 0x60/0x6C/0x38/0x4C match the
// SubtitleManagerAccessors.cpp sibling and the Rva003625C3Glow Debug shape.
// The near file parseSubtitle.cpp already links this manager.

#include <vector>

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);

class SubtitleEntry
{
public:
	char m_pad[0x18];
	int m_startFrame;
};

class SubtitleManager
{
public:
	int getStartFrame(int index) const;

private:
	char m_pad[0x14];
	_STL::vector<SubtitleEntry *> m_entries;
};

int SubtitleManager::getStartFrame(int index) const
{
	if (index < (int)m_entries.size())
		return m_entries[index]->m_startFrame;
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::GetStartFrame.").CrashDone(1);
	return 0x7fffffff;
}
