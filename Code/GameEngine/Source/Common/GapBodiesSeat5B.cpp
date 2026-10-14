// cl: /DNDEBUG /MD
// Small bodies from .text gaps in the 0x00654850.. O2 region (seat-5 batch
// B). Retail bytes establish every shape; names are address-derived unless a
// row names them. Callees use the ledger's existing spellings.

// --- 0x00667FB0 (15B): virtual slot 0 of the secondary base at +4 (retail
// loads its vptr before adjusting this, the O2 order), then the
// rowed field getter 0x00656F30 on what it returns.
class Rva00656F30DwordField
{
public:
	int get() const;										// 0x00656F30
};

class Rva00667FB0Member
{
public:
	virtual Rva00656F30DwordField *v00();
};

class Rva00667FB0Primary
{
public:
	virtual void p00();
};

class Rva00667FB0 : public Rva00667FB0Primary, public Rva00667FB0Member
{
public:
	int rva00667FB0();
};

int Rva00667FB0::rva00667FB0()
{
	return v00()->get();
}
