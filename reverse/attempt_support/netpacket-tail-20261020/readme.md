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
