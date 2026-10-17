// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Constructor of ScriptList's 0x20-byte subrecords at 0x003B761E (41B).
// The subrecord holds two 12-byte vectors (built through the rowed
// vector_base at 0x00211E58 with a one-byte stack allocator temp, hence
// the EBP frame) plus two ints initialized to -1 (plain -1 stores take
// the or-form under /O1). The same body serves both the +0x0C and +0x2C
// members (called twice from the ScriptList constructor at 0x003B7720),
// so it carries one address-derived row. The element type is a stand-in:
// the image fixes only the 12-byte stride. Retail builds both vectors
// through the folded empty vector-base ctor at 0x00211E58 (not the
// BfmeE12 instance at 0x0007FAEA, whose allocator-proxy call differs), so
// the stand-in is the 12-byte Rva00390729Element whose base ctor is rowed
// there.

#include <vector>

struct Rva00390729Element { int opaque[3]; };

class Rva003B761E
{
public:
	Rva003B761E();

private:
	_STL::vector<Rva00390729Element> m_a;			// +0x00
	_STL::vector<Rva00390729Element> m_b;			// +0x0C
	int m_first;						// +0x18
	int m_second;						// +0x1C
};

// ??0Rva003B761E@@QAE@XZ
Rva003B761E::Rva003B761E() : m_first(-1), m_second(-1)
{
}
