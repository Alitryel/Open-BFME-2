// cl: /DNDEBUG /MD /EHsc
// Native C730..C8F1 (450B): the getBounds callback. More than one argument
// returns undefined; one argument names the target coordinate space (an
// undefined one returns undefined), otherwise the receiver's own. It builds a
// fresh object -- the inlined Rva006D6360(0x1B, 8) / Rva006D6470Owner
// construction (vtables 0x00CEA228 then 0x00CEA264) from the 0xE176F4 pool,
// freed through 0x006F12F0 on unwind -- fetches the receiver's bounds through
// the rowed rva006E1DD0, offsets them by the target's +0x1C/+0x20 position,
// and stores the four as floats under pool strings 0xAD, 0xAE, 0xB0 and 0xB1
// through the rowed AptNativeHash::Set. Callback name address-derived.
// Shape notes: the stores go through an inline member setter, so both
// argument calls are evaluated before either is pushed (retail's ebx temp and
// merged stack cleanup); the right edge is offset first as in retail.
// Private views only; the Rva006D6360 / Rva006D6470Owner bodies stay with
// their rowed out-of-line owners in Rva006D6360Ctor.cpp.
class AptCIH;
class EAStringC;
class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isUndefined() const;
};
class AptCIH
{
public:
    void rva006E1DD0(void *);
};
class AptBasePtrStack {public:AptValue *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
struct Rect {float left,top,right,bottom;};
AptValue *Rva008A4EA0MakeFloat(float);
class AptNativeHash {public:AptNativeHash(int);void Set(const EAStringC *const,AptValue *const);int m_size;void *m_data;AptValue *m_proto,*m_prototype;unsigned int m_events;};
class BfmeAptValue006DCD20 {public:BfmeAptValue006DCD20(int);virtual ~BfmeAptValue006DCD20();unsigned int m_flags;};
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
void Rva006F12F0Free(void *,int);
EAStringC *Rva0070B4F0GetString(int);
class Rva006D6360 : public BfmeAptValue006DCD20
{
public:
 Rva006D6360(int type,int size) : BfmeAptValue006DCD20(type),m_hash(size) {}
 virtual ~Rva006D6360();
 AptNativeHash m_hash;
};
class Rva006D6470Owner : public Rva006D6360
{
public:
 Rva006D6470Owner(int type,int size) : Rva006D6360(type,size)
 {
  *(unsigned char *)&m_bits=0;
  m_bits&=0xFFFFFCFF;
 }
 virtual ~Rva006D6470Owner();
 static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 void setMember(const EAStringC *name,AptValue *value){m_hash.Set(name,value);}
 unsigned int m_bits;
};
AptValue *__cdecl Rva006EC730GetBounds(AptValue *self,int count)
{
 if(count>1)return gpUndefinedValue;
 AptCIH *target=self->c_cih(false);
 if(count==1){
  AptValue *arg=g_aptDateInterpreter.stack.At(0);
  if(arg->isUndefined())return gpUndefinedValue;
  target=arg->c_cih(false);
 }
 Rva006D6470Owner *object=new Rva006D6470Owner(0x1B,8);
 Rect bounds;
 self->c_cih(false)->rva006E1DD0(&bounds);
 bounds.right-=((float *)target)[7];
 bounds.left-=((float *)target)[7];
 bounds.top-=((float *)target)[8];
 bounds.bottom-=((float *)target)[8];
 object->setMember(Rva0070B4F0GetString(0xAD),Rva008A4EA0MakeFloat(bounds.right));
 object->setMember(Rva0070B4F0GetString(0xAE),Rva008A4EA0MakeFloat(bounds.left));
 object->setMember(Rva0070B4F0GetString(0xB0),Rva008A4EA0MakeFloat(bounds.bottom));
 object->setMember(Rva0070B4F0GetString(0xB1),Rva008A4EA0MakeFloat(bounds.top));
 return (AptValue *)object;
}
