// cl: /O1 /GX /DNDEBUG /MD
// Heap factories in this unit: 66B @0x005D4FBA and 64B @0x005EC832.
// Each allocates its product, stores it at +0, and returns the owner.
// Operator new and __EH_prolog resolve via their rows; the product ctors
// are declared-only at the addresses established by each retail REL32.

class Rva005D4FBAOwner;

class Rva005D4EA8
{
public:
	Rva005D4EA8(int x, int y);

private:
	char m_pad[0x10];
};

class Rva005D4FBAOwner
{
public:
	Rva005D4FBAOwner *rva005D4FBA(int x, int y);

private:
	Rva005D4EA8 *m_product;
};

Rva005D4FBAOwner *Rva005D4FBAOwner::rva005D4FBA(int x, int y)
{
	m_product = new Rva005D4EA8(x, y);
	return this;
}

class Rva005EC832Owner;

class Rva005EC64E
{
public:
	Rva005EC64E(Rva005EC832Owner *owner, int x);

private:
	char m_pad[0x2C];
};

class Rva005EC832Owner
{
public:
	Rva005EC832Owner *rva005EC832(int x);

private:
	Rva005EC64E *m_product;
};

Rva005EC832Owner *Rva005EC832Owner::rva005EC832(int x)
{
	m_product = new Rva005EC64E(this, x);
	return this;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005D4EA8 reads ?rva005D4EA8@Rva005D4EA8@@QAEPAXHH@Z
#pragma comment(linker, "/alternatename:??0Rva005D4EA8@@QAE@HH@Z=?rva005D4EA8@Rva005D4EA8@@QAEPAXHH@Z")
//   0x005EC64E reads ??0Impl@StrategicVeterancy@@QAE@PAV1@PAVData@1@@Z
#pragma comment(linker, "/alternatename:??0Rva005EC64E@@QAE@PAVRva005EC832Owner@@H@Z=??0Impl@StrategicVeterancy@@QAE@PAV1@PAVData@1@@Z")
