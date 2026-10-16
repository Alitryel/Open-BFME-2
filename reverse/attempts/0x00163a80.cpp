// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHRawAnimClass@@M@Z
// partial score=0.6060081329 date=2026-10-16
// Owner integration for HTreeClassReadPivots.cpp. Before compiling this bank,
// add the already-pinned Capture_Update declaration using this header patch.
// Trial used an isolated header copy under build; shared header was not edited.
#if 0
--- a/reference/shims/bfme2htree/htree.h
+++ b/reference/shims/bfme2htree/htree.h
@@ -134 +134,2 @@
-	void					Capture_Bone(int boneindex);
+	int Capture_Update(int);
+ void Capture_Bone(int boneindex);
#endif
// cl: /O2 /Ireference/shims/bfme2htree /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
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

// BFME 2 WorldBuilder read_pivots and retail 0x001614F0 agree on the
// 0x58-byte pivot and quaternion/vector transform, unlike ZH's Matrix3D pivot.
struct Bfme2HTreeTransform {
    Quaternion Rotation;
    Vector3 Translation;
    // ?Bfme2HTreeTransform::Bfme2HTreeTransform absent-from-retail
    __forceinline Bfme2HTreeTransform(bool identity) {
        Rotation.Make_Identity();
        Translation.Set(0.0f, 0.0f, 0.0f);
    }
    // ?Bfme2HTreeTransform::operator= absent-from-retail
    __forceinline Bfme2HTreeTransform &operator=(const Bfme2HTreeTransform &source) {
        Rotation = source.Rotation;
        Translation = source.Translation;
        return *this;
    }
};
struct Bfme2HTreePivot {
    char Name[16];
    Bfme2HTreePivot *Parent;
    Bfme2HTreeTransform BaseTransform;
    Bfme2HTreeTransform Transform;
    int Index;
    bool IsVisible;
    float PivotFade;
};
typedef char Bfme2HTreePivotSize[(sizeof(Bfme2HTreePivot) == 88) ? 1 : -1];
bool HTreeClass::read_pivots(ChunkLoadClass &cload, bool pre30)
{
    W3dPivotStruct piv;
    int first_piv = 0;
    if (pre30) {
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Index = 0;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Parent = NULL;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].BaseTransform = Bfme2HTreeTransform(true);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Transform = Bfme2HTreeTransform(true);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].IsVisible = true;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].PivotFade = 1.0f;
        strcpy(reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Name, "RootTransform");
        first_piv++;
    }
    for (int pidx = first_piv; pidx < NumPivots; pidx++) {
        if (cload.Read(&piv, sizeof(W3dPivotStruct)) != sizeof(W3dPivotStruct))
            return false;
        memcpy(reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Name, piv.Name, W3D_NAME_LEN);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Index = pidx;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].BaseTransform.Translation.Set(piv.Translation.X, piv.Translation.Y, piv.Translation.Z);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].BaseTransform.Rotation.Set(piv.Rotation.Q[0], piv.Rotation.Q[1], piv.Rotation.Q[2], piv.Rotation.Q[3]);
        if (pre30) piv.ParentIdx += 1;
        if (piv.ParentIdx == -1) {
            reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Parent = NULL;
            assert(pidx == 0);
        } else {
            reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Parent = &reinterpret_cast<Bfme2HTreePivot *>(Pivot)[piv.ParentIdx];
        }
    }
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Transform = Bfme2HTreeTransform(true);
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].IsVisible = true;
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].PivotFade = 1.0f;
    return true;
}

inline Vector3 rawRotateVector(const Vector3 &v, const Quaternion &q)
{
	float x = (v.Z*q.Y - q.Z*v.Y) + q.W*v.X;
	float y = q.W*v.Y - (v.Z*q.X - q.Z*v.X);
	float z = (q.X*v.Y - v.X*q.Y) + v.Z*q.W;
	float w = -((v.X*q.X + v.Z*q.Z) + v.Y*q.Y);

	return Vector3
	(
		(z*q.Y - q.Z*y) + (q.W*x - q.X*w),
		(q.W*y - w*q.Y) - (q.X*z - q.Z*x),
		(q.X*y - x*q.Y) + (q.W*z - q.Z*w)
	);
}

