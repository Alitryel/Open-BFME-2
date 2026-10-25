# FX-list constructor and native bucket helpers, 2026-10-25

Inspected after `feb95824fa`; BFME 1 input remains
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. No header, donor pointer,
compiler flag, pin or verifier changed.

This resolves the concrete constructor-emission prerequisite recorded in
[the earlier handoff](../fxlist-store-link-20261025/readme.md). That attempt
already showed that optimization alone and exposing the vector constructor
were insufficient. The additional evidence here is the complete allocator
lifetime and recursive bucket-helper call chain.

The store's existing 68-byte constructor and 31-byte hash-map wrapper retain
their whole bytes and relocations. Its 10-byte EH handler retains its bytes;
the compiler-local FuncInfo label changes, and the complete parent graph
remains EXACT. The native 64-byte bucket constructor calls the existing
55-byte vector base at 00025100, not the 15-byte outer vector constructor.
Its unused allocator lives in the argument home at EBP+0B, not a new local.

Remove the declaration-only specializations that hid the allocator destructor,
vector/base constructors, end() and insert() from this compiler. Standard
definitions restore the native lifetime, inline forwarding wrappers and read
of the finish pointer. The complete recursive helpers are normally admitted
with `add_match.py --icf-owner`, with no new pins:

- Bucket-count selection: 0005571B, all 48 bytes and all data/call relocations.
- Bucket initialization: 00148DDF, all 59 bytes, including the direct native
  `_M_fill_insert` call at 00029CA0 instead of its outer insert wrapper.
- Bucket-table construction: 001E2F8E, all 64 bytes and exact EH graph.

`FXListMapNodeEmit.cpp` previously supplied a speed-optimized 50-byte copy of
the bucket-count operation. Declare that specialization there so the link
keeps the constructor unit's whole retail 48-byte copy. The node unit's owned
41-byte operation retains its complete bytes and relocations. Existing
optimization pragmas are unchanged.

Target facts establish empty-table/bucket operations and their calls. The
existing by-value FXList template spelling is retained as a code-generation
view, with the new rows explicitly `gen-alias`. Empty bucket construction
does not establish the application's value payload, original type spelling,
or compatibility of other FX-list lifecycle views. No broader family or
closed-executable clearance is claimed.

Validation first passed 19/19 rows across the two changed units and both existing
owners, four EXACT EH graphs, one data row and four strict current receipts.
Both changed sources pass the frozen-definition check. The placement rescan
finds zero further bodies/pins. The normal current-object preview against
index `51fde01dff` links all four units, covering 726 authored bytes; the
constructor unit's previously blocked 109 bytes now preview cleanly.

`paired-preview.json` replays old and repaired objects under two fixed fact
sets. The original-facts pair excludes exactly the three new aliases from
both sides; the final-facts pair includes them on both sides. Shared-address
uncertainty makes the final-facts old control less strict, so its clearance
is not source-repair credit. The production helpers' normal whole-byte and
relocation admissions independently prove the actual source fix. Only a
later maintainer census can change headline linked coverage; no headline or
closed-strict gain is asserted here.

Final provider check: the identity gate exposed a wrong 84-byte clear copy in
the constructor unit, competing with FXList.cpp's rowed 73-byte owner at
0060CFB6. Declare that operation instead of emitting another copy. All six
owned constructor-unit rows retain their bytes; both parent EH graphs remain
EXACT, and the final identity scan reports zero new findings. The clear owner
also passes its seven rows with a strict current receipt: the expanded scope
therefore has 26 verified rows, four exact EH graphs and five strict receipts.
The unchanged enforced data gate judges all five sources, with zero second
names and zero unjudged rows.

The four original units still preview cleanly (726 authored bytes). The fifth,
FXList.cpp (620 bytes), retains independent particle-manager, terrain-layer and
drawable-factory bindings, two nugget vtables, and FXNugget-list construction/
destruction blockers. Its clear operation is verified; its whole unit is not
claimed link-clean. `final-link-with-clear.txt` records this limit. This is the
next concrete family scope, not a new issue hidden by the constructor repair.

Publication preflight initially refused mismatched raw-object hashes in local
cache receipts. Removing the two generated object/sidecar pairs alone reused
the same bad artifact. Fresh normal compilation with the supported
`BFME_OBJSTORE=off` cache setting regenerated matching receipts; the supporting
Armor owner needed the same refresh. The unchanged enforced data gate then
passes all four sources with zero second names and zero unjudged rows. Final
receipt evidence independently asserts each raw object's MD5 equals its
recorded object identity. No verifier was changed or bypassed.
