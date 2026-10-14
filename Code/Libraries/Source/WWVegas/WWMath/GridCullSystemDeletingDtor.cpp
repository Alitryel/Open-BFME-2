// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.

// ??_GGridCullSystemClass, the scalar deleting destructor in vtable 0xCEFCB0
// slot 0 (retail 0x0071B170).  The class is declared locally only so its
// deleting destructor is emitted; the complete-destructor call resolves
// through that destructor's own row at 0x0071AD00.
class GridCullSystemClass
{
public:
	explicit GridCullSystemClass(int) {}
	virtual ~GridCullSystemClass();
private:
	int m_famgen;
};

GridCullSystemClass *famgenNew_GridCullSystemClass() { return new GridCullSystemClass(0); }

void famgenDelete(GridCullSystemClass *p)
{
	delete p;
}
