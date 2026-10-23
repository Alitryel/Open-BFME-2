// cl: /DNDEBUG /MD /EHsc
// Retail 0x008FD640: BFME WW3D initialisation stores the static sort-list pair.

class DX8Wrapper
{
public:
	static bool Init(void *hwnd, bool lite);
};

class DefaultStaticSortListClass
{
public:
	DefaultStaticSortListClass();

private:
	char m_body[0x324];
};

void *g_WW3D_Hwnd;
unsigned char g_WW3D_Lite;
struct WW3DStaticSortGlobals
{
	void *defaultList;
	void *currentList;
};

WW3DStaticSortGlobals g_WW3D_StaticSortGlobals;
// The global at this VA is WW3D::IsInitted; this name aliases it rather than
// defining a second variable the rest of the game never sees.
extern unsigned char g_WW3D_IsInitted;
#pragma comment(linker, "/alternatename:?g_WW3D_IsInitted@@3EA=?IsInitted@WW3D@@0_NA")

extern "C" __declspec(dllimport) unsigned long __stdcall timeBeginPeriod(unsigned long period);

class WW3D
{
public:
	static bool Init(void *hwnd, char *defaultpal, bool lite);
};

bool WW3D::Init(void *hwnd, char *, bool lite)
{
	g_WW3D_Hwnd = hwnd;
	g_WW3D_Lite = lite;
	if (!DX8Wrapper::Init(g_WW3D_Hwnd, lite))
		return false;
	timeBeginPeriod(1);
	DefaultStaticSortListClass *list = new DefaultStaticSortListClass;
	g_WW3D_StaticSortGlobals.defaultList = list;
	g_WW3D_StaticSortGlobals.currentList = list;
	if (!lite)
		g_WW3D_IsInitted = 1;
	return true;
}
