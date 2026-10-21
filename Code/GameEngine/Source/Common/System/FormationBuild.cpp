// Native 00424E77..004251C4; WB 0113C210 FormationAssistant.cpp callgraph.
// Template selection, pooled Object list, repeated row placement and centered
// 32-byte placement records. The three native unwind states own the row list,
// pooled object list and unsigned position vector, in that order.
// Keep both list-base constructors and node/proxy helpers visible: together
// they prove the allocator temporaries do not escape and reproduce reuse of
// the dead type argument for the pooled header. No frame-forcing constructs.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include/Lib /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <deque>
#include "Coord3D.h"
void Rva00030830GameFree(void*);
namespace _STL {template<> __declspec(dllimport) __forceinline void allocator<unsigned>::deallocate(unsigned*p,size_t)const{if(p)Rva00030830GameFree(p);}}
class FreelistPool {public:void*pop();};
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {template<> __declspec(dllimport) __forceinline unsigned*allocator<unsigned>::allocate(size_t n,const void*)const{return n?(unsigned*)allocator<char>::allocate(n*sizeof(unsigned),0):0;}}
class Object;
class GameWindow;
struct BfmePod32 {int words[8];};
struct Rva00422D82Element {void *value;};
namespace _STL {
template<> Rva00422D82Element &_Deque_iterator<Rva00422D82Element,_Nonconst_traits<Rva00422D82Element> >::operator[](int) const;
struct _List_node_base {_List_node_base *next,*prev;};
template<class T>struct _List_node : _List_node_base {T data;};
template<class T,class Traits> struct _List_iterator {
 _List_node_base *_M_node;
 typedef T value_type;typedef T*pointer;typedef T&reference;typedef int difference_type;typedef bidirectional_iterator_tag iterator_category;
 _List_iterator(_List_node_base*n):_M_node(n){}
 T &operator*()const{return *(T*)(_M_node+1);}
 _List_iterator&operator++(){_M_node=_M_node->next;return *this;}
 _List_iterator operator++(int){_List_iterator t=*this;_M_node=_M_node->next;return t;}
 bool operator!=(const _List_iterator&o)const{return _M_node!=o._M_node;}
 bool operator==(const _List_iterator&o)const{return _M_node==o._M_node;}

 _List_iterator(const _List_iterator<T,_Nonconst_traits<T> >&o):_M_node(o._M_node){}
};
template<class T,class A> class _List_base {public:_List_base(const A&);_List_node_base *head;};
template<class T,class A=allocator<T> > class list {public:
 typedef _List_iterator<T,_Nonconst_traits<T> > iterator;
 typedef _List_iterator<T,_Const_traits<T> > const_iterator;
 iterator erase(iterator,iterator);
 void insert(iterator,const_iterator,const_iterator);
 
 __declspec(noinline) _List_node<T> *_M_create_node(const T&x){
  _List_node<T>*node=(_List_node<T>*)g_freelistPool00DB8FEC.pop();
  T*value=&node->data;
  if(value)*value=x;
  return node;
 }

 __declspec(noinline) iterator insert(iterator position,const T&x){
  _List_node<T>*node=_M_create_node(x);
  node->next=position._M_node;
  node->prev=position._M_node->prev;
  position._M_node->prev->next=node;
  position._M_node->prev=node;
  return iterator(node);
 }
 _List_node_base *head;
};
template<> void vector<BfmePod32>::reserve(unsigned);
template<> void vector<BfmePod32>::push_back(const BfmePod32&);
}
extern unsigned g_Va00E03174;
class Rva000799D0 {public:void rva000799D0();};
class Rva001EB769 {public:void rva001EB769() throw();};
class Rva001EB984Member {public:void *init(void*);};
struct FormationSlot16 {int candidate;Object*object;int width,height;};
struct FormationRowNode {_STL::_List_node_base link;_STL::vector<FormationSlot16> slots;};
class FreelistProxyHead {public:__declspec(noinline) void setup(const void*,void*value){*(void**)this=value;}};

