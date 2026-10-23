MultiByteToWideCharSingleLine link blocker, 2026-10-22
===================================================

Inputs: BFME2 f01c130123, retained BFME1 37c3022de1; census ae3b3e68e2,
retail-truth-4. Parent 0x003288E9 is 195 B; handler 0x0077B2AC is 10 B.
Current source passes both rows with strict reusable receipts. The legacy
preview counts 204 nonpadding bytes and refuses the local wide C-string
constructor and const-wchar range-initializer copies. Monetary string
providers were included in the paired preview to avoid their stale allocator
copies being mistaken for a new blocker.

Trial 1: declare only the wide C-string constructor and its const-wchar
forward-tag range helper. All parent instructions and calls retain retail
shape, but frame grows 0x10 -> 0x14, local string -0x1C -> -0x20 and allocator
argument +0x0B -> -0x0D. This matches the historical opaque-callee packing
problem: constructor visibility proves the empty allocator does not escape.

Trial 2: retain constructor visibility and declare only its forward-tag range
helper. MSVC 13.10 crashes with C1001, Utc/src/P2/main.c line 148, attributed
to vendor/stlport/stl/_string.h:376. No alternate compiler or gate workaround.

Original source restored; ./build.sh passes 2/2 plus string/float/import checks.
No retained source edit or link gain. Resume with a supported way to preserve
the constructor non-escape information and keep its retail out-of-line call,
while replacing its mismatching helper emission. Scratch diagnostics are in
build/link-seat-20261022e/multibyte-{trial1,trial2,restored}-byte.log (untracked).
