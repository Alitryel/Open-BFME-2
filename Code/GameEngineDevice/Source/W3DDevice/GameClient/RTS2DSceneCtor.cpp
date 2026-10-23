// ??0RTS2DScene@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0006F9D6, 154 bytes (EH). "RTS2DScene" is the setName string;
// donor is Zero Hour's RTS2DScene::RTS2DScene (W3DScene.cpp): setName,
// m_status = NEW_REF(W3DStatusCircle), Add_Render_Object(m_status).
// Bases follow the RTS3DScene ctor: matched SimpleSceneClass ctor 0x142960,
// SubsystemInterface at +0x108. W3DStatusCircle is the 0xE8-byte object
// built by the matched ctor at 0x8E54F. BFME 2 zeroes m_camera (+0x118)
// after the publish.
#include "ascii_string.h"

typedef unsigned int size_t;
void *operator new(size_t size);
void operator delete(void *p);

class RenderObjClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
private:
	int m_numRefs;
};

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
	char m_pad004[0x108 - 0x04];
};

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class W3DStatusCircle
{
public:
	W3DStatusCircle();
	char m_storage[0xE8];
};

class CameraClass;

class RTS2DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	RTS2DScene();
	virtual ~RTS2DScene();
protected:
	RenderObjClass *m_status;
	CameraClass *m_camera;
};

// The vtable this ctor emits needs the destructor. Retail's is the rowed
// 0x0006ED6F (Rva006ED6FDtor.cpp, same vftables 0x00BC62A0/+0x108); this inline
// copy has its body: remove and release the status object, then the bases.
inline RTS2DScene::~RTS2DScene()
{
	SimpleSceneClass::Remove_Render_Object(m_status);
	if (m_status)
	{
		m_status->Release_Ref();
		m_status = 0;
	}
}

RTS2DScene::RTS2DScene()
{
	setName("RTS2DScene");
	m_status = (RenderObjClass *)new W3DStatusCircle();
	Add_Render_Object(m_status);
	m_camera = 0;
}
