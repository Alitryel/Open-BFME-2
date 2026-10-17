// cl: /O1 /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?Thread_Function@PingThreadClass@@UAEXXZ
// retail 0x005501F4..0x0055037E (394 bytes, RET 0), vtable 0x0086AB44 slot 1
// (slot 0 is the rowed ThreadClass entry 0x006104B0). WorldBuilder 1406570
// is the debug twin. Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_BFMEThreadFunction.cpp,
// itself Zero Hour's PingThreadClass::Thread_Function with the running flag
// replaced by a one-millisecond try-lock of the thread's mutex (+0x50): the
// loop runs while the lock FAILS, i.e. while the owner still holds it.
// Target facts: WSAStartup(0x101), ThePinger slots getRequest +0x14 and
// addResponse +0x18, isdigit/inet_addr/gethostbyname imports, the rowed
// MutexClass::LockClass pair 0x00613A70/0x00613AC0, STLport string default
// ctor 0x00007850 and assignment 0x000120C0, and the ICMP helper 0x0054F99E
// called as a thiscall member (this in ECX) with IP and timeout (an
// address-named member pin beside its stdcall row).
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE
// Retail's allocators free through the game's free wrapper at 0x00030830 (the rowed
// Rva00030830GameFree), as in the sibling GameResultsThreadClassThreadFunction.cpp.
#include <stdlib.h>
void __cdecl Rva00030830GameFree(void *);
#define free Rva00030830GameFree
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <cstddef>
#include <winsock.h>	// This one has to be here. Prevents collisions with winsock2.h

#include "GameNetwork/GameSpy/PingThread.h"
#include "mutex.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end

// BFME 2's thread base (rowed ThreadClass members): name +0x04, id +0x44,
// handle +0x48, priority +0x4C. Only the layout this body reads is needed.
class PingThreadBase
{
public:
	virtual ~PingThreadBase();
protected:
	virtual void Thread_Function() = 0;
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};

class PingThreadClass : public PingThreadBase
{
public:
	virtual void Thread_Function();

private:
	// 0x0054F99E, rowed as the stdcall ?MeasureIcmpPing@@YGHIH@Z (Zero Hour's
	// doPing; its body never reads ECX): this caller passes ECX=this, so here
	// it is an address-named member.
	Int rva0054F99E(UnsignedInt IP, Int timeout);
	MutexClass *m_runMutex;		// +0x50, held by the owner while the thread may run
};

void PingThreadClass::Thread_Function()
{
	try {
	PingRequest req;
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSAStartup(wVersionRequested, &wsaData);

	for (;;) {
		MutexClass::LockClass lock(*m_runMutex, 1);
		if (!lock.Failed())
			break;

		if (ThePinger->getRequest(req)) {
			const char *hostnameBuffer = req.hostname.c_str();
			UnsignedInt IP = 0xFFFFFFFF;
			if (isdigit(hostnameBuffer[0])) {
				IP = inet_addr(hostnameBuffer);
			} else {
				HOSTENT *hostStruct = gethostbyname(hostnameBuffer);
				in_addr *hostNode = (in_addr *)hostStruct->h_addr;
				IP = hostNode->s_addr;
			}

			Int totalPing = 0;
			Int goodReps = 0;
			Int reps = req.repetitions;
			while (reps-- && IP != 0xFFFFFFFF) {
				MutexClass::LockClass pingLock(*m_runMutex, 1);
				if (!pingLock.Failed())
					break;
				Int ping = rva0054F99E(IP, req.timeout);
				if (ping >= 0) {
					totalPing += ping;
					++goodReps;
				}
			}

			if (!goodReps)
				totalPing = -1;
			else
				totalPing = totalPing / goodReps;

			PingResponse resp;
			resp.hostname = req.hostname;
			resp.avgPing = totalPing;
			resp.repetitions = goodReps;
			ThePinger->addResponse(resp);
		}
	}

	WSACleanup();
	} catch (...) {
	}
}
