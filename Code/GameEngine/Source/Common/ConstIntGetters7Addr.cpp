// The members of the ConstIntGetters7.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters6.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// The three 0x0052349B/0x005234A1/0x005234A7 "getters" were retired: they
// are the return arms of the 36-byte player status label static at
// 0x00523489 (AptStrategicPlayerStatus.cpp).

// Four 559F57/5D/72/78 return arms were retired: they belong to the
// complete 27-byte selectors at 559F48 and 559F63. Internal case branches
// target them; no independent function entry is proved.

// ?get@Rva006C5E80@@QBEPBDXZ @ 0x006c5e80 and ?get@Rva006C5E90@@QBEPBDXZ
// @ 0x006c5e90 (13B each, int3-padded): the char pointer at +0xC (+0x8) or
// the shared "" literal 0x00bbac1c when null. No call, jump or data
// reference in retail; owners unrecovered, address-derived names. The 6B
// getters once rowed at 0x006c5e87 / 0x006c5e97 were their null arms.
class Rva006C5E80
{
public:
	const char *get() const;
private:
	int m_00[3];
	const char *m_0c;
};

const char *Rva006C5E80::get() const
{
	return m_0c ? m_0c : "";
}

class Rva006C5E90
{
public:
	const char *get() const;
private:
	int m_00[2];
	const char *m_08;
};

const char *Rva006C5E90::get() const
{
	return m_08 ? m_08 : "";
}
