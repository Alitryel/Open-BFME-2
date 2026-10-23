// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii
// ?rva004E37CF@Rva004E37CF@@QAEXABVAsciiString@@PAVRva004E37CFValue@@@Z,
// retail 0x004E37CF (71 bytes, RET 8): replace-or-insert into the
// AsciiString-keyed map held at +0 (header at +0). An existing entry's
// polymorphic value at node +0x14 is deleted (global-scope delete: vtable[0]
// with flags 0, then ::operator delete) and replaced; otherwise the rowed
// map<AsciiString, TreeHintPayload004E2257>::operator[] 0x004E368A slot
// receives the value. The search is the shared AsciiString-key _M_find
// 0x001F8437 under its rowed map<AsciiString, int> spelling (same node
// layout). Owner and value identities are not established.
#include "ascii_string.h"

namespace _STL {
template<class T> class allocator;
template<class T> struct less;
template<class T> struct _Select1st;
template<class T1,class T2> struct pair;
struct _Rb_tree_node_base {
 char color;
 _Rb_tree_node_base* parent;
 _Rb_tree_node_base* left;
 _Rb_tree_node_base* right;
};
template<class T> struct _Rb_tree_node;
template<class K,class V,class KeyOfValue,class C,class A> class _Rb_tree {
 template<class SearchKey> _Rb_tree_node<V>* _M_find(const SearchKey&) const;
public:
 template<class SearchKey> __forceinline _Rb_tree_node<V>* findNode(const SearchKey& k) const {return _M_find(k);}
};
template<class K,class V,class C,class A> class map {
public:
 V& operator[](const K&);
};
}

struct TreeHintPayload004E2257;
typedef _STL::pair<const AsciiString, int> Rva004E37CFFindValue;
typedef _STL::_Rb_tree<AsciiString, Rva004E37CFFindValue, _STL::_Select1st<Rva004E37CFFindValue>,
	_STL::less<AsciiString>, _STL::allocator<Rva004E37CFFindValue> > Rva004E37CFFindTree;
typedef _STL::map<AsciiString, TreeHintPayload004E2257, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, TreeHintPayload004E2257> > > Rva004E37CFMap;

class Rva004E37CFValue
{
public:
	virtual ~Rva004E37CFValue();
};

struct Rva004E37CFNode
{
	_STL::_Rb_tree_node_base m_base;
	AsciiString m_key;		// +0x10
	Rva004E37CFValue *m_value;	// +0x14
};

class Rva004E37CF
{
public:
	void rva004E37CF(const AsciiString &key, Rva004E37CFValue *value);
private:
	_STL::_Rb_tree_node_base *m_header;
};

void Rva004E37CF::rva004E37CF(const AsciiString &key, Rva004E37CFValue *value)
{
	Rva004E37CFNode *node = (Rva004E37CFNode *)((const Rva004E37CFFindTree *)this)->findNode(key);
	if (node != (Rva004E37CFNode *)m_header)
	{
		::delete node->m_value;
		node->m_value = value;
	}
	else
	{
		*(Rva004E37CFValue **)&(*(Rva004E37CFMap *)this)[key] = value;
	}
}