class MotionChannelClass {
public:
 unsigned PivotIdx,Type; int VectorLen;float ValueOffset,ValueScale;float *Data;int FirstFrame,LastFrame;
 __forceinline void Get_Vector(int frame,float *out) const {
  if(frame<FirstFrame || frame>LastFrame) {
   if(Type==15)out[0]=1.0f;
   else if(Type==6){out[0]=out[1]=out[2]=0.0f;out[3]=1.0f;}
   else out[0]=0.0f;
  } else {
   int vframe=frame-FirstFrame;
   for(int i=0;i<VectorLen;++i)out[i]=Data[vframe*VectorLen+i];
  }
 }
 __forceinline void Get_Vector_As_Quat(int frame,Quaternion &q) const {
  if(frame<FirstFrame || frame>LastFrame)q=Quaternion(0,0,0,1);
  else {const float *d=&Data[(frame-FirstFrame)*VectorLen];q=Quaternion(d[0],d[1],d[2],d[3]);}
 }
};
class BitChannelClass {
public:
 unsigned PivotIdx,Type;int DefaultVal,FirstFrame,LastFrame;unsigned char *Bits;
 __forceinline int Get_Bit(int frame) const {
  if(frame<FirstFrame || frame>LastFrame)return DefaultVal;
  int bit=frame-FirstFrame;unsigned char mask=(unsigned char)(1<<(bit%8));
  return (Bits[bit/8]&mask)!=0;
 }
};
struct NodeMotionStruct { MotionChannelClass *X,*Y,*Z,*XR,*YR,*ZR,*Q,*Fade;BitChannelClass *Vis;};
class HRawAnimClass {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();
 virtual int Get_Num_Frames();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual int Get_Num_Pivots();
 char pad[0x4c];NodeMotionStruct *Nodes;
};
void HTreeClass::Anim_Update(const Matrix3D &root,HRawAnimClass *motion,float frame) {
 Bfme2HTreePivot *pivots=(Bfme2HTreePivot*)Pivot;
 Bfme2HTreeTransform &initial=pivots[0].Transform;
 initial.Rotation=Build_Quaternion(root);
 initial.Translation.X=root[0][3];initial.Translation.Y=root[1][3];initial.Translation.Z=root[2][3];
 pivots[0].IsVisible=true;pivots[0].PivotFade=1.0f;
 int iframe=WWMath::Float_To_Long(frame);
 if(iframe>=motion->Get_Num_Frames())iframe=0;
 NodeMotionStruct *node=motion->Nodes+1;
 Bfme2HTreePivot *pivot=&pivots[1];
 Bfme2HTreePivot *endpivot=pivot+(NumPivots-1);
 Bfme2HTreePivot *lastAnimPivot=&pivots[motion->Get_Num_Pivots()];
 int captured=OwnedSequence1C[0]==OwnedSequence1C[1]?-1:*(int*)OwnedSequence1C[0];
 for(;pivot<endpivot;++pivot,++node) {
  const Bfme2HTreeTransform &parent=pivot->Parent->Transform;
  pivot->Transform.Translation=parent.Translation+rawRotateVector(pivot->BaseTransform.Translation,parent.Rotation);
  pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;
  if(pivot<lastAnimPivot) {
   Vector3 trans(0,0,0);
   if(node->X)node->X->Get_Vector(iframe,&trans.X);
   if(node->Y)node->Y->Get_Vector(iframe,&trans.Y);
   if(node->Z)node->Z->Get_Vector(iframe,&trans.Z);
   if(ScaleFactor!=1.0f){trans.X*=ScaleFactor;trans.Y*=ScaleFactor;trans.Z*=ScaleFactor;}
   if(node->Q) {
    Quaternion q;node->Q->Get_Vector_As_Quat(iframe,q);
    pivot->Transform.Translation=rawRotateVector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
    Quaternion old=pivot->Transform.Rotation;
    pivot->Transform.Rotation.X=(old.Y*q.Z-q.Y*old.Z)+q.W*old.X+old.W*q.X;
    pivot->Transform.Rotation.Y=q.W*old.Y+old.W*q.Y-(old.X*q.Z-q.X*old.Z);
    pivot->Transform.Rotation.Z=(q.Y*old.X-old.Y*q.X)+q.W*old.Z+old.W*q.Z;
    pivot->Transform.Rotation.W=q.W*old.W-((q.Z*old.Z+q.Y*old.Y)+old.X*q.X);
   } else {
    pivot->Transform.Translation=rawRotateVector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
   }
   if(node->Fade){float fade=1;node->Fade->Get_Vector(iframe,&fade);pivot->PivotFade=fade;}else pivot->PivotFade=1;
   pivot->IsVisible=node->Vis?node->Vis->Get_Bit(iframe)==1:true;
  }
  if(pivot->Index==captured)captured=Capture_Update(captured);
 }
}
