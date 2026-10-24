# Wide string base destructor provider, 2026-10-24

Inputs: BFME2 `4b0bf28a81f4a6c2e8b71377e7d150e3c3cfd345`, BFME1
`32774ab03393709a7f14331ba8d98d281a55ffd9`; census index
`2026-10-24 07:31 at a9f880ad06`, `retail-truth-4`.

## Cause and target evidence

`stlport_wide_money_put_string.cpp` is the first definer of
`??1?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAE@XZ` in the published
link order (position 187). Its inline-cost carrier emits an 82-byte outline:
free the first pointer, then nine calls to an empty `_MoneyPhantom` destructor.
The later `stlport_wide_num_put_bool.cpp` (position 193) provides a proven
14-byte copy. With the unproven copy first, retail-truth-4 correctly refuses
the monetary formatter's differing COMDAT. This is separate from the recursive
proof-cache defect fixed immediately before this work.

Target identity is already established by the base-only constructor cleanup
and money_put state 21 reaching RVA `0x00142D70`, while complete strings reach
the 63-byte `~basic_string` at `0x0000B3C0`. See
`df20-funclet-naming-20261021/handoff.md` and
`df20-exact-true-naming-20261021/handoff.md`. The existing wide-base fold pin
also carries a whole-body proof. The target's 14-byte body tests the first
pointer, calls free at `0x00030830` when nonnull, and returns.

## Repair

Define and instantiate the already declared wide base destructor in
`stlport_wide_string_cstr_ctor.cpp`. This constructor's `0x0000BF20` start
precedes the monetary formatter's `0x0000DF20`, so its proven 14-byte copy is
kept first. Definition placement after the explicit constructor instantiation
preserves the opaque cleanup call and exact constructor/EH code generation.

The new COMDAT has bytes `8b0185c0740750e80000000059c3`, one REL32 at +8 to
`_free`, and a RetailTruth verdict of `retail`. It independently reproduces
all 14 target bytes and the free relocation. The formatter stays unchanged,
including the inline-cost carriers that preserve its exact call/cleanup map.
No ledger rows, pins, aliases, baselines or verifier rules are changed.

BFME1's wide string-from-pointer view was reviewed at the input revision; it
likewise declares the base destructor but offers no corresponding provider
repair to transfer. The body and its placement here are supported by BFME2
target bytes, the existing constructor view and the measured link order.

## Trials ruled out

- Force-inline annotations on the phantom/member destructors, throw()
  specifications, and unqualified destructor-call spelling retain the
  82-byte outline; the monetary parent still matches.
- Function and class extern-template declarations leave that specialized
  outline unchanged. Earlier DF20 handoffs also found such declarations inert.
- Automatic local phantom lifetimes, and nine null-this guards with
  `__assume(this != 0)`, emit a retail 14-byte base but inline the three
  cold base cleanups the monetary parent must call. The parent fails its byte
  comparison, while its other nine rows still match. Flattening the phantom's
  member-destructor chain also fails the parent.
- Nine guards without the assumption emit an 88-byte base and fail the parent.
  An eager non-inline phantom definition emits a 66-byte base and also fails
  the parent. All these formatter edits were restored; the existing exact
  DF20 source remains the better reconstruction.

## Validation

- Provider plus unchanged formatter: 11/11 function rows match; string, float
  and import-reference checks pass. Both EH-bearing rows are EXACT, no debt.
- Both provider/consumer argument orders pass `link_check.py`: 2/2 units,
  98 -> 2,714 authored linked bytes (formatter 0 -> 2,616).
- Recheck all nine published base-destructor definers plus the new provider,
  first with the original provider source, then with this change: 7/10 ->
  8/10 clean units; 13,290 -> 15,906 current authored linked bytes, +2,616.
  Every previously clean unit remains clean. The monetary reader's 2,830
  bytes already link in the before run and are not credited to this repair.
- `numpunct_virtuals` loses this destructor blocker but still lacks four
  true/false-name statics. PeerThread's unrelated unresolved/COMDAT blockers
  remain. The two family runs therefore correctly return failure overall.
- `find_declared_unmatched.py` accepts the provider; `git diff --check` passes.
- The identity shadow check reports a divergent two-argument const-wide
  `_M_range_initialize` helper. Rebuilding the original provider source proves
  this inherited: before and after both have the same 23 bytes, digest
  `052180a652e0`, and REL32 at +16 to the three-argument overload. No baseline
  or helper was changed to suppress the warning.

The gain is a local link preview against the published index, not a new full
link census or newly recovered unique C++ coverage. No verification runner
requiring maintainer approval was started.
