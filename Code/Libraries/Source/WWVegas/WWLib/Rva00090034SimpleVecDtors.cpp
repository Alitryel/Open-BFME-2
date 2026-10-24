// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??1Rva0090034@@UAE@XZ @0x00090034 33B and ??1Rva0090088@@UAE@XZ
// @0x00090088 35B. The bodies have the exact shape of the vendor
// SimpleVecClass / SimpleDynVecClass dtors (compare the matched
// SimpleVecClass<Vector3> pair in simplevec_vector3_dtor.cpp): vtables
// 0x00BC7DF4 and 0x00BC7E00, delete[] via 0x0002FD80, the derived tail-jumps
// to the base. The element type is unrecovered, so the classes keep the
// existing address-derived pin names instead of a SimpleVecClass<T> spelling.
// Scalar deleting dtors at 0x000900AB / 0x000900C7 call these bodies.

void __cdecl operator delete[](void *) throw();

class Rva0090034
{
public:
	virtual ~Rva0090034();

protected:
	int *Vector;
	int VectorMax;
};

Rva0090034::~Rva0090034()
{
	if (Vector) {
		delete[] Vector;
		Vector = 0;
		VectorMax = 0;
	}
}

class Rva0090088 : public Rva0090034
{
public:
	virtual ~Rva0090088();

protected:
	int ActiveCount;
};

Rva0090088::~Rva0090088()
{
	if (Vector) {
		delete[] Vector;
		Vector = 0;
	}
}
