// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.9103003663003664 date=2026-10-16
// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.904 date=2026-10-15
// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.910443 date=2026-10-15
// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.9 date=2026-10-14
// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.5 date=2026-10-12
// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.863408111 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WW3D2 /ICode
// ZH dx8renderer.cpp Render semantic source; BFME1 revision9cbfb551fe20.
// WB9DAE60 names target148520 and source1383..1527. Native full1400B
// ends148A98 after dynamicVB cleanup13A780 (queue1379 cuts the call).
#include "vector3.h"
#include "vector2.h"
#include "vector.h"
#include "multilist.h"
struct S2Buffer {char pad[12];void*Data;};
struct S2MaterialDesc {
 char pad[12];unsigned UVCount;S2Buffer*UV[8];int UVIndex[2];char gap[0x18];S2Buffer *Colors[2];
 const Vector2*Get_UV_Array_By_Index(int n)const {
  S2Buffer*b;
  if(UVCount && n<2){int i=UVIndex[n];if(i==-1)return 0;b=UV[i];}else b=UV[n];
  if(b)return (Vector2*)b->Data;return 0;
 }
};
struct MeshPolygonCount
{
    int Count;
};

class MeshModelClass
{
public:
    unsigned char pad[0x24];
    int PassCount;
    int VertexCount;
    unsigned char pad1[0x94 - 0x2C];
    S2MaterialDesc *descriptor;MeshPolygonCount *PolygonCount;
    int Get_Vertex_Count() const
    { return VertexCount; }
    int Get_Pass_Count() const
    { return PassCount; }
    int Get_Polygon_Count() const
    { return PolygonCount->Count; }
};

class MeshClass {
public:
 virtual void vt0();virtual void vt4();virtual void vt8();virtual void vtC();virtual void vt10();virtual void vt14();virtual void vt18();virtual void vt1C();virtual void vt20();virtual void vt24();
 virtual int Get_Num_Polys()const;
 virtual void vt2C();virtual void vt30();virtual void vt34();virtual void vt38();virtual void vt3C();virtual void vt40();virtual void vt44();virtual void vt48();virtual void vt4C();virtual void vt50();virtual void vt54();virtual void vt58();virtual void vt5C();virtual void vt60();virtual float Get_Alpha()const;
 char pad[0xC4-4];MeshModelClass *Model;char gapC8[0x238];unsigned BaseVertexOffset;MeshClass*NextVisibleSkin;char gap308[8];MeshClass **Anchor;
 MeshModelClass*Peek_Model(){return Model;}unsigned Get_Base_Vertex_Offset(){return BaseVertexOffset;}void Set_Base_Vertex_Offset(unsigned v){BaseVertexOffset=v;}MeshClass*Peek_Next_Visible_Skin(){return NextVisibleSkin;}void Set_Next_Visible_Skin(MeshClass*m){NextVisibleSkin=m;}
 void Get_Deformed_Vertices(Vector3*,Vector3*);
};
struct VertexFormatXYZNDUV2 {float x,y,z,nx,ny,nz;unsigned diffuse;float u1,v1,u2,v2;};
class DynamicVBAccessClass {
public:
 void *format;unsigned type,index,declaration;unsigned short count,offset;void*buffer;
 DynamicVBAccessClass(unsigned,unsigned,unsigned short,unsigned);~DynamicVBAccessClass();
 class WriteLock {public:void*owner;VertexFormatXYZNDUV2 *vertices;char lock;WriteLock(DynamicVBAccessClass*);~WriteLock();VertexFormatXYZNDUV2*Get_Formatted_Vertex_Array()const{return vertices;}};
};
class VertexBufferClass;
class IndexBufferClass
{
public:
    unsigned char pad[0x0C];
    unsigned index_count;
    unsigned Get_Index_Count() const
    { return index_count; }
};


