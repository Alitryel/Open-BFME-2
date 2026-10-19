# EmotionTrackerUpdate nugget selector

Recovered native `0x004B13D8..0x004B15AE` (470 bytes) as
`EmotionTrackerUpdate::rva004B13D8()` in the official module source. The
address-derived method name is intentional: WB `0x01232340` establishes the
class and selector relationship, but not an original method name. No donor
source, new pin, assembly, volatile allocation lever or verifier change is used.

Input tree: `7a44bdd956`, BFME 1 reference
`b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`. Compiler: the normal VC7.1 RTM
profile, `/I. /O1 /arch:SSE /G7 /MD /EHsc`, with the configured STLport headers.
The BFME 1 reference supplies build dependencies, not selector identity.

## Evidence and semantics

Native entry follows the previous RET at `0x004B13D7`; its own RET is at
`0x004B15AD`, followed immediately by the next body. The update caller passes
the module root and consumes the returned nugget pointer. Native accesses
establish module data/object at root `+4/+8`, the nugget vector at `+0x90`, the
active nugget at `+0x9C`, forced kind/frame count at `+0xB0/+0xB4`, and the
flag/expiry/target arrays at `+0x24/+0x30/+0x60`. The declared interface bases
retain the root/secondary-update distinction from the parent investigation;
they do not claim complete reconstructed class definitions.

The selector computes two shroud sums from relationship masks, reads the
owner's experience level and scans every nugget with a pretested iterator.
Every continue advances it. The active-duration path and ordinary eligibility
path call the existing `EmotionNugget::CanBeActivatedFor` provider. The kind-6
path checks the target's template/status bits and compares the owner's and
target's existing `Object::rva0028B511()` results. Exhaustion clears the forced
frame count and retries recursively, as WB corroborates. The native compiler
turns this recursion into a restart jump. The prior farm bank's invalid
`*begin` loop and equal-arm/volatile levers remain removed.

## What closed the mismatch

The semantically repaired bank emitted 475 bytes: iterator allocation,
comparison and return placement differed. Making **both** existing lookup
bodies visible (`ObjectIdMap::find` and `GameLogic::findObjectByID`) gave the
compiler their read-only effects and restored the native iterator and return
layout: 468 bytes, with only the comparison's ECX reload missing. Showing only
the facade did not suffice. Both visible helper bodies independently reproduce
their already-owned complete 47- and 37-byte native bodies.

The actual owning-object accessor in the direct two-call comparison restores
native call order and the reload. Replacing the draft's artificial local-frame
aggregate with ordinary locals removes its extra stack slot and reproduces the
complete 470-byte body. The expression still short-circuits on the existing
template/status checks. Direct field comparisons, named result/reference
variants, comparison helpers, getter-body visibility and alternate compiler
profiles either retained the mismatch or made it worse. This is a source and
compiler-lifetime explanation, not a proven code-generation blocker.

## Verification

`production-selector-proof.txt` records the cleaned production TU's exact
470-byte result. `lookup-map-proof.txt` and `lookup-facade-proof.txt` record the
complete existing helper matches. `selector-alignment.txt` has zero structural
or register differences; its seven memory entries are absolute relocations.
Normal `add_match.py` admission passed the source, function, string, float and
import gates, removed the obsolete bank and recorded the landing.
`place_bodies.py` found no additional unclaimed bodies, and
`find_declared_unmatched.py` accepted every emitted definition.

The supported `link_check.py --new-variants --staged-peers` check passed.
The five external call providers were traced from the actual object's REL32
records (`provider-map.json`); their normal source gate passed all 60 bodies
across five sources (`provider-byte-gate.txt`). The two lookup definitions
were also rechecked in the final production TU, rather than only the draft.
These checks establish exact provider bodies and no new conflicting variant;
they do not assert a full census LINKS measurement.

`link_check.py --refresh --current-ledger` could not produce that full preview:
after the one missing EmotionNuggetOnDeactivation object was prepared with the
supported bounded command, 10,711 other current-ledger objects still lacked
census-grade compiler evidence. The check was allowed to refuse. No receipt,
census index, status row or verification rule was changed to bypass it, and no
maintainer-only verification runner was started. Global link status remains
unmeasured for this new source until the required receipts/census are available.

The parent update at `0x004B1633` remains a separate, nonmatching bank: 2194 of
2200 bytes, with the case-2 comparison order/lifetime still different. Its
selector prerequisite is now recovered. No parent row is added by this change.
