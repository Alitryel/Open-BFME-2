// cl: /EHsc
// ??1Rva00006856@@QAE@XZ 0x00006856 8B, unreferenced in retail.
// Evidence: add ecx,0x20 then a tail jump into the rowed
// ATL::CSimpleArray<unsigned short>::RemoveAll (0x000055B0): the destructor of
// a class whose only member with a destructor is a CSimpleArray<WCHAR> at
// +0x20 (CSimpleArray's destructor is RemoveAll). Owner address-derived.

namespace ATL
{
template <class T> class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> > class CSimpleArray
{
public:
	~CSimpleArray() { RemoveAll(); }
	void RemoveAll();
private:
	T *m_aT;
	int m_nSize;
	int m_nAllocSize;
};
}

class Rva00006856
{
public:
	~Rva00006856();
private:
	char m_pad[0x20];
	ATL::CSimpleArray<unsigned short> m_20;
};

Rva00006856::~Rva00006856()
{
}
