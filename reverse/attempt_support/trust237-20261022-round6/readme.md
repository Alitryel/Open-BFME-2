# 0x237D3D: unsigned arithmetic and late dead work

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round5/readme.md`. BFME2 input
`36a1a28383`; committed and checked-out BFME1 input `42bba2ddbd`.
Model: GPT-6.1-sol. No Code source, ledger row, pin or baseline changed.

## Hypothesis and results

Read the per-RVA history through `pick-hard --rva`, the prior handoffs and
`docs/recipes.md` before editing. Earlier work covers narrow predicates,
wide/float ranges, loops, EH, SDK layouts, callee visibility, debug options,
barriers and supported-profile LTCG. Do not repeat those matrices unchanged.
The new hypothesis here is that unsigned polynomial, division or bit-ring
identities might retain status through cleanup, then lose arithmetic late
enough to leave padding or the required return order.

| Family | Compiles | Distinct raw bodies | Result |
| --- | ---: | ---: | --- |
| Isolated arithmetic predicates | 184 | 90 | No NOP instruction |
| Full-function combinations | 384 | 39 | No NOP, unresolved call or bank improvement |

The probes use 46 unsigned expressions: products of consecutive values,
division/remainder recomposition, quotient bounds, inverse rotations,
distributivity and bit-ring identities. Crossed with O1/O2 and G6/G7.
They have no object relocations. Unicorn executed each on 152 boundary
and seeded inputs: all **27,968** executions returned one. These samples
are a compiler diagnostic, not an exhaustive proof over 32-bit inputs.
Unsigned wrap, nonzero divisors and shift counts below 32 also matter to
the identities; there is no signed-overflow assumption.

Eight representative status-consuming expressions were carried into the
whole function, crossed with three return forms, predicate evaluation
before/after LocalFree, direct/forceinline form, G6/G7 and flat/nested
scope. The best regional output, `arithmetic-region.cpp.txt` (t0052), is
222 bytes, prefix 205, 21 diagnostic positional differences and 69/86
matching mnemonics. This ties the existing diagnostic counts with a larger
body; it does not improve the bank. It retains real arithmetic after the
matching xor and contains no NOP. `tail-comparison.txt` shows the residue.

## Semantic checks and retained bank

The 384 full objects and independently recompiled bank form **40 distinct
code-and-relocation groups**. A scratch Unicorn harness patched each
relocation by its actual symbol, rather than masking it with retail bytes.
Each group ran on the same 152 status values: **6,080 executions passed**.
The mocked API calls check their count and arguments, the GUID, 16-byte
file and 44-byte trust-data fields, return EAX=1, balanced stack and saved
registers. Calls clobber ECX, EDX and flags. This validates the diagnostic
source under the stated call model; it is not a real WinTrust run or a
byte-admission receipt.

Keep the existing 219-byte bank, score 69/86 = **0.802326**, raw SHA256
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
Independent `variant.py` reproduced 21 differences, first +0xCD.
The sixteen NOPs at +0xCD..DC and return-tail ordering remain unresolved.
These finite trials establish neither universal compiler impossibility nor
an original post-link patch. No missing game callee was identified.

## Reproduce and resume

Copy round5's saved `search.py.txt` and `base.cpp.txt` to
`build/trust237-round5/search.py` and `base.cpp`. Copy this directory's
three `.py.txt` files to `build/trust237-round6/` without the `.txt` suffix.
Use the round4 diagnostic venv with Unicorn 2.1.4 at the path the scripts
declare. Run `arithmetic.py`, then `full_arithmetic.py` from the repo root.
Then run:

```
python3 tools/variant.py reverse/attempts/0x00237d3d.cpp '=?Rva00237D3DCheck@@YAHXZ' 0x237D3D 226 _memset=0x6291ae _WinVerifyTrust@12=0x655652
python3 build/trust237-round6/emulate_full.py
```

Compiles use isolated objects, never `build.compile_source`. Full-function
closeness scores retain the earlier diagnostic DIR32 masking and REL32
map; those scores do not verify relocations or admit a match. The semantic
harness separately resolves all its calls by symbol. `summary.json`
preserves counts, compiler hash and the regional result.

Initial ledger check passed. The shared BFME1 freshness lock remains live
under `claudec2`; the update was skipped and no success timestamp written.
The claim is released on banking. Preserve unrelated untracked
`reverse/zh_sweep/`. Continue this assigned body with a different,
evidence-backed explanation for the remaining NOP span.
