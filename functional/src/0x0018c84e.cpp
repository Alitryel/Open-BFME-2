// ?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z
// partial score=0.986 date=2026-10-17
// ?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z
// partial score=0.9935589632 date=2026-10-15
// W7-D1 r10 checkpoint: whole 2333B body; raw instruction diff12; EH EXACT.
// The former bank's dummy assign is replaced by the real 169B provider from
// Code/GameEngine/Source/Common/Rva0018C705AllocateCopy.cpp at 646a9870ce19118752904649d4ffac99cb9677e9.
// Visible vector-base/alloc-proxy constructors implement the vendored STLport
// initialization; same-object full29B/11B and the base's proxy relocation equal
// retail211E58 and its actual callee. Their short instantiation still needs
// ordinary fold admission before landing this parent; no pins were invented.
// Target frame10C and every slot are restored by one padding byte on the
// inline IndexBuffer WriteLock wrapper. The nested dead AsciiString scope
// after the VB lock reproduces the retail null-action EH state5.
// Remaining: normal-X pointer-load order; 2-bone remap load/allocation order;
// four SIB base/index orders. No nonmatching Code edit is retained.
// ?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z
// partial score=0.95 date=2026-10-14
// cl: /I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native18C131..18C262 RET16. Original helper name unknown. FXShaderGeometry::Init supplies this + four
// stack arguments: effect, technique handle, FVF output and basis flag.
// D3DXGetShaderInputSemantics is the owned stdcall12 PE thunk 62AFC2.
// Descriptor extents/fields and usage branches come from target accesses.
// These are narrow effect API views; no complete effect object layout is claimed.
// The 64-record stack array and reference binding preserve native SIB loads.
// Texture-count min/max use reference semantics to retain native address selection.
struct FxTechniqueDesc {const char *name;unsigned passes,annotations;};
struct FxPassDesc {const char *name;unsigned annotations;const unsigned long *vertexShader,*pixelShader;};
struct FxShaderSemantic {unsigned usage,index;};
extern "C" long __stdcall D3DXGetShaderInputSemantics(const unsigned long *,FxShaderSemantic *,unsigned *);
class FxEffectView {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual long __stdcall GetTechniqueDesc(void *,FxTechniqueDesc *);
 virtual long __stdcall GetPassDesc(void *,FxPassDesc *);
 virtual void slot07();virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();
 virtual void *__stdcall GetPass(void *,unsigned);
 virtual void slot15();virtual void slot16();virtual void slot17();virtual void slot18();
 virtual void *__stdcall GetAnnotationByName(void *,const char *);
 virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();virtual void slot24();virtual void slot25();virtual void slot26();
 virtual long __stdcall GetInt(void *,int *);
};
// Init 18C84E..18D169 support views. Field offsets come from Init's own accesses.
#include <string.h>
#include "reference/shims/bfme2_ascii/ascii_string.h"
#include "reference/shims/wwmath/Vector2.h"
void free(void *);
namespace _STL {
template<class T> class allocator {public:allocator() {} T *allocate(unsigned int,const void *) const;};
template<class T> struct less {};
struct input_iterator_tag {};
struct forward_iterator_tag:input_iterator_tag {};
template<class T> inline const T &min(const T &a,const T &b) {return b<a?b:a;}
template<class T> inline const T &max(const T &a,const T &b) {return a<b?b:a;}
struct _Rb_tree_node_base {int _M_color;_Rb_tree_node_base *_M_parent,*_M_left,*_M_right;};
template<class K,class C,class A> class set {
public:
 set();
 unsigned size() const {return _M_node_count;}
 _Rb_tree_node_base *_M_header;
 unsigned _M_node_count;
 C _M_key_compare;
};
template<class T> class reverse_iterator {
public:
 explicit reverse_iterator(T *x):current(x) {}
 T &operator*() const {T *tmp=current;return *--tmp;}
protected:
 T *current;
};
template<class Value,class T,class A> class _STLP_alloc_proxy:public A {
public:
 __declspec(noinline) _STLP_alloc_proxy(const A &a,Value p):A(a),_M_data(p) {}
 Value _M_data;
};
template<class T,class A> class _Vector_base {
public:
 __declspec(noinline) _Vector_base(const A &a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
 ~_Vector_base() {if(_M_start) free(_M_start);}
 T *_M_start,*_M_finish;
 _STLP_alloc_proxy<T*,T,A> _M_end_of_storage;
};
template<class T,class A=allocator<T> > class vector:public _Vector_base<T,A> {
public:
 vector(const A &a=A()):_Vector_base<T,A>(a) {}
 T *begin() {return this->_M_start;}
 T *end() {return this->_M_finish;}
 bool empty() {return begin()==end();}
 reverse_iterator<T> rbegin() {return reverse_iterator<T>(end());}
 T &operator[](unsigned n) {return *(begin()+n);}
 T *erase(T *,T *);
 void clear() {erase(begin(),end());}
};
}
template _STL::_Vector_base<short,_STL::allocator<short> >::_Vector_base(const _STL::allocator<short>&);
// Bone set: header +0, node count +4; destroyed by the owned 18C3E6.
class Rva0018C262:public _STL::set<int,_STL::less<int>,_STL::allocator<int> > {public:~Rva0018C262();};
class Rva0018C6D5 {public:void rva0018C6D5(const unsigned short *,const unsigned short *);};
struct Rva0018C2E7Node { int unknown; void *parent; void *left; void *right; short value; };
namespace _STL {struct __false_type {};}
short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node *, Rva0018C2E7Node *, short *,const _STL::__false_type &);
struct Rva0018C533Input;
struct Rva0018C533Output;
Rva0018C533Output *__cdecl Rva0018C533RangeForward(Rva0018C533Input *, Rva0018C533Input *, Rva0018C533Output *);
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
 template<class I> int __distance(const I &,const I &,const input_iterator_tag &);
 template<class I,class D> void advance(I &,D);
}
// The existing generic tree cursor providers only advance/count the node
// token. Their application key interpretation is not used in this unit.
struct Rva005E59FCKeyIterator { _STL::_Rb_tree_node_base *node; };
namespace _STL {
template<class T> struct _Rb_global {static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);};
template<> __declspec(noinline) inline int __distance(const Rva005E59FCKeyIterator &first,const Rva005E59FCKeyIterator &last,const input_iterator_tag &) {
 int result=0;
 _Rb_tree_node_base *node=first.node;
 while(node!=last.node){node=_Rb_global<bool>::_M_increment(node);++result;}
 return result;
}
}
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node*,Rva0018C2E7Node*,short*,void*,int);
inline __declspec(noinline) short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node *first,Rva0018C2E7Node *last,short *result,const _STL::__false_type &) {
 char category;
 return Rva0018C2E7Copy(first,last,result,&category,0);
}
static __forceinline short *copyTreeWords(Rva0018C2E7Node *first,Rva0018C2E7Node *last,short *result) {
 return Rva0018C3C9Copy(first,last,result,_STL::__false_type());
}
struct Rva0018C73CStorage : _STL::allocator<short> {short *data;};
class Rva0018C73CWordVector {
public:
 short *allocateCopy(unsigned int,Rva005E59FCKeyIterator,Rva005E59FCKeyIterator);
 void assign(Rva005E59FCKeyIterator,Rva005E59FCKeyIterator,const _STL::forward_iterator_tag&);
private:
 short *begin;
 short *end;
 Rva0018C73CStorage storage;
};
inline __declspec(noinline) short *Rva0018C73CWordVector::allocateCopy(unsigned int n,Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last) {
 short *result=storage.allocate(n,0);
 Rva0018C3C9Copy((Rva0018C2E7Node*)first.node,(Rva0018C2E7Node*)last.node,result,_STL::__false_type());
 return result;
}
inline __declspec(noinline) void Rva0018C73CWordVector::assign(Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last,const _STL::forward_iterator_tag &) {
 unsigned int len=_STL::__distance(first,last,_STL::input_iterator_tag());
 short *finish;
 if(len>(unsigned int)(storage.data-begin)) {
  short *fresh=allocateCopy(len,first,last);
  if(begin) Rva00030830GameFree(begin);
  begin=fresh;
  finish=begin+len;
  storage.data=finish;
 } else if((unsigned int)(end-begin)>=len) {
  finish=(short*)Rva0018C533RangeForward((Rva0018C533Input*)first.node,(Rva0018C533Input*)last.node,(Rva0018C533Output*)begin);
 } else {
  Rva005E59FCKeyIterator mid=first;
  _STL::advance(mid,(unsigned int)(end-begin));
  Rva0018C533RangeForward((Rva0018C533Input*)first.node,(Rva0018C533Input*)mid.node,(Rva0018C533Output*)begin);
  finish=copyTreeWords((Rva0018C2E7Node*)mid.node,(Rva0018C2E7Node*)last.node,end);
 }
 end=finish;
}

