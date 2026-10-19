// ?LoadAsset@AssetManagerImpl@@QAEXPAVAssetLoadEntry@@@Z
// partial score=0.7 date=2026-10-17
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// ?LoadAsset@AssetManagerImpl@@QAEXPAVAssetLoadEntry@@@Z
// retail 0x00623600..0x006240DC, 2780 bytes incl. 7-entry phase table at 0x6240C0.
// WorldBuilder 0x167B5C0 names AssetManagerImpl::LoadAsset (assetmanager_impl.cpp
// lines 1050..1205). BFME1 donor: targets/game/reverse/attempts/0x009f0fa0.cpp
// (Q1Receiver0134FAAC::m009F0FA0, 1198B) supplies the phase machine, the two
// registry sets, the queue removal and the required-keys set; BFME2 adds the
// DX8 wait dance, the demand-load debug log and the per-phase profiling CSV.
// All 25 callees are rowed except the inlined waits and the folded tree find.
// 2026-10-17 (opus): /G6 /arch:SSE + bfmealloc from sibling Rva00622290CollectKeys;
// scoped CS lock (EH states 2/3), Queue_Keys(true), out-of-line push_back_aux
// 0x621620, inline pop_back_aux, set-group ctor, static freq, shifted type code.
// Remaining: retail keeps this in ebp / asset in edi, frame 0x84 (mine 0x8c).

#define _STLP_NO_CSTD_FUNCTION_IMPORTS 1
namespace _STL { void __cdecl free(void *); }

#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <deque>
#include <hash_map>
#include <map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

namespace _STL {
static __forceinline int **copyAssetDequeNodes(int **first, int **last, int **result) {
    return last == first ? result : (int **)((char *)memmove(result, first,
        (char *)last - (char *)first) + ((char *)last - (char *)first));
}
static __forceinline int **copyAssetDequeNodesBackward(int **first, int **last, int **result) {
    int bytes = (char *)last - (char *)first;
    return bytes > 0 ? (int **)memmove((char *)result - bytes, first, bytes) : result;
}
template <> inline void deque<int>::_M_reallocate_map(unsigned nodesToAdd, bool addAtFront) {
    unsigned oldNumNodes = _M_finish._M_node - _M_start._M_node + 1;
    unsigned newNumNodes = oldNumNodes + nodesToAdd;
    int **newStart;
    if (_M_map_size._M_data > 2 * newNumNodes) {
        newStart = _M_map._M_data + (_M_map_size._M_data - newNumNodes) / 2
            + (addAtFront ? nodesToAdd : 0);
        if (newStart < _M_start._M_node)
            copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        else
            copyAssetDequeNodesBackward(_M_start._M_node, _M_finish._M_node + 1, newStart + oldNumNodes);
    } else {
        unsigned newMapSize = _M_map_size._M_data + (max)(_M_map_size._M_data, nodesToAdd) + 2;
        int **newMap = newMapSize ? (int **)allocator<char>::allocate(newMapSize * 4, 0) : 0;
        newStart = newMap + (newMapSize - newNumNodes) / 2 + (addAtFront ? nodesToAdd : 0);
        copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        if (_M_map._M_data) free(_M_map._M_data);
        _M_map._M_data = newMap;
        _M_map_size._M_data = newMapSize;
    }
    _M_start._M_set_node(newStart);
    _M_finish._M_set_node(newStart + oldNumNodes - 1);
}
template <> void deque<int>::_M_push_back_aux_v(const int &value);
template <> inline void deque<int>::_M_push_front_aux_v(const int &value) {
    int copy = value;
    if (1 > (unsigned)(_M_start._M_node - _M_map._M_data))
        _M_reallocate_map(1, true);
    *(_M_start._M_node - 1) = (int *)allocator<char>::allocate(0x80, 0);
    _M_start._M_set_node(_M_start._M_node - 1);
    _M_start._M_cur = _M_start._M_last - 1;
    if (_M_start._M_cur) *_M_start._M_cur = copy;
}
template <> inline void deque<int>::_M_pop_back_aux() {
    if (_M_finish._M_first) free(_M_finish._M_first);
    _M_finish._M_set_node(_M_finish._M_node - 1);
    _M_finish._M_cur = _M_finish._M_last - 1;
}
template <> inline void deque<int>::_M_pop_front_aux() {
    if (_M_start._M_first) free(_M_start._M_first);
    _M_start._M_set_node(_M_start._M_node + 1);
    _M_start._M_cur = _M_start._M_first;
}
}
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
typedef _STL::_Rb_tree<Rva001408C0Key,Rva001408C0Key,_STL::_Identity<Rva001408C0Key>,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > AssetKeyTree;
typedef _STL::hash_map<int, void *> AssetHash;
typedef _STL::map<int, void *> AssetKeyMap;

