// cl: -GR- -EHsc-
// ?Run@Rva005BC474Box@@QAEXXZ @0x005BC474 33B: two-flag clearer. Runs the
// pinned 0-arg callee when +0x78 is clear, returns when +0x79 is clear,
// else runs the pinned 0-arg callee and clears +0x79. Targets from retail
// REL32; both callees unrowed.
class Rva005BB5CEOwner { public: bool rva005BB5CE(); };
class AptOnlineQuickMatch { public: void rva005BBF15(); };

struct Rva005BC474Box
{
	char pad[0x78];
	unsigned char m_78;
	unsigned char m_79;

	void Run();
};

void Rva005BC474Box::Run()
{
	if (m_78 == 0)
		((Rva005BB5CEOwner *)this)->rva005BB5CE();
	if (m_79 == 0)
		return;
	((AptOnlineQuickMatch *)this)->rva005BBF15();
	m_79 = 0;
}
