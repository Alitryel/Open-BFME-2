// ?rva00059EAE@MilesAudioManager@@QAE?AVRva00051ADA@@PBVAsciiString@@@Z
// partial score=0.9 date=2026-10-14
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva00059EAE@MilesAudioManager@@QAE?AVRva00051ADA@@PBVAsciiString@@@Z @0x00059EAE 206B
// Reference-counted audio-event-info lookup: under the manager's mutex guard (+0x9D4) the event table at +0xBC is
// searched for the name (rowed find 0x0041534B); a hit whose info can still take a reference (rowed try-add-ref
// 0x00050EFA) is returned as a counted reference (copy 0x00051ADA); no hit, or an info that is going away, returns
// the empty reference. Evidence: target bytes; the same guard/table views as the other MilesAudioManager units
// (StopAudio / Rva00052917 / Rva00056F61IterFind). The method name and the reference class name are
// address-derived; WorldBuilder has no match for this body.
#include "ascii_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *mutex, int defer);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_held;
};

class OpaqueRefCounted
{
public:
	bool rva00050EFA();
	void Release_Ref();
};

class AudioEventInfo;

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(const AudioEventInfo *info);
	~AudioEventInfoRef()
	{
		if (m_info)
			((OpaqueRefCounted *)m_info)->Release_Ref();
	}
	const AudioEventInfo *m_info;
};

class Rva00051ADA
{
public:
	Rva00051ADA(void *p) : m_ptr(p) {}
	Rva00051ADA(const Rva00051ADA &other, int unused) { rva00051ADA(other, unused); }
	Rva00051ADA &rva00051ADA(const Rva00051ADA &other, int unused);
	void *m_ptr;
};

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};

class MilesAudioManager
{
public:
	Rva00051ADA rva00059EAE(const AsciiString *name);

private:
	char m_pad0[0xBC];
	Rva00056F61 m_eventTable;	// +0xBC
	char m_padBC[0x9D4 - 0xBC - 4];
	int m_mutex9D4;
};

Rva00051ADA MilesAudioManager::rva00059EAE(const AsciiString *name)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	Rva0041534BIter found = m_eventTable.rva0041534B(name);
	Rva0041534BIter it = found;
	if (it.m_node == 0)
		return Rva00051ADA((void *)0);
	OpaqueRefCounted *info = *(OpaqueRefCounted **)((char *)it.m_node + 8);
	if (info->rva00050EFA())
	{
		AudioEventInfoRef ref((const AudioEventInfo *)info);
		((OpaqueRefCounted *)ref.m_info)->Release_Ref();
		return Rva00051ADA(*(const Rva00051ADA *)&ref, 0);
	}
	return Rva00051ADA((void *)0);
}
