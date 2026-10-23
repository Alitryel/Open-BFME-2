// cl: /GS

void sendFeslMessage( void *message, const char *route, void *connection ) throw();

// The pinned buffer/capacity ctor and +0x10/+0x14 buffer fields identify the
// message layout; key/value types select the matched record add accessors.
// Its derived destructor is chosen over the folded BfmeMsg base destructor.
#pragma comment(linker, "/alternatename:??0FeslEchoMessage@@QAE@PADH@Z=??0BfmeMsgVJH@@QAE@PADH@Z")
#pragma comment(linker, "/alternatename:??1FeslEchoMessage@@QAE@XZ=??1BfmeMsgVJH@@UAE@XZ")
#pragma comment(linker, "/alternatename:?addInt@FeslEchoMessage@@QAEXPBDH@Z=?addInt@Rva007E8810Message@@QAEXPBDH@Z")
#pragma comment(linker, "/alternatename:?addString@FeslEchoMessage@@QAEXPBD0@Z=?addString@Rva007E8810Message@@QAEXPBD0@Z")

class FeslEchoMessage
{
public:
	FeslEchoMessage( char *buffer, int capacity ) throw();
	~FeslEchoMessage() throw();
	void addInt( const char *key, int value ) throw();
	void addString( const char *key, const char *value ) throw();

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char m_pad10[ 0x0c ];
	unsigned int m_type;
	int m_20;
	char m_pad24[ 0x0c ];
	char m_ready;
	char m_pad31[ 3 ];
};

class FeslEchoNotifier
{
public:
	void notifyEcho();

private:
	char m_pad00[ 8 ];
	int *m_owner;
	char m_pad0c[ 4 ];
	void *m_connection;
	char m_pad14[ 8 ];
	char m_userId[ 0x25 ];
	char m_secret[ 0x25 ];
	char m_pad66[ 0x62 ];
	int m_transactionId;
};


// ?notifyEcho@FeslEchoNotifier@@QAEXXZ
void FeslEchoNotifier::notifyEcho()
{
	char buffer[ 0x100 ];
	FeslEchoMessage message( buffer, sizeof( buffer ) );

	int *echo = (int *)( (char *)m_owner[ 3 ] + 0x28c );
	message.m_04 = echo[ 1 ];
	message.m_08 = echo[ 2 ];
	message.m_0c = echo[ 3 ];
	message.m_type = 'ECHO';
	message.m_20 = 0;
	message.m_ready = 1;
	message.addInt( (char *)"TID", m_transactionId );
	message.addInt( (char *)"TYPE", 1 );
	if( m_userId[ 0 ] )
	{
		message.addString( (char *)"UGID", m_userId );
		message.addString( (char *)"SECRET", m_secret );
	}
	sendFeslMessage( &message, (char *)"->D", m_connection );
}
