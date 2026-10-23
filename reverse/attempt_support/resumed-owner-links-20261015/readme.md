# Resumed owner and declaration repairs

Base: 0e400b433. Resumes the ordinary unfinished linkage work from Claude
session 74165ef7-8aac-4414-98f2-14d1c8683fb8 in worktree 3528.

## Changes and evidence

- GettingBuiltBehavior's self-heal caller at 0x0045479A binds the already
  matched 0x00453124 BfmeThingE63::isValid owner with the same primary this.
  That provider now uses the already matched CastleBehavior lookup at
  0x00395708 and Object shroud query at 0x0028D2A2. Native REL32 destinations,
  cdecl/thiscall argument cleanup and result widths support these bindings.
  Donor view names and uncertain field interpretations remain local views.
- ScriptActions' player-ownership counter binds its 0x00376C50 call to the
  existing 82-byte provider. Its two STLport vector views retain three pointer
  words and four-byte trivial elements. ModuleData/Drawable are that existing
  provider's physical names, not newly claimed caller semantic identities.
- MilesAudioCache uses local comparison/construction helpers and a declaration
  of the existing set insertion provider to avoid competing emitted copies.
  This resumes r3-o1's saved patch, with the already-published iterator repair
  retained. The 0x00760C03 cleanup now names its verified readAudioFile EH
  parent; the compiler label is resolved through that graph after renumbering.
- Move the existing 31-byte 0x00051ADA row to MilesAudioManagerRva00059EAE,
  which already emits its exact body and relocations. Remove the redundant
  split provider. No new retail function or pin is claimed.

## Verification and measurement

The source byte gate and strict provider preparation verify all 19 rows in
five retained units. The exception-data verifier checks five exact EH graphs;
enforced data and converged-address checks have no findings. Normal commit
hooks are required. The placement rescan found zero bodies and zero pins. Raw acceptance output is in acceptance.txt.

Run `python reverse/attempt_support/resumed-owner-links-20261015/proof.py`
from the repository root after ordinary builds and strict source preparation.
The script checks current receipts, refreshes explicit current providers, and
removes only the actually deleted split provider from an in-memory index using
link_check.forget. It asserts the saved index did not change. Output is stored
in preview.txt. The local prediction is 2,021 linked bytes across five units:
63 + 346 + 523 + 842 + 247. These are per-object linkage predictions, not a
fresh census or a whole-program closed-link/placement measurement. The 523
includes a pre-existing 10-byte handler; no newly authored bytes are claimed.
Ordinary preview with the old, unchanged index can still report the removed
31-byte provider as a duplicate; the reproduction makes that adjustment
explicit. Census tables and history are not edited.

## Resumed-session disposition

The completed variant driver found no new exact body. Its 22 exact results
were already-exact seeds; most substantive searches failed in the Claude
command invocation. Camera 0x000865DB remains another worker's live claim.
The earlier WorldToCell patch is already upstream as 6f7415f75. The 33-file
STLport opt-in stash and verifier/receipt patches held for review remain
parked, as in the original session.

Official BFME1 master was fetched as 2558c65129397acfca97c5fbe985a462f6a42018.
The clean verified checkout/gitlink stays a7c38d3b2597121f178ab5190b3062478823257d.
An initial full fetch stalled and was stopped; bounded shallow fetch succeeded.
The previous-input full-verification blocker is documented in the prior
voice-record-link-20261015 evidence: 2,806 of 2,982 stale TUs still remained
after 21 minutes. This resumed batch does not advance the pointer or claim a
successful freshness update; it retains the verified inputs. No full census,
link cycle, nightly or boot runner was started.
