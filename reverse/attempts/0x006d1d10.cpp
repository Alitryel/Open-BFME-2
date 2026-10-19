// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.7681818181818182 date=2026-10-20
// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.7318181818181818 date=2026-10-19
// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.727 date=2026-10-17
// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.8380635624538064 date=2026-10-10
// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.8380635624538064 date=2026-10-09
// Both record constructors copy second; native loads [esp+0x38] after two pushes.
// The 615-byte body retains the original ownership operations and all prior comments.
// cl: /MD /EHsc
// List nodes hold a counted record reference; the push uses the rowed 0x006D15B0 node shape.
// WB 0x01752A20 shape: found = *find(first), it = findByName(target), end() test, erase only when found.
class Rva006DB270 {public:void freeBlock(void*,int);};
class Rva006DB160 {public:void *allocBlock(int);};
extern Rva006DB270*g_pChainBlockAllocator;
struct Rva006D0280 {~Rva006D0280();int m_useCount;};
class Rva006D07E0Key {public:__forceinline static int dec(int*p){return --*p;}
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&key):m_object(key.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*r=m_object;if(r&&dec(&r->m_useCount)==0){Rva006D0280*p=m_object;if(p){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}}
 Rva006D0280*m_object;
};
class Rva006D0790 {public:
 Rva006D0790(Rva006D07E0Key,void*);
 static void *operator new(unsigned size){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void*p){g_pChainBlockAllocator->freeBlock(p,0x10);}
 int count;Rva006D07E0Key key;void *name;bool flag;
};
class Rva006D0790Ref {public:__forceinline static int dec(int*p){return --*p;}
 Rva006D0790Ref(Rva006D0790*p):ptr(p){if(p)++p->count;}
 Rva006D0790Ref(const Rva006D0790Ref&o):ptr(o.ptr){if(ptr)++ptr->count;}
 ~Rva006D0790Ref(){Rva006D0790*p=ptr;if(p&&dec(&p->count)==0){p->key.~Rva006D07E0Key();g_pChainBlockAllocator->freeBlock(p,0x10);}}
 Rva006D0790*operator->()const{return ptr;}
 Rva006D0790*ptr;
};
class BfmeNodeVMU {public:Rva006D0790Ref entry;BfmeNodeVMU *next;};
class BfmeListVMU {public:void bfmeEraseVMU(BfmeNodeVMU**);BfmeNodeVMU*head;};
struct Rva006D07E0Iterator {Rva006D07E0Iterator(BfmeNodeVMU*p):node(p){} Rva006D0790Ref&operator*()const{return node->entry;} BfmeNodeVMU*node;};
class Rva006D07E0List {public:Rva006D07E0Iterator find(Rva006D07E0Key);BfmeNodeVMU*head;};
class AptLinker {public:void rva006D1450(Rva006D07E0Key);};
struct Rva006D15B0Node {
 Rva006D15B0Node(int *const *handle){m_count=*handle;if(m_count!=0)++*m_count;m_next=0;}
 static void *operator new(unsigned int size){return (*(Rva006DB160**)&g_pChainBlockAllocator)->allocBlock((int)size);}
 static void operator delete(void *,unsigned int){}
 int *m_count;Rva006D15B0Node *m_next;
};
class Rva006D15B0Stack {public:void rva006D15B0(int *const *handle);Rva006D15B0Node *m_head;};
inline void Rva006D15B0Stack::rva006D15B0(int *const *handle){Rva006D15B0Node *node=new Rva006D15B0Node(handle);node->m_next=m_head;m_head=node;}
class Rva006D1D10 {public:
 struct Iter{BfmeNodeVMU*node;Iter(BfmeNodeVMU*n):node(n){}
  bool operator==(const Iter&o)const{return node==o.node;} bool operator!=(const Iter&o)const{return node!=o.node;}
  Iter&operator++(){node=node->next;return *this;} Rva006D0790Ref&operator*()const{return node->entry;}};
 Iter begin(){return Iter(head);}
 Iter end(){return Iter(0);}
 Iter findByName(void*name){for(Iter it=begin();it!=end();++it)if((*it)->name==name)return it;return end();}
 void erase(Iter it){((BfmeListVMU*)this)->bfmeEraseVMU(&it.node);}
 void push_front(const Rva006D0790Ref&r){((Rva006D15B0Stack*)this)->rva006D15B0((int *const *)&r);}
 void update(Rva006D07E0Key first,Rva006D07E0Key second);
 BfmeNodeVMU*head;
};
void Rva006D1D10::update(Rva006D07E0Key first,Rva006D07E0Key second){
 ((AptLinker*)this)->rva006D1450(second);
 Rva006D0790Ref found=*((Rva006D07E0List*)this)->find(first);
 void*name=found->name;
 Iter it=findByName(name);
 if(it==end()){push_front(Rva006D0790Ref(new Rva006D0790(second,name)));}
 else{erase(it);push_front(Rva006D0790Ref(new Rva006D0790(second,name)));}
}
