# DirectInput keyboard descriptor table

## Established from the target

At BFME 2 revision ee4143834a85941b460d691fad819f662987b67f, RVA
0x00629F20 / VA 0x00A29F20 contains 256 consecutive 16-byte records, ending
at RVA 0x0062AF20 (the DirectInput8Create import thunk). Every record i is:

    { pointer VA 0x00CDF6B8, i, 0x8000000C | (i << 8), 0 }

The complete extent is 4096 bytes. The progress metric excludes two literal
0xCC bytes inside record 204 as padding and therefore reports 4094 real bytes.
These two bytes are data, and the data verifier checks all 4096 bytes.

The GUID at VA 0x00CDF6B8 is 55728220-D33C-11CF-BFC7-444553540000.
The 24-byte DIDATAFORMAT at VA 0x00C7C9A4 is
{24, 16, 2, 256, 256, VA 0x00A29F20}. The existing matched
DirectInputKeyboard::openKeyboard at RVA 0x00098BD4 passes this descriptor
to SetDataFormat. This provides consumer evidence independently of adjacency.

## SDK contract, not recovered source names

The checked-in BFME 1 reference pointer is
138757e9b74645fbcbb7724a7af2764e34931e11.
Its inputs/toolchains/dx81/include/dinput.h gives the DIOBJECTDATAFORMAT
field types and the exact GUID_Key value. No dinput8.lib source was copied.
The new source reconstructs the target initializer from the record formula.
BFMEKeyboardObjectFormats is a descriptive inferred name, not a claim about
an original library symbol. GUID_Key is the SDK identity proven by its value
and use in the keyboard records. The local structs reproduce that SDK ABI;
no shared header or reference pointer was changed.

## Verified result

Code/GameEngineDevice/Source/Win32Device/GameClient/DirectInputKeyboardFormat.cpp
owns two data_rows.csv entries: the complete 4096-byte table in retail .text,
and its 16-byte GUID in retail .rdata. Both compiled sizeof probes agree.
The normal data verifier passes all initialized bytes and all 256 table
DIR32 relocations to GUID_Key. Normal scoped build also passes source claims
and both data rows. No function row, pin, raw pointer initializer, assembly,
or progress-metric exception was added. These are verified data bytes, not
new C++ function bytes, so current tools/progress.py gains nothing from them.

## Remaining consumer integration: reproducible verifier limitation

DirectInputKeyboardOpen.cpp currently defines g_00C7C9A4 as 24 raw bytes,
including the table's retail VA, rather than as a typed DIDATAFORMAT with a
relocation. That existing definition was left unchanged. Replacing its pointer
with BFMEKeyboardObjectFormats requires a separate verifier repair:

    import data_rows
    r = data_rows.Resolver(data_rows.load())
    assert r('_BFMEKeyboardObjectFormats') == {0x00A29F20}
    assert r('_BFMEKeyboardObjectFormats', False) == set()
    assert r('_GUID_Key', False) == {0x00CDF6B8}

Resolver.__call__ filters every data-pointer target by executable-section
characteristics. It therefore discards the explicit verified data row in .text.
This is a false rejection for typed data pointers to this table. A repair must
admit independently verified data ownership without admitting ordinary code
as data, and needs regression coverage. No check was weakened or bypassed.
Once repaired, replace the existing raw descriptor with a typed definition,
verify its 24 bytes and relocation as well as openKeyboard's full 188-byte
body, and inspect linker placement of the .text-resident data. No fresh linking
census or linked executable was run or claimed here.

## Coverage accounting follow-up

The progress tools now include matched data_rows.csv extents in .text in a
separate data lane. This credits 4094 non-0xCC bytes from the table (4096 in
the full-section diagnostic), with interval union preventing double counting.
It does not increase authored C++, function-row counts, or census linking.
The pointer-resolution and consumer-integration limitation above still applies.
