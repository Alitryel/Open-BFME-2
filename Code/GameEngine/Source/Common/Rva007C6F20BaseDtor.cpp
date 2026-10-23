// cl: /O1 /MD /EHsc
// ??1Rva007C6F20Base@@UAE@XZ, folded at 0x004E84A4 (7 bytes).
//
// StrategicHUD::ArmyMemberIconMovieClip's first base (Rva005FC8FDApt*.cpp):
// the shared one-slot vtable 0x007C6F20 and a word at +0x04. Its destructor
// only restores that vptr, so retail folds it onto 0x004E84A4 with the other
// destructors of the 0x007C6F20 base views; the owner constructor's unwind
// state for the base subobject (FuncInfo of 0x005FCEA9) calls 0x004E84A4.
// The owner TU declares this base novtable because the owner constructor
// stores no base vptr; the destructor does restore it, so it is defined here
// without novtable.
class Rva007C6F20Base
{
public:
	virtual ~Rva007C6F20Base();

protected:
	int m_04;
};

Rva007C6F20Base::~Rva007C6F20Base()
{
}
