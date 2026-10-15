// cl: -GF -Gy -MD -EHsc -GR -DNDEBUG -DWIN32 -D_WINDOWS -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

class Rva00791F70CallbackHost;

typedef void (__cdecl *Rva00791F70Callback)(
	Rva00791F70CallbackHost *, int, int, int );

enum WindowMsgHandledType { BFME_WMHT_IGNORED = 0 };
class GameWindow;
WindowMsgHandledType GadgetListBoxInput( GameWindow *, unsigned, unsigned, unsigned );

class Rva00791F70CallbackHost
{
public:
	void dispatch( int first, int second, int third );

private:
	char m_unreconstructed[ 0x1E0 ];
	Rva00791F70Callback m_callback;
};

void Rva00791F70CallbackHost::dispatch(
	int first, int second, int third )
{
	if( m_callback )
		m_callback( this, first, second, third );
	else
		GadgetListBoxInput( (GameWindow *)this, (unsigned)first, (unsigned)second, (unsigned)third );
}
