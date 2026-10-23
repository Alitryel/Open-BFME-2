# LargeGroupAudioUpdateModuleData interface and lifetime repair

The existing constructor, copy constructor and destructor emitted different
private tables for the same native class: 16, 4 and 16 bytes respectively.
The constructor table named three nonexistent overrides; the destructor table
used purecall entries. Retail table RVA 0x008549F8 is exactly 124 bytes: the
class deleting destructor followed by the 30 inherited ModuleData defaults.
The next word is 0xC7C34FF3, followed by rain-setting text, not another slot.
The data ledger's old 424-byte heuristic extent includes that subsequent data
and is not used as a table boundary.

Use the existing BfmeModuleData.h interface in all three consuming views, remove
the unsupported overrides, retain the unknown word at +4, and give the destructor
view the same proven 32-byte extent as allocation/factory 0x0024F362. Keep the
one strong class destructor in its existing unit. An initial trial also defined
it inline in the consumers: the copy view uses a different existing member
cleanup name, so the new-variants check rejected that extra destructor COMDAT.
Removing these unnecessary definitions makes the consumers call the existing
provider; their compiler-emitted deleting helpers remain whole-byte exact.

Target identity is established by factory 0x0024F362, the class-name pool key,
the Key/TimeBetweenUpdates/UnitWeight field table, and the constructor/destructor
stores of VA 0x00C549F8. The original intermediate inheritance and meaning of
the word at +4 remain unknown. Rva001408C0Target is the existing neutral name
for the offset-zero base used by the outlined copy call at 0x004ABCE6; this
repair does not promote it to a recovered original class identity. The existing
member copy/destructor names and their admitted fold are retained.

Native destructor 0x004ABFD9 independently restores Snapshot table 0x00BBB554
after destroying the member at +8. The shared native EH graph binds cleanup
0x0078E2F1 to the canonical seven-byte Snapshot fold at 0x0049B47C and cleanup
0x0078E2F9 to the existing member destructor at 0x003ED94F. Qualified canonical
Snapshot teardown in the interface destructor, and the empty neutral base
destructor, emit that whole seven-byte body including its real vtable relocation.
Admit those two lifetime folds as zero-unique-byte rows, with no pins. The
existing generated eight- and eleven-byte cleanup placeholders are rehomed to
the actual C++ constructor and independently located through its entire EH
graph; no generated source is edited. Admit the naturally emitted ten-byte
handler 0x0078E304, whose native FuncInfo is 0x0093EA40.

The three old registry declarations also disagreed on their mangled type.
Use the already defined data-ledger owner g_Va00E03CE0 and cast its address to
the existing insert/remove views. This introduces no second datum or definition.
The generic AsciiString empty-string reference in the shared slot-14 body is
an existing data-ledger spelling, not newly recovered data ownership.

Validation: normal build.sh passes nine rows across all three files, every
parent EH graph is EXACT, frozen-file checks pass, and data_check reports zero
findings with all nine converged addresses also clean. The independent family
audit requires strict include-inventory receipts, complete function extents,
all 31 table destinations, full literals, and existing cleanup/runtime bindings.
It verifies all three complete 124-byte tables, all 30 local inherited bodies
per table, the existing 111/102/72/28-byte functions, and the seven-byte lifetime
folds. The handler proof resolves and compares all ten bytes independently.
place_bodies finds zero further bodies and zero pins after the final change.

The default scratch compilation initially omitted the tracked copy unit's
regional /O1 /arch:SSE /G7 settings and emitted 123 bytes. Restoring the actual
settings gives the complete native 102 bytes. Moving the base destructor
definition in the unit was inert and is not a useful further hypothesis.

The new-variants check passes with the strong destructor kept out of consumers.
A refreshed published-index preview (census 8eecc93d07, 2026-10-19 13:17) predicts
all three units link, 0 -> 313 existing bytes. It rebuilt 202 stale objects and
replaced 985 rebuilt definitions in memory. This is a bounded preview, not a
new census or runtime result. One shadow identity finding remains: other units
still emit divergent global ModuleData destructor views; thirteen copies have
four variants, while all three repaired copies agree on the complete native
seven-byte provider. Those other views are not reconciled or newly certified
here. No full-engine link gain is claimed.

This recovers ten new strict C++ bytes and replaces nineteen bytes of generated
cleanup scaffolding with real parent lifetimes. Existing constructor/destructor
bytes and both seven-byte folds are not new unique coverage. No shared header,
verifier, baseline, assembly, artificial throw, volatile barrier or alias pin is
added. Inputs: BFME2 06b1831adb; verified BFME1 pointer
6b9d92bf92debd03e4357462bab41f701651e67c. Model gpt-6.1-sol.
