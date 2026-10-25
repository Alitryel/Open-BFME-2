// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// SimpleDynVecClass<unsigned>::Add. Twin of the landed Vector3 body
// with a four-byte element. Use the existing Zero Hour simplevec.h template
// declaration so the W3DGameFont seed can host this explicit specialization.
// The field accesses and the already-rowed BfmePod4 Grow callee are unchanged.

#include "simplevec.h"

struct BfmePod4 { char m_data[4]; };
template <> class SimpleDynVecClass<BfmePod4>
{
protected:
	bool Grow(int new_size_hint);
	friend bool SimpleDynVecClass<unsigned>::Add(const unsigned &object, int new_size_hint);
};

template <>
bool SimpleDynVecClass<unsigned>::Add(const unsigned &object, int new_size_hint)
{
	if (ActiveCount >= VectorMax) {
		if (!((SimpleDynVecClass<BfmePod4> *)(void *)this)->Grow(new_size_hint))
			return false;
	}
	int n = ActiveCount;
	ActiveCount = n + 1;
	n *= sizeof(unsigned);
	unsigned *slot = (unsigned *)((char *)Vector + n);
	*slot = object;
	return true;
}
