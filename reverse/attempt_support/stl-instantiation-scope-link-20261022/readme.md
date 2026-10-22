# Restrict STL instantiation scope

At parent dc83965f1e, the current-object legacy link preview rejects
`stlport_rope_char.cpp` (147 matched bytes) and
`stlport_list_002b4dc1_insert.cpp` (133 matched bytes). The published census is
08160bc2c9, 2026-10-22 17:08. These are legacy preview gains, not a measured
closed-strict link cycle.

Both units explicitly instantiated a whole STLport container class to emit a
few recovered helpers. This also emitted unrelated methods. Rope pulled in
`__imp__putchar` and selected non-retail uninitialized-copy/deallocation copies;
the list pulled in undefined record comparisons. Instantiate the recovered
members/helpers individually instead. An address-returning anchor retains the
existing out-of-line atomic-swap body in the rope unit. No flags, layouts, pins,
retail identities, or ledger extents change.

Acceptance:

- `./build.sh` passes all 6 rope rows and all 4 list rows, including full byte,
  relocation, literal and import checks.
- `find_declared_unmatched.py` passes both units (the rope retention anchor is
  explicitly absent from retail).
- Current-object `link_check.py` changes rope 0 -> 147 bytes and list 0 -> 133
  bytes: +280 legacy linked bytes total.
- `link_check.py --prepare-current` verifies both providers together and writes
  strict reusable receipts (10/10 rows). This prepares self-strict inputs;
  it does not establish closed-strict link closure.

The same scope reduction was investigated in the money-put unit, but MSVC 7.1
hits C1001 at STLport `_alloc.h:253`; it was restored. The string-record vector
trial preserves all six byte rows but confirms the existing bank's assignment
identity blocker: its assignment pin at 26F4F4 belongs to a vector assignment,
not the scalar/string record assignment this unit emits. It was restored.
These negative trials are recorded in re_attempts.log.
