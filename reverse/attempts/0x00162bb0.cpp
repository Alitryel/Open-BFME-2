// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimClass@@M@Z
// partial score=0.5 date=2026-10-19
// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimClass@@M@Z
// partial score=0.5 date=2026-10-19
// Bank r3 (claude-opus-5-5): 68 structural regions under build/try.sh (prior bank 78). Compiles with
// /Ibuild/htshim = a copy of the htree shim header adding 'int Capture_Update(int);' to HTreeClass (same as 0x163A80 bank).
// Handoff: reverse/attempt_support/00162bb0-anim-update-r3-20261019.md
// cl: /O2 /Ibuild/htshim /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// stlport
// ZH read_pivots adapted to the BFME 2 compact pivot ABI proven by
// WorldBuilder HTreeClass::read_pivots and retail RVA 0x001614F0 (526 bytes).
// BFME 1 donor revision: ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
#include "htree.h"
#include "chunkio.h"
#include <string.h>
#include <assert.h>
struct S2CompactTransform {
 Quaternion Q; Vector3 Position;
 S2CompactTransform(){}
 __forceinline explicit S2CompactTransform(const Matrix3D &m) {
  Q=Build_Quaternion(m);
  m.Get_Translation(&Position);
 }
 explicit S2CompactTransform(bool init):Q(init),Position(0.0f,0.0f,0.0f){}
};
struct S2PivotView {
 char Name[16]; S2PivotView *Parent;
 S2CompactTransform Base,Current;
 int Index; bool visible; float factor;
};
class HAnimClass;
class S2CompactAnimView {
public:
 virtual void vt0();virtual void vt4();virtual void vt8();virtual void vtC();virtual void vt10();
 virtual void vt14();virtual void vt18();virtual void vt1C();virtual void vt20();virtual void vt24();
 virtual void rva_vt28(S2CompactTransform&,int,float)const;
};
static __forceinline void rotate(const Quaternion &q,const Vector3&v,Vector3*out){
 float x=(q.Y*v.Z-q.Z*v.Y)+q.W*v.X;
 float y=-(q.X*v.Z-q.Z*v.X)+q.W*v.Y;
 float z=(q.X*v.Y-q.Y*v.X)+q.W*v.Z;
 float w=0.0f-(q.X*v.X+q.Y*v.Y+q.Z*v.Z);
 out->X=(q.Y*z-y*q.Z)+(q.W*x-q.X*w);
 out->Y=(q.W*y-q.Y*w)-(q.X*z-q.Z*x);
 out->Z=(q.X*y-q.Y*x)+(q.W*z-q.Z*w);
}
static __forceinline void compose(const S2CompactTransform&a,const S2CompactTransform&b,S2CompactTransform&result){
 Vector3 r;rotate(a.Q,b.Position,&r);result.Position=r+a.Position;
 result.Q=a.Q*b.Q;
}

