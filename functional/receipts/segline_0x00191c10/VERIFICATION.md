# SegLine renderer differential verification

These scripts compare the retail `SegLineRendererClass::Render` body at RVA
`0x00191C10` with a compiled C++ candidate. They provide bounded behavioral
evidence. They do not replace the repository's byte, relocation, exception,
provider, or link acceptance gates.

## Results for the delivered candidate

| Scope | Matching cases | Compared observations |
| --- | ---: | --- |
| Complete renderer, established fixture corpus | 77 / 77 | All generated vertex and index bytes, draw parameters, recorded callee inputs, receiver state, directly written render state, preserved registers, stack return and FS chain |
| Complete renderer, reduced regression fixtures | 3 / 3 | Nearest-point dot rounding, interior parallel TOP projection, first BOTTOM vertex projection |
| Complete renderer with native subdivision | 3 / 3 | Levels 1, 2 and 7, including native subdivision output points/UV/RGBA, RNG state and subsequent renderer outputs |
| Native versus compiled x87 branch blocks | 66 / 66 | Stored float32 dot and branch decision at the parallel threshold |

The complete renderer results therefore cover **83 input scenarios**. Each
scenario executes both versions. The x87 cases are additional focused block
comparisons. Thirty of those 66 cases distinguish the recovered extended
precision comparison from an incorrect comparison after early float32 rounding.

The candidate compiled for these receipts has a 15,940-byte Render COMDAT; the
retail body is 16,018 bytes. The differing machine-code extent means these results
must not be described as a byte-exact recovery or an accepted repository match.
The receipts retain the relevant object/body or bounded-block hashes, relocation
bindings, and script provenance. The object was deliberately supplied from outside the checkout
to verify the portable `--object` interface.

## Running the checks

Requirements are a compatible Python 3 installation, the packages pinned in
`requirements.txt`, an Open-BFME-2 checkout with its matching tooling, a compiled
candidate COFF object, and the user's own retail baseline. No game executable or
Microsoft compiler is included with these scripts.

The expected baseline is:

```
baselines/bfme2/workshop-vanilla-1.06/files/game.dat
SHA256 f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640
```

From the `verification/` directory, after installing the requirements:

```sh
python3 probe_renderer_differential.py \
  --repo /path/to/Open-BFME-2 \
  --object /path/to/candidate.obj \
  --fixtures renderer-fixtures-77.json \
  --output renderer-77-results.json

python3 probe_renderer_differential.py \
  --repo /path/to/Open-BFME-2 \
  --object /path/to/candidate.obj \
  --fixtures targeted-renderer-fixtures.json \
  --output targeted-results.json

python3 probe_renderer_differential.py \
  --repo /path/to/Open-BFME-2 \
  --object /path/to/candidate.obj \
  --fixtures native-subdivision-fixtures.json \
  --output subdivision-results.json

python3 probe_x87_vdp_boundary.py \
  --repo /path/to/Open-BFME-2 \
  --object /path/to/candidate.obj \
  --output x87-boundary-results.json
```

An `EQUAL` result compares raw bytes and integer state. It does not use a floating
point tolerance. A different candidate may produce different results; inspect
`comparison.first_event_difference` and the paired call sites to locate the first
observable arithmetic difference.

## Relocation handling

The candidate body is loaded from the Render COFF symbol, with its actual
relocations. Function relocations bind through repository symbol identities to
the unique corresponding retail callee in the native Render call set. Audited
globals use their independently established addresses and class offsets.
Literal relocations use the exact bytes of the candidate's literal COMDATs.

**No relocation operand is copied from the retail renderer at the candidate's
offset.** That shortcut would conceal incorrect references while layouts differ.
The receipt lists every binding and its evidence category.

The neutral 16-byte matrix row callback binds to the independently verified
three-byte retail constructor body at VA `0x0087A6A9`. Exception-handler identity
is dormant in these scenarios; no exception is raised and candidate EH metadata
is not evaluated by this probe.

## What executes and what is substituted

Both complete Render bodies execute as machine code under Unicorn. The retail
renderer instructions are unchanged. Native `WWMath::Inv_Sqrt`, `__chkstk`, the
array constructor iterator and the neutral row constructor execute unchanged.
In particular, inverse square root is not replaced with a host-language
`1 / sqrt(x)` approximation.

The graphics device boundary is substituted with deterministic mapped buffers.
Vertex buffer layout is position/diffuse/UV with 24-byte stride. Buffer
constructors and locks provide memory; unlocks capture every written vertex or
index byte. Buffer binds, texture binds, sorting insertion and draw operations
record their arguments. Material ownership and the temporary string allocation
used by shader setup receive explicit, simple contracts. Heap allocation is a
deterministic mapped allocator.

