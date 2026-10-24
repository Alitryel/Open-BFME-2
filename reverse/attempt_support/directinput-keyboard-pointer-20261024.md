# Complete keyboard data format and relocated table pointer

Base BFME2 `007527709d`, BFME1 `32774ab0`. The separate preceding verifier
commit is `d837021300` (`data-row-executable-home-20261024.md`).

The old 24-byte raw `g_00C7C9A4` initializer contains six dwords:
`24, 16, 2, 256, 1, 0x00A29F20`. Reading retail at VA 0x00C7C9A4 gives
`24, 16, 2, 256, 256, 0x00A29F20`: the raw reconstruction incorrectly
declares one object instead of 256. Its bytes at +16/+17 differ. That raw
array had no data_rows.csv entry, so the passing function byte gate did not
verify this count. This corrects the earlier handoff's assumption about the
source initializer; its observation of retail's 256-object descriptor was right.

The initializer also embeds the table's original VA as literal bytes. It
cannot follow `_BFMEKeyboardObjectFormats` when the linker places the owned
table elsewhere. The table and GUID were already independently verified;
no additional table bytes are claimed here.

Replace the raw array with an SDK-layout DIDATAFORMAT, the correct object
count, and a real pointer to the existing 256-record owner. A shared header
keeps DIOBJECTDATAFORMAT's four fields and DIDATAFORMAT's six fields consistent
between consumer and provider. The descriptor's pointer is const in this
read-only view; field widths/order are the DX8.1 dinput.h contract. BFME1's
Win32DIKeyboard::openKeyboard also supplies its keyboard descriptor to
SetDataFormat. No SDK source or compiler input was modified.

The global identifier is unchanged. Its newly emitted struct-typed COFF
symbol now has one explicit 24-byte data row at the native address; there
was no prior data row for the byte-array spelling to move or rename. The
derived data_ledger.csv inventory is not hand-edited. No pin or alias is added.

`directinput-keyboard-pointer-20261024.json` records the native descriptor,
old/new compiled initializers and relocation graphs. All 188 compiled bytes
of openKeyboard are identical before/after. Its only changed relocation
target spelling is the same descriptor under its actual struct type. The
descriptor now has exactly one DIR32 relocation at +20, with addend zero,
to `_BFMEKeyboardObjectFormats`. Resolving it produces all 24 retail bytes.

Ordinary verification passes the complete function and all five data rows:
the 24-byte descriptor, two existing 16-byte consumer GUIDs, the existing
4096-byte table with 256 GUID relocations, and its existing 16-byte GUID.
The scoped two-unit link preview passes both units at 188 -> 188 function
bytes. All five registered .text data extents were also checked in the
preceding verifier cohort, including the four unchanged CRT dispatch cells.
No further raw pointer to these extents was found to repair in this scope.

This repairs the reconstructed keyboard descriptor and its link connection.
It adds data ownership, not C++ function coverage or a measured census gain.
No linked executable or runtime game test was run.
