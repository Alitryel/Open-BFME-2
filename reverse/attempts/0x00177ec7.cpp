// ?rva00177EC7@@YAXPAURva00177EC7Pair@@AAU1@@Z
// partial score=0.8 date=2026-10-14
// cl: /arch:SSE /G7 /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
// 0x00177EC7..0x00177F0C (70B). The first 56B (through the if-arm ret at
// 0x00177EFF) byte-matched in Rva00177E95Fill.cpp; the else arm is the
// 13B tail at 0x00177F00 that the ledger currently claims as
// ?setOne@Rva00177F00Fields@@QAEXXZ. Retire that row, then land this.
struct Rva00177EC7Pair
{
	Rva00177EC7Pair &operator=(const Rva00177EC7Pair &that)
	{
		x = that.x;
		y = that.y;
		return *this;
	}
	float x;
	float y;
};

void rva00177EC7(Rva00177EC7Pair *out, Rva00177EC7Pair &value)
{
	*out = value;
	if (value.x != 0.0f) {
		value.x = 0.0f;
		value.y = 1.0f - value.y;
	} else {
		value.x = 1.0f;
	}
}
