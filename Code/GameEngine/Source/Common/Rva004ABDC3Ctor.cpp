// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 4ABDC3 constructs the pointer registry at +4 and clears +11.
// Retail 4ABE53 restores the same vtable; sets +11; destroys the registry.
// C549F0 slot zero is key collection4ABDDC; destruction is nonvirtual.
#include <set>
class Rva003ED658;
struct Rva004ABDDCEntry;
#include "../../Include/Common/ModuleKeyRegistry.h"

struct Rva004ABDDCEntry;
typedef _STL::set<Rva004ABDDCEntry *> ModuleKeyRegistrySet;
typedef _STL::_Rb_tree<Rva004ABDDCEntry *, Rva004ABDDCEntry *,
    _STL::_Identity<Rva004ABDDCEntry *>, _STL::less<Rva004ABDDCEntry *>,
    _STL::allocator<Rva004ABDDCEntry *> > ModuleKeyRegistryTree;
namespace _STL {
template <> void ModuleKeyRegistryTree::clear();
}

Rva004ABE53Dtor::Rva004ABE53Dtor() : m_destroying(0) {}
Rva004ABE53Dtor::~Rva004ABE53Dtor() { m_destroying = 1; }

// Keep the existing registry data-ledger symbol. This view adds no datum.
extern unsigned g_Va00E03CE0;
extern "C" int __cdecl atexit(void (__cdecl *callback)());
// Preserve the initializer's nonallocating placement operation. The standard
// void* placement-delete pair adds a non-retail EH cleanup with this compiler.
inline void *operator new(unsigned int, unsigned *where) { return where; }
void rva007B89C1();
void rva007B1CDC()
{
    new (&g_Va00E03CE0) Rva004ABE53Dtor;
    atexit(rva007B89C1);
}
void rva007B89C1()
{
    reinterpret_cast<Rva004ABE53Dtor *>(&g_Va00E03CE0)->~Rva004ABE53Dtor();
}
