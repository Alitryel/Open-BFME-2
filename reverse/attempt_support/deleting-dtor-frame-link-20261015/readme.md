# Shared deleting-destructor frame settings

At BFME2 `d27f9c0cd3e9d41ce136281fd2f95b0d078e41e6`, three units passed
their byte gates but emitted losing scalar deleting destructors. Their explicit
`/Oy-` added an EBP frame to each wrapper. The native wrappers, independently
rowed in their provider units, omit that frame. Removing only `/Oy-` makes each
31-byte wrapper a 28-byte whole-body and relocation twin of its provider:

| Consumer | Shared wrapper | Verified provider |
| --- | --- | --- |
| W3DViewAggregateDtor.cpp | Rva008BD5E | OpaqueScalarDeletingDtorsB09.cpp |
| BaseUpgradeModuleDataCtor.cpp | BaseUpgradeModuleData | FamilyDeletingDtors_muse-67c0.cpp |
| RiderChangeContainModuleDataCtor.cpp | RiderChangeContainModuleData | ContainModuleDeletingDtors.cpp |

The EH-bearing bodies retain their native frames under the default setting.
`proof.py` compares paired COFFs: every other nondebug section, relocation and
external binding is unchanged, including every recorded parent and associative
EH section. No symbol, pin, alias, class layout, code identity or lifetime
semantics changes. Hatch counts do not grow; BaseUpgrade's existing two
optimization pragmas remain unchanged.

## Acceptance and measurement

The downloaded index is measurement commit **a2839ea429**, 2026-10-15 13:35,
census **5986a99448**, 2026-10-15 04:52, SHA256
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
`object-proof.json` records before/after findings against that same index with
the six explicit consumer/provider objects refreshed in memory. The index and
tracked census/status artifacts are not modified.

- Before and after, `link_check.py --prepare-current` verifies **72/72 rows**
  across the six units and produces strict current reusable receipts.
- `eh_verify.py` reports **5/5 EXACT** parent EH graphs, no baseline exceptions.
- Byte, string, float and import gates pass. Class, declared-definition,
  data shadow and converged-data checks pass; no second data names.
- `place_bodies.py` on the three consumers finds **0 bodies, 0 pins**.
- `proof.py` verifies exactly three changed COMDAT bodies, all native provider
  twins, no other section or external-binding changes, no new variants, and no
  regression in the three providers' local findings.
- `link_check.py` predicts all three consumers and
  `FamilyDeletingDtors_muse-67c0.cpp` now link: **279 + 187 + 177 + 28 = 671
  existing authored bytes**. The latter provider previously selected the wrong
  BaseUpgrade deleting destructor; correcting its consumer also repairs that
  selection. The other two providers retain unrelated unresolved/duplicate
  blockers listed in the proof.

This is a **legacy local preview gain**, with self-strict byte verification.
It is not a closed-strict gain or a full-link result. No census, full link
cycle, nightly or boot runner was started. Authored C++ coverage grows by zero.
Original objects, dependency receipts, source snapshots and command logs are
retained in ignored `build/w3dview-frame-link-20261015/`. Run `proof.py` from the
repository root while those paired objects and the measured index remain.

## Reference review and handoff

The verified BFME1 pointer is `a7c38d3b2597121f178ab5190b3062478823257d`.
Upstream fetched HEAD is `a5a369864461df0da0a435313edc3252a761de4a`; another
worker holds `file:reference/open-bfme-1`, so the verified pointer was preserved
and no freshness-success stamp written. Reviewed donor repairs `4966496c5ae4`
(AsciiString accessor COMDAT ownership) and `de59a7e9f891` (Apt predicate shape)
provide the shared-code reconciliation guide; neither supplies this flag fix.
The wrapper identities, frame delta and retained EH behavior are BFME2 evidence.

The same-settings scan also found ObjectModuleCtor.cpp, but it has an additional
wrong selected ObjectModule destructor; its claim was released without editing.
Other frame-sensitive units need their own consumer and provider evidence before
changing flags. Separate const-AsciiString pair and mesh RefPtr destructor trials
were reverted after byte failures, recorded in `re_attempts.log`, and released.
Their inline cleanup requirements still need cross-unit reconciliation; do not
repeat those unchanged trials.
