# PolygonTrigger camera: C2 selection and scheduling, 2026-10-23

Target `?adjustCameraMovement@PolygonTrigger@@QAE_NPBUCoord3D@@0PAU2@_N@Z`,
0x002E3AA8..0x002E3D7B, 723 bytes, RET 16. BFME2 input 46bc0001c5;
BFME1 checkout and committed pointer f890413e75e671748215ba2ef3304aa7953993e9.
Ledger check passed. The fresh BFME1 update lock belonged to codex4, so this
seat respected the runner's instruction to skip that update this session.
No Code, ledger, pin, header, verifier, baseline or linked-byte change.

## Result and preserved alternatives

The bank now emits 723 bytes instead of the incoming clean bank's 715.
Normal relocation resolution has no unresolved references; 714 of 723 bytes
agree at the same offsets (bank score 0.9875518672199171). The frame, registers,
stack offsets and every instruction other than one load's position agree.

Bank: `reverse/attempts/0x002e3aa8.cpp`, generated as bar-j00-m01.
`movss xmm0,[ebp-0x0c]` is at 0x2E3D1E instead of retail's 0x2E3D2D,
before three instructions that retail places ahead of it. This is **not** a
matched body. It recovers the historical one-load plateau on the newer
constructor-repaired prefix; it does not establish a new all-history record.
The retained-read qualifiers and compiler barrier are source adapters measured
against retail, not evidence that retail's original declarations were volatile.

The incoming ordinary C++ source is retained as clean-base.cpp.txt (715 B).
no-barrier.cpp.txt emits 723 B with three aligned instruction differences and
11 differing bytes at the same offsets. candidate-load-late.cpp.txt is the
complementary 723 B alternative: z is scheduled correctly, but candidate.x
is loaded at 0x2E3D2D instead of 0x2E3D1E. Both complementary variants have
nine byte differences after resolution. Do not repeat the old barrier family
unchanged; the useful addition here is the C2 phase evidence and the measured
interaction with the current clean prefix.

## Prior evidence and the new hypothesis

Read history only through `/opt/runner/pick-hard --rva 0x2E3AA8`. Reviewed the
20261021 planar-constructor, 20261022 selection-wall and 20261023 tail-selection
handoffs, relevant recipes, and prior C2 lowering/scheduler investigations.
Earlier exclusions include ordinary Add/Scale spellings, control-flow and scope
variants, real base layouts and helper visibility, authentic compiler builds,
and ordinary optimization flags. The old qualifier/barrier bank was already
known to plateau; it was used here as a diagnostic control on the newer prefix.
No missing callee currently blocks the body.

New hypothesis: inspect where C2 chooses the candidate as a folded memory
operand, then distinguish operand canonicalization from register allocation
and final scheduling. Constructor repair makes the prefix exact; testing
actual read intervals on this input can isolate the tail without the old dot
and subtraction residues. Qualifiers model existing component reads only;
the generated families add no dummy runtime calls, predicates or accesses.

## Compiler findings

RTM c2.dll 13.10.3077, image base 0x10700000, SHA256
bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e.
All unmodified debugger runs finish and reproduce the respective untraced
object. trace-checks.json records checkpoints, counts and body hashes.

