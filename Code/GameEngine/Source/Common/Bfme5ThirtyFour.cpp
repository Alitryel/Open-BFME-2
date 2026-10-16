// cl: /O2 /MD /EHsc
// A counted-handle getter and a doubly-linked unlink.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp); trimmed to the two T1
// bodies the sweep places.

class BfmeRefDB
{
public:
	int m_bfmeCount;					// +0x00
};

class BfmeHolderDB
{
public:
	BfmeHolderDB(void)
	{
		m_bfmeRef = 0;
	}

	BfmeHolderDB(const BfmeHolderDB &other)
	{
		BfmeRefDB *ref = other.m_bfmeRef;

		m_bfmeRef = ref;

		if (ref)
			++ref->m_bfmeCount;
	}

	~BfmeHolderDB(void)
	{
		if (m_bfmeRef)
			--m_bfmeRef->m_bfmeCount;
	}

	BfmeRefDB *m_bfmeRef;					// +0x00
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeHolderDB m_bfmeHolder;				// +0x04
};

// ?bfmeGet@Gen_00895650@@QBE?AVBfmeHolderDB@@XZ
BfmeHolderDB Gen_00895650::bfmeGet(void) const
{
	return m_bfmeHolder;
}

class Gen_008F7AC0
{
public:
	void bfmeUnlink(void);

private:
	int m_bfmeHead[5];					// +0x00
	Gen_008F7AC0 **m_bfmePrev;				// +0x14
	Gen_008F7AC0 *m_bfmeNext;				// +0x18
};

