# BuildListInfo destructor and post-load reconciliation

2026-10-23, gpt-6.1-sol. Inputs: BFME 2 e46c379cfbd9e139181b94625808a0cc1192f70b,
unchanged donor pointer 96c88c73a5cd1a58fc2f8db691beea50acd996db, MSVC 7.1
with the unit's `/DNDEBUG /MD /EHsc`. Published census: retail-truth-4,
456ce161c5, 2026-10-23 06:28. No full link cycle was run.

## Evidence and repair

Target retail table RVA 0x0080D904 contains four entries: 0x0072A4BB,
0x004B3FD0, 0x00729EE3, 0x00729BBF (image base 0x00400000).
These are the existing BuildListInfo deleting destructor, complete one-byte
empty post-load hook, name getter and xfer. The existing constructor and copy
constructor use this four-slot Snapshot ABI. The destructor unit instead had a
five-slot private Snapshot, a manual base vptr restoration and an undefined
BFMERetailAsciiString destructor.

Use the shared Snapshot interface with its name slot and ordinary AsciiString
members. The native loop still calls slot zero with flags zero and explicitly
frees its returned pointer; a narrow ABI call view preserves that operation.
Declare the existing getter and xfer with the access used by their rowed names.
Define the empty loadPostProcess override and row its complete RET at 0x000B3FD0
using the existing BehaviorModule loadPostProcess owner. This adds no unique
retail coverage, address pin, or inferred independent implementation.

The table, loop offsets, byte identity and shared empty body are target facts.
The field labels are retained from the pre-existing reconstruction. No new
donor-derived identity or layout claim is needed. The private Snapshot allowance
and linker alternatename are removed.

## Measurement and acceptance

The same four current source objects were checked before and after, including
SubsystemNameGetters2.cpp as the existing getter provider. Before: copy ctor
0/253 B, default ctor 0/369 B, destructor 0/148 B, getter unit 268/268 B.
After: 253/253, 369/369, 149/149 (including the shared one-byte hook), and
268/268 B. Thus the paired current-object legacy preview improves from
268 to 1,039 B: **+771 B linked**, including 770 previously rowed bytes.
The tool's displayed census delta is only +402 B because the old census already
credited the default constructor; that is not the paired baseline used here.

Commands passed:

- `add_match.py` with `--icf-owner ?loadPostProcess@BehaviorModule@@MAEXXZ`:
  normal scoped byte gate, 8/8 destructor-unit rows including EH funclets.
- `link_check.py` on Rva0032A186Finish.cpp, BuildListInfoCopyCtor.cpp,
  BuildListInfoCtor.cpp and SubsystemNameGetters2.cpp: all four link cleanly.
- `link_check.py --prepare-current` on the same four providers: strict reusable
  compiler receipts and normal byte gates, 60/60 rows.
- `find_declared_unmatched.py` on the changed source and `check_csv.py`.

This is a **legacy scoped preview** gain backed by strict current compilation
receipts. It is not a measured self-strict or closed-strict link gain. Neither
the census/index nor committed link_status.csv was rewritten.

Local detailed logs: build/link-seat-buildlist-before.log and
build/link-seat-buildlist/{final-after,final-strict}.log. The full freshness
baseline waited on the compiler lock for over sixteen minutes without starting
compilation; only this seat's waiting process was terminated. The fetched donor
HEAD f5140c1cff6a58e16276fd6de6788186286953d4 differs from the retained pointer
only in README progress prose. The pointer and freshness stamp remain unchanged
pending the required full verification.
