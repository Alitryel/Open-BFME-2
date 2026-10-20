# Apt stream relocation, 20 October 2026

Target: `_BfmeAux006FC670`, native code 0x006FC670..0x006FCFCE,
followed by two alignment bytes, a fourteen-entry dispatch table at 0x006FCFD0,
and a 56-byte index at 0x006FD008. The complete extent is 2512 bytes, ending
exactly at the independently rowed forwarder 0x006FD040. Ghidra's 2398 is
the code length. Do not compare only that prefix or score tables as instructions.

WB 0x0175B510 independently names AptActionInterpreter::_parseStream; its
debug Release path also has that qualified name as a literal. Target assertions,
opcode dispatch, constant-table conversion, temporary string relocation and
inverse conversion agree. The three-argument forwarder supplies a null constant
file; the four-argument asserted forwarder supplies it. Their historical
unguarded-insertion-sort comments are refuted by this evidence. No new original
type names are asserted from matching bytes alone.

The existing primary bank at 1a1e69c6aa remains unchanged. It emits all 2512
bytes, but retains two inherited volatile integer writes as diagnostic shaping.
It is not landable. A clean alternative removes both; the accompanying patch
also orders the two push-item arms as WB does. It is likewise not exact.

Fifty successful distinct caller controls cover:

- Eight baseline/type controls: unsigned versus signed byte stream, pointer
  versus integer relocation base, unsigned constant index, with and without
  inherited volatile writes. These types do not repair the machine shape.
- Three real-owner controls use the current complete AptActionInterpreter.cpp
  and its actual AptScriptFunction header. Reuse the canonical pool global,
  low-byte tests of the real integer-returning predicate, and measured 12-byte
  constructor views; do not invent overrides of the abstract AptValue interface.
  EHs preserves 2512 bytes; EHsc shortens this reconstruction to 2420/2436.
- Seven settings controls plus six hash-pinned SP1/DDK compiler controls.
  G7/SSE2 changes the graph and worsens it. G5/IA32 and both compiler versions
  retain the relevant RTM shape. O1 is much shorter and different.
- Seven flow/alignment/union-write controls. WB's push-arm order changes
  instruction-aligned structural regions from 16 to 7 in clean C++, and memory
  operand differences from 46 to 22, but moves an 85-instruction block and has
  worse positional agreement. It is not an improvement under every metric.
- Three static-member-name controls, five push-item representation/index-lifetime
  controls, four real INT3 assertion controls, two visible-provider controls and
  five counter/atom-lifetime controls. No control reaches exactness. The ordinary
  release-vector and predicate-family definitions do not improve the caller.
  No assembly control is retained as a proposed production change.

Baseline raw-code metrics (excluding relocation operands): 18 structural
regions, 34 memory and 63 register differences; nonvolatile: 16/46/73;
nonvolatile WB arm order: 7/22/62. All have complete 2512-byte extents and no
unresolved REL32 calls. Stream/base EBX/EBP roles, counter increment allocation,
constant-string read/modify/write and block order remain. Reassessed types,
control flow, lifetimes, helper visibility and compiler versions; no unresolved
callee is the prerequisite. The already rowed 762-byte numeric predicate in the
bank is a different body and must never be scored as this parser.

Replay: copy apt-stream-relocation-20261020.py.txt to build/ and run phases
abi, owner, flags, flow, method, compiler, items, assert, providers, counter in
that order. Seed is frozen from 1a1e69c6aa; current-owner/provider sources are
frozen from 1e1497c0b9. Restore that commit's AptScriptFunction header and
dependencies when reproducing the owner trial on a changed tree. The working
reference is verified BFME1 b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b.
Normal explain_mismatch compiles each isolated source, then the driver reads its
COFF code through the first dispatch-table relocation. Retail code/alignment is
2400 bytes. Do not trust patched side-by-side disassembly when a shifted DIR32
operand was copied from retail at a nonmatching offset. Complete outputs and
per-phase metrics remain under build/apt-stream-contracts-oct20/.

No production Code, pin, ledger or verifier edit. Claim released after banking.
