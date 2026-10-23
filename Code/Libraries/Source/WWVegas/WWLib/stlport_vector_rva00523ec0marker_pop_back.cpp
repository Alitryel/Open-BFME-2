// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?pop_back@?$vector@VRva00523EC0Marker@@V?$allocator@VRva00523EC0Marker@@@_STL@@@_STL@@QAEXXZ,
// retail 0x00523EBC, 12 bytes: --_M_finish by the 8-byte element, then the
// inline single-object _Destroy tail-jumps the element dtor. Retail emits it
// directly after vector<AsciiString>::pop_back (0x00523EB0). The element
// dtor is the pinned ??1Rva00523EC0Marker@@QAE@XZ (0x0029D7C2: AsciiString
// release at +4, ICF-shared); the element's real type is not recovered.
#include <vector>

// LINK: 0x0029D7C2 is rowed ??1CameraMarker@@QAE@XZ; the element dtor reaches it
// through a qualified call.
class CameraMarker
{
public:
	~CameraMarker();
};

class Rva00523EC0Marker
{
public:
	~Rva00523EC0Marker() { ((CameraMarker *)this)->CameraMarker::~CameraMarker(); }
private:
	int m_00;
	void *m_04;
};

template void _STL::vector<Rva00523EC0Marker>::pop_back();
