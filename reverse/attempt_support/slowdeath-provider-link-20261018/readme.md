Slow-death provider repair, 2026-10-18

Inherited BFME1 64d369b90170 inputs/reference/shims/slowdeathmoduledatadtor
as an include view in HelicopterSlowDeathUpdate.cpp. It is the original ZH
header with only an explicit virtual destructor declaration. It prevents
this TU from emitting the ZH-layout destructor in front of BFME2's exact
142B destructor at RVA0045E4A5. The BFME1 comment's RVA002095F0 is donor-only;
BFME2's existing row supplies the target identity/address and four-phase
layout. No donor layout is promoted to a new target claim. The changed cl
include directory exists and contains the intended header; byte preparation
receipts track that dependency. No header or submodule pointer was modified.

Same-index paired ordinary legacy link_check at index1a1c90e405 / census
c2c5ac8c27: 0/5 clean,0B ->3/5 clean,219 linked nonpadding bytes. Newly clean:
ClearanceTestingSlowDeathBehaviorModuleDataCtor.cpp159B,
ClearanceTestingSlowDeathBehaviorModuleDataDtor.cpp55B,
GiantBirdSlowDeathBehaviorModuleDataDtor.cpp5B. Helicopter remains excluded by
independent unresolved names; the base provider remains excluded by
SlowDeathSoundVec construction and UpdateModuleData copies. Their bytes are
not counted. No closed-strict closure gain is claimed.

./build.sh all five providers/consumers:11/11 exact, float/literal/import
checks pass. link_check.py --prepare-current:11/11 exact with strict reusable
receipts, explicitly no link-closure check. Frozen-source guard passes. Raw
logs:build/seat-slowdeath-{before,after,gate,strict}.log. No full link cycle,
census/status write, new pin, alias or data symbol. BFME1 freshness update
blocker remains the previously recorded Rva0007DF07 vtable DIR32 ambiguity.
