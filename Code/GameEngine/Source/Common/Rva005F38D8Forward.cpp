// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva005F38D8@Rva005F38D8@@QAE?AURva005F38D8Ref@@H@Z @0x005F38D8 29B, moved out of
// Rva005F2CBAProgress.cpp: its callee 0x005F3652 is rowed there as
// Impl::CreateMemberIconSlot returning Rva005F2577Holder, while this forwarder's
// own row returns Rva005F38D8Ref (the same counted reference under two
// placeholder names), so it still calls the address-named spelling.

// Counted icon-slot reference, returned by value through a hidden pointer
// (native 5F3652/5F38D8 RET8), so the type is not a POD; destructor declared
// only.
struct Rva005F38D8Ref
{
	void *m_ptr;
	~Rva005F38D8Ref();
};

namespace StrategicHUD {
namespace ArmyDetailsMovieClip {
class Impl
{
public:
	Rva005F38D8Ref rva005F3652(int position);
};
}
}

// Native 0x005F38D8 29B RET8: forwards the position argument to the
// implementation (+4) icon-slot lookup 0x005F3652 and returns its counted
// reference through the caller's hidden pointer. Same shape as the checklist
// forwarder Rva005CCFF3::rva005CCFF3 (29B, native 5CCFF3, masked twin 1.0);
// the receiver's outer class is unidentified, so address-derived, while the
// +4 implementation is ArmyDetailsMovieClip::Impl (the callee reads its
// +0x24 icon-slot vector) and the int argument follows from the callee's
// clamp of [ebp+0xc] against that vector's size.
class Rva005F38D8
{
public:
	Rva005F38D8Ref rva005F38D8(int position);
	void *unknown00;
	StrategicHUD::ArmyDetailsMovieClip::Impl *implementation;
};
Rva005F38D8Ref Rva005F38D8::rva005F38D8(int position)
{
	return implementation->rva005F3652(position);
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva005F3652@Impl@ArmyDetailsMovieClip@StrategicHUD@@QAE?AURva005F38D8Ref@@H@Z=?CreateMemberIconSlot@Impl@ArmyDetailsMovieClip@StrategicHUD@@QAE?AVRva005F2577Holder@@H@Z")
