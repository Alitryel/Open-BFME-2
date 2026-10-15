// ?rva002AB894@Player@@QBE_NABURva002AB894List@@@Z
// partial score=1.0 date=2026-10-15
// ?rva002AB894@Player@@QBE_NABURva002AB894List@@@Z
// partial score=0.85 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Bank for 0x002AB894 (60B): all-of over a pointer list via Player::rva002AB87D.
// Everything but register assignment matches: retail keeps the counter in edi
// (xor edi,edi) and copies begin into ebx after the empty check; cl puts the
// counter in ebx (push 0/pop ebx) and the pointer in edi.
class UpgradeTemplate;
struct Rva002AB894List { const UpgradeTemplate **m_begin; const UpgradeTemplate **m_end; };
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *tmpl) const;
	bool rva002AB894(const Rva002AB894List &list) const;
};
bool Player::rva002AB894(const Rva002AB894List &list) const
{
	unsigned int i = 0;
	unsigned int count = list.m_end - list.m_begin;
	if (0 < count) {
	const UpgradeTemplate **it = list.m_begin;
	for (; i < count; ++i, ++it) {
		if (!rva002AB87D(*it))
			return false;
	}
	}
	return true;
}
