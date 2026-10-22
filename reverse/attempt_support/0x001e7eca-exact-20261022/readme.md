# Locomotor 0x001E7ECA: exact recovery, 22 October

The standing 1563-byte assignment now matches exactly as real C++ in
`Code/GameEngine/Source/GameLogic/Object/LocomotorRva001E7ECA.cpp`.
This supersedes the 0.975 bank and its earlier allocator blockers. No compiler
binary, flags, optimization pragma, assembly or emitted bytes were changed.
Model: gpt-6.1-sol. Starting BFME2 revision: 257ff359f0.
BFME1 committed/checkout inputs: 37c3022de1ab944c7ffe536440d637dc8199091c.
The freshness updater lock belonged to claudeb3 and was under six hours old
at session start; this seat used the runner exception and did not advance
the pointer or write a freshness-success marker.

## Source-level explanation

The previous body emitted 1567 bytes. Its zero register crossed the sea
underwater/layer calls and the ground-height/mask-constructor boundary.
`docs/recipes.md`'s identical-arm store recipe suggested delaying tail merge:
duplicate the actual call in two identical branches, rather than duplicate
only subsequent statements or alter the value of NULL.

First, duplicating the ground-height call under `object->disabled & 1`
removed the case-6 discrepancy. C2's case-6 zero piece (index 8 in allocator
round 3) naturally gets cost zero instead of two and is split on round 4.
The resulting 1568-byte body has only case 1's five extra bytes. The pinned
compiler was inspected using the existing read-only debugger scripts; its
on-disk SHA-256 remained unchanged. `ground-allocator-rounds.txt` captures
the new source's rounds.

Second, duplicate the underwater call under `flags44 & 1`, assign both arms
to a local bool, and test that bool afterwards. This also splits case 1's
zero web: all three NULL arguments use literal pushes and the vptr stays in
EDI. Both conditions disappear in optimized output; every execution still
makes exactly one identical call. Ground's EDI zero starts at the mask ctor.
Retail and compiled instructions now agree throughout the 1527-byte body
and the 36-byte nine-entry jump table.

The first factorial family tested 289 pairs of duplicated layer/ground
forms (four selectors and if/conditional/local/switch forms). The second
tested 256 underwater forms across eight selectors, eight control-flow
forms, polarity and declaration scope. All 545 compiled. The exact result
is mergedunder_5_0_00; several equivalent variants also match. `families.json`
records the diagnostic scores. Its remaining score of one is a relocated
vptr immediate inside a memory store, not a byte defect:
`scratch-byte-check.txt` records `explain_mismatch.py` resolving every
relocation and reporting EXACT MATCH, compiled size 1563.

The two generator scripts reproduce the search with the earlier tracked
`../0x001e7eca-zero-web-20261022/search.py.txt` copied as `search.py` into
`build/locomotor-zero-cfg/`. Recover base.cpp from the pre-landing bank at
257ff359f0 and retain retail.bin / toolchain setup from the earlier handoff.
Run the merged-calls generator first, then merged-underwater.

## Identity and provenance

The bank's source-level semantic guides were BFME1 cee35b7d8 handleBehaviorZ
and ZH Locomotor.cpp:2220. These establish related purpose, not a proven
original spelling for this BFME2 method; its neutral address-derived name
is retained. Retail callers establish the Locomotor receiver and two-pointer
ABI. Native accesses independently establish template behavior +0x70,
receiver flags +0x44 / height +0x48 / damping +0x50 / matrix +0x68 and the
Object offsets recorded in earlier evidence. WB twin AEB870 is structural
evidence from another revision, including its building-query case.
All 22 direct callee addresses already resolve to matched bodies.

The three rowed callers now declare this member on Locomotor, replacing
their Rva001E46E1 call shim. The obsolete shim pin is removed rather than
adding another name at this address. Their 16 existing rows and the new
body pass the scoped build together (17/17); float literals 53/53 verified.
`find_declared_unmatched` accepts all four sources. The new TU placement
rescan finds zero additional bodies or pins. The usual ledger check needs
the removed bank staged before walking tracked paths; no gate change was
made for that transient unstaged-file error.

Full link status for the new TU is unavailable from the published census
(e20daa4e78); no maintainer-only census or link cycle was started. The normal
new-variant check and commit/push gates provide the available acceptance
checks; publication results are reported in the session result.
