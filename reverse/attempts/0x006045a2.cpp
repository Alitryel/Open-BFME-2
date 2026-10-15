// ?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z
// partial score=0.9922685185185185 date=2026-10-15
// ?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z
// partial score=0.9922685185185185 date=2026-10-15
// cl: /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// W7-D1 r11: native6045A2..6046B0 RET16; whole270B and frame44 exact.
// insertFolder(const source_pair&) makes the const-key copy INSIDE an inline
// void helper. It consumes make_pair's actual EAX return, removing r10's LEA.
// Two remaining instruction bytes are first source-pair home -40 versus
// retail -50; the matching destructor funclet is off by16 in one byte too.
// The old273B/frame44/EH-exact alternative is preserved in
// reverse/attempt_evidence/big_archive_r11_eh_exact.cpp.
// All8 original call candidates plus17 transitive bodies/relocations/EH
// were independently checked whole against retail. See r11_call_graph.json.
// Alternate270B/EH-exact direct-return experiment: r11_prvalue.patch,
// three later member-pair homes differ; factory whole27B separately checked.
// No candidate is an admitted production pin; owner-unit/fold admission is
// still required before this parent can land. Never substitute the existing
// 4B Rva00603A00Mapped placeholder for the native12B member descriptor.
#include <map>
// ?init@Win32BIGFileSystem@@UAEX_N@Z @0x00603944 188B: vslot 1 of vtable 0x0087A94C (class of ??0Win32BIGFileSystem@@QAE@XZ). Loads lang big files. Evidence: vtable slot 1; strings "%s*.big" "lang\" "lang\%sAudio.big" "EnglishAudio.big" "*.big" "apt\"; global TheArchiveFileSystem; buffers g_00DD509C g_Rva0107301CEmptyString.


class File
{
public:
 virtual ~File();
 virtual void slot01();
 virtual void slot02();
 virtual int read(void *buffer, int size);
};

// Native 6046B0 builds this twelve-byte descriptor; helper6045A2 copies
// its three words into the archive filename map. Names describe this view.
struct BigArchiveMemberInfo
{
 File *file;
 unsigned int offset;
 unsigned int size;
};

struct Rva006038D4Less
{
 bool operator()(const char *a, const char *b) const;
};
typedef _STL::map<const char *, BigArchiveMemberInfo, Rva006038D4Less> BigMemberMap;
typedef _STL::map<const char *, BigMemberMap, Rva006038D4Less> BigFolderMap;
class Rva006054AF
{
public:
 void *rva006054AF(const char *text);
};
extern unsigned int g_Va00E06E60;

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unknown);
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern char g_00DD509C[];

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void init(bool flag);
	virtual void V2();
	virtual void V3();
	virtual void V4();
	virtual bool addArchiveFile(const char *filename, bool overwrite);
	virtual void V6();
	virtual void V7();
	virtual void S8(const char *a, const char *b, int c);
 bool rva006045A2(const char *folder, const char *name, BigArchiveMemberInfo *info, bool overwrite);
private:
 BigFolderMap m_folders;
};



// Native DD5150/DD5154 point to full BIGF/BIG4 strings at BD22F0/BD22E8.
// Mutable pointer storage keeps the same two global loads as the retail body.
extern const char *BigArchiveSignatures[2];

struct BigArchiveHeader
{
 char identifier[4];
 unsigned int archiveSize;
 unsigned int entryCount;
 unsigned int directorySize;
};

class Rva00603925
{
public:
 unsigned int offset;
 unsigned int size;
 char name[1]; // variable trailing NUL-terminated name, not a fixed allocation
 void *rva00603925();
};
unsigned int __cdecl Rva009CC290Swap(unsigned int);
char *Rva00605365(char *);

extern "C" unsigned char *__cdecl _mbscpy(unsigned char *, const unsigned char *);
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *) throw();

// WorldBuilder16507D0 names the method and source path. Native C7A94C
// vtable slot5 selects6046B0; complete RET8 body314 bytes. ZH's BIG parser
// is a semantic lead only: this target uses File read slot3, a single
// directory read, two accepted identifiers and a twelve-byte descriptor.



