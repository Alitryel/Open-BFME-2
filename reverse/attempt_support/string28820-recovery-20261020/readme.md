# String range insertion at 0x00028820

The recovery expresses the complete 740-byte insertion as C++ in
`Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp`, preserving that
unit's existing 501-byte alias-aware replacement. Existing neutral class,
method and helper names are retained. This is byte recovery; the unit still
has unresolved linking debt.

## Target evidence and provenance

The native image has MD5 `34391b253b0ee12d6cec1178f46d3bf9`.
The insertion is `[0x28820,0x28B04)`, file offset `0x27E20`, 253 instructions,
RET16, followed by 12 CC bytes. The replacement is `[0x2B050,0x2B245)`, file
offset `0x2A650`, 162 instructions, RET20, followed by 11 CC bytes.

Native operations establish three pointer fields at +0/+4/+8, byte-sized
element movement, NUL termination, capacity testing, and allocation of
`old_size + max(old_size, inserted_size) + 1`. The replacement's two direct
calls at +0x126 and +0x173 independently identify the insertion. Its overlap
arm preserves source/destination offsets across possible reallocation.

The BFME1 donor pointer reviewed is
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`. Its STLport header declares version
0x460; BFME2's selected `vendor/stlport` declares 0x452. The later donor and
native behavior support `_M_move` and the alias-aware replacement, which are
absent from the local 0x452 string header. The generic versus const-pointer
copy distinction follows donor overloads and target call relationships;
machine bytes alone do not establish source-level const qualifiers.

Four copies of mutable string storage retain generic POD dispatch. Two copies
of the external source range use the direct worker underlying the donor's
const-character overload. Native memmove semantics are preserved.

## Complete relocation receipt

These are operand offsets within insertion. All addends are zero; there are
12 calls and 12 relocation fields.

| Operand offsets | Kind | Native destination |
| --- | --- | --- |
| +7E, +131, +15D, +23B, +252, +26C | REL32 | copy worker RVA 0x179B0 |
| +C5, +FC, +1A0 | DIR32 | msvcr71.dll memmove IAT VA 0x00BBA688 |
| +204 | REL32 | allocator RVA 0x307F0 |
| +292 | REL32 | empty destroy RVA 0x69E440 |
| +2BA | REL32 | free RVA 0x30830 |

The replacement has six fields: DIR32 memmove at +95/+1B9; REL32 erase
0x12150 at +B4, insertion at +127/+174, and forward replacement 0x2A730 at
+1E9. `receipt.json` gives exact symbol names, hashes and offsets for all 18.

The independent receipt checks every byte after resolving only those named
fields, verifies decoded call boundaries, checks that internal branches land
on instruction starts, and rejects any compiled body extending past its
declared COFF section. Both compiled sections end exactly at the native body
extents. Source, object and included-header hashes must agree with the
compiler's dependency receipt.

## Hypotheses and compiler context

The prior bank emitted 696 bytes, used six direct copies and lacked 0x14 of
the native frame. The landed 0x284D0 sibling supplied a new POD-dispatch lead.
Separating four generic storage copies from two const-source copies gave the
complete 740-byte match.

Integrating that body initially changed the existing replacement's frame.
Ordinary vendor inline declarations and const-reference tags improved the
context; bounded inline-depth controls found depth 6 preserves both complete
740-byte and 501-byte bodies. This is a compiler inlining policy, not added
storage or executable padding, and is not asserted to be the original build
setting. It must remain in force for the TU: resetting it after the function
definitions breaks the existing 501-byte owner. A separate
default-depth control matches the
285-byte forward replacement, but that body is not exact under the chosen
depth-6 policy and is not claimed as another recovery.

## Remaining linking debt

The existing generic-copy name emits 68 bytes at /Od, while its pinned native
worker is 41 bytes. A separate optimized genuine-STLport provider matches
41 bytes, but adding it alone leaves the caller's wrong COMDAT. Early and late
extern-template suppression change the caller to 719 bytes; imported inline
gives 723 and introduces import calls; imported forceinline gives 1045.
Scoped optimization also fails. None is a proposed production workaround.

Normal `link_check.py` previews against the same census (2026-10-20 12:21,
commit `5366c4f808`) report 13 blockers before and 7 afterwards:

| Blocker class | Before | After |
| --- | --- | --- |
| Unresolved names | 4 | 1 |
| Non-retail COMDAT copies | 5 | 3 |
| Selected definitions proven wrong | 4 | 3 |

The four old unresolved allocator/copy/deallocator declarations are removed.
The empty-destroy declaration is a newly referenced unresolved dependency in
this TU under an existing helper name. The copy helper's existing 68-byte
sibling-family defect is now referenced by this TU; erase and forward
replacement remain wrong as before. These three definitions each contribute
both a COMDAT and selected-definition blocker. A correct empty destroy
provider would remove only the unresolved blocker. The unit remains unlinked,
and linked-byte progress is zero.

## Reproduction

Use the repository's supported Windows VC7.1 setup and normal build entrypoint:

```sh
./build.sh Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp
python3 reverse/attempt_support/string28820-recovery-20261020/receipt.py
python3 tools/link_check.py Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp
```

The receipt reads already compiled objects; it does not compile or change the
ledger. Its source/object paths and hashes identify the exact checked state.
The source contains the retained candidate, so dozens of superseded controls
are not required to resume the remaining provider work.