struct AssetSetGroup
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	AssetSetGroup() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

class Rva009EF0D0Element
{
public:
	virtual const char *slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(AssetSetGroup *keys);
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual unsigned slot34();
	virtual unsigned slot38();

	union
	{
		volatile unsigned int m_bfmeFlags;
		volatile unsigned int m_bfmeFlagsShared;
	};
	void *m_bfmeEntry;		// +0x08
	Rva001408C0Key *m_bfmeKeys;	// +0x0C
};

typedef _STL::deque<int> AssetQueue;

class Rva000309B0 {
    void *m_previous;
public:
    Rva000309B0 *rva00030980(void *value);
    void rva000309B0();
};
class AssetHeapScope {
    Rva000309B0 m_slot;
public:
    __forceinline AssetHeapScope(unsigned value) { m_slot.rva00030980((void *)value); }
    __forceinline ~AssetHeapScope() { m_slot.rva000309B0(); }
};

int bfmeRva0011F600();
bool BFME_DX8_Thread_Assert();
void BFME_DX8_Thread_Lock();

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(void);
	virtual void Slot08(void);
	virtual void Slot0C(void);
	virtual void Slot10(void);
	virtual void Slot14(void);
	virtual void Slot18(void);
	virtual void Slot1C(void);
	virtual void Slot20(void);
	virtual void Slot24(void);
	virtual void Slot28(void);
	virtual void Slot2C(void);
	virtual void Slot30(void);
	virtual void Slot34(void);
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(void);
	virtual void Slot40(void);
	virtual void Slot44(void);
	virtual void Slot48(void);
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(void); virtual void Slot04(void); virtual void Slot08(void); virtual void Slot0C(void);
	virtual void Slot10(void); virtual void Slot14(void); virtual void Slot18(void); virtual void Slot1C(void);
	virtual void Slot20(void); virtual void Slot24(void); virtual void Slot28(void); virtual void Slot2C(void);
	virtual void Slot30(void); virtual void Slot34(void); virtual void Slot38(void); virtual void Slot3C(void);
	virtual void Slot40(void); virtual void Slot44(void); virtual void Slot48(void); virtual void Slot4C(void);
	virtual void Slot50(void); virtual void Slot54(void); virtual void Slot58(void); virtual void Slot5C(void);
	virtual void Begin_Report(void);
	virtual void Slot64(void); virtual void Slot68(void);
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context, void *extra);
};

extern BFMEIndexBufferDebugClass *g_bfmeTheDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);


// Asset load profiling state (BFME2-only; retail VAs 0xE09B08/0xE09A08/
// 0xE09A00/0xE09C20/0xE09DB0/0xE09C10/0xE09C18).
extern char g_bfmeProfileFile[];
extern char g_bfmeProfilePrevFile[];
extern int g_bfmeProfileFrame;
extern Rva009EF0D0Element *g_bfmeProfileAssets[];
extern int g_bfmeProfileCount;
__int64 rva0061FCE0GetClockCyclesFast(void) throw();
// Same helper as the committed Rva0061FFD0Cluster.cpp / BFME1 profile.cpp:
// inline rdtsc is compiler machinery (the retail bytes are this exact body).
__forceinline void ProfileGetTime(__int64 &t)
{
	_asm
	{
		mov ecx,[t]
		push eax
		push edx
		rdtsc
		mov [ecx],eax
		mov [ecx+4],edx
		pop edx
		pop eax
	};
}

class AssetLock
{
	CRITICAL_SECTION *m_cs;
public:
	__forceinline AssetLock(CRITICAL_SECTION *cs) : m_cs(cs) { EnterCriticalSection(cs); }
	__forceinline ~AssetLock() { LeaveCriticalSection(m_cs); }
};

