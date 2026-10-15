// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00218468@FontLibrary@@QAEXPBVAsciiString@@PAMPA_N@Z (the caller
// FontLibraryFindRecord.cpp's spelling), retail 0x00218468, 278 bytes.
// FontLibrary font-substitution adjustment: look the name up in the
// substitution tree at this+0x20, and when a non-empty substitution list is
// found, replace the name/size/style with the neighbouring record's values,
// interpolating the size when the request falls between two records.
//
// Semantic guide: BFME1 Rva00476B00FontLibrary::adjustFont (donor
// FontLibraryBFMEAdjustFont.cpp). Structure from the WorldBuilder debug twin
// 0x00B70F70 (target evidence): every use reads the list's begin()/end(),
// the edge case is `next == end || next == begin` with a ternary pick, and
// both name assignments call StringBase::set 0x000366F0. BFME2 deltas: tree
// at this+0x20; cvttss2si key (/arch:SSE).
//
// The search is STLport's real upper_bound. Its __upper_bound instantiation
// (pinned fold-proof onto the rowed Gen00473A40 body 0x0021764D) is defined
// in this unit before the caller, so cl knows it stores nothing: begin/end
// stay in registers across the call and the edge test is not threaded, as
// retail. Original method name unknown: address-derived name.
#include <map>
#include <algorithm>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL
{
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits> &a,
			      const _Rb_tree_iterator<T, RightTraits> &b)
{
	return a._M_node != b._M_node;
}
}

struct Gen00473A40Elem;

struct Rva004779C0Vector
{
	Gen00473A40Elem *begin() const { return (Gen00473A40Elem *)m_first; }
	Gen00473A40Elem *end() const { return (Gen00473A40Elem *)m_last; }
	unsigned int size() const { return (unsigned int)(m_last - m_first) >> 4; }

	char *m_first;
	char *m_last;
	char *m_end;
};

struct Rva00475680Node
{
	int m_color;
	Rva00475680Node *m_parent;
	Rva00475680Node *m_left;
	Rva00475680Node *m_right;
	AsciiString m_key;
	Rva004779C0Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *find(const AsciiString &key) const
	{
		return reinterpret_cast<Rva00475680Node *>(
			reinterpret_cast<const _STL::map<AsciiString, AsciiString> *>(this)
				->find(key)
				._M_node);
	}

	Rva00475680Node *m_header;
};

struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	AsciiString m_name;
};

// The comparator carries one byte retail zeroes with stosb before pushing the
// whole dword to the by-value __upper_bound parameter; an empty functor
// elides that store and the body comes out short.
struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const
	{
		return value < elem.m_inputSize;
	}

	unsigned char m_pad0x00;
};


class FontLibrary
{
public:
	void rva00218468(const AsciiString *name, float *size, bool *style);

	// Nothing before the tree is read here; the landed sibling
	// FontLibraryFontList.cpp spells the real prefix (font list at +0x0C,
	// count at +0x10, table map at +0x14), so this stays a pad.
	char m_pad0x00[0x20];
	Rva00475680Tree m_fontSubstitution;
};

void FontLibrary::rva00218468(const AsciiString *name, float *sizeOut, bool *style)
{
	Rva00475680Tree *tree = &m_fontSubstitution;
	float &size = *sizeOut;
	Rva00475680Node *node = tree->find(*name);
	if (node == tree->m_header)
		return;

	Rva004779C0Vector *list = node->m_value;
	if (list == 0)
		return;

	if (list->size() == 0)
		return;

	Gen00473A40Elem *next = _STL::upper_bound(list->begin(), list->end(), (int)size, Gen00473A40Less());
	int flags;

	if (next == list->end() || next == list->begin())
	{
		Gen00473A40Elem *elem = (next == list->end()) ? list->end() - 1 : list->begin();
		if (elem->m_name.getLength() != 0)
			((StringBase<char> *)name)
				->set(*(const StringBase<char> *)&elem->m_name);
		flags = elem->m_flags;
		size = (float)elem->m_outputSize;
	}
	else
	{
		Gen00473A40Elem *previous = next - 1;
		if (previous->m_name.getLength() != 0)
			((StringBase<char> *)name)
				->set(*(const StringBase<char> *)&previous->m_name);

		flags = previous->m_flags;
		size = (float)previous->m_outputSize +
			(size - (float)previous->m_inputSize) *
				((float)next->m_outputSize -
					(float)previous->m_outputSize) /
				((float)next->m_inputSize -
					(float)previous->m_inputSize);
	}

	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}

