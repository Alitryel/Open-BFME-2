// ?Rva0030C2CESave@@YAXPAVRva0030C2CECollection@@PAVDataChunkOutput@@@Z
// partial score=0.97 date=2026-10-14
// ?Rva0030C2CESave@@YAXPAVRva0030C2CECollection@@PAVDataChunkOutput@@@Z
// partial score=0.93 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE
// ?Rva0030C2CESave@@YAXPAVRva0030C2CECollection@@PAVDataChunkOutput@@@Z, retail 0x0030C2CE, 316 bytes.
// RiverAreas save via DataChunkOutput: openDataChunk RiverAreas, write count, cursor-iterate areas, write int, Rva00537EAD, 4 AsciiStrings, RGBColor int, floats, enum string via 0xDB9650 table, Rva0053850B. Evidence: packet disassembly, WaterLookup cursor pattern, callees rowed.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short unk);
	void writeInt(int v);
	void writeReal(float v);
	void writeAsciiString(const AsciiString &s);
	void closeDataChunk();
};

class RGBColor
{
public:
	int getAsInt() const;
private:
	char m_pad00[12];
};

class Rva00537EAD
{
public:
	void rva00537EAD(DataChunkOutput *output);
};

class Rva0053850B
{
public:
	void rva0053850B(DataChunkOutput *output);
};

extern const char *g_00DB9650[];

struct Rva0030C2CEElem
{
	int m_int00;
	void *m_ptr04;
};

struct Rva0030C2CEArea
{
	char m_pad00[0x40];
	AsciiString m_strings40[4];
	RGBColor m_color50;
	float m_float5C;
	int m_int60;
	int m_int64;
	Rva0053850B m_save68;
};

class Rva0030C2CECollection
{
public:
	char m_pad00[0x14];
	Rva0030C2CEElem *m_begin14;
	Rva0030C2CEElem *m_end18;
};

struct Rva0030C2CECursor
{
	Rva0030C2CECollection *m_store;
	int m_index;
};

// ?Rva0030C2CECursorEqual present-unmatched
extern "C" __declspec(noinline) bool __cdecl Rva0030C2CECursorEqual(const Rva0030C2CECursor &a, const Rva0030C2CECursor &b)
{
	return a.m_store == b.m_store && a.m_index == b.m_index;
}

// ?Rva0030C2CESave@@YAXPAVRva0030C2CECollection@@PAVDataChunkOutput@@@Z present-unmatched
void __cdecl Rva0030C2CESave(Rva0030C2CECollection *coll, DataChunkOutput *out)
{
	out->openDataChunk("RiverAreas", 2);
	int count = (int)(coll->m_end18 - __vref(coll->m_begin14));
	out->writeInt(count);
	Rva0030C2CECursor endCur;
	Rva0030C2CECursor cur;
	endCur.m_store = coll;
	endCur.m_index = (int)(coll->m_end18 - coll->m_begin14);
	cur.m_store = coll;
	cur.m_index = 0;
	unsigned char nc_91 = Rva0030C2CECursorEqual(cur, endCur);
	if (nc_91 == false)
	{
		do
		{
			Rva0030C2CEElem *begin = cur.m_store->m_begin14;
			int idx = cur.m_index;
			{
			Rva0030C2CEArea *area = (Rva0030C2CEArea *)begin[idx].m_ptr04;
			_ReadWriteBarrier();
			out->writeInt(begin[idx].m_int00);
			((Rva00537EAD *)area)->rva00537EAD(out);
			AsciiString *p = area->m_strings40;
			for (int k = 4; k > 0; --k)
			{
				out->writeAsciiString(*p);
				++p;
			}
			out->writeInt(area->m_color50.getAsInt());
			out->writeReal(area->m_float5C);
			out->writeInt(area->m_int64);
			AsciiString tmp;
			if (area->m_int60 >= 0 && area->m_int60 < 4)
				((StringBase<char> &)tmp).set(g_00DB9650[area->m_int60]);
			out->writeAsciiString(tmp);
			area->m_save68.rva0053850B(out);
			}
			++cur.m_index;
		} while (Rva0030C2CECursorEqual(cur, endCur) == false);
	}
	out->closeDataChunk();
}
