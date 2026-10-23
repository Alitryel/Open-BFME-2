// Clean room: reverse/vp6_cleanroom/specs/001bb9c0.md plus retail only. No
// decoder source was consulted.
//
// Equiprobable bool-coder symbol decode, register form (retail 0x001BB9C0):
// the coder state arrives in ECX with no stack arguments, which __fastcall
// with one pointer argument spells. The boundary is half of (range + 1); a 1
// symbol takes the boundary off the range and window, a 0 symbol makes the
// range the boundary; both are doubled exactly once, and one bit is consumed
// from the refill count with a byte refill from the buffer when it expires.
// VP6_ReadTokens (0x001BC3D0) calls it for coefficient signs.

struct Vp6BoolCoder
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

// RVA 0x001BB9C0
extern "C" int __fastcall VP6_DecodeBool128(Vp6BoolCoder *state)
{
	unsigned code = state->m_code;
	int bitsRemaining = state->m_bitsRemaining;
	unsigned range = state->m_range;
	unsigned half = (range + 1) >> 1;
	unsigned threshold = half << 24;
	int bit;

	bit = (code >= threshold);
	range = bit ? range - half : half;
	code = bit ? code - threshold : code;
	range += range;
	code += code;

	if (--bitsRemaining == 0) {
		bitsRemaining = 8;
		code |= state->m_inputBase[state->m_inputCursor];
		++state->m_inputCursor;
	}

	state->m_range = range;
	state->m_bitsRemaining = bitsRemaining;
	state->m_code = code;
	return bit;
}
