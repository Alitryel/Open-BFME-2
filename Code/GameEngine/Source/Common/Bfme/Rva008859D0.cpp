// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) char* __cdecl _mbsdup( const char* );
extern "C" __declspec(dllimport) int __cdecl sprintf( char*, const char*, ... );
extern "C" __declspec(dllimport) void __cdecl free( void* );

class Cftp
{
public:
	char pad0[0x34];
	const char* m_dir34;

	void d_008859d0( const char* name, char* outBuf );
};

void Cftp::d_008859d0( const char* name, char* outBuf )
{
	char* dupName = _mbsdup( name );
	for ( char* p = dupName; *p; ++p )
	{
		if ( *p == '\\' || *p == '.' || *p == ' ' )
		{
			*p = '_';
		}
	}

	sprintf( outBuf, "download\\%s_%d.tmp", dupName, m_dir34 );
	free( dupName );
}
