// ?rva006E5050@Rva006E58D0@@QAEXPAX00@Z
// partial score=0.489 date=2026-10-17
// cl: /O2 /MD
//
// AptActionQueueC action-pool neighbours next to Rva006E4D50.cpp. Layout and
// assert triple are shared with Rva006E3230Validate.cpp: pool at +0, current
// at +4, end at +8, size at +0x10, 24-byte action stride.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

void *__cdecl Rva006CD440Alloc(int size);

struct Rva006E3230Action
{
	char data[24];
};

class AptValue
{
public:
	virtual void unused0();
	virtual void unused1();
};

struct Rva006E3230ActionFull
{
	int eActionType;
	char _pad4[8];
	AptValue *m_pValues[3];
};

class AptActionQueueC
{
	Rva006E3230Action *m_aActionPool;
	Rva006E3230Action *m_pCurrent;
	Rva006E3230Action *m_pEnd;
	char _padC[4];
	int m_iActionPoolSize;

public:
	void rva006E3230(Rva006E3230Action *pCur);
	void ClearActions();
	AptActionQueueC(int nSize);
};

#include <windows.h>

extern void* (__cdecl *g_pfnE17798)(void*, int);
extern void* (__cdecl *g_pfnE1777C)(void*, void*, void*);
extern void* (__cdecl *g_pfnE1778C)(void*, void*);
extern void __cdecl Rva006FD060Forward(void*,void*,void*,void*);
extern int __cdecl Rva006CFDF0DecRef(int*);
extern void __cdecl bfmeDropVGO(void*);
extern unsigned __cdecl Rva00894D80Inc(unsigned*);

class EAStringC
{
	char _d[16];
public:
	EAStringC(const char* s);
	~EAStringC();
};

struct Rva006D07E0Key
{
	int vgo;
};

class Rva006D0A30List
{
public:
	Rva006D07E0Key Find(const EAStringC& s);
};
extern Rva006D0A30List* g_pListAtE176CC;

#define APT_ASSERT(c, exprStr, line) do { if(!(c)) { (*g_bfmeAptAssertAtE17734)(exprStr, "C:\\Projects\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", line); if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); } } while(0)

struct AptCharShape
{
	int m_type;
	int pParentAnim;
	int f08;
	int f0C;
	int f10;
	int f14;
	int f18;
	int f1C;
	int f20;
	int f24;
	int f28;
	int f2C;
	int f30;
	int f34;
	int f38;
	int f3C;
	int f40;
};

struct AptExport
{
	unsigned szName;
	int v;
};

struct AptMovieRef
{
	unsigned a;
	unsigned b;
};

class Rva006E58D0
{
public:
	int f00;
	int f04;
	int f08;
	int m_nChars;
	AptCharShape** apCharacters;
	int f14;
	int f18;
	int f1C;
	int m_nVals;
	unsigned* m_pVals;
	int m_nExports;
	AptExport* aExports;
	int f30[8];
	void rva006E5050(void*,void*,void*);
};

extern int g_Unnamed70E900(int,int,int,int);
struct Unnamed70E900Obj { char d[8]; void Fix(int,int,int); };

