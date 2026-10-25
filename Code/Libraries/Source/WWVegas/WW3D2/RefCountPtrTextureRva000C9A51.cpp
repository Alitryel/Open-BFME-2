// cl: /MD /DNDEBUG /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?rva000C9A51@Rva000C9A51@@QAEXXZ @0x000C9A51 30B
// Neighbours Rva000C99F9Destroy and W3DLaserDrawModuleData ctor; unlocks 0x000C9C17.
// Evidence: dual RefCountPtr<TextureClass> destroy call 0x000C99F9 then free 0x00030830 of +0 member; caller 0x000C9CAD.
// The game replaces the C allocator entry points; free is the direct wrapper,
// not the CRT import. Keep the real declaration with the game import setting.
#include <stdlib.h>
template <class T> class RefCountPtr;
class TextureClass;
void __cdecl Rva000C99F9Destroy(RefCountPtr<TextureClass> *, RefCountPtr<TextureClass> *);
class Rva000C9A51
{
public:
	void rva000C9A51();
	RefCountPtr<TextureClass> *m_0;
	RefCountPtr<TextureClass> *m_4;
};
void Rva000C9A51::rva000C9A51()
{
	Rva000C99F9Destroy(m_0, m_4);
	RefCountPtr<TextureClass> *p = m_0;
	if (!p)
		return;
	free(p);
}