void *rva000307F0_new(unsigned,int);
namespace _STL {
template<> __declspec(noinline) inline _List_base<Coord3D,allocator<Coord3D> >::_List_base(const allocator<Coord3D>&a){
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 _List_node_base*n=(_List_node_base*)rva000307F0_new(20,0);
 n->next=n;n->prev=n;head=n;
}
}
class FormationRowList:public _STL::_List_base<Coord3D,_STL::allocator<Coord3D> > {public:
 FormationRowList(const _STL::allocator<Coord3D>&a=_STL::allocator<Coord3D>()):_STL::_List_base<Coord3D,_STL::allocator<Coord3D> >(a){}
 ~FormationRowList(){((Rva000799D0*)this)->rva000799D0();}
 FormationRowNode *begin(){return (FormationRowNode*)head->next;}
 FormationRowNode *end(){return (FormationRowNode*)head;}
 unsigned size(){_STL::_List_node_base*p=head->next;_STL::_List_node_base*last=head;unsigned n=0;while(p!=last){p=p->next;++n;}return n;}
};
struct FormationObjectNode {_STL::_List_node_base link;Object *object;};
class Rva001EB130Holder {public:_STL::_List_node_base *head;};
template<class T> class Rva001EB984PoolAllocator {public:Rva001EB984PoolAllocator(){}};



