# DamageNugget position effect: exact recovery

Native `0x00507D84..0x00508120` is 924 bytes. The bank had 36 differing
relocation-resolved bytes: position/object used EBX/EDI instead of EDI/EBX,
with nearby argument-load scheduling differences. All stack homes, arithmetic,
EH states and behavior already matched. The earlier w6 and w9 handoffs and the
RVA-filtered runner history were read before experiments; their inert loop,
accessor, callee-visibility, scope, flag and permutation trials were excluded.

The new hypothesis was that equivalent source paths can change allocation
costs before merging, as this seat's 0x4404AC and 0x655B90 recoveries showed.
An eight-site factorial varied duplicated cone, coordinate, height, distance,
virtual-call and return paths, using two side-effect-free pointer predicates
and three branch forms. All 1,531 trials compiled; 24 matched exactly. The
smallest selected source is `paths-008-0-1`: only the first, discarded
`obj->getHeightAboveTerrain()` call is duplicated under `if (position == 0)`.
Both paths call exactly the same accessor. C2 removes the test and duplicate
call, preserving every native instruction. This is equivalent C++, without
assembly, a runtime barrier or an optimization pragma.

Read-only C2 debugger traces explain the result: baseline object/position
allocation priorities were 59/59; the selected source makes them 57/59.
The position priority is unchanged; the object loses two units before final
allocation. `priorities.json` retains the relevant records. The compiler was
observed, never modified. `search.py.txt`, `trace.py.txt` and `wdbg.py.txt`
allow isolated reruns under build/; set the drivers' OUT and debugger import
paths there. `results.json` groups all scores rather than retaining 1,531
redundant source files. The original bank/control and raw trials remain in
ignored `build/507d84-mergeweights/` for this checkout.

Integration uses the existing `Made002CC5E1Ctor.cpp` owner and its established
`DamageNugget` class spelling. The position method keeps an address placeholder;
no original retail method spelling is asserted. A pointer-only virtual-call
view expresses native slots 1 and 14 without changing the constructor unit's
existing partial vtable. It emits no instance, alternate vtable or global.
The target's slot 6 and RET 8 establish dispatch and the receiver/argument ABI;
the emitted method is declared nonvirtual in that partial owner view. Removing
the bank's unused constructor context and this integration both retained the
complete exact 924-byte body.

Three bank declarations needed routine link repair, each preserving the parent:
use the real `TheWritableGlobalData` at native load `0x005080DE`/VA 0x00DFE758;
use the existing strong Thing height-accessor provider rather than defining a
second identical 25-byte body; and give partition-filter base Rva000421C8 its
retail three-slot prefix (virtual destructor, allow, getPlayerMask), as its
existing constructor provider and native BC26E0 table establish. No pin added.

Identity/layout evidence remains the w6/w9 record: native vtable 0x00864048
slot 6, existing constructor 0x00507C2D and target field/callee accesses establish
the owner and layout. WorldBuilder 0x0109FAD0 supplies the doEffectPosition
semantic association. No new donor source was read or imported. `inputs.json`
records the working and BFME1 revisions and dependency hashes; the verified
BFME1 checkout stayed at 42bba2d while another runner seat held its freshness
update lock.

Validation: normal add_match/build gates pass all 14 owner rows, including
11 float literals. All three owner EH graphs are EXACT. Native parent handler
0x0079421E is newly rowed (10 bytes, FuncInfo 0x0094714C); the graph-proven
11-byte and 8-byte cleanups at 0x0079420B/0x00794216 replace their gen_uw rows
with the parent's own compiler-emitted labels. No generated source was edited.
`eh-placements.json` records the exact bindings. Link preview is LINKS,
463 -> 1,393 linked bytes against published census 08160bc2c9. Frozen-source,
class and pin consistency checks pass. place_bodies reports no additional body
or pin. A separate trial TU also matched, but was discarded because the existing
owner gives a measured census context. The first unstaged check_csv invocation
could not read the deleted bank; the final check runs after staging its deletion.
