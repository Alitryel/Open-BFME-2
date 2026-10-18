# Production prerequisite size-helper repair, 2026-10-18

Two units emitted 12-byte vector<ProductionPrerequisite>::size copies that
conflict with the 25-byte retail owner at RVA 0x00626DF0 in ThingFactory.cpp.
Keep each caller's existing inline arithmetic, using the established MSVC
import/forceinline declaration form to suppress its out-of-line copy.

The paired bounded legacy preview refreshes the same two objects and the
unchanged current ThingFactory provider against index c2c5ac8c27 in both
phases. It moves 0/2 to 2/2 units, +592 existing authored bytes (386 + 206).
Other consumers still have independent selected-definition blockers and are
left for their own repairs. This is not closed-strict or census evidence.

Self-strict byte gate: 9/9 matched rows; literal/import checks pass. Strict
reusable receipts are current. Object comparison in proof.json proves all
25 retained COMDAT byte/relocation digests unchanged; each object removes
only the wrong size helper. Strong definitions, undefined symbols and weak
bindings are unchanged: no import reference is introduced. Frozen-source,
shadow data, converged-data and CSV checks pass; placement rescan finds zero
bodies or pins. No new row, pin or authored C++ coverage is claimed.

Original objects, source backups and reproducer remain in local
build/prereq-size-link-20261018/. The unrelated lower-bound helper trial was
restored and its blocker recorded separately in the attempt log.

Rebase reconciliation: upstream 5f1c587026 independently landed the same
size-helper repair in four units while this batch was unpublished. Keep
upstream's source spelling in both units. This directory records the original
pre-rebase experiment only; its +592 B is not an incremental gain over the
rebased origin/master. The source/object hashes in proof.json identify the
historical trial, not the final upstream source. No source change from this
trial remains after rebase.
