// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C5D9@Rva0049C5D9@@QAEX_N0@Z @0x0049C5D9 27B.
// Clears the id at +0x40, then forwards both stack args to the rowed
// SpecialAbilityUpdate::onExit (0x4502CE, SpecialAbilityUpdate.cpp).

class Rva0049C592
{
public:
	void rva0049C592();
};

class Rva0049C5D9;

class SpecialAbilityUpdate
{
	friend class Rva0049C5D9;
protected:
	virtual void onExit(bool a, bool b);
};

class Rva0049C5D9
{
public:
	void rva0049C5D9(bool a, bool b);
};

void Rva0049C5D9::rva0049C5D9(bool a, bool b)
{
	((Rva0049C592 *)this)->rva0049C592();
	((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::onExit(a, b);
}
