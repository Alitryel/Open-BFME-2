// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
//
// ??ARva00304DC7Map@@QAEAAVRva00304DC7Record@@ABVAsciiString@@@Z, retail 0x00304dc7, 157 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString&,const AsciiString&);
class Rva00304DC7Record {public:Rva00304DC7Record();~Rva00304DC7Record();private:char consumed[256];};
struct Rva00304DC7Entry {AsciiString key;Rva00304DC7Record value;Rva00304DC7Entry(const AsciiString&,const Rva00304DC7Record&);~Rva00304DC7Entry();};
typedef _STL::_Rb_tree_iterator<Rva00304DC7Entry,_STL::_Nonconst_traits<Rva00304DC7Entry> > Rva00304DC7Iterator;
class Rva00304DC7Map {public:Rva00304DC7Record&operator[](const AsciiString&);
private:_STL::_Rb_tree_node<Rva00304DC7Entry>*header;
_STL::_Rb_tree_node<Rva00304DC7Entry>*lower_bound(const AsciiString&);
Rva00304DC7Iterator insert(Rva00304DC7Iterator,const Rva00304DC7Entry&);};
Rva00304DC7Record& Rva00304DC7Map::operator[](const AsciiString&key) {
 Rva00304DC7Iterator i(lower_bound(key));
 if(i._M_node==header || key<i->key)
  i=insert(i,Rva00304DC7Entry(key,Rva00304DC7Record()));
 return i->value;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0022DBC6 reads ??1MapMetaData@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00304DC7Record@@QAE@XZ=??1MapMetaData@@QAE@XZ")
//   0x0022DDF4 reads ??1Rva0022DDF4@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00304DC7Entry@@QAE@XZ=??1Rva0022DDF4@@QAE@XZ")
//   0x00304DAA reads ?insert@?$map@VAsciiString@@UTreeHintOpaque00304573@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@4@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@2@@2@U32@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@2@@Z
#pragma comment(linker, "/alternatename:?insert@Rva00304DC7Map@@AAE?AU?$_Rb_tree_iterator@URva00304DC7Entry@@U?$_Nonconst_traits@URva00304DC7Entry@@@_STL@@@_STL@@U23@ABURva00304DC7Entry@@@Z=?insert@?$map@VAsciiString@@UTreeHintOpaque00304573@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@4@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@2@@2@U32@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@2@@Z")
//   0x00303D6B reads ??0?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@QAE@ABVAsciiString@@ABVMapMetaData@@@Z
#pragma comment(linker, "/alternatename:??0Rva00304DC7Entry@@QAE@ABVAsciiString@@ABVRva00304DC7Record@@@Z=??0?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@QAE@ABVAsciiString@@ABVMapMetaData@@@Z")
//   0x003031D3 reads ??0MapMetaData@@QAE@XZ
#pragma comment(linker, "/alternatename:??0Rva00304DC7Record@@QAE@XZ=??0MapMetaData@@QAE@XZ")
//   0x00221B8D reads ?_M_lower_bound@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@2@ABVAsciiString@@@Z
#pragma comment(linker, "/alternatename:?lower_bound@Rva00304DC7Map@@AAEPAU?$_Rb_tree_node@URva00304DC7Entry@@@_STL@@ABVAsciiString@@@Z=?_M_lower_bound@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@2@ABVAsciiString@@@Z")
