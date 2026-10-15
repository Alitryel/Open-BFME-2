# Vector4 scalar-first unit: suppress the unused vector-first copy

Base: 034ea1a937. Measurement index a2839ea429 (2026-10-15 13:35), underlying
census 5986a99448 (04:52); SHA256
c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37.
The committed link-status measurement is different and was not rewritten.

`Vector4ScaleO1.cpp` owns the matched scalar-first operator at RVA 0x00308182,
69 bytes. Its donor header also emits an unused vector-first operator with
SSE register allocation different from retail. Retail's vector-first body at
0x00191070 belongs to `seglinerenderer.cpp`; the current provider is byte-exact
(69 bytes, digest da7831003ea8). The rejected incidental copy is also 69 bytes,
digest 8f65de4af8db. Neither copy has relocations. This follows the existing
constructor suppression in this unit and the BFME1 unused-COMDAT repair pattern
reviewed at 66b19a8e95a4add525ef808fcea088e306798e2b. The original header retains
its BFME1 provenance; no donor body, identity or layout has been newly imported.

A TU-local imported force-inline redeclaration keeps the original donor
arithmetic available to the compiler while preventing its unused out-of-line
copy. The shared header and scalar-first implementation remain untouched.
No new pin, alias, baseline, ledger row, class view or compiler override.

## Acceptance evidence

The source file was claimed before editing. Bounded preparation before the edit
passed its 1/1 matched row. Final bounded preparation of consumer and canonical
provider passes 15/15 rows and six compiler float literals with strict reusable
receipts. `./build.sh` passes the consumer's matched row. The normal local link
preview passes both units; the provider was already clean in the paired baseline.

`proof.json` records a same-index before/after comparison refreshing only these
two explicit objects in memory. Consumer findings go from one wrong COMDAT to
zero; its legacy linked bytes go 0 -> 69. Provider findings stay zero: its 2480
bytes are not a new gain. Four retained COMDATs are byte-and-relocation identical;
all other nondebug sections, external bindings and directives are unchanged.
The removed helper has no nondebug relocation callers and no replacement import
reference is introduced. Original and final object snapshots and strict receipts
remain under `build/vector4scale-helper-link-20261015`; `proof.py` reproduces the
comparison using them without updating the census or its index.

Also passed: new-variants admission, converged data (eight addresses, no second
names or unjudged rows), EH verification (no EH rows), declared-definition check,
check_csv (91504 functions / 15481 symbols / 464 data rows), and diff whitespace.
Commit hooks supply the staged identity, class and hatch checks.

These are self-strict byte receipts and a legacy local link preview. No
closed-strict closure, real link placement, full census, nightly or boot result
is claimed. Authored C++ byte coverage is unchanged.

## Other probes and handoff

AptStringSplit's ranked default-EAStringC-constructor finding is stale: unchanged
strict preparation and local preview already pass its 685 bytes. No edit or gain.
WideStringCompareCharacterBFME2 still needs the comparator's compiler summary:
removing its visible worker creates an extra stack slot and changes the matched
66-byte caller. Original source restored and byte-verified. Both outcomes are
recorded in re_attempts.log and their claims released. Do not repeat the same
trials without new evidence. The BFME1 freshness update remains with the worker
holding the submodule claim; the verified pointer and success stamp were retained.
