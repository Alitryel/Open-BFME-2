# Wide-string allocator emitter repair

Two owned units, `stlport_wide_string_insert_aux.cpp` (RVA 0x12D10, 232 bytes)
and `stlport_wide_string_append.cpp` (RVA 0x13160, 241 bytes), fully inline their
private allocator proxy but also emit an unused out-of-line copy. Those copies
lose to the first definition in the census index. Applying `dllimport
__forceinline` to the existing proxy method removes just that unused definition
from each object, without changing allocation semantics or the allocator call.

This uses the technique reviewed in BFME 1 commit
66b19a8e95a4add525ef808fcea088e306798e2b. BFME 2's own bytes, COFF bindings,
relocations and local link checks establish applicability; no donor identity,
layout, address or linkability claim is transferred.

The saved before objects and current after objects were compared using the
normalized-section method from the existing shader-copy-link-20261015 proof.
All retained COMDAT bytes/relocations, other nondebug sections, external bindings
and directives are identical. Each removed allocator has zero incoming nondebug
relocations; no import, alternate name, pin or replacement body was added.
`proof.json` includes hashes, removed bytes/digests and per-source results.
Scratch scripts and original objects remain under `build/wide-proxy-link-20261015/`.

Both phases refresh the two cohort objects into separate deep copies of the
same runner index (825b86983f, underlying census 5986a99448) at BFME 2 commit
2a46a4801de86e9daa104a4b0d0d8a79b28e6537. Allocator COMDAT-loser findings fall
from two to zero. Selected-definition findings remain two. Local legacy linked
bytes remain zero, with zero new authored bytes and no self-strict or
closed-strict gain claimed. No persisted index/status/census was changed.

Remaining blockers:

- `_M_insert_aux` keeps an earlier wrong copy. Indexed providers include
  `stlport_classic_locale.cpp`, `stlport_wide_money_get_long_double.cpp`,
  `stlport_wide_string.cpp`, and `stlport_money_get_wide.cpp`; this owner emits
  the retail-proven copy.
- Wide forward-iterator `append` keeps an earlier wrong copy. Indexed providers
  include `stlport_wide_string.cpp`, `stlport_wide_stringbuf.cpp`, `PeerThread.cpp`,
  `PeerTextRequestValidate.cpp`, `AptOnlineCustomMatchCallbacks.cpp`, and
  `AptOnlineCustomMatchMessageHandler.cpp`; this owner emits the retail-proven copy.

These provider lists are census leads, not fresh measurements of those unowned
units. Repairing them needs separate claims and byte/consumer checks; this repair
does not suppress any referenced definition or claim full linkability.

Acceptance: `./build.sh` 2/2 exact; `link_check.py --prepare-current` before/after
strict reusable receipts; ordinary local check confirms only the two selected
blockers remain; `--new-variants` none; `eh_verify.py` no EH rows or missing
objects; data enforcement and convergence zero findings; class and frozen-file
checks pass; placement rescan has no additional bodies or pins. A maintainer
full link cycle remains outstanding.
