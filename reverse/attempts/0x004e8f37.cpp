// ?rva004E8F37@Rva004E8F37@@QAE_NPAVPlayer@@@Z
// partial score=0.95 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /MD
// ?rva004E8F37@Rva004E8F37@@QAE_NPAVPlayer@@@Z, retail 0x004E8F37 (63 bytes,
// RET 4): over the pointer vector at +0/+4, false as soon as an entry owned
// by the player (rowed Rva004989D7::rva004989D7 0x004989D7) answers its
// vslot 6 with true; true otherwise, including for an empty vector. Owner,
// element and slot identities are not established; names are
// address-derived.
class Player;

class Rva004989D7
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual bool slot06();
	Player *rva004989D7() const;
};

class Rva004E8F37
{
public:
	bool rva004E8F37(Player *player);
private:
	Rva004989D7 **m_begin;
	Rva004989D7 **m_end;
};

bool Rva004E8F37::rva004E8F37(Player *player)
{
	Rva004989D7 **end = m_end;
	Rva004989D7 **it = m_begin;
	if (it == end)
		return true;
	while (it != end)
	{
		Rva004989D7 *entry = *it;
		if (entry->rva004989D7() == player && entry->slot06())
			return false;
		++it;
	}
	return true;
}
