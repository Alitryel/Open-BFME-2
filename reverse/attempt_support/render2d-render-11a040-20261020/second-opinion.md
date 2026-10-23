# Render2D::Render second opinion, 2026-10-20

The best bank remains 7476 bytes, fitness 0.9451478802311812, frame EC,
unresolved relocations zero, unmasked. No exact recovery or new Code/ row.
The original bank was reproduced before and after the BFME1 pointer update.
Do not replace it with the diagnostic patch merely because fewer instructions
differ: the patch's resolved-byte fitness is lower.

## Strongest continuation: copy allocation recovered

`second-opinion-copy.patch` is the more promising continuation. Apply it to
the bank in scratch, then use the measurement script below. It produces 7471
bytes, frame EC, region counts **[0,0,18,0]**, ordinary gate-style fitness
0.907071452228971, and zero unresolved calls. The six remaining instruction
replacements are exactly terminator sites 8 through 13:

| Site | Retail offset | Remaining replacement |
| --- | --- | --- |
| 8 | 0xd01 | buffer-first ECX/DL versus terminator-first CL/EDX |
| 9 | 0xd85 | buffer-first EAX/CL versus terminator-first AL/ECX |
| 10 | 0xe02 | same |
| 11 | 0xe87 | same |
| 12 | 0xf09 | same |
| 13 | 0xf86 | same |

The bank's first-copy receiver, batch induction variables, run loop, EH-store
scheduling and second-loop EBP/EDI roles now all agree at the instruction
level. Resolved bytes before 0x7e0 differ only at offsets 0x2c and 0x7d6:
both are forward-branch displacements to the tail, five bytes earlier because
of the five short AL-form loads. Site 8 uses CL, so its wrong ordering does
not change length. No padding was added. The instruction diff is preserved
in `second-opinion-copy-diff.json`.

The enabling interaction was to replace Get_Transform's VIEW and PROJECTION
transpose-result assignments with the same explicit scalar stores already
used in the bank's Set_Transform WORLD/VIEW specialization. With both gets
expanded, the real ShaderClass default ctor/setters no longer add the extra
64-byte matrix region. On this base, the branch-form index accessor fixes
the run allocation without swapping EBP/EDI in loop2; using Vertices.Get(0)
for the first memcpy then recovers the remaining copy allocation. The patch
also uses WB's viewport shape, the plain string terminator, and the RS
cache-pointer/old-value locals. These interactions were not established by
the earlier isolated trials.

The scalar transpose expansion is supported by the operation's definition
and target accesses. It is a reconstruction choice, not proof that this was
the original target header spelling. The shader setter sequence is supported
independently by WB as described below.

Measurement limitation: build.compile_function copies retail DIR32 bytes at
the compiled relocation offsets, even when its `masked` result is false.
Consequently its fitness for an offset-shifted candidate is position-sensitive;
it is not an independent aligned data-address check. The diagnostic instruction
alignment also normalizes absolute operands and branch/call destinations.
Neither metric alone proves a full match. The existing bank remains the best
under the same ordinary fitness metric; retain both patches as continuations.

## New finding: the late RS+next forms are changeable

Giving Set_DX8_Render_State a local cache pointer and a local old value makes
sites 23 and 24 use retail's N form. Thus the earlier unconditional RS+next
rule is false. The change also makes site 11 N, leaving sites 11/12/13 wrong:
7473 bytes, region counts [0,43,9,0], resolved fitness 0.9111410271492482.
The emitted state-cache loads/stores themselves remain the same.

Combine this with the actual WorldBuilder viewport shape (assign Width/Height
directly from the getters, without width/height locals) to retain B at site 11:
7474 bytes, [0,43,6,0], resolved fitness 0.9150442214790041. Only sites 12/13
remain wrong in loop2, at retail offsets 0xf09/0xf86 (11af49/11afc6). Each is
the three-instruction terminator store, N instead of B. Sites 23/24 are now
correct. The missing two bytes come from these two A0-form loads; no padding
was attempted. Copy allocation is still the bank's 43 differing instructions.

