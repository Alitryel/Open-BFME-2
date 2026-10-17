// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /I.
// stlport
// Retail 0x00547CB6..0x00547DE9, 307B: populate the formation group-order
// positions. Callees are the rowed FormationAssistant::rva00424E77 (0x00424E77),
// Formation::rva0042245F (0x0042245F), Formation::optimizeUnits (0x0042550E) and
// the thiscall release 0x00423FBD. Each slot position is written from the slot
// offset first and then read back for the origin add, which gives retail's
// register-register addss.
#include <list>
#include <hash_map>
#include <string>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
// bfme link decl-only end
class Object{public:char pad[0x74];ObjectID id;};
class Rva001EB769{public:void rva001EB769() throw();};
namespace _STL{
template<> inline _List_base<Object*,allocator<Object*> >::~_List_base(){((Rva001EB769*)this)->rva001EB769();}
}
extern GameLogic*TheGameLogic;
namespace rts{template<class T>struct hash{size_t operator()(const T&v)const{return(size_t)v;}};}
typedef _STL::hash_map<ObjectID,Coord3D,rts::hash<ObjectID>,_STL::equal_to<ObjectID> > ObjectCoord3DMap;
struct Rva00424E77Slot{int unknown0;ObjectID id;char unknown8[16];float x,y;};
class Rva001EB130Holder;
class Formation{public:void rva0042245F(float);void optimizeUnits(const Coord3D*);Rva00424E77Slot*begin,*end;};
class FormationAssistant{public:Formation*rva00424E77(int,Rva001EB130Holder*,const Coord3D*);};
// The formation is released through the rowed thiscall 0x00423FBD with the
// assistant in ECX, as AIGroupRva00372571.cpp spells it.
class Rva00423FBDThis{public:void Delete(_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*);};
class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem*TheFormationAssistant;
class MoveToFormationGroupOrder{public:void rva00547CB6();
 char pad0[4];ObjectID*first,*last;char padC[0x18-0xc];int kind;Coord3D origin;float angle;bool flag2C;char pad2D[3];ObjectCoord3DMap positions;bool flag44;
};
void MoveToFormationGroupOrder::rva00547CB6(){
 _STL::list<Object*>objects;
 for(ObjectID*p=first;p!=last;++p){Object*object=TheGameLogic->findObjectByID(*p);if(object)objects.push_back(object);}
 if(!objects.empty()){
  Formation*formation=((FormationAssistant*)TheFormationAssistant)->rva00424E77(kind,(Rva001EB130Holder*)&objects,&origin);
  if(formation){
   formation->rva0042245F(angle);formation->optimizeUnits(&origin);
   for(Rva00424E77Slot*p=formation->begin;p!=formation->end;++p){
    Object*object=TheGameLogic->findObjectByID(p->id);
    if(object){const Coord3D &o=origin;const Rva00424E77Slot &slot=*p;Coord3D position;position.x=slot.x;position.y=slot.y;position.x=o.x+position.x;position.y=o.y+position.y;position.z=o.z;ObjectID id=object->id;positions[id]=position;}
   }
   ((Rva00423FBDThis*)TheFormationAssistant)->Delete((_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*)formation);
  }
 }
}