class DX8Wrapper {public:static void Set_Vertex_Buffer(const VertexBufferClass*,unsigned);static void Set_Vertex_Buffer(const DynamicVBAccessClass&);static void Set_Index_Buffer(const IndexBufferClass*,unsigned short);};
namespace Debug_Statistics {void Record_DX8_Skin_Polys_And_Vertices(int,int);}
class DX8TextureCategoryClass:public MultiListObjectClass {public:void Render();};
class MaterialPassClass;
class DX8FVFCategoryContainer {
public:
 void Add_Visible_Material_Pass(MaterialPassClass*,MeshClass*);
 virtual ~DX8FVFCategoryContainer();char pad[4];MultiListClass<DX8TextureCategoryClass> lists[4],visible[4];void *mathead,*mattail;IndexBufferClass*index_buffer;unsigned used_indices,FVF,passes;unsigned dynamic_fvf_type;bool sorting,AnythingToRender;
protected:
 bool Render_Procedural_Material_Passes();
};
class DX8SkinFVFCategoryContainer:public DX8FVFCategoryContainer {
public:
 unsigned VisibleVertexCount,rva_ec;MeshClass*VisibleSkinHead,*VisibleSkinTail;bool rva_f8;
 virtual void Render();
 virtual bool Check_If_Mesh_Fits(MeshModelClass*);virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass*,MeshClass*);void Add_Visible_Skin(MeshClass*);private:void clearVisibleSkinList();
};
typedef char BaseSize[(sizeof(DX8FVFCategoryContainer)==0xe8)?1:-1];
typedef char MeshSize[(sizeof(MeshClass)==0x314)?1:-1];
void DX8SkinFVFCategoryContainer::Render() {
 static DynamicVectorClass<Vector3> tempVertices;
 static DynamicVectorClass<Vector3> tempNormals;
 if(!AnythingToRender)return;
 AnythingToRender=false;
 DX8Wrapper::Set_Vertex_Buffer((const VertexBufferClass*)0,0);
 unsigned maxVertexCount=VisibleVertexCount;if(maxVertexCount>65535)maxVertexCount=65535;
 DynamicVBAccessClass vb(sorting?3:2,5,maxVertexCount,0);
 unsigned renderedVertexCount=0;
 MeshClass*mesh=VisibleSkinHead;
 MeshClass*remainingMesh=mesh;
 while(renderedVertexCount<VisibleVertexCount){
  mesh=remainingMesh;
  {
   DynamicVBAccessClass::WriteLock l(&vb);
   VertexFormatXYZNDUV2*dest_verts=l.Get_Formatted_Vertex_Array();
   unsigned vertex_offset=0;
   remainingMesh=0;
   while(mesh){
    MeshModelClass*mmc=mesh->Peek_Model();int mesh_vertex_count=mmc->VertexCount;
    if(vertex_offset+mesh_vertex_count>maxVertexCount || remainingMesh){mesh->Set_Base_Vertex_Offset(65535);if(!remainingMesh)remainingMesh=mesh;mesh=mesh->Peek_Next_Visible_Skin();continue;}
    if(mesh->Anchor && *mesh->Anchor){
     Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);
     mesh->Set_Base_Vertex_Offset((*mesh->Anchor)->Get_Base_Vertex_Offset());
     renderedVertexCount+=mesh_vertex_count;mesh=mesh->Peek_Next_Visible_Skin();continue;
    }
    Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);
    if(tempVertices.Length()<mesh_vertex_count)tempVertices.Resize(mesh_vertex_count);
    if(tempNormals.Length()<mesh_vertex_count)tempNormals.Resize(mesh_vertex_count);
    Vector3 *loc=&tempVertices[0],*norm=&tempNormals[0];
    const Vector2*uv0=mmc->descriptor->Get_UV_Array_By_Index(0);
    const Vector2*uv1=mmc->descriptor->Get_UV_Array_By_Index(1);
    const unsigned*diffuse=mmc->descriptor->Colors[0]?(unsigned*)mmc->descriptor->Colors[0]->Data:0;
    VertexFormatXYZNDUV2 *verts=dest_verts+vertex_offset;
    mesh->Get_Deformed_Vertices(loc,norm);
    for(int v=0;v<mesh_vertex_count;++v){
     verts[v].x=(*loc)[0];verts[v].y=(*loc)[1];verts[v].z=(*loc)[2];
     verts[v].nx=(*norm)[0];verts[v].ny=(*norm)[1];verts[v].nz=(*norm)[2];
     if(diffuse)verts[v].diffuse=*diffuse++;else verts[v].diffuse=0;
     if(uv0){verts[v].u1=uv0->X;verts[v].v1=uv0->Y;++uv0;}else {verts[v].u1=0.0f;verts[v].v1=0.0f;}
     if(uv1){verts[v].u2=uv1->X;verts[v].v2=uv1->Y;++uv1;}else {verts[v].u2=0.0f;verts[v].v2=0.0f;}
     ++loc;++norm;
    }
    float alpha=mesh->Get_Alpha();
    if(alpha<1.0f){unsigned a=(unsigned)(alpha*255.0f)<<24;for(int v=0;v<mesh_vertex_count;++v)verts[v].diffuse=(verts[v].diffuse&0xFFFFFF)|a;}
    mesh->Set_Base_Vertex_Offset(vertex_offset);
    if(mesh->Anchor)*mesh->Anchor=mesh;
    renderedVertexCount+=mesh_vertex_count;vertex_offset+=mesh_vertex_count;mesh=mesh->Peek_Next_Visible_Skin();
   }
  }
  DX8Wrapper::Set_Vertex_Buffer(vb);DX8Wrapper::Set_Index_Buffer(index_buffer,0);
  for(unsigned pass=0;pass<passes;++pass){MultiListIterator<DX8TextureCategoryClass> it(&visible[pass]);while(!it.Is_Done()){it.Peek_Obj()->Render();it.Next();}}
  Render_Procedural_Material_Passes();
  for(MeshClass*m=VisibleSkinHead;m;m=m->NextVisibleSkin)if(m->Anchor)*m->Anchor=0;
 }
 for(unsigned pass=0;pass<passes;++pass)while(visible[pass].Remove_Head()){}
 while(VisibleSkinHead){MeshClass*next=VisibleSkinHead->NextVisibleSkin;VisibleSkinHead->NextVisibleSkin=0;VisibleSkinHead=next;}
 VisibleSkinHead=0;VisibleSkinTail=0;VisibleVertexCount=0;rva_ec=0;
}

