// ?Add_Rendering_Task@Rva00DF6F94GapFillerContext@@QAEXV?$RefCountPtr@VMeshClass@@@@ABV?$vector@V?$RefCountPtr@VRenderingMethod@FXShader@@@@V?$allocator@V?$RefCountPtr@VRenderingMethod@FXShader@@@@@_STL@@@_STL@@@Z
// partial score=0.85 date=2026-10-14
// ?Add_Rendering_Task@Rva00DF6F94GapFillerContext@@QAEXV?$RefCountPtr@VMeshClass@@@@ABV?$vector@V?$RefCountPtr@VRenderingMethod@FXShader@@@@V?$allocator@V?$RefCountPtr@VRenderingMethod@FXShader@@@@@_STL@@@_STL@@@Z
// partial score=0.8 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Add_Rendering_Task@Rva00DF6F94GapFillerContext@@QAEXV?$RefCountPtr@VMeshClass@@@@ABV?$vector@...@Z @0x00174AAD 249B
// FXShaderRenderer::Add_Rendering_Task (WorldBuilder assert string; the address-derived context class name
// stays until the ledger rename lands): queues a mesh with its rendering-method stack. A stack of more than six
// methods is dropped. Otherwise the mesh's light environment picks one of the context's three 32-byte-record
// queues (+0 plain; +0xC when the environment's +0x19 bit 2 is set and the byte behind its +0xBC is nonzero; +0x18
// when the bit is set and that byte is zero); a record {mesh, method count, up to six methods} is appended
// through the rowed grower 0x00174A8A and filled with the rowed holder assignment 0x00072A94. The by-value mesh
// pointer is released on exit. Evidence: target bytes; callee MeshClass::Render 0x0014BB90 (MeshClassRender.cpp)
// and the three-queue layout of Rva00DF6F94GapFillerContext (MeshGapFillerFlush.cpp). Field names are structural.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>

class DummyPtrType;

class RefCountClass
{
public:
	virtual void Delete_This(void);
	__forceinline void Add_Ref(void) { NumRefs++; }
	__forceinline void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}
	~RefCountPtr(void)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}
	T *volatile Referent;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
};
}

struct Rva00174AADLightEnv
{
	char m_pad00[0x19];
	unsigned char m_flags19;
	char m_pad1A[0xBC - 0x1A];
	unsigned char *m_ptrBC;
};

class MeshClass : public RefCountClass
{
public:
	char m_pad08[0xC4 - 0x08];
	Rva00174AADLightEnv *m_lightEnv;
};

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

// The rowed holder assignment (0x00072A94) the record fill goes through.
class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &other);
private:
	RefCountClass *m_ptr;
};

struct Rva00174AADRecord
{
	Rva00072A94 mesh;
	int count;
	Rva00072A94 methods[6];
};

struct Rva00174AADQueue
{
	Rva00174AADRecord *m_begin;
	Rva00174AADRecord *m_end;
	Rva00174AADRecord *m_limit;
};

class Rva00174A8A
{
public:
	void rva00174A8A(int n);
};

class Rva00DF6F94GapFillerContext
{
public:
	void Add_Rendering_Task(RefCountPtr<MeshClass> mesh, const RenderingMethodStackType &renderingMethodStack);

private:
	Rva00174AADQueue m_plain;	// +0
	Rva00174AADQueue m_second;	// +0xC
	Rva00174AADQueue m_third;	// +0x18
};

void Rva00DF6F94GapFillerContext::Add_Rendering_Task(RefCountPtr<MeshClass> mesh, const RenderingMethodStackType &renderingMethodStack)
{
	if (renderingMethodStack.size() <= 6)
	{
		Rva00174AADRecord *record;
		_ReadWriteBarrier();
		Rva00174AADLightEnv * volatile env = mesh.Referent->m_lightEnv;
		if (env->m_flags19 & 4)
		{
			if (*env->m_ptrBC)
			{
				record = m_second.m_end - 1;
				((Rva00174A8A *)&m_second)->rva00174A8A((int)(m_second.m_end - m_second.m_begin) + 1);
			}
			else
			{
				((Rva00174A8A *)&m_third)->rva00174A8A((int)(m_third.m_end - m_third.m_begin) + 1);
				record = m_third.m_end - 1;
			}
		}
		else
		{
			((Rva00174A8A *)&m_plain)->rva00174A8A((int)(m_plain.m_end - m_plain.m_begin) + 1);
			record = m_plain.m_end - 1;
		}
		record->mesh = *(const Rva00072A94 *)&mesh;
		record->count = (int)renderingMethodStack.size();
		for (unsigned int i = 0; i < renderingMethodStack.size(); ++i)
			record->methods[i] = *(const Rva00072A94 *)&renderingMethodStack[i];
	}
}
