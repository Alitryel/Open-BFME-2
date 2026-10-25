// A length check against a limit (trimmed from a six-body donor; the other
// five are declared-only here).

class BfmeItemDX
{
public:
	int m_bfmeBody[4];					// +0x00
};

void __cdecl bfmePush(BfmeItemDX *item);
void __cdecl bfmeRemove(BfmeItemDX *item);

class BfmeNodeDX
{
public:
	int m_bfmeHead[19];					// +0x00
	BfmeNodeDX *m_bfmeNext;					// +0x4C
};

class Gen_008A0C30
{
public:
	bool bfmeAllows(BfmeNodeDX *node) const;
};

extern "C" unsigned int __cdecl strlen(const char *text);

#pragma intrinsic(strlen)

class BfmeThingDX
{
public:
	int m_bfmeHead[4];					// +0x00
	const char *m_text;					// +0x10
};

// ?isTextTooLong@@YGHPBVBfmeThingDX@@@Z
int __stdcall isTextTooLong(const BfmeThingDX *thing)
{
	return strlen(thing->m_text) > 0x800;
}

class Gen_008991B0
{
public:
	void bfmeBump(void);
};

class Gen_00899DA0
{
public:
	void bfmeBump(void);
};
