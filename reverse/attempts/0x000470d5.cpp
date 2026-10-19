// ?Rva000470D5GetTexture@@YA?AVBFME2ParticleTextureHandle@@PBURva000470D5Source@@@Z
// partial score=1.0 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};
class ShroudFilter { public: int m_00, m_04, m_08, m_0C, m_10; };
class ShroudTexture { public: ShroudFilter *getFilter(void); };
class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
	~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
	ShroudFilter *getFilter() { return ((ShroudTexture *)this)->getFilter(); }
	void setQuality(bool b);
};
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char*,int,int);
	void rva00132FE9(bool flag);
};
inline void BFME2ParticleTextureHandle::setQuality(bool b) { ((TextureAsset *)this)->rva00132FE9(b); }
struct Rva000470D5Source
{
	int m_00;
	int m_04;
	AsciiString m_name08;
	char m_pad0C[0x2C - 0x0C];
	BFME2ParticleTextureHandle *m_texture2C;
	unsigned int m_flags30;
	unsigned int getStatus() const { return m_flags30; }
	const AsciiString &getFilename() const { return m_name08; }
};
// TU-local static helper: retail keeps the hidden result in EDI from entry
// only when the helper is file-static beside its caller (0x000471AD).
static BFME2ParticleTextureHandle Rva000470D5GetTexture(const Rva000470D5Source *src)
{
	if (src->getStatus() & 2) {
		BFME2ParticleTextureHandle tex(*src->m_texture2C);
		tex.getFilter()->m_10 = 1;
		tex.getFilter()->m_0C = 1;
		return tex;
	} else {
		BFME2ParticleTextureHandle tex(TextureAsset::Get(src->getFilename().str(), 1, 0));
		tex.getFilter()->m_10 = 1;
		tex.getFilter()->m_0C = 1;
		tex.setQuality(true);
		return tex;
	}
}
class Rva000456C9 { public: void rva000456C9(const BFME2ParticleTextureHandle &); };
void Rva000470D5Caller(Rva000456C9 *render, const Rva000470D5Source *src)
{
	render->rva000456C9(Rva000470D5GetTexture(src));
}
