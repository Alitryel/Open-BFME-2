// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /O1 /arch:SSE /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva004DFF2C@Rva004DFF2C@@QAEXPAX@Z, retail 0x004DFF2C..0x004E005E (306
// bytes, EH, RET 4): the byte-for-byte twin (identical masked instruction
// stream) of the group merge 0x00283114 (Rva00283114GroupMerge.cpp) over the
// same 40-byte group class (rowed ctor 0x00281A76): it differs only by the two
// rowed helpers it reaches, the first-match scan 0x004DFE4F (Rva00282B26.cpp)
// and the group add 0x004DFCE6. WB 0x0129C960 AIDefenseTree<Object>::addItemToTree
// supports the family identity, the owner class and method names stay
// address-derived.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class Object;
typedef void *(__cdecl *Rva004DFE4FCallback)(void *key);
// The 40-byte group built by the rowed constructor 0x00281A76; the member
// call 0x004DFCE6 keeps its pinned address-derived class spelling.
class Rva004DFCE6 { public: void rva004DFCE6(void *key, Rva004DFE4FCallback callback); };
class Rva00281A76
{
public:
 Rva00281A76(float);
 void add(void *key, Rva004DFE4FCallback callback) { ((Rva004DFCE6 *)this)->rva004DFCE6(key, callback); }
 bool active00; float radius04, centerX08, centerY0C, centerZ10; float padding14; bool selected18;
 _STL::vector<Object *> objects1C;
 ~Rva00281A76() {}
};
class Rva004DFE4F { public: int rva004DFE4F(void *key); };

// Native 004DFF2C..004E005E RET4: clear every group's active flag and run the
// rowed nested scan 0x004DFE4F. No match: build a new group from virtual slot
// zero's padding and append it. Otherwise merge each later active group into
// the first active one, then destroy it and erase its slot.
class Rva004DFF2C
{
public:
 virtual float padding() = 0;
 void rva004DFF2C(void *key);
private:
 char m_pad04[0xC];
 _STL::vector<Rva00281A76 *> m_groups;
 int m_1C;
 Rva004DFE4FCallback m_callback;
};

void Rva004DFF2C::rva004DFF2C(void *key)
{
 Rva00281A76 *group;
 _STL::vector<Rva00281A76 *>::iterator it;
 _STL::vector<Rva00281A76 *>::iterator end = m_groups.end();
 for (it = m_groups.begin(); it != end; ++it)
 {
  Rva00281A76 *g = *it;
  g->active00 = false;
 }
 int count = ((Rva004DFE4F *)this)->rva004DFE4F(key);
 if (count == 0)
 {
  group = new Rva00281A76(padding());
  group->add(key, m_callback);
  m_groups.push_back(group);
  return;
 }
 Rva00281A76 *first = 0;
 it = m_groups.begin();
 end = m_groups.end();
 while (first == 0 && it != end)
 {
  if ((*it)->active00)
   first = *it;
  ++it;
 }
 while (it != end)
 {
  if ((*it)->active00)
  {
   group = *it;
   _STL::vector<Object *> &objects = group->objects1C;
   _STL::vector<Object *>::iterator oend = objects.end();
   for (_STL::vector<Object *>::iterator o = objects.begin(); o != oend; ++o)
    first->add(*o, m_callback);
   objects.erase(objects.begin(), objects.end());
   delete group;
   it = m_groups.erase(it);
   end = m_groups.end();
  }
  else
   ++it;
 }
}
