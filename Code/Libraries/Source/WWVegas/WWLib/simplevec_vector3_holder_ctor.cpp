// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// 0x0007EEB0 (14B), unreferenced in retail: the default constructor of a
// class holding a SimpleDynVecClass<Vector3> at +0 and nothing else to
// initialise; it calls the rowed SimpleDynVecClass<Vector3>(int) constructor
// (0x0007E99E, call site 0x0007EEB5) with size 0 and returns this. The
// declaration-only specialisation keeps that call out of line, as retail
// does. The owner is not recovered; its name is address-derived.
#include "always.h"
void __cdecl operator delete[](void *) throw();
#include "simplevec.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

template <> SimpleDynVecClass<Vector3>::SimpleDynVecClass(int size);

class Rva0007EEB0
{
public:
	Rva0007EEB0();
private:
	SimpleDynVecClass<Vector3> m_points;
};

Rva0007EEB0::Rva0007EEB0() : m_points(0)
{
}
