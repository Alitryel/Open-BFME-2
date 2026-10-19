# ControlBarSchemeManager cleanup: add_match local-label collision

The whole `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSchemeManagerDtor.cpp`
was read and its two original rows byte-verified. The native destructor at
0x003204D9 installs handler 0x0077AFC6. Full EH verification is EXACT and binds
FuncInfo 0x00923C88 and the compiler-local cleanup `$L367` to 0x0077AFBB.
The handler is now rowed as its own 10-byte body. No source edit was necessary:
these are the native exception machinery emitted by the recovered C++ lifetime.

The cleanup has an exact 11-byte body, ending at the handler. The object-symbol
reader returns 21 bytes because the following 10-byte handler shares the section;
that is not a 21-byte cleanup extent. `explain_mismatch.py '$L367' --rva
0x0077AFBB --size 11 --source <the source above>` reports an exact match; the
parent EH graph independently proves ownership, rather than adjacency.
The current placeholder is `uw_0077afbb` in Code/gen_small/uw_gen_011.cpp.

`add_match.py '$L367' 0x0077AFBB 11 <source> --replace-rva 0x0077AFBB` refuses
before verification because other translation units already use `$L367` at
0x007989BB, 0x007699CE and 0x0075D392. Those are COFF local labels in independent
objects, not competing external names. This appears to be a false rejection
from the globally unique-name admission rule. No existing row was repointed,
no object-symbol alias was added, and no verifier was changed to evade it.

The existing generated scaffold is retained, so this blocker claims no exact
coverage gain. Future tooling work should scope proven compiler-local labels
to their source while retaining the uniqueness rule for real linkage names,
with a regression test and the required Verifier-Change trailer. The exception
handler itself passed ordinary add_match, byte/EH checks and pre-commit.
The link preview is clean: the source's own matched bytes rise 129 to139 with
the newly rowed handler (census 26f19e6e34, retail-truth-2).

Inputs: BFME2 d8961f14c2 plus geometry bank 970c23d0f8 and handler 364e2d2294;
BFME1 f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. Reproduce with normal build.sh,
tools/eh_verify.py on the source, and the explain command above. Existing source
flags and toolchain are unchanged.
