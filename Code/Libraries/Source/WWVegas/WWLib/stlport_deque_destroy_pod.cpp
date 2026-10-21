// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// The rows here are the deque iterator helpers over 20-byte elements in
// 0x78-byte nodes: _Deque_iterator_base::_M_increment and operator!=.
// The range __destroy/__destroy_aux and operator++ over this element are
// Rva0054FD83Destroy.cpp's rows (their element holds a string); this unit
// instantiates only its own two bodies so it emits no copy of those.

#include <deque>

struct PodPayload20 { char m_body[20]; };

namespace _STL
{
template void _Deque_iterator_base<PodPayload20>::_M_increment();
template bool _STLP_CALL operator!=<PodPayload20>(
	const _Deque_iterator_base<PodPayload20> &,
	const _Deque_iterator_base<PodPayload20> &);
}
