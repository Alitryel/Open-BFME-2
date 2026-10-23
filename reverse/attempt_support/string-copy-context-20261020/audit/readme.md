# Independent audit of the shared copy debt

**Blocked research, not code progress or a link pass.** The audit read current
compiled objects without compiling or changing production, pins or checkers.
Seat: GPT-6 Astra. BFME2 revision at audit:
`cbf7608fb05a1180b2e2c7fa19a5a523e1f95d7c`.

## Results

| Banked candidate | Independently proved | Remaining blockers |
|---|---|---|
| `../primary-timing-in-class.cpp.txt` | Complete 740-byte insertion and 41-byte legacy copy | 501-byte replacement frame 0xfc versus 0x118; extra `__uninitialized_copy` emits 41 bytes that are wrong for its own existing pin |
| `../exact-copy-Od-depth6.cpp.txt` | Complete 740-byte insertion and 41-byte legacy copy | Same replacement mismatch; only the original five definitions, so no extra inner helpers |
| `../repair/best-sibling22.patch` | Complete 848-byte insertion, 511-byte replacement and 41-byte legacy copy | Explicit specialization must be reconciled in all four consumer TUs; extra wrong 86/97-byte helpers and 45-byte `max` |

The primary-template timing candidate has no explicit specialization, so the
specialization-before-use objection does not apply to it. It does not establish
global ODR conformance or fix its remaining provider and caller mismatches.
Its newly emitted `__copy_aux` is now an exact 41-byte native twin; the
`__uninitialized_copy` name is bound elsewhere, so identical bytes to the
0x179b0 copy worker do not make that other name correct.

The original legacy
`??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z` is a 68-byte wrapper
in all four production consumers. Its sole REL32 +0x39 calls the canonical
`?__copy_trivial@_STL@@YAPAXPBX0PAX@Z`. The existing legacy pin at 0x179b0
records caller destinations; it is not proof of that 68-byte body.

The canonical owner is 41 bytes at 0x179b0 in
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp`. Each positive
candidate copy has exactly the owner's raw bytes and sole DIR32 relocation at
+0x1e to `__imp__memmove`, addend zero, native IAT RVA 0x7ba688. Raw SHA256:
`07d84357dc85cbcdfcfccbb4e7b9f4c6e342b9f26802457e6d29523d941653a4`.
All candidate copy extents are independent 41-byte sections with no tail.

## Caller and relocation scope

The 740-byte insertion at 0x28820 is identical to its current production body,
including all 12 relocation tuples:

- REL32 +0x7e, +0x15d, +0x23b, +0x26c to the legacy copy name;
  +0x131, +0x252 to the canonical name. All land at 0x179b0.
- DIR32 +0xc5, +0xfc, +0x1a0 to the memmove import IAT at RVA 0x7ba688.
- REL32 +0x204 to allocation at 0x307f0, +0x292 to destruction at 0x69e440,
  and +0x2ba to game free at 0x30830.

The 848-byte insertion at 0x284d0 and 511-byte replacement at 0x2ae50 also
have identical raw bytes and relocation tuples in sibling22 and production.
The insertion's six legacy-copy operand offsets are +0x96, +0x161, +0x196,
+0x28c, +0x2a3 and +0x2c0. The receipts contain every remaining relocation.

The baseline diagnostic's reported 1,360-byte replacement is the entire COFF
section: 511 bytes ending in `ret 0x14`, one CC alignment byte, then the
848-byte insertion starting at section +0x200. The next typed function symbol
proves that boundary. The final sibling22 puts each body in its own exact-size
section. No reported positive depends on truncating a longer function.

Any eventual shared repair must preserve both homes' 848/511 and 740/501 rows,
the V21/V22 149/170-byte rows, and their emitted 740-byte insertion copies.
Changing the canonical narrow-string provider also requires checking its 20
ledger rows. No candidate here satisfies that complete scope.

## Remaining named providers and source constraints

The specialized global `/O2` candidate emits:

- `__copy_aux<char*,char*>(...,const __true_type&)`: 86 bytes, wrong for
  its 0x179b0 binding.
- `__uninitialized_copy<char*,char*>(...,const __true_type&)`: 97 bytes,
  wrong for its existing 0x4598cc fold pin. The resolver also considers 0x598cc.
- Sibling22's global `max<unsigned int>`: 45 bytes, wrong for the 16-byte
  native body at 0x9fde5. The scratch returns the first reference on equality;
  the native owner returns the second. This is also a semantic difference.

These are locally unreferenced, but the current keep rule rejects a proven
wrong native-bound copy. The rule for unknown unreferenced COMDATs does not
exempt them. The primary-timing variant fixes the first emission to exact 41
bytes but still emits a wrong 41-byte `__uninitialized_copy` at the other pin.
Existing erase 101 versus native 57 and replaceBase mismatches remain
independent debt.

The earlier explicit-specialization approach cannot safely land in one TU
while other consumers implicitly instantiate the same primary. The declaration
must precede first instantiating use in every affected TU; identical semantics
do not remove that rule. Repeated inline definitions must also meet the ODR.
See [specialization rules](https://eel.is/c++draft/temp.expl.spec) and
[MSVC C2908](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2908?view=msvc-170).
The candidate optimization pragmas are counted hatch growth, not a hatch-free
repair. This packet admits no allowance or rule change.

## Replay

Materialize the source using the enclosing packet's replay instructions, then
compile it through the normal diagnostic/build path. This script does not
compile or install anything:

```powershell
python3 reverse/attempt_support/string-copy-context-20261020/audit/replay.py --role owner --source build/string-copy-context-replay/primary-timing-in-class.cpp
python3 reverse/attempt_support/string-copy-context-20261020/audit/replay.py --role owner --source build/string-copy-context-replay/exact-copy-Od-depth6.cpp
python3 reverse/attempt_support/string-copy-context-20261020/audit/replay.py --role sibling --source build/string-copy-context-replay/repair/candidate.cpp
```

The JSON records source/object hashes, real function extents, complete
relocation tuples for the three compared bodies, native operand destinations
for exact bodies, and all native-bound providers. It refuses stale objects
and rechecks inputs after reading. It streams narrow ledger filters and reads
existing objects only. Stored receipts retain the original scratch source
paths; their source hashes bind them to the banked snapshots or patch result.
No private executable or object binary is included.
