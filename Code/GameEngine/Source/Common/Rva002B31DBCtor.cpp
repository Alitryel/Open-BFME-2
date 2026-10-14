// cl: /O1 /MD /EHsc
//
// ??0Rva002B31DB@@QAE@XZ retail 0x002B31D2 (9B): the out-of-line default
// constructor of the single-slot battle visitor whose invoke is rowed at
// 0x002B31DB (Rva002B2AFDSelect.cpp, where the constructor is inlined into
// its one user). Retail keeps this uncalled copy right before invoke; it only
// installs the visitor's vtable (0x007FE090, ??_7Rva002B31DB@@6B@).

class Rva003F498ACallback
{
public:
	virtual bool invoke(int) = 0;
};

class Rva002B31DB : public Rva003F498ACallback
{
public:
	Rva002B31DB();
	virtual bool invoke(int);
};

Rva002B31DB::Rva002B31DB()
{
}
