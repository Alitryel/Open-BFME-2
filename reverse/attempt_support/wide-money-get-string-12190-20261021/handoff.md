# 0x00012190 wide money_get::do_get (string), round claudeb (2026-10-21)

Continues `../wide-money-get-string-12190-20261020/handoff.md`. The current
bank is another seat's 0.898 (e7ee3c9b6c, per-site `#pragma inline_depth(0)`).
Its residue includes the base-dtor relocation (0xB3C0 vs 0x142D70), and the
funclet finding below explains it: the name the body calls must resolve to
0xB3C0. This round's own best was 0.845, which that bank supersedes.
This round answers which destructor the 13 outlined calls and the unwind
funclets name. A probe (`p5_base.cpp.txt` and its generator `p5_gen.py.txt`)
also measured when MSVC 7.1 outlines a string destructor. The session ended at
the runner's wind-down.

## Target facts (retail and WorldBuilder bytes)

- Retail wide unwind funclets destroy strings with `jmp 0xb3c0`. This holds in
  this body and in the long-double wide do_get (0x75BB40: `lea ecx,[ebp-0x18];
  jmp 0xb3c0`). Narrow funclets use `jmp 0x142d70`.
- WorldBuilder links incrementally (no ICF) and shows the same split. Wide
  funclets go straight to 0x6E4540, a 63 B framed body byte-identical to 0xB3C0
  and the only copy of it in the image. Narrow funclets reach 0x520D50 through
  ILT 0x40BDD9. The 0x6E4540 callers are wide STLport facets plus game code
  (`MultiByteToWideCharSingleLine` 0xE5DF00, 0x1366080, 0x1366BF0). The body
  sits right after num_get<wchar_t> 0x6E42C0.
- WorldBuilder is no debug twin for this body: its wide string do_get
  (0x6EB4C0, 2824 B) and narrow one (2548 B) are the same optimized STLport
  library build, with the same call counts as retail.
- Retail narrow do_get 0x11230: 0 calls to 0xB3C0, 13 inline frees.

## Compiler finding (probe p5, this round)

- MSVC 7.1 unwind funclets name the **derived** string destructor
  (`??1?$S@G@@QAE@XZ`, i.e. `~basic_string`). Outlined calls inside the body
  name the **base** destructor (`??1?$sbase@...`, i.e. `~_String_base`), because
  `~S` inlines into a call of `~sbase`. Measured with
  `build/claudeb/tools/funclets.py` (reloc lister over `.text$x`) on
  `v_tcplali0w.obj`.
- Therefore retail's wide `jmp 0xb3c0` funclets mean
  `~basic_string<wchar_t>` resolves to the framed 63 B body at 0xB3C0. The
  in-body calls are `~_String_base<wchar_t>`, already rowed at 0xB3C0 (row
  90990, fold-proof). Scoring the body itself is unaffected.
- **Suspect ledger row:** `??1?$basic_string@GV?$char_traits@G@...@QAE@XZ` at
  0x142D70 (stlport_wide_money_get_long_double.cpp, "ICF twin of the owner
  row") contradicts the funclet evidence. Its unit's copy is a frameless 14 B
  body only because that TU forces a nothrow `~_String_base<G>`. Moving the
  name to 0xB3C0 is a pin/fold-proof change (AGENTS pin rules); do it before
  landing 0x12190's funclet rows, not as part of the body.

## p5 probe table (one body with 13 cold string sites plus a final exit)

| contract | in-body result |
|---|---|
| `free` nothrow (any proxy/allocator dtor) | all frameless, fully inline |
| `tcpla`: `free throw(...)`, `~proxy` with leak check, `~allocator` | `~S` framed 63 B (= `~sbase`); wide 8 calls / 8 inline frees; inlined sites add EH states |
| `tcplali`: as `tcpla` plus a leak-checking `~allocator` | the 13 outlined calls and the 3 inline final-exit frees, as retail, but with extra inner states 0x10/0x12/0x14 |

- The inline decision uses post-optimization cost; dead IL does not count. A
  hot site (final exit) inlines at a cost where a cold site (early exits,
  conditional temporaries) is outlined. The cold threshold falls between about
  60 and 84 B.
- There is a char/wchar_t asymmetry: under the same contract the narrow
  instantiation inlines where the wide one outlines.

## Open contradiction and next angles

Retail outlines the destructor at 13 cold sites but inlines it at the final
exit with **no** inner EH state. `tcplali` reproduces the split but adds the
states. Untested contracts:

1. A heavy `~basic_string` (or `~_String_base`) whose inlined copy, after
   optimization, has no throwing call left (the inner try state is dropped only
   when nothing in the inlined range can throw). For example, a leak-checking
   proxy dtor whose free folds away at the hot site.
2. `__declspec(nothrow) __forceinline ~_String_base<G>` as in the long-double
   TU, combined with a costly non-inline `~basic_string<G>`. Calls would then
   name `~basic_string`, so the in-body relocations would need the 0xB3C0 name
   fix above.
3. Carry whichever p5 contract gives 13/3 with no inner states into the bank,
   then score with `vd.py ... 0x12190 2802`.

Landing scope (unchanged): 2802 B, retiring gen_asm rows 0x12190 (122 B) and
0x1220A (2680 B) in `Code/gen_asm/d_000112aa.asm`.
