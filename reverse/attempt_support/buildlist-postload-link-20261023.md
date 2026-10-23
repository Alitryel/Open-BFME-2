# BuildListInfo post-load linkage repair

The canonical Snapshot views in BuildListInfoCtor.cpp and
BuildListInfoCopyCtor.cpp both declare the protected loadPostProcess override,
but no provider defined it. Define its empty body in the default-constructor
unit and admit its genuine identical-code fold at RVA 0x000B3FD0.

Target evidence: the complete matched default constructor at RVA 0x0032A0CE
and copy constructor at 0x00329DE6 both store VA 0x00C0D904. Its four entries
are VA 0x0072A4BB, 0x004B3FD0, 0x00729EE3 and 0x00729BBF. The canonical
Snapshot contract establishes slot 1 as the post-load callback. RVA 0x000B3FD0
contains the complete one-byte RET and no relocations, matching the existing
BehaviorModuleLoadPostProcess.cpp owner. No pin or second address is added.
The existing BuildListInfo identity, layouts and other method bodies remain
unchanged; this is a link repair with zero new unique authored code bytes.

The previous blocked attempt (re_attempts.log entry for 0x00329DE6) required
reconciling the neutral name-getter owner first. Upstream has now renamed that
owner to GetSnapshotName@BuildListInfo in SubsystemNameGetters2.cpp. Its current
provider is explicitly included in both measurements, so its upstream repair
is not credited here. BFME1 donor revision reviewed in this session was
96c88c73a5cd1a58fc2f8db691beea50acd996db; this override follows target table
evidence and the existing target Snapshot contract.

Legacy current-object preview against census 456ce161c5 (2026-10-23 06:28):
before, both constructor units are blocked solely by loadPostProcess, 0/622
non-padding bytes linked; after, both LINKS, 622/622. Relative to the published
census, this adds 253 bytes and restores 369 bytes that the current declarations
otherwise lose. The unchanged name-getter provider LINKS with 268 bytes in
both measurements. Logs: build/link-seat-buildlist-{before,after,final}.log.
These are scoped legacy preview results, not self-strict or closed-strict
closure measurements; no full link cycle or runtime test was run.

Acceptance: add_match verified the fold and all eight default-constructor-unit
rows. link_check.py --prepare-current verified all 53 rows across the three
explicit providers with strict reusable receipts, including 45 string literals
and the renumbered cleanup labels through their exact parent EH graphs.
find_declared_unmatched and check_csv pass. Ordinary commit hooks must also
pass before this repair is banked.
