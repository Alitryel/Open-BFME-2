# Watchdog primary-table reconciliation

Base: `7b4cd7d93454a26413b5f7dd3ec111ee7a6c7e21`.
Frozen local index SHA256:
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
Index measurement: `a2839ea429`, 2026-10-15 13:35; underlying census:
`5986a99448`, 2026-10-15 04:52. The newer committed status CSV was used
for discovery only. No census, full link cycle or status/index publication ran.

## Target evidence and repair

Retail table VA `0x00BE6FD8` contains four words:
`0x006257CD, 0x006256C0, 0x006254CA, 0x006255AD`. Existing matched
rows bind these to the deleting destructor, start, Thread_Function and
reportWatchdog. The matched constructor installs this table; the thread
function calls its diagnostic slot 3. The existing provisional method names
are retained; exact bytes do not prove original spellings.

The destructor unit's private base declaration allocated Thread_Function
before the derived start entry, reversing slots 1 and 2. The constructor unit
instead emitted three slots: deleting destructor, ThreadClass::Execute,
Thread_Function. Model only the base's virtual destructor in these two local
views and declare all four Watchdog entries in retail order. This makes no
claim about the complete ThreadClass interface. Base layout, destructor,
constructor, and stop declarations remain sufficient for these bodies.

The thread-function unit already declares the complete table in this order;
it is an unchanged provider/consumer in the acceptance cohort. No canonical
header is introduced. Other private views remain outside this bounded repair.
BFME 1 donor `a7c38d3b2597121f178ab5190b3062478823257d`'s
WatchdogDestructor.cpp supports the member teardown order, but uses Execute
rather than BFME 2's existing provisional start name. The four entries and
ordering above are established independently from BFME 2 retail, not inferred
from donor names. Reviewed donor repair `53d32d6b4b377317a3397971629ca3ad20b870e9`;
its string-constructor suppression is inapplicable to this table repair.

## Acceptance and result

`link_check.py --prepare-current` verifies 13/13 rows across Watchdog.cpp,
WatchdogDtor.cpp and WatchdogThreadFunction.cpp, with strict reusable receipts.
`./build.sh` passes all 8/8 rows in the two edited units, including naturally
emitted cleanup and handler rows. String, float and import checks pass.

The paired proof refreshes both phases against the same frozen index. Only
two .rdata COMDATs change: the destructor table swaps two symbolic relocations;
the constructor table becomes the retail four-slot table. All executable
COMDATs, EH data, other nondebug sections, and weak externals are identical.
The constructor replaces its unused Execute binding with the existing start
and reportWatchdog providers; the destructor adds no binding. No code variant,
pin, alias, import or baseline entry is added. The two emitted tables agree.

The local legacy preview and paired proof change WatchdogDtor's sole conflicting
COMDAT finding to zero, unlocking 127 existing nonpadding bytes. The other two
units stay clean: cohort LINKED 643 -> 770 bytes. Self-strict byte checks and
current receipts are established. Self-strict executable placement and
closed-strict closure are unmeasured; no census or closed-strict gain is claimed.
New authored C++ bytes: zero.

Other checks: find_declared_unmatched and class_gate pass; EH verifier has
3 EXACT, 0 nonexact, 0 missing; data enforcement has zero findings; converged
data checks eight addresses without second names or unjudged rows;
place_bodies finds zero bodies/pins. Ledger and whitespace checks pass.

The proof script requires the ignored build/watchdog-vtable-link-20261015
before snapshots and context, the frozen index, and current strict objects.
proof.json records hashes and findings for reconstruction at the named base.
Official BFME 1 master was fetched at `95eeb3be`; checkout/gitlink remains
`a7c38d3b` while the pointer update is separately claimed. No freshness-success
stamp was written. Broader link validation and reference-update verification
remain outstanding.

## Independent rejected trial

FileFactoryClass's deleting destructor still conflicts. Imported forceinline
base-dtor suppression removed only the nondeleting destructor, retained the
wrong deleting body, added an unresolved import and lost required cleanup
uw_007a6f10 (32/33 byte gate). The source and original object/strict receipt
were restored and the claim released. re_attempts.log records the trial and
corrects its initial mistaken description; it is not a verifier false reject.
Scratch evidence remains under build/ffactory-base-link-20261015. A native
cleanup-preserving deleting-body repair needs separate investigation.
