// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme_projection_matrix_link /Ireference/shims/bfme_vp_math /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Rebase note: upstream d7b143eb97 retains the earlier 0.866 near-match in
// history; this bank preserves the whole2821B byte/EH-exact canonical-owner body.
// Copyright 2025 Electronic Arts Inc. SPDX-License-Identifier: GPL-3.0-or-later
//
// Native sentence-renderer operation 0x00118F50..0x00119A55, 2821 bytes.
// The existing 0x00155AD0 caller iterates renderer pointers at sentence+0x38.
// Retail proves the packed 44-byte vertex and 16-bit index arrays, owning
// texture at renderer+0x40, global bindings, device calls and full EH graph.
// ZH render2d.cpp Render2DClass::Render is the semantic source; WB9C07A0 is a
// callgraph lead, not proof that this older layout has that original name.
// Keep the independently pinned Rva00118F50 entry and its measured layout.
//
// Two named transpose results and a temporary final texture reference give
// retail's lifetimes and 0x118-byte frame. ComposeShader preserves the native
// two-word evaluation order; no volatile local or new code/data pin is used.
// Existing data owners are declared with their actual types/access so this
// consumer does not introduce separate globals at the same retail addresses.
// BFME1 semantic inputs remain at verified pointer5bb8ca80ae66.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <string.h>
#include "vector4.h"
#include "matrix4.h"
class DynamicVBAccessClass {
public:
    DynamicVBAccessClass(unsigned,unsigned,unsigned short,unsigned);
    ~DynamicVBAccessClass();
    unsigned char native[24];
    class WriteLock {
    public:
        WriteLock(DynamicVBAccessClass*);~WriteLock();
        DynamicVBAccessClass*owner;void *data;char guard[4];
    };
};
class DynamicIBAccessClass {
public:
    DynamicIBAccessClass(unsigned short,unsigned short);~DynamicIBAccessClass();
    unsigned char native[12];
    class WriteLockClass {
    public:
        WriteLockClass(DynamicIBAccessClass*);~WriteLockClass();
        DynamicIBAccessClass*owner;unsigned short *data;char guard[4];
    };
};
class VertexMaterialClass {
public:
    virtual void Delete_This();
    int references;
    enum PresetType { PRELIT_DIFFUSE };
    static VertexMaterialClass *Get_Preset(PresetType);
    __declspec(dllimport) __forceinline void Add_Ref() {++references;}
    __declspec(dllimport) __forceinline void Release_Ref() {if(--references==0) Delete_This();}
};
class TextureBaseClass {public:void Release_Ref();};
typedef TextureBaseClass BFME2TextureResource;
struct BFME2TextureRef {
    BFME2TextureResource*texture;
    __declspec(dllimport) __forceinline BFME2TextureRef():texture(0) {}
    __forceinline ~BFME2TextureRef() {if(texture)texture->Release_Ref();}
};
void BFME2Set_Texture(unsigned,const BFME2TextureRef&);
class StringClass {
public:
    __declspec(dllimport) __forceinline StringClass(int length,bool isTemp) {m_Buffer=m_EmptyString;Get_String(length,isTemp);m_Buffer[0]=m_LeadByte;}
    ~StringClass() {Free_String();}
    private:
    char *m_Buffer;
    static char*m_EmptyString;static char m_LeadByte;
    void Get_String(int,bool);void Free_String();
};
extern int BfmeRenderWidth,BfmeRenderHeight;
#define renderDeviceWidth ((unsigned)BfmeRenderWidth)
#define renderDeviceHeight ((unsigned)BfmeRenderHeight)
extern int g_Va00DB5FC0,g_Va00DB5FC4,g_Va00DB5FBC;
extern unsigned g_Va00DEC4A0,g_Va00DEC4A4;
#define render2DSrcBlend ((unsigned)g_Va00DB5FC0)
#define render2DDstBlend ((unsigned)g_Va00DB5FC4)
#define render2DShaderBits ((unsigned)g_Va00DB5FBC)
#define render2DExtraShaderBits g_Va00DEC4A0
#define render2DShaderAlphaFlag g_Va00DEC4A4
struct _D3DVIEWPORT8 {unsigned X,Y,Width,Height;float MinZ,MaxZ;};
struct IDirect3DDevice8 { void **vtable; };
struct RenderStateStruct { unsigned shader;VertexMaterialClass*material;unsigned char unmodelled[0x1EC-8];Matrix4 world,view; };
extern Matrix4 g_mapperProjectionUpload_009EDBF0;
class ShaderClass { protected: static bool ShaderDirty; friend class DX8Wrapper; };
class DX8Wrapper {
public:
    static void Set_Viewport(const _D3DVIEWPORT8*);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
    static void Set_Index_Buffer(const DynamicIBAccessClass&,unsigned short);
    static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
protected:
    static unsigned render_state_changed;
    static RenderStateStruct render_state;
    static Matrix4 ProjectionMatrix;
    static float ZFar,ZNear;
    static IDirect3DDevice8 *D3DDevice;
    static unsigned matrix_changes;
    friend class Rva00118F50;
public:
    static __forceinline void SetMaterial(VertexMaterialClass*m) {
        if(m)m->Add_Ref();
        if(render_state.material)render_state.material->Release_Ref();
        render_state.material=m;render_state_changed|=0x4000;
    }
    static __declspec(dllimport) __forceinline void GetView(Matrix4&m) {if(render_state_changed&0x80000)m.Make_Identity();else {const Matrix4 &src=render_state.view;m[0][0]=src[0][0];m[0][1]=src[1][0];m[0][2]=src[2][0];m[0][3]=src[3][0];m[1][0]=src[0][1];m[1][1]=src[1][1];m[1][2]=src[2][1];m[1][3]=src[3][1];m[2][0]=src[0][2];m[2][1]=src[1][2];m[2][2]=src[2][2];m[2][3]=src[3][2];m[3][0]=src[0][3];m[3][1]=src[1][3];m[3][2]=src[2][3];m[3][3]=src[3][3];}}
    static __forceinline void GetProjection(Matrix4&m) {const Matrix4 &src=g_mapperProjectionUpload_009EDBF0;m[0][0]=src[0][0];m[0][1]=src[1][0];m[0][2]=src[2][0];m[0][3]=src[3][0];m[1][0]=src[0][1];m[1][1]=src[1][1];m[1][2]=src[2][1];m[1][3]=src[3][1];m[2][0]=src[0][2];m[2][1]=src[1][2];m[2][2]=src[2][2];m[2][3]=src[3][2];m[3][0]=src[0][3];m[3][1]=src[1][3];m[3][2]=src[2][3];m[3][3]=src[3][3];}
    static __forceinline void SetWorldIdentity() {if(!(render_state_changed&0x40000)){render_state.world.Make_Identity();render_state_changed|=0x40001;}}
    static __forceinline void SetViewIdentity() {if(!(render_state_changed&0x80000)){render_state.view.Make_Identity();render_state_changed|=0x80002;}}
    static __forceinline void SetProjection(const Matrix4&m) {
        Matrix4 transposed=m.Transpose();ProjectionMatrix=transposed;g_mapperProjectionUpload_009EDBF0=ProjectionMatrix;ZFar=0.0f;ZNear=0.0f;
        typedef long(__stdcall *SetTransform)(IDirect3DDevice8*,unsigned,const Matrix4*);
        ((SetTransform)D3DDevice->vtable[0xB0/4])(D3DDevice,3,&g_mapperProjectionUpload_009EDBF0);++matrix_changes;
    }
    static __forceinline void SetView(const Matrix4&m) {Matrix4 transposed=m.Transpose();render_state.view=transposed;render_state_changed&=~0x80000;render_state_changed|=2;}
    static __forceinline void SetShader(unsigned shader) {
        if(!ShaderClass::ShaderDirty && shader==render_state.shader)return;
        render_state.shader=shader;render_state_changed|=0x8000;
        StringClass text(0,false);
    }
};
struct Render2DRawArray {void *Data;unsigned Size,Count;int GrowthStep;};
class Rva00118F50 {
public:
    void rva00118F50();
private:
    unsigned shader;float scale[2],offset[2];Render2DRawArray vertices,indices;
    char batches[12];BFME2TextureRef texture;
};
// ?<ComposeShader> absent-from-retail
static __forceinline unsigned ComposeShader(unsigned state,unsigned extra) { return state | (extra<<3); }
void Rva00118F50::rva00118F50() {
    if(vertices.Count) {
    Matrix4 view,proj;
    _ReadWriteBarrier();
    DX8Wrapper::GetView(view);DX8Wrapper::GetProjection(proj);
    _D3DVIEWPORT8 vp={0,0,renderDeviceWidth,renderDeviceHeight,0.0f,1.0f};
    DX8Wrapper::Set_Viewport(&vp);
    VertexMaterialClass*vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::SetMaterial(vm);if(vm)vm->Release_Ref();
    DX8Wrapper::SetWorldIdentity();DX8Wrapper::SetViewIdentity();
    DX8Wrapper::ProjectionMatrix.Make_Identity();g_mapperProjectionUpload_009EDBF0.Make_Identity();DX8Wrapper::ZFar=0.0f;DX8Wrapper::ZNear=0.0f;
    typedef long(__stdcall *SetTransform)(IDirect3DDevice8*,unsigned,const Matrix4*);
    ((SetTransform)DX8Wrapper::D3DDevice->vtable[0xB0/4])(DX8Wrapper::D3DDevice,3,&g_mapperProjectionUpload_009EDBF0);++DX8Wrapper::matrix_changes;
    // Keep the native DWORD count argument loads; the equivalent conditional
    // preserves MSVC 7.1's argument lowering for these WORD-parameter ABIs.
    DynamicVBAccessClass vb(2,5,(vertices.Count ? vertices.Count : vertices.Count),0);
    DynamicIBAccessClass ib(2,(indices.Count ? indices.Count : indices.Count));
    {
        DynamicVBAccessClass::WriteLock vblock(&vb);
        memcpy(vblock.data,vertices.Data,vertices.Count*44);
        DynamicIBAccessClass::WriteLockClass iblock(&ib);
        memcpy(iblock.data,indices.Data,indices.Count*2);
    }
    DX8Wrapper::Set_Vertex_Buffer(vb);DX8Wrapper::Set_Index_Buffer(ib,0);
    BFME2Set_Texture(0,texture);
    DX8Wrapper::SetShader(ComposeShader(
    ((render2DShaderBits & 0xFFFF3F1F) | (((render2DSrcBlend<<9)|render2DDstBlend)<<5)) &0xFFFFF8FF,
    (render2DExtraShaderBits&0xFFFE6703) | (render2DShaderAlphaFlag<<15) |0x22302));
    DX8Wrapper::Draw_Triangles(0,indices.Count/3,0,vertices.Count);
    DX8Wrapper::SetView(view);DX8Wrapper::SetProjection(proj);
    BFME2Set_Texture(0,BFME2TextureRef());
}
}



// Sentence-level dispatch, retained with its existing 47-byte row.
class Rva00154FD0
{
public:
	void rva00154FD0();
};

void __cdecl Rva00118810();
void __cdecl Rva001188A0();

struct Rva00155AD0Entry
{
	Rva00118F50 *obj;
	void *second;
};

class Rva00155AD0
{
public:
	void rva00155AD0();
private:
	char m_pad[0x38];
	Rva00155AD0Entry *m_array; // +0x38
	char m_pad2[8]; // +0x3C
	int m_count; // +0x44
};

void Rva00155AD0::rva00155AD0()
{
	((Rva00154FD0 *)this)->rva00154FD0();
	Rva00118810();
	for (int i = 0; i < m_count; ++i) {
		m_array[i].obj->rva00118F50();
	}
	Rva001188A0();
}
