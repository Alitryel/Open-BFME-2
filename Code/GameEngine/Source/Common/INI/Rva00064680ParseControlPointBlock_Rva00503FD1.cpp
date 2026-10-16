// cl: -DNDEBUG -MD -EHsc /Ob1 -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI
// Open-BFME7: the ControlPoint INI block parser at 0x00064680 (140 B).  Both
// the INI and the instance must be present (else INIException(3
// "ControlPoint::ParseINIBlock::Invalid data passed in.")); a record built by
// the constructor at 0x00064390 (R3ScalarFieldConstructors2.cpp layout) is
// filled through INI::initFromINI with the table at VA 0x010753D0 the
// unsigned +0x18 count is rescaled by the 0.03f constant at VA 0x01075354
// (the fild / sign test / add 2^32 sequence is the unsigned-to-float
// conversion) and the
// record is handed with the instance to the callback the userData argument
// carries.  Address-derived names.

typedef int Int;
typedef float Real;

struct FieldParse;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class Rva00064390
{
public:
	Rva00064390();
	int m_00, m_04, m_08, m_0C;
	float m_10, m_14;
	unsigned int m_18;
};

extern const FieldParse Rva00064680FieldParseTable[];
extern const Real Rva00064680NegativeScale;

// Retail 0x00503E4F (39 bytes): the millisecond-to-frame rescale as its own
// file static (value * frames-per-second global 0x00DBA4E8 * 0.001, then
// _ftol2). It takes the value in EAX, the private convention cl 7.1 picks
// for a file static; identical copies in the 0x003FD1xx constructor units
// were ICF-folded onto this one.
extern int BfmeClientFramesPerSecond;
static unsigned int msecToFramesRva00503E4F( unsigned int value )
{
	return (unsigned int)( (Real)BfmeClientFramesPerSecond * (Real)value * 0.001f );
}

typedef void ( *Rva00064680Callback )( void *instance, Rva00064390 *record );

class Rva00064680
{
public:
	static void parseControlPointBlock( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseControlPointBlock@Rva00064680@@SAXPAVINI@@PAX1PBX@Z
void Rva00064680::parseControlPointBlock( INI *ini, void *instance, void *, const void *userData )
{
	if( ini && instance )
	{
		Rva00064390 record;
		ini->initFromINI( &record, Rva00064680FieldParseTable );
		record.m_18 = msecToFramesRva00503E4F( record.m_18 );
		Rva00064680Callback callback = (Rva00064680Callback)userData;
		if( callback )
			callback( instance, &record );
	}
	else
		throw INIException( 3, "ControlPoint::ParseINIBlock::Invalid data passed in." );
}
