// ?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z
// partial score=0.79529 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// Target-only first reconstruction: native18C84E..18D16B and WB A39110.
// WB supplies Init identity and algorithm; all offsets below are native.
// BfmeFVFDescriptor is the existing dx8fvf.cpp 96-byte target descriptor.
// Container specialization/link reconciliation is deliberately unclaimed.
#include <vector>
#include <set>
#include <string.h>
class Vector3 {public:float x,y,z;Vector3 &operator=(const Vector3 &v){x=v.x;y=v.y;z=v.z;return *this;}};
class Vector2 {public:float x,y;};
class FxEffectView {
public:
#define V(n) virtual void slot##n();
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18)
 virtual void *__stdcall GetAnnotationByName(void *,const char *);
 V(20) V(21) V(22) V(23) V(24) V(25) V(26)
 virtual long __stdcall GetInt(void *,int *);
#undef V
};
class TextureBaseClass {public:void Release_Ref();};
class Rva0015148D {public:void *rva0015148D();};
class AssetReference {
public:
 void *p;AssetReference(const AssetReference &);
 ~AssetReference(){if(p)static_cast<TextureBaseClass*>(p)->Release_Ref();}
 Rva0015148D *operator->()const{return static_cast<Rva0015148D*>(p);}
};
class Rva0007B9EE {public:AssetReference rva0007B9EE();char pad[0x20];void *technique;};
template<class T>struct FxSharedBuffer {char pad[12];T *data;};
class MeshMatDescClass {
public:
 Vector2 *Get_UV_Array_By_Index(int,bool);
 char pad00[0x50];FxSharedBuffer<unsigned> *colors;char pad54[0xa8-0x54];void *materialArray;
 char padac[0xb8-0xac];Rva0007B9EE *setup;char padbc[0xe8-0xbc];void *shaderArray;
};
class FXShaderGeometry;
class MeshGeometryClass {
 friend class FXShaderGeometry;
protected:unsigned short *get_bone_links(bool);
public:
 const char *Get_Name()const;int rva0018C088()const;
 const Vector3 *Get_Vertex_Normal_Array(bool);Vector3 *rva0016ABC0();Vector3 *rva0016ABE0();
 char pad0[0x18];unsigned flags;char pad1c[8];int polygonCount,vertexCount;
 FxSharedBuffer<unsigned short> *triangles;FxSharedBuffer<Vector3> *vertices,*secondVertices;
 char pad38[0x94-0x38];MeshMatDescClass *material;
};
class MeshModelClass:public MeshGeometryClass {};
class DX8FVFCategoryContainer {public:static unsigned Define_FVF(MeshModelClass*,bool);};
class BfmeFVFDescriptor {
public:
 unsigned fvf;bool basis;unsigned count,stride,position,secondPosition,normal,secondNormal,blend;
 unsigned tex[8],diffuse,specular,tangent,binormal,indices,weights,last;
 BfmeFVFDescriptor(unsigned,unsigned,bool,unsigned);void *rva001818C0();
};
typedef char FxDescriptorSize[sizeof(BfmeFVFDescriptor)==0x60?1:-1];
class VertexBufferClass {public:class WriteLockClass {public:VertexBufferClass *buffer;char *data;char lock;WriteLockClass(VertexBufferClass *,int);~WriteLockClass();};};
class BfmeDynamicNativeVB:public VertexBufferClass {char bytes[0x20];public:BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);};
class IndexBufferClass {public:class WriteLockClass {public:IndexBufferClass *buffer;unsigned short *data;char lock;WriteLockClass(IndexBufferClass *,int);~WriteLockClass();};};
class DX8IndexBufferClass:public IndexBufferClass {char bytes[0x18];public:enum UsageType {STATIC=0};DX8IndexBufferClass(unsigned,UsageType);};
class FxBatchCountView {public:virtual int getCount(const char *);};
extern int g_00DFCEBC;
class Debug;extern Debug *theDebug;
class FxDebugView {
public:
#define V(n) virtual void slot##n();
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
 virtual FxDebugView &putUnsigned(unsigned);virtual FxDebugView &putInt(int);virtual FxDebugView &putText(const char *);
 V(15) V(16) V(17) V(18)
 virtual void end(int);V(20) V(21) V(22) V(23)
 virtual void ignored();V(25) V(26)
 virtual FxDebugView &start(int,int,int);
#undef V
};
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
class Rva0018C6D5 {public:void rva0018C6D5(const unsigned short*,const unsigned short*);};
struct Rva005E59FCKeyIterator {_STL::_Rb_tree_node_base *node;};
class Rva0018C73CWordVector {public:void assign(Rva005E59FCKeyIterator,Rva005E59FCKeyIterator,const _STL::forward_iterator_tag &);};
class Rva0018C7E5Vector {public:void resize(unsigned,unsigned short);};
class FXShaderGeometry {
public:
 bool Init(MeshModelClass *mesh);
 void rva0018C131(FxEffectView *,void *,unsigned *,bool *);
 bool softwareSkinning;unsigned fvf;void *declaration;VertexBufferClass *vertexBuffer;IndexBufferClass *indexBuffer;
 std::vector<short> bones;int influences,copies;
};
bool FXShaderGeometry::Init(MeshModelClass *mesh)
{
 vertexBuffer=0;indexBuffer=0;declaration=0;bones.clear();influences=0;copies=0;
 MeshMatDescClass *mat=mesh->material;
 if(!mat->setup || mat->materialArray || mat->shaderArray)return false;
 FxEffectView *effect=(FxEffectView*)mat->setup->rva0007B9EE()->rva0015148D();
 if(!effect)return false;
 void *technique=mat->setup->technique;
 int maxBones=0;
 void *annotation=effect->GetAnnotationByName(technique,"MaxSkinningBones");
 if(annotation && effect->GetInt(annotation,&maxBones)<0)maxBones=0;
 bool skinned=(mesh->flags&0x400)!=0;
 if(skinned){
  softwareSkinning=true;
  if(maxBones>0){
   unsigned short *links=mesh->get_bone_links(true);
   if(links){
    int linkCount=mesh->rva0018C088()*mesh->vertexCount;
    std::set<short> unique;
    ((Rva0018C6D5*)&unique)->rva0018C6D5(links,links+linkCount);
    if(unique.size()<=(unsigned)maxBones){
     softwareSkinning=false;
     Rva005E59FCKeyIterator first={unique.begin()._M_node},last={unique.end()._M_node};
     ((Rva0018C73CWordVector*)&bones)->assign(first,last,_STL::forward_iterator_tag());
    } else if(bfmeRva000387C0()){
     _bfme_debugRecordCallsite(1);
     ((FxDebugView*)theDebug)->ignored();
     ((FxDebugView*)theDebug)->start(0,0,0).putText("Cannot do shader skinning on model: ").putText(mesh->Get_Name()).putText(". Has ").putUnsigned(unique.size()).putText(" bones, maximum is ").putInt(maxBones).putText(".").end(2);
    }
   }
  }
 }else softwareSkinning=false;
 if(!skinned && g_00DFCEBC && maxBones>1 && !(mesh->flags&0xa00)){
  copies=((FxBatchCountView*)g_00DFCEBC)->getCount(mesh->Get_Name());
  copies=std::min((int)copies,maxBones);
  if(mesh->vertexCount*copies>65000)copies=65000/mesh->vertexCount;
  if(mesh->polygonCount*copies*3>65000)copies=65000/(mesh->polygonCount*3);
  copies=std::max((int)copies,1);
 }else copies=1;
 fvf=0;bool basis=false;
 if(!softwareSkinning){
  rva0018C131(effect,technique,&fvf,&basis);
  if(!fvf)fvf=DX8FVFCategoryContainer::Define_FVF(mesh,true)|0x10;
  if(skinned)influences=mesh->rva0018C088();else if(copies>1)influences=1;
 }else fvf=0x252;
 BfmeFVFDescriptor info(fvf,0,basis,influences);
 if(!softwareSkinning){
  if(!info.basis && !info.count)vertexBuffer=new BfmeDynamicNativeVB(fvf,(unsigned short)(mesh->vertexCount*copies),0,0);
  else {declaration=info.rva001818C0();vertexBuffer=new BfmeDynamicNativeVB(0,(unsigned short)(mesh->vertexCount*copies),0,info.stride);}
  VertexBufferClass::WriteLockClass lock(vertexBuffer,0);
  char *dst=lock.data;
  const Vector3 *vertices=mesh->vertices->data,*secondVertices=0;
  const Vector3 *normals=mesh->Get_Vertex_Normal_Array(false),*secondNormals=0;
  const Vector3 *tangents=mesh->rva0016ABC0(),*binormals=mesh->rva0016ABE0();
  unsigned *colors=mesh->material->colors?mesh->material->colors->data:0;
  unsigned textureCount=(fvf>>8)&15;
  unsigned short *links=mesh->get_bone_links(true),*secondLinks=0,*weights0=0,*weights1=0;
  if(influences>1){secondLinks=links+mesh->vertexCount;weights0=secondLinks+mesh->vertexCount;weights1=weights0+mesh->vertexCount;secondVertices=mesh->secondVertices->data;secondNormals=mesh->Get_Vertex_Normal_Array(true);}
  std::vector<short> remap;
  if(!bones.empty() && links){
   ((Rva0018C7E5Vector*)&remap)->resize(bones.back()+1,0);
   int i=0;for(std::vector<short>::const_iterator it=bones.begin();it!=bones.end();++it,++i)remap[*it]=(short)i;
  }
  for(unsigned copy=0;copy<copies;++copy){
   for(unsigned v=0;v<(unsigned)mesh->vertexCount;++v){
    *(Vector3*)(dst+info.position)=vertices[v];
    if(fvf&0x10)*(Vector3*)(dst+info.normal)=normals[v];
    if(fvf&0x40)*(unsigned*)(dst+info.diffuse)=colors?colors[v]:~0u;
    for(int t=0;t<(int)textureCount;++t){Vector2 *uv=mesh->material->Get_UV_Array_By_Index(t,false);if(uv)*(Vector2*)(dst+info.tex[t])=uv[v];}
    if(basis){if(tangents)*(Vector3*)(dst+info.tangent)=tangents[v];if(binormals)*(Vector3*)(dst+info.binormal)=binormals[v];}
    if(copies>1)*(unsigned*)(dst+info.indices)=copy;
    else if(influences>0 && links){
     if(influences==1)*(int*)(dst+info.indices)=remap[links[v]];
     else if(influences==2){
      *(int*)(dst+info.indices)=remap[links[v]]+(remap[secondLinks[v]]<<8);
      Vector2 weight;weight.x=weights0[v]*0.01f;weight.y=weights1[v]*0.01f;*(Vector2*)(dst+info.weights)=weight;
      if(secondVertices)*(Vector3*)(dst+info.secondPosition)=secondVertices[v];
      if(secondNormals)*(Vector3*)(dst+info.secondNormal)=secondNormals[v];
     }
    }
    dst+=info.stride;
   }
  }
 }
 indexBuffer=new DX8IndexBufferClass(mesh->polygonCount*3*copies,DX8IndexBufferClass::STATIC);
 IndexBufferClass::WriteLockClass lock(indexBuffer,0);
 unsigned short *indices=mesh->triangles->data,*dst=lock.data;
 memcpy(dst,indices,mesh->polygonCount*6);dst+=mesh->polygonCount*3;
 for(unsigned copy=1;copy<copies;++copy){
  int offset=mesh->vertexCount*copy;
  for(unsigned p=0;p<(unsigned)mesh->polygonCount;++p){dst[0]=indices[p*3]+offset;dst[1]=indices[p*3+1]+offset;dst[2]=indices[p*3+2]+offset;dst+=3;}
 }
 return true;
}
