// ?rva00104BDA@Rva001041D8@@UAEXXZ
// partial score=0.83 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00104BDA@Rva001041D8@@UAEXXZ @0x00104BDA 409B
// vtable slot 1 of the 0x88-byte Rva001041D8 object whose dtor is
// 0x001041D8 and whose ctor 0x0010461F is rowed (Rva001041D8Dtor.cpp).
// Body: when the owned asset-registry pointer 0x00E099F8 is non-null, build a
// pointer set containing the "palantir" receiver and hand it to the rowed
// bfmeMarkReceiverPayloads; then create the "palantir" render object
// (Create_Render_Obj), give it the identity transform (RenderObjClass slot
// 21), allocate the 0x108-byte scene 0x001040D5 (base pin 0x00142960, vtable
// 0x00BCF6F0), set its ambient light (SceneClass slot 6, rowed 0x0006E265) and
// add the model (SimpleSceneClass slot 2, rowed 0x001413A0), allocate the
// 0x3FC-byte CameraClass (rowed ctor 0x00134AB0) and set its clip/view planes
// and aspect ratio, then call the rowed forwarder 0x002D55CA.
// Set ctor 0x000D3A71 / insert view 0x0006C995 / tree dtor 0x0006BF2A are the
// pinned pointer-set family. The Palantir identity is the dtor file's
// donor/structural lead; names stay address-derived.
#include <set>

class Rva009EB960;
// Owned by W3DDisplayDtor.cpp: the asset registry the W3DDisplay dtor deletes.
extern Rva009EB960 *Rva0134FAA0;

struct Rva001408C0Target
{
	int opaque;
};

typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > PtrSet001408C0;

class Rva0006C995
{
public:
	Rva0006C995() : m_zero0C(0), m_flag(true) {}
	Rva0006C995 *rva0006C995(Rva001408C0Target *p);

private:
	PtrSet001408C0 m_set;
	int m_zero0C;
	bool m_flag;
};

void bfmeMarkReceiverPayloads(int value);

struct Vector3
{
	float x, y, z;
};

struct Matrix3D
{
	float m[3][4];
};

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void Set_Transform(const Matrix3D &m); // slot 21 (+0x54)
};

RenderObjClass *Create_Render_Obj(const char *name);

class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();
};

class Rva001040D5 : public Rva00142960Base
{
public:
	Rva001040D5() {}
	virtual ~Rva001040D5();
	virtual void slot01();
	virtual void Add_Render_Object(RenderObjClass *obj); // slot 2 (+0x08)
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void Set_Ambient_Light(const Vector3 &v); // slot 6 (+0x18)
private:
	char m_rest[0x104];
};

class CameraClass
{
public:
	CameraClass();
	void Set_Clip_Planes(float nearz, float farz);
	void Set_View_Plane(float horizontal, float vertical);
	void Set_Aspect_Ratio(float ratio);
};

class Rva002D55CAForwarder
{
public:
	void rva002D55CA();
};

class Rva001041D8
{
public:
	virtual void rva00104BDA();

private:
	char m_pad00[0x10];
	Rva001040D5 *m_scene;
	CameraClass *m_camera;
	RenderObjClass *m_model;
};

void Rva001041D8::rva00104BDA()
{
	Rva001041D8 *self = this;
	const char *name = "palantir";
	if (Rva0134FAA0 != 0)
	{
		Rva0006C995 receivers;
		receivers.rva0006C995((Rva001408C0Target *)(const void *)name);
		bfmeMarkReceiverPayloads((int)&receivers);
	}

	RenderObjClass *model = Create_Render_Obj(name);
	self->m_model = model;
	if (model != 0 && (RenderObjClass *)self->m_model == model)
	{
		Matrix3D transform = { 1.0f, 0.0f, 0.0f, 0.0f,
		                       0.0f, 1.0f, 0.0f, 0.0f,
		                       0.0f, 0.0f, 1.0f, 0.0f };
		model->Set_Transform(transform);
	}

	Rva001040D5 *scene = new Rva001040D5;
	self->m_scene = scene;
	Vector3 ambient = { 0.0f, 0.0f, 0.0f };
	scene->Set_Ambient_Light(ambient);
	if (self->m_model != 0)
		scene->Add_Render_Object(self->m_model);

	CameraClass *camera = new CameraClass;
	self->m_camera = camera;
	camera->Set_Clip_Planes(0.1f, 5000.0f);
	camera->Set_View_Plane(0.87266463f, -1.0f);
	camera->Set_Aspect_Ratio(1.0f);

	((Rva002D55CAForwarder *)self)->rva002D55CA();
}
