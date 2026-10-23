# Debug network base-deleter link repair, 2026-10-22

Before and after use the published legacy census/index at 08160bc2c9,
2026-10-22 17:08, with the same two current objects substituted together.
Starting tree: 891ac62816. BFME 1 verified donor pointer reviewed:
37c3022de1ab944c7ffe536440d637dc8199091c; no donor update or source import.

`DebugIONet_Create.cpp` (106 B counted) and `DebugIONetConstructorThunk.cpp`
(70 B) each failed solely because their emitted DebugIOInterface scalar deleting
destructor differed from retail. The rowed provider is the 31-byte frameless
0x0003F340 body in `Rva0088FAA0DebugIOInterfaceDestructor.cpp`; both caller
units globally specify /Oy- for their native EBP-based EH bodies.

Scoped frame-pointer optimization around only the base class makes the emitted
base helper compatible while retaining /Oy- on the derived constructor/factory.
Removing file-wide /Oy- instead failed both parents and cleanup labels; that
trial was discarded. This is a demonstrated MSVC code-generation prerequisite.
No source identity, ABI, vtable slots, pins, or baseline changed. The census
lists precisely these two units for this exact scalar-deleter blocker.

Acceptance:

- Before: 0/2 units, 0 B linked. After: 2/2 units, 176 B linked (legacy preview).
- Byte gate: 5/5 rows; parent-EH evidence resolves renumbered funclet labels.
- `link_check --prepare-current`: both explicit providers pass strict reusable
  receipts and byte gates (self verification; closure not measured).
- `link_check --new-variants` and declared-definition checks pass.
- Full EH verification run on both touched units before commit.

No closed-strict gain, full-link result, or authored-C++ coverage gain claimed.
