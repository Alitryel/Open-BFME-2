// cl: /DNDEBUG /MD /EHs-c-
// Disable both C++ EH modes, as in the matched deleting-destructor units.
// Otherwise VC7.1 emits deleting destructors that call these 11-byte bodies;
// retail inlines the derived vptr store and calls the base destructor directly.
//
// Opaque single-inheritance destructors tail-calling BfmeDirtyBase::~
// BfmeDirtyBase at 0x00658650 (matched 7B leaf base dtor in
// DirtySock/BfmeDirtyBaseDtor.cpp; only declared here so each tail-call
// resolves to the ledger address instead of a same-TU definition). Each
// class below stores its own vtable (DIR32 auto-patches) and tail-jumps to
// the base destructor. Owner identities are unproven (opaque Rva names). One
// ledger row per destructor, landed one commit at a time.

struct BfmeDirtyBase
{
	BfmeDirtyBase();
	virtual ~BfmeDirtyBase();
};

class Rva006560E0 : public BfmeDirtyBase
{
public:
	virtual ~Rva006560E0();
};

Rva006560E0::~Rva006560E0()
{
}

class Rva0065D1D0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065D1D0();
};

Rva0065D1D0::~Rva0065D1D0()
{
}

class Rva0065E7D0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065E7D0();
};

Rva0065E7D0::~Rva0065E7D0()
{
}

class Rva0065ECF0 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065ECF0();
};

Rva0065ECF0::~Rva0065ECF0()
{
}

class Rva0065F970 : public BfmeDirtyBase
{
public:
	virtual ~Rva0065F970();
};

Rva0065F970::~Rva0065F970()
{
}

class Rva00660060 : public BfmeDirtyBase
{
public:
	virtual ~Rva00660060();
};

Rva00660060::~Rva00660060()
{
}

class Rva00660BE0 : public BfmeDirtyBase
{
public:
	virtual ~Rva00660BE0();
};

Rva00660BE0::~Rva00660BE0()
{
}

class Rva006672E0 : public BfmeDirtyBase
{
public:
	virtual ~Rva006672E0();
};

Rva006672E0::~Rva006672E0()
{
}

class Rva00668120 : public BfmeDirtyBase
{
public:
	virtual ~Rva00668120();
};

Rva00668120::~Rva00668120()
{
}
