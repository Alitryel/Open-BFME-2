# Subsystem base link repair, 2026-10-20

The five constructors used private wrapper bases that called the rowed
SubsystemInterface constructor through a cast. Their undefined base methods,
or a short competing vtable, prevented linking. Adopt the existing BFME2
subsystem header instead. Reconcile the paired destructor views where needed;
RadarDtor already used that header. Shell also uses the existing AsciiString
view at +0x58 and its external destructor, removing its private StringBase view
and stale update-to-empty alternatename.

## Evidence and scope

Target facts: each constructor calls 0x001B4E63, each paired destructor calls
0x001B4E74, and member/Snapshot accesses prove the twelve-byte subsystem base.
Radar has Snapshot at +0 and SubsystemInterface at +4; Rva00420E67 has these
bases in reverse order, with Snapshot at +0xC. The other three have their first
member at +0xC. The shared header documents the fourteen slots read from
retail BD77A0; no new original class identities or member types are asserted.
The shared-header technique follows the BFME1 reference linking lane reviewed
at 4483e88da1c2f3b9a273f779baac7458bd8bb891; target layout and slot differences
come from BFME2 evidence, not an assumption that the donor ABI transfers.

## Measurement

Paired previews refresh the same ten providers in independent copies of the
published index, before and after. Index commit: 3f413ed3ff, 2026-10-20 18:52.
Object/source SHA256s, exact blockers, index digest and per-file counts are in
measurements.json. Before objects were captured after --prepare-current and
before each source edit. Counts exclude retail 0xCC padding and follow
link_check.source_bytes. The five unchanged clean providers are retained.

| Constructor unit | Before | After | Gain |
| --- | ---: | ---: | ---: |
| RadarRva002D7BD3 | 0 | 256 | 256 |
| Rva00420E67Ctor | 0 | 82 | 82 |
| ShellCtor | 0 | 213 | 213 |
| Rva0022CA95Ctor | 0 | 75 | 75 |
| Rva0022CA74Ctor | 0 | 61 | 61 |
| Paired destructor units | 2917 | 2917 | 0 |
| Total | 2917 | 3604 | **687** |

Each pair was checked using tools/link_check.py before and after. A ctor-only
Rva00420E67 trial moved the vtable conflict to its destructor; reconciling the
paired view preserves all 112 already-linked bytes. Shell similarly needs both
views. Final tools/link_check.py --prepare-current on all ten providers verifies
61/61 rows, four literals and two empty-string refs, one floating literal and
one import, with strict reusable receipts. find_declared_unmatched passes all
nine changed sources. No pins, ledger extents, globals, tool code or shared
headers changed.

This is a **legacy-index link prediction with self-strict provider objects**.
It is not closed-strict LINK evidence or a newly published census; no full link
cycle was run. Reproduce the paired check with the same published index and
strictly compiled providers from the parent and repaired revisions.
