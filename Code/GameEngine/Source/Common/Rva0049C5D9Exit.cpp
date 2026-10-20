// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C5D9@Rva0049C5D9@@QAEXHH@Z @0x0049C5D9 27B.
// Clears the id at +0x40, then forwards both stack dwords unchanged to the rowed
// SpecialAbilityUpdate::onExit 0x004502CE.

class Rva0049C592
{
public:
	void rva0049C592();
};

class SpecialAbilityUpdate
{
protected:
	virtual void onExit(bool a, bool b);
	friend class Rva0049C5D9;
};

class Rva0049C5D9
{
public:
	void rva0049C5D9(int a, int b);
};

void Rva0049C5D9::rva0049C5D9(int a, int b)
{
	((Rva0049C592 *)this)->rva0049C592();
	((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::onExit((bool &)a, (bool &)b);
}
