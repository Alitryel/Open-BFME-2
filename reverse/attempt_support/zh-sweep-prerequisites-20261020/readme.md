# Incomplete Zero Hour sweep

Inputs: BFME2 413ecd9e74b1c122e930f26a1f9d3099f4ad6d20; pinned BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790. Model Codex (runtime model not exposed).

Ran the BFME1 lift_lane with limit 1000 and a fresh BFME2 zh_sweep compile
with one worker. Four objects completed: FramGrab, aabtree, aabtreebuilder
and agg_def. The next donor, WW3D2/animatedsoundmgr.cpp, remained at high CPU
for more than six minutes. Its identified compiler child was stopped;
the automatic missing-include retry stalled on the same donor and was also
stopped with its sweep parent. No other worker's compiler was terminated.
The cache is retained and this lane is incomplete, not exhausted.

The completed four-object cache yielded 162 bodies: exact-multi 15/899B,
exact-unique-already-claimed 18/1061B, and near 25/2638B. The subsequent
packets pass produced no unclaimed packet from that partial cache.

Read-only include auditing found a concrete prerequisite defect: this donor
directly includes wwaudio.h and audiblesound.h, but neither the normal nor
retry include roots includes the sibling WWAudio directory. The ordinary
VC7 INCLUDE also lacks PlatformSDK unless explicitly selected. The source,
SDK and audio files exist; this is an include-profile problem. A missing
header normally exits quickly, so this does not establish the CPU stall's
cause. build.py buffers showIncludes output until compiler completion, which
left the outer sweep log empty.

The already tracked reference-zh-sdk-repair-20261020.py.txt lists an isolated
profile for this donor using the real PlatformSDK, DX81, WWAudio and Benchmark
roots before sweep shims. Its presence is evidence of a prior attempted
profile, not a successful compilation. Do not execute it blindly: its root
calculation assumes relocation and it requires an absent historical results
file. Resume with an isolated wrapper, direct child logging and a bounded
process-tree timeout; preserve the donor and check receipts. No global shim,
gate or reference pointer was changed for this failed sweep.
