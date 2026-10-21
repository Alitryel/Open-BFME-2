# BigObf wrapper data providers

At the unchanged BFME 2 checkout, current-object `link_check.py` against the
published census 17918792f6 (2026-10-21 09:22) reported zero linked bytes for
`BigObfHookWrappers.cpp`, solely six unresolved `g_ObfSlot...` records. Defining
those existing names in the same unit changes that prediction to 1,958 linked
bytes (22 functions). No authored C++ function bytes were added.

Target evidence: every wrapper's existing verified relocations read its slot
base at offsets 0, 4, 0x88 and 0x8c. All six complete 0x90-byte spans are in
retail .data and contain only zero bytes; none overlaps an existing data row.
The existing donor-derived type preserves opaque intervening bytes. The new
rows and definitions preserve the address-derived names and do not assert a
recovered semantic identity or meaning for the opaque bytes.

Checks: `find_declared_unmatched.py` passes; `./build.sh` verifies all 22 code
rows and six data rows; `data_rows.py --check`, `check_csv.py` and
`data_check.py --converged` pass. `link_check.py --prepare-current` passes the
strict reusable receipt and byte checks for this unit. The link gain above is
the per-unit prediction against frozen peer definitions, not a closed-strict
closure result; no full link cycle or census was run.
