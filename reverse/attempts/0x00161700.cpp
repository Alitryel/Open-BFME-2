// ?Simple_Evaluate_Pivot@HTreeClass@@QBE_NPAVHAnimClass@@HMABVMatrix3D@@PAV3@@Z
// partial score=0.9612220526 date=2026-10-16
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

// Animated compact-pivot evaluation; see bank 0x00161700 for target evidence.
struct S2CompactTransform {
 Quaternion Q; Vector3 Position;
 S2CompactTransform(){}
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

static __forceinline Matrix3D &S2PivotMatrix(const S2CompactTransform &q,Matrix3D &m) {
 const float xx=q.Q.X*q.Q.X*2.0f,xy=q.Q.X*q.Q.Y*2.0f,xz=q.Q.Z*q.Q.X*2.0f,wx=q.Q.W*q.Q.X*2.0f;
 const float yy=q.Q.Y*q.Q.Y*2.0f,yz=q.Q.Z*q.Q.Y*2.0f,wy=q.Q.W*q.Q.Y*2.0f;
 const float zz=q.Q.Z*q.Q.Z*2.0f,wz=q.Q.W*q.Q.Z*2.0f;
 m[0][0]=1.0f-yy-zz;m[0][1]=xy-wz;m[0][2]=xz+wy;
 m[1][0]=xy+wz;m[1][1]=1.0f-zz-xx;m[1][2]=yz-wx;
 m[2][0]=xz-wy;m[2][1]=yz+wx;m[2][2]=1.0f-yy-xx;
 m[0][3]=q.Position.X;m[1][3]=q.Position.Y;m[2][3]=q.Position.Z;
 return m;
}
bool HTreeClass::Simple_Evaluate_Pivot(HAnimClass *motion,int pivot_index,float frame,const Matrix3D &obj_tm,Matrix3D *end_tm)const {
 if(!end_tm)return false;
 end_tm->Make_Identity();
 if(!motion || pivot_index<0 || pivot_index>=NumPivots)return false;
 S2CompactTransform total(true);
 for(S2PivotView *p=&reinterpret_cast<S2PivotView *>(Pivot)[pivot_index];p && p->Parent;p=p->Parent){
  S2CompactTransform anim;
  ((S2CompactAnimView*)motion)->rva_vt28(anim,p->Index,frame);
  anim.Position*=ScaleFactor;
  S2CompactTransform current;compose(p->Base,anim,current);
  compose(current,total,total);
 }
 S2PivotMatrix(total,*end_tm);
 end_tm->preMul(obj_tm);
 return true;
}
