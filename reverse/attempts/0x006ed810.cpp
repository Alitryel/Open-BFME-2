// ?Rva006ED810@@YAPAVAptValue@@PAVBfmeAptValue006DCD20@@H@Z
// partial score=0.96 date=2026-10-15
// cl: /O2 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// scratch transcription of retail 0x006ED810 (953B, AptCharacter.cpp per the
// WB debug body's assert strings) for byte-matching; not part of the tree.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern unsigned char g_00E1771C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
public:
	void clear();
	~EAStringC();
};

class BfmeAptValue006DCD20;

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int index);
private:
	char bytes[12];
};

class AptActionInterpreter
{
public:
	AptBasePtrStack stack;
};
extern AptActionInterpreter g_aptDateInterpreter;

class AptValue;
extern AptValue *gpUndefinedValue;

class AptCIH;

class BfmeAptValue006DCD20
{
public:
	int toInteger() const;
	float rva006DD460() const;
	AptCIH *rva006DCF60(bool undefinedOK);
	bool isCharacterInst();
	bool isUndefined();
	int rva006DBB30get();
	void toString(EAStringC *out);
};

#define APT_CHECK(cond, msg, line) do { if (!(cond)) { g_bfmeAptAssertAtE17734(msg, "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); } } while(0)

static __forceinline void *getCharacterInst(BfmeAptValue006DCD20 *v)
{
	APT_CHECK((unsigned char)v->isCharacterInst(), "isCharacterInst()", 0xa5);
	return *(void **)((char *)v + 0x4C);
}

static __forceinline bool isSpriteInstBase(BfmeAptValue006DCD20 *v)
{
	if (v->isUndefined()) return false;
	if (v->rva006DBB30get() == 0x0D) return true;
	if (v->rva006DBB30get() == 0x12) return true;
	return false;
}

static __forceinline void *getSpriteInstBase(BfmeAptValue006DCD20 *v)
{
	APT_CHECK(v != 0, "this", 0xe2);
	APT_CHECK(isSpriteInstBase(v), "isSpriteInstBase()", 0x7D);
	return *(void **)((char *)v + 0x4C);
}

class AptValue
{
public:
};

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;

class AptCIH : public BfmeAptValue006DCD20
{
public:
	void *rva006CFF40() const;
	void factorySetProperty(int index, float value, int flag);
	bool rva006E02B0();
	AptCIH *rva006E0F40();
};

class Rva006E9A40List
{
public:
	unsigned short mnElements, mnMaxElements;
	void **maElements;
	void add(AptValue *element);
	void add(AptCIH *element);
};

struct Rva006E34D0Animations
{
	unsigned char m_pad00[0x20];
	Rva006E9A40List values;	// +0x20
	Rva006E9A40List clips;	// +0x28
};
extern Rva006E34D0Animations *g_bfmeAptPtrAtE176D0;

struct Rva006ED810Clip
{
	int m_type;					// +0x00 = 2
	void *m_matrix;				// +0x04
	unsigned int m_08;			// +0x08
	unsigned int m_0C;			// +0x0C
	unsigned int m_radius;		// +0x10 (float bits)
	unsigned int m_height;		// +0x14 (float bits)
	int m_labelIndex;			// +0x18
	unsigned int m_1C;
	unsigned int m_20;
	unsigned int m_scale;		// +0x24 = 12.0f (bits 0x41400000)
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_pad40[0x74 - 0x40];
	unsigned int m_flags74;		// +0x74
};

struct Rva006ED810Sprite
{
	unsigned char m_pad00[0x24];
	unsigned int m_24;			// +0x24
	unsigned char m_pad28[0x30 - 0x28];
	unsigned int m_30;			// +0x30
	unsigned int m_34;			// +0x34
	unsigned char m_pad38[0x3C - 0x38];
	unsigned int m_3C;			// +0x3c
	unsigned char m_pad40[0x44 - 0x40];
	unsigned int m_44;			// +0x44
	unsigned int m_48;			// +0x48
	unsigned char m_pad4C[0x50 - 0x4C];
	unsigned int m_50;			// +0x50
	unsigned int m_54;			// +0x54
	unsigned int m_58;			// +0x58
	unsigned int m_5C;			// +0x5c
	unsigned int m_60;			// +0x60
	unsigned int m_64;			// +0x64
	unsigned char m_pad68[0x6C - 0x68];
	unsigned int m_6C;			// +0x6c
	unsigned char m_pad70[0x74 - 0x70];
	unsigned int m_74;			// +0x74
};

struct Rva006ED810Labels
{
	unsigned char m_pad00[0x14];
	int m_count;		// +0x14
	void **m_items;		// +0x18
};

