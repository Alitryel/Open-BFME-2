# Wide string zeroing constructor link repair

Base bf792a84b9a3d8e0490e0522164fef7903e3a148. Frozen index a2839ea429,
2026-10-15 13:35; underlying census 5986a99448. proof.json records the exact
index hash, object hashes, measurement metadata and paired local findings.

The wide c-string constructor and wide range/collation unit each emitted an
unused 15-byte `_String_base` zeroing constructor and its 11-byte allocator
proxy constructor. The zeroing constructor differs from the kept copy; the
index has no retail verdict for this wide name. This repair makes no new
identity, address, layout or canonical-provider claim for that helper.

Mark the existing fully inlined base constructor imported forceinline, as in
BFME 2's verified narrow sibling stlport_narrow_string_cstr_ctor.cpp and BFME 1
66b19a8e95a4add525ef808fcea088e306798e2b. Reviewed donor repair
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 uses the same unused-copy suppression
technique. The technique is inherited; target byte and object comparisons
independently establish that retained behavior and bindings are unchanged.
No flags, class layouts, headers, pins, ledger rows or baselines change.

Both files were claimed and passed the declared-definition check before editing.
The original three matched target bodies retain their existing identities and
layout evidence; donor addresses and layouts are not transferred here.

## Acceptance

- build.sh: 3/3 matched rows, string/float/import reference checks pass.
- Bounded link_check --prepare-current before and after: 3/3 exact, both sources
  have strict reusable receipts. This is byte validity, not executable placement.
- proof.py: all four retained range/collation COMDATs and all three retained
  c-string COMDATs preserve bytes, extent and normalized relocation digests.
  Only the two unused constructor COMDATs disappear from each object. All other
  nondebug sections, normalized relocations and linker directives are unchanged.
  Neither removed section has an incoming relocation from retained nondebug
  code/data. External bindings lose just those definitions, with no added import.
- Deep copies of the same frozen index, refreshed with exactly the two before
  or after objects, reduce each consumer's legacy findings from three to two:
  six to four total. Ordinary link_check agrees on remaining blockers. Both
  units still predict zero linked bytes; this is verified link-debt reduction,
  with zero new authored bytes and no self-strict or closed-strict gain claimed.
- EH verifier: 2 EXACT, none nonexact or missing. Enforced data and converged
  data checks, class gate, frozen-file check, new-variant check pass. Placement
  rescan: zero bodies, zero pins. CSV and whitespace checks pass.

proof.py requires the ignored build/wide-constructors-link-20261015 snapshots;
proof.json preserves this session's result, not a portable standalone test.
The census index, link status and history were not changed. No full census,
link cycle, nightly, boot or scheduler operation ran.

## Sweep and handoff

sweep.json records the frozen index's 17 emitters of this wide base constructor.
Only these two units carry the removed 443225058d4a digest. Other indexed
variants are leads, not newly verified current inputs or further repair claims.
The range/collation unit still has a competing basic_string destructor and a
wrong selected _String_base destructor. The c-string unit still has a competing
rowed constructor and the same destructor-selection blocker. The previously
recorded wide-string cleanup/name mismatch needs independent reconciliation;
no aliases or import-EH workaround were introduced.

Two independent trials were restored and logged blocked: the window collector's
CriticalSectionLock destructor differs from its native provider and is referenced
by EH cleanup; suppressing the iterator _M_getc copy changes nested sgetc
inlining, while explicit imported member instantiation fails MSVC linkage.
Their claims were released. These are separate codegen/dependency blockers,
not a reason to repeat unchanged trials.

Official BFME 1 master fetched at 95eeb3bef370a7cd730b0ad5f228c317c8756e72;
the clean verified gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Another worker holds file:reference/open-bfme-1 and attempt 53899 records the
old-input full baseline rebuild blocker. Verified inputs were preserved and
no successful freshness stamp or pointer advancement was made.
