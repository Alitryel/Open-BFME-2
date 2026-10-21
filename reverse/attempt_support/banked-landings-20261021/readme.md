# Last 50 previously banked functions that landed

Snapshot: `a2fe7665ed515a7aad86d5d4738d8e00af02d45c`.

Method: newest landing commits in Git history, one row per unique retail RVA. Each selected commit deletes a tracked `reverse/attempts/<rva>.cpp` bank and adds/changes a real matched ledger row at that RVA in the same commit. The inventory preserves each landing commit. Parent banks and complete landing diffs are recoverable from those commits; the local extraction also preserves them under `build/banked-history-20261021/`. Same-commit ties use RVA order. This is a retrospective of what landed, not an endorsement of every historical technique under later rules.

The 50 rows span 34 commits and 84,948 declared body bytes. That is a sum of final row extents, not a measured net-new unique-byte claim.

## Main findings

Seventeen functions belong to one BigObf batch and share one compiler mechanism. Treating that batch as 17 independent confirmations would overstate the evidence. Among the other 33 functions, 18 primarily closed through type, ABI, callee visibility or inline context; 10 through control-flow shape or variable lifetime; three through compiler symbol order; one through an accounting invariant; and one through proving an already-matching helper binding. Categories are analyst-assigned primary final unblockers; many changes touch more than one mechanism.

- **Faithful context changes code generation even when the call stays out of line.** Visible noinline math (BuildAssistant), visible hashing/constructors (DoXfer/AIPlayer), and helper definitions (XferSave/W3DDisplay) changed escape, throw and stack-packing information.
- **Replace abbreviated views with proven types and accessor chains before inventing more arithmetic variants.** The callback pair return ABI, SDK enum parameter, canonical AsciiString fields, full KindOf chain, and POINT/SIZE aggregate layout are concrete examples.
- **Control-flow and lifetimes before compiler merging matter.** Separate return arms, duplicate source definitions, label placement, and flat/scoped local declarations repeatedly affected final tail selection and stack homes.
- **Tiny residuals can be compiler ordering, but this is a measured diagnosis, not a general cure.** Declaration order fixed refresh; an extent reference fixed ClassifyWall; a counted-local shift fixed EmotionTracker. Other successful functions needed substantive context changes despite similar register symptoms.
- **A bank is a starting artifact, not the complete handoff.** Several landing commits refer to newer support candidates and disassembly/WorldBuilder evidence. Historical bank score is neither a standardized quality measure nor a reliable estimate of remaining work.

## Primary-cause counts

| Primary final unblocker | Functions |
|---|---:|
| Type / callee / inline context | 18 |
| Control flow / lifetime | 10 |
| Compiler symbol order | 3 |
| Accounting invariant | 1 |
| Identity / integration admission | 1 |
| BigObf shared compiler mechanism | 17 |

## Auditable inventory

