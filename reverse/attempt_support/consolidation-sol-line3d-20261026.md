# Line3D compiler-context prerequisite, 2026-10-26 (codexb)

Allocated family B, shard 0/2; `consolidation_queue.py --check-tu
Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp` authorized the destination.
The WW3D2 naming planner's original-path evidence, alternatives and blockers
were reviewed. No merge or ledger move was applied.

## Demonstrated unblock

The ordinary `tu_skeleton.py --merge ... --dry-run` initially accepted the
seed and RenderObjClassDerivedDtors: eight rows in two files. The endpoint
constructor's private class lacked the copy-constructor and assignment
declarations implemented by the seed. Adding those two existing signatures
makes the constructor donor compatible: eleven rows in three files, including
the endpoint body's 621 bytes and its two EH rows. The renderer donor remains
rejected and has not been changed. This is a prerequisite for Luna, not a
confirmed downstream merge or new byte coverage.

Declaration-only composition passed the eleven function rows but failed the
provider audit. It changed four shared helpers (RefCountClass destructor,
deleting destructor, Delete_This and the vector constructor iterator) and
added seven math providers. A byte-only trial was therefore not publishable.
Rechecking after upstream e633ca36a9's include-order fix still reproduced all
four changed and seven added providers: its preservation of declarations
between includes does not keep the anchor function ahead of the includes.

Line3DCompileView.h groups the three donors' existing, identical constructor
iterator anchor and size-optimized RefCount inclusion. The include remains
atomic during composition. The seed also loads the endpoint donor's existing
inline-only Vector3 and Matrix3D views before its full math headers. No new
optimization setting or alias is introduced. `hatch_counters.py --update`
transfers four existing pragma occurrences to the header and removes eight
duplicate occurrences (2159 -> 2151 repository total at verification).
Existing opaque destructor identities, pins and baseline keys are preserved.

## Acceptance evidence

The following scoped checks passed:

- `link_check.py --prepare-current` for line3d.cpp, Line3DClassCtor.cpp,
  RenderObjClassDerivedDtors.cpp and unchanged Line3DClassRender.cpp:
  25/25 rows, fourteen float literals, five EH funclet locations and four
  strict reusable current-object receipts. This does not assert link closure.
- `find_declared_unmatched.py` for the three edited sources: no frozen body.
- `data_check.py --staged`: three sources, zero findings.
- `code_identity_gate.py --staged`: eleven rows, zero new findings.
- `header_dependents.py --staged`: the three edited sources plus the
  conservative macro-include consumer Eva.cpp. Eva also passes 27/27 rows,
  ten strings, five empty strings and five floating literals.

Before editing, the four standalone objects were copied and indexed with
their source/object SHA256 in build/sol-line3d-before-20261026.json. The
provider comparison uses allowed_symbols.Obj and the census's COMDAT-selection
reader; it compares every external defined symbol's body, relocation targets,
section flags and selection. Local relocation normalization is limited to
verified EH-handler names. Every standalone provider and undefined reference
is unchanged, including both native Line3D tables. The accepted composition
has no missing, added or changed external provider and no new undefined
reference. Its only removed undefined reference is Clone, satisfied by the
equal admitted seed provider. There are no pre-existing multi-variant names
in this scoped provider union. The constructor and Clone EH graphs are EXACT,
with the native funclet locations 0x00767520 and 0x00767500 respectively.
Thus the selected provider candidates and affected bindings are preserved,
not merely the ledger-row bytes. Scratch receipts and the comparison script
are under build/sol-line3d-{before,context,final,upstream}-*20261026*.

No relevant source keys occur in code_identity_baseline.tsv,
data_check_baseline.txt, header_queue.tsv or ms_header_queue.tsv. Nothing was
retired from the identity/data/header registers; all surviving debt stays
owned by its existing source. Header queue currency is checked through the
owning audit, rather than a scoped write that would truncate the global queue.

## Remaining prerequisites and batch audit

Line3DClassRender.cpp still selects an opaque RenderObjClass view with 98
virtual slots and no Clone/copy/assignment declarations. The seed and endpoint
use the established full render-object view. Appending a guessed virtual or
silently choosing the opaque view would not prove BFME 2's ABI. Leave that
donor for a separate full-view reconciliation. Mixed Common donors are outside
this seat's family and remain untouched.

No source path or ledger ownership changes in this prerequisite. The complete
pending batch also adds the two NetCommandList headers from the recovery
commit. Active tools, hooks, workflows, source/header includes, build inputs
and registries were searched for all affected basenames/paths. New header
references resolve locally; unchanged TU-map and census mentions still name
their existing sources. No consumers require repointing, historical EA paths
are preserved, and no TU map is regenerated. The audit covers the pending
NetCommandList commit plus this prerequisite; any later source move needs a
new audit. No maintainer-only link/smoke/nightly runner was invoked.

Measured result: one more donor and three more rows accepted by dry-run;
zero source files removed, zero identity keys retired, zero recovered C++ or
linked bytes claimed. Retain file claims for the three edited sources, new
header and this handoff while publication is pending; release after the
runner confirms the push. NetCommandList's pending claims are listed in its
separate recovery handoff.
