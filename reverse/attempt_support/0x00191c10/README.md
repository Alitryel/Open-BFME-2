# SegLineRendererClass::Render 0x00191C10 (16,018 B): handoff 2026-10-20

Banked body: `../../attempts/0x00191c10.cpp`. It compiles to 16,018 B with frame
0x6D8C and the retail EH (maxState 2). 3574 of 3597 retail instructions are
exact when aligned, and 3576 when ebp offsets are masked. Same-offset bytes are
12,305 of 16,018, because one first-endpoint x87 sequence is 4 bytes short and
shifts the code until the next alignment pad. No row, pin or Code/ change was
made.

Its `// cl:` line puts `reference/shims/banked_segline_bfme2/dx8wrapper.h` first. That header is the BFME 2 view
of DX8Wrapper:

- Get_Transform has the shape of retail's out-of-line copy at 0x000768FE.
- Set_Transform stores the matrix before the flags, and its projection case
  keeps DeviceProjectionMatrix, as in VertexMaterialClass::Apply 0x0013D570.
- Set_Material and Set_Shader have no SNAPSHOT_SAY. Set_Shader keeps its
  `StringClass str`.

It is a copy of the scratch shim this work was scored with. It differs from
`reference/shims/banked_segline/dx8wrapper.h` only in those functions.

## Source evidence (target facts)

`python3 tools/wb_show.py 0x191C10` pairs Render with the WorldBuilder debug
twin at 0xA454A0 (13,402 B, /Od, no EH frame). The twin fixes the text:

- Its callee census matches our /Od compile call for call: 59 V3 copy/=,
  30 Dot, 25 Normalize, 20 V3*f, 16 V3-, 12 V3(), 12 Cross, and the rest.
- Every frame slot matches ours, including all 47 $T, once WB's missing 12-byte
  EH record is allowed for. WB's only extra slots (>= 0x7140) hold the debug
  "Bad vArray[%d]" assert's Debug::Format temporary.
- Statement and argument order match in every block checked: prologue,
  first and last endpoint, tri prime and submit.

The /Od frame is laid out by local NAME:

- Renaming `tidx` moves three slots.
- Swapping two declarations moves none.

So the twin confirms local names and sizes, but not declaration order. Moving
uninitialised declarations does not change the /O2 output. The exceptions are
objects with constructors, `modelview` and `v_index_array`, and moving those
only made it worse (1,170 variants).

## The two deviations from the twin text, and the residue

The bank differs from the twin-faithful text in two places:

1. **Tri prime, bottom line.** The twin has `Vector3 &bottom_dir = ...;
   bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);`. The bank
   has `bottom = intersection[1][BOTTOM_EDGE].Direction; bottom *=
   Vector3::Dot_Product(points[0], intersection[1][BOTTOM_EDGE].Direction);`.
   This drops one named local and one $T. Without that, the twin text needs 30
   inert end ints (period 32, so -2) before pro, seg, fe, isec and merge match.
   Even then tri is about 420 off and the frame layout is wrong (2929 strict).
2. **First endpoint.** `intersection[1][BOTTOM_EDGE].Direction = bottom;` comes
   after `Vector3 segdir = points[1] - points[0];`. Retail's fe code wants the
   twin order. With the twin order (variant T0B3: revert this swap) every section
   is exact except tri, which has 40 instructions of register-allocation residue
   in the tri prime: retail keeps p0.X in xmm7 and preloads Direction.Y into
   xmm5. The swap fixes tri (2 left) but breaks fe (18). The x87 inverse is
   folded there, where retail keeps it on the stack.

Bank residue, retail offsets:

| Where | Retail | Bank |
|---|---|---|
| fe 0x14f8-0x1570 | Direction.X store before the segdir subtract | Direction stores after it |
| fe x87 at 0x15bf | `fld [ebp-0x29c]; fmul st(1); fstp; fstp st(0)` | `fmul [ebp-0x29c]; fstp` |
| tri 0x2fa2 | bottom multiplies in order Y, Z, X | order Y, X, Z |

