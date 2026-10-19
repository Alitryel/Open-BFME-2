// ?rva00475F61@Rva00475F61Iface@@UAEXAAV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z
// partial score=0.38 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// ?rva00475F61@HordeContain@@UAEXXZ
// partial score=0.017 date=2026-10-17
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// STLport 4.5.3 vector<T>::push_back for element types whose push_back sits
// unclaimed in retail: the 55-byte body that copy-constructs at _M_finish
// through an out-of-line _Construct and otherwise calls _M_insert_overflow
// with __false_type.  Element types are code-generation views sized from the
// stride push_back adds to _M_finish (the stlport_pod_vector_bodies.cpp
// convention).  Where retail's _Construct callee is already rowed under a
// plain type name, that name is reused; otherwise the element is named after
// the push_back address and both callees are pinned at the addresses the
// retail REL32s prove.  No element layout beyond its size is claimed.
//
//   push_back   stride  _Construct  _M_insert_overflow  element
//   0x000475F2A   4     0x004740AD  0x00475BE8          Rva00475F2AElement
// ---------------------------------------------------------------------------
// Minimal views of the types this body walks across.  Only the members the
// disassembly proves are declared, at the exact offsets it uses.
// ---------------------------------------------------------------------------
// STLport vector<Object*> receiver of the trailing push_back.
// The 4-byte element appended by vector<Rva00475F2AElement>::push_back.
// Per-rank record: first word is a list<Object*> node chain, second the
// ThingTemplate used by isEquivalentTo.
// Interaction class at owner-0x11c: the replacement recorder.
// Minimal Object/Thing view for the slots the body touches.
// ---------------------------------------------------------------------------
// Out-of-line stubs pinned to retail addresses.  Only declarations: these are
// defined in their own translation units.
// ---------------------------------------------------------------------------
// The preceding bank comments are historical. Native RET4 requires an output vector;
// +0x60 is an ID/index map, and the temporary batches are vector<list<Object *> >.
template<class T> class Rva001EB984PoolAllocator;
namespace _STL {
template<class A,class B> Rva001EB984PoolAllocator<B> &__stl_alloc_rebind(Rva001EB984PoolAllocator<A> &,const B *);
template<class A,class B> Rva001EB984PoolAllocator<B> __stl_alloc_create(const Rva001EB984PoolAllocator<A> &,const B *);
}
#include "ascii_string.h"
#include <list>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include <string.h>
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LatchRestore.h"

class ThingTemplate;
class Team;
class Player;
class Object;
class AICommandInterface;
class Rva00475F61Contain;
struct Rva0046E6EAObject;
struct Rva0046E6EACoord;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *,const Rva0046E6EACoord *,Rva0046E6EACoord *,bool); };

struct Coord3D {
    float x, y, z;
    Coord3D() {}
    __forceinline Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
    __forceinline void scale(float f) { x *= f; y *= f; z *= f; }
    __forceinline void add(const Coord3D &other) { x += other.x; y += other.y; z += other.z; }
};
class Matrix3D {
public:
    float m[3][4];
    __forceinline Matrix3D(const Matrix3D &other) {
        m[0][0]=other.m[0][0]; m[0][1]=other.m[0][1]; m[0][2]=other.m[0][2]; m[0][3]=other.m[0][3];
        m[1][0]=other.m[1][0]; m[1][1]=other.m[1][1]; m[1][2]=other.m[1][2]; m[1][3]=other.m[1][3];
        m[2][0]=other.m[2][0]; m[2][1]=other.m[2][1]; m[2][2]=other.m[2][2]; m[2][3]=other.m[2][3];
    }
};
class Thing {
public:
    const Coord3D *getUnitDirectionVector2D() const;
    void setPosition(const Coord3D *);
    void setTransformMatrix(const Matrix3D *);
    void *vtbl;
    const ThingTemplate *m_template;
    float m_transform[12];
    Coord3D m_position;
};
enum ObjectStatusTypes { OBJECT_STATUS_NONE=0 };
enum WeaponSetType { WEAPONSET_NONE=0 };
enum CommandSourceType { CMD_NONE=0 };
class AICommandInterface { public: virtual void aiCommandInterfaceAnchor(); void aiIdle(CommandSourceType); };
class Rva0028B7AELeaGetter { public: void *get() const; };
class Rva00475F61AIUpdate;
class Object : public Thing {
public:
    Player *getControllingPlayer() const;
    bool testStatus(ObjectStatusTypes) const;
    void bfmeTransferReplacementState(Object *);
    void *rva0028C197() const;
    void setWeaponSetFlag(WeaponSetType);
    char pad44[0x74-0x44];
    ObjectID m_id;
    char pad78[0xB8-0x78];
    float m_b8;
    char padBC[0x258-0xBC];
    Rva00475F61AIUpdate *m_ai;
    __forceinline ObjectID getID() const { return m_id; }
    __forceinline const ThingTemplate *getTemplate() const { return m_template; }
    __forceinline Rva00475F61AIUpdate *getAI() const { return m_ai; }
    char pad25C[0x284-0x25C];
    unsigned int m_mask[32];
};
class ThingTemplate {
public:
    bool isEquivalentTo(const ThingTemplate *) const;
    char pad[0x115];
    unsigned char m_flags115;
};
class BfmeD975 { public: char bfmeGo975D(int); };
class Rva00475F61BaseBitset { public: void merge(const Rva00475F61BaseBitset &); };
struct Rva00475F61Result { char pad[0x2B4]; bool flag; };
struct Rva00475F61Rank { int key; char pad[0x18]; };
struct Rva00475F61Name { AsciiString name; AsciiString memberName; int key; };
struct Rva00475F61ModuleData {
    char pad[0x1A4];
    _STL::vector<Rva00475F61Name *> names;
    char pad1B0[0x24C-0x1B0];
    bool m_sameRank;
};
class Player { public: char pad[0x2EC]; Team *m_defaultTeam; };
struct CreateMask { unsigned int bits[4]; };
class ThingFactory { public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *,Team *,const CreateMask *,bool);
};
class Pathfinder { public: void AddObjectToPathfindMap(Object *); };
class AI { public: char pad[0x10]; Pathfinder *m_pathfinder; };
extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
typedef _STL::list<Object *> MemberList;

