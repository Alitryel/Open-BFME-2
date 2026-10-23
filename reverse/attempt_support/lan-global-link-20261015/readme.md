# LAN global binding repair, 2026-10-15

At BFME2 base `01b0aa53cf8fbe6a4046d7f30fe7b5f1fc8122bb`, replace the
address-named `g_00DFE958` declaration and macro in
AptLanLobbyRva004467AC.cpp with `extern LANAPI *TheLAN`.
The data ledger identifies RVA 0x009FE958 (VA 0x00DFE958) as
`?TheLAN@@3PAVLANAPI@@A`; Rva00446A77Enable.cpp already defines that global.
No layout, ABI, function identity, extent, pin, header or compiler flag changes.

## Controlled evidence

The original and repaired consumer both pass strict byte preparation with
current dependency receipts. proof.py compares genuine saved objects against
separate in-memory copies of the same index. proof.json records its hash,
measurement commit `19a2565407` (2026-10-15 09:33), underlying census commit
`5986a99448`, source base and object hashes. Binary scratch remains in
build/lan-global-link-20261015.

Exactly five DIR32 relocations change their external name to the existing
global. After that explicit rebinding, all nondebug sections, their bytes,
relocations and external bindings compare equal. The local preview removes
exactly one finding: the unresolved address-named global. Other findings are
identical before and after. The consumer's findings fall from four to three.

The remaining findings are the base tree iterator comparison, the map find
wrapper and a selected tree find definition that is not retail's. Consequently
legacy preview LINKED stays 0 -> 0 for this consumer (547 credited bytes, 549
retail row bytes); new authored C++ bytes are zero. This is a verified binding
repair, not a self-strict or closed-strict placement gain, new census result,
or full executable link result. No index or link status was rewritten.

## Acceptance

- `link_check.py --prepare-current` consumer: original and repaired 1/1
  matched, strict reusable receipt current; string/float/import checks pass.
- `./build.sh` consumer: 1/1 matched, 549 bytes; same reference checks pass.
- `./build.sh` provider Rva00446A77Enable.cpp: 3/3 matched, 98 bytes.
- `link_check.py` consumer and provider together: consumer has exactly the
  three findings above; provider remains LINKS, 98 -> 98 legacy preview bytes.
  The command exits 1 for those remaining consumer findings, as expected.
- `link_check.py --new-variants` consumer: passes.
- `data_check.py --enforce`: zero findings; `--converged`: zero second names
  or unjudged rows at the eight enforced addresses.
- `eh_verify.py`: 1/1 EXACT, zero baselined or missing objects.
- `find_declared_unmatched.py`, `class_gate.py`, `git diff --check`: pass.

## Lane sweep and handoff

Started with repair_queue.py link and link_rank.py. Current local checks show
ParticleSystemDebugDisplayBody.cpp, AIIdleStateUpdate.cpp,
AIAttackApproachTargetStateOnExit.cpp and AptMpGameSetupRefreshMapList.cpp
already link-clean; no edits made. EvaRva001DDF04.cpp still has the iterator
comparison conflict, but its file claim belongs to another worker.
Rva000A7E9E.cpp's recorded funclet-label false reject remains unchanged; the
temporary claim was released without editing or retrying it.
Rva00525ABFXfer.cpp still has its list comparison, insert and parent/selected
conflicts; its recorded vcall-thunk consistency blocker was not retried.
This repair drains the remaining live g_00DFE958 declaration: the other two
source occurrences are comments. Further iterator/map repair is independent.

Reviewed BFME1 repair `363b11ce5ffda35ebbf8a41f87dbdd3273a3f8af`
(canonical zero-float binding): its global ownership principle is applicable;
no BFME1 addresses, class layouts or C++ bodies are imported. Official master
was fetched at `584f5ded3661b120cfacf26be58eee3800752666`. The clean verified
submodule remains `a7c38d3b2597121f178ab5190b3062478823257d`.
The previously documented pointer-update baseline remains blocked by
stale/missing dependency inputs and a stalled MSVC verification; another worker
holds the reference scope claim. No pointer update, false success stamp or
repeat of that unchanged baseline was attempted. Broader census/full-link
verification remains maintainer-only and was not started.
