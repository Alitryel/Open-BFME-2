// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP=
// GenericObjectCreationNugget::AnimSet from ObjectCreationList.cpp.
// Existing STLport placement copy 0x1F06B9 calls this 77-byte copy at0x1F0558.
// The reference fields are initial, flying and final animation names.
#include "ascii_string.h"
class GenericObjectCreationNugget {
public:
    struct AnimSet {
        AsciiString m_animInitial, m_animFlying, m_animFinal;
        AnimSet(const AnimSet &);
    };
};
inline GenericObjectCreationNugget::AnimSet::AnimSet(const AnimSet &other)
    : m_animInitial(other.m_animInitial), m_animFlying(other.m_animFlying),
      m_animFinal(other.m_animFinal) {}

// AnimSet copy is a header inline elsewhere: other units emit select-any
// copies, so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitGenericObjectCreationNuggetAnimSetCopy@@YAXPAUAnimSet@GenericObjectCreationNugget@@PBU12@@Z present-unmatched
void bfmeEmitGenericObjectCreationNuggetAnimSetCopy(GenericObjectCreationNugget::AnimSet *p, const GenericObjectCreationNugget::AnimSet *q)
{
	p->AnimSet::AnimSet(*q);
}
#pragma inline_depth()
