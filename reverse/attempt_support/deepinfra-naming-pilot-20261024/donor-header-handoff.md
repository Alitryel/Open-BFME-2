# Pinned donor-header discovery: finishing prerequisite

The circle-local refusal is caused by header discovery, not a proven capture.
`header_closure` indexes only `Code` and `reference/shims` main-repo paths.
The source explicitly includes the BFME1 gitlink's tracked
`game/GameEngine/Source/Common/discrete_circle.h`, which declares DiscreteCircle
without a base. This header is omitted, so class_ancestors reports the owner
unknown and conservatively counts unrelated tagPOINT fields. The same scanner
proves the source-local TerrainResourceManager complete, and its analogous
circle-offset locals renamed successfully under the unchanged checks.

A DeepSeek high-effort engineering draft is preserved in
`rejected-donor-header-draft.json`. It is NOT a verified or installable repair:
it loses the popped includer and incorrectly resolves against frontier[-1],
omits its promised regression test file, lacks subprocess timeouts, and adds an
import already present (the initial excerpt did not show the import list).
Two corrected-draft requests hit bounded response deadlines; their requests,
partial accounting and reviewer feedback are retained in the private run archive.
No checker, whitelist or baseline changed, and no circle-local rename was forced.

Resume by resolving genuine explicit quoted headers under committed gitlinks,
checking the pinned checkout and exact tracked header blob. Reject or ignore
dirty/untracked, mismatched-pin and escaping/symlinked inputs. Retain basename
widening for Code/shims and every existing scope/member/macro/capture guard.
Track the actual popped includer. Add real regression fixtures, including nested
relative donor includes and all failed trust cases, and keep every
`tools/tests/test_gate_exploits.py` exploit refused. Land a separate
Verifier-Change commit before retrying the two recorded circle agreements.

This is a scope-limited research handoff, not progress credit for repaired gates.
The external farm kit, controller failures, all attempts and model/tool records
remain under the private research archive. No credentials belong in that data.
