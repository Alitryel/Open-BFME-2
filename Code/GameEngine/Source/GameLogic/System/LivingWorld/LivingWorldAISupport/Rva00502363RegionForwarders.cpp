// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// Two same-object forwarders (RET 0x10), each passing its player and limit
// through, the region id at +0x14 of the region the third argument points
// at, and the output vector, to the rowed living-world AI query beside it:
//  - 0x00502363 (30B) -> Rva0050228B::rva0050228B 0x0050228B
//    (LivingWorldAIInformation.cpp), output by reference;
//  - 0x0050243F (30B) -> Rva00502381::rva00502381 0x00502381
//    (Rva005009AANextStep.cpp), output by pointer.
// Neither forwarder is referenced in the image; names are address-derived.
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}
struct Rva00501E3FElement;
typedef _STL::vector<Rva00501E3FElement, _STL::allocator<Rva00501E3FElement> > Rva00502363Vector;

struct Rva00502363Region
{
	char m_pad00[0x14];
	int m_regionID;	// +0x14
};

struct Rva0050228B
{
	void rva0050228B(int playerID, int maxDistance, int *regionID, Rva00502363Vector &out);
	void rva00502363(int playerID, int maxDistance, Rva00502363Region **region, Rva00502363Vector &out);
};

void Rva0050228B::rva00502363(int playerID, int maxDistance, Rva00502363Region **region, Rva00502363Vector &out)
{
	rva0050228B(playerID, maxDistance, &(*region)->m_regionID, out);
}

struct Rva00502381
{
	void rva00502381(int who, int limit, const int *key, Rva00502363Vector *out);
	void rva0050243F(int who, int limit, Rva00502363Region **region, Rva00502363Vector *out);
};

void Rva00502381::rva0050243F(int who, int limit, Rva00502363Region **region, Rva00502363Vector *out)
{
	rva00502381(who, limit, &(*region)->m_regionID, out);
}
