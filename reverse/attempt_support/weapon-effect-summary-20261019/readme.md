# Weapon coordinate lifetime and outlined-callee summaries

Inputs: BFME2 31fa5a596fc4cddfc00aaeab8aeb65aa99972eb8,
BFME1 verified pointer 6b9d92bf92debd03e4357462bab41f701651e67c.
The complete banks and prior return-value, real-caller, lifetime-visibility,
typed-boundary and alias-option handoffs were read before these experiments.
Both banks and production source remain unchanged. No row or pin was added.

The real privateFireWeapon caller, 0x002CE30A..0x002CE6C5, still emits955B with
eight non-relocation byte differences: offsets5,18,1D,E6,130,1A9,2E4,2F1 hex.
Retail frame24/bonus EBP-24 versus candidate frame30/bonus EBP-30 remains the
only difference. Real getLinearPosition, 0x002CB594..0x002CB65B, is199B exact
with this caller. It must not be landed through a synthetic driver or an
invented standalone standard-convention pin.

## Legal result lifetime

Lifetime-extending the by-value linear result through a const reference,
making it a named const object, and directly copy-constructing the scatter
coordinate all preserve955B and the same eight differences. Replacing scatter
copy construction with three member assignments emits947B,307 differing bytes
in the common span and8 missing bytes, both alone and with the linear reference.
Every variant's whole199B helper remains exact; diagnostic resolution has no
unresolved names. The lifetime-category explanation is refuted.

## Specific inline/noinline effect-summary hypothesis

Matched Bfme5ThirtyFour.cpp uses an inline, noinline outlined COMDAT to expose
callee argument effects without inlining. Both actual weapon dispatch providers
ignore their bonus argument, so this was a supported new test beyond the prior
plain-provider visibility experiment. Merged the actual complete fire provider
and special provider ahead of the real caller in an isolated diagnostic TU.
Compared noinline plain definitions with noinline inline definitions.

In BOTH controls, the whole helper199B, firing provider1561B and special
provider93B reproduce all retail bytes and relocations. Only after each whole
body passed was its address admitted to the in-memory diagnostic resolver.
The caller remains955B with precisely the same eight differences and no
unresolved symbols. The COMDAT effect-summary explanation is refuted too.

Raw sources, preparation and measurement scripts, explain output and JSON
receipts are under build/weapon-result-lifetime-oct19 and
build/weapon-effect-summary-oct19. The normal explain_mismatch compiler path
compiled each isolated path; no build.compile_source call was made. The latter
prepare.py reconstructs the merged diagnostic TU from the two tracked provider
owners and existing caller bank. Provider-source adaptation preserved every
accessed offset and was independently checked by their whole-body results.

The best candidate remains reverse/attempts/0x002ce30a.cpp, unchanged; the
separate helper bank also remains unchanged. No qualifying improvement to bank.
No shortened bonus, explicit overlap, expired pointer, additional assembly,
production compiler override or verifier change was introduced. No new viable
source explanation was identified after these trials; release both claims and
continue with independent work. Earlier target/donor identity and layout
evidence remains in 002ce30a-real-caller.md; no new target identity is inferred
from diagnostic byte equality. t=18min model=gpt-6.1-sol.

## Newly pulled AnimalAIUpdate declaration-order lead

After the first verdict, upstream8eab6fbd26 landed the previously blocked
AnimalAIUpdate stack packing. Read its full current owner and tracked stack
packing evidence before a separate bounded follow-up. Moving the linear
coordinate declaration before its loop emits965B/frame3C/519 common-span byte
differences. Moving scatter declaration before its victim branch emits938B/
frame30/473 differences. Both emit946B/frame3C/539 differences. Separate
function-scope coordinates before or after bonus emit946B/frame48/539;
shared function-scope controls emit946B/frame3C/539. Every whole199B helper
remains exact with no unresolved diagnostic names. The real declarations
stay alive during calls and no dummy tail local was introduced. No closer
candidate: both banks unchanged. Raw sources/results remain under
build/weapon-declaration-order-oct19. Additional t=3min model=gpt-6.1-sol.
