# Two tree consumers: local link repair, 2026-10-15

At BFME2 base `2f90b52cc0fc89ab2039483c1c68e202784b3dbb`, suppress incidental
STLport external definitions in FormationPreviewPoolLookup.cpp and
Rva0041573FParse.cpp using existing BFME2 patterns. The typed iterator comparison
is local; fully inlined comparator/increment definitions use the established
`dllimport`/`forceinline` specializations. No imports are emitted. Matched body
source, declarations, ABI, globals, ledger rows and retail extents are unchanged.

## Measurement and result

Use the exact index identity and provider set in final-context.json. Its update
commit is `19a2565407`, census commit `5986a99448`; SHA-256 is recorded there.
The ordinary legacy local check refreshed the same two strict-current objects in
both controlled phases against that unchanged index. Each goes from two COMDAT
findings to zero; every other finding collection is unchanged:

| Consumer | Matched bytes | Before | After |
| --- | ---: | --- | --- |
| FormationPreviewPoolLookup.cpp | 252 | tree-base comparison, less<unsigned> | LINKS |
| Rva0041573FParse.cpp | 163 | tree-base comparison, typed iterator increment | LINKS |

This is **415 existing bytes / two units made link-clean in the legacy local
preview**, with zero new authored matched bytes. Strict byte receipts establish
current provider identity only. No self-strict placement, closed-strict gain,
new census result or full executable link is claimed. Index/status were not
rewritten; maintainer-only broader verification remains outstanding.

final-object-proof.json records 40 and 15 retained COMDATs respectively, all
byte/relocation identical. Each unit removes two external helper definitions and
adds one unreferenced local comparison. Normalized nondebug section contents,
relocations and directives otherwise agree. No retained section references the
removed helpers. final-link-proof.json records before/after findings, not a
manufactured ranking.

## Acceptance

- Baseline `link_check.py --prepare-current` for the original four-file trial:
  22/22 matched. Final preparation of the accepted pair: 2/2 strict-current.
- `./build.sh` accepted pair: 2/2 matched; two string references verified.
- `link_check.py` accepted pair: two of two LINKS, 0 -> 415 legacy preview bytes.
- `link_check.py --new-variants` accepted pair: passes.
- `eh_verify.py` accepted pair: 1/1 EXACT.
- `data_check.py --enforce` accepted pair: zero findings.
- `data_check.py --converged` accepted pair: eight addresses, zero second names
  and zero unjudged names.
- `find_declared_unmatched.py`, `class_gate.py`, and `git diff --check`: pass.
- `place_bodies.py` accepted pair: zero additional bodies or pins.

Proof scripts operate from repository root with scratch artifacts under
build/tree-iterator-wave2-link-20261015. Baseline objects were compiled under the
same inputs and saved before editing, not taken from an obsolete cache. They
remain in scratch with genuine dependency receipts. Published JSON preserves the
comparison results; scripts document their method.

## Reverted audio trials: verifier handoff

The same local comparison was tried in Rva000A7E9E.cpp and MilesAudioCache.cpp.
The strict four-file trial passes 20/22, refusing only unparented funclet pins:
`uw_00760bc6` (`object-symbol=$L7970` becomes `$L7983`) and `uw_00760c03`
(`object-symbol=$L6948` becomes `$L6961`). Four other parented audio funclets
rediscover correctly. EH is EXACT 5/5 across the pair. All 95 and 66 retained
COMDATs, normalized nondebug sections and directives remain identical; the only
change is an unreferenced local comparison replacing its unused external copy.
Each renamed funclet retains its whole native eight-byte body. Their containing
COFF sections respectively remain:

```
8d4df0e900000000b800000000e900000000
8d4dd4e900000000b800000000e900000000
```

object-proof.json and eh-audio-trial.json preserve the successful structural
comparisons; strict-after.txt preserves the refusal and audio-trial.patch the
minimal reproducer. The missing parent metadata blocks local-label rediscovery.
Recorded both as false rejects through re_log.py, restored both sources AND
saved genuine objects/receipts, and released both claims. No label/check/ledger
workaround is included. A tooling seat may reproduce and repair resolution with
a regression test, separately from this repair.

## Donor review and freshness

Reviewed official BFME1 `master` at
`c02ec78acef9c8555a7cf8c1d5da79c7d42fa8b3`, especially helper reuse repairs
`63e68aaa567add9eb42a79913d23eece6a19ceee` and
`94f453a51ffa2807bb6102cf9272c69c7be368d6`. Those import earlier BFME2 repairs:
applicable principle is existing typed library-helper reuse; no BFME1 ABI,
layout or function identity is transferred. Exact local recipes already exist
in W3DShroudInterpolate.cpp, Rva0059D7C4ArmyTally.cpp and
TerrainLogicWaypointLookups.cpp, and the previous tree-iterator repair evidence.

Retained clean, verified submodule pointer
`a7c38d3b2597121f178ab5190b3062478823257d`. Another worker holds its file claim;
the recorded old/new full-gate comparison is still blocked by stale/missing
baseline dependencies. Did not change the pointer, mark freshness successful,
or repeat that unchanged blocker. No decoder sources were read.
