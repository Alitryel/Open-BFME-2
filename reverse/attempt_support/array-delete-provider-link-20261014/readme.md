# Direct array-delete provider repair

BFME 2 checkout 0d68e6544d. Discovery used repair_queue.py link and
link_rank.py top/near/A rankings. Local previews use the runner's unchanged
index measured at 147cfae2cb, 2026-10-14 07:27; index-meta.json records its
SHA256. Committed link_status.csv is a separate discovery measurement at
67e1365aa9. No census build, measurement, status/history update, full link
cycle, nightly or boot operation was run.

## Verified repair

BfmeConv909, BfmeConv1393, BfmeConv943 and BfmeThreeHundredFiftyThree
call the existing global operator delete[](void *) directly. BfmeConv908
loses an unused stand-in declaration. The provider mem_ops loses its six
remaining alternatename directives, and symbols.csv loses the six matching
pins. bfmeFreeArrayTXA and bfmeFreeTXA already had no source users. The
actual hatch use shrinks by twelve occurrences: six aliases and six
pins. The keyed baseline shrinks by thirteen, also tightening one existing
unused allowance at scalar delete (six -> four; array delete 36 -> 31). No new pin, alias, marker, class view, compiler setting or layout is
introduced. The unmatched 943F/G definitions keep their existing markers;
their calls follow the same direct-provider binding so the old name has
no residual source user.

Target evidence independently proves all six call operands in the four
matched consumer bodies reach 0x0002FD80, the rowed 21-byte array delete.
Scalar delete's separate row at 0x0002FD60 is retained. Existing cdecl
pointer argument contracts and memory-manager class 2 behavior are
preserved; no application class identity is inferred from these calls.
Donor identities/layout uncertainty and existing ledger provenance remain.

The bounded before/after strict preparations each verify 11/11 matched
rows across all six owned sources. proof-before.json and proof-after.json
capture reusable self-strict compiler receipts, full non-debug/non-directive
COFF section payloads, extents, flags, external definitions and relocation
referents. All payloads and definitions agree after normalizing only the
four stand-in names to array delete. BSS has no file payload and is compared
as zero-filled storage, rather than reading the COFF header at offset zero.
comparison.json records the comparisons and native call destinations.

The independent ./build.sh gate passes 11/11; EH verification finds no
affected exception-data rows. Pin consistency, CSV, declared definitions,
canonical classes, converged data and shadow data checks pass. Affected-unit
placement rescan finds zero bodies and zero pins. Normal commit/push hooks
remain required without bypass.

## Link acceptance and limits

With the same current provider and same index, both legacy local previews
report four of six units linking and 219 -> 219 LINKED bytes. The four clean
units also pass a separate local check. The two unchanged failures are
g_bfmeVftBVJS in BfmeConv1393 and g_bfme943VftF1/F2/G1/G2 in BfmeConv943.
This repair replaces alias-dependent resolution with the rowed provider and
lowers hatch debt; it does not establish new link closure. Authored/matched
bytes grow by zero. Self-strict object currency is proven; closed-strict
placement and gain are not claimed. No maintained census result is changed.

## Donor review and freshness

Official BFME 1 master fetch discovers
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed direct-operator repair
fea964f85433012ec0c95a44a8d88f77b4c29af5 and scalar/array discrimination
repair 39928bad445d45d73d25efc24ade970820326b5f. The former's direct-provider
principle applies; the latter reinforces checking each actual native target.
Neither donor addresses nor donor array/scalar choices are target proof.
The existing matched provider and six retail operands establish the choice.
The unchanged verified checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Prior freshness evidence records
old-input MSVC hangs and compiler/stale-provider preparation blockers; the
comparative full old/new byte gate remains outstanding. No unchanged blocker
is retried, pointer advanced or freshness success stamp written.

Remaining follow-up: establish the unresolved vtable providers from target
evidence, or row/remove the unclaimed 943F/G bodies where appropriate. This
batch completes the supported mem_ops alias sweep; other allocator pins
remain in other units and need their own consumer evidence and claims.

## Preparation recovery

The runner stopped replaying 31397ba881 onto 040e15a702. Upstream commit
f53ef500b374526058b5e021ec599ad5b1f7c74c already contains all six source
repairs, six alias removals and six pin removals. The four consumer conflicts
only differ in declaration parameter names; recovery retains upstream's
`void *block` spelling. The scalar-delete hatch count is reconciled to four,
matching the four remaining pins at 0x0002FD60, instead of upstream's five.
The evidence above records the original repair and its historical receipts;
its twelve removed hatch uses and unchanged link totals are not additional
recovery gains. Recovery retains that evidence without reintroducing any
source or symbol change. The preparation record names no stash, and the
original commit remains protected by
refs/runner/preparation/1791967750273672301.

Recovery acceptance at 040e15a702: all 28 original changed paths are
accounted for in recovery.json. Strict-current preparation and an independent
./build.sh both verify 11/11 rows across the six sources. CSV, pins, EH,
declared definitions, class and six-source data/converged checks pass.
The upstream hatch scanner independently counts four scalar-delete pins.
The unchanged census index SHA256 matches index-meta.json; legacy local
link_check remains four of six clean, 219 -> 219 bytes, with the same
unresolved vtable globals. The four clean units independently pass (4/4).
No closed-strict gain is claimed. progress.py origin/master reports +0
authored C++ bytes and +0 linking bytes. No live claims remain for this seat.
The BFME 1 comparative freshness gate remains the previously recorded
follow-up; recovery changes no donor checkout or pointer.

## Subsequent preparation resync recovery

The runner replayed the evidence-only recovery commit 03c1d6ec94 onto
e2b592f647 and stopped at reverse/hatch_baseline.tsv. Current upstream
e04645659d has retired three more unused scalar-delete pins; its one-pin
allowance replaces the earlier four-pin reconciliation described above.
The conflict resolution retains the entire upstream baseline unchanged.
The upstream hatch scanner confirms exactly one remaining scalar-delete
pin. No source, symbol, baseline or maintained census changes are introduced
by this recovery. The earlier repair and recovery evidence remains historical.

resync-recovery.json accounts for all 22 paths in the saved commit, with
hashes of their saved/current contents. All 21 evidence files were preserved
verbatim before this note was appended. The original and resync backup refs
remain intact; the preparation record names no stash. The rebase is complete,
the conflict index is clear, and no seat claims remain.

Acceptance at e2b592f647: strict preparation and independent ./build.sh pass
11/11 rows across all six sources. CSV, pin consistency, declared definitions,
class, EH and six-source shadow/converged data checks pass. The same index at
147cfae2cb retains SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Legacy local link returns the expected failure for the same two vtable-blocked
units: four of six clean, 219 -> 219 bytes. The clean subset passes four of
four. These existing blockers remain a handoff; no closed-strict gain is
claimed. The BFME1 comparative freshness follow-up remains outstanding.