// Native 6045A2,270B,RET16; caller6046B0 and shared header at this+4.
// Nested map semantics and record words are target-derived; names of mapped
// records and fields are descriptive views, not original-name claims.
static __forceinline void insertFolder(BigFolderMap&m,const _STL::pair<const char*,BigMemberMap>&v,BigFolderMap::iterator&out) { BigFolderMap::value_type copy(v);out=m.insert(copy).first; }
struct SecondInfoPairPad { unsigned char pad[15]; BigMemberMap::value_type value; __forceinline SecondInfoPairPad(const char*k,const BigArchiveMemberInfo&i):value(k,i){} };
bool Win32BIGFileSystem::rva006045A2(const char *folder, const char *name,
                                  BigArchiveMemberInfo *info, bool overwrite)
{
 if (folder == name)
  folder = "";
 BigFolderMap::iterator parent = m_folders.find(folder);
 Rva006054AF *pool = (Rva006054AF *)&g_Va00E06E60;
 if (parent == m_folders.end()) {
  folder = (const char *)pool->rva006054AF(folder);
  insertFolder(m_folders,_STL::make_pair(folder,BigMemberMap()),parent);
 }
 BigMemberMap &members = parent->second;
 BigMemberMap::iterator entry = members.find(name);
 if (entry == members.end()) {
  name = (const char *)pool->rva006054AF(name);
  members.insert(SecondInfoPairPad(name,*info).value);
 } else {
  if (!overwrite)
   return false;
  entry->second = *info;
 }
 return true;
}


// stlport
// ?rva00604374@Rva00604374@@QAEPAXABVRva0060426C@@@Z @0x00604374 34B node alloc 0x20 via rowed 0x000307F0 then rowed Construct 0x00604289 at +0x10. Evidence: callers 0x00604400 0x00604419 in insert 0x006043CE same shape as Rva00397CC9Alloc.
#include <memory>
#include <set>

class Rva0060426C;
void Rva00604289Construct(Rva0060426C *dest, const Rva0060426C &src);

class Rva00604374
{
public:
	void *rva00604374(const Rva0060426C &src);
};

void *Rva00604374::rva00604374(const Rva0060426C &src)
{
	char *p = _STL::allocator<char>::allocate(0x20, 0);
	Rva00604289Construct((Rva0060426C *)(p + 0x10), src);
	return p;
}


