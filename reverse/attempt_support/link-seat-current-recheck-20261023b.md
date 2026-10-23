# Link-seat current-object reassessment, 2026-10-23

At BFME 2 `80954c1c28`, no new repair was established: +0 authored C++ bytes
and +0 newly linked bytes. No source edits, speculative pins, claims, or
nonmatching trials remain. This is a bounded seat handoff, not evidence that
all repository work is exhausted. Existing banks remain the starting points.

Fetched the published census index and objects: `0393df10e2`, 2026-10-23
19:47 UTC. Checked `link_rank.py --top 30`, `--near 2`,
`class_views.py --blockers`, and `repair_queue.py link --limit 12`.
Reused the prior read-only current-object probe for unclaimed, current-cache
units with 1-5 blockers and at least 100 census bytes. It retained 29 failed
previews (7,179 census-sized bytes), including stale-provider failures that
disappear when their current providers are passed together. The probe changes
only its in-memory index. These are legacy previews; no self-strict or
closed-strict improvement is claimed.

Current `link_check.py` confirmations:

* GameLOD and FormationTemplate already link, 572 B and 917 B respectively.
* PoisonedBehavior constructor/destructor already link together, 190 B.
* W3DView_Rva0008BB27/View and tree-insert/map-index pairs already link,
  1,962 -> 1,962 B. Moving their rows would establish no repair.
* The narrow num_put unit remains blocked on the mutable range initializer;
  prior evidence identifies the apparent BF90 pin as the wide identity.
* Rva002611F2Ctor remains blocked on its PartitionFilterRejectBuildings table
  and provider ABI. The predicate source is absent from this census index;
  its paired preview refuses it. The constructor alone is only 84 B.

Other retained prerequisites include Rva008314E0StringReplace helper codegen,
DX8Skin's Vector3 destructor, unrecovered mesh/VisRasterizer callees, shader
and filter singleton ownership, native vtable contracts, and private class
reconciliation. Read the earlier handoffs and attempt records before trials;
no new evidence here reopens their rejected variants. Many large families
are held by other seats.

`name_globals.py --dry-run` proposes zero rewrites. The current 100 rehome
pairs are a subset of the prior completed 101-pair scan (three exact
placements). Stopped a redundant read-only rescan after confirming that
relationship; the unclaimed exact placements were rechecked above. The
remaining exact EntryCtor placement's home is foreign-claimed. No matching
measurement artifact was available for data-back ranking. No maintainer-only
runner was started.

Correction to the earlier link-seat-index-recheck handoff: BFME 1 pointer
`f5140c1cff6a58e16276fd6de6788186286953d4` is now verified and committed by
`7d17f2fc38`; see `bfme1-reference-f5140c1c-20261023/readme.md` for paired
full gates and identical EH results. The old pointer-update blocker is gone.
Fetched official upstream `8964e30d91f3e69642b0455abff1fd2a79496a64` and
reviewed its new string/STL linking repairs; no fresh directly applicable
repair was identified. Retained the clean verified f5140c1c checkout rather
than advance to unverified inputs. No freshness success stamp was written.

`check_csv.py` passes (98,192 function rows, 15,771 symbols, 2,175 data rows).
`progress.py origin/master` reports zero coverage and census linking deltas.
Local diagnostics are under ignored `build/link-seat-*`, notably
`live-reassessment.txt`, `current-probe-rest.json`, `table-before.txt`,
`now-probe.txt`, `rehome-current-confirm.txt`, and `current-session-progress.txt`
(each with the `link-seat-` prefix).
