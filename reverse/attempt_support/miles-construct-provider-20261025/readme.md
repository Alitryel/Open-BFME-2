# Miles pointer-construction provider, 2026-10-25

BFME2 b7baa1eca9; published retail-truth-4 census at ce1b975697.
BFME1 input 0bf534ea7ccde110c456edb9cd2dd5dae823c953 is already paired-full
verified by dadf344e56; that donor linking review is reused. This repair uses
existing target caller, retail bytes and fold-pin evidence, not a new donor
class identity or assumed reference-count behavior.

The manager declares the external _Construct<PlayingAudioRef,PlayingAudioRef>
helper and calls it at its existing pinned address 0x000A9840. The pin names
MilesAudioManagerRva006A8DC0_Rva00584C9B.cpp as its fold-proof source, but
narrowing that provider to deque::begin stopped emitting the helper. Explicitly
instantiate this helper alone using the provider's unchanged trivial pointer
view. Do not restore the whole deque instantiation and its wrong pop-back copy.
No manager source, class definition, compiler flags, pins or ledger rows change.

The complete emitted helper is 17 bytes, 8b44240485c074088b4c24088b098908c3,
with no relocations. pin_admission.fold_proof_problems returns no problems,
proving the existing pin against the complete retail owner's body; the proof
receipt is retained here. No new name or address is claimed.

Paired current-object checks of the provider and manager, refreshing both
in memory against the same published index, give 19 -> 41,666 available
nonpadding authored bytes: **+41,647 B linked** in the legacy preview. This
is not a self-strict/closed-strict census gain or a link.exe result. Both
providers have strict reusable receipts, which separately does not prove
closure. No authored C++ coverage gain is claimed.

Acceptance: normal byte/data/literal/float/import gate 338/338 bodies across
the two units; 19 string refs, 32 float refs, 105 named imports; existing
funclet renumbering verified against parent EH graphs. Frozen definitions,
CSV, whitespace, complete fold proof, EH and new-COMDAT-variant checks pass.
Local full logs are build/seat7-miles-*. No verifier, baseline or hatch added.
