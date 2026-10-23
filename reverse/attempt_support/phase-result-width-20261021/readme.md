# Recovered LivingWorld phase predicate: separate source cases

Native2B5EB5..2B5F8A is a complete213B thiscall Boolean predicate with no stack
arguments. WorldBuilder D8FB00 independently names LivingWorldLogic::
IsLocalPlayerAllowedToEndPhase in the same original file and asserts7743.
worldbuilder.txt preserves the fresh local evidence. The native call sites,
field accesses and RET0 establish the ABI and used layout separately from
the debug name. Existing callers' address-derived spelling is retained;
no name, global or pin was replaced. Source is the existing home TU.

## Decisive change

The original .995 bank emits213B with one wrong default-branch byte at+63:
it reaches case4's integer-zero block2B5F35 instead of byte-false2B5F85.
Keep equivalent true cases3 and6 as separate source bodies, keep cases1/5
grouped, and return false directly from default. In the natural0..6 case
order this compiles every native instruction, extent and relocation exactly.
The equivalent0361542 case order also matches. Grouping3/6 in source loses
the distinction even though their eventual instructions are shared.

Case4 computes an integer exactly0 or1. Its native return consumes the
Boolean byte, while direct integer-to-bool spellings add normalization.
The production implementation copies the byte through unsigned-character
access into a bool object, whose representation is valid0/1 on this target.
It does not read an int through a bool alias. All five character-reference
and fixed-size-memcpy controls are exact; no asm, volatile, barrier,
optimizer pragma, dummy helper, new private layout or new pin is needed.
The unused forceinline member from the old bank is omitted.

## Full home admission and limits

The entire4041-line prior home was reviewed, including its existing layout,
164 rows and remaining declared definitions. A friend grants the already-used
caller ABI view access to that established layout; no second LivingWorldLogic
view is introduced. The actual existing typed TheCampaignManager global is
used. Normal add_match verifies165/165 functions, eight strings, one float
and all imports; all36 EH-bearing rows are EXACT with no missing objects.
place_bodies finds no additional bodies or pins. The old attempts bank was
cleared by add_match; prior-bank.cpp.txt retains it for the replay controls.

The owning TU retains pre-existing link blockers (all listed in the published
census), so this is not a claim that the full unit or game links. The joint
preview finds two direct peers newly LINKS (+201 non-padding bytes predicted),
one other peer already LINKS, and another still blocked by two unrelated
constructors. This is a static preview, not a new census or runtime result.

## Controls and replay

verification.json audits all85 source trials from existing COFF objects:
actual emitted size, complete patched bytes and every unresolved relocation.
Eight are exact. It separately identifies two invalid signed-one-bit
equality-to1 controls; these cannot support recovery. Fifteen initial
wrong-profile trials were discarded after detecting the bank's missing
home flags. Their240B baseline is not a comparable control.

The unsuccessful home-profile families are byte stores/unions (stack traffic),
enum/one-bit results, whole guard placement and full direct-bool returns.
The successful case-copy family was found by the full object audit, not by
assuming a diagnostic exit0 means exactness. Replay scripts use the retained
prior bank and isolated build/ sources. Run results-home before guards,
ranges and case-copies; clean after case-copies; byte-copy after clean.
The source patch and final verification summary identify the production body.

## Paired shadow identity audit

The normal commit hook passes but reports11 shadow identity findings. A paired
comparison restores the prior source, compiles it through ordinary
explain_mismatch, runs the unchanged identity checker, then always restores
the committed source and runs its full ordinary byte gate again (165/165).
The earlier source has9 findings; the same five non-funclet binding findings
and four definition findings remain unchanged. The new predicate's eight
code references all classify owner.

The two additional messages are literal compiler-label collisions: ledger
$L32036/$L32037 now happen to name unrelated actions. The byte gate uses the
verified CheckHeadToHeadBattles EH graph to locate their real actions as
$L32247/$L32248 at7768F9/776901. Both complete8B actions and their actual
callees are unchanged before/after and strict patched-byte exact. The shadow
checker instead reads the literal old labels, which happened not to exist
before. shadow-comparison.json and shadow-funclets.json preserve this proof.
No verifier, ledger label, baseline, whitelist or binding was changed to
silence the diagnostic; tooling follow-up is logged separately.
