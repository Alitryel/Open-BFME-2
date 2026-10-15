// cl: /DNDEBUG /MD /EHsc
// Readable out-of-line body of ?isSelectionLocked@BfmeSelectionState@@QBE_NXZ
// (retail 0x0042253A, 20B): the selection-locked guard the two landed
// selectMatching bodies call out-of-line (pin 1744). Returns true only when
// both flag bytes are non-zero (xor/cmp-je/cmp-je/inc shape). Dedicated TU:
// defining it alongside the selectMatching callers would let MSVC inline the
// call and break those matched rows (callee-visibility trap), so it lives
// here with its own TU-local class replica (duplicate emissions pass).

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;

private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};

// ?isSelectionLocked@BfmeSelectionState@@QBE_NXZ
inline bool BfmeSelectionState::isSelectionLocked() const
{
	return m_first != 0 && m_second != 0;
}

// VictoryConditions.cpp defines a visible noinline copy of this body (so its
// testDefeat 0x004207D4 keeps TheGameLogic in a register across the call),
// which is a select-any definition: the owner emits a select-any copy as well,
// or the linked build sees duplicate symbols. This anchor only makes this unit
// emit it for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitIsSelectionLocked@@YA_NPBVBfmeSelectionState@@@Z present-unmatched
bool bfmeEmitIsSelectionLocked(const BfmeSelectionState *state)
{
	return state->isSelectionLocked();
}
#pragma inline_depth()
