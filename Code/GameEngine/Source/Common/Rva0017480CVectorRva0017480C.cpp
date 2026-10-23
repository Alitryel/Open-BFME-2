// cl: /EHsc /MD /DNDEBUG
//
// ?resize@Rva0017480CVector@@QAEXIURva0017480CRecord@@@Z, retail 0x0017480c, 100 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native 100B by-value resize: RET36; opaque record width32.
// Callees: erase173FB6; fill17422D; dtor17330A.
struct Rva0017480CRecord {~Rva0017480CRecord();unsigned char consumed[32];};
class Rva0017480CVector {public:
 unsigned size()const{return finish-start;} Rva0017480CRecord*begin(){return start;} Rva0017480CRecord*end(){return finish;}
 void resize(unsigned,Rva0017480CRecord);
private:
 Rva0017480CRecord*start;Rva0017480CRecord*finish;Rva0017480CRecord*limit;
 Rva0017480CRecord*erase(Rva0017480CRecord*,Rva0017480CRecord*);
 void fill(Rva0017480CRecord*,unsigned,const Rva0017480CRecord&);
};
void Rva0017480CVector::resize(unsigned count,Rva0017480CRecord value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0017330A reads ??1BfmeAssignRecord32@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva0017480CRecord@@QAE@XZ=??1BfmeAssignRecord32@@QAE@XZ")
//   0x0017422D reads ?_M_fill_insert@?$vector@URva0017422DElement@@V?$allocator@URva0017422DElement@@@_STL@@@_STL@@QAEXPAURva0017422DElement@@IABU3@@Z
#pragma comment(linker, "/alternatename:?fill@Rva0017480CVector@@AAEXPAURva0017480CRecord@@IABU2@@Z=?_M_fill_insert@?$vector@URva0017422DElement@@V?$allocator@URva0017422DElement@@@_STL@@@_STL@@QAEXPAURva0017422DElement@@IABU3@@Z")
//   0x00173FB6 reads ?erase@?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord32@@PAU3@0@Z
#pragma comment(linker, "/alternatename:?erase@Rva0017480CVector@@AAEPAURva0017480CRecord@@PAU2@0@Z=?erase@?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord32@@PAU3@0@Z")