class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(BfmeAptValue006DCD20 *item, int a1, int pCharacter, int a3, int a4,
		int a5, int a6, float *copy0, int copy1, int v9, int v10, int hash);
};

AptValue *Rva006ED810(BfmeAptValue006DCD20 *arg0, int arg1)
{
	if (arg1 != 6)
		return (AptValue *)(*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);

	BfmeAptValue006DCD20 *v0 = g_aptDateInterpreter.stack.At(0);
	BfmeAptValue006DCD20 *v1 = g_aptDateInterpreter.stack.At(1);
	BfmeAptValue006DCD20 *v2 = g_aptDateInterpreter.stack.At(2);
	BfmeAptValue006DCD20 *v3 = g_aptDateInterpreter.stack.At(3);
	BfmeAptValue006DCD20 *v4 = g_aptDateInterpreter.stack.At(4);
	BfmeAptValue006DCD20 *v5 = g_aptDateInterpreter.stack.At(5);

	int i1 = v1->toInteger();
	float f2 = v2->rva006DD460();
	float f3 = v3->rva006DD460();
	float f4 = v4->rva006DD460();
	float f5 = v5->rva006DD460();

	EAStringC name;
	name.clear();
	v0->toString(&name);

	AptCIH *target = arg0->rva006DCF60(false);

	Rva006ED810Clip *clip = (Rva006ED810Clip *)(*(Rva006DB160 * *)&g_pChainBlockAllocator)->allocBlock(0x40);
	if (clip == 0)
	{
		g_bfmeAptAssertAtE17734("pCharacter", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp", 0x3C3);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	clip->m_type = 2;
	clip->m_08 = 0;
	clip->m_0C = 0;
	clip->m_radius = (unsigned int &)f4;
	clip->m_height = (unsigned int &)f5;
	clip->m_1C = 0;
	clip->m_20 = 0;
	clip->m_scale = 0x41400000u;
	clip->m_28 = 0;
	clip->m_2C = 0;
	clip->m_30 = 0;
	clip->m_34 = 0;
	clip->m_38 = 0;
	clip->m_labelIndex = -1;

	{
		AptCIH *character = arg0->rva006DCF60(false);
		void *q = getCharacterInst(character);
		clip->m_matrix = *(void **)(*(char **)((char *)q + 0xC) + 4);
	}

	{
		AptCIH *character = arg0->rva006DCF60(false);
		void *q = getCharacterInst(character);
		Rva006ED810Labels *labels = (Rva006ED810Labels *)*(void **)(*(char **)((char *)q + 0xC) + 4);
		int i = 0;
		int n = labels->m_count;
		void **it = labels->m_items;
		for (; i < n; ++i, ++it)
		{
			if (*(int *)*it == 3)
			{
				clip->m_labelIndex = i;
				break;
			}
		}
	}

	void *spriteInst = getSpriteInstBase(target);

	void *submit = ((BfmeSubmitter1283 *)((char *)spriteInst + 0x24))->bfmeSubmit1283(
		(BfmeAptValue006DCD20 *)0, i1 + 0x4000, (int)clip, (int)&name, (int)target, 1, -1,
		0, 0, 0, 0, 0);
	AptCIH *created = (AptCIH *)submit;
	APT_CHECK(created != 0, "this", 0xc4);
	if (created->rva006DBB30get() != 0x0F)
		goto done;
	if (created->isUndefined())
		goto done;

	{
		Rva006ED810Sprite *sprite = (Rva006ED810Sprite *)created->rva006E0F40();
		sprite->m_74 |= 1;
		sprite->m_74 &= ~2;
		sprite->m_74 &= ~4;
		sprite->m_34 = 0xFF000000;
		sprite->m_30 = 0xFFFFFFFF;
		sprite->m_5C = clip->m_height;
		sprite->m_50 = clip->m_08;
		sprite->m_58 = clip->m_radius;
		sprite->m_54 = clip->m_0C;
		sprite->m_44 = 0;
		sprite->m_48 = 0;
		sprite->m_24 = 0;
		sprite->m_60 = 0x41400000u;
		sprite->m_3C = clip->m_1C;
		sprite->m_64 = clip->m_labelIndex;
		sprite->m_6C = 6;
		created->factorySetProperty(0, f2, 0);
		created->factorySetProperty(1, f3, 0);
		if (g_00E1771C)
		{
			g_bfmeAptPtrAtE176D0->values.add((AptValue *)created);
			g_bfmeAptPtrAtE176D0->clips.add((AptCIH *)created);
		}
	}

done:
	return (AptValue *)(*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}
