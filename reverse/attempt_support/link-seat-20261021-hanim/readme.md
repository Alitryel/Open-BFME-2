# Counted-holder setter link repair

At BFME 2 8ca40fecae, using the published retail-truth-2 census index from
c7845fd6e7 (2026-10-21 15:41), the rowed HAnimComboDataClass::Set_HAnim owner
was an exclusive definition. Counted-holder consumers emitted retail-exact
select-any copies. Change the owner to an inline, noinline definition and keep
its emission with an explicitly non-retail anchor, as existing WW3D owners do.
Its entire 37-byte body and relocation identities remain verified.

Paired current-object `python3 tools/link_check.py` previews used this exact
cohort before and after:

```
Code/Libraries/Source/WWVegas/WWLib/string_base.cpp
Code/GameEngine/Source/GameLogic/System/GameLogicDoXfer.cpp
Code/Libraries/Source/WWVegas/WW3D2/HAnimComboDataSetHAnim.cpp
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMeshHolderHold.cpp
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraHandleGet.cpp
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterDrawOceanWater.cpp
Code/Libraries/Source/WWVegas/WW3D2/HAnimComboBFME1.cpp
```

Before: 2/7 clean, 1,326 current linked bytes. After: 4/7 clean, 1,563 bytes.
The +237 B is 37 B in the setter owner and 200 B in W3DMeshHolderHold.cpp.
The string unit already links when its current GameLogicDoXfer peer is included;
its census-to-current difference is excluded from this repair's gain.
OceanWater and HAnimComboBFME1 retain unrelated blockers; the latter also has
a non-retail setter copy, which this repair does not excuse.

`./build.sh` verified the setter. `link_check.py --prepare-current` on the setter
and mesh-holder unit passed all 11 rows, references and strict reusable compiler
receipts. `find_declared_unmatched.py` passed. This is a legacy LINKED preview
gain; strict compiler receipts do not establish self-strict or closed-strict
placement, and no full link cycle was run.

A declaration-only setter in the mesh unit was tested and reverted: both
factories gained alias reloads and ceased matching. Their visible callee summary
is necessary. No reconstruction or new identity is claimed.

Reference linking repairs reviewed before selection: BFME 1 a1b87e2c (row-name
map binding) and bf91f4be (single Buffer destructor owner). Both support provider
binding as a lead, but neither directly supplies this BFME 2 change; the target
objects and existing BFME 2 inline-owner pattern are the evidence here. The
committed donor checkout remains 00c2ffbb23e9154fbe9970954afacb04e4943dd7.