// Native 6043CE/6044A0 use strcmp6038D4 on the first pointer-sized word.
// Node creator604374 allocates32B and copies the16B Rva0060426C value via
// matched Construct604289. Payload's remaining12B are preserved by that
// existing copy provider; no application type or no-case ordering is asserted.
// Algorithms follow matched6012ED/6013B7 and the new600854/600991 siblings;
// every layout access, branch, and call is checked against these native bodies.
class Rva0060426C;
struct Rva006044A0Node {
	unsigned color;
	Rva006044A0Node *parent;
	Rva006044A0Node *left;
	Rva006044A0Node *right;
};
struct Rva006044A0Pair {
	Rva006044A0Node *first;
	bool second;
	Rva006044A0Pair(Rva006044A0Node *f, bool s) : first(f), second(s) {}
};
struct Rva006044A0 {
	Rva006044A0Node *m_header;
	int m_count;
	Rva006038D4Less m_less;
	// Native helper returns the output pointer in EAX.
	void **rva006043CE(void **result, void *x, void *y, const void *value, void *known);
	Rva006044A0Pair rva006044A0(const Rva0060426C &v);
	Rva006044A0Pair rva0060458E(const Rva0060426C &v);
};
Rva006044A0Pair Rva006044A0::rva006044A0(const Rva0060426C &v)
{
	Rva006044A0Node *y = m_header;
	Rva006044A0Node *x = m_header->parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = m_less(*(const char **)&v, *(const char **)((char *)x + 0x10));
		x = comp ? x->left : x->right;
	}
	Rva006044A0Node *j = y;
	if (comp) {
		if (j == m_header->left)
		{
			Rva006044A0Node *tmp;
			void **pres = rva006043CE((void **)&tmp, y, y, &v, 0);
			tmp = (Rva006044A0Node *)*pres;
			return Rva006044A0Pair(tmp, true);
		}
		j = (Rva006044A0Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (m_less(*(const char **)((char *)j + 0x10), *(const char **)&v))
	{
		Rva006044A0Node *tmp;
		void **pres = rva006043CE((void **)&tmp, x, y, &v, 0);
		tmp = (Rva006044A0Node *)*pres;
		return Rva006044A0Pair(tmp, true);
	}
	return Rva006044A0Pair(j, false);
}

void **Rva006044A0::rva006043CE(void **result, void *x, void *y, const void *value, void *known)
{
	Rva006044A0Node *yn = (Rva006044A0Node *)y;
	Rva006044A0Node *node;
	if (yn != m_header && (known != 0 || (x == 0 && !m_less(*(const char **)value, *(const char **)((char *)yn + 0x10))))) {
		node = (Rva006044A0Node *)((Rva00604374 *)this)->rva00604374(*(const Rva0060426C *)value);
		yn->right = node;
		Rva006044A0Node *header = m_header;
		if (yn == header->right)
			header->right = node;
	} else {
		node = (Rva006044A0Node *)((Rva00604374 *)this)->rva00604374(*(const Rva0060426C *)value);
		yn->left = node;
		Rva006044A0Node *header = m_header;
		if (yn == header) {
			header->parent = node;
			m_header->right = node;
		} else if (yn == header->left) {
			header->left = node;
		}
	}
	node->left = 0;
	node->right = 0;
	node->parent = yn;
	_STL::_Rb_global<bool>::_Rebalance(
		reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
		reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
	++m_count;
	*result = node;
	return result;
}

// 603B0A/603E50: same strcmp-key insertion control flow, with the existing
// 29E11A allocator copying a 16B value through Construct41360E. That provider
// is ledgered as ModuleFactory; this is its measured four-word ABI view only.
// The new tree's application owner and remaining payload meanings are unknown.
struct Rva00603E50Value { const char *key; unsigned words[3]; };
enum NameKeyType { NameKeyZero = 0 };
class ModuleFactory {
public:
 class ModuleTemplate {
 public: void *m_createProc; void *m_createDataProc; int m_whichInterfaces;
 };
};
typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleWordPair;
typedef _STL::_Rb_tree<NameKeyType, ModuleWordPair, _STL::_Select1st<ModuleWordPair>, _STL::less<NameKeyType>, _STL::allocator<ModuleWordPair> > ModuleWordTree;
struct ModuleWordNodeView : ModuleWordTree {
 static __forceinline _STL::_Rb_tree_node<ModuleWordPair> *create(void *receiver, const ModuleWordPair &value) {
  return ((ModuleWordNodeView *)receiver)->_M_create_node(value);
 }
};
struct Rva00603E50Node {
	unsigned color;
	Rva00603E50Node *parent;
	Rva00603E50Node *left;
	Rva00603E50Node *right;
};
struct Rva00603E50Pair {
	Rva00603E50Node *first;
	bool second;
	Rva00603E50Pair(Rva00603E50Node *f, bool s) : first(f), second(s) {}
};
struct Rva00603E50 {
	Rva00603E50Node *m_header;
	int m_count;
	Rva006038D4Less m_less;
	// Native helper returns the output pointer in EAX.
	void **rva00603B0A(void **result, void *x, void *y, const void *value, void *known);
	Rva00603E50Pair rva00603E50(const Rva00603E50Value &v);
	Rva00603E50Pair rva00603FAC(const Rva00603E50Value &v);
};
Rva00603E50Pair Rva00603E50::rva00603E50(const Rva00603E50Value &v)
{
	Rva00603E50Node *y = m_header;
	Rva00603E50Node *x = m_header->parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = m_less(*(const char **)&v, *(const char **)((char *)x + 0x10));
		x = comp ? x->left : x->right;
	}
	Rva00603E50Node *j = y;
	if (comp) {
		if (j == m_header->left)
		{
			Rva00603E50Node *tmp;
			void **pres = rva00603B0A((void **)&tmp, y, y, &v, 0);
			tmp = (Rva00603E50Node *)*pres;
			return Rva00603E50Pair(tmp, true);
		}
		j = (Rva00603E50Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (m_less(*(const char **)((char *)j + 0x10), *(const char **)&v))
	{
		Rva00603E50Node *tmp;
		void **pres = rva00603B0A((void **)&tmp, x, y, &v, 0);
		tmp = (Rva00603E50Node *)*pres;
		return Rva00603E50Pair(tmp, true);
	}
	return Rva00603E50Pair(j, false);
}

void **Rva00603E50::rva00603B0A(void **result, void *x, void *y, const void *value, void *known)
{
	Rva00603E50Node *yn = (Rva00603E50Node *)y;
	Rva00603E50Node *node;
	if (yn != m_header && (known != 0 || (x == 0 && !m_less(*(const char **)value, *(const char **)((char *)yn + 0x10))))) {
		node = (Rva00603E50Node *)ModuleWordNodeView::create(this, *(const ModuleWordPair *)value);
		yn->right = node;
		Rva00603E50Node *header = m_header;
		if (yn == header->right)
			header->right = node;
	} else {
		node = (Rva00603E50Node *)ModuleWordNodeView::create(this, *(const ModuleWordPair *)value);
		yn->left = node;
		Rva00603E50Node *header = m_header;
		if (yn == header) {
			header->parent = node;
			m_header->right = node;
		} else if (yn == header->left) {
			header->left = node;
		}
	}
	node->left = 0;
	node->right = 0;
	node->parent = yn;
	_STL::_Rb_global<bool>::_Rebalance(
		reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
		reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
	++m_count;
	*result = node;
	return result;
}

// Gap bodies 0x00603FAC and 0x0060458E (20B each): the insert wrappers that
// return the rowed 0x00603E50 / 0x006044A0 results by value.
Rva00603E50Pair Rva00603E50::rva00603FAC(const Rva00603E50Value &v)
{
	return rva00603E50(v);
}

Rva006044A0Pair Rva006044A0::rva0060458E(const Rva0060426C &v)
{
	return rva006044A0(v);
}
