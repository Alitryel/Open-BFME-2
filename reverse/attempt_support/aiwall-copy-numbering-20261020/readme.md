# AIWall 0x004EACF5: copy construction and local numbering

Session: 2026-10-20, gpt-6.1-sol, owner `codex-desktop-01a158c7`.
Inputs: BFME2 master `063b128c47`, BFME1 reference
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`, default MSVC 7.1 profile;
bank flags `/O1 /G7 /arch:SSE /MD /DNDEBUG`.

The existing joint bank `reverse/attempts/0x004eadba.cpp` remains the best
candidate and is unchanged. Read its earlier handoff
`reverse/attempt_support/0x004eadba_20261020_w1.md` and the hans handoff
`reverse/attempt_support/004eacf5-20261020-hans/handoff.md` first. No new
production definition, symbol pin, or ledger row was added by these trials.

## Reproduced baseline

The static helper's complete retail boundary is 0x004EACF5..0x004EADBA,
197 bytes. Official `explain_mismatch.py` reproduces 197 compiled bytes,
no unresolved symbols, and four differing instructions. Retail computes
`apx` into xmm1 before `apy` into xmm0; the bank computes the same two
subtractions in the opposite order. Every subsequent instruction agrees.
The public caller at 0x004EADBA..0x004EAE9D (227 bytes) still depends on this
helper. These trials did not change the caller or establish a new identity.

## New hypotheses tested

1. Non-trivial coordinate copies, named return-value inlining, and by-value
   dot-product parameters could keep the input differences out of a
   single substituted scalar expression. Tested 108 combinations: x/y or
   y/x user copy constructor or implicit copy; named returned difference,
   two-point constructor, or member assignment; dot helper by value/by
   reference/member; accumulator or sum; both assignment orders. All compiled
   to 197 bytes, but had 14 to 54 instruction differences. No improvement.
   This tests non-trivial copying, beyond previously tested plain aggregate
   assignments and inline scalar dot expressions.
2. The documented initialized-local numbering effect in `docs/recipes.md`
   might explain the swapped subtraction pair. Tested counts 0..80 for each
   of four forms: scalar differences or a member-assigned Coord2D difference,
   with canonical Coord2D.h or the existing Coord2DCtorView.h. All 324 compiled.
   Counts were completely inert: scalar forms retained four differences,
   member-assigned forms retained sixteen. The constructor companion header
   did not improve either. No artificial padding belongs in the bank.

Both generators use `permute.Scorer` and isolated depth-two directories
under `build/`; they do not overwrite production objects. The preserved
`.py.txt` files are diagnostic generators, not build inputs. Copy them back
to `build/aiwall-probe/*.py` to reproduce with the same existing joint bank.
Instruction differences compare complete Capstone mnemonic/operand tuples;
they are not claims of semantic or byte-gate acceptance.

## Remaining prerequisite and reassessment

The earlier known distinction remains: an aggregate forces x-before-y but
changes the direction and length temporary's XMM colours; scalars give the
right colours but reverse the input subtraction pair. No new bytecode or
layout fact was found. Previous work already tested branch/tail structure,
pointer use counts and parameter order, arithmetic spellings, carrier types,
compiler profiles and optimization flags. These two independent additional
hypotheses did not justify replacing the better bank. Release both retail
claims and the AIWall.cpp file claim; resume only with another supported
explanation of the entry scheduling/colouring interaction.
