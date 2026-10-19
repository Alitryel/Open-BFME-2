# ControlBarSchemeManager cleanup: corrected local-label admission

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

The first admission attempt omitted the required notes tokens
`gen-funclet;parent=??1ControlBarSchemeManager@@QAE@XZ`. It therefore correctly
used global-name semantics and refused the other `$L367` rows at 0x007989BB,
0x007699CE and 0x0075D392. The previous false-reject diagnosis was wrong and
has been retracted with `re_log.py record ... void`.

Commit 96131fefe9 already implements source-scoped compiler-local EH labels.
With the proven parent recorded, ordinary `add_match.py` admits this cleanup
and verifies all four rows in the owner TU. Its collision checks require a
same-source byte-verified parent, exact parent EH graph, COFF-local label and
exact cleanup bytes and relocations. No verifier edit or alias is needed.
The generated scaffold row is replaced by the native C++ cleanup. This moves
11 bytes to the authored owner but adds no C++ exact coverage, since the
generated scaffold was already exact. The exception handler separately added
10 bytes of exact coverage in the preceding batch.
The link preview is clean: the source's own matched bytes rise 129 to139 with
the newly rowed handler (census 26f19e6e34, retail-truth-2).

Inputs: BFME2 d8961f14c2 plus geometry bank 970c23d0f8 and handler 364e2d2294;
BFME1 f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. Reproduce with normal build.sh,
tools/eh_verify.py on the source, and the explain command above. Existing source
flags and toolchain are unchanged.
