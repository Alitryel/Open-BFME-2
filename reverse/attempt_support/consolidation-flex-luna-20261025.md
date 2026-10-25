# Mechanical TU handoff, 2026-10-25

## Completed composition trials

- `Mouse.cpp` absorbed three unchanged accepted donors: `Rva001EDDC6Store.cpp`,
  `Rva001EDE45Getter.cpp`, and `Rva005A4660Copy.cpp`. The TU build passed
  24/24 matched rows, including two compiler float literals and one named
  import. `find_declared_unmatched.py` found no unmatched definitions.
- `HealContain.cpp` absorbed `HealContainCtor.cpp`; its 84-byte ctor row passed
  the TU byte build and frozen-file check.
- `WindowLayout.cpp` absorbed `Rva00538ADCFinish.cpp`; the TU build passed all
  three matched rows, including the 43-byte `0x00538ADC` body.

## Donor blockers left for a prerequisite pass

- HealContain `0x00466BE9`, `HealContainXfer.cpp`: merge trial fails with
  `C2061: syntax error: identifier 'Snapshot'` at
  `Code/GameEngine/Include/Common/BfmeXfer.h` lines 37 and 48. The module data
  parser (`0x00466AD0`) and pool-key getter (`0x00466B88`) are refused because
  their sources are keyed in protected path-keyed registers. No repair or
  register change was attempted.
- WindowLayout `0x00538C0E`, `BfmeQuickMatchScreenBaseDefaultCtor.cpp`: merge
  trial fails with `C2600`, because the generated special member function is
  not declared in the class first. `window_layout.cpp` rows are refused because
  that source is keyed in a protected path-keyed register. No repair or
  register change was attempted.

## Audit

`data_check.py --staged` and `tu_ownership.py --staged --shadow` reported no
findings for the verified merges. Scoped `link_check.py --new-variants
--shadow` over the five changed source files reported no new COMDAT variants.
The regular link preview declined `WindowLayout.cpp` and `HealContain.cpp`
because neither is in census `d2636bb381`; the next census will measure them.
Their function names, RVAs, sizes and byte-verified bodies are unchanged, so
only the row source owners changed. No data rows or global owners changed.
The path audit found no affected consumers in tools, hooks, workflows, source
includes or build inputs; remaining matches refer to unchanged destinations,
documentation or donor provenance. No linked coverage is claimed. All changes
are byte-neutral; net source files removed by the three merges: five.
