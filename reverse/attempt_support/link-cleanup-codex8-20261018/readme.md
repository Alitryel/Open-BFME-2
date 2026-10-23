# Native cleanup binding repairs

At BFME2 revision 11686d672b, four private cleanup declarations prevented
otherwise matched units from linking. No matched rows, pins, address globals,
shared headers, census status or rules were changed.

| Unit | Native evidence and repair | Newly linked bytes |
| --- | --- | ---: |
| FireWeaponUpdateModuleDataCtor | Cleanup 0x0078C551 jumps to Snapshot dtor 0x0049B47C; qualified canonical Snapshot destruction follows FloodUpdateModuleData precedent. | 76 |
| ElvenWoodSpecialPowerModuleDataDtor | Retail range destroy 0x0032C0CA iterates 8-byte string/int pairs and calls the string destructor; inline pair member teardown removes the undefined private pair destructor. | 81 |
| GODupBaseConstructor | Actual BFME2 ctor is 0x00306782 (66 bytes; old source introduction describes the donor). Cleanup 0x00779B36 jumps to Snapshot dtor 0x0049B47C. | 66 |
| Rva00260FF5 | Cleanup 0x00772D57 jumps to filter dtor 0x0049C38A; qualified rowed PartitionFilterRejectByKindOf destruction restores the native base vptr. | 81 |

Identities and layouts remain those of the existing rows. Target cleanup
instructions establish the called destructor independently of donor names.
Snapshot header selection uses the existing local moduledata shim, as already
verified sibling repairs do. The string/int pair is a structural view, not a
new target type identity. BFME1 remains at verified pointer 64d369b90170:
its newer linking commits were reviewed, but these repairs use target evidence
and existing BFME2 siblings. The known BFME1 freshness whole-gate vtable
DIR32 ambiguity remains unresolved; the pointer and success stamp were not advanced.

Paired ordinary legacy link_check uses exactly paths.txt on both sides, with
only these four sources restored to HEAD for before. Published index is
1a1c90e405 (underlying census c2c5ac8c27). Baseline 2/7 clean and 110 B;
after 6/7 clean and 414 B: +304 B. The edited units go from 0/4 to 4/4.
Snapshot and the named filter provider remain clean. StlportVectorDtorFamily
still has independent element-helper/selected-copy blockers; no whole-family
gain is claimed. This is a legacy preview gain, not closed-strict closure or
a new census measurement. No full link cycle was run.

link_check --prepare-current on the four owned sources passes all six matched
rows and one data row with strict reusable receipts. This establishes their
own byte verification (self-strict preparation); closure was not checked.
EH verification reports EXACT for all four EH-bearing rows, zero new debt.
find_declared_unmatched and class_gate pass. Logs are included verbatim.

Other trials were restored and recorded through re_log.py: GDI+ import
visibility changes alter native calls/vptr stores; plain inline GameInfo
getConstSlot, revisited after the newer bridge COMDAT precedent, still changes
EDX preservation in three callers. Their claims were released. The global-name
sweep made zero edits. Many stale ranked entries are already repaired on master;
current previews should precede further trials. Remaining low-blocker leads
include UnitCrate/Animal/Wander/SupplyCenter module-data destructor ownership;
their tables fold onto existing real or opaque owners, so adding names requires
identity/whole-body relocation proof rather than a guessed alias.
