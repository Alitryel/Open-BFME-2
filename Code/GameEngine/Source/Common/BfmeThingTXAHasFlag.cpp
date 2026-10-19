// BfmeThingTXA slot presence test: twelve-byte frameless member with one
// shape:
//
//     xor eax,eax / cmp [slot],eax / setne al / ret
//
// The global slot at DEC3DC holds the BfmeThingTXA singleton (proven by the
// creator at 0x1185F4); the body reports whether it is populated. Unlike the
// sibling flag helpers in BfmeThingTXAFlags.cpp (defaults), this comparison
// keeps the slot in memory against a zeroed eax, which needs /O1 (defaults
// load the slot into a register first); hence the shard TU, split on
// mismatch per the landed-TU flag law. Identity beyond the slot is not
// recovered, so the body keeps its Rva name.
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// The slot is ww3d.cpp's private ?Movie@WW3D@@0PAVFrameGrabClass@@A, read
// through a TU-scoped friend view (real decoration, no alias).
class FrameGrabClass;
class WW3D
{
	friend bool Rva00117AC0HasFlag(void);
	static FrameGrabClass *Movie;
};

bool Rva00117AC0HasFlag(void)
{
	return WW3D::Movie != 0;
}