void Rva006E58D0::rva006E5050(void* pBase, void* pArg1, void* pArg2)
{
	APT_ASSERT((unsigned)apCharacters < 0xfffff, "(unsigned)apCharacters < 0xfffff", 0x28);
	if (apCharacters)
		apCharacters = (AptCharShape**)((char*)apCharacters + (int)pBase);
	APT_ASSERT((unsigned)aExports < 0xfffff, "(unsigned)aExports < 0xfffff", 0x2c);
	if (aExports)
		aExports = (AptExport*)((char*)aExports + (int)pBase);
	for (int i = 0; i < m_nExports; i++)
	{
		APT_ASSERT((unsigned)aExports[i].szName < 0xfffff, "(unsigned)aExports[i].szName < 0xfffff", 0x2f);
		if (aExports[i].szName)
			aExports[i].szName += (unsigned)pBase;
	}
	struct { int v; unsigned char pad[3]; } nLimit = { m_nChars, { 0, 0, 0 } };
	for (int i = 0; i < nLimit.v; i++)
	{
		if (i) nLimit.v = i;
		APT_ASSERT((unsigned)apCharacters[i] < 0xfffff, "(unsigned)apCharacters[i] < 0xfffff", 0x35);
		if (1 ? apCharacters[i] : apCharacters[i])
			apCharacters[i] = (AptCharShape*)((char*)apCharacters[i] + (int)pBase);
		if (!apCharacters[i])
			continue;
		APT_ASSERT((unsigned int)apCharacters[i]->pParentAnim == 0x09876543, "(unsigned int)apCharacters[i]->pParentAnim == 0x09876543", 0x38);
		apCharacters[i]->pParentAnim = (int)apCharacters[0];
		int t = apCharacters[i]->m_type - 1;
		if ((unsigned)t > 0xb)
		{
			APT_ASSERT(0, "bad type", 0xa9);
			continue;
		}
		switch (t + 1)
		{
		case 1:
			APT_ASSERT(apCharacters[i]->f18 == i, "(int)apCharacters[i]->shape.zID == i", 0x3f);
			apCharacters[i]->f18 = (int)(*g_pfnE17798)(pArg1, i);
			break;
		case 2:
			{
				APT_ASSERT((unsigned)apCharacters[i]->f34 < 0xfffff, "(unsigned)apCharacters[i]->text.szInitialText < 0xfffff", 0x45);
				if (apCharacters[i]->f34)
					apCharacters[i]->f34 += (int)pBase;
				APT_ASSERT((unsigned)apCharacters[i]->f38 < 0xfffff, "(unsigned)apCharacters[i]->text.szVariable < 0xfffff", 0x46);
				if (apCharacters[i]->f38)
					apCharacters[i]->f38 += (int)pBase;
			}
			break;
		case 3:
			APT_ASSERT((unsigned)apCharacters[i]->f08 < 0xfffff, "(unsigned)f08 < 0xfffff", 0x4b);
			if (apCharacters[i]->f08)
				apCharacters[i]->f08 += (int)pBase;
			APT_ASSERT((unsigned)apCharacters[i]->f10 < 0xfffff, "(unsigned)f10 < 0xfffff", 0x4c);
			if (apCharacters[i]->f10)
				apCharacters[i]->f10 += (int)pBase;
			break;
		case 4:
			APT_ASSERT((unsigned)apCharacters[i]->f24 < 0xfffff, "(unsigned)f24 < 0xfffff", 0x54);
			if (apCharacters[i]->f24)
				apCharacters[i]->f24 += (int)pBase;
			APT_ASSERT((unsigned)apCharacters[i]->f28 < 0xfffff, "(unsigned)f28 < 0xfffff", 0x55);
			if (apCharacters[i]->f28)
				apCharacters[i]->f28 += (int)pBase;
			APT_ASSERT((unsigned)apCharacters[i]->f30 < 0xfffff, "(unsigned)f30 < 0xfffff", 0x57);
			if (apCharacters[i]->f30)
				apCharacters[i]->f30 += (int)pBase;
			APT_ASSERT((unsigned)apCharacters[i]->f38 < 0xfffff, "(unsigned)f38 < 0xfffff", 0x58);
			if (apCharacters[i]->f38)
				apCharacters[i]->f38 += (int)pBase;
			{
				int n = apCharacters[i]->f34;
				if (n > 0)
				{
					for (int k = 0; k < n; k++)
					{
						AptMovieRef* r = (AptMovieRef*)apCharacters[i]->f38;
						APT_ASSERT((unsigned)r[k].b < 0xfffff, "(unsigned)r.b < 0xfffff", 0x5b);
						if (r[k].b)
							r[k].b += (unsigned)pBase;
						Rva006FD060Forward((void*)r[k].b, pBase, pArg1, (void*)&f30);
					}
				}
			}
			APT_ASSERT((unsigned)apCharacters[i]->f3C < 0xfffff, "(unsigned)f3c < 0xfffff", 0x5e);
			if (apCharacters[i]->f3C)
				apCharacters[i]->f3C += (int)pBase;
			break;
		case 5:
			((Unnamed70E900Obj*)((char*)apCharacters[i] + 8))->Fix((int)pBase, (int)pArg1, (int)&f30);
			break;
		case 6:
			{
				APT_ASSERT(apCharacters[i]->f08 == i, "(int)f08 == i", 0x6f);
				int found = 0;
				for (int e = 0; e < m_nExports; e++)
					if ((int)aExports[e].v == i)
						found = (int)aExports[e].szName;
				apCharacters[i]->f08 = (int)(*g_pfnE1777C)(pArg1, (void*)i, (void*)found);
			}
			break;
		case 7:
			APT_ASSERT(apCharacters[i]->f08 == i, "(int)f08 == i2", 0x8c);
			apCharacters[i]->f08 = (int)(*g_pfnE1778C)(pArg1, (void*)i);
			break;
		case 8:
			((Unnamed70E900Obj*)((char*)apCharacters[i] + 8))->Fix((int)pBase, (int)pArg1, (int)&f30);
			if (i != 0)
			{
				APT_ASSERT(0, "(int)i == 0", 0x97);
			}
			break;
		case 9:
			APT_ASSERT((unsigned)apCharacters[i]->f34 < 0xfffff, "(unsigned)g34 < 0xfffff", 0x9e);
			if (apCharacters[i]->f34)
				apCharacters[i]->f34 += (int)pBase;
			{
				int n = apCharacters[i]->f30;
				if (n > 0)
				{
					int off = 0;
					for (int k = 0; k < n; k++)
					{
						int* pp = (int*)apCharacters[i]->f34;
						APT_ASSERT((unsigned)*(int*)((char*)pp + off + 0x34) < 0xfffff, "(unsigned)h < 0xfffff", 0xa1);
						if (*(int*)((char*)pp + off + 0x34))
							*(int*)((char*)pp + off + 0x34) += (int)pBase;
						off += 0x38;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	APT_ASSERT((unsigned)m_pVals < 0xfffff, "(unsigned)m_pVals < 0xfffff", 0xaf);
	if (m_pVals)
		m_pVals = (unsigned*)((char*)m_pVals + (int)pBase);
	for (int k = 0; k < m_nVals; k++)
	{
		APT_ASSERT((unsigned)m_pVals[k*4] < 0xfffff, "(unsigned)v0 < 0xfffff", 0xb2);
		if (m_pVals[k*4])
			m_pVals[k*4] += (unsigned)pBase;
		APT_ASSERT((unsigned)m_pVals[k*4+1] < 0xfffff, "(unsigned)v1 < 0xfffff", 0xb3);
		if (m_pVals[k*4+1])
			m_pVals[k*4+1] += (unsigned)pBase;
		{
			Rva006D07E0Key key = g_pListAtE176CC->Find(EAStringC((const char*)m_pVals[k*4]));
			int* dst = (int*)&m_pVals[k*4+3];
			if (dst != (int*)&key)
			{
				if (*dst)
				{
					if (!Rva006CFDF0DecRef(dst))
						bfmeDropVGO((void*)*dst);
				}
				*dst = *(int*)&key;
				if (*dst)
					Rva00894D80Inc((unsigned*)*dst);
			}
		}
	}
}
