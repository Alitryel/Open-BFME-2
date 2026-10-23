// ?rva004E06A7@Rva004E06A7@@QBEXXZ @0x004E06A7 17B
// Conditional virtual tail-call: calls ?rva004E0632@Rva004E0632@@QBEHXZ with the
// same this; if it returns 0 return void else tail-jump to virtual slot 5
// (offset 0x14) of the returned object. Retail is call / test eax,eax /
// je ret / mov edx,[eax] / mov ecx,eax / jmp [edx+0x14] / ret (17B).
// Evidence: chain lane (calls 0x004E0632 landed in Rva004E0625Getters.cpp);
// caller at 0x004E06D7 does not use eax (void return); same-this pass-through
// proves __thiscall. No // cl: line (defaults; neighbours default).
class Rva004E0632
{
public:
	int rva004E0632() const;
};

class Rva004E06A7Target
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
};

class Rva004E06A7
{
public:
	void rva004E06A7() const;
};
void Rva004E06A7::rva004E06A7() const
{
	int raw = ((const Rva004E0632 *)this)->rva004E0632();
	if (raw != 0)
		((Rva004E06A7Target *)raw)->v5();
}
