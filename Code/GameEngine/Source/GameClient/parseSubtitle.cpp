// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// VideoPlayer::init passes the retail callback at 0x0081D7C0 to INI::load.
// The callback looks up a subtitle manager through TheVideoPlayer's virtual
// slot at +0x58, then fills it with the subtitle field table at 0x0112CDA0.
// The error text at 0x0112CF14 identifies the callback as parseSubtitle.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

#include "ascii_string.h"


struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *parseTable );
	int getLineNum( void ) const;

	AsciiString getFilename( void ) const;

private:
	char m_prefix[ 4 ];
	AsciiString m_filename;
};

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface() { }
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual const void *getVideo( const AsciiString &title ) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;
extern const FieldParse Rva0081D7C0FieldParseTable[];
#pragma comment(linker, "/alternatename:?Rva0081D7C0FieldParseTable@@3QBUFieldParse@@B=??_C@_01GBGANLPD@0?$AA@")

class INIException
{
public:
	INIException( int argumentCount, const char *format, ... );
	INIException( const INIException &other );
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};


// ?parseSubtitle@@YAXPAVINI@@PAX1PBX@Z
void parseSubtitle( INI *ini, void *, void *, const void * )
{
	const void *subtitle = TheVideoPlayer->getVideo( ini->getFilename() );
	if ( subtitle != 0 )
	{
		if ( ini->getNextToken( 0 ) != 0 )
		{
			ini->initFromINI( const_cast<void *>( subtitle ), Rva0081D7C0FieldParseTable );
		}
	}
	else
	{
		throw INIException( 8, "Could not get SubTitleMgr * for %s on line %d",
			ini->getFilename(), ini->getLineNum() );
	}
}

// ?TheVideoPlayer@@3PAVVideoPlayerInterface@@A: matched references place it at VA 0xe0aba8; also referenced as ?TheVideoPlayer@@3PAVVideoPlayer@@A.
VideoPlayerInterface * TheVideoPlayer = 0;
#pragma comment(linker, "/alternatename:?TheVideoPlayer@@3PAVVideoPlayer@@A=?TheVideoPlayer@@3PAVVideoPlayerInterface@@A")
