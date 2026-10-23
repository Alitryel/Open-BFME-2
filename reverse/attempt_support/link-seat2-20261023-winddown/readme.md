# Link-repair seat handoff

Model: gpt-6.1-sol. Started from BFME 2 `88983ceb42`; published census
`456ce161c5` (2026-10-23 06:28, retail-truth-4), fetched with
`link_check.py --fetch-index`. No source repair retained and no link gain claimed.
The runner requested wind-down before another candidate was claimed.

## Verified trial

In `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_substring_ctor.cpp`,
declaring `_String_base<char, allocator<char> >::_M_throw_out_of_range() const`
without a local definition removed that helper's COMDAT conflict. All four
matched bodies remained byte-exact under `./build.sh`. A current twelve-provider
`link_check.py` cohort still linked zero bytes: the kept const-range constructor
and mutable `__uninitialized_copy` providers were independently non-retail.
The source change was reverted. Existing copy-summary evidence (attempt 82078)
still applies; no new source candidate needs preserving. All five claims were
released, and the final owner-filtered claim list was empty.

## Queue checks and remaining leads

- `check_csv.py` passed. `link_rank.py --top 30 --near 2`, a wider top-100 rank,
  `class_views.py --blockers`, and `repair_queue.py link --limit 8` were reviewed.
  A current-object preview of 658 existing, unclaimed near-link source units
  found 58 linking units (12,982 legacy bytes), all inherited improvements;
  those are not session credit. No self-strict or closed-strict gain is claimed.
- Large remaining causes include the documented narrow-string provider and
  hash identity blockers, Eva compiler summaries, and CreateAHeroData vtable
  identity. Avoid repeating their unchanged banked trials.
- GeometryInfo's missing `LoadPostProcess` definition is a concrete follow-up:
  its retail table at RVA `0x007C4E94` contains targets `0x00050C31`,
  `0x000B3FD0`, `0x00050C2B`, `0x006C0030`. The no-op body `0x000B3FD0`
  was claimed by another worker awaiting publication; no edit was attempted.
- `name_globals.py --dry-run` on the inspected shader, map-cache and timer
  sources produced no rewrites. `rehome_rows.py --limit 15` could not run
  because the published index lacks `build/link_census/census.log`; no census
  was started. This is a missing secondary artifact, not an empty-work result.
- BFME 1 remains at verified pointer `138757e9b74645fbcbb7724a7af2764e34931e11`.
  Official upstream was fetched at `38cba658aa0945145c3c8afd422a921f44636c2b`;
  another worker holds the submodule claim. Donor linking commit
  `c20e733a1574ca4a09df3cc4a1153c02b06fd2eb` was reviewed: most declaration-only
  wrapper repairs were already inherited. The existing verified-pointer report
  is `reverse/attempt_support/bfme1-reference-138757e9-20261023/README.md`.

Local diagnostic output remains under `build/seat-*`. Before publication,
`progress.py origin/master` reported zero linked-byte delta; its -24 C++ byte
delta reflected the upstream strlen recovery absent from this checkout, not a
session source change.
