# Narrow-string constructor link sweep, 2026-10-22

BFME2 b68575f39f, BFME1 37c3022d, unchanged TU flags. Published census 08160bc2c9: PeerThreadNickError.cpp 394 B, MainMenuUtils_hasWriteAccess.cpp 233 B, stlport_money_put_long_double.cpp 184 B each legacy 0 -> 0; sole blocker nonretail narrow basic_string<char>(const char*,allocator) emitted COMDAT.

Two trials each: plain explicit-specialization declaration; extern-template constructor declaration (same result, unlike reserve suppression). Money do_put frame grows 0x4c -> 0x50 and cleanup label disappears. hasWriteAccess no longer reuses allocator byte at ebp-0d: four distinct slots appear. Nick callback parent fails and cleanup group has two indistinguishable matches. Neither suppression preserves optimizer knowledge. All original sources restored, claims released, no gain claimed.

A future repair must retain allocator/side-effect knowledge and original cleanup identities, or repair shared provider selection; do not repeat these declaration forms. Horde/PCA notes hold related visible-body trials. No need to bank a nonmatching product body: only a constructor declaration was added immediately before each existing bfme link decl-only block.

## Preserved checkout investigation (base 8e4ab4d89b)

Narrow C-string constructor visibility, 2026-10-22
================================================

Base 8e4ab4d89b, census 08160bc2c9 (2026-10-22 17:08). Current
hasWriteAccess, PeerThreadNickError and W3DHordeModelDrawSetModelState all
link 0 B; their sole blocker is the emitted basic_string<char> C-string
constructor differing from the rowed 108-byte body at 0x9100. In the first
consumer it is a 73-byte /O1 body using EH_prolog, an outlined base ctor and
strlen, unlike the native /O2 body. Changing its name is unjustified.

Tested explicit extern-template constructor instantiation declarations both
after includes and at EOF, preserving vendor code. Both suppress visibility
needed for caller temporary escape/lifetime analysis: hasWriteAccess uses
four distinct allocator-byte slots instead of one; NickError changes its
allocator temporary from ebp+0xb to ebp+0xf. Horde changes its parent and
unwind symbol mapping, including an ambiguous funclet group. Both complete
byte gates fail. All three sources restored from exact preparation backups.
No provider pin, marker or unverified body remains.
Restored-source final byte gate: 44/44 rows across these three consumers,
AssetManagerImplRefresh.cpp and stlport_locale_global.cpp. Literal, import
and floating-point reference checks pass. Model: gpt-6.1-sol; repository
MSVC 7.1/Wine toolchain and each unit's unchanged source flags.

Other sole-blocker consumers BfmeNarrowRecord00079C23Ctor,
VersionBlockParserText and stlport_money_put_long_double were not changed:
foreign RVA/file claims cover them. A future repair must preserve the
constructor's compiler-visible escape summary while supplying a retail
outlined body; do not repeat extern-template placement variations unchanged.

Final independent locale triage: the published index still contains a strong
locale destructor in stlport_wide_money_put_string.cpp. Replacing only the
consumer's destructor visibility changes locale::global's verified unwind
funclets (and an incomplete import declaration fails linkage). Both trials
were reverted. Checking the unchanged current provider and consumer together
removes this stale duplicate: locale_global already LINKS 364 B. This is an
existing upstream improvement, not a gain from this session. No source change
or new claim is needed for it.
