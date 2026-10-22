# Wall canMake: factorial controls and EH comparison

`AIBuildableWallSegment::canMake`, RVA `0x00596E15..0x00596EEF`,
218 bytes through `RET 4`. The existing best body remains
`reverse/attempts/0x00596e15.cpp` (204 bytes, historical bank score 0.886).
No source, row, pin, compiler contract or bank was changed. All earlier
verdicts were read using the assigned pick-hard history command, along with
their linked handoffs and the complete current home and bank.

The new useful constraint is `eh_verify.verify_row(...) == ('EXACT', '')`
for the baseline object. Its reachable EH sections, including the handler
and unwind action, already agree with retail under that check. This does
not make the 204-byte main body a match. Retail has separate failure/success
destructor calls, failure values in ESI, and `xor eax,eax` after success
cleanup. The bank merges those exits, shares the constructor's EBX zero
with its return value, and stores the cache before the shared state change.
The prefix through the saved quote Boolean agrees except for the early
epilogue jump displacement. The ordinary mismatch tool confirms 204 versus
218 bytes and the first displaced jump at +0x23.

The WB twin at `0x015386C0` was reread with `wb_show.py --gd`. Its independent
locals are startNode, the 24-byte quote, the failed Boolean, the 12-byte
position temporary, and five return temporaries. Its inline money/cost
reads and cache store support the existing bank, rather than additional
source locals. Retail's installed table at `0x00870AF0`, slot 13, contains
VA `0x00996CC7`: that 24-byte position provider is already matched in
`VslotSmallBodiesJ.cpp`. It copies the three words at this+0x40. Its first
word's x87 access is established; the existing row intentionally leaves
the other words and original return type opaque. The Coord3D-return body
used below is a diagnostic structural interpretation, not a new identity.

Before editing, the earlier disproved trials were enumerated: ordinary
branch/switch/scope rewrites, WB literal getters, scalar/enum return forms,
known-zero expressions, volatile cache stores, destructor visibility in
the baseline, constructor ordering, three compiler maintenance versions,
and the 216-byte post-cleanup cost-store form. New tests combined controls
and examined representations not covered by those individual trials.
`receipt.json` records extents for 1,854 compiled source variants:

| Family | Variants | Result |
| --- | ---: | --- |
| Inline quote wrappers, cached-return helper, declaration context | 64 | 204-byte forms unchanged; 32 whole-body helpers did not inline and were excluded as unresolved-call diagnostics |
| Inert int/const-int locals, k=0..64 at four declaration positions | 520 | All 204 bytes; no instruction or register gain |
| Value/reference cost, status and money getters; setter; inline tail helper; packing | 144 | 204 or 213 bytes; no better tail |
| Real destructor body in-class/before/after, inline controls and constructor order | 54 | 204, 242 or 299 bytes |
| Ow/Ot/Zi/Oi, position temporary, diagnostic function exception spec | 128 | No improvement; Ot/exception variants diverge substantially |
| Six single-iteration loop forms, failure exit/success scope, cost and cache aliases | 96 | 204..223 bytes; post-scope costs retain a live register |
| Count/cost/status/ID/flag/money types | 64 | All 204 bytes |
| Visible installed-position getter model, override/inheritance, call throw specs, function order | 96 | All 204 bytes after correcting 12 generated return-type errors |
| Quote output/reference/void pointer, argument references/pointers, constness and Boolean width | 192 | All 204 bytes |
| Post-scope cost combined with actual destructor visibility and failure joins | 96 | 214..247 bytes; no native store-before-cleanup tail |
| Single/pair value wrappers and conversions at success/failure returns | 112 | 204..223 bytes; no exact body |
| Four 32-bit bit-field representations, initializer list, pair return and failed/code locals | 256 | 204 or 209 bytes |
| Inline destructor calling a separately declared cleanup operation | 32 | Same 204-byte code after relocation masking |

Some combinations intentionally overlap controls from earlier work; their
interactions, rather than another isolated spelling, were the hypothesis.
All corrected variants compiled. None matched. Full-width bit-fields retain
the observed layout; no new target type is asserted. The ordinary-cleanup
probe temporarily maps its invented method to the existing destructor RVA
inside the scratch scorer only. Its masked code hash equals the baseline;
it provides no identity, pin or recovery. Diagnostic `throw()` contracts
were not established for production. `/Gy-` was ignored by this compiler
command path, so that matrix bit provides no compiler-setting evidence.

The original scorer copied DIR32 operands positionally, as the mismatch
tool does. After a length divergence that corrupts the displayed FS:[0]
operand; its normalized difference counts and raw fitness are secondary
ranking aids only. It also picked the first of the destructor's two legal
addresses, making the cleanup-operation probe appear to score better.
The latter emits the same code, not an improvement. The retained replay
uses observed data addresses, FS:[0] and the actually called destructor
address consistently. No scorer result substitutes for the full gates.

Run from the repository root:

```sh
python3 reverse/attempt_support/canmake-00596e15-20261022/replay.py.txt --list
python3 reverse/attempt_support/canmake-00596e15-20261022/replay.py.txt baseline
# Supply individual family names from --list when a new hypothesis warrants it.
```

It regenerates standalone sources under `build/canmake-replay-20261022`,
using eight workers, the project's compiler command and isolated object/PDB
paths. It never writes the shared match cache. Baseline cleanup removes
only the old dead AsciiString block/register-zero annotation, resolves the
home-relative includes, and uses the current failBuild spelling. The bank
hash and input revisions are in the receipt. The replay's baseline was
compiled and checked; the family generators are the executed trials with
the noted return-type correction. Future bank changes require reviewing
the substitutions before reuse.

Checks: ledger validation passed; the unchanged production home passes its
declared-definition check and `./build.sh AIBuildableWallSegment.cpp`
(2/2 matched, source/string/float/import checks). The published index was
fetched. BFME1 freshness was due, but the prescribed live update lock was
owned by claudec2, so this seat skipped that update and wrote no success
marker. The current committed and checked-out donor pointer agree.

The remaining task is still the main-body cleanup/coalescing decision.
All five required reassessment angles received concrete trials: control
flow/loop entry, variable lifetime/declarations, types/layout, callee
visibility/inlining, and compiler settings. No missing callee blocks
compilation. Keep the existing bank rather than a worse two-tail candidate.
Do not rerun these matrices unchanged. A further attempt needs a new
explanation for retaining the separate success exit while storing the
cost before destruction. Model gpt-6.1-sol; approximately 35 minutes.
