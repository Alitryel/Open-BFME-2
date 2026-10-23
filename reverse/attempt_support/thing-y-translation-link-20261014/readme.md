# Thing::setPosition surplus matrix setter repair

Base: `46b43b5293f85b585ad1eb052ddcd00e1e823ab0`.
Legacy prediction index: commit `147cfae2cb`, dated 2026-10-14 07:27,
SHA-256 `690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
The index and committed census/status were not changed by this repair.

## Change and target evidence

`ThingSetPosition.cpp` previously emitted a 14-byte
`Matrix3D::Set_Y_Translation` COMDAT that the census judges wrong. This was
the consumer's sole remaining local link finding. The established provider,
`Thing.cpp`, emits the 10-byte retail setter (owner RVA `0x00665600`, alias
`0x00318B09`). No provider definition or alias was changed.

Use the public row accessor to assign `m_transform[1].W`. The existing header
defines the setter as `Row[1][3] = y`; `W` is the fourth vector component.
The complete 285-byte `Thing::setPosition` body at `0x0030AA80` still matches
retail. The only removed consumer COMDAT is the wrong setter. The only added
one is the 12-byte matrix accessor, identical to all 21 existing census copies,
each classified retail. All nine retained consumer COMDATs have unchanged
bytes, relocations, digests and retail verdicts. Ordinary nondebug sections
and relocations are unchanged. The provider object is byte-identical.
`object-proof.json` records these comparisons and resolved matrix headers.

The index identifies this consumer as the only losing/selected-wrong/unresolved
consumer of this setter; no other affected consumer was found in that sweep.
Claims covered both source files during inspection and verification.

## Acceptance and limits

- `link_check.py --prepare-current` for consumer and provider passed before
  and after: 11/11 matched rows, strict reusable receipts for both objects,
  no skipped/baselined string or import checks. This establishes self-strict
  current objects, not a closed-strict link closure.
- `./build.sh Code/GameEngine/Source/Common/Thing/ThingSetPosition.cpp` passed
  1/1, including reference checks.
- The paired legacy `link_check.py` changed the consumer from one finding to
  `LINKS`, predicting linked bytes **0 -> 284**. The command still exits 1
  because the provider's nine independent findings remain unchanged; see
  `link-after.txt` for their names. These include the STL out-of-range import,
  kind-of helpers, bitset helpers and array constructor machinery.
- `link_check.py --new-variants --staged-peers` passed for the consumer.
- `find_declared_unmatched.py`, `class_gate.py`, converged-data validation,
  shadow data checks, `eh_verify.py`, `check_csv.py` and `git diff --check`
  passed. EH checks found no EH rows in these units.
- `place_bodies.py` found no additional bodies or pins to admit.

No new authored C++ bytes are claimed. No closed-strict or measured census
gain is claimed. Full link measurement remains for the authorized runner.

## Donor review and reference freshness

Reviewed BFME 1 repair `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`, which
removes surplus local constructor bodies. Its general COMDAT suppression
approach applies; its types, layouts and aliases were not imported here.
The earlier BFME 2 matrix-copy repair is recorded in
`../bone-fetch-matrix-link-20261013/readme.md`; this repair addresses its
remaining setter blocker.

The verified BFME 1 gitlink remains
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. This session fetched official
master `a7c38d3b2597121f178ab5190b3062478823257d`; the intervening changes
affect Apt string-transform work and attempt records, with no WWMath changes.
The overdue pointer update is still blocked on the previously recorded full
old-input verification (thousands of stale units), documented in
`../unicode-comparator-link-20261014/readme.md`. The verified pointer and
freshness stamp were preserved; no successful freshness check is claimed.

The comparison scratch and executable proof remain under ignored
`build/thing-y-link-20261014/`. The tracked logs and object-proof report are
the durable evidence for this repair.