At +0x5CD11 (the existing FactCanonSort investigation's return checkpoint),
the final x/y additions give product variables larger keys than candidate
variables: x 174/0x115c0 vs 163/0x11460; y 177/0x11620 vs 167/0x114e0.
This is an observed ordering, **not** proof that sorting causes the fold.
Reversing those lists in a debugger at that checkpoint (14 visits) leaves the
715 B output unchanged. Reversing the two final ADD source lists at +0xB0037
also leaves output unchanged. These two mutation experiments are causal
diagnostics only; their objects are inadmissible and were never used as bank
or matching evidence. Only normally compiled C++ candidates are banked.

The ordinary source has selected SSE register/memory operations already at
+0xB0037; simply reversing its ADD list there does not reconstruct absent loads.
Read-only snapshots cover +0xB0037, +0xB003E, +0xB0065, +0xB0079, +0xB0087,
+0xB48E7, +0xB4915, +0xB492F and +0xB493C. For no-barrier.cpp.txt, the final
scheduler call +0x8734C, observed before/after at +0xB299B/+0xB29E0, changes
instruction order while preserving the relevant XMM roles. The z load moves
before the x multiply. Later +0xB2A0B/+0xB2A1D/+0xB2A3A do not fix it.

The snapshot helper records the first source operand recursively, but does
not recursively collect every linked secondary operand. Missing secondary
nodes in a JSON dump are a collection limitation, not missing compiler IR.
Do not infer operand identity from an uncollected pointer. The diagnostic
list reversals explicitly read both operands live.

## Source families

All use /O1 /DNDEBUG /MD /arch:SSE /I., private objects, eight workers per
family; no direct build.compile_source call or shared match-cache pollution.
The exact predicate checks all 723 bytes with ordinary relocation resolution.
nd is normalized instruction alignment only, not the bank's byte score.
Preserved source samples trim trailing whitespace; receipt source hashes name
the original generated trials, with separate preserved-source hashes recorded.

| Family | Compiles | Distinct bodies | Result |
| --- | ---: | ---: | --- |
| Existing-load qualifiers, nine-bit factorial plus baseline | 513 | 362 | best nd 9 |
| Six event orders x eight qualifier masks x 120 declarations | 5760 | 32 | best nd 8 |
| All 2240 valid event orders x four qualifier masks | 8960 | 2789 | best nd 3 |
| All 255 barrier subsets on ten best distinct ordered bodies | 2550 | 232 | best nd 2 |
| Ten retained-load bodies x 120 declarations x eight product orientations | 9600 | 10 | inert |
| Separate z read/use, three paths, four masks, scopes/orientations/barrier | 5376 | 60 | best nd 2 |
| Retail-order path x six masks x eight orientations x 128 barriers | 6144 | 37 | best nd 9 |
| Requested /G5 /GB /G6 /G7 on four controls | 16 | 4 across all controls | each control unchanged |

38,919 completed compiles, zero compile errors, zero exact. G5/GB results
establish only identical requested-command outputs, not that the compiler
accepted each as a distinct internal scheduling mode. Declaration and
commutative orientation changes were completely inert on the ten retained-load
bodies. Separating the z read from its multiply reached the same wall.

Two additional valid intrinsic probes were worse: ordinary __m128 forces
16-byte stack alignment and 834 B; an internal unaligned intrin_type struct
avoids alignment but gives 753 B with extra LEAs/copies. Those sources are
preserved. An initial wrong union declaration produced C4391/C1001 and is not
negative evidence about a valid intrinsic implementation. No full intrinsic
permutation family was run after these structural failures.

## Resume

A useful remaining investigation is earlier SSE instruction selection, before
+0xB0037, using a small extracted scale-plus-add probe and the current clean
source. Determine which candidate destination/load property survives lowering;
canonical operand-list direction alone is insufficient. The two complementary
one-load schedules separate the allocation requirement from its final load
priority. Avoid another unchanged local-numbering, parenthesis, ordinary
Add/Scale, qualifier/order or late-barrier sweep. Real helper/ABI/compiler
exclusions from prior handoffs still apply.

Replay: copy *.py.txt into build/camera-c2-20261023/ as *.py, and copy
clean-base.cpp.txt there as base.cpp. search.py accepts qual, events, orders,
barriers, depend, split, recombine. Run families sequentially: barriers/depend
read orders.jsonl and generated sources. The original events/order generators
remain in this unified replay. For a private body compile, use its run()
helper. diff.py prints aligned differences for object tags.

Read-only traces: early.py late-base base.cpp; trace.py post-base base.cpp;
trace.py end-near <no-barrier source filename>; canon.py <base path> canon-base.
The wdbg ROOT is this checkout's absolute path; change it for another checkout.
canon explicitly supplies base.cpp, not another bank. diag_flip.py and
diag_late.py are debugger mutations for diagnosis only: never admit their
objects. Recompilation of the bank after recording reproduced the receipt.
Claim released for the next session; assignment remains in progress. About
30 minutes, model gpt-6.1-sol.
