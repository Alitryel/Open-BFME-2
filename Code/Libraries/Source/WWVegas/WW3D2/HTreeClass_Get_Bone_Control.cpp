// ?Get_Bone_Control@HTreeClass@@QBEXHAAVMatrix3D@@@Z
// ?Get_Bone_Control@HTreeClass@@QBEXHAAVMatrix3D@@@Z
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2htree /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
#include <windows.h>
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "../../../../../reference/shims/bfme2htree/htree.h"
// Target-decoded capture record; the shared HTree seed retains the vector
// as three 32-bit words at +1C, +20 and +24.
struct CapturedBone {int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
// HTreeClass::Control_Bone (0x00162060) is rowed in htree_control.cpp.

void HTreeClass::Get_Bone_Control(int index,Matrix3D &out) const
{
 // Target Matrix3D is twelve row-major floats. A scalar view keeps this
 // body from emitting a second Matrix3D accessor under its own flags.
 typedef float MatrixWords[3][4];
 MatrixWords &matrix=*reinterpret_cast<MatrixWords *>(&out);
 CapturedBone *bone=reinterpret_cast<CapturedBone *>(OwnedSequence1C[0]);
 while(bone!=reinterpret_cast<CapturedBone *>(OwnedSequence1C[1]) && bone->Index<index) ++bone;
 if(bone==reinterpret_cast<CapturedBone *>(OwnedSequence1C[1]) || bone->Index!=index) {
  matrix[0][0]=1.0f;matrix[0][1]=0.0f;matrix[0][2]=0.0f;matrix[0][3]=0.0f;
  matrix[1][0]=0.0f;matrix[1][1]=1.0f;matrix[1][2]=0.0f;matrix[1][3]=0.0f;
  matrix[2][0]=0.0f;matrix[2][1]=0.0f;matrix[2][2]=1.0f;matrix[2][3]=0.0f;
  return;
 }
 {
  const Quaternion &quaternion=bone->Rotation;
  float xx=quaternion.X*quaternion.X*2.0f;
  float xy=__vref(quaternion.X)*quaternion.Y*2.0f;
  float xz=quaternion.X*quaternion.Z*2.0f;
  float xw=quaternion.X*quaternion.W*2.0f;
  float yy=quaternion.Y*quaternion.Y*2.0f;
  float yz=quaternion.Y*quaternion.Z*2.0f;
  float yw=quaternion.Y*quaternion.W*2.0f;
  float zz=quaternion.Z*quaternion.Z*2.0f;
  float zw=quaternion.Z*quaternion.W*2.0f;
  matrix[0][0]=1.0f-yy-zz; matrix[0][1]=xy-zw; matrix[0][2]=yw+xz;
  matrix[1][0]=zw+xy; matrix[1][1]=1.0f-zz-xx; matrix[1][2]=yz-xw;
  matrix[2][0]=xz-yw; matrix[2][1]=yz+xw; matrix[2][2]=1.0f-yy-xx;
  matrix[0][3]=bone->Translation.X;matrix[1][3]=bone->Translation.Y;matrix[2][3]=bone->Translation.Z;
 }
}
