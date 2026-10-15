# ReflectDamage constructor-wrapper link repair

Base: 4043d6628a. Frozen runner index: update 19a2565407, 2026-10-15
09:33, based on census 5986a99448 at 04:52. The committed status CSV is a
different measurement and served only discovery. proof.json records the index
hash, source and object hashes, exact removed wrapper, and paired findings.

ReflectDamageOnDamage.cpp emitted an unused 12-byte external
`DamageInfo::DamageInfo()` wrapper. It loses COMDAT selection and makes the
unit touch a selected definition proven wrong. Its matched 137-byte callback
already inlines the wrapper and calls the native member constructor at
0x00263895. Mark the inline wrapper imported and force-inline to suppress its
external copy. No import reference, alias, pin, class layout, compiler flag,
ledger row, or shared header changes. The file was claimed before editing.

## Evidence and donor review

The existing source documents target identity via damage-interface vtable
RVA 0x00859CB0, callback 0x004BABFA, native field accesses, and constructor
0x00263895. This change establishes no new target identity or layout. Native
callback bytes and every relocation remain exact; the unchanged provider is
Rva00263895Init.cpp, with its own 45-byte matched body.

Reviewed BFME 1 repair c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 at
upstream 86d49b09744d9dfb7896d0d1b6e621d3536f30d2. Its suppression technique
is applicable: retain inlined construction while removing an unused competing
constructor. Its 102-byte private constructors and native BFME 1 constructor
address are not imported. BFME 2's 12-byte wrapper, member-constructor call,
and object-level comparison independently establish this repair.

## Acceptance

- ./build.sh passes the callback, 1/1, including reference gates. Bounded
  --prepare-current verifies caller and provider before and after, 2/2 with
  strict reusable receipts. The provider object is byte-for-byte unchanged.
- proof.py compares saved before objects with current objects. All three
  retained COMDATs have identical bytes, extents, and relocation digests.
  All retained nondebug sections and normalized relocations are identical;
  only the unused wrapper section disappears. Directives are identical.
  No retained code/data references that wrapper. The only external-binding
  difference is removal of its definition; no __imp binding is introduced.
- Paired previews deep-copy the same frozen index and replace only these two
  explicitly prepared objects. Caller legacy findings fall 2 -> 0 (one COMDAT
  loser, one wrong-selected name); provider findings remain 0 -> 0. Existing
  caller LINKED authored bytes are 0 -> 137, provider remains LINKS at 45.
  Ordinary local link_check agrees: both units LINKS, total 45 -> 182 bytes.
- Class, declared-definition, data, converged-data, new-variant admission,
  CSV and whitespace checks pass. EH verification has zero applicable rows,
  zero missing objects, and zero nonexact rows. Placement resweep finds zero
  additional bodies and zero pins.

This is a local legacy link prediction with strict-current compiler inputs.
It adds zero authored C++ bytes. No self-strict executable-placement gain,
closed-strict gain, census measurement, or runtime result is claimed. The index,
status CSV, and measurement history are unchanged. Full link cycles, census
rebuilds, nightlies and boot/scheduler checks were not run.

proof.py replays the object checks using ignored snapshots in
build/reflect-damage-link-20261015 and the unchanged frozen index; proof.json
preserves the result. It is evidence, not a portable acceptance gate.

## Sweep and handoff

sweep.json records all 15 indexed emitters of this constructor spelling. The
remaining 14 use header-based Zero Hour definitions rather than the local
wrapper repaired here. Each has 10–70 independent findings in the frozen index;
none is asserted to link after this repair. Reconciling those shared DamageInfo
headers requires separate layout/caller checks and a full dependency gate.
No unchanged setDisabledUntil or string-lookup codegen blocker was retried.

Official BFME 1 master was fetched at 86d49b09744d9dfb7896d0d1b6e621d3536f30d2.
The clean verified gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Another worker holds file:reference/open-bfme-1; the overdue comparative update
still depends on the old-input full baseline rebuild recorded in attempt 53899.
No pointer advancement or successful freshness stamp was made. The index fetch
kept the newer local runner index and restored published objects to the store.

Model: gpt-6.1-sol.
