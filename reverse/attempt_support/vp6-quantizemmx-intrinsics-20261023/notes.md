# VP6 quantizer: genuine unsigned-high MMX prepass

## Identity and allowed inputs

Whole TU `Code/Libraries/Source/VP6/QuantizeMmx.cpp`, sole body
`_VP6_quantize_mmx`, retail RVA `0x001C4A70`, 539 bytes through the RET at
`0x001C4C8A`. Identity, ABI, tables and arithmetic come from
`reverse/vp6_cleanroom/specs/001c4a70.md` and the retail bytes. No external
decoder source was read. The previous attempt record was the original
inline-MMX landing; no prior intrinsic bank was found for this body.

Input HEAD was `05207ac05415ed38309aceb744085f11cf2fe8fa`.
The parent integrated the three earlier seat banks separately during this
attempt; no child rebase or publication was attempted. The child BFME1
gitlink and checkout both remained
`138757e9b74645fbcbb7724a7af2764e34931e11`. Retail image SHA256:
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.

## Independent source hypotheses and results

All trials replaced the entire prepass assembly with real MMX intrinsics,
preserved the existing scalar DC/AC dead-zone logic, and used the normal
scoped `./build.sh` through the unchanged isolated OrbStack seat runtime.
No compiler invocation bypass, artificial locals, volatile, helper calls,
EMMS, source pins, alignment padding or assembly was added.

| Trial | Genuine variation | Emitted body | Result |
| --- | --- | ---: | --- |
| 1 | Common byte offset, original flags | 474 B | Wrong frame, scalar allocation and loop addressing |
| 2 | Typed source/candidate/output cursors, fixed end pointer | Not retained | Byte gate failed; arithmetic sequence preserved, pointer increments replace shared index |
| 3 | Cursor loop, real candidate/run aggregate | 511 B | Run acquires memory home but is promoted again across scalar work |
| 4 | Trial 1 with admitted `/Oy-` | 512 B | Correct return-address-copying prologue, smaller frame and wrong scalar allocation |
| 5 | Trial 1 with admitted `/Og-` | 1238 B | Spill-heavy expansion, not retail |
| 6 | Trial 3 with `/Oy-` | 511 B | Correct 0xA8 frame and candidate at EBP-0xA0; scalar/run ownership still wrong |

Original flags: `/O2 /G6 /Z7 /MD`. Only scoped trial builds were run;
no full-tree flag/header gate was started. `/Oy-` is a real independent
frame explanation: `/Z7` alone did NOT retain the native prologue after
assembly removal. Candidate sources retain the original introductory
assembly comments as historical context, not accurate descriptions of the
banked intrinsic bodies.

`candidate.cpp.txt` preserves trial 4 with the simpler unaggregated state.
`grouped-state.cpp.txt` preserves trial 6, which independently closes the
native frame size and candidate-array location. Neither is production-ready
or byte-exact. Corresponding whole-symbol disassemblies and retail are
included; COFF relocation slots in candidate disassemblies are zeroed by
the existing readback utility and must not be treated as resolved addresses.

## Concrete remaining differences

Retail loads row/DC multiplier and spills row, rounding pointer, multiplier
pointer, and run before entering the prepass. It keeps the byte induction
in ECX, coeffs in ESI, candidate in EDI, output in EAX. The arithmetic uses
MM0 value, MM1 sign, MM2 rounding, MM3 multiplier and MM7 zero; ADD/CMP follow
both stores. No EMMS is present, and no calls occur in the body.

All observed intrinsic trials use MM4 zero, not MM7; arithmetic operations
and the MM0-to-MM1 MOVQ encoding do otherwise agree. Trial 4 rewrites the
three-array common-index loop to candidate-relative pointer differences,
reloads those differences, and schedules ADD/CMP before the final XOR/SUB
and stores. Trial 6 uses independent cursors; it gets the exact first 28
prologue bytes and EBP-0xA0 candidate location, but run lives at EBP-0x20
and is promoted into ECX after DC. Retail run is EBP-4 throughout the
scalar stage, and retail row is reloaded from EBP-0x10 rather than retained
in ESI/EDI. Thus this is not merely a single MMX register-number mismatch.

The original inline-assembly region changes integer clobber/lifetime
constraints as well as vector allocation. The experiments do not prove
that every genuine C++ shape is impossible. Further work needs independent
evidence for preserving these real lifetimes/alias relationships and
allocation, not dummy vectors to force MM7, volatile to manufacture spills,
or arbitrary wrapper functions. Callee-visibility recovery offers no
existing retail call to restore here.

## Arithmetic validation and limits

An independent integer model exhaustively checked all 65,536 signed-16
coefficient encodings with each combination of rounding word
`0,1,32767,65535` and multiplier word `0,1,32768,65535`: 1,048,576 cases
passed. The model compares wrapping16 XOR/SUB absolute value, wrapping16
rounding, unsigned product high16 and wrapping16 sign restoration with a
direct magnitude/product description. It includes coefficient -32768.
This is arithmetic-model validation, NOT execution of either compiled
function, and does not establish whole-function alias or MMX-state parity.

The compiler header establishes `_mm_mulhi_pu16` as the genuine unsigned
high-word multiply intrinsic. The four values use wrapping packed-word
operations; using signed high multiply or adding EMMS is not equivalent.

Verdict: blocked byte-exact hatch removal, zero coverage/hatch gain. Restore
the original whole TU and verify its 539-byte body before committing only
this evidence. Keep this bank separate from the existing matched-row ledger;
do not replace the production body with a nonmatching candidate.
