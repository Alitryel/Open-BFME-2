// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/reference/shims/objectdlink /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// stlport
// Object team-list iterator with the target virtual-inheritance member pointer.
#include "ObjectDlinkPmf.h"

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR( OBJCLASS *cur, GetNextFunc getNextFunc )
		: m_cur( cur ), m_getNextFunc( getNextFunc ) {}

	void advance()
	{
		if ( m_cur )
			m_cur = (m_cur->*m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

template DLINK_ITERATOR<Object>::DLINK_ITERATOR(Object *, DLINK_ITERATOR<Object>::GetNextFunc);
template void DLINK_ITERATOR<Object>::advance();
