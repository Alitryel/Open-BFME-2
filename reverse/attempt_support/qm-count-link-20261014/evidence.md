Quick-match player-template count link repair
===========================================

The side-combo unit's private PlayerTemplate layout is 0x1DC bytes. Calling
STLport vector<PlayerTemplate>::size() inlined the right count but also emitted
a 14-byte helper dividing by 0x1DC. The index's first same-name copy, in
SkirmishGameOptionsMenu.cpp, divides by 0x124. There is no proven retail
address for that standalone size helper; these private element layouts cannot
share that out-of-line instantiation.

The unit now uses a local range view derived from the existing STLport vector.
It adds no fields and computes the same unsigned count from the inherited
_M_finish and _M_start pointers. This retains the original representation,
allocator, element type and subtraction/division semantics. Its implementation
helper has a distinct name and exactly the old helper's bytes, extent and
relocations. This is not a newly recovered retail function or a new class ABI
claim. External PlayerTemplateStore and getNthPlayerTemplate spellings remain
unchanged; no shared header, pin, alias or global was added.

Native 0x005BB3E5 contains 8b41102b410cb9dc01000099f7f9: load finish +0x10,
subtract start +0x0C, and divide by 0x1DC. The whole native function remains
557 bytes at 0x005BB3A1..0x005BB5CE. It has no relocation to the removed or new
count helper. Existing ZH populateQMSideComboBox/WB 0x01588250 identity and
semantic provenance remain in the source and ledger. Target bytes independently
prove this count computation; they do not establish the donor's complete
PlayerTemplate layout or the selected provider's 0x124 layout as target facts.

Baseline source commit: e2b592f647. Discovery queue: committed link_status.csv
at 67e1365aa9, 2026-10-13 16:47 UTC. Actual before/after local comparison:
index 147cfae2cb, 2026-10-14 07:27, SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Index, status and history are untouched. No per-row data-back artifact was used.

The saved before and verified after consumer objects were each substituted
into the same index together with the current, byte-verified Skirmish provider.
Consumer legacy preview changes from one losing COMDAT to clean: LINKED
0 -> 554 existing authored retail bytes (progress excludes three 0xCC bytes).
Provider findings are identical: 46 unresolved, 2 duplicate, 49 losing COMDAT
and 18 wrong-selected findings. Its generic size helper remains selected.
Removing the later conflicting copy changes no existing selected provider.
The new helper has no other indexed definition or source consumer. This index
contains no additional losing copy in this same two-copy conflict.

Acceptance:
- link_check --prepare-current: consumer before 1/1; current consumer/provider
  pair after 6/6, with strict reusable compiler receipts and normal byte gates.
- ./build.sh consumer: 1/1 exact, two literals and one empty-string reference,
  zero skipped/baselined string or import checks.
- EH verify: the parent's complete graph is EXACT, no baseline or missing object.
- Object proof: all 47 retained COMDATs have identical raw bytes, extents and
  relocation digests. The renamed helper is an exact 14-byte twin with no
  relocations. Ordinary nondebug sections, external undefined/strong/weak names,
  hatch counts and the complete parent's raw bytes remain identical.
- Frozen-file, class gate, new-variants admission, CSV and whitespace checks pass.
  Shadow data: zero findings; converged data: eight addresses, zero second names.
- Affected-unit place_bodies: zero additional bodies and zero pins.
- Commit hook code-identity shadow reports five outstanding findings on unchanged
  symbols: the AsciiString destructor binding, list-iterator equality, AsciiString
  scalar-delete, AsciiString-tree erase and PlayerTemplate::isPlayableSide.
  The retained-body/binding proof covers these existing emissions; this repair
  does not resolve that debt. The new count helper has no shadow finding.
- Paired link_check CLI: consumer LINKS; provider fails on its unchanged findings.
  The CLI exit 1 reflects that provider, not a regression in this repair.

BFME1 reference review: verified committed donor pointer
23b143233b5a8664a3bdf8572df6d905c310a5a1; current successful freshness stamp
2026-10-14 08:17, under 24 hours old. Reused today's broader linking review and
read donor repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d. Suppressing a
surplus conflicting private emitter is applicable as a repair principle.
Its alias/pin mechanism, addresses and private layouts are inapplicable here.
No donor code or dependencies were changed. The already-fixed ScriptEngine
getOrCondition and Horde radius conflicts were skipped after reading their
current evidence; the stale discovery queue was not treated as a new task.

One discarded alternative, direct end()-begin(), generated an extra pointer
load and changed scheduling/length to 559 bytes. The final inherited-pointer
expression retains the exact original source semantics and compiled body.
Backups and the reproducible proof script remain in build/qm-count-link-20261014.

New authored bytes: zero. Strict compiler currency is proven; LINKED gain is
legacy local preview only. Self-strict placement, closed-strict closure and a
fresh maintained census gain remain unmeasured. No full link cycle, census
build/measure/history, nightly or boot runner was started. The selected
Skirmish provider's broader donor/layout/dependency blockers need separate work.
