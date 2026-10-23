// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>






// The element is GenericObjectCreationNugget::AnimSet: the destroy loop's only
// call goes to its rowed destructor at 0x001F0495 (ObjectCreationList.cpp), and
// that unit emits this same __destroy_aux for vector<AnimSet>. Three AsciiStrings.
class GenericObjectCreationNugget
{
public:
	struct AnimSet { void *m_animInitial; void *m_animFlying; void *m_animFinal; ~AnimSet(); };
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<GenericObjectCreationNugget::AnimSet *>(GenericObjectCreationNugget::AnimSet *, GenericObjectCreationNugget::AnimSet *, _STL::__false_type const &);