`second-opinion.patch` derives this candidate from the bank. It changes only
the viewport locals and the RS cache expression. It is diagnostic evidence,
not an admitted source. `second-opinion-measure.py` compiles a supplied candidate
to a private object, reports the four region counts and terminator sites, and
can resolve relocations and report the ordinary byte fitness with --resolve.
Its instruction counts normalize branch destinations and absolute operands:
they locate residue but cannot prove a byte match. The full gate is decisive.

## Trials completed; do not repeat individually

- Declaration scopes: hoist b/mode or head/run; batch reference to pointer;
  inline/forceinline helpers around fallback and dot3 state sequences. Inert.
- Factorial copy choices: signed counts, signed index with unsigned bounds,
  exact WB startIdx local, for-header linked-run advancement, source/count
  memcpy locals, branch accessor, genuine STLport vector. No improvement.
  The actual vector needs <vector> before always.h and
  _OPERATOR_NEW_DEFINED_ to avoid duplicate placement-new definitions. It
  yielded 7475 bytes and [0,43,15,0] at best, without recovering copy registers.
- Real struct member types (Vector3 position, Vector2 UV[2]), unsigned run
  fields, ShaderClass member instead of unsigned, union data-pointer view,
  explicit vertex-data local. No improvement. The explicit local changes
  matching regions substantially.
- Pointer-return index accessor and signedness combinations reproduce the
  known index-loop improvement but retain the bad global register allocation.
  This measurement counts [0,32,77,11] at 7549 bytes; the prior handoff used
  a slightly different alignment count. Neither is byte-exact.
- Faithful Vertices.Get(0), Indices.Get(start), removal of equal-arm VB/IB and
  batch-index expressions, for-header advancement, crossed with the RS-cache
  change and plain/named terminators. No improvement over the bank. Removing
  multiple scaffolds changes the first region too.
- Const run/batch references, const array accessors: inert. Explicit
  Peek_Buffer()/const-char-pointer snapshot arguments: inert. Moving state-name
  calls into locals changes call order and worsens the body.
- RS/TSS old-value and cache-pointer choices, both terminator forms, both
  viewport shapes: the best loop2 result is the patch above. Cache references
  instead of pointers produce the same results. A plain terminator fixes some
  sites while making too many later sites B.
- Private StringClass header copies: const static NullChar, Peek_Buffer store,
  reference-return Null_Char accessor, body assignment instead of initializer.
  All inert except the known plain/named distinction. A const local terminator,
  reference terminator or unsigned-char local also stays identical. A local
  buffer pointer/reference plus terminator worsens the site pattern.
- Actual ShaderClass constructor and setters, following WB's call sequence,
  were tested independently for global setup and mode overrides, with closed
  shader scopes, short-lived copies, Get_Bits comparisons and value/reference
  Set_Shader forms. In these standalone trials they introduce an extra 0x40 frame region and worsen the
  body; closing the shader block does not remove it. Direct setters remain a
  possible source-shape lead, but no tested form fixes the copy residue.
- /Oa and /Ow, separately and together, crossed with the branch accessor and
  actual shader form: worse across multiple regions. Extending identity's
  scope is inert on each base. Do not carry these alias settings forward.
- Moving array fields/accessors into a base class, with either the storage
  prefix or all fields in the base: inert on the corresponding expression
  bases. This does not recover an original PlainDataVectorClass declaration.
- WB 9a0990 is a bool conversion (cmp pointer, setne, return AL), not a pointer
  getter. Adding a real Get() or pointer/bool conversion to BFME2TextureRef
  initially adds the same 64-byte matrix region as the real shader. The
  explicit-transform interaction above removes it. The bool conversion does
  not improve the six-site residue on the recovered-copy base.
