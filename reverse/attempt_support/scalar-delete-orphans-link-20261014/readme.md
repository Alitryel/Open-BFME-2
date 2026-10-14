# Retire three unused scalar-delete donor pins

BFME 2 base: 81f7402784. Remove bfmeFreeVDB, bfmeDelVGP and bfmeFreeVMN
from symbols.csv: no Code source refers to those spellings. Their former
consumers BfmeConv1350, BfmeConv1356 and BfmeConv1447 already call the real
scalar operator delete directly. Preserve their established donor identities
and layouts. Correct BfmeConv1447's stale note describing the removed alias.
No authored C++ body, relocation, compiler setting or name is introduced.

Target evidence: scalar delete is rowed at 0x0002FD60, size 21, in
Code/Libraries/Source/WWVegas/WWLib/mem_ops.cpp. The three consumers independently
pass the full byte gate. Their five REL32 calls bind to ??3@YAXPAX@Z in current
COFF and reach precisely 0x0002FD60 in retail. The proof JSON records offsets,
row extents and whole-object SHA256s. Before/after whole objects are identical
and both have strict reusable receipts; none references the removed names.
This establishes the allocator destination, not any additional class identity.

Actual scalar-delete pins decrease 5 -> 2. The keyed hatch allowance decreases
6 -> 2, also retiring one inherited unused allowance. The two remaining pins
are the canonical operator and bfmeFreeTXA. There is no new baseline entry.
This is escape-hatch debt repair with zero new authored bytes and zero claimed
linked-byte gain, rather than a new recovery or census measurement.

## Acceptance

- link_check.py --prepare-current on the three explicitly claimed consumers,
  before and after: 3/3 byte-exact rows, strict reusable receipts; zero skipped
  or baselined literals and two named imports verified.
- Independent ./build.sh on the same three files: 3/3 exact rows.
- Same-index local link_check.py before and after: all three LINKS;
  legacy LINKED 220 -> 220 bytes, with no findings in either preview.
- CSV, pin consistency, declared definitions, canonical class, converged data,
  shadow data and whitespace checks pass. Staged hatch checks accept the shrink;
  inherited shadow findings add no new debt. Commit/push hooks must also pass.

Both previews use census cb660e4d97, 2026-10-13 04:02, index SHA256
4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e.
The committed discovery status measures 67e1365aa9 and is not this measurement.
No index, census receipt, status or history is updated. Self-strict objects
and legacy local linking are evidenced; closed-strict gains are not asserted.
The scratch proof script remains under build/scalar-delete-orphans-link-20261014.

## Donor review and handoff

Discovery checked repair_queue.py link and link_rank.py, then reviewed official
BFME 1 allocator repairs fea964f85433012ec0c95a44a8d88f77b4c29af5 and
e0c623620c077cc216eb49c8e74c16e6349a9a7d. Direct operator binding is applicable;
BFME 1 addresses are not imported. Official master was fetched at
23b143233b5a8664a3bdf8572df6d905c310a5a1. The verified checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85: prior evidence in
allocator-provider-link-20261014/readme.md records unfinished comparative
old/new verification, unchanged-input MSVC hangs and stale-TU/compiler-lock
preparation blockers. No success stamp is written, and those unchanged blockers
are not retried by this standalone consumer repair.

The related mem_ops bfmeFreeTXA directive/pin is left alone because its file
claim is held by yasinschroeder-codex4. This seat claimed only the three consumer
files for this final task; its unused TXA file claim was released immediately.
The already-recorded FireWeapon secondary-vtable blocker was not retried.
Broader donor freshness verification and a future census remain outstanding.
No full link cycle, census build/measure/history, nightly, boot or scheduler
operation was started.

## Preparation recovery on 2026-10-14

The runner replayed this commit onto 692efd52c7. Upstream independently
removed bfmeFreeTXA and reduced array-delete pin debt. Resolve the sole hatch
conflict by retaining upstream's array-delete bound of 31 and setting the
scalar-delete bound to the one surviving canonical operator pin. The three
obsolete donor pins remain removed; no source body is changed. Original
before/after artifacts above describe the earlier base, not a new census.
The preparation backup refs/runner/preparation/1791966347375000662 remains
available; the preparation record names no stash and no untracked files
were present at recovery start.

Recovery acceptance: recovery-prepare.txt confirms 3/3 byte-exact rows and
strict reusable receipts with the synchronized BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Independent recovery-byte.txt passes
3/3 rows; recovery-link.txt uses the unchanged index hash and measurement
cb660e4d97 and reports legacy 220 -> 220 linked bytes. recovery-proof.json
records the current object hashes (which differ from the historical objects),
strict currency and all five independently proven retail scalar-delete calls.
Those call records equal the original proof exactly; all removed spellings
remain absent from the consumers' objects. No closed-strict gain is claimed.
CSV, pin consistency, declared definitions, class gate, converged and shadow
data checks pass; staged hatch checks report inherited findings only. All eight
original evidence artifacts are byte-for-byte preserved, and all three
consumer sources equal the preparation backup. No claims were acquired, no
new task was selected, and no maintainer-only runner was invoked. The rebase
is complete and the conflict index is clear.
