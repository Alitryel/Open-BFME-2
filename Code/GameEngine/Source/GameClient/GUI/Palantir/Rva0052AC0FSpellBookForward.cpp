// cl: /O1 /G7 /arch:SSE /EHsc /MD
// ?rva0052AC0F@Rva0052AF1C@@QAEXXZ @0x0052AC0F 7B: MOV ECX,[ECX]; JMP 0x0052A85D.
// Forwards to the rowed in-game spell book interface update on the implementation
// object this Palantir sub-object holds at +0 (tail call). The sibling 0x00526F0B
// does the same for the hero-select interface. Caller: the AptPalantir update
// (0x002D65F6). The holder class is the one whose constructor is 0x0052AF1C.
class AptInGameSpellBookInterface
{
public:
	class Impl
	{
	public:
		void Update();
	};
};

class Rva0052AF1C
{
public:
	void rva0052AC0F();
private:
	AptInGameSpellBookInterface::Impl *m_impl;
};

void Rva0052AF1C::rva0052AC0F()
{
	m_impl->Update();
}
