# Rebase reconciliation

Upstream 1df7b97d10 gives native 0x003B693A its ScriptList owner,
independently resolving the initial script-cleanup cause. After the normal
publisher rebase, this seat's old Rva003B693AHolder call names become
unresolved. Full verification reported precisely two caller failures, with
97324 other functions and all 1116 data rows exact.

Restore only this seat's three receiver-view edits to the original ScriptList
declarations and calls. Scoped byte gate:94/94 exact;14 EH rows exact;
declared-definition and whitespace checks pass. Same-index legacy preview
59->715B restores the 656B Player unit; the two Map units retain unrelated
blockers. This is a correction to the initial repair, not another gain.

The initial 656B repair is superseded by upstream, so this seat's retained
independent gain against the rebased origin is3821B (1147+1152+578+394+550),
from five repairs, with no self-strict or closed-strict claim.
