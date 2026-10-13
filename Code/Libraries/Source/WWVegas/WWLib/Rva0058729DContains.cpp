// cl: /MD
//
// ?rva0058729D@Rva0058729D@@QAE_NABUICoord2DBase@@@Z, retail 0x0058729D 50B.
// Linear search: count at +0x10, inline ICoord2D array at +0x14 (8B each).
// For i in 0..count-1 if arr[i]==needle (rowed ??8ICoord2D 0x00004CAD)
// return true else false. Caller 0x00588553.
#include "../../../Include/Lib/ICoord2D.h"
#include "../../../Include/Lib/ICoord2DBase.h"

class Rva0058729D
{
public:
	bool rva0058729D(const ICoord2DBase &needle);
private:
	char _pad00[0x10];
	int m_count; // +0x10
	ICoord2D m_arr[1]; // +0x14 inline
};

bool Rva0058729D::rva0058729D(const ICoord2DBase &needle)
{
	int n = m_count;
	for (int i = 0; i < n; ++i)
	{
		if (m_arr[i] == needle)
			return true;
	}
	return false;
}
