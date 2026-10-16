// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B7DC3Box@@QAEXXZ @0x005B7DC3 54B: allocate-transform-consume.
// Raw-allocates 0x28 bytes through operator new at 0x2FDA0, then
// transforms non-null results through the pinned
// 0-arg method, stamps the block's first word with 4, and runs the +0x0C
// sub-object's pinned consumer on the block pointer. The null path leaves
// a null block (the store is unconditional). Targets from retail REL32.
// 0x005B72BE is the rowed Rva0040C1F0 constructor; the +0x0C consumer
// 0x0005548F is the rowed STLport list<int>::push_back.
struct Rva0040C1F0
{
	Rva0040C1F0();
	int m_00;
	char m_pad[0x24];
};

namespace _STL
{
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class list;
template <>
class list<int, allocator<int> >
{
public:
	void push_back(const int &value);
	void *m_node;
};
}

struct Rva005B7DC3Box
{
	char pad[0xc];
	_STL::list<int, _STL::allocator<int> > m_0C;

	void Run();
};

void *__cdecl operator new(unsigned int size);
// Placement new: inlined here, and dllimport keeps cl from emitting an
// out-of-line copy that would compete with retail's 0x00006EE0 body.
__declspec(dllimport) __forceinline void *operator new(unsigned int, void *where) { return where; }

void Rva005B7DC3Box::Run()
{
	Rva0040C1F0 *p = (Rva0040C1F0 *)::operator new(0x28);
	p = (p != 0) ? new (p) Rva0040C1F0 : 0;
	int out = (int)p;
	p->m_00 = 4;
	m_0C.push_back(out);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0005548F reads ?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z
#pragma comment(linker, "/alternatename:?Consume@Rva005B7DC3Sub@@QAEXPAPAX@Z=?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z")
//   0x005B72BE reads ??0Rva0040C1F0@@QAE@XZ
#pragma comment(linker, "/alternatename:?Xform@Rva005B7DC3Block@@QAEPAU1@XZ=??0Rva0040C1F0@@QAE@XZ")
