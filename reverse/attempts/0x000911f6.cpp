// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z
// partial score=0.99 date=2026-10-17
// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z
// partial score=0.9668 date=2026-10-15
// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z
// partial score=0.9 date=2026-10-14
// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z
// partial score=0.94 date=2026-10-04
// cl: /O1 /MD
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Rva00091189 { public: void rva00091189(); };
class At2cObj { public: virtual void v0(); };
class Gen_0081E480 { public: virtual ~Gen_0081E480(); int m_b04; int m_b08; int m_b0c; int m_b10; };
class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
	virtual void v0(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual bool v5( int arg ); virtual int rva000911F6( int arg );
	virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual bool v13();
	int rva00090FE0( int value );
private:
	void *m_at14; void *m_at18; char m_parser[ 0x10 ]; At2cObj *m_at2c;
	int m_at30; int m_at34; unsigned char m_at38; int m_at3c;
	int m_at40; int m_at44; int m_at48; int m_at4c; int m_at50;
	char *m_at54; int m_at58; int m_at5c; int m_at60;
};
extern char g_00DE4498;
// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z present-unmatched
int Rva007E3C20Vp6Stream::rva000911F6( int arg )
{
	bool b = v13();
	int ebx = b ? 2 : 0;
	if ( m_at48 < 0 )
		v2();
	int edi = arg & 4;
	if ( edi == 0 && ( ebx & 2 ) )
		return ebx;
	if ( !v5( arg ) )
		return ebx;
	int trans = rva00090FE0( arg );
	if ( g_00DE4498 != 0 || edi != 0 || ( arg & 0x40 ) != 0 ) {
		int m44 = m_at44; int m40 = m_at40;
		unsigned int now = timeGetTime();
		int diff = (int)now - (int)( ( (__int64)( m44 * 1000 ) * trans ) / (edi ? m40 : m40) );
		int q1 = m40 / m44;
		int q2 = 1000 / q1;
		if ( diff - m_at50 > q2 )
			m_at50 = diff;
	}
	int limit = arg ? trans : trans;
	while ( m_at48 < limit ) {
		if ( v13() )
			break;
		if ( edi != 0 )
			break;
		v2();
		ebx |= 4;
	}
	if ( arg & 1 )
		return ebx;
	if ( (m_at4c) == m_at48 )
		return ebx;
	v3();
	m_at2c->v0();
	ebx |= 1;
	v2();
	if ( *(volatile int*)&edi == 0 )
		return ebx;
	if ( !v13() )
		return ebx;
	( (Rva00091189 *)this )->rva00091189();
	return ebx;
}
