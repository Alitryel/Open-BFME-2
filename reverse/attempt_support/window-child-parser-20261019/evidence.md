# Recover the child-window parser in its real owner

`parseChildWindows`, retail RVA `0x00316CF8`, is the complete 407-byte body
through `0x00316E8F`. Its purpose and structure follow the same-name Zero Hour
source already carried by `GameWindowManagerScript.cpp`; target calls, literal
sequence, stack/default state and both tab-control checks independently support
that identity. This does not rely on the stale structural picker's `parseWindow`
signature or an unrelated WorldBuilder match.

The real owner already compiles all the relevant file-static helper bodies and
their compiler-private conventions together. In this body File arrives in ECX;
the window and buffer are stack arguments. The original standalone bank's
description of this ABI is wrong. Recompiling the owner first gives 404 bytes,
with the first difference caused by a virtual-call encoding, not register
allocation. Two target-supported interface corrections close the whole body:

- Destroy each saved current child through the existing `TheWindowManager`
  global at vtable offset 0x8C. A declaration-only local slot view preserves the
  established integer return type and one window parameter. The donor manager
  declaration selected offset 0x78, whose call encoding was three bytes shorter.
- Scan the command string through the existing local File slot view at 0x24;
  the donor File declaration selected 0x28.

The source's original walk saves the next child and then destroys the current
one. It parses the global default colors and nested WINDOW entries before
checking the window stack and fixing the tab-control pane list. The old farm
bank instead assigned `child = next` before destroying it, addressed per-window
colors, and inserted an equal-arm conditional. That unreviewed body is discarded
by `add_match.py`; none of those changes are imported.

Normal byte verification passes all 23 matched bodies in the owner, including
the complete child parser, with all string/import checks. Exception metadata
verification reports four exact rows, no baseline or missing objects.
Converged-data and declared-definition checks pass. The placement rescan finds
no additional bodies or pins. No header, compiler flag, pin, alias, synthetic
caller or scheduling device is added.

The existing owner remains unlinked in the census preview (0 -> 0 linked bytes):
its previously present FunctionLexicon/font/Unicode/window-method imports and a
list erase provider remain unresolved or conflicting. This does not claim a
linking repair. The paired unrowed `parseWindow` is being investigated in the
same owner next.

Reference pointer: `a18d9ed50607e9175de4d6568798d7d73119de09`.
Starting BFME 2 revision: `0789d34c28`.
