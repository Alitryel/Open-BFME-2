# Strong deringing: transfer the weak sibling's loop repair

Target `_DeringBlockStrong_C`, RVA `0x001C1AD0`, 2030 bytes through
`0x001C22BE`. Only approved clean-room specs `001c1ad0.md` and `001c22c0.md`,
retail disassembly and existing repository reconstructions were read. No external
decoder source was consulted. This is banked reconstruction, not exact coverage.

The weak sibling's advancing vertical and horizontal row/weight pointers also
restore the strong filter's native weight-loop structure. Direct conditional
assignments of clipped results into the eight-element row buffer retain the
retail delayed row stores and improve stack allocation. A view of the vertical
weight row starting at the downward pair gives the strongest diagnostic result.
The complete bank emits 2046 bytes with a 0x174 frame; retail is 2030 bytes with
a 0x178 frame. First difference remains +2, and register/stack allocation,
pointer biases and instruction scheduling still differ.

`trials.json` contains 38 normal `explain_mismatch.py` compilations, covering
sibling loop transfers, conditional clipping, output/weight row pointers,
counter/array lifetimes, explicit stores and compatible intermediate types.
No compiler, verifier or baseline change is involved. Some experimental type
variants were not selected or behaviorally certified. In particular, unsigned
sample promotion is not accepted as a replacement for the signed blend.

For a comparable diagnostic score, the full COFF body is used, including its
tail beyond the target length, and its single actual sharpen-table relocation
is bound to the spec's VA `0x00DB7A28`. Ordered byte alignment rises from
805/2030 (0.396552) for the old bank to 1633/2030 (0.804433). This is not byte
identity. The normal mismatch tool copies retail bytes into DIR32 sites, so a
relocation at a different instruction offset can otherwise contain unrelated
retail instruction bytes; the independent execution checks use the real table
address. The table's existing global name is retained.

`oracle-results.json` records 2560 passing comparisons among complete retail,
actual relocated compiled bank and an independent approved-spec model. They
cover all 64 sharpen indices, positive/negative pitches, four input patterns,
and disjoint, identical and partially overlapping buffers. The model computes
all eight results before writing a row, preserving the strong filter's alias
behavior. Complete buffers/canaries, preserved registers, the cdecl stack
pointer and the unchanged quantizer table are checked. These cases do not
replace the missing whole-byte proof. The accompanying oracle defaults to the
bank and was run again after `re_log.py --stash` wrote it.

Flags: `/O2 /G6 /DNDEBUG /MD`. Reference pointer:
`a18d9ed50607e9175de4d6568798d7d73119de09`. Base: `bc6450dbc6`.
No production source, function row, pin or alias is added.
