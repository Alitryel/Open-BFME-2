# HordeContain deferred map lookup profile

The current HordeContain::onContaining object alone loses its int/int map
_M_find copy. It is frame-built under the application /Oy- profile; retail
0x00388F63 is the canonical 56-byte frame-omitting implementation. The unit
already has the native inline left/right field accessors. Apply the verified
Rva000BBE29 repair's deferred-helper profile after the application definition.
Its 469-byte matched body retains /Oy- and is byte exact. The helper's entire
COFF section is exactly retail's 56 bytes, with zero relocations, no masking,
and no bytes beyond the native extent (native-proof.json).

Same-source-set current-object legacy previews: Horde 0 -> 468 nonpadding
linked bytes; the explicit canonical owner remains 1683 -> 1683. Combined
1683 -> 2151, gain 468. Normal byte/literal/import gate and self-strict
prepare-current pass 1/1. Closed-strict closure and runtime are not measured.
The same indexed int/int _M_find loser occurs only in this unit. Existing
broader map-helper repairs and known blocked variants were reviewed before
trial; no speculative sweep edits were made.

The prior verified repair evidence is
reverse/attempt_support/link-ten-20261020/18-map-find/readme.md. Donor review
remains at BFME1 5987fd1b859e86801d093256eadc6fb63d87785f; the current
BFME2 owner and the production COFF/native comparison prove this profile.
This introduces one scoped optimization pragma, recorded by the existing
shadow hatch counter; no baseline is expanded and no executable bytes are
injected or lifted.
