// cl: /O2 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 random-access copy for the HTree captured-bone record.
// BFME1 reference a7c38d3b2597121f178ab5190b3062478823257d supplies the
// STL algorithm and quaternion/vector assignment definitions. Target HTree
// capture/control and vector-insert call sites prove the 36-byte record:
// index, a nested quaternion/translation transform, then the world-space flag.
// The nested transform is required for retail's +0x1C loop address bases.
// Record names preserve existing positional pins; original type names are unknown.
#include <vector>

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

template Elem36 *_STL::__copy_backward<Elem36 *,Elem36 *,int>(Elem36 *,Elem36 *,Elem36 *,const _STL::random_access_iterator_tag &,int *);
