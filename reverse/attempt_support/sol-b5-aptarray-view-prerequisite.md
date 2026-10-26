# AptArray value-view composition prerequisite (codexb5, 2026-10-26)

## Scope and demonstrated result

Allocated family-B shard-1/2 target: `Code/Libraries/Source/Apt/AptArray.cpp`.
The runner queue lists this destination, not HELD. File claims cover the seed
and `AptObject/AptArrayConstructor_Unresolved.cpp`; the latter remains unchanged.
Common donors were inspected and verified but not edited or claimed for changes.
No merge, split, ledger repoint, identity retirement or recovered body is claimed.

Normal `python3 tools/tu_skeleton.py --merge
Code/Libraries/Source/Apt/AptArray.cpp --dry-run` before this repair accepted the
seed, constructor donor and `Common/Rva008B8B80ReleaseAll.cpp`: 14 rows.
After the repair it additionally accepts `Common/Rva006D94A0Cluster.cpp`
(reverse-array body at RVA 0x006DA130, 104 bytes): 15 rows. This is a demonstrated
prerequisite unblock for Luna, not a confirmed downstream merge or linked-byte gain.

## Target facts and change

The seed comparator calls the existing key builder through
`BfmeAptValue006DCD20`. The reverse-array donor requires the same private view's
array predicates and storage (+0x20 data, +0x24 capacity, +0x28 length), already
used by the rowed array helpers. The seed now retains both declaration sets.
The existing slot-1 release declaration follows the clear-array donor; these
are private target views, not a new canonical class or a donor-source claim.
The comparator's C linkage is expressed by a declaration followed by its ordinary
C++ definition. This prevents composition from classifying its entire definition
as an early extern-C declaration before the complete value view is available.
No flags, pins, alternatenames, symbol names, data definitions or layouts used by
an emitted standalone body change.

## Verification and provider/consumer evidence

* `./build.sh` seed, constructor, Common cleanup, Common clear and Common reverse:
  16/16 exact before repair. Final seed rebuild: 10/10 exact; eight strings and
  three renumbered funclets verified. Other four objects/sources are unchanged.
* `find_declared_unmatched.py` seed and constructor: all definitions matched
  (constructor's existing three admitted inline definitions remain unchanged).
* Scoped before/after receipt (`build/sol-b5-aptarray-view-proof.py`) uses
  `allowed_symbols.load/scan`, its object definition facts, `link_census` COMDAT
  selections and `data_check.object_facts`, reading existing build objects only.
  All 16 row receipts, 30 classified references (7 aliases, 20 owners, 3 EH),
  definition/undefined sets, selection flags and data facts are equal. Only
  verified local EH label numbers are normalized.
* Scoped capture (`build/sol-b5-aptarray-view-composition.py`) delegates to normal
  `tu_skeleton.merge(dry_run=True)` and captures its accepted object. All 15
  accepted rows match; 14 standalone code definitions survive unchanged; no
  dropped definition or new undefined symbol.
* Composition bindings and selection comparisons use upstream allowed-symbol,
  COFF and census helpers: 28 before/after references, no added/removed binding,
  no divergent duplicate copy; 14 inspected definitions, no selected-provider
  change, equal data binding sets and definition sets. Comparison includes the
  constructor and cleanup consumers, the comparator and newly accepted reverse.
* Final normal dry-run independently confirms the four accepted sources above.
* `data_check.py` scoped five sources, `--converged` seed, `class_gate.py` seed,
  `eh_verify.py` seed, `check_csv.py` and `git diff --check`: all pass (data shadow: five sources, zero findings; converged: ten addresses, zero second names/unjudged; EH: two EXACT).

Planner: `name_lane.py consolidate --under Code/Libraries/Source/Apt/` and its
AptArray group were reviewed (original-path evidence, duplicate classes, mixed
routing, flag overrides, private declarations). Current routing is rebuilt in
memory by the merge tool. No regenerated TU map is committed.

## Remaining prerequisites and audit

Clear-array donor still refuses: allocator declaration ordering, then likely its
private AptArray view versus the canonical-base constructor view. The value
string helper still refuses because `Rva006D6470Owner` is not defined before its
derived view. `Rva006D9780Finish.cpp` still has an uncarried flag override. Mixed
AptArrayConstructor/AptValueArrayAt/Common cluster donors need the supported split
lane and their own owners' claims; no manual carve or cross-family edit was made.
Leave the newly accepted reverse donor for Luna.

No source paths change in this prerequisite batch (including the staged move
set, which is empty), so no active include/tool/hook/workflow/build/registry
consumer requires repointing. Existing original EA path strings and protected
registers are preserved. Existing seed ms-header queue entry remains. No code
identity or data key is dropped or retired. Pending-path audit is recorded with
publication below. File reduction 0; retired identity debt 0; new C++ bytes 0.

Pre-publication audit: after pull/rebase to bf438b551c, `git diff --name-status
--find-renames origin/master..HEAD` is empty. The only pending source edit is
the existing AptArray.cpp; there are no old/new source paths to repoint.
Registers, includes and build inputs retain their owners. Snow trial source
edits are fully restored; its companion commit records evidence only.
Claims remain held until confirmed publication; release the seed and unchanged
constructor file claims after landing if the shared publisher defers this batch.
