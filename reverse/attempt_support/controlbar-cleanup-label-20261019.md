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

Follow-up identity audit: the shadow check exposed a pre-existing declaration
error hidden by the parent's masked cleanup comparison. The private `ListBaseInt`
member named the base destructor at 0x004EC395, while the native cleanup calls
the complete list destructor at 0x00200667. Replacing the private view with the
actual STLport `list<ControlBarScheme *>` preserves the entire parent and EH
graph and emits the complete 5-byte destructor at the latter address. That body
is admitted as an identical folded copy, with all owner relocations checked.
The cleanup label becomes `$L3825`; the existing parent-owned `$L367` row is
resolved by the verifier's supported EH-based renumbering check. No alias pin
or verifier change is introduced. The full cleanup and its actual callee now
agree, instead of relying on the parent's masked comparison.

The consumer declares its list-base operations out of line. Compiling their
bodies inside it either emits non-retail allocator operations or removes the
native exception-state transition before the base destructor call. The small
`ControlBarSchemeList.cpp` provider follows the already verified
`RadarObserverListBase.cpp` compiler settings: `/O1 /MD /EHsc /DNDEBUG`, the
bfmelist and bfmealloc shims, `_CRTIMP=` and `_STLP_USE_STATIC_LIB`. Its explicit
specializations preserve the STLport 4.5.3 clear and destructor bodies. Both
whole bodies match the existing 39-byte and 23-byte int-list owners, including
every relocation. This supplies genuine pointer-list definitions without
linker alias directives, new address pins or shared-header edits.

Final verification: the manager's five rows and the provider's two rows pass
the ordinary byte gates; the manager's full EH graph is EXACT. The identity
scan reports 13 references and zero wrong bindings across both units, and
placement finds no further bodies or pins. Normal pre-commit COMDAT checks pass.
The old census cannot preview a newly added provider. A current-ledger preview
first needed the missing Rva00034D10Snapshot object (ordinary build passed),
then refused because 10,827 unrelated objects lacked current compiler evidence.
No full rebuild, census or link cycle was launched. The earlier clean preview
above describes the original owner before this type repair; a complete link
result for the repaired owner and new provider remains unmeasured.

Inputs: BFME2 d8961f14c2 plus geometry bank 970c23d0f8 and handler 364e2d2294;
BFME1 f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. Reproduce with normal build.sh,
tools/eh_verify.py on the source, and the explain command above. Existing source
flags and toolchain are unchanged.
