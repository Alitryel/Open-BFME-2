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

Recovery reconciliation: upstream 8bf8041bea now provides loadPostProcess in
Rva0032A186Finish.cpp and owns its fold row. Remove the saved duplicate row
and constructor-unit definition rather than introducing a second provider.
The +622 B above is the original saved legacy measurement, not an additional
recovery gain over origin/master. Constructor declarations still bind to the
upstream provider. The recovered source matches upstream's constructor unit.

## Transfer-unit duplicate repair

At BFME 2 `0c95e5179b`, the transfer unit still defined the empty
`BuildListInfo::loadPostProcess` after `Rva0032A186Finish.cpp` acquired its
verified complete retail body at RVA `000B3FD0`. Remove the older unrowed
definition and retain its virtual declaration, binding to the rowed provider.
No layout, identity, pin or matched-body change is needed.

Measured with `tools/link_check.py` on BuildListInfoXfer,
Rva0032A186Finish, BuildListInfoCtor and BuildListInfoCopyCtor together:

| Current-object preview | Before | After |
| --- | ---: | ---: |
| Units linking | 2/4 | 4/4 |
| Matched bytes linking | 622 | 1,076 |

The repair gains **454 B** against the current pre-edit tree: 305 B in the
transfer unit and 149 B in the destructor unit. The published census
(`0393df10e2`, 2026-10-23 19:47) had 927 B in this cohort, so the net change
against that older census is 149 B. These are legacy previews, not self-strict
or closed-strict measurements. The unreferenced setNextBuildList diagnostic
remains and does not block either unit.

Acceptance: scoped `./build.sh` passes 1/1 transfer rows and 8/8 provider
rows, including four EH funclet pins; `find_declared_unmatched.py --fail`
passes for the edited unit; `git diff --check` passes. BFME 1 donor inputs
remain at the verified `96c88c73a5cd` revision; this repair uses the existing
BFME 2 provider rather than importing a donor change.
