# BFME 1 reference freshness: 96c88c73

Controlled update from the committed, previously verified pointer
`138757e9b74645fbcbb7724a7af2764e34931e11` to official master
`96c88c73a5cd1a58fc2f8db691beea50acd996db`, fetched on 2026-10-23.
Both comparisons use the same BFME 2 production sources at
`83cd376544900c32de4dd99ec3c115ac1c174ad6`. The donor checkout was clean;
the prior checkout and verified pointer remain reachable through preserved
local refs. No dirty or unpublished donor work was discarded.

Both ordinary full `./build.sh` gates passed: **98,158 function rows and
2,148 data rows**, all literal/import/float checks, DIR32 consistency, pins,
module registry, source claims and the no-op patch. The initial baseline
restored 6,922 stale objects from the published object bundle before compiling
the remaining stale units. The new-pointer gate needed **0/23,417** TU
recompiles; its recorded dependencies were current. See `old-full.txt` and
`new-full.txt`.

Both complete `eh_verify.py --all --json` runs covered 11,891 EH rows with no
missing objects: 11,867 exact and 24 existing baselined findings. Their entire
JSON verdict artifacts were compared byte for byte and are identical, SHA256
`f0d3994ca0c33fae5036deae8bb6cd7034301fae6dd9aaf6ac5cbf0a0bd13186`.
No update regression was found. The 24 advisory EH findings are pre-existing;
neither baseline nor verifier was changed.

The upstream diff changes 236 game source files, donor ledgers/evidence and
two donor tool files. It changes no `inputs/` file, game header, compiler,
shim or layout. The existing layout resolver still resolves `game/`,
`inputs/reference`, `inputs/vendor`, `inputs/toolchains` and the game ledger.
The actual Vector3/AsciiString headers and C2 DLL were checked on disk and
hashed in `inputs.json`. No include substitution or layout repair was needed.

Refreshed all separate reference lanes at the new pointer:

* BFME 1 scan: 38,786 donors, 5,525 placements, 5,516 independently matched
  boundary controls; ranked and near queues both zero.
* Named lift lane: 146 bodies, 103 servable; this is a source lead, not recovery.
* ZH cache: forced rebuild after the elapsed root changes, 919 compiled and
  the same 68 discovery compile failures as before. Matching scans 27,013
  functions; fresh packets are zero. Packets were written under ignored
  `build/` to preserve an unrelated untracked `reverse/zh_sweep/` directory.
* No previously cached donor trial uses one of the changed donor source files.
  Two plausible changed clean TUs, `VectorClassBfmeHandleCXResize.cpp` and
  `AIPlayerIsPossibleToBuildTeam.cpp`, were additionally compiled/searched by
  `place_bodies.py` using BFME 2's toolchain: zero free bodies/pins. This does
  not exhaust every possible reference reconstruction.

The former FireWeapon class-table blocker was rechecked before updating:
upstream `274668bf9b` already reconciled its primary table names. No local
class repair was needed. Temporary investigation claims were released.

Success was recorded in ignored `build/bfme1-last-check.txt` only after both
full gates and the exact EH comparison completed. The verified gitlink is
banked with this evidence. No maintainer-only verification runner was used.
