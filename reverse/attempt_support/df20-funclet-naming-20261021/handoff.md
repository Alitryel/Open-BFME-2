# 0x0000DF20 wide money_put::do_put(string): blocked on string-dtor naming (2026-10-21)

Follows `df20-inline-budget-20261021/handoff.md` (bank `reverse/attempts/0x0000df20.cpp`,
fit 0.9067, nd 166, frame 0x118). This round found that the ledger names the
two STLport string destructors the wrong way round. The DF20 cleanup map only
makes sense once that is fixed.

## Target evidence (retail unwind maps, `lea/mov ecx; jmp`)
MSVC 7.1 names the funclets as follows (scratch probe p5, see
`wide-money-get-string-12190-20261021/handoff.md`):
- an unwind state for a complete object calls `~basic_string` (W);
- a base-only state (after the `_String_base` ctor, inside a basic_string
  ctor) calls `~_String_base` (S).

| body | state | object | target |
|---|---|---|---|
| 0x0000BF20 `basic_string<G>(const G*, alloc)` | 0, base-only | `[ebp-0x10]` | 0x142D70 (funclet 0x75B6D0) |
| 0x0000EA90 `basic_string<G>(const&)` | 0, base-only | `[ebp-0x10]` | 0x142D70 (0x75B6D0) |
| 0x00009170 `basic_string<char>(const&)` | 0, base-only | `[ebp-0x10]` | 0x142D70 (0x75B6D0) |
| 0x00009100 `basic_string<char>(const char*, alloc)` | 0, base-only | `[ebp-0x10]` | 0x142D70 (0x75B6D0) |
| 0x00017830 `basic_string<char>(char*, char*, alloc)` | 0, base-only | `[ebp-0x10]` | 0x142D70 (0x75C310) |
| 0x0000DF20 | 21, base-only | `ebp-0x94` | 0x142D70 |
| 0x0000DF20 | 22, complete | `ebp-0x94` (same object) | 0xB3C0 |

The statics' atexit thunks also show the complete-object case:
`rva007B6A00/6A10/6A40` (`Code/GameEngine/Source/Common/Rva007B6880Thunks.cpp`)
are `mov ecx, 0xDDEEF0|0xDDEF20|0xDDEF2C; jmp 0xB3C0`. These are complete-object
destructions of wide strings. Today the source casts them to
`StlNarrowStringBase *` and calls S<char>.

Conclusion (target evidence):
- S<char> = S<G> = **0x142D70**, the frameless 14 B `if (p) free(p)`.
- W<G> = **0xB3C0**, framed, 63 B, one EH state; funclet 0x75B7C0 destroys
  the member at +8.
- W<char> = 0x142D70 by ICF, which is unchanged.

## Ledger rows this contradicts (none touched in this round)
- `reverse/functions.csv`:
  - S<char> @0xB3C0 (owner, `stlport_narrow_string_base_dtor.cpp`);
  - S<G> @0xB3C0 (fold-proof twin);
  - `uw_0075b7c0`, whose parent names S<char>;
  - `__ehhandler$S<char>` @0x75B7CB;
  - W<G> @0x142D70 (ICF twin in `stlport_wide_money_get_long_double.cpp`).
- `reverse/symbols.csv` pin of S<G> at 0xB3C0. Its note cites the bool num_put
  calls at 0xEC2F and 0xEC46. Under the new naming those calls are W<G>.

## Repair plan (zero new bytes, about 8 units; do it as one reconciliation)
1. Respell the owner TU so that it emits W<G> at 0xB3C0. Rename the owner row,
   the `uw_0075b7c0` parent and the `__ehhandler$` row to W<G>. Drop the S<G>@0xB3C0
   twin and its pin.
2. Delete the W<G>@0x142D70 twin row. Admit S<char> and S<G> at 0x142D70 as
   fold pins with `tools/pin_admission.py --add`, from a unit that compiles
   retail's 14 B body.
3. Respell the callers whose `.text` relocations name S<G>, so that they call
   W<G>: `stlport_wide_num_put_bool.cpp` (declare `~basic_string<G>`
   non-inline instead of `~_String_base`), `stlport_wide_num_get_bool.cpp` and
   `stlport_wide_num_get.cpp`.
4. Move the `_MoneyPhantom` cost in `stlport_wide_money_get_string.cpp` (0x12190)
   from S<G> to W<G>, then re-verify 12190.
5. `stlport_wide_money_put_long_double.cpp` (0xBE50) calls W<G>, but retail
   calls 0x142D70 there. Respell those calls as S<G> or the deallocate path.
6. Respell `rva007B6A00/6A10/6A40` to destroy wide basic_strings (W<G>).
7. Units checked with no affected `.text` refs (`build/c6/textrefs.py`, scratch):
   OwnedRecord492/840 (Wc only), StlSweepR3 and
   `stlport_wide_money_get_long_double` (no `.text` refs).

## What it means for DF20
In retail, the currency temps (0x108/b, 0xF0/a) and return 1 call **S** out of
line, so W is inlined there. The sign temps (0xCC/14, 0xE4/13, 0xFC/12,
0x114/11) and return 2 call **W** out of line. The final exit is fully inline.

The bank and every phantom map tried before this round assumed the reverse
naming, so the inline-budget search was aimed at the wrong dtor. After the
rename:
- re-run the phantom map with the cost on W (not S) at the sign sites;
- check that the frame stays 0x118 (any inlined phantom shrank it to 0x110
  before).

Tried this round:
- callee visibility, with the S/W declaration grid;
- the inline-budget phantom maps from the previous handoff.

Each of those misses for the reason above. Control flow, lifetime and the flags
are as recorded in the earlier df20-* handoffs.