void DX8SkinFVFCategoryContainer::clearVisibleSkinList()
{
    while (VisibleSkinHead != NULL) {
        MeshClass *next = VisibleSkinHead->Peek_Next_Visible_Skin();
        VisibleSkinHead->Set_Next_Visible_Skin(NULL);
        VisibleSkinHead = next;
    }
    VisibleSkinHead = NULL;
    VisibleSkinTail = NULL;
    VisibleVertexCount = 0;
    rva_ec = 0;
}

void DX8SkinFVFCategoryContainer::Add_Visible_Skin(MeshClass *mesh)
{
    if (mesh->Peek_Next_Visible_Skin() != NULL || mesh == VisibleSkinTail)
        return;
    if (VisibleSkinHead == NULL)
        VisibleSkinTail = mesh;
    mesh->Set_Next_Visible_Skin(VisibleSkinHead);
    VisibleSkinHead = mesh;
    VisibleVertexCount += mesh->Peek_Model()->Get_Vertex_Count();
}

// ?Check_If_Mesh_Fits@DX8SkinFVFCategoryContainer@@UAE_NPAVMeshModelClass@@@Z
// Retail 0x00143C20, 54 bytes: slot 4 of the container vtable 0x007D3544, in
// Zero Hour's DX8FVFCategoryContainer order (~, Render, Add_Mesh, Log,
// Check_If_Mesh_Fits, then the two Delayed passes; the rigid container's table
// just before it has the same shape). Aligning that table against lotrbfme.exe
// names this slot DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits, and the body
// sits right before the rowed clearVisibleSkinList. It is Zero Hour's body
// minus the gap-filler branch, which BFME's skin container does not have
// (BFME1 matched the same shape at 55 bytes).
bool DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits(MeshModelClass* mmc)
{
    if (!index_buffer) return true;	// No IB created - mesh will fit as a new ib will be created when inserting
    int required_polygons=mmc->Get_Polygon_Count();

    if ((required_polygons*3*mmc->Get_Pass_Count())<=index_buffer->Get_Index_Count()-used_indices) {
        return true;
    }
    return false;
}

// ?Add_Delayed_Visible_Material_Pass@DX8SkinFVFCategoryContainer@@UAEXPAVMaterialPassClass@@PAVMeshClass@@@Z
// retail 0x001460B0, 5 bytes: slot 5 of the class's vtable. Zero Hour's
// dx8renderer.h defines it inline: skins route delayed passes straight into
// Add_Visible_Material_Pass (a tail jump).
void DX8SkinFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    Add_Visible_Material_Pass(pass, mesh);
}
