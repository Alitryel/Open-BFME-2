// ?Rva00525CC5@Holder00526309@@QAEXPAUObj00526309@@@Z
// partial score=0.774 date=2026-10-17
// ?Rva00525CC5@Holder00526309@@QAEXPAUObj00526309@@@Z
// partial score=0.756 date=2026-10-15
// ?Rva00525CC5@Holder00526309@@QAEXPAUObj00526309@@@Z
// partial score=0.7 date=2026-10-14
// stlport
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?Rva00525CC5@Holder00526309@@QAEXPAUObj00526309@@@Z @0x00525CC5 213B.
// The add counterpart of the rowed removeHero at 0x005259B9 (same holder layout and
// views as InGameHeroSelectDataRemoveHero.cpp): checks the image provider 0x0033B634,
// returns when the object id is already in the hero list at +0x10, otherwise builds
// the {id, rank, 0} record (rank from 0x005C3180) and inserts it before the first
// entry whose object has a higher rank at template +0x638 (early game frames,
// counter at the game logic +0x40 below 6) or appends it, then notifies the
// listeners with the new node through the rowed 0x005258F8.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <list>

namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Object;class ThingTemplate;class Image;
enum ObjectID { INVALID_OBJECT_ID = 0 };
const Image *getButtonImage(ThingTemplate *,Object *);
int ComputeObjectRank(const Object *);
class ThingTemplate {public:char pad[0x638];int rank638;};
class Object {public:void *vptr;ThingTemplate *templ;char pad08[0x74-8];int id;};
class GameLogic { public: Object *findObjectByID(ObjectID id); };
extern GameLogic *TheGameLogic;
struct GameLogicFrameView { char pad[0x40]; unsigned int counter; };
struct BfmePod12 {int id,unknown,flash; BfmePod12(const BfmePod12 &); ~BfmePod12();};
struct HeroButtonInfo {int id,unknown,flash;};
typedef _STL::list<BfmePod12> HeroInfoList;
class Rva005259B9Listener {public:virtual void v0();virtual void v1();virtual void v2();virtual void removeHero(void *);virtual void removeBuilder(void *);virtual void addHero(void *);};
typedef void(Rva005259B9Listener::*HeroNotify)(void *);
struct Pod12Node00525D9A;
struct NodeRef00525D9A {NodeRef00525D9A(Pod12Node00525D9A*p):m_ptr(p){} Pod12Node00525D9A*m_ptr;};
class Holder00525D9A {
public:
 __declspec(noinline) void Rva005258F8(int,NodeRef00525D9A);
private:void *begin,*end,*capacity;unsigned int index;
};
struct Obj00526309;
class Holder00526309 : public Holder00525D9A {
public:
 __declspec(noinline) void Rva00525CC5(Obj00526309 *);
 HeroInfoList heroes;char builders[12];
};

void Holder00526309::Rva00525CC5(Obj00526309 *arg)
{
	Object *obj = reinterpret_cast<Object *>(arg);
	ThingTemplate *templ = obj->templ;
	if (!getButtonImage(templ, obj))
		return;
	for (HeroInfoList::iterator it = heroes.begin(); it != heroes.end(); ++it)
	{
		if (it->id == obj->id)
			return;
	}
	int id = obj->id;
	HeroButtonInfo record;
	record.unknown = ComputeObjectRank(obj);
	record.flash = 0;
	*(volatile int *)&record.id = id;
	_ReadWriteBarrier();
	HeroInfoList::iterator where;
	ThingTemplate *const tmpl = obj->templ;
	int rank = tmpl->rank638;
	unsigned int cnt = *(volatile unsigned int*)&reinterpret_cast<GameLogicFrameView *>(TheGameLogic)->counter;
	_ReadWriteBarrier();
	if ((cnt < 6 ? true : true))
	{
		HeroInfoList::iterator it = heroes.begin();
		HeroInfoList::iterator theEnd = heroes.end();
		do
		{
			Object *other = TheGameLogic->findObjectByID((ObjectID)it->id);
			if (other && rank < other->templ->rank638)
				break;
			++it;
		} while (it != theEnd);
		{
			HeroInfoList::iterator inserted = heroes.insert(it, reinterpret_cast<const BfmePod12 &>(record));
			where = inserted;
		}
	}
	else
	{
		heroes.push_back(reinterpret_cast<const BfmePod12 &>(record));
		where = heroes.end();
		--where;
	}
	union { HeroNotify method; int fn; } binding;
	binding.method = &Rva005259B9Listener::addHero;
	Rva005258F8(binding.fn, (Pod12Node00525D9A *)where._M_node);
}
