// cl: /O2 /MD /EHsc /ICode/Libraries/Source/Apt/AptValue /ICode
// Native 006D77B0..006D7A5D: 685-byte String split callback, registered by
// the String setup at 006D815B. WB0177F430 corroborates delimiter conversion,
// default limit 999999, decoded-character mode and Find-based substring mode.
// Preserve the explicit argument temporary before initializing the limit,
// and increment the segment index before the part string leaves scope.
// EAStringC, array and allocator layouts follow the already matched providers;
// the callback retains its established address-derived name.

class AptValue
{
public:
	void toString(class EAStringC &out) const;	// 0x006DD6C0
	void SetString(const char *text);		// 0x006CBF70
};

class EAStringC
{
public:
	EAStringC() { clear(); }
	EAStringC(const EAStringC &other);
	~EAStringC();
	EAStringC &clear();
	EAStringC &operator=(const EAStringC &other);
	unsigned int rva006D3750() const;		// length
	const char *rva00620090() const;		// c_str
	EAStringC &rva006D61E0(int codepoint);		// assign one character
	int Find(const char *text, int start);
	EAStringC &Append(const char *const text, unsigned int length);
private:
	void *m_data;
};

class BfmeAptValue006DCD20
{
public:
	int toInteger() const;
	BfmeAptValue006DCD20 *checkedString();		// the AptString this value is
	unsigned char m_pad00[8];
	EAStringC m_text;				// +0x08
};

class AptBasePtrStack { public: BfmeAptValue006DCD20 *At(int index); };
struct AptActionInterpreter { AptBasePtrStack stack; };
extern AptActionInterpreter g_aptDateInterpreter;

class AptString
{
public:
	static AptString *Create();
	unsigned char m_pad00[8];
	EAStringC m_text;				// +0x08
};

const char *rva006d4280(const char *text, int *codepoint);	// decodes one character

class Rva006D2A60 { public: void *allocBlock(int size); void freeBlock(void *p, int size); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;

class AptArray
{
public:
	AptArray();
	void set(int index, AptValue *value);
	static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p, n); }
private:
	unsigned char m_pad[0x2C];
};

AptValue *rva006D77B0(BfmeAptValue006DCD20 *self, int argc)
{
	AptArray *result = new AptArray;
	if (argc == 0)
	{
		result->set(0, (AptValue *)self);
		return (AptValue *)result;
	}
	if (argc >= 1)
	{
		EAStringC delimiter;
		const AptValue * arg0=(const AptValue *)g_aptDateInterpreter.stack.At(0);
		int limit=999999;
		arg0->toString(delimiter);
		if (argc >= 2)
			limit = g_aptDateInterpreter.stack.At(1)->toInteger();
		EAStringC source(self->checkedString()->m_text);
		int delimiterLength = delimiter.rva006D3750();
		if (delimiterLength == 0)
		{
			const char *p = source.rva00620090();
			for (int i = 0; i < limit; ++i)
			{
				int codepoint;
				p = rva006d4280(p, &codepoint);
				if (codepoint == 0)
					break;
				EAStringC character;
				character.rva006D61E0(codepoint);
				AptString *piece = AptString::Create();
				((AptValue *)piece)->SetString(character.rva00620090());
				result->set(i, (AptValue *)piece);
			}
		}
		else
		{
			int position = 0;
			const char *text = source.rva00620090();
			for (int i = 0; i < limit;)
			{
				int found = source.Find(delimiter.rva00620090(), position);

				if (found == -1)
				{
					AptString *piece=AptString::Create();
					EAStringC rest;
					if (position != -1)
						rest.Append(source.rva00620090() + position, -1 - position);
					piece->m_text = rest;
					result->set(i, (AptValue *)piece);
					break;
				}
				AptString *piece=AptString::Create();
				EAStringC part;
				part.Append(text + position, found - position);
				piece->m_text = part;
				result->set(i, (AptValue *)piece);
				++i;
				position = found + delimiterLength;
			}
		}
	}
	return (AptValue *)result;
}
