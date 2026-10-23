# NetPacket command decoder: tail and provider follow-up

Complete target `0x00593F15..0x005944D8`: 1351 bytes of executable code and
124 bytes of switch table, 1475 total. The picker still advertises the old
1351-byte extent. Read all prior attempt records before testing the current
barrier-free `.995` bank. Both the body and its approved NetPacket.cpp file
scope were claimed remotely before work. Production source stays unchanged.

Normal explain_mismatch reproduces the same seven resolved code-byte residue:
all executable code through +0x507 agrees. Native's Z arm ends with detach,
reload this into EBX, then a long backward jump into D's already correct
`mov esi,[ebp-0x14]; jmp loop-check`. C++ reloads ESI before EBX, then takes a
short jump directly to the loop check. Equal total size conceals this different
tail sharing. Do not count raw switch-table disassembly or blank relocation
bytes as instruction defects.

New independent checks, all normal isolated diagnostic builds:

- Target-verified NetCommandRef ctor36B and dtor12B plus NetCommandMsg
  detach26B definitions, individually and together, retaining the native
  out-of-line calls. Exact provider source is already in Code. They do not
  change the decoder residue. The detach visibility trial uses the provider's
  real slot0 destroy-and-return view; its body is not promoted into a header.
- Inline and const inline packet-length accessors are inert.
- Current whole-home integration: reconcile the bank's ACK declarations,
  add the list declaration and decoder, use the actual current NetPacket.cpp
  flags/definitions. Every relative header in the scratch copy resolves to the
  exact existing production header, with existence checked. EHs and EHsc all
  retain 1475 bytes and first difference +0x508. This is compilation evidence,
  not a claim that all rows in that scratch object have been byte-verified.
- ZH's NetCommandMsg.h confirms ACK classes derive from NetCommandMsg. Native
  accesses separately establish the BFME2 base extent1C and extra fields20/24.
  Proper inheritance replacing the flat prefix, alone and with G7, is inert.
- G5/G6/G7, G7 SSE/SSE2 and both hash-pinned SP1/DDK compiler profiles leave
  the same code residue (SP1 adds one byte of symbol padding).
- One specific legal shared-tail CFG: put all D locals inside a nested block,
  then place the completion label and `i=offset` inside D after that block;
  Z jumps backward to this label. There is no skipped initialization or new
  side effect. Both D fallthrough and explicit-goto variants compile, but the
  compiler still lays out the join after Z: 1472 bytes, first difference +0x11.
  The bounded independent reviewer confirmed this exact placement was not
  recoverable from earlier shared-label summaries; it is now preserved.

The ZH and BFME1 donor getCommandList bodies were read, including the
newInstance/NEW_NETCOMMANDREF distinction; their ordinary non-debug allocations
do not supply a different lifetime. Target-specific timestamp/ID logic and
early-return behavior remain the earlier bank's established reconstruction.
New provider, inheritance and compiler trials do not resolve the tail ordering.
No asm, volatile, barrier, dummy helper effect, pin, baseline or Code change.
Keep the better existing bank. Measurements and three concise patches preserve
the useful tests; the next attempt needs new evidence for this exact tail.

## Addendum, 2026-10-20 (claude-opus-5-5, second seat pass)

The bank is unchanged: fit 0.9826, bytes 0.958644, 1475 B. Each trial below
was scored against retail with the bank's flags.

| Trial | Explanation tested | Change | Result |
|---|---|---|---|
| b1-b3 | control flow | `break` in place of the arm `return`s | 0.974 |
| r1-r4 | control flow | if/else wrappers around the Z arm | inert (bank bytes) |
| v4-v6 | control flow | loop wrappers (`for(;;)`, do/while) around the decode switch | inert |
| s1 | control flow | nested structured join | 0.899, 1472 B |
| g1 | control flow | `goto` shared tail | 0.912, 1472 B |
| z1 | lifetime | Z arm without `offset` | 0.773 |
| z2 | lifetime | Z arm without the `i = offset` reload | 0.804 |
| a1 | lifetime | address-taken `i`; repeats the ZH form already disproven above | 0.891 |
| flags | compiler settings | `permute.py --flags` | 0 of 1 closed |
| permute | all | `permute.py 0x593F15 --minutes 30 --jobs 6` | 1167 trials, no gain in 600 |

Explanations not covered here (types and layout, callee visibility) are the
provider, inheritance and accessor trials above. The residue is still the Z
tail's reload order (`ebx` reload before `i = offset`), which decides whether
cl cross-jumps into the D tail.

## 2026-10-20 claude2 follow-up (all scored against the .995 bank)

