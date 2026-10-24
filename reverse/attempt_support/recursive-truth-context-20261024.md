# Recursive retail proof cache context, 2026-10-24

Tooling follow-up to `streak-truth-cache-order-20261024.md`. No C++ source,
ledger, pins, baseline or link-selection policy is changed.

Inputs: BFME2 `66561788a029c95f2021dd32177b64e299ec1506`, BFME1
`32774ab03393709a7f14331ba8d98d281a55ffd9`; published census index
`2026-10-24 07:31 at a9f880ad06`, `retail-truth-4`.

## Reproduced defect

Run `python tools/link_check.py` with these two arguments, then reverse them:

```
Code/Libraries/Source/WWVegas/WW3D2/StreakLineDestructor.cpp
Code/Libraries/Source/WWVegas/WWLib/simplevec_float_cleanup.cpp
```

Before this repair, consumer first refuses Streak's 327-byte unit on
`??1?$SimpleDynVecClass@M@@UAE@XZ`, while provider first accepts both units
(327 + 175 = 502 bytes). Neither source nor compiled object changes between
the two runs. The index's older 357-byte Streak entry is not a coverage gain.

The regression constructs two COFF objects with identical ctor, vtable and
deleting-thunk bytes, relocation names and local COMDAT digests. Only the
transitively reached leaf differs or is undefined. With the old cache,
judging the bad object first poisons the good object's proof; judging the good
object first can wrongly certify the bad object. All 16 combinations of
object order, public/private proof entry point, tagged/untagged definitions
and bad/undefined leaf fail before the fix.

## Repair and boundaries

COMDAT definitions carry the SHA-256 of their complete originating COFF
object. Verdict keys include that context; recursive-definition keys include
the context, symbol index and target address. These identify the actual graph
being proved, including transitive referents that a local COMDAT digest omits.
Hand-built definitions without immutable object provenance are freshly proved;
identity is used only to recognize cycles during the active traversal.

Only outermost recursive results are memoized, as before: an inner result
may depend on an ancestor cycle assumption. Existing byte, relocation,
depth-limit and link-selection checks remain in force. Regressions also check
that a valid cycle succeeds, a cycle with an unresolved extra edge fails,
and an over-depth chain fails. No rule rebaseline is required.

## Validation on Windows

- New regressions before repair: 16 failed, 3 passed.
- `python -m pytest tools/tests/test_link_census.py -q`: 67 passed.
- `python -m pytest tools/tests/test_gate_exploits.py -q`: 25 passed,
  1 skipped (the repository has no audit-escape fixtures in this checkout).
- All `test_link_census*.py`, `test_link_check*.py` and the exploit suite:
  376 passed, 1 skipped, 1 failed. The existing
  `test_census_dates_are_utc` calls POSIX-only `time.tzset()` before reaching
  production code; Windows Python lacks it. The unchanged HEAD test has the
  same call. Repeating with only that platform-unavailable test deselected:
  376 passed, 1 skipped, 1 deselected. No test or platform shim was changed.
- Both real `link_check.py` argument orders now accept both unchanged units,
  502 bytes total, using the same published index and object receipts.
- `./build.sh` for those two units: 6/6 functions byte-match; source claims
  and string, float and import-reference verification pass.

This resolves an order-dependent verifier result, not newly recovered or
newly linked C++ coverage. BFME1 at the committed verified pointer has no
equivalent recursive-definition cache repair to transfer. Refreshed reference
searches found no BFME1 exact/near donors; the ZH rebuild produced 919 objects
and 68 compile failures, and matching those objects yielded no viable packets.
