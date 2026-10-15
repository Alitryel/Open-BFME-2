Object544 vector destructor ownership repair, 2026-10-15

Base: 03496f402ce1b31d93475112a759dab98455ce17. Claimed the edited file
before changing it. No new authored C++ bytes, ledger entries, pins, aliases,
compiler flags, shared headers or verifier changes.

StlportObject544Vector.cpp explicitly instantiates the vector under /EHsc,
which also emits a 59-byte destructor (digest eaf068a8ce4d) proven wrong
against the existing retail owner. StlportVectorDtorFamily.cpp owns the
complete 63-byte /GX destructor at 0x004CAE89 and its 10-byte EH handler at
0x00790683. Both files pass strict preparation together: 54/54 matched rows.
The target element type remains a neutral 544-byte view; no original class
name or layout beyond existing evidence is inferred here.

Declare the vector destructor specialization before the class instantiation,
as already done by the target consumer
ModelConditionSoundSelectorClientBehaviorModuleDataDtor.cpp and other vector
units. The 59-byte competing body disappears with its two associative EH
sections and exactly its SafeSEH entry. The retained _M_fill_assign call still
references the same external destructor name, now undefined in this unit;
it can bind to the existing native owner. No import indirection is introduced.
All 88 retained COMDATs, every retained nondebug section's complete bytes,
flags, external definitions and symbolic relocations are unchanged. The
native owner's whole object and 370 COMDATs are unchanged. Data-reference
facts are identical. proof.py asserts these properties, including associative
section ownership, unchanged undefined references except the destructor,
strict reusable receipts, no added variants and paired link findings.

Measurement: frozen census ac77c85054, 2026-10-15 14:25; exact index hash is
in object-proof.json. Both sides refresh the same two strict-current objects
in memory against that index. The wrapper loses its only finding (wrong
COMDAT) and becomes locally clean: 0 -> 473 existing nonpadding matched bytes.
The owner's unrelated unresolved/COMDAT/selection findings are identical.
The current target consumer already has the declaration-only specialization;
its older wrong copy in the index is stale and was not edited or counted as
an improvement. Self-strict object currency is verified. Dependency closure
remains legacy; closed-strict, actual executable placement and runtime gains
are unmeasured. No index, link_status or history is changed.

Acceptance: before/after bounded prepare-current covers 54/54 rows across the
two sources; ordinary ./build.sh passes all 10 edited-source rows. Local
link_check passes 1/1 and reports +473 legacy linked bytes. EH: 1/1 EXACT,
zero missing objects. String/float/import checks have no skipped references.
Enforced data check has zero findings; converged-data check covers eight
addresses with zero second names or unjudged rows. Frozen-definition, class,
CSV and whitespace checks pass. Placement resweep finds zero bodies and pins.
Normal commit/push hooks remain required.

Donor review: clean BFME1 gitlink/checkout a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed c1315665a1b22beb7e6d9279548fe5b1c26ed1f9, which suppresses unused
DamageInfo constructor copies while preserving inlined callers. Its general
emission/ownership principle applies; its dllimport technique, class layout,
address and body are not imported. The direct declaration-only repair is
supported by BFME2's existing native owner and consumer. The overdue BFME1
old/new-input verification and pointer update remain under another live
file:reference/open-bfme-1 claim; no success stamp is written.

Discovery checked repair_queue.py link, link_rank.py help/top/near and blocker
kinds, current sources and earlier attempt evidence. link_check --fetch-index
kept the same local measurement and fetched published cached objects. No
missing/mismatched data-back artifact ranking was manufactured. Previously
deferred independent reconstruction blockers were not retried. Unrelated
reverse/zh_sweep preparation is preserved. No maintainer-only census build,
full link cycle, nightly, boot or scheduler runner was started.

Reproduction: ignored build/object544-vector-link-20261015/before holds the
original source/object/receipt snapshots under their original basenames;
context.json records the original paired preview and index identity. Apply
the source edit, prepare both explicit providers, then run the committed
proof.py from the repository root. object-proof.json preserves the result
and hashes when these local snapshots are unavailable.
