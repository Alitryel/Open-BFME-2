// cl: /MD /EHsc
// ?rva0006B7BF@BaseHeightMapRenderObjClass@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@M@Z @0x0006B7BF 69B
// Wrapper over rowed 0x000E6135: loads Rva000E6135* from this+0x3860 and forwards
// (id, by-value AsciiString name, float value) if non-null. By-value name gives
// the EH prolog with state 0 guard and the releaseBuffer teardown. Caller at
// 0x000CF40E passes TheTerrainRenderObject as this, id from [ecx+8], name copy
// from ([ecx+4]+8), float from ([ecx+4]+0x20).
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// The narrow teardown is rowed at 0x00036410 (StringBaseWideReleaseBuffer.cpp).
template <> StringBase<char>::~StringBase();


class Rva0055A88BDwordField;

class Rva000E6135
{
public:
	void rva000E6135(const Rva0055A88BDwordField *idSrc, const StringBase<char> &name, float value);
};

class BaseHeightMapRenderObjClass
{
private:
	char m_pad[0x3860];
	Rva000E6135 *m_3860;
public:
	void rva0006B7BF(const Rva0055A88BDwordField *id, StringBase<char> name, float value);
};

void BaseHeightMapRenderObjClass::rva0006B7BF(const Rva0055A88BDwordField *id, StringBase<char> name, float value)
{
	if (m_3860 != 0)
		m_3860->rva000E6135(id, name, value);
}
