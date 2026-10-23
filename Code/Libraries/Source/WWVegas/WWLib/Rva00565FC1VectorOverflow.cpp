// cl: /MD /DNDEBUG
// stlport
// Reference: STLport 4.5.3 vector::_M_insert_overflow (nontrivial element).
// Target: 0x00565FC1, 183B; 16-byte stride and null-guarded copy constructor
// at 0x0052BB9A. STLport semantics supplied by donor; boundaries, ABI,
// field offsets and helper relationships independently read from retail.
// Apply argument-slot tag finding proven by 0x004C77C4 to this sibling.
struct Rva00565FC1Pair { Rva00565FC1Pair(const Rva00565FC1Pair &); char data[16]; };
struct Rva00565FC1Tag {};
// Retail borrows byte 3 of the four-byte final argument slot for the empty tag.
struct Rva00565FC1EndSlot { bool value; char padding[2]; Rva00565FC1Tag tag; };
Rva00565FC1Pair *Rva0052C2CACopy(Rva00565FC1Pair *,Rva00565FC1Pair *,Rva00565FC1Pair *,const Rva00565FC1Tag &);
Rva00565FC1Pair *Rva00564C7DFill(Rva00565FC1Pair *,unsigned int,const Rva00565FC1Pair &,const Rva00565FC1Tag &);
struct Rva00565FC1Storage {
    Rva00565FC1Pair *end;
    Rva00565FC1Pair *allocate(unsigned int,const void *);
};
class Rva00565FC1 {
public:
    void overflow(Rva00565FC1Pair *,const Rva00565FC1Pair &,const Rva00565FC1Tag &,unsigned int,Rva00565FC1EndSlot);
    void clear();
private:
    Rva00565FC1Pair *start,*finish;
    Rva00565FC1Storage storage;
};
inline const unsigned int &Rva00565FC1Max(const unsigned int &a,const unsigned int &b) { return a<b?b:a; }
void Rva00565FC1::overflow(Rva00565FC1Pair *position,const Rva00565FC1Pair &value,const Rva00565FC1Tag &,unsigned int count,Rva00565FC1EndSlot at_end) {
    const unsigned int old_size=finish-start;
    const unsigned int length=old_size+Rva00565FC1Max(old_size,count);
    Rva00565FC1Pair *new_start=storage.allocate(length,0);
    Rva00565FC1Pair *new_finish=Rva0052C2CACopy(start,position,new_start,at_end.tag);
    if (count==1) {
        if (new_finish) new_finish->Rva00565FC1Pair::Rva00565FC1Pair(value);
        ++new_finish;
    } else new_finish=Rva00564C7DFill(new_finish,count,value,at_end.tag);
    if (!at_end.value) new_finish=Rva0052C2CACopy(position,finish,new_finish,at_end.tag);
    clear();
    start=new_start;
    finish=new_finish;
    storage.end=new_start+length;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00565A60 reads ?_M_clear@?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@IAEXXZ
#pragma comment(linker, "/alternatename:?clear@Rva00565FC1@@QAEXXZ=?_M_clear@?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@IAEXXZ")
//   0x00564C7D reads ?Rva00564C7DFill@@YAPAVRva003A6360Record@@PAV1@IABV1@@Z
#pragma comment(linker, "/alternatename:?Rva00564C7DFill@@YAPAURva00565FC1Pair@@PAU1@IABU1@ABURva00565FC1Tag@@@Z=?Rva00564C7DFill@@YAPAVRva003A6360Record@@PAV1@IABV1@@Z")
//   0x0052BB9A reads ??0Rva003A6360Record@@QAE@ABV0@@Z
#pragma comment(linker, "/alternatename:??0Rva00565FC1Pair@@QAE@ABU0@@Z=??0Rva003A6360Record@@QAE@ABV0@@Z")
//   0x0052C2CA reads ??$__uninitialized_copy@PAVRva003A6360Record@@PAV1@@_STL@@YAPAVRva003A6360Record@@PAV1@00ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:?Rva0052C2CACopy@@YAPAURva00565FC1Pair@@PAU1@00ABURva00565FC1Tag@@@Z=??$__uninitialized_copy@PAVRva003A6360Record@@PAV1@@_STL@@YAPAVRva003A6360Record@@PAV1@00ABU__false_type@0@@Z")
//   0x002226BE reads ?allocate@?$allocator@UBfmeE16@@@_STL@@QBEPAUBfmeE16@@IPBX@Z
#pragma comment(linker, "/alternatename:?allocate@Rva00565FC1Storage@@QAEPAURva00565FC1Pair@@IPBX@Z=?allocate@?$allocator@UBfmeE16@@@_STL@@QBEPAUBfmeE16@@IPBX@Z")