`floor` is a finite-double floor contract returning through x87. The point
transformation boundary records the complete incoming model-view matrix and point
bytes, then applies a documented float32 row-wise transform. It does not execute
the retail vector processor. Therefore the internal model-view matrix comparison
is meaningful independently of that substitute's arithmetic.

The ordinary fixture corpus uses a level-zero subdivision copy contract. The
three separate subdivision fixtures execute the original subdivision utility at
VA `0x00591480`, the native Random3 constructor/operator and the native solid-box
randomizer constructor/Get_Vector. They use zero noise amplitude. Level 2 covers
the frozen RNG branch; levels 1 and 7 use the ordinary global RNG branch. Level 7
also covers two chunks of 129 subdivided points each. Native subdivision's output
count, points, texture coordinates and colors are compared before the renderer
continues.

The x87 block probe executes the original and compiled three-product dot,
non-popping single-precision store, `FABS`, and threshold branch without any
callee substitutions. It asserts that no earlier pop/store changes precision.
The nearly unit input vectors produce a dot just below `0.9f` in retained
precision while its stored float rounds to exactly `0.9f`. This exposes the
otherwise easy-to-miss branch difference.

## Boundaries of the evidence

These runs do not boot the game, create a graphics device, validate rendered
images, exercise exception unwinding, or perform a production link. They do not
prove every input or every initial machine state. The fixtures are finite floats,
zero-initialized emulator stack/heap, and the documented x87 control word
`0x027F` with MXCSR `0x1F80`. Zero input points, nonzero subdivision noise, random
engine initialization, allocation failure and destructive material release are
outside this corpus.

Passing receipts support the recovered arithmetic and behavior under those
explicit conditions. A repository acceptance claim still requires the project's
independent gates and actual provider/data identity review.

## Additional arithmetic and matching checks

The final source also passes the two merge-abort reduction probes. The retained
receipt records 1,582 vector/threshold comparisons (plus the named boundary
witness), 6,332 native/candidate block executions, and zero result-bit or branch
flag mismatches. Run `probe_abort_distances.py` from `verification/` with `--repo`,
`--object`, and `--out` pointing to a new JSON report. This probe checks the exact
retained candidate body hash before using its bounded instruction regions.

Independent instruction tracing checks all 25 normalization reductions, all 30
three-product dot reductions including their SSE/x87 precision kind, and all 12
modelview outputs. The modelview combines Z and Y before X, then adds translation
last. The remaining weighted point/texture/color merge and UV arithmetic were
also reviewed. See `evidence/RESIDUAL_ARITHMETIC_AUDIT.md` and the JSON receipts.

The original four behavior corrections were corroborated with 16,414 native
block cases (zero failures): unsigned timer conversion, paired expansion,
parallel merge projection, and shader gradient bits. Those tests compare the
native operations with the recovered scalar formulas; they are not another
16,414 whole-renderer runs.

The portable compiler helper `scripts/compile_candidate.py` was tested by
staging the packaged source/header in a fresh isolated build directory. It
reproduced the complete 15,940 instruction bytes and all relocations identically.
The configured compiler was MSVC 13.10.3077. The strict extent/byte result is
false. `eh_verify` independently reports one differing byte in the `.text$x`
cleanup handler at retail RVA `0x00768980`. The renderer's stack reservation is
0x6D90, versus retail 0x6D8C. These are remaining matching tasks, not masked
exceptions or accepted differences.

### Reproduce the scoped static arithmetic audits

After compiling, use the newly printed trial directory (which contains the
actual `raw.bin`, original `target.bin`, and COFF relocation records):

```sh
python3 verification/arithmetic/audit.py \
  --trial /path/to/new-trial --out normalization-results
python3 verification/arithmetic/dot_audit.py \
  --trial /path/to/new-trial --out dot-results
python3 verification/audit_matrix_arithmetic.py \
  --trial /path/to/new-trial \
  --trace-module verification/arithmetic/audit.py \
  --out matrix-results.json
```

The dot scanner records possible component mappings when stack slots have been
reused. The 30-site evidence table supplies the independently confirmed labels;
its initial TOP/BOTTOM output cases use the manually traced point/direction
fields. Do not accept an arbitrary mapping just because it agrees with a target.

To rerun the original four semantic-block probes from the package root:

```sh
python3 verification/probe_native_blocks.py \
  --repo /path/to/Open-BFME-2 --output native-block-results.json
```

The packaged native-block and static-tracing scripts were rerun after their
portable path handling was prepared. The corresponding packaged receipts are
included alongside the original development receipts.
