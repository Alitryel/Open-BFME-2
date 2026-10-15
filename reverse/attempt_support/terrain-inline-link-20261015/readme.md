# Terrain recursive flip inline emission repair

W3DTerrainBackgroundSetFlipRecursive.cpp emitted two unused nine-byte
WorldHeightMap wrapper COMDATs. getHeight differed from the first indexed
copy; setFlipState differed from the first copy and duplicated the strong
WorldHeightMap.cpp definition. Imported forceinline keeps the verified inline
calls and suppresses the two external wrappers. No import reference is emitted.
No class layout, identity, ABI, flags, ledger row, pin or global changes.

Target evidence remains the existing full retail body at 0x00112898..0x00112AD1,
569 bytes, and its ledger provenance. This change establishes no new identity
or layout. BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b supplies the
emission technique only; its diff was reviewed. Existing donor review in
../link-inline-emitters-20261014/readme.md was reused.

## Paired verification

Target base 4544ab62d3f5797b7da06856b37c8450d2c49fd1. Frozen runner index
a2839ea429, 2026-10-15 13:35, from census 5986a99448, 2026-10-15 04:52;
context.json records its hash. The committed link-status selection queue is a
separate measurement. No census/index/status/history or baseline was modified.

Strict-current preparation passes before and after. proof.py independently
refreshes the saved original and repaired object into copies of the same index:
legacy findings 3 -> 0, predicted LINKED 0 -> 569 existing bytes. All three
retained COMDATs, and every retained nondebug section's bytes, flags, definitions,
relocations and directives are unchanged. No retained relocation targets either
removed helper. Data facts are identical and clean; no new COMDAT variant or
import is introduced. object-proof.json records hashes and complete findings.

The five direct providers are BoundedShortGridLoad.cpp, Rva000AD9ABFinish.cpp,
Rva00729300BitPlanes.cpp, Rva000ABD19.cpp and
W3DTerrainBackgroundIsEdgeAligned.cpp. Strict bounded preparation of these and
the caller passes all 15 rows, one float reference and zero skipped references.
Local link_check of all six refreshed objects passes 6/6, legacy preview
1,708 -> 2,277 bytes (providers unchanged). See providers-prepare.txt and
providers-link-after.txt. The first provider-preparation run refused witness
acceptance because the caller's explanatory comment was edited during it; the
recorded successful run was sequential with stable inputs.

The index's four other getHeight copies share digest 5a748c5df570; this unit was
the sole differing wrapper (745fc019f914). WorldHeightMap.cpp owns the remaining
setFlipState definition (d5defe4d3f5d). Those peer objects are absent locally;
their unchanged inventory is legacy evidence, not strict-current verification.
The same-symbol blocker sweep reports only this consumer and that owner. No
other consumer needs a matching emission edit. Authored C++ bytes grow by zero.
This proves a strict-current caller and its direct providers, plus a local
legacy preview improvement; closed-strict placement and census gains are
unmeasured. No full executable link, census build, nightly or boot was run.

## Acceptance

- Ordinary ./build.sh: 1/1 caller row exact, zero literal/import references.
- Strict bounded provider/caller preparation: 15/15 exact, one float verified.
- EH verifier: zero EH rows, no missing objects or baseline debt.
- Data enforce: zero findings; converged admission: eight addresses, zero
  second names or unjudged rows. Paired data facts unchanged.
- Frozen definitions, class gate, new COMDAT variants, CSV and whitespace pass.
- place_bodies.py resweep: zero bodies, zero pins.

Before source/object/dependency snapshots remain under
build/terrain-inline-link-20261015/before; restore the original source from the
recorded target base to reproduce them. proof.py is a bounded evidence check,
not a new gate or census writer.

## Separate blocked attempt and reference freshness

BfmeResultSourceA.cpp's GetAllObjects at 0x00628980 (209 bytes) still emits a
nonretail BfmeResultA destructor versus the canonical 0x0004AA28 provider.
Original strict preparation and restored byte gate both pass 4/4. A
declaration-only destructor outlines required normal cleanup and changes the
parent. Imported forceinline preserves that parent but changes both unwind
direct jumps (0x007A7928/0x007A7920) to IAT jumps and adds an unresolved import.
After these two failed gates the source was restored, the blocker was logged
and both claims released. No repair to this unit is claimed. Reproduction
snapshots are in build/result-dtor-link-20261015. A subsequent repair must keep
normal cleanup inline while retaining direct calls to the canonical unwind
provider; repeating the two trials will not help.

Verified BFME1 checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d;
official master fetched as 95eeb3bef370 during this session. Its update is held
by another seat's live file claim (codex-6bc6-20261008), so no pointer/input
substitution or freshness-success stamp was made. The update still needs
comparative full-byte verification by the owning seat. No donor decoder source
was read.
