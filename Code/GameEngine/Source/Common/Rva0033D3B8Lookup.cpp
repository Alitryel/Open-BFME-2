// cl: /DNDEBUG /MD
//
// ?rva0033D3B8@Rva0033D3B8@@QAEPBDABVAsciiString@@@Z @0x0033D3B8 48B.
//
// String-map lookup over the map at +0x394: empty keys return null without
// touching the tree, otherwise the STLport find worker (pinned alias at
// 0x001F8437, same 78B key-only body as the Skirmish/MapCache twins) runs
// on the key and a header hit returns null while a real node returns the
// mapped value chars at node +0x14 (the pair second). The isEmpty spelling
// is the local non-inline declaration so retail's direct 0x00001E2F call
// shape is preserved (the shared header inlines extra checks).

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct MapNode
{
	char m_pad00[0x14];
	const char *m_value; // +0x14 (pair second chars)
};

class Rva0033D3B8Map
{
public:
	MapNode *find(const AsciiString &key);
	MapNode *m_header; // +0x00
};

class Rva0033D3B8
{
public:
	const char *rva0033D3B8(const AsciiString &key);
private:
	char m_pad00[0x394];
	Rva0033D3B8Map m_map; // +0x394
};

const char *Rva0033D3B8::rva0033D3B8(const AsciiString &key)
{
	if (key.isEmpty())
		return 0;
	MapNode *node = m_map.find(key);
	if (node == m_map.m_header)
		return 0;
	return node->m_value;
}

// The retail call in this body reads 0x001F8437, an address the ledger already
// carries as ??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@H@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@H@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@H@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@H@_STL@@@1@ABVAsciiString@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?find@Rva0033D3B8Map@@QAEPAUMapNode@@ABVAsciiString@@@Z=??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@H@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@H@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@H@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@H@_STL@@@1@ABVAsciiString@@@Z")