class AssetRegistry
{
public:
	void Worker_Thread_00622480();
	void Queue_Keys_00622680(bool front, const Rva001408C0Set &keys);
	void LoadAsset(Rva009EF0D0Element *asset);
	__forceinline void WaitForQueue()
	{
		int count = 0;
		if ((char)bfmeRva0011F600() != 0)
		{
			do
			{
				++count;
			} while (BFME_DX8_Thread_Assert() == 0);
		}
		LeaveCriticalSection(&m_lock68);
		Sleep(1);
		EnterCriticalSection(&m_lock68);
		while (count != 0)
		{
			BFME_DX8_Thread_Lock();
			--count;
		}
	}

private:
	unsigned int m_thread;
	unsigned int m_threadId;
	bool m_flag08;
	unsigned char m_unmodelled_009[0x17];
	__int64 m_totalCount;
	unsigned char m_unmodelled_028[0x24];
	AssetHash m_map4c;
	unsigned char m_unmodelled_060[8];
	CRITICAL_SECTION m_lock68;
	AssetQueue m_deques80[7];
	AssetSetGroup m_set198;
	AssetSetGroup m_set1ac;
	AssetSetGroup m_set1c0;
	AssetSetGroup m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned int m_unmodelled_1f0;
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_padding1f7;
};

