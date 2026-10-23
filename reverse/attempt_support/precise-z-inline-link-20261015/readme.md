# Locomotor precise-Z inline-emitter link repair

Base tree: 058a2e5da385284b23daa343145b2e3b682311fc.
Measurement: legacy census 28269d8e8d, 2026-10-15 09:31 UTC.
Index SHA256: 6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.

## Change and target evidence

The five consumers in sources.txt emitted the same unused 20-byte
?setUsePreciseZPos@Locomotor@@QAEX_N@Z body (digest 0bd2992e4971).
It lost to the first copy in this census (JetAIUpdate, c38056c85db8).
The helper has no proven retail address: this repair makes no name, layout,
or retail-identity claim for its standalone COMDAT or the winning copy.

The existing source expresses bit 3 of its private Locomotor flag word at
+0x44. Its inlined updates in the retained matched callers remain byte-exact.
Mark the method __declspec(dllimport) __forceinline to preserve these updates
without emitting the unused competing outline. There is no new imported call,
external or weak binding and no incoming nondebug relocation to the removed
section. No flags, private layouts, headers, pins, data names or ledgers change.

## Donor review

Verified BFME1 pointer: a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed linking repairs d3f9000fe08615a100e844adfff57fa4a39cd615
(TileData ctor), c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
(DamageInfo ctor) and fetched 66b19a8e95a4add525ef808fcea088e306798e2b
(Apt allocation helpers). Suppressing unused outlines with imported inline
methods is applicable; their types, addresses, layouts and link gains are not
inherited. Existing BFME2 inline-emitter evidence and the repaired sibling
AIAttackApproachTargetStateOnExit.cpp support testing this technique here.

Freshness update remains blocked by the live foreign claim on
file:reference/open-bfme-1 (codex-6bc6-20261008). Official master was fetched
at 86d49b09744d9dfb7896d0d1b6e621d3536f30d2; preserve the verified clean
checkout/gitlink. No successful freshness stamp was written.

## Verification and measured improvement

Before and after, link_check.py --prepare-current byte-verified all five
explicit owned sources with strict reusable receipts (31 + 1 + 29 rows).
Final ./build.sh: 61/61 matched; 57 string literals, 39 float literals,
0 named imports; no skipped/baselined string checks. EH: 5/5 EXACT.
Frozen-file and class checks pass. Converged data check passes: 8 addresses,
0 second names, 0 unjudged. CSV passes. place_bodies.py: 0 bodies, 0 pins.

proof.py is the paired comparison used with ignored before-source/object/receipt
snapshots under build/precise-z-inline-link-20261015/before/. It performs only
in-memory refreshes against the unchanged measured index; it never publishes
or rewrites the census. For each old and new object it verifies:

- Exactly this helper COMDAT disappears; 342 retained COMDATs are identical.
- All retained nondebug section bytes, sizes, flags, symbolic relocations,
  external/weak definitions and data bindings are unchanged.
- No incoming nondebug relocation targets the removed helper.
- Current objects have strict current-input receipts; no new COMDAT variants.
- Five losing-helper findings disappear; all other legacy findings and the
  winning provider and existing-copy selection decisions are unchanged.

object-proof.json records object hashes, per-source findings, provider
selection and the exact index digest. To reproduce the paired test, compile the
five parent-revision sources and changed sources with identical dependencies,
retain the before objects/receipts under that scratch directory, and run the
script from the repository root with the recorded index. The stored JSON is
this session's result, not a new census receipt.

The ordinary local link check still reports 0/5 clean, LINKED 0 -> 0. Existing
unresolved callees, duplicate definitions and other conflicting private views
remain (listed in link-after.txt). The affected sources contain 18,675 existing
nonpadding row bytes. This repair removes five blockers, adds zero authored C++
bytes and claims zero legacy linked-byte gain. Self-strict receipts are current;
closed-strict closure/gains are unmeasured. No full link cycle, census run,
nightly or boot runner was started.

Data enforcement reports three unchanged wrong-name findings, one outside its
baseline: the OnEnter static counter at 0x00A01DF4 named
?$S1@?N@??update@AIAttackMeleeHordeWaitPathState@@UAE?AW4StateReturnType@@XZ@4IA.
The other two are g_00DFEFF0 bindings at 0x009FEFF0. All three exist in the
before objects; proof.py asserts exact data-fact equality. The data check is in
shadow mode under AGENTS.md; its optional --enforce probe exits 1 for the
pre-existing unbaselined finding. No baseline was edited. Correcting those
names and the remaining link blockers is separate work.
