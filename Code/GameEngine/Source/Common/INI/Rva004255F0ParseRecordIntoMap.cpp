// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI
// Open-BFME7: INI block parser at 0x004255F0 (105 B): a zeroed (AsciiString
// name + 4-byte value) record local is filled through INI::initFromINI with
// the field table at VA 0x010F1B34 then inserted into the map the store
// argument points at (the red-black tree insert_unique at 0x00424BA0 whose
// pair result comes back through the hidden pointer) and destroyed by the
// record destructor at 0x00423280.  Address-derived names.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

#include "ascii_string.h"

struct Rva004255F0Record
{
	Rva004255F0Record() : m_value( 0 ) {}
	~Rva004255F0Record();

	AsciiString m_name;
	int m_value;
};

struct Rva004255F0InsertResult
{
	void *m_where;
	bool m_inserted;
};

class Rva004255F0Map
{
public:
	Rva004255F0InsertResult insert_unique( const Rva004255F0Record &record );
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void parseAsciiString( INI *ini, void *instance, void *store, const void *userData );
};

void Rva00339900Parse( INI *ini, void *instance, void *store, const void *userData );

// Retail VA 0x00BDC048: the record's two fields and the zero sentinel.
extern const FieldParse Rva004255F0FieldParseTable[] = {
	{ "Side", &INI::parseAsciiString, 0, 0x0 },
	{ "Sound", &Rva00339900Parse, 0, 0x4 },
	{ 0, 0, 0, 0 }
};

class Rva004255F0
{
public:
	static void parseRecordIntoMap( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseRecordIntoMap@Rva004255F0@@SAXPAVINI@@PAX1PBX@Z
void Rva004255F0::parseRecordIntoMap( INI *ini, void *, void *store, const void * )
{
	Rva004255F0Record record;
	ini->initFromINI( &record, Rva004255F0FieldParseTable );
	((Rva004255F0Map *)store)->insert_unique( record );
}