void AssetRegistry::LoadAsset(Rva009EF0D0Element *asset)
{
	if (!asset->m_bfmeEntry || (asset->m_bfmeFlagsShared & 0xff0000) == 0x30000)
		return;

	__int64 tStart;
	if (g_bfmeProfileFile[0])
	{
		ProfileGetTime(tStart);
		g_bfmeProfileAssets[g_bfmeProfileCount++] = asset;
	}

	EnterCriticalSection(&m_lock68);
	if (((AssetKeyMap *)&m_set198)->find((int)(size_t)asset->m_bfmeEntry) == ((AssetKeyMap *)&m_set198)->end() &&
		!(asset->m_bfmeFlagsShared & 0x4000000))
	{
		m_set1d4.m_tree.insert((Rva001408C0Key)asset->m_bfmeEntry);
		if (!m_flag1f5)
			return;
		if (m_flag1f6)
		{
			const char *name = asset->slot00();
			if (name && name[0] != '#' &&
				strnicmp(name, "apt_", 4) != 0 &&
				strnicmp(name, "sfe_", 4) != 0 &&
				bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				g_bfmeTheDebug->Begin_Report();
				g_bfmeTheDebug->Get_Stream(0, 0, 0)
					->Put_String("[info] Demand load: ")
					->Put_String(name)
					->Finish(2);
			}
		}
		m_set198.m_tree.insert((Rva001408C0Key)asset->m_bfmeEntry);
	}

	while (((asset->m_bfmeFlagsShared & 0xff0000) == 0x10000 ||
		(asset->m_bfmeFlagsShared & 0xff0000) == 0x50000) &&
		m_deques80[(asset->m_bfmeFlagsShared >> 16) & 0xff].front() == (int)asset &&
		m_flag1f4)
	{
		WaitForQueue();
	}
	while ((asset->m_bfmeFlagsShared & 0xff0000) == 0x80000)
	{
		WaitForQueue();
	}

	unsigned int queue = (asset->m_bfmeFlagsShared >> 16) & 0xff;
	if (queue != 7)
	{
		unsigned int i = 0;
		for (; i < m_deques80[queue].size(); ++i)
		{
			if (m_deques80[queue][i] == (int)asset)
				break;
		}
		if (i < m_deques80[queue].size())
		{
			m_deques80[queue][i] = m_deques80[queue][m_deques80[queue].size() - 1];
			m_deques80[queue].pop_back();
		}
	}
	LeaveCriticalSection(&m_lock68);

	__int64 t[9];
	if (g_bfmeProfileFile[0])
	{
		ProfileGetTime(t[0]);
		for (int k = 1; k < 9; ++k)
			t[k] = t[0];
	}

	asset->m_bfmeFlags |= 0x2000000;
	AssetHeapScope heap(0x61737374);
	if (queue == 7)
		asset->m_bfmeFlags &= 0xff00ffff;

	switch ((asset->m_bfmeFlagsShared >> 16) & 0xff)
	{
	case 4:
		m_totalCount += asset->slot38();
		asset->m_bfmeFlags = (asset->m_bfmeFlagsShared & 0xff03ffff) | 0x30000;
		break;
	case 5:
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
		asset->slot18();
		asset->m_bfmeFlags = (asset->m_bfmeFlagsShared & 0xff06ffff) | 0x60000;
	case 6:
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
		asset->slot1C();
		asset->m_bfmeFlags = asset->m_bfmeFlagsShared & 0xff00ffff;
	case 0:
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
		asset->slot04();
		asset->m_bfmeFlags = (asset->m_bfmeFlagsShared & 0xff01ffff) | 0x10000;
	case 1:
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
		asset->slot08();
		asset->m_bfmeFlags = (asset->m_bfmeFlagsShared & 0xff02ffff) | 0x20000;
		m_totalCount += asset->slot38();
	case 2:
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
		asset->slot0C();
		{
			AssetSetGroup set;
			asset->slot10(&set);
			if (asset->m_bfmeKeys && asset->m_bfmeKeys[0])
			{
				for (int k = 0; asset->m_bfmeKeys[k]; ++k)
				{
					set.m_tree.insert(asset->m_bfmeKeys[k]);
				}
			}
			if (set.m_tree.size() != 0)
			{
				AssetLock lock(&m_lock68);
				Queue_Keys_00622680(true, set.m_tree);
			}
		}
		asset->m_bfmeFlags = (asset->m_bfmeFlagsShared & 0xff03ffff) | 0x30000;
		if (g_bfmeProfileFile[0])
			ProfileGetTime(t[(asset->m_bfmeFlagsShared >> 16) & 0xff]);
	default:
		break;
	}

	AssetLock lock(&m_lock68);
	m_deques80[3].push_back((int)asset);
	if (g_bfmeProfileFile[0])
	{
		static __int64 g_bfmeProfileFreq = rva0061FCE0GetClockCyclesFast();
		__int64 tEnd;
		ProfileGetTime(tEnd);
		char type[8];
		unsigned code = asset->slot34();
		int n = 0;
		if (code >> 24)
			type[n++] = (char)(code >> 24);
		code <<= 8;
		if (code >> 24)
			type[n++] = (char)(code >> 24);
		code <<= 8;
		if (code >> 24)
			type[n++] = (char)(code >> 24);
		code <<= 8;
		if (code >> 24)
			type[n++] = (char)(code >> 24);
		type[n] = 0;
		FILE *f;
		if (strcmp(g_bfmeProfileFile, g_bfmeProfilePrevFile) != 0)
		{
			strcpy(g_bfmeProfilePrevFile, g_bfmeProfileFile);
			f = fopen(g_bfmeProfileFile, "wt");
			fprintf(f, "frame,type,asset,tInit,tPreload,tLoad,tPostload,tTotal,recursion\n");
		}
		else
		{
			f = fopen(g_bfmeProfileFile, "at");
		}
		fprintf(f, "%d,%s,\"", g_bfmeProfileFrame, type);
		for (int k = 0; k < g_bfmeProfileCount; ++k)
		{
			fprintf(f, "%s%s", k ? "/" : "", g_bfmeProfileAssets[k]->slot00());
		}
		fprintf(f, "\"");
		fprintf(f, ",%.3lf", (double)(t[0] - tStart) / ((double)g_bfmeProfileFreq * 0.001));
		if (t[0] < t[1])
			fprintf(f, ",%.3lf", (double)(t[1] - t[0]) / ((double)g_bfmeProfileFreq * 0.001));
		else
			fprintf(f, ",");
		if (t[1] < t[2])
			fprintf(f, ",%.3lf", (double)(t[2] - t[1]) / ((double)g_bfmeProfileFreq * 0.001));
		else
			fprintf(f, ",");
		if (t[2] < t[3])
			fprintf(f, ",%.3lf", (double)(t[3] - t[2]) / ((double)g_bfmeProfileFreq * 0.001));
		else
			fprintf(f, ",");
		fprintf(f, ",%.3lf,%i\n", (double)(tEnd - tStart) / ((double)g_bfmeProfileFreq * 0.001), g_bfmeProfileCount);
		fclose(f);
		--g_bfmeProfileCount;
	}
}