class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DB8FEC;
extern void *g_freeList001EB130;
template<class T> class Rva001EB984PoolAllocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef unsigned int size_type;
    typedef int difference_type;
    template<class U> struct rebind { typedef Rva001EB984PoolAllocator<U> other; };
    Rva001EB984PoolAllocator() {}
    template<class U> Rva001EB984PoolAllocator(const Rva001EB984PoolAllocator<U> &) {}
    T *allocate(unsigned int, const void * = 0) { return (T *)g_freelistPool00DB8FEC.pop(); }
    void deallocate(T *p,unsigned int) { *(void **)p=g_freeList001EB130; g_freeList001EB130=p; }
    void construct(T *p,const T &v) { new(p) T(v); }
    void destroy(T *p) { p->~T(); }
    unsigned int max_size() const { return (unsigned int)-1/sizeof(T); }
};
namespace _STL {
template<class A,class B> inline Rva001EB984PoolAllocator<B> &__stl_alloc_rebind(Rva001EB984PoolAllocator<A> &a,const B *) {
    return (Rva001EB984PoolAllocator<B> &)a;
}
template<class A,class B> inline Rva001EB984PoolAllocator<B> __stl_alloc_create(const Rva001EB984PoolAllocator<A> &,const B *) {
    return Rva001EB984PoolAllocator<B>();
}
}
typedef _STL::list<Object *,Rva001EB984PoolAllocator<Object *> > PooledMemberList;
typedef char PoolListExtent[sizeof(PooledMemberList)==4 ? 1 : -1];
namespace _STL {
template <> list<Object *,Rva001EB984PoolAllocator<Object *> >::iterator
list<Object *,Rva001EB984PoolAllocator<Object *> >::insert(
    list<Object *,Rva001EB984PoolAllocator<Object *> >::iterator,Object *const &);
template <> _List_base<Object *,Rva001EB984PoolAllocator<Object *> >::~_List_base();
}

class Rva00475F61AIUpdate {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142(int);
    char gap[0x20-4];
    AICommandInterface command;
    __forceinline AICommandInterface *commands() { return &command; }
};
class Rva00475F61Contain {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30(const PooledMemberList *);
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual Rva00475F61Result *slot134();
};
class Rva00475F61Iface {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42(Object *);
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67(MemberList *);
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void rva00475F61(_STL::vector<Object *> &out);
    char pad004[0x60-4];
    _STL::map<int,int> m_indices;
    _STL::vector<Rva00475F61Rank> m_ranks;
    char pad078[0x150-0x78];
    ObjectID m_held;
    __forceinline Rva00475F61Rank &record(int index) { return m_ranks[index]; }
};

