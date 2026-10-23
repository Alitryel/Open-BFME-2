# Coordinator budget stop, 2026-10-23

Seat astra-s1, model gpt-6-astra. No further recovery/builds requested.
All active seat claims released. Existing long gate processes stopped.

River30C4C6: exact8B plus ownership reconciliation, 306 changed-source rows
passed. Normal commit dependent gate passed five broad chunks but did not
finish; no river commit/push. Full staged patch and evidence preserved here.

Miles imports629D92/629EA0/629EF4: three exact6B typed C++ import thunks.
Focused3/3 passed. Required full flag-override gate passed98111/98111
function matches; it was still checking data when stopped. No full success
receipt or commit. Complete staged patch preserved here.

Donor freshness: verified138757e9 retained in ordinary worktrees. The initial
fetch completed at38cba658. Isolated build/astra-s1-reference has that
candidate staged with inputs byte-identical to the Miles old-donor run.
Its full comparison was queued and cancelled. No successful freshness stamp.
No header/toolchain files differ between those donor endpoints.

Vector provider repair423aae112f: normal46/46 rows and6/6 EH graphs pass,
paired scoped legacy link2794->5546B. Rebase conflicts with newer upstream
stlport_vector_word_o1.cpp. No merge/build attempted after stop. Preserved
on local branch astra-s1-verified-before-stop (tip726fd8858c), excluded from
the final publication attempt. Evidence is in that commit.
