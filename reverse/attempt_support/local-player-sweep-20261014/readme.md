# InGameUI local PlayerList accessor link repair

Base checkout cb7a733168. Discovery used repair_queue.py link and link_rank.py
against committed link_status.csv (67e1365aa9); paired local previews use the
runner-provided census index 147cfae2cb, 2026-10-14 07:27. Its SHA256 and the
source/object hashes are recorded in object-proof.json. No census index,
status, history, baseline, pin or per-row data-back artifact was changed.

The three InGameUI units independently inline a PlayerList view reading
+0x10, but also emit a surplus generic getLocalPlayer COMDAT (8b4110c3).
The first indexed copy is PartitionManager.cpp's +0x0C read (8b410cc3,
digest 96acfa69671b); the census has no retail address for that accessor.
These different implementations cannot safely share one linker name.
This repair gives each local implementation a distinct name and updates
its inline callers, preserving the existing target behavior and ABI.

The new names are implementation helpers, not claimed retail identities
or a canonical PlayerList layout. Target evidence for the +0x10 accesses
is the existing callers' full byte gates. Every helper retains all four
bytes and its relocation facts. All 82 retained COMDAT bodies have identical
complete bytes, extents, digests and relocations. Ordinary nondebug sections,
symbolic EH targets, external undefined/strong/weak bindings and hatch counts
are unchanged. Both paired previews select the same generic keeper.

| Consumer | Existing authored bytes | Legacy findings before | After |
| --- | ---: | ---: | ---: |
| InGameUIIdleWorker.cpp | 717 | 19 | 18 |
| InGameUIRemoveIdleWorker.cpp | 108 | 5 | 4 |
| InGameUIUpdate.cpp | 1410 | 4 | 3 |

The same-index legacy preview removes three losing COMDAT findings. Clean
units remain 0/3 and LINKED remains 0 -> 0 bytes. Strict reusable compiler
receipts prove the three owned objects current before and after; this is
self-strict object evidence, not a self-strict placement gain. Closed-strict
provider closure, actual link.exe placement and a fresh census were not
measured. New authored C++ bytes: zero.

Acceptance evidence:

- Bounded link_check.py --prepare-current, before and after: 10/10 exact
  rows, strict reusable receipts; no provider scope expansion.
- Ordinary ./build.sh: 10/10 exact; five string literals, four compiler
  float literals, zero baselined/skipped/unverified reference checks.
- Prescribed link_check.py preview before and after, plus a paired preview
  which refreshes only these three source objects in the same index.
  All finding categories other than the three COMDAT removals are identical.
- EH verifier: 2 EXACT, no nonexact, baselined or missing rows. Frozen
  definitions, class gate, new-variant admission and whitespace checks pass.
- Converged data: all three sources checked, eight addresses, no second
  names or unjudged rows. Shadow data reports three pre-existing wrong-name
  findings (two static NameKey guard symbols and MessageStreamSubsystem).
  paired-data.json proves every data binding and definition, and all three
  findings, identical before and after; these are not new findings.
- Affected-unit place_bodies.py resweep: zero bodies and zero pins. CSV
  checks pass. Normal commit hooks remain required.

Independent blockers remain: the idle-worker units have duplicate definitions
and selected providers proven wrong, plus other local Object/Drawable/STL
COMDAT conflicts. InGameUIUpdate still references unresolved Rva0043D15FUpdate,
g_00DBBADC and g_00DFE32C. These dependencies were not retried or renamed.
Full lists are in paired-link-after.txt. No broader link gain is claimed.

This continues the prior session's reference review, preserved in
../local-player-link-20261014/readme.md: verified BFME1 revision 23b143233,
linking repairs de59a7e9, d2e21369 and b955ec48. Their conflicting local
emission cause applies; their donor-specific layouts, pins and aliases do
not. No donor code was imported or unchanged donor scan repeated. The
freshness success stamp from 2026-10-14 08:17 remains under 24 hours old;
no reference pointer or input was changed here.

The original thirteen-consumer preparation waited on the host's full-build
compiler lock and was stopped before source changes. This batch was narrowed
to the three InGameUI consumers using the supported small-file compile path;
no compiler lock, verifier or hook was changed. All ten other file claims were
released before editing. They remain eligible same-cause follow-up candidates,
with additional independent blockers listed in the prior sweep handoff.
No full link cycle, census build/measure/history, nightly or boot/scheduler
runner was started. Scratch source/object backups and proof scripts are in
build/local-player-sweep-20261014; claims are released at session completion.
