# Return-address-relative dispatch: four machine entries, 40 bytes

Session: Codex (GPT-6); t=10 minutes since family reservation.

This is an assembly recovery of an observed register/stack mechanism. It is
not a C++ conversion, a newly identified import, or a functioning resolver.
The original API names, outer callers, writer and final provider remain unknown.
The descriptive symbols name only the independently bounded machine entries.

Prior evidence read: re_attempts entries for 7AF3/7C63/7ED9/8449, the runtime
pointer-slot verdicts, and runtime-slot-712b-20261023.md. Those correctly reject
invented import names and ordinary C++ prototypes. This recovery retains those
uncertainties and establishes the narrower machine contract independently of
the destination's source-level identity.

| Entry RVA | Extent | Observed role |
| --- | ---: | --- |
| 0x7ED9 | 7 | Save ECX/EAX, CALL the 0x7AF3 core |
| 0x7AF3 | 13 | Consume return PC 0x7EE0; read cell at PC-3509; jump through it |
| 0x8449 | 7 | Save ECX/EAX, CALL the 0x7C63 core |
| 0x7C63 | 13 | Consume return PC 0x8450; read cell at PC-4341; jump through it |

The two actual E8 transfers prove the core entry points and their callable
relationship; whole native extents and the entry-after-CALL addresses are
checked separately. The cell identities follow by arithmetic: 0x712B and
0x735B. The existing data sources own each four-byte initial value; their
current runtime contents, not an invented static provider, are the input.

The destination's incoming state is:

- EAX = value read from the cell; EIP = that same value.
- ECX = the consumed synthetic CALL return address.
- Stack top = saved incoming EAX, saved incoming ECX, outer caller's return.
- EDX, EBX, EBP, ESI, EDI and flags are unchanged. LEA, rather than ADD,
  matters here: computing the cell must not alter arithmetic flags.
- No normal RET returns to the synthetic CALL site. Its return address is
  data consumed by the core, not a normal C/C++ continuation.

An ordinary external C++ declaration cannot describe this stack protocol.
Assembly is used for that demonstrated machine ABI, not to claim C++ recovery
or to guess a callee signature. Two short macros implement the shared protocol
with instruction mnemonics and named core references; no db, raw opcode emit,
alias, speculative provider or baseline exemption is used.

The entry and core sources are separate so their calls carry real REL32
relocations. Both relocations resolve to the independently verified core rows.
The two PC biases are native layout invariants, not general relocations of the
cells: final placement must retain those code/data RVA relationships. Moving
the whole image preserves them; arbitrary rearrangement does not. No ordinary
link preview, final placement, complete program execution or census credit is
claimed by this evidence.

Byte checks compile the actual production sources into private objects and
prove complete 13/13/7/7-byte extents, every byte, and both relocations. The
ML expression `[ecx+eax]` selects retail's SIB encoding; reversing the source
operands produces the same arithmetic but a different encoding.

Independent Unicorn checks compare candidate and retail execution with 136
register/flag vectors, two dispatch paths, entry/core starting modes, and two
image bases. All 1,088 differential pairs pass the stated contract, stack
canaries, untouched cells and destination EIP. Four additional pairs preserve
the same unmapped-fetch fault for the initial file values (zero and
0x66825AB4); those initial values do not establish an executable binding.
A negative control replacing LEA with ADD is rejected despite computing the
same cell address, because it changes flags. These sampled tests are not
exhaustive runtime verification. Complete byte
identity is checked separately.

Run from the repository root:

```
python reverse/attempt_support/runtime-dispatch-20261023/verify_bytes.py
python reverse/attempt_support/runtime-dispatch-20261023/verify_contract.py
```

Use the installed Python interpreter directly on this Windows host. The second
script needs Unicorn; an optional local install under
build/runtime-dispatch-validation/deps is supported. Outputs and objects stay
under that ignored scratch directory. These entry points contribute assembly
rebuild credit only after normal byte admission, never authored-C++ credit.
