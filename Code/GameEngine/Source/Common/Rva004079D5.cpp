// cl: /O1 /MD
//
// ?rva004079D5@Rva004079D5@@QAEDHPAH@Z @0x004079D5 31B.
// Out-param helper: run the +0x74 subobject member with the address of the
// (otherwise unused) first-arg slot as scratch — frameless, no sub —
// store the int result through the second arg, and return whether it
// differs from the subobject head.
// Evidence: retail push esi / lea esi,[ecx+0x74] / lea eax,[esp+8] /
// push eax / mov ecx,esi / call 0x388E63 / mov ecx,[esp+0xc] /
// mov [ecx],eax / cmp eax,[esi] / pop esi / setne al / ret 8.
class Rva004079D5Sub74
{
public:
	int rva00388E63(int *out);
	int m_0;
};

class Rva004079D5
{
public:
	__declspec(noinline) char rva004079D5(int key, int *out);
private:
	char m_pad00[0x74];
	Rva004079D5Sub74 m_74;
};

inline char Rva004079D5::rva004079D5(int key, int *out)
{
	int node = m_74.rva00388E63(&key);
	*out = node;
	return node != m_74.m_0;
}

// ?bfmeBlingLookupAnchor absent-from-retail
char bfmeBlingLookupAnchor(Rva004079D5 *hero, int key, int *out)
{
	return hero->rva004079D5(key, out);
}

// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
#pragma comment(linker, "/alternatename:?rva00388E63@Rva004079D5Sub74@@QAEHPAH@Z=??$_M_find@H@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@1@ABH@Z")
