# BFME 1 freshness: pre-existing byte failure, pointer retained

Official Open-BFME/Open-BFME-1 master was fetched at
`703bb287647d74ae4025d53513102c27c008e64e`. The clean checkout and committed
pointer remain `42bba2ddbd5cb895d99293583891d3b7315fa49e`, independently
verified by the previous update's evidence in
`../bfme1-freshness-20261022-bce2/readme.md`.
No dirty or unpublished donor work was overwritten.

This seat acquired `/home/agent/.cache/bfme1-update.lock` as `codexb` and ran
the previous-pointer full gate before changing any donor input. The BFME 2
production inputs were origin/master `21b0fe73b2`; HEAD `a852d600cc` adds only
two earlier attempt-evidence commits. The new shroud handoff also changes
only attempt evidence. The gate exited 1 after approximately 32 minutes;
its complete output is retained in `old-gate.txt`.

The single function-byte failure is pre-existing, at the old donor pointer:

```
?rva00042036@Rva00042036@@QAEPAVRva000647B5@@XZ
0x00042036, 50 B
Code/GameEngine/Source/Common/Rva00042036Factory.cpp
+0x0C: compiled allocation operand 0x14; retail 0x10
```

The factory uses `new Rva000647B5`. The canonical-SubsystemInterface adoption
in `d0823bd581` replaced its 8-byte private base view with the 12-byte
canonical base while retaining the derived `char m_pad[4]`. With the other
4-byte polymorphic base, the resulting allocation is 20 B. This explains
the observed 4-byte difference. Removing that obsolete derived padding is
a plausible focused repair, but was not attempted or claimed verified in
this assigned banked-body seat. The constructor's separate private view
still has the old base shape and deserves reconciliation with that repair.

Every other function row passed (98,068 of 98,069). All 2,135 data rows,
baseline, literal, float, import, DIR32, pin, module-registry and source-claim
checks passed. The no-op patch check was explicitly unrunnable because the
function verification did not produce a complete patch set; it is not an
independent second byte defect. This is an actual mismatching allocation,
not evidence of a verifier false rejection.

The input audit inspected 23,493 dependency receipts with no malformed
receipt and no dependency on any of the 49 changed donor files. No donor
header or toolchain file changed. The existing layout resolver selects
`game/`, `inputs/reference/`, `inputs/toolchains/`, `inputs/vendor/`,
`inputs/baselines/` and `targets/game/reverse/`; all directories exist.
Intended WWMath/WWLib headers and `tools/lift_lane.py` were checked directly;
their hashes are in `input-audit.json`. No layout repair or header
substitution was made.

Because the comparison prerequisite failed, this session did not advance
the checkout, stage a new pointer, run a new-pointer comparison or refresh
discovery caches for uninstalled inputs. The ignored freshness-success
stamp was left unchanged. The update lock is released after recording this
blocker. A later freshness check must retry after the factory mismatch is
repaired; this note does not waive or indefinitely suspend that check.

No authored C++ or newly linked bytes are claimed. No maintainer-only
verification runner was started. Model gpt-6.1-sol, 2026-10-23 UTC.

## Concurrent upstream resolution

The final progress comparison found that origin/master had advanced while
the old-pointer gate ran. After rebasing this evidence onto `0fa5a5b477`,
the factory repair was already present in upstream `6ae1fde8d5` (obsolete
derived padding removed). A fresh ordinary
`./build.sh Code/GameEngine/Source/Common/Rva00042036Factory.cpp` then exited
zero: 1/1 function row, source claims and scoped reference checks passed.
The allocation failure above is therefore historical, not a current
unresolved factory blocker. No full gate was rerun after this rebase.

Upstream also contains the independently verified pointer
`f890413e75e671748215ba2ef3304aa7953993e9` and its paired passing gates in
`../bfme1-freshness-20261022-f890/readme.md`. The clean donor checkout now
agrees with that committed pointer. The pull fetched a newer official
master, `f36a4db066aa61edeee90085a31d628eb829001d`; this seat did not test an
update to that revision or write a freshness-success stamp. The next
freshness pass must use the now-repaired production inputs and preserve
the upstream verified pointer until its new comparison passes.
