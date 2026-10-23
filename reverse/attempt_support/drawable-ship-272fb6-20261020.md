# Drawable ship physics: 0x00272FB6, 1682 bytes

Recovered `Code/GameEngine/Source/GameClient/DrawablePhysicsXformShip.cpp` from
the complete existing bank and its tracked spring-operand-order handoff.

## Identity and provenance

Target facts: the rowed 208-byte `Drawable::calcPhysicsXform` dispatcher at
0x0027BA95 calls this exact protected thiscall signature for appearance case 9.
The whole boundary is 0x00272FB6..0x00273648, ending in `ret 8`. Retail accesses
the state at Drawable+0x13C and the fields/arguments documented in the source;
its random call contains the exact Drawable.cpp filename and line 3491.
The target method name remains address-derived, preserving the existing pin.

WorldBuilder CA79F0 and Open-BFME-1's Drawable.cpp guide the ship spring,
acceleration and bobbing structure; donor field meanings are provenance, not
independent proof of original BFME2 names. Donor revision reviewed:
`b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`. The already matched target dispatcher
and treads sibling support the relationship. No donor path is a ledger source.

## New explanation and result

The prior 1682-byte bank had one reversed memory/register operand pair in the
first pitch damping product, at +0x22D. A genuine inline spring-update helper
changes the optimizer's value context without changing the spring equation.
Using the same member helper for all four integrations reproduces every byte
and every callee. The helper's name is reconstruction structure, not a claimed
original retail method. It uses ordinary scalar values and the actual rate
reference; no volatile, barrier, empty branch, assembly or compiler pragma.

A bounded 14-trial comparison distinguished returned deltas, reference updates,
member updates and parameter records. Returned deltas retain the original
operand pair; a free value-argument updater moves the residue to acceleration
roll. A one-site free reference updater and the shared four-site member updater
are exact. The shared member form is retained for clear common spring logic.
The canonical Coord3D length/normalize definitions remain visible as in the bank.

## Verification

- Normal `explain_mismatch` at the production path: exact 1682/1682 bytes,
  no unresolved calls. Normal `add_match` verifies the whole row and removes
  the old bank: 1/1 function, one exact filename literal and eight float literals.
- Complete EH graph: EXACT 1, no missing objects and no baseline entry.
- `find_declared_unmatched --fail`: all definitions declared; no new markers.
- Whole-unit `place_bodies`: zero additional bodies or pins.
- `link_check --new-variants`: passes. The ordinary link preview cannot measure
  this new unit because it is absent from census d5ae1ce9c2; no census was run
  or modified. The existing frame-rate providers are used without new globals:
  logic VA DBA4E4 holds 5; client VA DBA4E8 holds 30.

The source uses `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc`, with the existing
Coord3DInline.h. No pin, header, baseline or verifier edits are required.
