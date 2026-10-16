// ?addHotKey@HotKeyManager@@QAE?AURva00359302Result@@ABUTreeHintRef00217D4C@@ABVAsciiString@@_N@Z
// partial score=0.995 date=2026-10-16
// ?addHotKey@HotKeyManager@@QAE?AURva00359302Result@@ABUTreeHintRef00217D4C@@ABVAsciiString@@_N@Z
// partial score=0.995 date=2026-10-16
// W9-O3 2026-10-16: all calls resolve now (bank had 3 stale names): factory called by its row Rva00358C60Factory through a function-pointer view returning Rva00358B65; Rva00358B65 derives from pair<const AsciiString,TreeHintRef> so the value copy calls the rowed pair copy ctor 0x358B43 and both temps die through ~Rva00358B65 0x358B65. Size exact, residue = epilogue only: retail 'pop esi; mov fs:0,ecx; pop ebx', ours 'pop esi; pop ebx; mov fs:0,ecx'. Inert: Result ctor body/order, flag token order, NRVO local, single-return goto (worse).
// ?rva00359302@Rva00359302@@QAEXXZ
// partial score=0.987954 date=2026-10-15
// ?addHotKey@HotKeyManager@@QAE?AURva00359302Result@@ABUTreeHintRef00217D4C@@ABVAsciiString@@_N@Z
// partial score=0.99 date=2026-10-13
// ?addHotKey@HotKeyManager@@QAE?AURva00359302Result@@ABUTreeHintRef00217D4C@@ABVAsciiString@@_N@Z
// partial score=0.99 date=2026-10-13
// ?addHotKey@HotKeyManager@@QAE?AURva00359302Result@@ABUTreeHintRef00217D4C@@ABVAsciiString@@_N@Z
// partial score=0.98 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// HotKey.cpp -- HotKeyManager members at their WorldBuilder home
// (reverse/wb_name_leads.csv: WB's debug build names the file and method and
// asserts action.IsBound() and that the message type is not yet mapped);
// retail supplies the bytes.
//
// Layout (target evidence): the message-action map at +0x24, whose
// operator[] (0x003596AD, unrowed) yields the reference-counted action
// handle that the rowed handle assignment 0x002174A4 overwrites. The two
// hot-key maps at +0x0C and +0x18 (the second for the alternate binding)
// are STLport trees keyed by AsciiString, header node first; their nodes
// carry the (key, action) pair whose destructor is 0x00358B65.

#include "ascii_string.h"

typedef int Int;

// The reference-counted action handle (rowed under this address name).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &that);	// 0x002174A4

	void *m_node;
};

// View of the STLport map from message type to action handle.
class HotKeyMessageActionMap
{
public:
	TreeHintRef00217D4C &operator[](const Int &messageType);		// 0x003596AD

private:
	unsigned char m_data[0xc];
};

// The shared AsciiString-keyed tree find worker (0x001F8437): the key's
// node, or the header when it is absent.
class Rva001F8437
{
public:
	void *rva001F8437(const AsciiString &key);
};

// Just enough of STLport's tree to name its insert_unique (0x00359032).
namespace _STL
{
template <class _Tp> struct _Identity {};
template <class _Tp> struct less {};
template <class _Tp> class allocator {};
template <class _Tp> struct _Nonconst_traits {};
template <class _Value, class _Traits> struct _Rb_tree_iterator
{
	void *_M_node;
};
template <class _T1, class _T2> struct pair
{
	pair() {}
	pair(const pair &that);

	_T1 first;
	_T2 second;
};
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<_Value, _Nonconst_traits<_Value> > iterator;

	pair<iterator, bool> insert_unique(const _Value &value);
};
}

// The key/action pair (copy constructor 0x00358B43). The factory 0x00358C60
// returns one and the map's value is copied from it; both temporaries are
// destroyed by 0x00358B65, which ICF shares between the two pair types.
typedef _STL::pair<const AsciiString, TreeHintRef00217D4C> HotKeyPair;
HotKeyPair Rva00358C60Factory(const AsciiString &key, const TreeHintRef00217D4C &action);
struct Rva00358B65 : public HotKeyPair
{
	~Rva00358B65();
};
typedef Rva00358B65 (*Rva00358C60FactoryView)(const AsciiString &, const TreeHintRef00217D4C &);
struct Rva00359032Value : public Rva00358B65
{
	Rva00359032Value(const Rva00358B65 &that) : Rva00358B65(that) {}
};

class HotKeyMap : public _STL::_Rb_tree<Rva00359032Value, Rva00359032Value,
	_STL::_Identity<Rva00359032Value>, _STL::less<Rva00359032Value>,
	_STL::allocator<Rva00359032Value> >
{
public:
	void *find(const AsciiString &key) { return ((Rva001F8437 *)this)->rva001F8437(key); }
	void *end() const { return m_header; }

private:
	void *m_header;		// +0x00
	int m_count;		// +0x04
	int m_compare;		// +0x08
};

// What addHotKey hands back: the key's node in the chosen map, and which
// map that is.
struct Rva00359302Result
{
	Rva00359302Result(void *node, bool alt) : m_node(node), m_alt(alt) {}

	void *m_node;
	bool m_alt;
};

class HotKeyManager
{
public:
	Rva00359302Result addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool alt);
	void addMessageAction(const TreeHintRef00217D4C &action, Int messageType);

private:
	unsigned char m_pad00[0x0c];
	HotKeyMap m_map;		// +0x0C
	HotKeyMap m_altMap;		// +0x18
	HotKeyMessageActionMap m_messageActionMap;		// +0x24
};

// HotKeyManager::addHotKey, retail 0x00359302 (214 bytes): binds the action
// to the key in the plain or alternate map. A key already bound in lower
// case is retried in upper case (two buttons may share a hot key); when both
// are taken the map's end comes back unbound.
Rva00359302Result HotKeyManager::addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool alt)
{
	HotKeyMap *map = alt ? &m_altMap : &m_map;
	AsciiString name(key);
	name.toLower();
	void *node = map->find(name);
	if (node != map->end())
	{
		name.toUpper();
		void *upper = map->find(name);
		if (upper != map->end())
			return Rva00359302Result(map->end(), alt);
	}
	_STL::pair<HotKeyMap::iterator, bool> inserted = map->insert_unique(((Rva00358C60FactoryView)&Rva00358C60Factory)(name, action));
	return Rva00359302Result(inserted.first._M_node, alt);
}

// HotKeyManager::addMessageAction, retail 0x003597A8 (27 bytes): the action
// is bound to the message type.
void HotKeyManager::addMessageAction(const TreeHintRef00217D4C &action, Int messageType)
{
	m_messageActionMap[messageType] = action;
}