The bottom-multiply order comes from the split spelling. The twin's operator*
form gives retail's order. In variant `W_s1b_split` (twin fe order, twin tri
prime, with the loop's paired-branch bottom line split instead) every section
before tri is exact, and the tri prime is right except the register choice
above.

## Mechanism (measured, not guessed)

- **Per-function numbering.** Functions placed before Render in the TU change
  nothing, whatever temporaries or Vector3 operators they use. The scratch TU is
  representative.
- **First-$T counter.** At /Od the front end numbers named locals before
  temporaries. One end int shifts the first $T number by +1. Dropping the tri
  ref, or its $T, shifts it by -1 each.
- **Phase follows symbol count** (as RenderStreak 0x743700 found, see
  `../00743700-phase-20261020.md`). End ints shift every site together. From
  WB-text + 0..40 end ints:
  - fe and le match at e = 5,6 (mod 8);
  - pro, seg, isec and merge match only at e = 29/30;
  - tri never matches.
- **Second dimension: tuple numbering.** The fe swap changes no counts. It does
  renumber compiler temporaries across the body: the spilled tv in the sw loop
  moves by -2 and the one in the submit loop by -5. Tri follows this, not the
  symbol phase.
- **Inert probes:**
  - `int`/`const` pads: count only, position irrelevant.
  - One-parameter forceinline calls: count thresholds at k = 8, 28 and 64,
    whatever their position.
  - Empty inlines: no effect.
  - `(void)expr` reads: dropped by the front end.

## Ruled out (do not repeat)

- Compiler and flags:
  - `/Zi`, `/Z7` and `/Zd`; `#pragma inline_depth` 4/8/16/254/default.
  - Defines `_RELEASE`, `RTS_RELEASE`, `WIN32`, `_WINDOWS`, `_MBCS`,
    `IG_DEBUG_STACKTRACE` and `_USE_32BIT_TIME_T` change nothing.
  - `WWDEBUG` and `_INTERNAL` wreck the body.
  - WWINLINE as plain `inline` wrecks the body (helpers stop inlining).
- Vector3 helper spellings that leave the generated code unchanged:
  - No effect: initializer-list ctors, `X *= k` in operator*=, `k * a.X` in
    operator*, Cross_Product without its assert, `return Vector3(...)` without
    parentheses.
  - Much worse: operator[]-based Dot or operator-, a named-local operator*, and
    an operator= through Set().
- Evaluating BFME 2's `isInitialized()` checks in release (VERIFY style) leaves
  code behind (16,947 B, frame 0x7168).
- A constructor-less POD `TriIndex` is worse everywhere. The twin's TriIndex has
  a constructor.
- Swapping the le block, re-spelling the fe Direction store (`Set`, scalar
  stores, a ctor copy), and 16 tri-prime spellings x 34 end-int counts
  (`tp2`): best 3559, tri at least 38.
- An e x k grid (twin text, end ints x inert inline expansions): best 3375; tri
  is never at or below 2.

## Next angles

- Find a real construct that moves tuple numbering the way the fe swap does,
  without touching fe's statement order. Candidates are the release bodies of
  the inlined DX8Wrapper helpers in the submit code (between the tri prime and
  the tri loop in IL order) and getVertexBuffer. A construct is right only if it
  also leaves sw, le, isec and merge exact.
- RenderStreak (0x743700) shows the same retained-inverse x87 residue at its
  Normalize sites. A shared cause would unblock both.

Scratch tools (untracked, `build/s191/`):

- `secsweep.py`: per-section scores.
- `view.py`: aligned diff.
- `igreedy3.py` / `intgreedy.py`: greedy searches.
- `declmove.py`: declaration moves.
- `odfa.py`: /Od $T listing.
- `wbc/callees.py`: WorldBuilder callee bodies.
- Notes: `NOTES.md`.

`control-flow-proof.json` (native switch control flow) still holds for this bank.
