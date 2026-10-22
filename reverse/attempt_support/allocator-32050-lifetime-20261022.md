# GeneralAllocator chunk-check count, RVA 0x00032050

The 140-byte retail body is recovered in `memory_pool.cpp`, replacing the
generated dump row. The existing 0x000320E0 caller now calls the member directly
instead of using a union to reinterpret the dump symbol as a member pointer.

The intermediate sum dies before lock teardown; a separate final count survives
the `LeaveCriticalSection` call. This ordinary lifetime split lets MSVC 7.1 keep
the intermediate sum in EAX and final count in EDI. A negative control that
accumulates and returns the same variable changes the register allocation.
`CheckCount` is the existing helper, with five checks in native order. The fifth
failure condition is `size >= requested + 0x10`, where `requested` is argument
two, not the chunk's size. No padding, added volatile access, barrier or inert
conditional was introduced.

Target image SHA256:
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
Target body SHA256:
`b318c9d690e25f3a6a4347ed1999846a59623c150507d5733652eba78d93e85f`.
Initial isolated raw body SHA256:
`29d6475962e10b9da941945bf2bd83f9874f7bbac8298e76313ab5a2f851cc22`.

The three relocation sites are +0x11 (EnterCriticalSection IAT), +0x31
(GeneralAllocator::rva00031F90), and +0x81 (LeaveCriticalSection IAT).
The full body ends in `ret 8`; no truncation or extra tail is admitted.
The final admission uses the actual owner's `/EHsc` settings, not merely the
isolated experiment's default `/EHsc-`. `add_match.py --replace-rva` verified
49/49 owner rows, including the direct caller, and all 40 named imports.
An independent fresh owner-context compilation manually resolved all three
relocations from import names and the rowed callee, reproducing all 140 bytes
without copying retail relocation bytes. Its 0x00031F90 callee also matches its
complete 179-byte body. The negative control is 141 bytes in full extent; its
earlier 140-byte diagnostic comparison was truncated and is not an exact claim.
Commit and push hooks independently check the outgoing change.

This is C++ recovery of an already ledger-covered dump, not a claim of 140 new
ledger-covered bytes or a whole-program linking/runtime improvement.

Experiment artifacts: ignored `build/rea-campaign-20261022/allocator_count_round2/`.
Independent review artifacts: ignored `build/rea-campaign-20261022/allocator_exact_review/`.
REA's separately retained native allocator dossier corroborates the observed
140-byte body but is not used as a byte-match or source-identity proof.
