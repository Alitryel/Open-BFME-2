# Narrow-string constructor link sweep, 2026-10-22

BFME2 b68575f39f, BFME1 37c3022d, unchanged TU flags. Published census 08160bc2c9: PeerThreadNickError.cpp 394 B, MainMenuUtils_hasWriteAccess.cpp 233 B, stlport_money_put_long_double.cpp 184 B each legacy 0 -> 0; sole blocker nonretail narrow basic_string<char>(const char*,allocator) emitted COMDAT.

Two trials each: plain explicit-specialization declaration; extern-template constructor declaration (same result, unlike reserve suppression). Money do_put frame grows 0x4c -> 0x50 and cleanup label disappears. hasWriteAccess no longer reuses allocator byte at ebp-0d: four distinct slots appear. Nick callback parent fails and cleanup group has two indistinguishable matches. Neither suppression preserves optimizer knowledge. All original sources restored, claims released, no gain claimed.

A future repair must retain allocator/side-effect knowledge and original cleanup identities, or repair shared provider selection; do not repeat these declaration forms. Horde/PCA notes hold related visible-body trials. No need to bank a nonmatching product body: only a constructor declaration was added immediately before each existing bfme link decl-only block.
