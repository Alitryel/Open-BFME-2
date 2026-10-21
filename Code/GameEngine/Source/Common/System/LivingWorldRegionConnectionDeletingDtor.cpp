// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.

// ??_GLivingWorldRegionConnection@@UAEPAXI@Z, the scalar deleting
// destructor in vtable 0x00C36E48 slot 0 (retail 0x003F2A70, 28 bytes).
// The class is declared locally only so its deleting destructor is
// emitted; the complete-destructor call resolves through that
// destructor's own row at 0x003F2517, and the operator delete through
// the rowed 0x0002FD60.
class LivingWorldRegionConnection
{
public:
	explicit LivingWorldRegionConnection(int) {}
	virtual ~LivingWorldRegionConnection();
private:
	int m_famgen;
};

LivingWorldRegionConnection *famgenNew_LivingWorldRegionConnection() { return new LivingWorldRegionConnection(0); }

void famgenDelete(LivingWorldRegionConnection *livingWorldRegionConnection)
{
	delete livingWorldRegionConnection;
}
