// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) char * __cdecl strncpy(char *, const char *, unsigned int);

class Rva00889780Class
{
public:
	char m_pad0[0x9E7C];
	char m_str[0x10]; // 0x9E7C
	int m_field9E8C;

	void d_00889780( const char *arg1, int arg2 );
};

void Rva00889780Class::d_00889780( const char *arg1, int arg2 )
{
	// BFME1's donor baked its empty-string VA here; retail BFME2 uses 0x00BBAC1C.
	strncpy( m_str, arg1 ? arg1 : "", 0x0F );
	m_str[0x0F] = 0;
	m_field9E8C = arg2;
}
