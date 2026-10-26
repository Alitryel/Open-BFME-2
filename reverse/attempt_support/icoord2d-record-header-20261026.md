# Coordinate record: canonical header and explicit prefix initialization

Base `1a79023625`, on upstream `d831bc2403`, 2026-10-26. The existing
ICoord2D class claim covers StlportCoordVectorRecordInsert.cpp. Its entire
source and prior attempts were read; the frozen-file check and all four
existing rows pass before editing.

## Target facts and scope

The 85-byte constructor at `0x002B8ED2..0x002B8F27` clears its receiver's
second integer, then its first integer, before the vector-base call to
`0x00211E58`. The exact instructions are `AND [esi+4],0` and `AND [esi],0`.
After the vector is constructed at offset eight, the constructor copies the
incoming coordinates and appends the payload through the existing owner.
The 153-byte append body at `0x002BC830..0x002BC8C9` calls the existing
coordinate equality body at `0x00004CAD`, then appends to a matching record
or constructs a new one. The existing copy owner establishes a 20-byte record.
These facts do not recover the record's original name or inheritance hierarchy.

The old private ICoord2D declaration supplies a forced-inline, imported
constructor that clears both fields. This is record initialization, unlike
the native empty default constructor exported as ICoord2D's constructor.
The change adopts the existing canonical ICoord2D and ICoord2DBase headers,
and performs `x=y=0` while evaluating the payload vector's initializer.
The POD base is already default-initialized at that point; both assignments
finish at the comma operator's sequence point before the allocator reference
is evaluated and the vector constructor is called. No uninitialized value is
read. The coordinates are still overwritten from the supplied position only
after that call, preserving the native lifetime and exception ordering.

## Rejected trial and verified change

The first trial explicitly value-initialized the aggregate base. Its behavior
was equivalent, but VC7.1 emitted XOR and two STOSD instructions, with the
first byte difference at offset 0x0C. Three of four rows passed. The owning
logging tool temporarily banked this partial as `reverse/attempts/0x002b8ed2.cpp`;
its 0.9 score is a reconstruction estimate, not a measured byte-match percentage.
After the final change matched, check_csv required removing the resolved stash.
It was removed as instructed; the log preserves the trial and its resolution,
and the scratch proposal retains its source. No failed trial remains in Code/.

Explicit chained assignment in the vector initializer retains the native
instruction order. Normal whole-file verification passes all four rows:
the constructor, append body and both ten-byte EH handlers (258 bytes).
Both EH graphs are EXACT. Independent COFF review, reproduced locally,
preserves all 13 non-debug sections, 463 bytes, 26 relocations and 15 external
symbols. Two compiler-local labels are renumbered; their physical targets
are unchanged. No external name is normalized for this comparison.

The frozen-file check passes after the final change.
`header_adopt_lane.py accept --class ICoord2D` retires this file's one queue
row through its normal verdict. No shared header, class layout, function
boundary, pin, data binding or provider definition changes. No linking,
ownership or C++ exact byte gain is claimed.

Local receipts under `build/codex-cleanup-20261025/`:
`iteration28-before-build.log`, `iteration28-value-init-build.log`,
`iteration28-ordered-init-build.log`, `iteration28-header-accept.log`,
`iteration28-eh.log`, `iteration28-coff-parity.log`, `iteration28-commit.log`.