namespace _STL {
template<> __declspec(noinline) inline _List_base<Object*,Rva001EB984PoolAllocator<Object*> >::_List_base(const Rva001EB984PoolAllocator<Object*>&a){
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();
 ((void**)n)[0]=n;((void**)n)[1]=n;head=(_List_node_base*)n;
}
}
class FormationObjectList:public _STL::_List_base<Object*,Rva001EB984PoolAllocator<Object*> > {public:
 FormationObjectList(const Rva001EB984PoolAllocator<Object*>&a=Rva001EB984PoolAllocator<Object*>()):_STL::_List_base<Object*,Rva001EB984PoolAllocator<Object*> >(a){}
 ~FormationObjectList(){((Rva001EB769*)this)->rva001EB769();}
 void push_back(Object *const&o){_STL::list<Object*> *p=(_STL::list<Object*>*)this;p->insert(_STL::list<Object*>::iterator(p->head),o);}
 FormationObjectNode*begin(){return (FormationObjectNode*)head->next;}
 FormationObjectNode*end(){return (FormationObjectNode*)head;}
};
class Rva00421A16 {public:
 Rva00421A16(const Coord3D &p):x(p.x),y(p.y),z(p.z){}
 Rva00421A16(const Rva00421A16&p):x(p.x),y(p.y),z(p.z){}
 ~Rva00421A16(){}
 float x,y,z;
};
class Rva00423D2FOwner {public:void rva00423D2F(Rva00421A16);};
class Rva00423D92 {public:
 typedef _STL::_List_iterator<GameWindow*,_STL::_Const_traits<GameWindow*> > ConstIter;
 typedef _STL::_List_iterator<GameWindow*,_STL::_Nonconst_traits<GameWindow*> > Iter;
 __declspec(noinline) void rva00423D92(ConstIter first2,ConstIter last2,const _STL::__false_type&){
  _STL::list<GameWindow*> *me=(_STL::list<GameWindow*>*)this;
  Iter first1(me->head->next),last1(me->head);
  for(;first1!=last1 && first2!=last2;++first1,++first2)*first1=*first2;
  if(first2==last2)me->erase(first1,last1);
  else me->insert(last1,first2,last2);
 }
};
class FormationTemplateRows {public:char vector[12];};
struct FormationTemplateRow24 {FormationTemplateRows cells;char extra[12];};
struct FormationTemplateView {_STL::vector<FormationTemplateRow24> rows;};
class Rva00421A57 {public:bool rva00421A57(int);};
struct Rva00174753Allocation {Rva00174753Allocation() throw();int header[3];};
class Formation:public Rva00174753Allocation {};
class Rva00421764 {public:Rva00421764(const void*,int,const void*);int words[8];};
class FormationAssistant {public:
 Formation *rva00424E77(int,Rva001EB130Holder*,const Coord3D*);
 bool rva0042481E(FormationRowList*,const FormationTemplateRows*,FormationObjectList*);
 char prefix[0x24];float rowSpacing,columnSpacing;
};
struct FormationObjectView {char prefix[0x438];unsigned char flags;};
Formation *FormationAssistant::rva00424E77(int type,Rva001EB130Holder*source,const Coord3D*origin) {
 typedef _STL::_Deque_iterator_base<void*> DequeBase;
 DequeBase *first=(DequeBase*)&g_Va00E03174;
 DequeBase *last=first+1;
 if(type==-1 || type<0 || (unsigned)type>(unsigned)last->_M_subtract(*first))return 0;
 typedef _STL::_Deque_iterator<Rva00422D82Element,_STL::_Nonconst_traits<Rva00422D82Element> > TemplateIterator;
 FormationTemplateView *formationTemplateView=(FormationTemplateView*)(*(TemplateIterator*)first)[type].value;
 if(!formationTemplateView)return 0;
 FormationRowList rows;
 FormationObjectList objects;
 for(FormationObjectNode*it=(FormationObjectNode*)source->head->next;it!=(FormationObjectNode*)source->head;it=(FormationObjectNode*)it->link.next) {
  Object *obj=it->object;
  if(obj && !(((FormationObjectView*)obj)->flags&1))objects.push_back(obj);
 }
 if(origin)((Rva00423D2FOwner*)&objects)->rva00423D2F(Rva00421A16(*origin));
 else {
  typedef _STL::_List_iterator<GameWindow*,_STL::_Const_traits<GameWindow*> > Iter;
  ((Rva00423D92*)&objects)->rva00423D92(Iter(source->head->next),Iter(source->head),_STL::__false_type());
 }
 for(int i=0;i<(int)formationTemplateView->rows.size();++i) {
  FormationTemplateRows *row=&formationTemplateView->rows[i].cells;
  if(rva0042481E(&rows,row,&objects)) {
   while(true) {
    FormationObjectNode *it;
    for(it=objects.begin();it!=objects.end();it=(FormationObjectNode*)it->link.next)
     if(((Rva00421A57*)row)->rva00421A57((int)it->object))break;
    if(it==objects.end())break;
    rva0042481E(&rows,row,&objects);
   }
  }
 }
 FormationRowNode *rowEnd=rows.end();
 if((FormationRowNode*)rowEnd->link.next==rowEnd)return 0;
 Formation *result=(Formation*)new Rva00174753Allocation;
 typedef _STL::_List_iterator<_STL::vector<FormationSlot16>,_STL::_Nonconst_traits<_STL::vector<FormationSlot16> > > RowIterator;
 unsigned rowCount=_STL::distance(RowIterator(rowEnd->link.next),RowIterator(&rowEnd->link));
 ((_STL::vector<BfmePod32>*)result)->reserve(((FormationRowNode*)rowEnd->link.next)->slots.size()*rowCount);
 FormationRowNode*firstRow=(FormationRowNode*)rowEnd->link.next;
 _STL::vector<unsigned> positions(firstRow->slots.size()+1);
 int y=0;
 for(FormationRowNode *it=((FormationRowNode*)rowEnd->link.next);it!=rowEnd;it=(FormationRowNode*)it->link.next) {
  int height=0;
  int width=0;
  for(unsigned i=0;i<it->slots.size();++i) {
   FormationSlot16 &slot=it->slots[i];
   if(slot.object) {
    positions[i]=width+slot.width/2;
    width=(int)((float)slot.width+(float)width+columnSpacing);
    const int &maxHeight=height>slot.height?height:slot.height;
    height=maxHeight;
   }
  }
  int center=(int)((width-columnSpacing)*0.5f);
  int step=1,sign=1;
  unsigned index=(it->slots.size()-1)/2;
  for(int n=it->slots.size();n>0;--n) {
   FormationSlot16 &slot=it->slots[index];
   int x=positions[index]-center;
   if(slot.object) {
    int offset[2]={x,y};
    ((_STL::vector<BfmePod32>*)result)->push_back(*(BfmePod32*)&Rva00421764(slot.object,slot.candidate,offset));
   }
   index+=step*sign;
   ++step;sign=-sign;
  }
  y=(int)((float)height+(float)y+rowSpacing);
 }
 return result;
}