- WB twin 0x154E140 has no `offset` local: one `i` (local_14) is used by the
  loop head, the memcpy arms and the readers (`lea eax,[local_14]`). Retail's
  esi-across-memcpy plus [ebp-0x14]-in-D/Z shape still needs a register
  candidate `i` and a separate address-taken home. Single address-taken `i`
  (a1, 0.891) puts `i` in edx and stores it around every memcpy. `/Oi` and
  `#pragma intrinsic(memcpy)` expand memcpy inline (0.796). `/Oa` and `/Ow`
  are inert (0.891). In-TU noinline reader bodies are also inert (0.881 to
  0.891), whether or not they store `&readOffset` globally. So the retail and
  WB sources likely differ here, or the gap is a compiler setting not yet found.
- Also disproven, all on the two-variable bank:
  - else-continue join of D/Z at loop level (0.899: the join is laid after Z
    and this/lastCommand swap registers);
  - Z without `offset`, or `offset` scoped to D (0.773);
  - scoped offsets (0.930);
  - if/else and do/while/for-break wrappers around the D/Z tails (identical);
  - lastCommand declaration position (no change);
  - `permute.py --flags` (0 of 1 closed).

## 2026-10-21 claude2 round 3 (scratch builds of the .995 bank; d = diff count, bank d=5)

The Z-arm reload order is now located: c2 emits the redundant `this` reload
(`mov ebx,[ebp-0x2c]`) immediately after the `i = offset` copy wherever that
copy sits, so retail's order (ebx, then the D tail's `mov esi,[ebp-0x14]`)
would need the esi load to be a split/fixup copy rather than a source copy.
Ruled out:

| Trial | Change | Result |
|---|---|---|
| z3 | `offset` scoped to D, Z without it | 1515 B, same flip as z1 |
| s1, s2 | Z `msg` handling in its own block, `i = offset` outside | inert (d=5) |
| p1 | uniform `Int &` reader parameters | inert |
| d1-d6 | Z content deletions (ACK arms, setters, delete, new, detach) | reload always right after the copy |
| e1, f1 | `commandIDSet` store after / before the copy | 1475 B d=7, reload still glued after the copy |
| e2 | `i = offset` before `msg = 0` | same as bank |
| e3 | copy before `detach` | 122 diffs |
| g2 | `goto` join from the `lastCommand == 0` exit to the copy | 1499 B, 157 diffs |

The only other reload-then-cross-jump site found by a retail scan is 0xE4070
in the matched FlatHeightMapUpdate `?rva000E3CE1@Rva000E3B41@@...`, where two
fixups (`mov edi,[ebp-0x10]`, `mov ebx,[ebp-0x14]`) are cross-jumped. A closer
should look for a source shape where `i` and `offset` are one coalesced web
with a split at the Z exit.

## 2026-10-21 claude4 follow-up (scored against the bank, fit 0.97819 on build/np scorer)

The pre-schedule order is fixed: `i = offset` is the block's own load and the
`this` reload (ebx) is compensation code appended at the block end. In x5
(`i = offset; frame = frame + 1;`) the ebx reload stays last
(`mov esi; inc [ebp-0x20]; mov ebx`). Retail therefore needs `i = offset` in a
successor block of Z. Every real join of the two tails changes register
allocation (this -> edi, 1472 B), so the tail must get merged after register
allocation.

All of these were built and scored, and none beat the bank:
- f1 factorial (216 variants):
  - Z `i = offset` position (5 positions; every one except the end is about 0.93);
  - offset assignment form (3);
  - `msg = 0` kept or dropped;
  - guarded or unguarded delete;
  - msg declaration position;
  - D `i = offset` before or after `msg = 0`.
  48 variants tie with the bank; `offset = i` after the lastCommand check gives 0.976.
- Statement edits:
  - Z else -> `break`: 0.969, with slots -0x18 and -0x1c swapped;
  - do-while(0), for/break, prefix-wrapper and `if (lastCommand) {...} else return;` forms: identical to the bank;
  - commandIDSet store moved to the end: 0.9737 (the store is scheduled after both loads);
  - `i = offset + 1`, and two further tail statements: same order or worse.
- Gotos and continues:
  - goto from D into a Z-side label, or from Z into a D-side label: 0.908, 1472 B;
  - `continue` after `i = offset` in Z or in both arms: identical to the bank.
- Loop and declaration forms:
  - loop head `m_packetLen > i`: cmp operands swap and the Z tail is unchanged;
  - `for (;;)` form, `(Int)` cast, `i` declared without an initializer: identical to the bank;
  - `i` / `offset` / `lastCommand` declared first in the function: 0.918 / identical / 0.916;
  - `i` declared before commandType or before offset: identical to the bank.
- Dummy-local meter, N = 0..96 `int dK = K;` after commandIDSet: all inert, so the local-count phase does not drive this residue.
Untested: a forceinline helper holding the setters and tail that D and Z share;
typed `msg` pointers in the Z arms.
