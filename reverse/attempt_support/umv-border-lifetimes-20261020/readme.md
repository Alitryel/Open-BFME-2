# UpdateUMVBorder: independent lifetime and compiler checks

Approved spec `reverse/vp6_cleanroom/specs/001b96a0.md` and native
`0x001B96A0..0x001B9AB7` only. No external decoder source was read. Read all
earlier attempt records, the complete bank, the s9 handoff, and the row-distance
follow-up before these trials. The existing complete six-phase bank stays
unchanged: 1042 bytes, 351 instructions, 280/353 aligned equal instructions,
first byte difference +0x43; native is 1047 bytes and 353 instructions.

The new tests distinguish ordinary source explanations rather than assuming
one allocator failure from one family of spelling changes:

| Explanation tested | Result |
| --- | --- |
| Shared meaningful edge-pixel variable across Y/U/V, byte or promoted integer | Byte identical to bank; integer 1039 bytes / 131 aligned |
| Consume memset's real return value to advance left/right destinations | 1031..1071 bytes, 107..165 aligned; worse |
| Read from an advanced cursor using the previous row offset | 1039 bytes / 128 aligned; worse |
| Unsigned border with explicit signed row-copy loop bounds | 1028 bytes / 152 aligned; worse |
| Form chroma top pointers from integer frame offsets | 1045 bytes / 239 aligned; worse, does not recover native row delta |
| Unsigned recon offsets, strides or dimensions; const source pointers | Same 1042-byte bank |
| Explicit Ot/Og/Oi/Oy/Ob2 configuration | Same bank; Og- and O1 are worse |
| Correct C frontend with typedef and no C++ linkage syntax | Same bank; promoted sample remains 1039/131 |
| Guard the first sample, read the next sample only after checking last row | 1071 bytes / 162..163 aligned; worse |
| Separate luma/chroma count lifetimes | 1039 bytes / 177 aligned; worse |
| Partial reuse of edge cursors for corresponding first/last/top/bottom row cursors | Eight natural lifetime groupings: 1017..1042 bytes, 106..263 aligned; worse |
| Typed fill wrapper, including inlined fill-and-advance reference helper | Byte helper reproduces bank; promoted helper 1039/131; returning destination 1055/133 |
| Hash-pinned VC71 SP1 and DDK 4035 compilers, bank and promoted sample | Both revisions reproduce default compiler exactly |

All objects were built through normal `explain_mismatch.py`; no raw shared-cache
compile calls were made. Successful objects have zero relocations. Concrete
revisions, measurements and four concise source patches are preserved here.
Two initial C diagnostics failed due to a scratch typedef-conversion mistake;
after correction both compiled normally and their successful results are listed.

The remaining mismatch is the earlier handoff's exact one: Y loop entry jump
and reload versus native direct entry and mid-fill source reload; rotated cursor
spill homes; early chroma border shift; native's repeated border*stride-source
plus bottom distance versus the bank's destination difference. The native and
bank complete first-loop listings were inspected directly. New tests have not
resolved that scheduling/lifetime coupling. This does not prove a compiler
blocker. Keep the stronger 1042-byte bank and earlier behavioral oracle evidence;
no new behavioral-proof or byte-match claim is made, and nothing is left in Code.
