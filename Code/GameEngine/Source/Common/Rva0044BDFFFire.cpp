// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?fire@Rva0044BDFF@@QAEXH@Z, retail 0x0044BDFF (30 bytes, RET 4): fire one
// of two adjacent functor slots (+0 for 0, +4 for 1) when it is set, through
// the rowed invoker BfmeA1042N::bfmeGo1042D 0x0044BD79 (which throws when
// the functor is empty). Retail reaches it from a vtable through the
// this-adjusting thunk 0x0044BDF7 (add ecx,8), so the slots sit at +8 of the
// complete object. Names are address-derived.
class BfmeB1042N;

class BfmeA1042N
{
public:
	void bfmeGo1042D(void);

	BfmeB1042N *m_bfmeP;
};

class Rva0044BDFF
{
public:
	void fire(int which);
private:
	BfmeA1042N m_slots[2];
};

void Rva0044BDFF::fire(int which)
{
	if (which == 0)
	{
		if (m_slots[0].m_bfmeP != 0)
			m_slots[0].bfmeGo1042D();
	}
	else if (which == 1)
	{
		if (m_slots[1].m_bfmeP != 0)
			m_slots[1].bfmeGo1042D();
	}
}
