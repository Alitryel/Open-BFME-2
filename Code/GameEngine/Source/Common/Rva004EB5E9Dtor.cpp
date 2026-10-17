// ??1Rva004EB5E9@@UAE@XZ
// cl: /O1 /G7 /arch:SSE /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail: 0x004EB5E9..0x004EB6DD, 244-byte virtual destructor.
// Identity: vtable VA 0x00C62928 slot 0 reaches deleting wrapper 0x004EB778,
// whose existing ABI names this destructor. Adjacent ctor 0x004EB583 initializes
// three 12-byte vector headers and the scalar fields below. The class name and
// element names remain unknown; the ctor's BfmeE16 type for the third header is
// a compatible source view, not independently established element identity.
// Target accesses prove pointer elements in the first two vectors, their
// unlink/notify/virtual-slot-0 cleanup, then vector erase and reverse member
// destruction. releaseStorage names the observed slot ABI, not a recovered name.
// Existing STLport/bfmealloc source supplies container behavior. /EHs keeps
// potentially throwing C free calls and the three retail unwind transitions;
// the local vector reference preserves the address reused at erase.
// The two pointer vectors are not vector<void *>: retail's unwind actions
// for +0x08 and +0x1C jump to the 14-byte free-first-pointer body 0x0007FAB3,
// not vector<void *>'s /Od destructor 0x00027370, so they are spelled with
// the element pointer type the loops use and emit no vector<void *> copies.
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
namespace _STL {
template <> vector<void *, allocator<void *> >::iterator vector<void *, allocator<void *> >::erase(iterator first, iterator last);
}
void __cdecl operator delete(void *p);
struct Rva002E36D5Node;
void Rva002E3714Unlink(Rva002E36D5Node *node);
class Rva0023D661 { public: void rva0023D661(int nodeAddress); };
class GameLogic;
extern GameLogic *TheGameLogic;
class Cleanup4EB5E9 { public: virtual void *releaseStorage(unsigned flags) = 0; };
#include "../../../Libraries/Include/Lib/BfmeE16.h"
class Rva004EB5E9 {
public: virtual ~Rva004EB5E9();
private:
 int count;
 _STL::vector<Cleanup4EB5E9 *> owned8;
 Cleanup4EB5E9 *single;
 int unknown18;
 _STL::vector<Cleanup4EB5E9 *> owned1C;
 _STL::vector<BfmeE16> data28;
 int unknown34,unknown38,unknown3C,unknown40,uniqueID,argument;
};
Rva004EB5E9::~Rva004EB5E9()
{
 Cleanup4EB5E9 **end = owned1C.end();
 for (Cleanup4EB5E9 **it=owned1C.begin();it != end;++it) {
  Cleanup4EB5E9 *p = *it;
  Rva002E3714Unlink((Rva002E36D5Node *)p);
  ((Rva0023D661 *)TheGameLogic)->rva0023D661((int)p);
  void *storage = 0;
  if (p) storage = p->releaseStorage(0);
  ::operator delete(storage);
 }
 count = 0;
 end = owned8.end();
 for (Cleanup4EB5E9 **it=owned8.begin();it != end;++it) {
  Cleanup4EB5E9 *p = *it;
  void *storage = 0;
  if (p) storage = p->releaseStorage(0);
  ::operator delete(storage);
 }
 // The range erase is the shared four-byte-pointer instantiation retail
 // calls; reach it through the vector<void *> spelling its row uses.
 _STL::vector<void *> &v = reinterpret_cast<_STL::vector<void *> &>(owned8);
 v.erase(v.begin(),v.end());
 if (single) {
  void *storage = single->releaseStorage(0);
  ::operator delete(storage);
 }
}
