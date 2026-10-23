// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??1BfmeAssignRecord32@@QAE@XZ @ 0x0017330A (71B): EH destructor of the
// 32-byte assignable record used by vector<BfmeAssignRecord32> helpers.
// Layout proven by the rowed assignment operator at 0x00173499 (copies
// AsciiString-like ref at +0 via helper 0x00072A94, int at +4, then six
// more via the same helper for +8) and by the 0x20 stride in callers
// 0x0017351C/0x00173572 plus the Destroy loop at 0x00173AE0 and the
// deleting dtor at 0x00173500 which both call this body. Destroys six
// Rva00087A93 elements at +8 via ehvec ??_M (size 4 count 6 dtor 0x0007B724)
// then the Rva00087A93 at +0 inline. No vtable, hence QAE.

class Rva00087A93 {
	struct Data {
		virtual void slot();
		int ref;
	};
	Data *m_data;
public:
	~Rva00087A93()
	{
		Data *d = m_data;
		if (d && --d->ref == 0)
			d->slot();
	}
};

struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	~BfmeAssignRecord32();
};

inline BfmeAssignRecord32::~BfmeAssignRecord32()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeAssignRecord32InlineAnchor@@YAXPAVBfmeAssignRecord32@@@Z absent-from-retail
void _bfmeBfmeAssignRecord32InlineAnchor(BfmeAssignRecord32 *p)
{
    p->BfmeAssignRecord32::~BfmeAssignRecord32();
}
#pragma inline_depth()
