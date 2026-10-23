# Object launch math-wrapper link repair

Source base a86a7d7960357b724515b2b80388ed67a5be39ec. Supplied local census
index measures cb660e4d97, 2026-10-13 04:02 UTC. Committed link_status.csv
measures 67e1365aa9 and supplied discovery only. Neither measurement, index
nor status was modified; no per-row data-back artifact or ranking was used.

ObjectRva00291A8C.cpp emits surplus MSVC math.h float wrappers while its
existing launch body inlines their operations. Apply the verified sibling
FloatUpdateUpdate/W3DLaserDrawBfmeDoDraw pattern: keep the original math.h
definitions, with static inline linkage only during that include. No identity,
layout, compiler setting, pin, alias, global or ledger row is changed.

Strict preparation initially refused the two unusual ../../Code/ includes:
they found the real headers through another search root, outside the
inventoried roots. Correct both paths to direct relative anchors resolving to
the same Coord3D.h and GameLogicObjectLookupView.h recorded in the original
compiler dependency receipt. This is a source-input repair, not a verifier
change. The original and anchored objects have identical definition bytes,
extents, relocations, verdicts, strong definitions, undefined externals and
weak bindings. Anchored preparation then passes with reusable strict receipts.

Target evidence in object-proof.json binds source/object hashes and records:

- Exactly four external copies removed: cos(float), sin(float), cosf, sinf.
- All 16 retained copies unchanged in full bytes, extents, relocation tuples,
  digests and retail verdicts; no added copy.
- Strong definitions, undefined externals and weak bindings unchanged. Every
  compiled consumer in this unit keeps its external bindings. Other units and
  the retained math providers were not edited.

Full snapshots, original source/object/dependency backups, strict receipts and
the comparison script remain in build/object-math-link-20261014. Include-only
and final self-strict preparation both pass 7/7 matched rows. Final ./build.sh
passes 7/7 whole rows (510 non-padding retail bytes), two compiler float
literals and zero skipped/baselined references. EH verification finds no EH
rows. New-variants admission, class gate, declared-definition check, CSV and
whitespace checks pass. Enforced converged-data verification finds zero second
names/unjudged rows at eight addresses; shadow data has zero findings.
The code-identity shadow check reports the same six duplicate definitions and
two unowned callee bindings listed below; retained object facts are unchanged.
Affected-unit placement resweep reports zero bodies and zero pins.

Identical legacy local link preview: 10 findings before, 8 after, precisely
removing the cos(float) and sin(float) losing-copy findings. No new blocker.
The unit remains 0/1 clean and LINKED 0 -> 0. This is a verified repair of
four surplus providers and two link blockers with +0 authored C++ bytes.
Self-strict verification is established; closed-strict closure, executable
placement and a refreshed census gain remain unmeasured. No full census,
link cycle, nightly, boot or scheduler operation was started.

Remaining preview findings are six duplicate Object status helpers in
ObjectScriptStatus.cpp, unresolved consume@Rva003909FAObj and unresolved
Object::setDisabledUntil. These require separate bounded provider repairs;
the latter's existing deferred reconstruction was not retried.

Donor review retains clean verified BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed upstream linking commit
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppressing surplus copies is
applicable as a principle; its string constructor/alias mechanism is
inapplicable. Current donor repair scan also found part_ldr Convert_To_Ver2
already removed locally. No donor code, name or layout was imported.

Official BFME1 master was fetched at
262d3e9507d68409d7cf86e730f4c75eefa58ccd. The due pointer update still
requires comparative full-byte verification against the retained inputs;
that pre-existing audit is outstanding. Verified checkout/gitlink and the
old success stamp were preserved; no successful freshness update is claimed.

Queue discovery found several already repaired top-ranked blockers, including
the animation pivot getter, Quaternion::Rotate_Vector helper and shrub/tree
StringBase callers. Their current-source/local checks were used to avoid
repeating stale census work. A read-only name_globals probe on
Rva004FA738ListenerWalks.cpp reports zero changes. Unchanged deferred
PlayerList and heartbeat repairs were left deferred.
