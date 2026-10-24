// cl: /MD /EHsc
// ??1W3DSnowManager@@UAE@XZ retail 0x000938C4 75B (formerly the address name Rva00938C4)
// The W3DSnowManager dtor shape (Zero Hour W3DSnow.cpp: ReleaseResources then
// the snow texture ref): own vptr BC8144 (the W3DSnowManager vtable, see
// ?update@W3DSnowManager slot 28); under EH state 1 the rowed
// ?ReleaseResources@W3DSnowManager 0x000931D3; the texture holder at +0x78 is
// released through the rowed ?Release_Ref@TextureClass 0x0061ED10 when set
// (state 0); then the rowed base dtor ??1SnowManager@@UAE@XZ 0x0020156B.
// Its deleting dtor 0x00094626 is slot 0 of the same vtable.

class TextureClass
{
public:
	void Release_Ref();
};

class SnowManager
{
public:
	virtual ~SnowManager();

private:
	unsigned char m_pad04[0x74 - 4];
};

class Rva00938C4TextureRef
{
public:
	~Rva00938C4TextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class W3DSnowManager : public SnowManager
{
public:
	virtual ~W3DSnowManager();
	virtual void init(); // slot 1, as W3DSnow.cpp's view
	void ReleaseResources();

private:
	void *m_indexBuffer; // +0x74
	Rva00938C4TextureRef m_snowTexture; // +0x78
};

W3DSnowManager::~W3DSnowManager()
{
	ReleaseResources();
}
