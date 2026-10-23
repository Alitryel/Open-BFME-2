# FoundationAIUpdate::construct, 0x0045569D

The native extent is 1174 bytes, 0x0045569D..0x00455B33, ending in
`ret 0x18`. WorldBuilder 0x011715D0 identifies FoundationAIUpdate::construct.
The matched constructor installs its interface vtable 0x00C1A690 at +0x20;
slot 7 and the matched 0x00456134 caller establish the receiver and arguments.
The construction body reads the owning Object at interface-this minus 0x18.

Native calls and accesses establish the construction behavior: create the
template on the player's default team, retain the foundation as producer,
choose orientation from the keep/castle relationship, apply construction
status and health, position the object, dispatch Lua event 16 when configured,
notify the player and pathfinder, copy the castle-member IDs, charge the
player, and propagate the foundation's value and upgrades. The two member
IDs are at +0x14/+0x18; the existing checkValid body independently passes
+0x14 to GameLogic::findObjectByID. Module-data mode is +0x0C and the castle
orientation flag is +0x74. The source's address-suffixed helper names retain
the existing ledger identities rather than asserting newly recovered names.

Both native control flow and WorldBuilder require ID copies under
`newMember && oldMember`, with cost additionally guarded by `!isRebuild`.
Earlier diagnostics that moved cost outside the member guard were invalid.
The landed body preserves both guards and their nesting.

## The closing compiler finding

The faithful bank emitted 1175 bytes and an exact EH graph. Its first
divergence was +0x345: native retained the secondary-interface receiver in
EDI through onStructureCreated, the module lookups and the final propagation;
the bank used EAX there and reloaded it into EBX later. newMember consequently
occupied EDI instead of native's EBX.

A c2.dll allocator trace isolated the choice. At initial priority calculation
(0x82897/0x82919, relative to c2.dll base 0x10700000), the ID-copy block added
`6 * 4 = 24` to each member pointer's priority. Their totals were newMember 34
and oldMember 32. In the invalid hoisted-cost diagnostic that contribution
was `6 * 2 = 12`, giving 22 and 20. Their reference counts and costs remained
4 and 8. The copy block's flag test accounts for the additional priority.

As a causal diagnostic only, setting newMember's priority to 22 at work-list
insertion (c2+0x82B26) made the unchanged faithful source emit all 1174 native
bytes outside relocation sites, with an exact EH graph. Changing oldMember
alone did not. Editing the priority after list insertion was inert because
the list had already been sorted. Modified-compiler objects were never used
for the ledger or production verification.

The source-level solution is a volatile **by-value** rebuild flag. Reading
only the nested cost guard through a volatile reference also closes the
body, but the ordinary `volatile Bool isRebuild` parameter needs no cast.
This preserves the Bool ABI and the local argument value, while preventing
the cached flag candidate from changing the copy block's priorities. The
qualifier is an evidence-backed code-generation choice, not a claim about
the unavailable original declaration.

An unmodified-compiler trace of the winning source confirms the mechanism:
the flag is absent from the copy block's register-candidate list, its factor
falls from 4 to 3, and the member priorities become 28 and 26. The ID loads,
stores and nested cost condition remain byte-exact.

This session generated 3102 source combinations: actual BFME1/ZH module
headers (2), lookup forms (512), inlined continuations (512), six visible
early callees (729), actual STLport map lookups (64), pinned compiler profiles
(2), storage/32-bit ID-field forms (1024), and selective volatile flag/receiver
reads (257). Only the final family closed the faithful body, with 65 exact
instruction-stream candidates. Ordinary declarations, control flow and EH
context had already been investigated in the linked October 20--22 attempts.

## Placement and validation

The implementation lives beside FoundationAIUpdateSlots.cpp in
FoundationAIUpdateConstruct.cpp. The older slots unit declares slot 7 with
an int final argument and forwards its full word; adopting the recovered
Bool interface there also requires reconciling that caller declaration.
This recovery retains the verified secondary-interface ABI in its own unit.

Inputs: BFME2 8fc0b42eae; verified BFME1 pointer
37c3022de1ab944c7ffe536440d637dc8199091c. Repository MSVC 7.1 under Wine,
`/O1 /G7 /arch:SSE /DNDEBUG /MD /GX`. Reference module headers and ZH dozer
construction supplied structural leads; the recovered body and layout are
supported by native/WB evidence, not a byte-identical donor transfer.

`add_match.py` ran the normal source, complete-body, relocation, string and
float checks successfully. Independent comparison found zero differing
non-relocation bytes, including branch displacements, and `eh_verify`
reported EXACT for the three-state unwind graph, both local-static guards,
and the Lua list at [ebp-0x84]. The source has no undeclared definitions.
The required placement rescan found zero additional bodies and pins.

The published census predates this new unit, so the ordinary link preview
cannot measure it until a census includes it; the COMDAT-variant check can
still check the new object against the published providers, and passed.
The body-module accessor uses the established inline-only declaration to
avoid emitting a competing private-view COMDAT, with the construction body
unchanged. Code-identity shadow mode still reports the shared Coord3D
copy-constructor variant; this recovery does not change its shared header.

Model: gpt-6.1-sol. Earlier evidence:
`reverse/attempt_support/foundation-45569d-context-20261022/readme.md` and
`reverse/attempt_support/foundation-45569d-cost-nesting-20261021.md`.
