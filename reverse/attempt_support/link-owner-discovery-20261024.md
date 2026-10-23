# Linking discovery through unresolved ownership gaps

Inputs: BFME2 c67f34cdc6; official BFME1 master and committed pointer
f5140c1cff6a58e16276fd6de6788186286953d4; published census 0393df10e2
(2026-10-23 19:47). The clean donor checkout was aligned to that pointer.
Its paired full-gate evidence is already recorded under
bfme1-reference-f5140c1c-20261023. The current ledger passes check_csv.

The old ranking repeatedly served landed repairs. Instead, join unresolved
linker names to **every** address candidate in the existing resolver, then
join those addresses to matched ledger owners. This discovers ownership and
ABI prerequisites even when a unit has several independent blockers. An
additive pin is only a hypothesis: neither address equality nor this report
permits an alias, rename, type substitution or claim of newly linked bytes.

The new read-only picker mode is:

```
python tools/link_rank.py --owner-gaps --near 3 --top 30 --json build/owner-gaps.json
python tools/link_rank.py --owner-gaps --near 100 --top 30
python tools/link_rank.py --owner-gaps --file Code/GameEngine/Source/Common/GameEngineInit.cpp
```

It distinguishes an already named provider needing a current-object check,
a different owner requiring native identity/ABI investigation, and a generated
owner needing recovery. Ranking divides each consumer's bytes among **all**
its blockers, including non-addressed unresolved names, COMDAT failures and
address debt. Candidate figures overlap and are not predicted gains. JSON
retains all candidates and the census provenance; console output limits large
fold groups. At these inputs there are 443 mapped unresolved-name leads,
64 among units within three census blockers. These counts are not new work
counts: current objects and previous attempts must still be checked.

Concrete checks illustrate the distinction:

- DeletionUpdate and FireSpreadUpdate now need their actual Snapshot getters,
  not the census's obsolete mask/CRC prerequisites. Including the existing
  ModuleNameGetters3 provider yields 713 -> 1048 B in the three-unit scoped
  preview. The 335 B is an inherited upstream repair, **not this session's gain**.
- GameEngineInit's current object reduces the old 41 blockers to 15, but still
  needs TLS lifetime, virtual-slot and selected-constructor reconciliation.
  Its 9424 nonpadding bytes are not yet linkable. Many old constructor names
  now have real owners; blindly replaying the census list would duplicate work.
- MilesAudioManager's 41566 B retain numerous virtual-owner and container
  dependencies. These need coordinated class/provider work, not one new pin
  per unresolved method. This scope is held by another worker.
- The public mutable string dispatch in the imbue units reaches an unbound
  public append specialization. The real dispatch owner calls private append.
  The matching 96-byte instruction shape alone does not prove that relocation.
  No alias was introduced to conceal this access/owner discrepancy.

The first proposed extension of the existing BFME2 UpdateModule shim was
stopped before edits when FloatUpdate/StructureTopple body claims were refused.
All four acquired file scopes were released; no claimed body was modified.

Validation: five new synthetic ownership-discovery tests pass, covering
additive candidates, duplicates, generated ownership, missing bodies and ranking
with independent blockers. Together with test_gate_exploits.py, pytest reports
26 passed and one existing open-escape fixture skipped by that suite. Ordinary
ranking and file-scoped discovery were exercised. No verifier behavior,
baseline, source body, pin, census or linked-byte counter is changed.

The published index and 23047 compiled objects were fetched. The authenticated
cycle bundle fetch reports no complete prerelease, so no data-back or closed
link measurement was claimed. No census, link cycle, nightly or boot runner
was started. Use this mode to select a claimable ownership prerequisite,
then verify current providers/consumers and native ABI before implementing it.
