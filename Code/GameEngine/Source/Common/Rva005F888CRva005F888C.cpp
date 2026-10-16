// cl: /O1 /G7 /MD /DNDEBUG /EHsc
//
// ?rva005F888C@Rva005F888C@@QAEXABURva005F888CRef@@@Z, retail 0x005f888c, 66 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <vector>
struct Rva005F888CRef {void* pointer;};
struct Rva005F8447 {
 Rva005F8447(const Rva005F888CRef&);
 ~Rva005F8447();
 Rva005F888CRef first,second;
};
namespace _STL { template<> void vector<Rva005F8447>::push_back(const Rva005F8447&); }
class Rva005F888C {public:void rva005F888C(const Rva005F888CRef&);char p00[0x20];_STL::vector<Rva005F8447> entries;};
void Rva005F888C::rva005F888C(const Rva005F888CRef& value){entries.push_back(Rva005F8447(value));}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005F8855 reads ?push_back@?$vector@UPayload@DeliverPayloadNugget@@V?$allocator@UPayload@DeliverPayloadNugget@@@_STL@@@_STL@@QAEXABUPayload@DeliverPayloadNugget@@@Z
#pragma comment(linker, "/alternatename:?push_back@?$vector@URva005F8447@@V?$allocator@URva005F8447@@@_STL@@@_STL@@QAEXABURva005F8447@@@Z=?push_back@?$vector@UPayload@DeliverPayloadNugget@@V?$allocator@UPayload@DeliverPayloadNugget@@@_STL@@@_STL@@QAEXABUPayload@DeliverPayloadNugget@@@Z")
//   0x005F842F reads ?rva005F842F@Rva005F842F@@QAEPAU1@ABURva004F6986Member@@@Z
#pragma comment(linker, "/alternatename:??0Rva005F8447@@QAE@ABURva005F888CRef@@@Z=?rva005F842F@Rva005F842F@@QAEPAU1@ABURva004F6986Member@@@Z")
