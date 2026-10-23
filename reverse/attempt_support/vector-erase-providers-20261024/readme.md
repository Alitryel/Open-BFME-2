# Existing vector erase providers

BFME2 input 9bc49e618f, published census b711de3634 (2026-10-23 14:28,
retail-truth-4). Model gpt-6.1-sol. Move ten existing named rows out of
StlportVectorEraseRangeFamily into already-emitted complete retail copies.
No source, flags, ABI, names, pins, aliases or element layouts change.
This adds no authored C++ coverage.

Preflight: all ten receiving whole bodies and relocations exact, zero
unresolved relocations, no wrong code-identity bindings in moved rows.
Existing row notes and same-name instantiations reached by receiving callers
preserve identity; address-derived element spellings remain codegen views,
without a new claim about application meaning or element layout.

BFME1 reviewed at verified f5140c1c: vendor _vector.h lines 466-488
preserve copy/destroy/finish range-erase semantics and clear's range-erase
call. PAVectorEraseRangeFamily003AF instantiates Elem003AF9E0 (0x10 B),
but its 77B PA bodies do not prove the BFME2 51B ABI or layout. No donor
repair or address imported; current BFME2 whole-body/relocation proof controls.
The prior full donor comparison is in link_library_providers_20261023/readme.md.

Excluded without editing source or row:

- 0x0007A7AA, 51B, Rva00309358Tokenize: exact range erase, but typed
  __copy_ptrs resolves to native 0x0007A401 with wrong/unknown identity.
- 0x005F97BC, 24B, Rva004F92E3Rva004F92E3: exact _Destroy forwarder,
  but typed __destroy_aux resolves to native 0x004F72ED with wrong/unknown
  identity. The independent rowed erase in the same unit has no such finding.

Both recorded blocked and claims released. No check was bypassed and no
new alias or pin was added. Existing historical conversion banks remain intact.

Rows (RVA, extent, receiving unit):

- 0x0004CD7C, 51 B, Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0004D47DParticleRender.cpp
- 0x0004CD20, 29 B, Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0004D47DParticleRender.cpp
- 0x000819EC, 51 B, Code/GameEngine/Source/Common/Rva004F92E3Rva004F92E3.cpp
- 0x002B4410, 29 B, Code/GameEngine/Source/Common/Rva002B6066Erase.cpp
- 0x00319B97, 51 B, Code/GameEngine/Source/Common/Rva00538E22Ctor.cpp
- 0x00565A94, 11 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp
- 0x00565A9F, 11 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp
- 0x00565AAA, 11 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp
- 0x00565AB5, 11 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp
- 0x00565AC0, 11 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp

Paired scoped legacy preview: 2,801 -> 3,067 B, **+266 B linked**,
5/6 units clean before and after. Collector retains independent unresolved
copy/destruction and wrong-selected helper blockers (complete diagnostics in
before.txt/after.txt). No self-strict, closed-strict or full-image gain claimed.

Acceptance: 142/142 function rows pass the byte gate; six string literals
verified, zero floats/imports. EH 9/9 exact, no baseline. Two pre-existing
code-identity findings unchanged, no new finding. Frozen-definition check,
check_csv and git diff --check pass. No source or verifier changes.