static __forceinline void rotate3(const Quaternion &q,const Vector3&v,Vector3*out){
 float x=(q.Y*v.Z-q.Z*v.Y)+v.X*q.W;
 float y=v.Y*q.W-(q.X*v.Z-v.X*q.Z);
 float z=(q.X*v.Y-q.Y*v.X)+v.Z*q.W;
 float w=0.0f-((v.X*q.X+q.Y*v.Y)+q.Z*v.Z);
 out->X=(q.Y*z-q.Z*y)+(x*q.W-q.X*w);
 out->Y=(y*q.W-q.Y*w)-(q.X*z-q.Z*x);
 out->Z=(q.X*y-q.Y*x)+(z*q.W-q.Z*w);
}
static __forceinline void qmul(const Quaternion &a,const Quaternion &b,Quaternion &self){
 self.X=a.W*b.X+b.W*a.X+(a.Y*b.Z-b.Y*a.Z);
 self.Y=a.W*b.Y+b.W*a.Y-(a.X*b.Z-b.X*a.Z);
 self.Z=a.W*b.Z+b.W*a.Z+(a.X*b.Y-b.X*a.Y);
 self.W=a.W*b.W-(a.X*b.X+a.Y*b.Y+a.Z*b.Z);
}
static __forceinline void qmuleq(Quaternion &self,const Quaternion &b){Quaternion a=self;qmul(a,b,self);}
static __forceinline void compose3(const S2CompactTransform&a,const S2CompactTransform&b,S2CompactTransform&result){
 Vector3 r;rotate3(a.Q,b.Position,&r);result.Position=a.Position+r;
 result.Q=a.Q*b.Q;
}
class TimeCodedBitChannelClass {public:int Get_Bit(int);};
class S2MotionChannel {
public:
 virtual void vt0();virtual void vt4();virtual void vt8();
 virtual void Get_Vector(float,float *,unsigned char **);
 virtual void vt10();virtual void Get_Quat(float,Quaternion *,unsigned char **);
};
struct S2NodeMotion {S2MotionChannel *X,*Y,*Z,*Q,*Fade;TimeCodedBitChannelClass *Vis;};
class S2HAnimView {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual void Get_Translation(Vector3 &,int,float);
 virtual bool Get_Orientation(Quaternion &,int,float);
 virtual void slot10(); virtual bool Get_Visibility(int,float); virtual float Get_Fade(int,float);
 virtual int Get_Num_Pivots();
 virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
 virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual int Get_Class_ID();
 char pad[0x54]; S2NodeMotion *Nodes;
};
class Rva00160FC0Input;
class Rva00160FC0 {public:void rva00160FC0(Rva00160FC0Input*);};
void HTreeClass::Anim_Update(const Matrix3D &root,HAnimClass *hmotion,float frame) {
 S2HAnimView *motion=(S2HAnimView*)hmotion;
 S2NodeMotion *nodes;
 if(motion->Get_Class_ID()==1 && (nodes=motion->Nodes)!=0) {
  ((Rva00160FC0*)this)->rva00160FC0((Rva00160FC0Input*)motion);
  S2CompactTransform &initial=((S2PivotView*)Pivot)[0].Current;
  initial.Q=Build_Quaternion(root);
  initial.Position.X=root[0][3];initial.Position.Y=root[1][3];initial.Position.Z=root[2][3];
  ((S2PivotView*)Pivot)[0].visible=true;((S2PivotView*)Pivot)[0].factor=1.0f;
  unsigned char *cache=(unsigned char*)Unknown2C;
  int count=motion->Get_Num_Pivots();
  int captured=OwnedSequence1C[0]==OwnedSequence1C[1]?-1:*(int*)OwnedSequence1C[0];
  for(int piv_idx=1;piv_idx<NumPivots;++piv_idx) {
   S2NodeMotion *node=&nodes[piv_idx];
   S2PivotView *pivot=&((S2PivotView*)Pivot)[piv_idx];
   compose3(pivot->Parent->Current,pivot->Base,pivot->Current);
   if(piv_idx<count) {
    float scale=ScaleFactor;
    Vector3 trans;
    if(node->X)node->X->Get_Vector(frame,&trans.X,&cache);else trans.X=0;
    if(node->Y)node->Y->Get_Vector(frame,&trans.Y,&cache);else trans.Y=0;
    if(node->Z)node->Z->Get_Vector(frame,&trans.Z,&cache);else trans.Z=0;
    trans.X*=scale;trans.Y*=scale;trans.Z*=scale;
    if(node->Q) {
     Quaternion q;node->Q->Get_Quat(frame,&q,&cache);
     Vector3 r;rotate3(pivot->Current.Q,trans,&r);pivot->Current.Position=pivot->Current.Position+r;
     qmuleq(pivot->Current.Q,q);
    } else {
     Vector3 r;rotate3(pivot->Current.Q,trans,&r);pivot->Current.Position=r+pivot->Current.Position;
    }
    if(node->Fade)node->Fade->Get_Vector(frame,&pivot->factor,&cache);else pivot->factor=1.0f;
    pivot->visible=node->Vis?node->Vis->Get_Bit((int)frame)!=0:true;
   }
   if(piv_idx==captured)captured=Capture_Update(captured);
  }
 } else {
  Unknown28=0;
  S2CompactTransform &initial=((S2PivotView*)Pivot)[0].Current;
  initial.Q=Build_Quaternion(root);
  initial.Position.X=root[0][3];initial.Position.Y=root[1][3];initial.Position.Z=root[2][3];
  ((S2PivotView*)Pivot)[0].visible=true;((S2PivotView*)Pivot)[0].factor=1.0f;
  int count=motion->Get_Num_Pivots();
  int captured=OwnedSequence1C[0]==OwnedSequence1C[1]?-1:*(int*)OwnedSequence1C[0];
  for(int piv_idx=1;piv_idx<NumPivots;++piv_idx) {
   S2PivotView *pivot=&((S2PivotView*)Pivot)[piv_idx];
   compose3(pivot->Parent->Current,pivot->Base,pivot->Current);
   if(piv_idx<count) {
    Vector3 trans;motion->Get_Translation(trans,piv_idx,frame);
    if(ScaleFactor!=1.0f){trans.X*=ScaleFactor;trans.Y*=ScaleFactor;trans.Z*=ScaleFactor;}
    Quaternion q;
    if(motion->Get_Orientation(q,piv_idx,frame)) {
     Vector3 r;rotate3(pivot->Current.Q,trans,&r);pivot->Current.Position=pivot->Current.Position+r;
     qmuleq(pivot->Current.Q,q);
    } else {
     Vector3 r;rotate3(pivot->Current.Q,trans,&r);pivot->Current.Position=r+pivot->Current.Position;
    }
    pivot->visible=motion->Get_Visibility(piv_idx,frame);
    pivot->factor=motion->Get_Fade(piv_idx,frame);
   }
   if(piv_idx==captured)captured=Capture_Update(captured);
  }
 }
}