namespace _STL {
template <> vector<PooledMemberList>::~vector();
template <> _List_base<Object *,allocator<Object *> >::~_List_base();
}
void Rva00475F61Iface::rva00475F61(_STL::vector<Object *> &out)
{
    out.erase(out.begin(),out.end());
    slot122();
    Object *self=*(Object **)((char *)this-0x114);
    Matrix3D transform(*(const Matrix3D *)self->m_transform);
    _STL::vector<PooledMemberList> groups;
    groups.erase(groups.begin(),groups.end());
    MemberList members;
    slot67(&members);
    Object *held=TheGameLogic->findObjectByID(m_held);
    if(held) {
        MemberList::iterator it=_STL::find(members.begin(),members.end(),held);
        if(it!=members.end()) members.erase(it);
        TheGameLogic->destroyObject(held);
    }
    Coord3D offset=*(*(Object **)((char *)this-0x114))->getUnitDirectionVector2D();
    offset.scale((*(Object **)((char *)this-0x114))->m_b8*0.5f);
    for(MemberList::iterator it=members.begin();it!=members.end();++it) {
        Object *obj=*it;
        if(obj->getAI()) obj->getAI()->slot142(0);
        bool found=false;
        unsigned groupCount=groups.size();
        for(unsigned i=0;i<groupCount;++i) {
            Object *first=groups[i].front();
            bool equal=first->getTemplate()->isEquivalentTo(obj->getTemplate());
            if(equal && (*(Rva00475F61ModuleData **)((char *)this-0x118))->m_sameRank) {
                _STL::map<int,int> &indices=m_indices;
                int a=record(indices[first->getID()]).key;
                int b=record(indices[obj->getID()]).key;
                if(a!=b) equal=false;
            }
            if(equal) { groups[i].push_back(obj); found=true; break; }
        }
        if(!found) {
            PooledMemberList group;
            group.push_back(obj);
            groups.push_back(group);
        }
        slot42(obj);
    }
    _STL::vector<Rva00475F61Name *> &names=(*(Rva00475F61ModuleData **)((char *)this-0x118))->names;
    unsigned groupCount=groups.size();
    for(_STL::vector<Rva00475F61Name *>::iterator it=names.begin();it!=names.end();++it) {
        Rva00475F61Name *entry=*it;
        bool used=false;
        const ThingTemplate *tmpl=TheThingFactory->findTemplate(entry->name);
        Object *replacement=0;
        if(tmpl->m_flags115 & 0x20) {
            Team *team=(*(Object **)((char *)this-0x114))->getControllingPlayer()->m_defaultTeam;
            CreateMask mask;
            memset(&mask,0,sizeof(mask));
            replacement=TheThingFactory->newObject(tmpl,team,&mask,false);
        }
        if(replacement) {
            if(self->testStatus((ObjectStatusTypes)0x3E)) self->bfmeTransferReplacementState(replacement);
            Coord3D pos=(*(Object **)((char *)this-0x114))->m_position;
            pos.add(offset);
            offset.scale(-1.0f);
            ((Rva0046E6EA *)((char *)this-0x11C))->rva0046E6EA((Rva0046E6EAObject *)replacement,
                (Rva0046E6EACoord *)&pos,(Rva0046E6EACoord *)*(Object **)((char *)this-0x114),true);
            replacement->setPosition(&pos);
            transform.m[0][3]=pos.x;
            transform.m[1][3]=pos.y;
            transform.m[2][3]=pos.z;
        }
        bool weaponFlag=false;
        for(unsigned i=0;i<groupCount;++i) {
            Object *first=groups[i].front();
            char equal=((BfmeD975 *)first->getTemplate())->bfmeGo975D((int)&entry->memberName);
            if(equal && (*(Rva00475F61ModuleData **)((char *)this-0x118))->m_sameRank) {
                _STL::map<int,int> &indices=m_indices;
                if(record(indices[first->getID()]).key != entry->key) equal=false;
            }
            if(equal) {
                Rva00475F61Contain *contain=replacement ? (Rva00475F61Contain *)replacement->rva0028C197() : 0;
                if(contain && replacement) {
                    Object *old=groups[i].front();
                    if(old) {
                        weaponFlag=(((unsigned char *)((const Rva0028B7AELeaGetter *)old)->get())[3]&1)!=0;
                        ((_STL::_Base_bitset<32> *)replacement->m_mask)->_M_do_or(*(const _STL::_Base_bitset<32> *)old->m_mask);
                    }
                    contain->slot30(&groups[i]);
                    used=true;
                    Rva00475F61Result *owner=contain->slot134();
                    LatchRestore<bool> restore(owner->flag,true);
                    if(weaponFlag) replacement->setWeaponSetFlag((WeaponSetType)0x18);
                } else {
                    for(PooledMemberList::iterator m=groups[i].begin();m!=groups[i].end();++m) {
                        Object *old=*m;
                        old->m_ai->commands()->aiIdle((CommandSourceType)2);
                        out.push_back(old);
                    }
                }
                break;
            }
        }
        if(used && replacement) {
            replacement->setTransformMatrix(&transform);
            replacement->m_ai->commands()->aiIdle((CommandSourceType)2);
            TheAI->m_pathfinder->AddObjectToPathfindMap(replacement);
            out.push_back(replacement);
        } else if(replacement) TheGameLogic->destroyObject(replacement);
    }
    TheGameLogic->destroyObject(*(Object **)((char *)this-0x114));
}
