# AnimalAIUpdate::update 0x47EDC9 (2916 B): 3-angle pass 2026-10-19

Result: partial. The bank now compiles to 2923 B (7 over) with frame 0xA4 against retail's 0x8C.
Against the previous bank, structural regions drop from 3 to 1 and non-reloc operand diffs from 28 to 23.
Model claude-opus-5-5.

## Changes in this bank
- **Semantic fix:** the returning-home threshold is 5.0f. Retail's constant at 0xBC4EB8 is 5.0f, as in WB.
  The previous 10.0f was hidden by reloc masking.
- The emitter radius test uses WB's `(float)(r*r)` form with no `int radius` local. This fixes the +0x604 register.
- WB-style `delta.sub(pos)` / `destination.scale(distance)` member calls, and no function-scope position pointer. Both are byte-neutral.

## What the 7 B are
- 6 B: kind at -0x94 and accept at -0xB0 need disp32, where retail's -0x7C/-0x98 are disp8. This follows from the frame.
- 1 B: retail emits `push [esi+0x74]`; ours emits `mov eax,[esi+0x74]; push eax` (the argument load of findObjectByID(enemy->getID()), at +0x450).

## Frame maps

Retail (each object top-aligned in its region):

| Offset | Size | Contents |
|---|---|---|
| -0x24 | 12 | emitter dest, alive filter at -0x20 |
| -0x28 | 4 | stateID, then radius^2 |
| -0x3C | 20 | relationship filter, overlapping {returning delta, no-emitter delta, no-emitter dest} at -0x34 |
| -0x58 | 28 | masks |
| -0x98 | 64 | accept, with kind at -0x7C |

Ours: {returning delta, emitter dest, alive} at -0x24, stateID -0x28, no-emitter dest alone at -0x34,
relationship filter alone at -0x48, no-emitter delta alone at -0x54, masks -0x70, kind -0x94, accept -0xB0.

## Mechanism found (types seat): the last address-taken stack object is pinned
The last address-taken object in the function never shares a slot, and the later objects stack below it.
- Remove the no-emitter dest: relationship goes to retail's -0x3C.
- A trailing `{ Coord3D probe ... isReachableLayer(&probe); }` before the final log: frame 0x98, relationship -0x3C.
- A trailing address-taken 4-byte probe passed to fprintf: frame exactly 0x8C, with mask/kind/accept/relationship
  all at retail's offsets (2942 B because of the extra code; this was a mechanism probe only).

Retail's source therefore has some construct after the no-emitter block that takes the pinned role and merges
into an existing 4-byte slot. Finding it (WB's tail: final log/return handling) is the next lever.

## Ruled out
- Types:
  - All filter types and sizes already match retail (relationship 20 B inline ctor, alive 8 B, kind 36 B
    ctor 0x3959FA, accept 64 B ctor 0x4584D, masks 28 B).
  - WB filters are larger only because the debug build adds m_prev.
- Coord3D form: plain POD Coord3D.h gives 2948-2951 B. A Coord3D dtor view is inert; retail has no Coord3D EH states,
  while WB does.
- Scope:
  - The no-emitter delta in its own {} gives frame 0x98 but joins the wrong group.
  - Deltas as by-value temporaries give 0x98, but the no-emitter dest stays pinned.
  - Named filters in blocks: nd 283-405. Destinations declared early: 471+.
- WB literal: the named dice roll and WB's enemy getID() re-reads are worse.
- Visible GetLengthEstimate2D (select-any in coord3d.cpp): moves the returning delta into retail's group but stays at 0xA4.

## WB 0x011B2240 scopes (EH states)
- Returning delta: block-scoped (state 1).
- Emitter dest: declared in the wander else-arm (state 7).
- No-emitter delta: covers the whole no-emitter else block (state 8), enclosing the no-emitter dest (state 9).
- Both queries use full-expression filter temporaries, destroyed before the `if`.
- WB is the bfme2 (not patch 1.03) revision, so its scopes may differ from retail.