struct Rva0018C7E5Vector {void resize(unsigned int,unsigned short);};
class BfmeAwakenLog {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual BfmeAwakenLog *slot30(unsigned value);
 virtual BfmeAwakenLog *slot34(int value);
 virtual BfmeAwakenLog *slot38(const char *text);
 virtual void slot3C();virtual void slot40();virtual void slot44();virtual void slot48();
 virtual void slot4C(int report);
};
class Debug {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();
 virtual void slot40();virtual void slot44();virtual void slot48();virtual void slot4C();
 virtual void slot50();virtual void slot54();virtual void slot58();virtual void slot5C();
 virtual void slot60();virtual void slot64();virtual void slot68();
 virtual BfmeAwakenLog *slot6C(int first,int second,int third);
};
extern Debug *theDebug;
#define TheDebug theDebug
extern void _bfme_debugRecordCallsite(int kind);
extern bool bfmeRva000387C0(void);
// Pass-count provider stored at 0xDFCEBC (set by 18C0E7, cleared by 18C0F1); slot 0 takes the mesh name.
class FxPassCountProvider {public:virtual int slot00(const char *name);};
extern int g_00DFCEBC;
#define TheFxPassCountProvider ((FxPassCountProvider *)g_00DFCEBC)
class CountedAsset {public:void Release_Ref();};
class Rva0015148D {public:void *rva0015148D();};
class AssetReference {
public:
 ~AssetReference() {if(m_object) m_object->Release_Ref();}
 Rva0015148D *View() {return reinterpret_cast<Rva0015148D *>(this);}
private:
 CountedAsset *m_object;
};
class Rva0007B9EE {public:AssetReference rva0007B9EE();char m_pad00[0x20];void *m_technique;};
class Vector3 {
public:
 float X,Y,Z;
 Vector3 &operator=(const Vector3 &v) {X=v.X;Y=v.Y;Z=v.Z;return *this;}
};
struct TriIndex {unsigned short I,J,K;};
template<class T> class ShareBufferClass {public:char m_pad00[0xC];T *Array;};
class MeshMatDescClass {
public:
 unsigned *Get_Color_Array(int index) {if(ColorArray[index]) return ColorArray[index]->Array;return 0;}
 Vector2 *Get_UV_Array_By_Index(int,bool);
 Rva0007B9EE *Peek_FXShader(int pass) {return FXShader[pass];}
 char m_pad00[0x50];
 ShareBufferClass<unsigned> *ColorArray[2];	// +0x50
 char m_pad58[0xA8-0x58];
 void *Material[4];	// +0xA8
 Rva0007B9EE *FXShader[4];	// +0xB8
 char m_padC8[0xE8-0xC8];
 void *MaterialArray[4];	// +0xE8
};
class MeshGeometryClass {
 friend class FXShaderGeometry;
public:
 enum FlagsType {ALIGNED=0x200,SKIN=0x400,ORIENTED=0x800};
 int Get_Flag(FlagsType flag) {return Flags&flag;}
 int Get_Polygon_Count() const {return PolyCount;}
 int Get_Vertex_Count() const {return VertexCount;}
 const char *Get_Name() const;
 int rva0018C088() const;
 const Vector3 *Get_Vertex_Normal_Array(bool);
 Vector3 *rva0016ABC0();
 Vector3 *rva0016ABE0();
 const Vector3 *Get_Vertex_Array(int index) {return Vertex[index]->Array;}
protected:
 unsigned short *get_bone_links(bool);
public:
 char m_pad00[0x18];
 unsigned Flags;	// +0x18
 char m_pad1C[0x24-0x1C];
 int PolyCount;	// +0x24
 int VertexCount;	// +0x28
 ShareBufferClass<TriIndex> *Poly;	// +0x2C
 ShareBufferClass<Vector3> *Vertex[2];	// +0x30
};
class MeshModelClass:public MeshGeometryClass {
public:
 char m_pad38[0x94-0x38];
 MeshMatDescClass *CurMatDesc;	// +0x94
};
class DX8FVFCategoryContainer {public:static unsigned Define_FVF(MeshModelClass *,bool);};
struct BfmeFVFDescriptor {
 unsigned fvf;                       // 0x00
 bool additionalBasis;              // 0x04
 unsigned extensionCount;           // 0x08
 unsigned stride;                   // 0x0C
 unsigned locationOffset;           // 0x10
 unsigned extensionOffset;          // 0x14
 unsigned normalOffset;             // 0x18
 unsigned extensionEnd;             // 0x1C
 unsigned blendOffset;              // 0x20
 unsigned textureOffsets[8];        // 0x24
 unsigned diffuseOffset;            // 0x44
 unsigned specularOffset;           // 0x48
 unsigned basisOffset;              // 0x4C
 unsigned basisSecondOffset;        // 0x50
 unsigned basisEnd;                 // 0x54
 unsigned extensionDataOffset;      // 0x58
 unsigned formatIndex;              // 0x5C
 BfmeFVFDescriptor(unsigned,unsigned,bool,unsigned);
 unsigned Get_Tex_Offset(unsigned n) const {return textureOffsets[n];}
 void *rva001818C0();
};
class VertexBufferClass {
public:
 class WriteLockClass {
 public:
  WriteLockClass(VertexBufferClass *buffer,int flags);
  ~WriteLockClass();
  void *Get_Vertex_Array() {return m_vertices;}
 private:
  VertexBufferClass *m_buffer;
  void *m_vertices;
  int m_flags;
 };
};
class BfmeDynamicNativeVB:public VertexBufferClass {
public:
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
 char m_pad00[0x20];
};
class IndexBufferClass {
public:
 class WriteLockClass {
 public:
  WriteLockClass(IndexBufferClass *buffer,int flags);
  ~WriteLockClass();
  unsigned short *Get_Index_Array() {return (unsigned short *)m_indices;}
 private:
  IndexBufferClass *m_buffer;
  void *m_indices;
 };
};
class DX8IndexBufferClass:public IndexBufferClass {
public:
 enum UsageType {USAGE_DEFAULT=0,USAGE_NPATCHES=4};
 DX8IndexBufferClass(unsigned,UsageType);
 char m_pad00[0x18];
};
class FXShaderGeometry {
public:
 bool Init(MeshModelClass *mesh);
 void rva0018C131(FxEffectView *,void *,unsigned *,bool *);
private:
 bool m_skin;	// +0x00
 unsigned m_FVF;	// +0x04
 void *m_Decl;	// +0x08
 VertexBufferClass *m_VB;	// +0x0C
 IndexBufferClass *m_IB;	// +0x10
 _STL::vector<short> m_bones;	// +0x14
 int m_BonesPerVertex;	// +0x20
 int m_Passes;	// +0x24
};
void FXShaderGeometry::rva0018C131(FxEffectView *effect,void *technique,unsigned *fvf,bool *basis)
{
 *fvf=0;*basis=false;
 int textureCount=0;
 if(effect) {
  FxTechniqueDesc td;
  if(effect->GetTechniqueDesc(technique,&td)>=0) {
   for(unsigned passIndex=0;passIndex<td.passes;++passIndex) {
    void *pass=effect->GetPass(technique,passIndex);
    unsigned count=0;
    if(pass) {
     FxPassDesc pd;
     if(effect->GetPassDesc(pass,&pd)>=0) {
      FxShaderSemantic semantics[64];
      if(D3DXGetShaderInputSemantics(pd.vertexShader,semantics,&count)>=0) {
       for(unsigned i=0;i<count;++i) {
        const FxShaderSemantic &semantic=semantics[i];
        if(semantic.usage==0) *fvf|=2;
        else if(semantic.usage==10 && semantic.index==0) *fvf|=0x40;
        else if(semantic.usage==10 && semantic.index==1) *fvf|=0x80;
        else if(semantic.usage==3) *fvf|=0x10;
        else if(semantic.usage==6 || semantic.usage==7) *basis=true;
        else if(semantic.usage==5) {
         int nextCount=semantic.index+1;
         const int &largest=textureCount>nextCount?textureCount:nextCount;
         textureCount=largest;
        }
       }
      }
     }
    }
   }
  }
  int limit=8;
  const int &clamped=textureCount<limit?textureCount:limit;
  *fvf|=((unsigned)clamped&15)<<8;
 }
}
bool FXShaderGeometry::Init(MeshModelClass *mesh)
{
 m_VB=0;
 m_IB=0;
 m_Decl=0;
 m_bones.clear();
 m_BonesPerVertex=0;
 m_Passes=0;
 if(!mesh->CurMatDesc->Peek_FXShader(0)) return false;
 if(mesh->CurMatDesc->Material[0] || mesh->CurMatDesc->MaterialArray[0]) return false;
 FxEffectView *effect=(FxEffectView *)mesh->CurMatDesc->Peek_FXShader(0)->rva0007B9EE().View()->rva0015148D();
 if(!effect) return false;
 void *technique=mesh->CurMatDesc->FXShader[0]->m_technique;
 int maxBones=0;
 void *annotation=effect->GetAnnotationByName(technique,"MaxSkinningBones");
 if(annotation && effect->GetInt(annotation,&maxBones)<0) maxBones=0;
 bool skin=mesh->Get_Flag(MeshGeometryClass::SKIN)!=0;
 if(skin) {
  m_skin=true;
  if(maxBones>0) {
   unsigned short *links=mesh->get_bone_links(true);
   if(links) {
    int linkCount=mesh->rva0018C088()*mesh->VertexCount;
    Rva0018C262 bones;
    ((Rva0018C6D5 *)&bones)->rva0018C6D5(links,links+linkCount);
    if(bones.size()<=(unsigned)maxBones) {
     m_skin=false;
     Rva005E59FCKeyIterator first={bones._M_header->_M_left},last={bones._M_header};
     ((Rva0018C73CWordVector *)&m_bones)->assign(first,last,_STL::forward_iterator_tag());
    } else if(bfmeRva000387C0()) {
     _bfme_debugRecordCallsite(1);
     TheDebug->slot60();
     TheDebug->slot6C(0,0,0)->slot38("Cannot do shader skinning on model: ")->slot38(mesh->Get_Name())->slot38(". Has ")
      ->slot30(bones.size())->slot38(" bones, maximum is ")->slot34(maxBones)->slot38(".")->slot4C(2);
    }
   }
  }
 } else m_skin=false;
 if(!skin && TheFxPassCountProvider && maxBones>1 && !mesh->Get_Flag(MeshGeometryClass::ALIGNED) && !mesh->Get_Flag(MeshGeometryClass::ORIENTED)) {
  m_Passes=TheFxPassCountProvider->slot00(mesh->Get_Name());
  m_Passes=_STL::min(m_Passes,maxBones);
  if(mesh->VertexCount*m_Passes>65000) m_Passes=65000/mesh->VertexCount;
  if(m_Passes*mesh->PolyCount*3>65000) m_Passes=65000/(mesh->PolyCount*3);
  m_Passes=_STL::max(m_Passes,1);
 } else m_Passes=1;
 m_FVF=0;
 bool basis=false;
 if(m_skin) m_FVF=0x252;
 else {
  rva0018C131(effect,technique,&m_FVF,&basis);
  if(!m_FVF) m_FVF=DX8FVFCategoryContainer::Define_FVF(mesh,true)|0x10;
  if(skin) m_BonesPerVertex=mesh->rva0018C088();
  else if(m_Passes>1) m_BonesPerVertex=1;
 }
 BfmeFVFDescriptor desc(m_FVF,0,basis,m_BonesPerVertex);
 if(!m_skin) {
  if(!desc.additionalBasis && !desc.extensionCount)
   m_VB=new BfmeDynamicNativeVB(m_FVF,(unsigned short)(m_Passes*mesh->Get_Vertex_Count()),0,0);
  else {
   m_Decl=desc.rva001818C0();
   m_VB=new BfmeDynamicNativeVB(0,(unsigned short)(m_Passes*mesh->Get_Vertex_Count()),0,desc.stride);
  }
  VertexBufferClass::WriteLockClass lock(m_VB,0);
 if(0){ AsciiString dead; if(0){ AsciiString inner; } }
  char *vertices=(char *)lock.Get_Vertex_Array();
  const Vector3 *positions[2]={mesh->Get_Vertex_Array(0),0};
  const Vector3 *normals[2]={mesh->Get_Vertex_Normal_Array(false),0};
  const Vector3 *tangents=mesh->rva0016ABC0();
  const Vector3 *binormals=mesh->rva0016ABE0();
  const unsigned *colors=mesh->CurMatDesc->Get_Color_Array(0);
  int textureCount=(m_FVF>>8)&0xF;
  const unsigned short *links[2]={mesh->get_bone_links(true),0};
  const unsigned short *weights[2]={0,0};
  if(m_BonesPerVertex>1) {
   links[1]=links[0]+mesh->Get_Vertex_Count();
   weights[0]=links[1]+mesh->Get_Vertex_Count();
   weights[1]=weights[0]+mesh->Get_Vertex_Count();
   positions[1]=mesh->Get_Vertex_Array(1);
   normals[1]=mesh->Get_Vertex_Normal_Array(true);
  }
  _STL::vector<short> remap;
  if(!m_bones.empty() && links[0]) {
   ((Rva0018C7E5Vector *)&remap)->resize(*m_bones.rbegin()+1,0);
   int index=0;
   for(short *bone=m_bones.begin();bone!=m_bones.end();++bone,++index) remap[*bone]=index;
  }
  for(unsigned pass=0;pass<(unsigned)m_Passes;++pass) {
   for(unsigned i=0;i<(unsigned)mesh->VertexCount;++i) {
    *(Vector3 *)(vertices+desc.locationOffset)=positions[0][i];
    if(m_FVF&0x10) *(Vector3 *)(vertices+desc.normalOffset)=normals[0][i];
    if(m_FVF&0x40) {
     if(colors) *(unsigned *)(vertices+desc.diffuseOffset)=colors[i];
     else *(unsigned *)(vertices+desc.diffuseOffset)=0xFFFFFFFF;
    }
    for(int t=0;t<textureCount;++t) {
     const Vector2 *uv=mesh->CurMatDesc->Get_UV_Array_By_Index(t,false);
     if(uv) *(Vector2 *)(vertices+desc.Get_Tex_Offset(t))=uv[i];
    }
    if(basis) {
     if(tangents) *(Vector3 *)(vertices+desc.basisOffset)=tangents[i];
     if(binormals) *(Vector3 *)(vertices+desc.basisSecondOffset)=binormals[i];
    }
    if(m_Passes>1) *(unsigned *)(vertices+desc.basisEnd)=pass;
    else if(m_BonesPerVertex>0 && links[0]) {
     if(m_BonesPerVertex==1) *(int *)(vertices+desc.basisEnd)=remap[links[0][i]];
     else if(m_BonesPerVertex==2) {
      int firstBone=links[0][i];
      *(int *)(vertices+desc.basisEnd)=remap[firstBone]+(remap[links[1][i]]<<8);
      *(Vector2 *)(vertices+desc.extensionDataOffset)=Vector2(weights[0][i]/100.0f,weights[1][i]/100.0f);
      if(positions[1]) *(Vector3 *)(vertices+desc.extensionOffset)=positions[1][i];
      if(normals[1]) *(Vector3 *)(vertices+desc.extensionEnd)=normals[1][i];
     }
    }
    vertices+=desc.stride;
   }
  }
 }
 m_IB=new DX8IndexBufferClass(m_Passes*mesh->Get_Polygon_Count()*3,DX8IndexBufferClass::USAGE_DEFAULT);
 {
  struct PaddedLock1:public IndexBufferClass::WriteLockClass { unsigned char pad[1]; __forceinline PaddedLock1(IndexBufferClass *p,int f):IndexBufferClass::WriteLockClass(p,f) {} }; PaddedLock1 lock(m_IB,0);
  const TriIndex *polys=mesh->Poly->Array;
  unsigned short *indices=lock.Get_Index_Array();
  memcpy(indices,polys,mesh->PolyCount*sizeof(TriIndex));
  indices+=mesh->PolyCount*3;
  for(unsigned pass=1;pass<(unsigned)m_Passes;++pass) {
   int offset=mesh->VertexCount*pass;
   for(unsigned j=0;j<(unsigned)mesh->PolyCount;++j) {
    indices[0]=polys[j].I+offset;
    indices[1]=polys[j].J+offset;
    indices[2]=polys[j].K+offset;
    indices+=3;
   }
  }
 }
 return true;
}