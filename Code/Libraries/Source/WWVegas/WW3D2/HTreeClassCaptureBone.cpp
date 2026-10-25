// ?Capture_Bone@HTreeClass@@QAEXH@Z
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2htree /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// ?Capture_Bone@HTreeClass@@QAEXH@Z, retail 0x00166980 (229 bytes).
//
// BFME2 rewrote Zero Hour's per-pivot IsCaptured flag as a sorted vector of
// 36-byte captured-bone records at +0x1C (Begin/End/Capacity), the same
// member HTreeClassFree.cpp clears and HTreeClassReleaseBone.cpp erases from.
// Target loop first tests equality, overwriting a matching identity record,
// then greater-than, inserting before it and resetting the scan to begin.
// After that scan, it appends only when the iterator equals the current end.
// BFME 1 874e38488 Zero Hour htree.cpp supplies the bone-capture purpose;
// target bytes and already-matched Control_Bone/Release_Bone supply this
// target-specific sorted-vector representation, not the donor flag layout.
// The record is Index, identity quaternion (0,0,0,1), zero translation, and a
// false world-space flag, matching the Control_Bone record model. The vector
// helpers keep the recovered Elem36 stand-in identity so the call sites mangle
// to the rowed STLport 36-byte vector bodies.
#include <windows.h>
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "../../../../../reference/shims/bfme2htree/htree.h"
#include <memory>

struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W; BfmeCapturedBoneRotation &operator=(const BfmeCapturedBoneRotation &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation &operator=(const BfmeCapturedBoneTranslation &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct CapturedTransform{BfmeCapturedBoneRotation Rotation;BfmeCapturedBoneTranslation Translation;};

struct Elem36{int Index;CapturedTransform Transform;bool WorldSpace;};

// Native placement construction is owned once, by the rowed 81-byte helper
// at 0x001610F0. Declare it; a forwarding COMDAT is not that retail body.
namespace _STL {
template<> void _Construct<Elem36, Elem36>(Elem36 *, const Elem36 &);
}
#include <vector>
namespace _STL {
template<> Elem36 *vector<Elem36>::insert(Elem36 *, const Elem36 &);
template<> void vector<Elem36>::_M_insert_overflow(Elem36 *, const Elem36 &, const __false_type &, unsigned int, bool);
// STLport's normal append algorithm, with an uninitialized empty dispatch
// tag: retail does not zero the tag byte, and the tag carries no value.
// Scoped here to preserve the independently verified shared providers.
template<> inline void vector<Elem36>::push_back(const Elem36 &v) {
 if(this->_M_finish != this->_M_end_of_storage._M_data) {
  _Construct(this->_M_finish,v);
  ++this->_M_finish;
 } else {
  __false_type tag;
  _M_insert_overflow(this->_M_finish,v,tag,1UL,true);
 }
}
}
typedef _STL::vector<Elem36, _STL::allocator<Elem36> > Elem36Vector;

// ?Capture_Bone@HTreeClass@@QAEXH@Z
void HTreeClass::Capture_Bone(int boneindex)
{
	// The seed retains the vector as its three 32-bit storage words.
	Elem36Vector &bones=*reinterpret_cast<Elem36Vector *>(OwnedSequence1C);
	Elem36 bone;
	bone.Index = boneindex;
	bone.WorldSpace = false;
	bone.Transform.Rotation.X=0.0f; bone.Transform.Rotation.Y=0.0f;
	bone.Transform.Rotation.Z=0.0f; bone.Transform.Rotation.W=1.0f;
	bone.Transform.Translation.X=0.0f; bone.Transform.Translation.Y=0.0f; bone.Transform.Translation.Z=0.0f;

	Elem36 *it = bones.begin();
	Elem36 *end = reinterpret_cast<Elem36 *>(OwnedSequence1C[1]);
 while (it != end) {
  if(it->Index == boneindex) {
   it->Index=boneindex;
   it->Transform.Rotation.X=0.0f; it->Transform.Rotation.Y=0.0f;
   it->Transform.Rotation.Z=0.0f; it->Transform.Rotation.W=1.0f;
   it->Transform.Translation.X=0.0f; it->Transform.Translation.Y=0.0f; it->Transform.Translation.Z=0.0f;
   it->WorldSpace=false;
   break;
  }
  if(it->Index > boneindex) {
   bones.insert(it, bone);
   it = bones.begin();
   break;
  }
  ++it;
 }
 if(it == reinterpret_cast<Elem36 *>(OwnedSequence1C[1])) bones.push_back(bone);
}
