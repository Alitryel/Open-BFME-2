// BfmeThingTXA singleton flag helpers: tiny byte accessors around the
// DEC3C8/DEC3C9 lifecycle bytes (sibling to the DEC3DC object slot, proven
// to hold the global BfmeThingTXA by the creator at 0x1185F4).
// Shapes (all frameless, defaults):
//   set1:  mov byte [addr],1 / ret                                    (8B)
//   setv:  mov al,[esp+4] / mov [addr],al / ret                       (10B)
//   getv:  mov al,[addr] / ret                                         (6B)
//   all3:  cmp-chain over the slot plus both bytes, 1/0, shared false (35B)
//   has:   xor / cmp [slot],eax / setne al / ret                      (12B)
// Identity beyond the slot is not recovered, so flag bodies keep Rva names
// (GlobalFlagClearers precedent); the slot test uses its proven meaning.
// No // cl: line (defaults first; split on mismatch).
// The bytes are ww3d.cpp's private ?RecordNextFrame@WW3D@@0_NA (DEC3C8) and
// ?PauseRecord@WW3D@@0_NA (DEC3C9), read through a TU-scoped friend view:
// real decorations, no alias, no second datum.
class WW3D
{
	friend void Rva00117A60SetFlag(void);
	friend void Rva00117A70SetFlag(unsigned char value);
	friend unsigned char Rva00117A80GetFlag(void);
	static bool RecordNextFrame;
	static bool PauseRecord;
};

void Rva00117A60SetFlag(void)
{
	WW3D::RecordNextFrame = 1;
}

void Rva00117A70SetFlag(unsigned char value)
{
	(unsigned char &)WW3D::PauseRecord = value;
}

unsigned char Rva00117A80GetFlag(void)
{
	return WW3D::PauseRecord;
}
