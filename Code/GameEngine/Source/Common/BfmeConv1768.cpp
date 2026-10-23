// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Identity repair: native SidesList music loader 0x0032FD8E and WB
// 0x00A86AD0 construct and destroy the same objects, with TeamsInfoRec
// at 28 bytes and the LibraryMapCache vector header at 12 bytes.
// Existing member/base provider declarations are preserved; this is not
// a claim that all private class views or inherited template pins agree.
// LINK: the base dtor 0x0032C36B is rowed as the STLport map tree dtor and the
// member dtor 0x0032C3A3 as ??1Rva0032C3A3, so the base and member take those types.
class AsciiString;
namespace _STL {
template <class A, class B> struct pair;
template <class P> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	~_Rb_tree();

	unsigned char m_bfmeHeadCH[0xc];
};
}
typedef _STL::pair<AsciiString, AsciiString> BfmeCHKey;
typedef _STL::pair<const BfmeCHKey, int> BfmeCHValue;
typedef _STL::_Rb_tree<BfmeCHKey, BfmeCHValue, _STL::_Select1st<BfmeCHValue>, _STL::less<BfmeCHKey>, _STL::allocator<BfmeCHValue> > BfmeBaseCH;

class Rva0032C3A3
{
public:
	~Rva0032C3A3();

	unsigned char m_bfmeHeadCH[0x10];
};
typedef Rva0032C3A3 BfmeMemCH;

class TeamsInfoRec : public BfmeBaseCH
{
public:
	TeamsInfoRec(const TeamsInfoRec &value) throw();
	TeamsInfoRec &operator=(const TeamsInfoRec &that);
	~TeamsInfoRec() {}

	void swap(TeamsInfoRec *owner) throw();

	BfmeMemCH m_bfmeMemCH;
};

TeamsInfoRec &TeamsInfoRec::operator=(const TeamsInfoRec &that)
{
	TeamsInfoRec(that).swap(this);

	return *this;
}
