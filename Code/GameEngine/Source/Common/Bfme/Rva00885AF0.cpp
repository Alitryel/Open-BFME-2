// cl: /DNDEBUG /MD /EHs-c-
//
// Cftp::~Cftp, retail 0x006CA600, 81 bytes (BFME1 donor Rva00885AF0;
// Zero Hour WWDownload ftp.cpp): close the data and control sockets and the
// transfer file. Written as the real virtual destructor, the compiler stores
// Cftp's vtable (0x00CE8A38) itself; Cftp::Cftp (ftp_constructor.cpp) and
// its vtable's deleting destructor reach this body by that name.
extern "C" int __stdcall closesocket( int );
extern "C" __declspec(dllimport) int __cdecl fclose( void* );

class Cftp
{
public:
	virtual ~Cftp();
	int m_socket4;
	int m_socket8;
	char padC[0x3AC];
	void* m_file3B8;
};

Cftp::~Cftp()
{
	if ( m_socket8 )
	{
		closesocket( m_socket8 );
		m_socket8 = 0;
	}
	if ( m_socket4 )
	{
		closesocket( m_socket4 );
		m_socket4 = 0;
	}
	if ( m_file3B8 )
	{
		fclose( m_file3B8 );
		m_file3B8 = 0;
	}
}
