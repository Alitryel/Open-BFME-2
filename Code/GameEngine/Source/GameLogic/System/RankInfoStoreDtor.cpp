// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// Native200280..20030F. BFME1 f989 RankInfoDestructors.cpp and ZH
// RankInfoStore::~RankInfoStore supply the signed deletion loop and clear.
// Target evidence: BE2704 table and rowed constructor/deleting destructor
// retain the existing Rva0022CA74 owner, vector at0C and SubsystemInterface
// base at0; GameEngine registration supports the rank-store role separately.
// Native slot0 flag0 followed by global delete requires ::delete, guarded
// by the donor's explicit null test. Pointer storage uses the already rowed
// void-pointer erase fold. Game allocator30830 retains native EH state0;
// ordinary CRT free is nonthrowing and incorrectly removes that transition.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
void Rva00030830FreeAllocation(void *);
// The rank vector is spelled with a unit-local pointer element (kept apart
// from RankInfoParse.cpp's vector<RankInfo *>), not vector<void *>:
// retail's unwind action for +0x0C jumps to the 14-byte free-first-pointer
// body 0x0007FAB3, not vector<void *>'s /Od destructor 0x00027370. Its clear
// still reaches the shared vector<void *> range erase.
struct Rva0022CA74Rank;
namespace _STL {
template<> inline void allocator<Rva0022CA74Rank *>::deallocate(Rva0022CA74Rank **p,unsigned int) const
{
 if(p) Rva00030830FreeAllocation(p);
}
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return _M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void *>::end() { return _M_finish; }
}
class SubsystemInterface
{
public:
 virtual ~SubsystemInterface();
private:
 char pad[8];
};
class RankInfo { public: virtual ~RankInfo(); };
class Rva0022CA74 : public SubsystemInterface
{
protected:
 virtual ~Rva0022CA74();
private:
 std::vector<Rva0022CA74Rank *> ranks;
};
Rva0022CA74::~Rva0022CA74()
{
 for(int i=0; i<(int)ranks.size(); ++i)
 {
  RankInfo *r=(RankInfo *)ranks[i];
  if(r) ::delete r;
 }
 std::vector<void *> &cleared=reinterpret_cast<std::vector<void *> &>(ranks);
 cleared.erase(cleared.begin(),cleared.end());
}
