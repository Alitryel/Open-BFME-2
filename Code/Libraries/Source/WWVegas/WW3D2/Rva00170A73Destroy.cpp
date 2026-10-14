// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// Native complete9B loads the sole cdecl stack pointer into ECX then tail-calls existing RefCountPtr<TextureClass> destructor17098D. Real destruction-helper semantics follow STLport _construct.h _Destroy; original helper/template name is unproven, so preserve neutral address identity. No new pin; actual destructor provider streakRender.cpp.
// Reference revision: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d.
class TextureClass;
template<class T>class RefCountPtr{public:~RefCountPtr();};
extern "C" void Rva00170A73Destroy(RefCountPtr<TextureClass> *p){p->~RefCountPtr();}
