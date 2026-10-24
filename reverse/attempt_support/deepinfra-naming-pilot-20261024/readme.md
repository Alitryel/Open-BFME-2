# DeepInfra naming pilot, 24 October 2026

Eight independent DeepSeek V4.1 Flash 1017 workers ran through DeepInfra on the
IBM CPU farm, at BFME2 revision 63dff0d8ad with BFME1 pinned at 32774ab03.
Each researcher had a private container/filesystem and a stable worker identity.
The shared source was read-only, inter-container connections were disabled, and
partners received only vote hashes after their independent answers were fixed.
The original workers submitted their own answers through name_lane.py. Original
vote records and their identities were merged unchanged; no votes were invented.

The initial high-reasoning turns exceeded an eight-minute controller timeout.
Docker logs and API receipts preserved their work. The same sessions resumed
with low reasoning and a bounded finish instruction, then the original B workers
submitted their frozen proposals. A controller stdout-on-timeout bug was repaired
in the external farm kit. No project gate was changed.

The run added 22 valid votes and four new agreements. All four combine a fresh
DeepSeek vote with older independent model votes. The fresh DeepSeek pairs did
not themselves converge on these four winning spellings; do not claim otherwise.
The exact model is `deepseek-ai/DeepSeek-V4.1-Flash-1017`, with no provider fallback.

Two parameter renames landed through normal rename.py dry-run/apply and its
byte, dependency, identity and ledger checks: `DelegateDesc::f` and
`MakeBinding::f` become `functorMethod` in Rva005D4913Dtor.cpp. Both parameters
are FunctorMethod member-function pointers; the constructor stores one as method
and MakeBinding forwards it. The unit remains 9/9 matched, with both retail
string literals and float/import checks passing. Prior voter identities remain
in the agreement records; DeepSeek supplied the new tie-breaking evidence.

Two proposed local renames remain blocked: DiscreteCircle::generateEdgePairs
x -> xOffset (nl-9a35be3c8085), y -> yOffset (nl-ce2338f03b0b). The matched body is
0x002DF8CF, 110 bytes. It explicitly declares Int x = 0 and Int y = radius;
these are offsets added to/subtracted from xCenter/yCenter. The planner refuses
because reference/shims/sweep/windows.h also declares unrelated tagPOINT members
x/y: "the function may mean it". Every affected use is lexically under those
local declarations. Investigate this as a false reject in the scope/ancestry
analysis, with regression tests; do not bypass or edit the check in this commit.
The discrete_circle.cpp source has not changed.

Full prompts, immutable source hashes, returned reasoning/tool events, answers,
failed turns, frozen-answer hashes, provider usage and verification receipts are
preserved privately under /mnt/titan_nv3/open-bfme2-agent-fleet/deepinfra-20261024,
and will be mirrored into the existing research archive. No credentials belong
in that export. Research model: DeepSeek V4.1 Flash 1017 (DeepInfra); integration
and semantic review: gpt-6.1-sol.