// ?bfmeUnlink@Gen_008F7AC0@@QAEXXZ
void Gen_008F7AC0::bfmeUnlink(void)
{
	*m_bfmePrev = m_bfmeNext;

	Gen_008F7AC0 *next = m_bfmeNext;

	if (next != 0)
		next->m_bfmePrev = m_bfmePrev;

	m_bfmePrev = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?unlink@PartitionData@@QAEXXZ=?bfmeUnlink@Gen_008F7AC0@@QAEXXZ")

// Growth helper 0x006D1130..0x006D1202. Semantic guide: BFME1
// Gen00896320Append.cpp at ba7ddda7, rva00896100. Target facts: signed
// capacity +4, count +0, pointer +8, one inline slot +12; unlike the donor,
// the copy helper receives two three-word iterator values by value.
// Neither the original container nor the iterator class name is known.
unsigned __cdecl bfmeDecVGO(unsigned *p);
void __cdecl bfmeDropVGO(void *p);
class BfmeRefVGO
{
public:
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &other);
	unsigned *m_bfmeP;
};
// The ref-counted assign (rowed 0x006CDB10, BfmeConv1355.cpp) is visible
// here as an out-of-line COMDAT copy of the same body: seeing that it never
// writes its argument lets MSVC drop the empty handles' destructors in
// insert (retail has no release call there) and keeps retail's slot choice.
class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *p);
};
__declspec(noinline) inline BfmeRefVGO &BfmeRefVGO::bfmeAssignVGO(const BfmeRefVGO &o)
{
	if (&o != this)
	{
		if (m_bfmeP && bfmeDecVGO(m_bfmeP) == 0)
			bfmeDropVGO(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			Rva00894D80Accessor::increment(m_bfmeP);
	}
	return *this;
}
class Rva006D1130Item : public BfmeRefVGO
{
public:
	Rva006D1130Item() { m_bfmeP = 0; }
	~Rva006D1130Item()
	{
		if (m_bfmeP && bfmeDecVGO(m_bfmeP) == 0)
			bfmeDropVGO(m_bfmeP);
	}
};
inline void rva006D1130RangeCheck(bool) {}
struct Rva006D1130Iterator
{
	BfmeRefVGO *position;
	BfmeRefVGO *begin;
	BfmeRefVGO *end;
	// Same release range check as Apt.cpp's PlaybackIterator (empty even in
	// the WB debug build); spelling the loop test through it keeps retail's
	// top-tested copy loop (0x006D05E0) instead of cl's rotated one.
	bool operator!=(const Rva006D1130Iterator &other) const
	{
		rva006D1130RangeCheck(begin == other.begin && end == other.end);
		return position != other.position;
	}
	Rva006D1130Iterator() {}
	Rva006D1130Iterator(BfmeRefVGO *p, BfmeRefVGO *b, BfmeRefVGO *e) : position(p), begin(b), end(e) {}
	int operator-(const Rva006D1130Iterator &other) const { return position - other.position; }
	Rva006D1130Iterator operator+(int amount) const { return Rva006D1130Iterator(position + amount, begin, end); }
	Rva006D1130Iterator operator++(int) {
		Rva006D1130Iterator old=*this;
		++position;
		return old;
	}
};
class Rva004A9DF3Element;
Rva004A9DF3Element *__cdecl Rva006CE3D0Resize(Rva004A9DF3Element *, int, int);
BfmeRefVGO *__cdecl Rva006D05E0Copy(Rva006D1130Iterator first,
	Rva006D1130Iterator last, BfmeRefVGO *result);
class Rva006D1130
{
public:
	void grow(int capacity);
	void insert(Rva006D1130Item *const &first, Rva006D1130Item *const &last,
		const Rva006D1130Iterator &position);
	void append(Rva006D1130Item *value);
	Rva006D1130Iterator begin() { return Rva006D1130Iterator(m_begin, m_begin, m_begin + m_count); }
	Rva006D1130Iterator end() { return Rva006D1130Iterator(m_begin + m_count, m_begin, m_begin + m_count); }
private:
	unsigned m_count;
	int m_capacity;
	Rva006D1130Item *m_begin;
	Rva006D1130Item m_inline[1];
};
void Rva006D1130::grow(int capacity)
{
	int current = m_capacity;
	if (capacity <= current)
		return;
	if (capacity <= 1)
	{
		m_capacity = capacity;
		return;
	}
	// The rowed ref-array resizer also allocates an empty array when called
	// with (0, 0, capacity+1), and destroys one when the last two args are 0.
	Rva006D1130Item *newData = (Rva006D1130Item *)
		Rva006CE3D0Resize(0, 0, capacity + 1);
	Rva006D1130Item *oldEnd = m_begin + m_count;
	Rva006D1130Iterator first(m_begin, m_begin, oldEnd), last(oldEnd, m_begin, oldEnd);
	Rva006D05E0Copy(first, last, newData);
	m_capacity = capacity;
	if (m_begin != m_inline)
		Rva006CE3D0Resize((Rva004A9DF3Element *)m_begin, 0, 0);
	m_begin = newData;
	const Rva006D1130Item empty;
	m_begin[m_count].bfmeAssignVGO(empty);
	__assume(empty.m_bfmeP == 0);
}

BfmeRefVGO *__cdecl Rva006D0460Copy(BfmeRefVGO *first, BfmeRefVGO *last, BfmeRefVGO *result);
BfmeRefVGO *__cdecl Rva006D04D0CopyBackward(Rva006D1130Iterator first, Rva006D1130Iterator last, BfmeRefVGO *result);
Rva006D1130Iterator __cdecl Rva006D0540Copy(BfmeRefVGO *first, BfmeRefVGO *last, Rva006D1130Iterator result);

// Native 6D1230..6D13D6 RET 0xC: range insert of [first, last) at position,
// the 4-byte-element twin of the matched Rva006CE660Vec::insert 0x006CE890
// (PlaybackBufferResize.cpp): in place when the capacity allows (copy at the
// end, or shift the tail with the backward copy 0x006D04D0 and copy into the
// gap with 0x006D0540, then store an empty terminator), otherwise grow to
// max(2 * capacity, count + added) and retry at the same offset. Calls and
// layout are target facts; the shape and names follow the sibling.
void Rva006D1130::insert(Rva006D1130Item *const &first, Rva006D1130Item *const &last,
	const Rva006D1130Iterator &position)
{
	int added = last - first;
	if (!added)
		return;
	int want = m_count + added;
	if (want < m_capacity)
	{
		Rva006D1130Item *end = m_begin + m_count;
		if (position.position == end)
		{
			Rva006D0460Copy(first, last, end);
			m_begin[want].bfmeAssignVGO(Rva006D1130Item());
		}
		else
		{
			BfmeRefVGO *begin = m_begin, *finish = end;
			Rva006D1130Iterator tail(finish, begin, finish);
			Rva006D04D0CopyBackward(position, tail, begin + ((position.position - begin) + added));
			Rva006D0540Copy(first, last, position);
			m_begin[want].bfmeAssignVGO(Rva006D1130Item());
		}
		m_count = want;
	}
	else
	{
		int next = (int)(2.0 * m_capacity);
		if (next < want)
			next = want;
		int offset = position - begin();
		grow(next);
		Rva006D1130Iterator at = begin() + offset;
		insert(first, last, at);
	}
}

// Native 6D13E0..6D141F RET4: append one element at end() through the
// unrowed range insert 0x006D1230 (two element references plus the position
// iterator), the 4-byte-element twin of the matched
// Rva006CE660Vec::append 0x006CEA90 (PlaybackBufferResize.cpp, 8-byte
// elements, insert 0x006CE890). Target facts: count at +0, data at +8, the
// last = value + 1 reference built in the argument slot, the by-value end
// iterator {data + count, data, data + count}. Names address-derived.
void Rva006D1130::append(Rva006D1130Item *value)
{
	Rva006D1130Item *last = value + 1, *first = value;
	insert(first, last, end());
}

// Target 6D07E0..6D085B: head at0; entry key at4; by-value counted
// owner parameter released through independently rowed pool providers.
// BFME1 ba7ddda7 Rva008951B0Find supplies the linked-list search guide;
// target uses a counted key instead of the donor's borrowed void pointer.
class Rva006DB270 { public: void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
// The independent EAStringC providers prove the 4-byte string ABI used
// by the 6D0660 comparison: C-string ctor6D4C80 equal6D3090 dtor6D3010.
class EAStringC {
public:
 EAStringC(const char *);
 EAStringC(const EAStringC&);
 ~EAStringC();
 bool IsEqualTo(const EAStringC *) const;
 int rva006D36C0(const EAStringC *) const;
 void *data;
};
class Rva006DB160 {public:void*allocBlock(int);};
void __cdecl Rva006D8680Free(void*,int);
struct Rva006D0280 {
 ~Rva006D0280();
 __forceinline Rva006D0280(const EAStringC*name):m_useCount(0),name8(*name),typeC(1),object14(0),buffer18(0){}
 __forceinline int increaseCount(){return ++m_useCount;}
 __forceinline int decreaseCount(){int &p=m_useCount;return --p;}
 __forceinline static void*operator new(unsigned int n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
 __forceinline static void operator delete(void*p,unsigned int n){Rva006D8680Free(p,n);}
 int m_useCount;
 int unknown4;
 EAStringC name8;
 int typeC;
 int argument10; void*object14;void*buffer18;
};
class Rva006D07E0Key {
public:
 Rva006D07E0Key(Rva006D0280 *p=0):m_object(p) {
  if(p) p->increaseCount();
 }
 Rva006D07E0Key(const Rva006D07E0Key &other) {
  m_object=other.m_object;
  if(m_object) m_object->increaseCount();
 }
 ~Rva006D07E0Key() {
  Rva006D0280 *r=m_object;
  if(r && r->decreaseCount()==0) {
   Rva006D0280 *p=m_object;
   if(p) { p->~Rva006D0280(); g_pChainBlockAllocator->freeBlock(p,0x1c); }
  }
 }
 Rva006D0280 *m_object;
};
struct Rva006D07E0Entry { int unknown0; Rva006D0280 *key4; };
struct Rva006D07E0Node { Rva006D07E0Entry *entry; Rva006D07E0Node *next; };
struct Rva006D07E0Iterator {
 Rva006D07E0Iterator(Rva006D07E0Node *p):node(p) {}
 Rva006D07E0Node *node;
};
class Rva006D07E0List {
public:
 Rva006D07E0Iterator find(Rva006D07E0Key key);
 Rva006D07E0Node *head;
};
Rva006D07E0Iterator Rva006D07E0List::find(Rva006D07E0Key key) {
 Rva006D07E0Node *node=head;
 while(node) {
  if(node->entry->key4==key.m_object) return Rva006D07E0Iterator(node);
  node=node->next;
 }
 return Rva006D07E0Iterator(0);
}

// Native Ghidra6D0660..6D0766; comparator called by6D0860 with
// counted owner key. The provider is at14; its string table is28/2c
// with10-byte stride (hex). All offsets are target facts; purpose and
// original owner/table names are unknown.
struct Rva006D0660Record { const char *text; char unknown4[12]; };
struct Rva006D0660Table {
 char unknown0[0x28];
 int count28;
 Rva006D0660Record *records2c;
};
class Rva006D0660 {
public:
 int contains(Rva006D07E0Key key);
 char unknown0[0x14];
 Rva006D0660Table *table14;
};
int Rva006D0660::contains(Rva006D07E0Key key) {
 for(int i=0;i<table14->count28;++i) {
  if(EAStringC(table14->records2c[i].text).IsEqualTo(&key.m_object->name8))
   return 1;
 }
 return 0;
}

// Native6D0460..6D04C4: raw four-byte owner range copy. Semantic
// guide BFME1 ba7ddda7 Rva008953C0RefRangeCopy.cpp; target's pooled
// owner release uses existing6D0280/6DB270 providers and1c bytes.
BfmeRefVGO *__cdecl Rva006D0460Copy(BfmeRefVGO *first,
 BfmeRefVGO *last, BfmeRefVGO *result) {
 if(first!=last) {
  do {
   BfmeRefVGO *destination=result++;
   if(first!=destination) {
    unsigned *old=destination->m_bfmeP;
    if(old && --*old==0) {
     Rva006D0280 *p=(Rva006D0280 *)destination->m_bfmeP;
     if(p) {
      p->~Rva006D0280();
      g_pChainBlockAllocator->freeBlock(p,0x1c);
     }
    }
    destination->m_bfmeP=first->m_bfmeP;
    if(destination->m_bfmeP) ++*destination->m_bfmeP;
   }
   ++first;
  } while(first!=last);
 }
 return result;
}

// Native 6D05E0..6D0656 RET0: the forward copy grow (0x006D1130) calls,
// two three-word source iterators by value and a raw output pointer. The
// post-incremented source copy is retail's two dead begin/end stores; each
// element is released and retained as in 0x006D0460. Target facts: the
// ABI, loop head (top test against last.position) and refcount sequence.
// Original algorithm name unknown.
BfmeRefVGO *__cdecl Rva006D05E0Copy(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result) {
 while(first!=last) {
  BfmeRefVGO *destination=result++;
  Rva006D1130Iterator source=first++;
  if(source.position!=destination) {
   unsigned *old=destination->m_bfmeP;
   if(old && --*old==0) {
    Rva006D0280 *p=(Rva006D0280 *)destination->m_bfmeP;
    if(p) {
     p->~Rva006D0280();
     g_pChainBlockAllocator->freeBlock(p,0x1c);
    }
   }
   destination->m_bfmeP=source.position->m_bfmeP;
   if(destination->m_bfmeP) ++*destination->m_bfmeP;
  }
 }
 return result;
}

// Native6D04D0..6D0537. Two three-word source iterators and raw
// output start proven by the two12-byte pushes at native caller6D1306;
// walks backward over the pointer difference, retaining
// each replacement exactly as6D0460. Original algorithm name unknown.
BfmeRefVGO *__cdecl Rva006D04D0CopyBackward(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result) {
 int count=last.position-first.position;
 --last.position;
 result+=count-1;
 while(count) {
  if(last.position!=result) {
   unsigned *old=result->m_bfmeP;
   if(old && --*old==0) {
    Rva006D0280 *p=(Rva006D0280 *)result->m_bfmeP;
    if(p) {
     p->~Rva006D0280();
     g_pChainBlockAllocator->freeBlock(p,0x1c);
    }
   }
   result->m_bfmeP=last.position->m_bfmeP;
   if(result->m_bfmeP) ++*result->m_bfmeP;
  }
  --last.position;
  --result;
  --count;
 }
 return result;
}

// Native6D0540..6D05D1, including RET before the INT3 padding:
// raw source range and a by-value three-word output iterator. The
// returned iterator carries output position plus unchanged begin/end.
Rva006D1130Iterator __cdecl Rva006D0540Copy(BfmeRefVGO *first,
 BfmeRefVGO *last, Rva006D1130Iterator result) {
 if(first!=last) {
  do {
   Rva006D1130Iterator destination=result++;
   if(first!=destination.position) {
    unsigned *old=destination.position->m_bfmeP;
    if(old && --*old==0) {
     Rva006D0280 *p=(Rva006D0280 *)destination.position->m_bfmeP;
     if(p) {
      p->~Rva006D0280();
      g_pChainBlockAllocator->freeBlock(p,0x1c);
     }
    }
    destination.position->m_bfmeP=first->m_bfmeP;
    if(destination.position->m_bfmeP) ++*destination.position->m_bfmeP;
   }
   ++first;
  } while(first!=last);
 }
 return result;
}

// Native6D0A30..6D0A82: same counted-owner family as6D07E0.
// Head0 nodes carry owner0/next4. Its existing compare provider6D36C0
// is the signed zero-equality string operation at owner8. Returned
// counted value supplies the construction slot that the old out-pointer
// reconstruction had to force with a volatile local.
struct Rva006D0A30Node { Rva006D0280 *entry; Rva006D0A30Node *next;
 Rva006D0A30Node(Rva006D0280*p):entry(p),next(0){}
 __forceinline static void*operator new(unsigned int n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
};
class Rva006D0A30List {
public:
 Rva006D07E0Key find(const EAStringC *key);
 Rva006D07E0Key findSpecial(const EAStringC *key);
 Rva006D07E0Key rva006D0B40(const EAStringC&);
 Rva006D0A30Node *head;
};
Rva006D07E0Key Rva006D0A30List::find(const EAStringC *key) {
 Rva006D0A30Node *node=head;
 while(node) {
  if(node->entry->name8.rva006D36C0(key)==0)
   return Rva006D07E0Key(node->entry);
  node=node->next;
 }
 return Rva006D07E0Key();
}

// Native6D0A90..6D0B35. Filters the counted lookup result by
// target owner tagC values4/5; value copying and local destruction
// preserve ownership even for a rejected non-null result.
Rva006D07E0Key Rva006D0A30List::findSpecial(const EAStringC *key) {
 Rva006D07E0Key found=find(key);
 if(found.m_object && (found.m_object->typeC==4 || found.m_object->typeC==5))
  return found;
 return Rva006D07E0Key();
}

Rva006D07E0Key Rva006D0A30List::rva006D0B40(const EAStringC&name){
 Rva006D07E0Key found=find(&name);
 Rva006D0280*p=found.m_object;
 if(p)return Rva006D07E0Key(p);
 Rva006D07E0Key key(new Rva006D0280(&name));
 Rva006D0A30Node*node=new Rva006D0A30Node(key.m_object);
 node->next=head;
 head=node;
 return key;
}
class Rva00893030Manager;extern Rva00893030Manager*g_rva00893030Manager;
Rva006D07E0Key Rva006CE110(const char*name){
 return ((Rva006D0A30List*)g_rva00893030Manager)->rva006D0B40(EAStringC(name));
}


// New target family6D0B40/6CE110: pooled28B owner count0/name8/typeC1,
// argument10 remains uninitialized, object14/buffer18 begin null; raw8B
// list nodes track it. Target shared lookup and allocator providers establish
// these fields independently of donor names. Returning updated counts through
// inline helpers gives native register cleanup; all11 existing home rows
// stay exact. Borrowed string pointer ABI is expressed as a const reference.

// Complete native 6D1450..6D151F RET4: register a counted owner unless its
// pointer is already in the vector at +4. The 6D1520 caller supplies the Apt
// linker global, establishing the owner; the original method name is unknown.
// The argument is released on both paths. Native leaves no stable pointer
// result in EAX, so the old pointer-return pin is replaced by this void view.
// The iterator's existing range check preserves the top-tested search and
// separate found-path release. The count reference above and reloaded owner
// in the key destructor preserve both retail decrement sequences and all
// earlier bodies in this unit; the complete exception graph is also exact.
class AptLinker {
public:
 unsigned char m_beforeEntries[4];
 Rva006D1130 entries;
 void rva006D1450(Rva006D07E0Key key);
};
void AptLinker::rva006D1450(Rva006D07E0Key key) {
 Rva006D1130Iterator p=entries.begin(),last=entries.end();
 for(;p!=last;p++) if(p.position->m_bfmeP==(unsigned*)key.m_object) return;
 entries.append((Rva006D1130Item*)&key);
}
