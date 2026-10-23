// cl: /DNDEBUG /MD /EHsc
// ??0Rva004ABB03@@QAE@ABV0@@Z @0x004ABB03 24B: derived copy calls rowed base 0x004AB7EB copy then reinstalls vptr 0x0084ED70. Base declared only so the E8 stays outlined. Caller at 0x004ABCED. Prev stlport_map_int_ptr_o1 next UpdateModuleDeletingDtors but model and flags from V3Poly family.

typedef int Int;

extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];

class Rva004AB7EB
{
public:
	Rva004AB7EB(const Rva004AB7EB &other);
	// Retail tears the object down through 0x0049B47C, the folded
	// Snapshot destructor: it restores the Snapshot table 0x00BBB554 and
	// returns. This view has no Snapshot base, so the restore is spelled
	// by hand.
	virtual ~Rva004AB7EB()
	{
		*(const void *const **)this = __identifier("??_7Snapshot@@6B@");
	}

	Int m_field04;
};

class Rva004ABB03 : public Rva004AB7EB
{
public:
	Rva004ABB03(const Rva004ABB03 &other);
	virtual ~Rva004ABB03() {}
};

Rva004ABB03::Rva004ABB03(const Rva004ABB03 &other)
	: Rva004AB7EB(other)
{
}
