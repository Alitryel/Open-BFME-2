// cl: /O2 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector copy construction, retail 0x00166110 (175 bytes).
// HTreeClass's verified copy constructor calls this for its +0x1C member.
// BFME1 a7c38d3b2597121f178ab5190b3062478823257d htree.cpp supplies
// hierarchy semantics; BFME2's captured-bone vector is target-specific.
// Its matched Capture_Bone/Control_Bone siblings establish the 36-byte
// record: index, quaternion, translation, and world-space flag. The original
// type name is unknown; retain the existing caller and allocator pin names.
// A memberwise translation copy retains the loop's +0x1C address bases.
// Advancing the source first retains retail's EAX/ECX induction registers.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end

struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W;
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct BfmePod36
{
    int Index;
    BfmeCapturedBoneRotation Rotation;
    BfmeCapturedBoneTranslation Translation;
    bool WorldSpace;

    BfmePod36() {}
    BfmePod36(const BfmePod36 &other)
        : Index(other.Index), Rotation(other.Rotation),
          Translation(other.Translation), WorldSpace(other.WorldSpace) {}
};

// Retail's allocation constructor already has an owner at 0x00162800.
// Keep it external instead of emitting a competing template definition.
namespace _STL {
template<> _Vector_base<BfmePod36, allocator<BfmePod36> >::_Vector_base(
    unsigned int, const allocator<BfmePod36> &);
}

class BfmeRva00166110
    : public _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >
{
public:
    BfmeRva00166110(const BfmeRva00166110 &other)
        : _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >(
              size_t(other._M_finish - other._M_start), other.get_allocator())
    {
        const BfmePod36 *last = other._M_finish;
        const BfmePod36 *first = other._M_start;
        BfmePod36 *out = this->_M_start;
        while (first != last) {
            new (out) BfmePod36(*first);
            ++first;
            ++out;
        }
        this->_M_finish = out;
    }

    _STL::allocator<BfmePod36> get_allocator() const
    {
        return _STLP_CONVERT_ALLOCATOR(
            (const _STL::allocator<BfmePod36> &)this->_M_end_of_storage,
            BfmePod36);
    }
};

// Retain the reference template's out-of-line get_allocator call shape.
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36> >;

// ?emitCapturedBoneVectorCopy absent-from-retail
void emitCapturedBoneVectorCopy(const BfmeRva00166110 &first,
                                const BfmeRva00166110 &second)
{
    BfmeRva00166110 copy(first);
    new (&copy) BfmeRva00166110(second);
}
