// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Open-BFME: INI parse-and-register factory at retail 0x0059EE10 (135B).
// Same S4_PARSE_WITH_FIELDS shape as S4ParseThenRegisterWithFields.cpp
// (twin 0x0059C4C0, 142B): allocate 0x10 bytes, run the matched base
// constructor Rva0035D47B at 0x0035D45A, which calls the native base at
// 0x001DBAA4, then overrides the vptr and fields +4/+C/+9. This instance has no
// tail fields (S4_NO_TAIL) and AT4 == 2. Target constructor and destructor
// rows establish the neutral Rva0035D47B owner; its original name remains
// unresolved. The empty field table uses its existing native data owner.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

struct Gen_00489270
{
	void m(int a);
};

// The native allocation calls the existing constructor at RVA 0x0035D45A.
// Match that provider's 16-byte view rather than emitting a second constructor
// and an undefined integer spelling for its vtable.
class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8, m_9, m_A;
    char m_padB;
    int m_C;
};
class Rva0035D47B : public Rva001DBAA4
{
public:
    Rva0035D47B();
    virtual ~Rva0035D47B();
};

// The native null record at VA 0x00C6BB18 already has this data owner.
extern const int g_emptyFieldParseTable[4];

void s4ParseFieldsRva0059EE10(INI *ini, Gen_00489270 *sink)
{
	Rva0035D47B *t = new Rva0035D47B;

	ini->initFromINI(t, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));

	sink->m((int)t);
}
