# WorldBuilder center cleanup: correction to older handoffs

The WorldBuilder twin at VA `0x010F6160` has an unwind action for its
12-byte center coordinate. The claim in `../queue-supply-truck-20261023c/readme.md`
that state 0 belongs to the command-parameter temporary is incorrect. The
archived history in `../queue-supply-truck-20261023-team/history.md.txt:74`
repeats that claim; it is not an independent confirmation.

Direct decoding of the local WorldBuilder image establishes:

| EH state | Previous state | Action | Object |
| --- | --- | --- | --- |
| 0 | -1 | `0x01CC9B80`: `lea ecx,[ebp-0x80]; jmp 0x0040BA05` | Center coordinate |
| 1 | 0 | `lea ecx,[ebp-0x1C0]; jmp 0x00CA4290` | On-map filter |
| 2 | 1 | `lea ecx,[ebp-0x1B4]; jmp 0x00CA42F0` | Player filter |
| 3 | 2 | `lea ecx,[ebp-0x184]; jmp 0x00AECC80` | Kind filter |
| 4 | 0 | Clear bit 0 of the static guard at `0x0225FA9C` | Static initialization |
| 5 | 0 | `lea ecx,[ebp-0x364]; jmp 0x00AE5890` | `AICommandParms` temporary |

Handler `0x01CC9BE9` selects FuncInfo `0x020F6364`, which has nine states.
States 6/7 release failed new-expression allocations; state 8 cleans the string.
The state-0 jump at `0x0040BA05` forwards to `0x00419060`, an empty instance
destructor. The three center words occupy `[ebp-0x80]`, `[ebp-0x7C]`, and
`[ebp-0x78]`. Ghidra's decompiler labels them `local_84`, `local_80`, and
`local_7c` because its stack naming includes a four-byte bias.

Thus the earlier 20261022 handoff's center-lifetime interpretation was the
correct one. The later attribution to the command-parameter object conflated
two different states and object homes. This identifies the cleaned object and
empty destructor behavior; it does not establish a particular original C++
destructor spelling.

Retail game.dat still has five states, beginning with the on-map filter, and
no surviving center cleanup. An empty destructor can disappear under
optimization. Prior empty-center-destructor trials did not fix the retail
match, so this correction is evidence for source lifetime, not a recovered
function or proof that this is the remaining allocator cause.
