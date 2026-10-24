# Verified BFME 1 reference update, 2026-10-24

Advance the clean official donor from 32774ab03393709a7f14331ba8d98d281a55ffd9
to 0bf534ea7ccde110c456edb9cd2dd5dae823c953. The previous pointer remains
reachable as local branch codex/bfme2-verified-32774ab0-20261024. No donor
changes were discarded. Official master was fetched once for this freshness pass.

Both ordinary full ./build.sh comparisons use BFME 2 production tree
3f5254f0d2dfd816b197c4175706d65353c1b3b6. The receipts attest that HEAD,
production sources, verification code and ledgers remained unchanged throughout
each run. Both gates pass all 98,234 functions and 2,186 data rows, literals,
imports, DIR32 consistency, pins, module registry, source claims and no-op patch.
The new pass rebuilds only three of 23,422 TUs. No regression or allowance change.

Both full exception-data results are byte-identical: 11,894 rows, 11,870 EXACT,
23 bytes_differ and one retail_only; all 24 existing findings are baselined and
there are zero missing objects. Complete JSON SHA256:
bac819e4dace30816ae512f5e702073c98b01091c145755fe8e847d80917da02.
Full logs and EH JSON remain under ignored build/reference-0bf534ea-20261024/.
An earlier launcher selected WSL bash without Wine and could not compile. That
invalid environment run is preserved separately as wrong-shell; it is not used
as evidence of an old-input failure. Both accepted runs explicitly use native
Git Bash and MSVC 7.1.

The existing resolver selects game/ and inputs/{reference,vendor,toolchains,
baselines}. Resolved directories and intended vector, mouse and lift files
exist. The dependency receipt confirms the actual Mouse/Win32Mouse headers.
Only two inputs/reference files change: the mouse layout headers. Their new
fields replace older padding; both inputs manifests retain exact hashes.
No layout migration, silent header substitution or BFME 2 source repair needed.

Reference lanes were refreshed at the new donor:

- BFME 1 scan: 38,796 clean donors, 5,524 placements, all on claimed ground;
  5,516 independent boundary controls. Ranked and near both return zero.
- Named lift lane: 140 bodies / 102,396 bytes; 98 servable / 76,835 bytes.
  These are source leads, not recovered C++ or proof of an original target name.
- ZH cache forced fresh: 919 built, 68 failed of 987 sources. The failures are
  the existing missing WWAudio/SDK and configuration dependencies, separate
  from the green BFME 2 byte gate. No old object survives a failed rebuild.
  Fresh matching: 27,013 functions; zero free exact placements. Packets: zero,
  242 addresses already claimed. Packet output stays under ignored build/,
  preserving unrelated reverse/zh_sweep work.

Linking donor review includes new native-import bindings, canonical globals,
virtual tables, specialized scalar deletion and library provider repairs.
Current BFME 2 objects already incorporate the large GameLogic and sentence
provider corrections. Their stale census blockers are not credited to this
update. The next selected native copy dispatcher issue is instead supported by
its own BFME 2 five-push call and STLport source interface, with a separate
paired repair trial. No census, link cycle, smoke runner or publisher was run.

This update adds zero recovered or linked bytes. The success stamp is written
only after both full comparisons, identical EH checks and refreshed lanes.
