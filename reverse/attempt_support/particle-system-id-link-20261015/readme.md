# Particle-system ID getter emission repair

Three private ParticleSystem views emitted an unused standalone
`getSystemID()` COMDAT that conflicts with the first census copy. Their matched
callers already inline the ID read at +0xA8. Read that field directly and remove
the unused definitions. BoneFX retains an explicit ID value temporary because
its vector insertion takes a reference; passing the field directly changes the
native call sequence. MSVC 7.1 also treats the same-enum static cast as the
field reference here, so that trial was replaced by the explicit local.

The existing BFME 2 caller bytes and layout evidence establish the +0xA8 load;
no donor identity, target offset, or ABI is newly asserted. Flags, ledger rows,
sizes, globals, headers and pins are unchanged. ActiveBody has the same census
finding but is under another contributor's live file claim and was not edited.

## Measurement

Base checkout: d98e4f8d628ba80bb74cb420019ae8c9de10a63c.
Unchanged census index: 28269d8e8d, 2026-10-15 09:31 UTC; SHA-256
6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
Both local previews use this index and refresh the explicit objects in memory.

| Consumer | Before | After | Existing bytes passing legacy local preview |
| --- | --- | --- | --- |
| TransitionDamageFXParse.cpp | getSystemID conflict | Clean | 0 -> 1,645 |
| LaserUpdateInitLaser.cpp | getSystemID conflict | Clean | 0 -> 746 |
| BoneFXUpdateUpdate.cpp | getSystemID plus two allocator conflicts | Two allocator conflicts | 0 -> 0 |

This removes three COMDAT findings and gives a **legacy local preview gain of
2,391 existing matched bytes** across two consumers. All three changed objects
have current **self-strict reusable receipts**. New authored bytes: **0**.
No closed-strict closure, executed linker result, or new census is claimed.
The census index, reverse/link_status.csv and history were not changed.

BoneFX still conflicts on `_STL::__node_alloc<false, 0>::allocate` and
`deallocate`. Those providers and other consumers require separate repair.
Its identity shadow also reports the existing vector push_back binding at
0x002E01C6. identity-paired.json scans the saved before caller objects and the
current callers against the same provider context: the finding is identical.
The complete retained-body and relocation comparison independently confirms
that this repair did not change that call. No identity baseline was changed.
Removing unused getters does not establish the remaining copies' retail
identity or reconcile the full ParticleSystem class.

## Acceptance and object proof

- Bounded link_check.py --prepare-current passes before and after: three
  strict reusable receipts and ordinary byte gates.
- ./build.sh: 19/19 matched rows, 15 string literals, four empty-string
  references, three float literals and four named imports pass.
- eh_verify.py: 5/5 EXACT; no baseline discrepancies or missing objects.
- COFF comparison: each object loses only
  `?getSystemID@ParticleSystem@@QBE?AW4ParticleSystemID@@XZ`. All 97 retained
  COMDATs preserve complete bytes, extents and relocation bindings. All retained
  nondebug sections, external bindings and weak externals compare exactly.
  No retained nondebug section referenced the removed getter. Local targets
  are compared by section contents, flags, extent and offset; SafeSEH indices
  are normalized to their bindings. Debug sections are excluded.
- Local link_check.py: two clean consumers; expected exit 1 for BoneFX's
  independent allocator findings. --new-variants passes.
- Frozen-file and canonical-class checks pass. Converged-data enforcement
  checks three sources and eight addresses: zero second names or unjudged rows.
  Shadow data check: three sources, zero findings.
- place_bodies.py rescan: zero bodies and zero pins.
- check_csv.py and git diff --check pass. The identity shadow passes with
  the single unchanged BoneFX binding described above.

The before snapshots, receipts and comparison script are retained under ignored
build/particle-system-id-link-20261015. object-proof.json records the hashes,
retained COMDATs, strict currency and comparison results. The saved index hash
is asserted unchanged. Evidence was produced with model gpt-6.1-sol.

## Reference review and remaining verification

Retained BFME 1 donor revision:
a7c38d3b2597121f178ab5190b3062478823257d. Its ParticleSystemDestructor.cpp
and ParticleSystemSetSlave.cpp use distinct private getter views; the latter
reads through a handle. They supply semantic context, not BFME 2 layout proof.
The prior linking review in link-inline-emitters-20261014/readme.md is reused
for removing unnecessary emitted inline copies. No donor source was imported.

The official BFME 1 master was fetched at this session start and resolved to
e27a65cb6bd7b2b3cc8ee320ef7ef8a3797b1d0e. The submodule has a live foreign
file claim (codex-6bc6-20261008), so its clean verified pointer was preserved.
The pointer update still needs comparative full verification; no successful
freshness stamp was written. No maintainer-only runner was started.
