# RadiusDecalUpdate constructor/create layout prerequisite, 2026-10-26

Allocated family A shard 1/2 target:
Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalUpdate.cpp.
This follows consolidation-radiusdecalupdate-blocked-20261025.md. No merge
or ledger move is applied; compatible donors remain for Luna.

## Target facts and repair

The fresh normal before trial accepts no donors. Constructor and update trials
fail declaration ordering (RadiusDecal/UpdateModule); Xfer fails because its
operand forward declarations do not precede the hoisted BfmeXfer include.
The planner has one destination alternative, compiler-setting disagreements,
duplicate private views and a stale committed map. Current in-memory routing
approves nine rows, four eligible files, one mixed file and one protected donor.
The displaced factory row has no approved destination and is outside this repair.

Do not equate the create body's byte at +0x28 with the constructor/update flag
at +0x30. The already exact create object reads +0x28; the matched RadiusDecal
constructor/clear establish its empty byte at member offset +8. The existing
RadiusDecalUpdate constructor view has a 0x20 base and a 0x10 decal, followed
by its flag at +0x30. A shared private view now preserves that constructor
layout, while create reads the decal's empty byte explicitly. The original
Zero Hour source is a structural lead, not proof of the complete BFME 2 layout.
Existing interface spellings are retained; no canonical/original header is claimed.

Both sources include RadiusDecalUpdateView.h. The constructor also declares
setWakeFrame through its rowed protected UpdateSleepTime signature, replacing
its existing unsigned-argument alias. No pin, hatch, flag or global was added.

## Verification

Before and after `./build.sh` passes all six rows in the two sources (342 bytes),
plus strings, floats and imports. find_declared_unmatched.py and class_gate.py
pass. The before/after code/data snapshots show:

- All definitions are unchanged except the constructor's relocation spelling
  for setWakeFrame and replacement of the main file's inline UpdateModule
  getObject copy by the inherited ObjectModule getObject copy.
- Both getObject spellings have identical four-byte digest dbc10ce76e7d and
  no external referrers. Their first providers remain FiringTrackerXfer and
  ToppleUpdate respectively; every current copy has that same digest.
- The constructor now binds directly to the existing owner at 0x0044DF71;
  the before alias reached that same address. All six rows have twenty code
  references and zero wrong bindings. The remaining CxxFrameHandler alias
  is unchanged. Data bindings and definitions are identical, with no unread row.

Receipts: build/codex4-radius-{plan,planner,trial-before,build-before,
ctor-before,build-after,offset-evidence,defs-before,defs-after,
identity-comparison,provider-before,provider-after} files.

## Path/debt audit and publication

The previous pending batch landed through 4321bc252b before this edit. Audited
origin/master..HEAD plus these source/header changes: no paths move or vanish.
The new private header has exactly the two intended source consumers, verified
together. Other hits are historical comments, original EA includes in factory
and object-creation units, and original reference paths in doxygen. Those are
preserved. Active tools, hooks, workflows, includes and build/config registries
need no repointing. Receipt: build/codex4-radius-path-audit.txt.

No affected code/data identity, header/MS-header, gate or duplicate register
key exists. The protected pool-key data debt remains with its unchanged source.
File reduction zero; registered identity debt retired zero; recovered C++ bytes
zero. This is prerequisite evidence, not a confirmed Luna landing or census gain.

Keep the two source file claims, new header/evidence file claims and six RVA
claims until publication is confirmed. Release file/RVA scope after publication;
release --landed alone does not settle existing-row prerequisite claims.

Final acceptance: the normal after dry-run accepts the seed and constructor
unit, six rows / 342 bytes, where the before trial accepted none. Actual
composed object build/tu_skeleton/fb47e511f99ad6c5.obj has all six code
definitions with identical digests, sizes and COMDAT selections to the donor
union. All sixteen undefined references agree after internal resolution.
Composed data bindings/definitions exactly equal both standalone donors:
three unchanged vtable targets plus the exception-list reference.

EH verification: two rows EXACT, no baseline exception or missing object.
Converged data check: two sources, ten protected addresses, zero second names
and unjudged rows. Scoped new-variant link admission exits zero without a
finding; this does not measure census gains. Planner currency check passes.
Receipts additionally include build/codex4-radius-{trial-after,composition-evidence,
composed-data-comparison,bindings-after,data-after,eh-after,link-after,
planner-after,currency-after}.

Remaining: Update is rejected because the shared class does not yet declare
its update virtual method. Its interface adjustment must be reconciled with
the constructor's existing secondary vtable identities before adopting it.
Xfer still lacks its operand declarations before BfmeXfer in composition.
The mixed SubsystemNameGetters4 file, protected pool key and unplaced factory
row remain outside this prerequisite. Do not repeat an unchanged trial for
those blockers. This demonstrates a constructor unblock; Luna has not landed
a merge here.
