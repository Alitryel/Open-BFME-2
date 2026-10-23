// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// Parses a WorldText block and appends its record to the campaign act.

typedef int Int;

class INI;
typedef void (*FieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	FieldParseProc parse;
	const void *userData;
	int offset;
};

#include "../../../../../reference/shims/iniexception/Common/INIException.h"

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void dup_002F0F7(INI *, void *, void *, const void *);
	static void parseAsciiString(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
};

#include "ascii_string.h"

class Rva004E194E
{
public:
	Rva004E194E() : m_04( 0 ), m_08( 0 ), m_flag10( false ) {}
	virtual ~Rva004E194E() {}

private:
	Int m_04;
	Int m_08;
	AsciiString m_text;
	bool m_flag10;
};

// The native table at 0x00861CE8 parses the two delays, text tag and summary flag.
extern const FieldParse Rva003B8610RecordFieldParseTable[] = {
	{ "DelayFromActStart", &INI::dup_002F0F7, 0, 4 },
	{ "Duration", &INI::dup_002F0F7, 0, 8 },
	{ "StringTag", &INI::parseAsciiString, 0, 12 },
	{ "SummaryEvent", &INI::parseBool, 0, 16 },
	{ 0, 0, 0, 0 }
};

class Rva00566557
{
public:
	void rva00566557(const Rva004E194E &record);
};

// ?ParseWorldTextBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseWorldTextBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva004E194E record;
		ini->initFromINI( &record, Rva003B8610RecordFieldParseTable );
		((Rva00566557 *)instance)->rva00566557(record);
	}
	else
		throw INIException( 3, "ParseWorldTextBlock::Invalid data passed in." );
}