| # | RVA / bytes | Function | Landing | Final unblocker |
|---:|---|---|---|---|
| 1 | `0x002FD344` / 781 | `?FindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PA_N@Z` | `2ca6e16c12` | Canonical four-byte AsciiString members restored native y/x/z latch reload order. |
| 2 | `0x002B5EB5` / 213 | `?rva002B5EB5@Rva002B5EB5@@QAE_NXZ` | `dc2fda309d` | Separate true case bodies and direct false default repaired the branch target; case-4 result width was preserved. |
| 3 | `0x0001C090` / 132 | `?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z` | `1e726cf7cf` | Real vendor ios_base/pair types and a non-POD growth result supplied the correct hidden-output ABI. |
| 4 | `0x0045AF14` / 527 | `?update@DualWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ` | `66537066ff` | Per-arm early returns and one shared notify call produced retail tail merging. |
| 5 | `0x004B1633` / 2200 | `?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ` | `78ccd150fc` | 29 inert initialized locals changed the symbol-number tie for the second layer comparison. |
| 6 | `0x0024797E` / 2195 | `?DoXfer@GameLogicSnapshot@@QAEXPAVXfer@@@Z` | `60c72c3990` | Visible correct AsciiString hasher made the iterator ++ chain inferred nothrow, enabling guard/iterator stack reuse. |
| 7 | `0x006EFBC0` / 5935 | `?Rva006EFBC0ObjectMemberLookup@@YAPAVAptValue@@PAV1@PBVEAStringC@@@Z` | `c8f8ffb429` | Return-label source order determined which blocks shared an epilogue; correct x87 unit flags retained. |
| 8 | `0x0004826C` / 4101 | `?gatherDebugStats@W3DDisplay@@UAEXXZ` | `9a4ca2c1db` | Duplicated lookup definitions in the RMB arms changed stack-packing weight, then merged to the same native block. |
| 9 | `0x00053BA1` / 320 | `?shouldPlayLocally@MilesAudioManager@@QAE_NPBVAudioEventRTS@@@Z` | `6f35948871` | Else-if/else viewType chain, separate null returns, and donor return order retained the EDI prologue save and native tails. |
| 10 | `0x00520CD1` / 684 | `?rva00520CD1@AptTimeLine@@QAEXXZ` | `300cc51bb1` | Inline GameSlot template accessor replaced direct member access and closed register-versus-stack allocation. |
| 11 | `0x006227E0` / 3244 | `?refresh@Q1Receiver0134FAAC@@QAEXXZ` | `ae782dbf28` | Deque reference declaration order r1,r0,r2 fixed FactCanonSort base/index order in two tails. |
| 12 | `0x00012190` / 2824 | `?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z` | `ecf29f951d` | TU-local phantom-cost string-base destructor produced 13 outlined calls plus inline final exit; visible tag-using assign dispatch restored tag store. |
| 13 | `0x00126433` / 11984 | `?rva00126433@Rva00126314@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAMABVSphereClass@@@Z` | `ff6cc8a176` | SDK enum-typed SetTransform and donor element-wise u_values assignments fixed inline-variable lifetimes. |
| 14 | `0x00743700` / 14036 | `?RenderStreak@StreakRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAVVector4@@PAMABVSphereClass@@PAI@Z` | `69927839aa` | SDK enum-typed SetTransform plus indexed Get_Location_Offset(0) restored native compiler context. |
| 15 | `0x004F9F39` / 470 | `?rva004F9F39@LivingWorldAutoResolveBattle@@QAEXXZ` | `c6a48af383` | Back element through STLport begin()+index, front through raw start, fixed LEA base/index order. |
| 16 | `0x00033150` / 374 | `?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z` | `13a1a422ce` | __assume(mappedBytes >= mappingSize) retained the accounting invariant and moved mapping-size LEA before unlink. |
| 17 | `0x00142170` / 443 | `?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z` | `3b7c8ec24b` | Sentinel test through a layout view removed Is_Empty inline this-copy effects on the allocator free list and join reload order. |
| 18 | `0x0039380F` / 2217 | `?rva0039380F@BuildAssistant@@UAE_NPAVRva0039205C@@PAVObject@@PBUCoord3D@@2I@Z` | `dc909e5e6b` | Visible noinline Coord3D length/normalize and Coord2D toAngle stopped address escape and restored the 0xe8 frame. |
| 19 | `0x0009CD9B` / 1984 | `?rva0009CD9B@Rva0009C134Host@@QAEXXZ` | `29d89a3a41` | Two theta computations (memory then CSE register value) ordered the home store and spill as retail. |
| 20 | `0x004F3DB1` / 985 | `?selectTeamToReinforce@AIPlayer@@MAE_NH@Z` | `62b59a4908` | Visible constructor bodies enabled inferred nothrow; two-base Team layout corrected member-pointer size and frame. |
| 21 | `0x002401DD` / 1424 | `?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z` | `bc83196e9a` | Both if/else arms store zero before tail merging; StringBase str() also restored the empty-string fold. |
| 22 | `0x0043003C` / 4054 | `?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z` | `fdcaa1a289` | Full Thing->ThingTemplate->BitFlags inline chain returning the masked word fixed the last register choice. |
| 23 | `0x002264B3` / 213 | `?Rva002264B3Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 24 | `0x0022665E` / 213 | `?Rva0022665EFallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 25 | `0x00226733` / 214 | `?Rva00226733Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 26 | `0x00434548` / 217 | `?Rva00434548Fallback@@YAIII@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 27 | `0x00434621` / 218 | `?Rva00434621Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 28 | `0x004346FB` / 217 | `?Rva004346FBFallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 29 | `0x004347D4` / 218 | `?Rva004347D4Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 30 | `0x0056DE2B` / 217 | `?Rva0056DE2BFallback@@YAIII@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 31 | `0x0056DF04` / 213 | `?Rva0056DF04Fallback@@YAIII@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 32 | `0x0056DFD9` / 213 | `?Rva0056DFD9Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 33 | `0x0056E0AE` / 217 | `?Rva0056E0AEFallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 34 | `0x0056E187` / 218 | `?Rva0056E187Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 35 | `0x0056E261` / 213 | `?Rva0056E261Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 36 | `0x0056E336` / 214 | `?Rva0056E336Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 37 | `0x0056E40C` / 214 | `?Rva0056E40CFallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 38 | `0x0056E4E2` / 218 | `?Rva0056E4E2Fallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 39 | `0x0056E5BC` / 214 | `?Rva0056E5BCFallback@@YAHHH@Z` | `03f758b787` | Protection-marker asm label reference disables optimization; hash-ordered named locals, constant conditions, and real member functors reproduce the native body. |
| 40 | `0x0052F63F` / 3027 | `?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z` | `274df0c48f` | Function-scope const IRegion2D& alias shifted IL state to native SIB base/index order. |
| 41 | `0x00470DC1` / 1699 | `?rva00470DC1@HordeContain@@UAEXXZ` | `2dce2d7d46` | Reference-returning cross/dot/scale helpers and a real objPos local closed three SSE residues. |
| 42 | `0x00157FF0` / 1323 | `?Store_Thai_GDI_Glyph@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z` | `14377c8f01` | POINT/SIZE coordinate aggregates, as in a sibling, kept the outer tile loop unreduced. |
| 43 | `0x006BEF80` / 1082 | `?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z` | `31df00fd85` | Visible transform body stopped pos escape; label placement and blend-factor conversion timing closed remaining merges/FP order. |
| 44 | `0x0014C470` / 2291 | `?RecolorHouseColor@MeshClass@@UAEXABVRva0013101E@@PBD@Z` | `0828173360` | WB-attested flat effect-scope declarations replaced nested scopes and restored stack slots. |
| 45 | `0x0060CE41` / 281 | `?rva0060CE41@XferSave@@UAEAAVXfer@@AAVRva0060CE41Argument@@@Z` | `690ff19fcc` | Correct table helpers and visible noinline callees stopped key escape, permitting the exception temporary to reuse its dead slot. |
| 46 | `0x00560B11` / 2148 | `?doParticles@ButterflyDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z` | `7489f29826` | Inline Get_Transform switch, by-value Transpose, reference-local texture assignment, and Vector4 construction closed the bank. |
| 47 | `0x00623600` / 2780 | `?LoadAsset@AssetManagerImpl@@QAEXPAVRva009EF0D0Element@@@Z` | `ab092ae24b` | Body already compiler-matched; proved the deque operator[] whole-body/relocation ICF twin, admitted the binding, used canonical globals. |
| 48 | `0x00398E9A` / 715 | `?rva00398E9A@CastleBehavior@@QAEXXZ` | `31ec10a3f8` | Single exit removed redundant destructor copies during stack packing; correct inline SetBit/accessor chain and order closed weights/ties. |
| 49 | `0x0041D60B` / 3709 | `?canDoSpecialPowerAtLocation@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@W4CommandSourceType@@PBVSpecialPowerTemplate@@0I_N@Z` | `025d06ed70` | Proven nonthrowing pointer walk declared throw(), plus a scoped distance block, removed three stack-colouring conflicts. |
| 50 | `0x0004776F` / 1105 | `?Rva0004776F@W3DDisplay@@UAEXPBVImage@@MMMMKH@Z` | `2aeb618625` | Texture getter and Add_Tri in the same TU plus visible select-any Add_Quad restored frame and SSE allocation. |

## Evidence files

- `inventory.tsv`: compact ordered list, commit timestamps, mangled identity, source and size.
- Local `build/banked-history-20261021/dataset.json`: matching ledger evidence, parent-bank headers and all same-RVA attempt-log entries.
- Local `build/banked-history-20261021/<commit>.diff.txt`: full commit message and source/ledger/evidence changes; reproducible with `git show <commit>`.
- Local `build/banked-history-20261021/<rva>-bank.cpp.txt`: actual bank immediately before its deletion in the landing commit; reproducible with `git show <commit>^:reverse/attempts/<rva>.cpp`.

For any claim above, inspect the corresponding landing commit and its before-bank rather than inferring the fix solely from the last partial score.
