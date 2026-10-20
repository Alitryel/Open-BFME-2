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
