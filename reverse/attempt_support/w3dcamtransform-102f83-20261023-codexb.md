# Camera seat: ownership handoff, 2026-10-23

No reconstruction was started. At BFME 2 commit
`5485a303c78320dfb8c2f5908921689f472047e5`, all three bodies in this seat's
standing assignment had live claims held by other contributors:

| RVA | Owner | Claim check |
| --- | --- | --- |
| `0x00102F83` | `yasinschroeder-codexb2` | `claims.py claim` refused; about 3.6 h remained |
| `0x001C2B80` | `yasinschroeder-claudec` | `claims.py claim` refused; about 3.8 h remained |
| `0x001C5E30` | `yasinschroeder-codex6` | `claims.py claim` refused; about 3.3 h remained |

Checks were made around 02:32 UTC. This seat's owner is
`yasinschroeder-codexb`; it acquired no claim and must not release the owners'
leases. Recheck ownership and landings on resumption. The standing assignment
restricts fallback selection to the two listed bodies, so no unrelated queue
was drawn.

The target-specific history was read through `pick-hard --rva`, including the
camera r66 handoff and its causal current-progress and Rotate_Y records. The
existing camera bank (score 0.95707) and all previous evidence remain unchanged.
No source hypothesis was tested or ruled out during this ownership check.
Resume from
`reverse/attempt_support/w3dcamtransform-102f83-r66-20261022/readme.md` after
obtaining the claim; do not repeat its allocator and compiler controls.

`git pull --rebase origin master` and `python3 tools/check_csv.py` passed.
`python3 tools/link_check.py --fetch-index` retained the current published
2026-10-22 23:07 census and populated the reusable object store. BFME 1's last
successful freshness stamp was overdue, but the recent shared update lock
belonged to `codex4`: the runner's lock rule requires leaving that update to
the owning seat. No success stamp or submodule pointer was changed here.

`python3 tools/progress.py origin/master` passed with authored C++ exact,
byte-matched and linking deltas all +0. No byte gate was required because no
production source, compiler input or ledger row changed. This is coordination
evidence only, with no coverage or linking improvement claimed.

## Ownership recheck at 03:12 UTC

At `6afcf9b84b49a0d1d5dedf40e19fd54c9ead879a`, fresh claim commands
again refused all three standing targets. The camera is still held by
`yasinschroeder-codexb2` (3.4 h left), `0x001C2B80` by
`yasinschroeder-claudec` (3.1 h), and `0x001C5E30` now by
`yasinschroeder-codex7` (4.0 h, verified locally and awaiting publication).
This seat acquired no claim. None of those leases was released here.

The camera bank has advanced independently to **0.9741961628516264**,
emitting exactly 4,299 bytes with 228 differing bytes and 57 resolved
relocations. Its new continuation is
`reverse/attempt_support/w3dcamtransform-102f83-seat23-20261023/readme.md`.
That handoff and the target history were read through the permitted picker;
the bank was preserved unchanged. No reconstruction hypothesis was tested
or ruled out in this recheck. On resumption, obtain the claim before source
work and use this newer bank and handoff rather than the earlier r66 input.

The pull, ledger check, published-index fetch and
`python3 tools/progress.py origin/master` passed; all coverage and linking
deltas were +0. The BFME 1 freshness update remains assigned to the recent
shared `codex4` lock, so no success stamp was written. No production source
or byte-verification input changed. The standing assignment allows only the
two fallback bodies above; unrelated queues were not opened.

## Ownership recheck at 03:30 UTC

At `05ad990e98f6867430289f7975008bb5d968bd62`, sequential fresh claim
commands again refused all three permitted targets. The camera lease belongs
to `yasinschroeder-codexb2` (3.9 h left), `0x001C2B80` to
`yasinschroeder-claudec` (2.8 h), and `0x001C5E30` to
`yasinschroeder-codex7` (3.8 h, verified locally awaiting publication).
An independent filtered claim listing confirmed these owners. An earlier
overlapping fetch lost `FETCH_HEAD`; the sequential checks completed without
that error, so the blocker is ownership rather than an inferred empty queue.

No claim was acquired, no reconstruction trial was started, and no other
owner's lease was released. The seat23 handoff and picker history were read;
the 0.9741961628516264 bank remains unchanged (SHA256
`f585abbaa3d1d5ef987cdfd827deebefca3c10b4a332114a9145f93f9f7ffb03`).
Resume from the seat23 handoff above after obtaining ownership. No new source
hypothesis has been disproved by this coordination-only check.

The pull and ledger check passed; the published link index fetch added 22,891
reusable objects. The recent BFME 1 update lock still belongs to `codex4`, so
the runner rule requires skipping this update without writing a freshness
success stamp. Production sources, ledger rows and compiler inputs were not
changed; no byte build is warranted for this evidence-only update. The final
`python3 tools/progress.py origin/master` result is reported in session metadata.
