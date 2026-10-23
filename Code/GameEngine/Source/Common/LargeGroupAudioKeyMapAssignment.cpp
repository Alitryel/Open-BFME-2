// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/LargeGroupAudioKeyMapAssignment.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??4LargeGroupAudioKeyMap@@QAEAAV0@ABV0@@Z 0x003ED989 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// Open-BFME5: LargeGroupAudioKeyMap copy assignment, retail 0x003D4540,
// 45 bytes. It releases the current key references, copies the three-dword
// map storage, then retains every selected key in the copy.

struct Rva0026F4F4Element;
namespace _STL
{
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class vector;
// 0x0026F4F4 is rowed as this vector's copy assignment.
template <>
class vector<Rva0026F4F4Element, allocator<Rva0026F4F4Element> >
{
public:
	vector &operator=(const vector &other);
};
}
typedef _STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > Rva0026F4F4Vector;

class LGA_MemberObj;

void bfmeClearMembers(LGA_MemberObj *map);

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &other);
};

// 0x003ED498 is rowed as the free Rva003ED498Count walker.
void __cdecl Rva003ED498Count(void const *arg);

// ??4LargeGroupAudioKeyMap@@QAEAAV0@ABV0@@Z
LargeGroupAudioKeyMap &LargeGroupAudioKeyMap::operator=(
	const LargeGroupAudioKeyMap &other)
{
	if (&other != this)
	{
		bfmeClearMembers((LGA_MemberObj *)this);
		*(Rva0026F4F4Vector *)this = *(const Rva0026F4F4Vector *)&other;
		Rva003ED498Count(this);
	}

	return *this;
}
