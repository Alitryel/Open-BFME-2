// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/LivingWorld/ParseEnableRegion.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ParseEnableRegion 0x004E1579 (129B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME7: ParseEnableRegion (retail 0x003B7BA0 162 B; a gap claimed through
// its own exception text).  With no INI or instance it throws INIException(3
// "ParseEnableRegion::Invalid data passed in."); otherwise the record below is built inline filled through
// INI::initFromINI with the table at VA 0x010ECE14 and handed to the
// instance's append routine (0x0043847E); the inline virtual destructor restores the vtable (VA 0x010EC76C) and releases the name.  Address-derived names.

typedef int Int;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
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
	static void parseAsciiString( INI *, void *, void *, const void * );
};

#include "ascii_string.h"

class Rva003B7BA0Record
{
public:
	virtual ~Rva003B7BA0Record() {}

private:
	AsciiString m_name;
};

// BFME 2's complete table at RVA 0x00861A50: the string at +4 and
// the four-zero terminator. The donor's table address is not used here.
extern const FieldParse Rva003B7BA0RecordFieldParseTable[2] = {
    { "Region", INI::parseAsciiString, 0, 4 },
    { 0, 0, 0, 0 }
};

class FXList;
class Rva00566527
{
public:
	void rva00566527( const FXList &record );
};

// ?ParseEnableRegion@@YAXPAVINI@@PAX1PBX@Z
void ParseEnableRegion( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7BA0Record record;
		ini->initFromINI( &record, Rva003B7BA0RecordFieldParseTable );
		// Existing rowed thunk 0x00566527 has this same reference ABI.
		// Its FXList spelling is a callable view, not this record's identity.
		((Rva00566527 *)instance)->rva00566527( (const FXList &)record );
	}
	else
		throw INIException( 3, "ParseEnableRegion::Invalid data passed in." );
}
