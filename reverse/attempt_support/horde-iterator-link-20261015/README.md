# Horde upgrade-mask iterator repair, 2026-10-15

At BFME2 base `2d0869b7a22ceece2b7be98d0561733bb3177b61`, make the
list/tree typed node comparisons local in HordeContainApplyUpgradeMask.cpp.
This follows existing BFME2 consumers (InGameUI.cpp and NetPacket.cpp) and
preserves STLport's node comparison semantics. The unit's /G7 build otherwise
emits two incompatible external base-iterator comparisons. No matched body,
ABI, global, compiler setting, ledger row or retail extent changes.

## Controlled result

Both phases use the exact index identified by context.json: update commit
`19a2565407`, census commit `5986a99448`, SHA-256
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
The baseline object was saved after strict byte preparation with the original
source and current dependencies, rather than read from an obsolete cache.
link-proof.py refreshes each phase separately in copies of that same index.
The only findings removed are:

- `_STL::_List_iterator_base::operator!=`: not retail's body.
- `_STL::_Rb_tree_base_iterator::operator!=`: differs from selected copy.

The consumer changes from two findings to zero, **0 -> 411 existing matched
bytes link-clean in the legacy local preview**. These are the 401-byte parent
at RVA 0x00472444 and its 10-byte compiler EH handler; the 34-byte gen-alias
is excluded from this preview's byte count. New authored matched bytes: zero.
This does not establish self-strict placement, closed-strict gains, a fresh
census or full executable linkage. Strict byte receipts establish current
provider identity only. Index/status were not rewritten. Maintainer-only
broader verification remains outstanding.

object-proof.json establishes that all 49 retained COMDATs have identical
bytes and relocation digests. Exactly two unreferenced 18-byte external
comparisons disappear, replaced by two unreferenced 12-byte static comparisons.
There are no added external bindings or imports, no nondebug references to any
of those four helpers, and no other normalized section/directive changes.
Automatic COFF label numbering and section indices are normalized by their
actual targets. The evidence does not infer a new game identity or layout.

The commit hook also reports four code-identity findings in shadow mode: the
upgrade-vector push_back binding at 0x004DFCB0, and divergent Object-pointer
list iterator construction/begin/end definitions. identity-proof.py runs the
upstream identity checker against the genuine saved baseline and repaired
objects without replacing shared compiled objects. identity-proof.json proves
all four diagnostics are identical before and after; this repair does not
resolve that existing identity debt. The ordinary local preview does not
measure those shadow findings.

## Acceptance

- Original and repaired strict byte preparation: 3/3 matched; one complete
  STLport constructor fold verified against its retail owners and callees.
- `./build.sh` consumer: 3/3 matched; string/float/import reference checks pass.
- `link_check.py` consumer: LINKS, legacy preview 0 -> 411 bytes.
- `link_check.py --new-variants` consumer: passes.
- `eh_verify.py` consumer: 1/1 EXACT, zero baselined/missing objects.
- `data_check.py --enforce`: zero findings; `--converged`: eight addresses,
  zero second names or unjudged rows.
- `find_declared_unmatched.py`, `class_gate.py`, `git diff --check`: pass.
- `place_bodies.py` consumer: zero additional bodies or pins.

The proof scripts run from repository root and use saved genuine baseline
objects/receipts in build/horde-iterator-link-20261015. Published JSON preserves
the comparison and hashes; binary scratch artifacts are not committed.

## Sweep and remaining leads

Started with `repair_queue.py link` and `link_rank.py`; fetched the published
object store with `link_check.py --fetch-index`, which retained the newer local
index. Current local checks show ChatWindowsOnlineBuddy.cpp,
RTS3DSceneFlushOccludedObjectsIntoStencil.cpp, CostModifierUpgradeModuleDataDtor.cpp,
PodVectorElementDtorTwins.cpp and Rva0059D7C4ArmyTally.cpp already link-clean;
the older status queue still serves them. No changes made to those files.
EvaRva001DDF04.cpp has the same comparison lead but another worker owns its
file claim. W3DFXParticleSystem.cpp additionally needs the unresolved global
`?g_bfmeVal991@@3HA`; GiantBirdAIUpdate.cpp additionally needs
`?consume@Rva003909FAObj@@QAEXPAXHH@Z`. Neither has been edited or claimed.
The two audio false rejects from tree-iterator-wave2-link-20261015 remain
deferred; they were not retried.

## Donor review and freshness

Reviewed BFME1 linking repairs `63e68aaa567add9eb42a79913d23eece6a19ceee`
and `de59a7e9f891b3ed2d4221d151ca881f4b75a583`: reuse/ownership of library
helpers is applicable; the latter unifies Apt predicate definitions. No donor
ABI, addresses or code bodies are imported; the directly applicable recipes
already exist in BFME2. Official BFME1 master was fetched during this session;
its fetched tip is `e27a65cb6bd7b2b3cc8ee320ef7ef8a3797b1d0e`. The clean
submodule stays at `a7c38d3b2597121f178ab5190b3062478823257d`.
Another worker holds file:reference/open-bfme-1. The previous full old/new
comparison remains blocked on stale/missing dependency inputs and a stalled
MSVC baseline, as recorded in earlier session evidence and
build/reference-update-blocker.txt. Did not repeat that unchanged blocker,
advance the pointer or mark the freshness timestamp successful.
