// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: _STL::_Deque_iterator_base<GameResultsRequest>::_M_set_node,
// retail 0x00419D9C, 21 bytes. BFME1 donor is
// Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp
// (b1 0x0063FFE0); the body is STLport's deque iterator re-seat, identical
// in both games once relocations are masked.
//
// GameResultsRequest is two strings around a port (hostname, port, results),
// 28 bytes under STLport, and STLport sizes deque blocks at 128 bytes
// (_MAX_BYTES), so each node holds 128 / 28 = 4 requests. Re-seating the
// iterator stores the new map node, reloads the block start from it, and
// parks the block end 4 elements (0x70 bytes) past the start.

// Use the shared STLport declaration so the queue donors compose with this iterator.
#include <deque>

class GameResultsRequest
{
	char m_requestBody[0x1C];
};

template void _STL::_Deque_iterator_base<GameResultsRequest>::_M_set_node(GameResultsRequest **);
