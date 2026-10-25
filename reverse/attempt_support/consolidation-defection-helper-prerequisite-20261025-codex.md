# ObjectDefectionHelper receiver prerequisite — 2026-10-25, codex

Target `Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelper.cpp` is allocated to codex by the runner's family A shard 0/2 queue. Current `tu_skeleton.py --plan` approves all three donors, three parent rows (six rows including EH), with no mixed or protected source. Planner original-path alternatives and prerequisites were reviewed; routing was rebuilt in memory, not committed.

## Demonstrated unblock

Before, `tu_skeleton.py --merge <target> --dry-run` exits 2 and accepts no donor. The timer donor's private base variants leave ObjectHelper undefined after composition; the Xfer donor's hoisted include precedes Snapshot and other operand declarations.

A scoped `ObjectDefectionHelperView.h` now shares the seed's accessed receiver hierarchy and tail among these three consumers. It adds declarations for the already matched timer, xfer and setWakeFrame methods. Xfer keeps its protected access and the timer keeps its native primary receiver. Required Xfer operand forward declarations travel with its include. The timer and Xfer bodies use the field names already carried by the seed's ZH-backed source; the timer uses the existing inline object/status accessors. No new function identity, complete-class recovery, or external donor-as-BFME-source claim is made.

After, the same supported dry-run exits 0, accepts the seed, startDefectionTimer and Xfer, verifies all six ledger rows, and rejects nothing. Leave the now-compatible donors for Luna. This prerequisite adds one scoped header, removes zero source files, retires zero debt keys and recovers zero C++ bytes. A later merge could absorb the two donor cpp files; no downstream landing is claimed here.

## Verification and binding evidence

`./build.sh` all three consumers passes 6/6 before and after, four float references, no string or import failures. Both compiler funclets are located through the exact parent EH data despite label renumbering. `find_declared_unmatched.py` passes all three. `link_check.py --new-variants --staged-peers --paths-from build/codex-defection-sources.txt` exits 0. `data_check.py` reports zero findings. The plain identity scan reports zero wrong bindings; its count excludes two stale-label funclet references, which the EH-aware comparison covers below.

Saved before sources and objects are under `build/codex-defection-before-{files,objects}/`. Read-only supported object, COMDAT-selection and row-reference APIs show:

- All ten existing external code definitions retain their bytes, sizes, relocation digests and exclusivity; undefined references and linker aliases are unchanged.
- The timer newly emits getObject (4 bytes) and getIsUndetectedDefector (12 bytes). Both are relocation-and-byte twins of the pre-existing seed definitions, with the same COMDAT selection 2 and section flags. Thus selecting either provider retains the same body; no competing variant is introduced.
- Every non-debug section in the seed and Xfer donor is unchanged after local compiler labels are normalized to section/offset. Timer section numbering changes because of the two added helper COMDATs; its existing functions and policies remain identical. External data definitions are identical in all three consumers.
- All 23 ledger reference sites, including both EH-located funclets, retain identical symbol/retail-target bindings. No consumer acquires a new binding.

No row is moved, no data or identity key is retired, and no source keyed in a protected register is deleted. The existing data finding for the separate ObjectDefectionHelperPoolKey source remains untouched. The scoped planner was regenerated after edits and its snapshot check passed before the final dry-run.

The first intermediate build caught xfer declared public rather than protected; correcting its declaration restored the existing mangled identity. No failing intermediate body remains. No gate was changed or bypassed.

Local receipts: `build/codex-defection-{before,after}.txt`, `*-build-{before,after}.txt`, `*-provider-proof.json`, `*-section-proof.json`, `*-eh-binding-proof.json`, `*-data.txt`, `*-link-variants.txt` and `*-code-identity.txt`.

## Publication audit and claims

Audited `origin/master..HEAD` at upstream bb7406fa12 (pending Recorder 85eecf1688, HeaderTemplate 2196aca8e0 and production-exit 69bbf5bce9), plus the staged three consumers, new scoped header and handoff. The clean rebase touched none of these consumers, their headers, AGENTS.md or docs/consolidation.md. `check_csv.py` and `git diff --check` pass, and the planner was refreshed after rebase. There are no source path deletions, renames or moves; this change adds one scoped header included only by its three verified consumers. Active tooling, hooks, workflows, includes, build inputs and registries keep existing paths. Preserve historical EA path strings. The prior production-exit commit hook also reports existing divergent definitions Vector3::operator*= and Object::getContain in shadow; its before/after object proof shows these were unchanged. They were not retired or baseline-admitted.

Keep file claims for the three ObjectDefectionHelper cpp files and ObjectDefectionHelperView.h until publication is confirmed. Earlier Recorder, HeaderTemplate and production-exit claims remain held while their commits are queued. Then release file/class scopes and settle landed RVA claims. No maintainer-only census, link, nightly or smoke run was started.
