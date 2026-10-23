# Bridge list value destructor: real definition, redundant pin retirement

## Scope and provenance

Seat2, `sol-team-supply-20261023`, isolated `t3-7faf7255`, 2026-10-23.
Base `5a13e528c5d00f8e0eb00a3675b3749bd814a08b`; BFME1 donor unchanged at
`138757e9b74645fbcbb7724a7af2764e34931e11`. No provider/header/runtime changes.

Native callback/copy evidence recorded in
`reverse/attempt_support/bridge-parser-link-20261018/readme.md` establishes the
12-byte pointer/delay/string record (offsets 0/4/8). The existing owning TU is
`Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorListCleanup.cpp`.
The original application type name remains unknown; this neutral name is not a
new inference of the original class identity. Canonical `ascii_string.h` gives
the actual owning 4-byte string its ordinary destructor lifetime. No fake
storage, wrapper, cast, alias, forced throw or additional cl flag was introduced.
The truthful `// stlport` dependency declaration was added after diagnosing the
initial strict-inventory refusal; its precise environment effect is below.

## Native contracts

The ordinary out-of-line/noinline record destructor emits all 8 bytes at
`0x00577998`: `83 c1 08 e9 70 ea ab ff`. Its sole relocation is REL32 at +4 to
`?releaseBuffer@?$StringBase@D@@AAEXXZ`, real RVA `0x00036410`.
All six pre-existing same-address/same-extent rows in four owner TUs independently
emit exactly this complete body and direct relocation (including gen-alias rows,
which resolved without masking). `verification.json` lists every real name.

The actual 133-byte releaseBuffer provider is completely exact, including
`?Rva00035C90Get@@YAPAVRva00041004@@XZ` at `0x00035C90`, `_free` at `0x00030830`,
critical-section import identities and its complete EH placement. Existing
Bridge list clear/base/list destructors remain exact at `457441/49`, `BD218/23`,
`BDB3C/5`. Clear and base destructor use real `_free` at `30830`.

Normal `add_match.py --icf-owner '??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ'`
admitted the genuine Bridge definition, not a pin-fold or gen-alias admission.
Only the now-redundant same-name `577998` symbols pin was deleted; only that
address's existing hatch count changed 3 to 2. Unique coverage gain is zero.

## Verification and limits

Normal explicit six-source `./build.sh`: 65/65 complete rows exact, all literal,
float and import checks pass (6 named imports). Independent noncompiling object
inspection: all 65 exact, zero masked and zero unresolved. EH 12/12 EXACT,
zero missing objects. See `verification.json` and `verification.log`.

All five prospective owner/provider command mappings passed with empty stderr,
existing seat-local paths, unchanged pin/flags, no FI/response arguments, and
compiler grant unset; full resolved commands/environments are in `mappings.json`.
The compiler ran only these six authorized production sources. No runtime,
transport or debugger anomaly was observed during this phase.

Initial strict consumer `link_check.py --prepare-current` REFUSED the unknown
include search-root inventory: `(macro or parent-traversing include has unknown
search roots)`. This original diagnostic is retained in `verification.log`.
The source already used real STLport list headers but lacked its truthful
`// stlport` declaration. That declaration enables native macro-root inventory
handling and adds the same seat-local vendor/stlport directory to INCLUDE.
Fresh normal command inspection proves argv, explicit /I order, LIB, WINEPATH
and selected compiler header unchanged; only INCLUDE gains vendor/stlport first.
No provider/header/tool/runtime edits or forced-include arguments were needed.
After this authorized real dependency correction, normal 4/4 consumer verification
and strict `--prepare-current` both PASS. The resulting version-2 receipt includes
the inventory and current source/object hashes. Subsequent six-source verification
reuses all six current objects (zero compiles), passes all65 rows/allrefs and
EH12/12. No fabricated receipt, blanket waiver or tooling bypass was used.
Strict self-currency does not establish current link closure.

Explicit six-source historical `link_check.py` preview: 6/6 LINKS, aggregate
2523 -> 2608 bytes; cleanup 0 -> 85. The loaded index is OLD `456ce161c5`,
2026-10-23 06:28. No fetch/refresh/census/current-ledger run was performed.
This does not measure current linked-byte gain or complete Scripted closure.
Existing owner/provider preview counts remain 385/171/642/385/940 unchanged.

Normal staged name_dependents returned exit0 with no output; normal call-target
comparison also found no lost names. Delta source is only the cleanup TU.
No claim of newer parent donor96 verification is made by this seat.
