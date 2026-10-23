# Camera movement: planar construction closes the slide dot

Target PolygonTrigger::adjustCameraMovement is native002E3AA8..002E3D7B,
723 bytes ending RET16. WB00ABA7D0 independently supplies identity and the
planar construction/subtraction, boundary intersection and optional slide
sequence. The entire existing home, bank and previous visibility, member-
mutator and floating-parenthesis handoffs were reviewed. No production code,
pin, canonical header or matched row changed.

The prior clean bank emits713 bytes. Restoring WB's two-dimensional source,
destination and copied delta construction, then subtracting through the planar
member, emits715 bytes and makes the slide dot native: delta is loaded into
fresh XMM registers rather than folded into the multiplies. All eight tested
planar construction/dot/destructor forms reach the same improvement. The saved
bank uses a TU-local derived CameraPlanar view with the canonical eight-byte
Coord2D base; this models observed operations, not a new original class name.
No third dot term, volatile read, fake effect or padding is introduced.

The remaining difference is the final scale/add block. Native reloads the
remaining scalar three times and loads candidate x/y before ADDSS; the candidate
reuses scalar registers and folds those candidate loads, saving eight bytes.
The improved instruction alignment agrees before that tail apart from branch
displacements caused by its shorter extent. The complete native body and both
residual disassemblies are retained.

Thirty-five completed diagnostics cover:

- Five real-provider/frame-policy controls motivated by the newly measured
  ArmyDefinition predecessor-availability finding. These all retain the old
  713-byte body. They do not establish a general refutation of compiler state.
- Eight planar constructor/copy/subtraction/dot models: all715 bytes.
- Eleven real spatial copy/assignment/destructor type controls:715 or736 bytes.
- Six spatial assignment and reference-return Scale/Add chains:715 or736 bytes.
- Five provider-alias controls. An opaque point predicate gives722 bytes but
  introduces a new z reload and retains the x/y folding; it is not closer.
  A typed planar point predicate stays715. Hiding the three real math providers
  changes the frame or gives730 bytes. No exact result was obtained.

Actual COFF extents and unresolved references are recorded for every input.
The new bank has zero unresolved calls. verification.json defines its score
as identical aligned retail instruction bytes after COFF relocation and branch
displacement masking:644/723 for the old control,662/723 for the improved bank.
This measured score is not comparable with the old handoff's estimated0.95;
the old source is preserved verbatim. Neither score proves a byte match.

Replay order is state, planar, then spatial/tail/alias. Each driver uses
ordinary explain_mismatch and distinct ignored build/ objects. state reads
the retained prior bank so landing this improved partial cannot change its
control. Earlier independent control-flow, lifetime, layout and compiler-
profile investigations were reassessed rather than repeated. Further work
needs a supported cause for the tail's reload/folding difference. The claim
is released; no nonmatching reconstruction is retained in Code.

Inputs and source hashes are recorded in verification.json. Flags remain
O1/DNDEBUG/MD/SSE with the existing canonical coordinate headers; the Oy-
variant is diagnostic only. gpt-6.1-sol; about18 minutes.
