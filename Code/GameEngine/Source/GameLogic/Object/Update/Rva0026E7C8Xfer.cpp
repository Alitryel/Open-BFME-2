// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00332975@Rva0026E7C8Ctor@@QAEXPAVXfer@@@Z, retail 0x00332975, 378 bytes.
//
// Target evidence: slot 3 (offset 0xC) of the table at VA 0x00BFA3A4 that
// ??0Rva0026E7C8Ctor stores at +0. Xfer Version1 (0x53EE), then the +4
// vector's element count (size / 12) through the int slot and reserve
// (rowed 0x33259F); per element two AsciiStrings (the second homed in the
// dead xfer argument slot). Storing: keyToName of the two element keys,
// xfer both strings, xferSTLObjectIDList (0x331F2D) on the element's +8
// list. Loading: xfer both strings, nameToKey both, push_back (0x3328B6) a
// temporary built by the rowed Rva00331EAD(int,int) ctor (0x331EAD) whose
// implicit destructor runs the pinned list destructor (0x268902), then
// reset (0x26549E) and xferSTLObjectIDList on back()'s list. Neither mode:
// only the string destructors run.
// Structural inference: Rva00331EAD is modelled as a ctor-only derivation of
// the 12-byte element and the list view derives from the
// xferSTLObjectIDList parameter type, so the rowed names stay distinct
// without pointer casts. Original class and member names are unproven.

#include "ascii_string.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	int m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	BridgeBehaviorObjectIDNode *m_node;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class Rva0029FB3BMember : public BridgeBehaviorObjectIDList
{
public:
	~Rva0029FB3BMember();
	void reset();
};

struct Rva003328B6Element
{
	NameKeyType m_key1;
	NameKeyType m_key2;
	Rva0029FB3BMember m_list;
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<Rva003328B6Element,Rva003328B6Element>(Rva003328B6Element *p,Rva003328B6Element const &v) { new (p) Rva003328B6Element(v); } }

class Rva00331EAD : public Rva003328B6Element
{
public:
	Rva00331EAD(int a, int b);
};

class Rva0026E7C8Ctor
{
public:
	Rva0026E7C8Ctor();
	void rva00332975(Xfer *xfer);

private:
	void *m_unk0;
	_STL::vector<Rva003328B6Element> m_vec;
};

void Rva0026E7C8Ctor::rva00332975(Xfer *xfer)
{
	xfer->Version1();
	int count = (int)m_vec.size();
	*xfer == count;
	m_vec.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		AsciiString s1;
		AsciiString s2;
		if (xfer->IsStoring())
		{
			Rva003328B6Element &e = m_vec[i];
			s1 = TheNameKeyGenerator->keyToName(e.m_key1);
			s2 = TheNameKeyGenerator->keyToName(e.m_key2);
			*xfer == s1;
			*xfer == s2;
			xferSTLObjectIDList(xfer, &e.m_list);
		}
		else if (xfer->IsLoading())
		{
			*xfer == s1;
			*xfer == s2;
			NameKeyType k1 = TheNameKeyGenerator->nameToKey(s1);
			NameKeyType k2 = TheNameKeyGenerator->nameToKey(s2);
			m_vec.push_back(Rva00331EAD(k1, k2));
			Rva0029FB3BMember *list = &m_vec.back().m_list;
			list->reset();
			xferSTLObjectIDList(xfer, list);
		}
	}
}