- On that recovered-copy base: all four RS and TSS cache forms (direct,
  old-value local, pointer local, pointer plus old value), plain/named string
  terminators, manual/real shader portions, bool conversion; removal of the
  equal-arm count/index scaffolds, memcpy source/count locals, WB startIdx.
  No tested combination fixes the six sites. The TSS expression includes
  `(unsigned int)state`; a first shader factorial's TSS toggle missed that
  spelling and was inert, then the 256-case cache factorial tested it correctly.
- Also on this base: direct constant ShaderClass ctor instead of default
  Reset, and StringClass ctor plain/named/const-char/buffer-pointer/char-reference
  stores, a real Store_Null inline, initializer versus body assignment,
  size/speed pragma removal or reversal and forceinline. None improves it.
- Replacing groups of Reset's nested setter calls with those setters' exact
  field operations (256 private-header combinations, every field still
  initialized) is completely inert: all yield 7471/[0,0,18,0]. This rules out
  that specific nested-Reset explanation on the recovered-copy base.

The broad factorials have interactions, but the fixed-budget model remains
unproven. The later transform/shader coupling does recover copy allocation;
isolated edits on the original bank did not. No missing callee is blocking
call resolution.

## Target evidence and remaining angles

WB 0x9c07a0 confirms the viewport has no width/height/bits/windowed locals.
It has startIdx after the head guard, a for-header run advance, and pointer
bounds getters at 9c2bd0/9c2e40. Both compare the index unsigned with Count,
return Data for invalid indices, and otherwise Data+index. Their machine ABI
does not distinguish a C++ reference from a pointer return. The whole file's
plain-vector source has not been recovered from a donor.

WB shader construction at 9c0e89 calls a default ctor, then DepthMask(global),
AlphaTest(global), DepthCompare(global), SrcBlend(global), DstBlend(global),
Fog(0), PrimaryGradient(6), Texturing(1), followed by the texture/mode branches.
Masks/shifts in 9ac510/540/600/630/660/690/6c0/720/750 identify the setters.
The BFME1 shader header supplies the names and structural guide; its being
the exact target header is an inference, not established by matching bytes.

Useful next angles:

1. Start from the recovered-copy patch for the next string/inlining hypothesis.
   Copy allocation and shader/matrix coupling no longer need rediscovery.
   The first patch remains useful as a separate two-site loop2 experiment.
2. Distinguish symbol-number effects from a fixed tracking budget. The earlier
   budget model is still not proven; docs/recipes.md describes per-site windows
   and period-32 effects in other functions. Previous dead-local trials do not
   establish that this body's six sites use that mechanism. Never ship padding.
3. Recover the actual StringClass/snapshot inline relationship where target
   evidence supports it. Repeating the ctor store syntax or cache-local
   factorials above on the same base has no new evidence.

Inputs: BFME2 baseline cb5d2432ec plus the three existing local link-repair
commits; MSVC 7.1 and the bank's O2/G7/arch:SSE flags. BFME1 a2c8039e61ad
was the initial pointer; 0dc8a26a9c60 is the updated pointer. Neither revision
changes a header used by the bank. Scratch trials lived under ignored
build/r2d and never touched the shared build/match object cache.

## Acceptance and reference freshness

The initial clean BFME1 checkout a2c8039e61ad was compared with official master
0dc8a26a9c60. The three donor commits change cpp bodies and ledgers only (data
EDI label, Palantir dispatch, MemoryPool::_Init); no donor headers or layout
inputs changed. The migrated game/ and inputs/reference/ paths were already
correct, and all 20 resolved include directories for this candidate exist.

BFME2 full `./build.sh` passed before and after the update, against the same
BFME2 tree and dependency cache: 97324/97324 functions, strings/floats/imports,
DIR32, pins, source claims, 1116 data rows and no-op patch all green. The updated
run reused all 23388 current TU objects. Logs are ignored build artifacts
`build/render2d-freshness-before.log` and `build/render2d-freshness-after.log`.
The same bank fit was reproduced at both donor revisions. The ignored
build/bfme1-last-check.txt was written only after the updated full gate passed.
Broad donor sweeps remain outside this seat's explicit hard-body assignment;
none of the changed donor cpp files is an input to this candidate.
