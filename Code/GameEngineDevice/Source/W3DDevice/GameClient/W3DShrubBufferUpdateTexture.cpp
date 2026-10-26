// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// W3DShrubBuffer::updateTexture, retail 0x000E7B3F (692B). WorldBuilder's
// debug build names it (W3DShrubBuffer.cpp, asserts at lines 176/181); BFME 1's
// matched W3DShrubBufferRva0071DAF0.cpp is the donor for the two-pass
// texture-page build. BFME 2 packs through two TexturePackers (+0x40 shrubs,
// +0x68 shadows): clear both, add every tree type's texture (and its shadow
// texture when the type casts one) as loaded by TextureAsset::Get (rowed
// 0x00132D89), then read back each texture's page coordinates, store the two
// result textures (+0x38 / +0x3C) and report a page larger than 1024 on either
// side. Tree type stride 0x5C from +0x4FB90, count at +0x51270.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Vec2
{
	Real x, y;
};

class ProxyClass
{
public:
	class ProxyData
	{
	};
};

// Callees rowed under other class views: the 16-bit-count release 0x0061ED10
// (TextureBaseClass::Release_Ref), the holder size getters 0x0013275A and
// 0x00132784 (TextureBaseClass, a one-pointer view), and the packer's clear,
// page lookup and result getter (0x00170EBC, 0x00171583, 0x00171625).
class TextureBaseClass
{
public:
	void Release_Ref();
	int rva0013275A() const;
	int rva00132784() const;
};

// One-pointer texture handles returned by value and released on scope exit.
class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle() { if (m_data) ((TextureBaseClass *)m_data)->Release_Ref(); }
	ProxyClass::ProxyData *m_data;
};
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *name, Int a, Int b);
};

class HierarchyPrototype : public ProxyClass::ProxyData
{
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_data) ((TextureBaseClass *)m_data)->Release_Ref(); }
	const RefCountPtr &operator=(const RefCountPtr &other);
	T *m_data;
};

class AssetReference : public RefCountPtr<HierarchyPrototype>
{
};

class Rva00132D0FHolder : public RefCountPtr<HierarchyPrototype>
{
public:
	using RefCountPtr<HierarchyPrototype>::operator=;
	const TextureBaseClass *texture() const { return (const TextureBaseClass *)this; }
};

class Rva00170EBC
{
public:
	void rva00170EBC(Bool shadow);
};
class Rva00171583
{
public:
	Bool rva00171583(const unsigned int &texture, Vec2 *topLeft, Vec2 *bottomRight);
};
class Rva00171024
{
public:
	AssetReference rva00171625();
};

class TexturePacker
{
public:
	void rva00171067(const BFME2ParticleTextureHandle &texture);
	Rva00170EBC *clearView() { return (Rva00170EBC *)this; }
	Rva00171583 *lookupView() { return (Rva00171583 *)this; }
	Rva00171024 *resultView() { return (Rva00171024 *)this; }
private:
	unsigned char m_bytes[0x28];
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
};
class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

#define DEBUG_CRASH_REPORT(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			theDebug->slot60(); \
			theDebug->slot6C(0, 0, 0)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)

struct ShrubTypeData
{
	unsigned char m_pad00[0x0C];
	AsciiString m_textureName;		// +0x0C
};

struct ShrubType
{
	const ShrubTypeData *m_data;		// +0x00
	Vec2 m_topLeft;				// +0x04
	Vec2 m_shadowTopLeft;			// +0x0C
	Vec2 m_bottomRight;			// +0x14
	Vec2 m_shadowBottomRight;		// +0x1C
	Bool m_doShadow;			// +0x24
	AsciiString m_shadowTextureName;	// +0x28
	unsigned char m_pad2c[0x5C - 0x2C];
};

class W3DShrubBuffer
{
protected:
	void updateTexture();
private:
	// Same opaque base storage and type array as the retail seed. The texture
	// view starts 0x20 bytes into each 0x5C type record.
	void *m_baseVtable;
	unsigned char m_storage[0x5BC - 4];
	Real m_pushRateScale;
	unsigned char m_pad5c0[0x4FB70 - 0x5C0];
	unsigned char m_types[64 * 0x5C];
	Int m_numTypes;

};

void W3DShrubBuffer::updateTexture()
{
	(*reinterpret_cast<TexturePacker *>(m_storage + 0x3C)).clearView()->rva00170EBC(false);
	(*reinterpret_cast<TexturePacker *>(m_storage + 0x64)).clearView()->rva00170EBC(true);
	Int i;
	for (i = 0; i < m_numTypes; i++)
	{
		(*reinterpret_cast<TexturePacker *>(m_storage + 0x3C)).rva00171067(TextureAsset::Get(reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_data->m_textureName.str(), 0, 0));
		if (reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_doShadow)
			(*reinterpret_cast<TexturePacker *>(m_storage + 0x64)).rva00171067(TextureAsset::Get(reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_shadowTextureName.str(), 0, 0));
	}
	for (i = 0; i < m_numTypes; i++)
	{
		(*reinterpret_cast<TexturePacker *>(m_storage + 0x3C)).lookupView()->rva00171583((const unsigned int &)TextureAsset::Get(reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_data->m_textureName.str(), 0, 0),
			&reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_topLeft, &reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_bottomRight);
		if (reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_doShadow)
			(*reinterpret_cast<TexturePacker *>(m_storage + 0x64)).lookupView()->rva00171583((const unsigned int &)TextureAsset::Get(reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_shadowTextureName.str(), 0, 0),
				&reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_shadowTopLeft, &reinterpret_cast<ShrubType *>(reinterpret_cast<unsigned char *>(m_types) + 0x20)[i].m_shadowBottomRight);
	}
	(*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x34)) = (*reinterpret_cast<TexturePacker *>(m_storage + 0x3C)).resultView()->rva00171625();
	(*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x38)) = (*reinterpret_cast<TexturePacker *>(m_storage + 0x64)).resultView()->rva00171625();
	if ((*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x34)).texture()->rva0013275A() > 1024U || (*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x34)).texture()->rva00132784() > 1024U)
		DEBUG_CRASH_REPORT("Combined shrub texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
	if ((*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x38)).texture()->rva0013275A() > 1024U || (*reinterpret_cast<Rva00132D0FHolder *>(m_storage + 0x38)).texture()->rva00132784() > 1024U)
		DEBUG_CRASH_REPORT("Combined shrub shadow texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
}
