# Deleting-destructor identity audit — 2026-09-26

Audited the 120 named wrappers and 30 remaining opaque B01 wrappers from the twelve local identity-redo commits. The scope includes the provenance of the names, not only the wrapper bytes. No new opaque family members were landed. The owner initially held publication and subsequently authorized pushing after the clean-commit and final verification review.

## Result

- Retained 118 named wrapper attributions and 30 explicitly opaque wrappers (28 bytes each).
- Retracted the unsupported `DamageModuleBase` wrapper at RVA `0x0044EF42`.
- Retracted the older public `TransitionDamageFX` family wrapper at RVA `0x00490E5F` (28 bytes), which inherited the same false destructor identity.
- Retracted the older incidental public `TransitionDamageFX` destructor at RVA `0x00490E7B` (56 bytes), the original source of the false base pin. The actual protected destructor at RVA `0x004BA47C` remains matched.
- Retracted the `AABTreeLinkClass` wrapper at RVA `0x0026EF34` and the older 29-byte constructor claim at RVA `0x0026EDDC` on which it depended.
- Consolidated six duplicate symbols introduced by the rebase: Watchdog, InvisibilitySpecialPowerModuleData, CashHackSpecialPowerModuleData, ProductionSpeedBonusModuleData, CloudBreakSpecialPowerModuleData, and TaintSpecialPowerModuleData. Their family sources remain; four redundant Common sources were removed.
- Replaced the unsupported DamageModuleBase destructor pin with `Rva0044ECCE` in ten module-data destructor sources. The target address and verified bodies are unchanged.
- Net unique-byte gain against origin/master at `b1bc2072a`: **2,743 bytes (+0.03 percentage points of non-padding code)**. The reduction from the original reported +3,080 bytes consists of 168 bytes independently landed upstream, 84 bytes of wrapper retractions, the 29-byte constructor retraction, and the 56-byte incidental destructor retraction.

## Evidence standard and limits

Every retained wrapper was independently decoded: the retail sequence passes the original this pointer to its recorded callee, tests bit 0 of the flags, conditionally calls operator delete at RVA `0x0002FD60`, returns this, and uses `ret 4`. The repository byte gate separately verifies the C++ output. One wrapper range is counted once.

For 62 named bodies, an actual slot in the same target vtable refers to code that uses the matching class-name string. For 47 others, the target ModuleFactory registration leads to a data factory and its final primary vptr store, directly or through the constructor. The module-data class spelling follows the donor convention; a module registration is not a C++ symbol export. GateProxy uses inlined construction. W3DModelDraw data is intentionally shared by W3DScriptedModelDraw, as already documented by the registry allowlist.

The remaining nine names use corroborated donor attribution, detailed below. They are not presented as RTTI or literal C++ names recovered from the executable. In particular, XferSave inherits its spelling from the reconstructed BFME1 donor; its target save-stream semantics and lifecycle corroborate that attribution but do not independently prove the original spelling. This residual provenance limitation is retained explicitly.

CaveContainModuleData construction is also reached from HealContain. TransportAIUpdateModuleData construction is also reached from AIUpdateInterface, HordeAIUpdate, and HordeWorkerAIUpdate. Those rows describe the chosen donor attribution at a shared address; they do not claim an exclusive owner.

These minimal declarations recover only the deleting wrappers. Their empty noinline destructors are unmatched compilation scaffolds. No complete member layout, inheritance graph, original access qualifiers, or destructor implementation is recovered by them. B01 address names are bookkeeping labels. The absence of invented bases does not establish the unknown target layout.

## Retractions

`DamageModuleBase` came from a harvested dependency pin introduced by commit `94adadadb`, with the note "address read from the REL32 displacement at a placed body". That proves a call destination, not a class. Its constructor counterpart at RVA `0x0044EB54` is explicitly opaque. The ten module-data consumers now use an address-derived base name so the old placeholder cannot become ownership evidence again. The full gate exposed the incidental public TransitionDamageFX destructor at RVA 0x00490E7B that supplied the false pin. It was retracted and denied from placement; the independently verified protected destructor at RVA 0x004BA47C shares the constructor vtable triple and is called by the deleting wrapper at RVA 0x004BA7C4. The constructor TU retains its unclaimed emission scaffold with an explicit annotation. The older family wrapper at RVA 0x00490E5F also depended on the false public destructor row and was retracted; the genuine protected wrapper remains matched.

The AABTreeLink constructor was accepted from a generic 29-byte body and a one-slot vtable. Its retail caller at RVA `0x002AE329` allocates 0x14 bytes, passes a game-object pointer, stores an enum at +8, links +0x0C/+0x10, compares the enum against 1 and 2, and updates bitsets indexed by the argument at +0x38. The donor identifies +8 as an AABTreeNode pointer. That contradiction invalidates the asserted tree-link layout and the wrapper identity derived from it. The actual target class is left unidentified.

## Named wrapper evidence

Addresses below are RVAs except the explicitly labelled vtable VA. All wrappers are 28 bytes. The source comments, ledger notes, and destructor-pin notes carry the same audited basis.

| Attribution | Wrapper RVA | Dtor RVA | Vtable VA | Basis | Evidence |
| --- | --- | --- | --- | --- | --- |
| W3DScriptedModelDraw | `0x000C8617` | `0x000C79C9` | `0x00BCA090` | retail name string | retail slot 4 -> RVA 0x000C1201 uses class-name string "W3DScriptedModelDraw" |
| W3DModelDrawModuleData | `0x000C8DC3` | `0x000C8BE0` | `0x00BCADE8` | registry | retail W3DScriptedModelDraw registration -> shared data factory RVA 0x000648D6 -> ctor RVA 0x000C8EEF; primary vptr store RVA 0x000C8F13; field parser RVA 0x000C9240 agrees with donor W3DModelDraw data |
| W3DRopeDraw | `0x000CA9D5` | `0x000CA8BC` | `0x00BCBD60` | retail name string | retail slot 4 -> RVA 0x000CA7F6 uses class-name string "W3DRopeDraw" |
| W3DTruckDraw | `0x000CDF34` | `0x000CDE73` | `0x00BCC650` | retail name string | retail slot 4 -> RVA 0x000CB578 uses class-name string "W3DTruckDraw" |
| W3DTankDraw | `0x000CEB2C` | `0x000CE960` | `0x00BCCBE8` | retail name string | retail slot 4 -> RVA 0x000CE9EE uses class-name string "W3DTankDraw" |
| W3DFloorDraw | `0x000CF492` | `0x000CF1A6` | `0x00BCD4E0` | retail name string | retail slot 4 -> RVA 0x000CF161 uses class-name string "W3DFloorDraw" |
| W3DLightDraw | `0x000CFBF0` | `0x000CFA42` | `0x00BCD728` | retail name string | retail slot 4 -> RVA 0x000CFAF9 uses class-name string "W3DLightDraw" |
| W3DSailModelDraw | `0x000D08A2` | `0x000D08BE` | `0x00BCDC60` | retail name string | retail slot 4 -> RVA 0x000D07CB uses class-name string "W3DSailModelDraw" |
| W3DBoatWakeModelDraw | `0x000D0D08` | `0x000D0B69` | `0x00BCDD70` | retail name string | retail slot 4 -> RVA 0x000D0C93 uses class-name string "W3DBoatWakeModelDraw" |
| W3DProjectileStreamDraw | `0x000D144F` | `0x000D146B` | `0x00BCE010` | retail name string | retail slot 4 -> RVA 0x000D140A uses class-name string "W3DProjectileStreamDraw" |
| W3DTornadoDrawModuleData | `0x000D16F7` | `0x000D1713` | `0x00BCE198` | registry | retail registration W3DTornadoDraw -> data factory RVA 0x00065171 -> ctor RVA 0x000D16B4; primary vptr store RVA 0x000D16CC |
| W3DTornadoDraw | `0x000D19DD` | `0x000D18AB` | `0x00BCE218` | retail name string | retail slot 4 -> RVA 0x000D1866 uses class-name string "W3DTornadoDraw" |
| W3DDisplayString | `0x0010625B` | `0x00106162` | `0x00BCF900` | corroborated donor | donor slots 9/16 at RVAs 0x00105FC6/0x0010657E, corroborated by ctor RVA 0x00106088 and dtor RVA 0x00106162 constructing/destructing two render-sentence members at +0x14/+0xD8; donor class attribution |
| SoundFXNugget | `0x001E0DEB` | `0x001E0E07` | `0x00BDD768` | corroborated donor | retail Sound FXList parse entry -> parser RVA 0x001E1329 -> ctor RVA 0x001E00A3; primary vptr store RVA 0x001E00AB; SoundFXNugget spelling from donor |
| AttackNugget | `0x001F0606` | `0x001F0622` | `0x00BE0FF4` | corroborated donor | retail Attack OCL parse entry -> parser RVA 0x001F0D96 -> ctor RVA 0x001F05C1; primary vptr store RVA 0x001F05D9; AttackNugget spelling from donor |
| Watchdog | `0x002257CD` | `0x0022576A` | `0x00BE6FD8` | corroborated donor | ctor RVA 0x00225616 stores primary vptr at RVA 0x00225633; slot 3 RVA 0x002255AD formats retail Watchdog diagnostic at VA 0x00BE6F70; thread start/run slots agree with donor |
| TerrainResourceClientBehavior | `0x00252E56` | `0x004CC5AA` | `0x00BEFF20` | retail name string | retail slot 4 -> RVA 0x00252E0B uses class-name string "TerrainResourceClientBehavior" |
| GateProxyBehaviorModuleData | `0x00254029` | `0x00254045` | `0x00BEF380` | registry | retail registration GateProxyBehavior -> data factory RVA 0x00253FB1; inlined construction stores this vtable at RVA 0x00253FD9 |
| DeployStyleAIUpdateModuleData | `0x00255F54` | `0x00255F70` | `0x00BF3440` | registry | retail registration DeployStyleAIUpdate -> data factory RVA 0x0025517E -> ctor RVA 0x00255154; primary vptr store RVA 0x0025515E |
| SlavedUpdateModuleData | `0x00255FA5` | `0x00255FC1` | `0x00BF34C0` | registry | retail registration SlavedUpdate -> data factory RVA 0x00255340 -> ctor RVA 0x002552D7; primary vptr store RVA 0x002552DE |
| SalvageCrateCollideModuleData | `0x002563D3` | `0x002563EF` | `0x00BF3A40` | registry | retail registration SalvageCrateCollide -> data factory RVA 0x00255BD2 -> ctor RVA 0x00255B7E; primary vptr store RVA 0x00255BA3 |
| ActivateModuleSpecialPowerModuleData | `0x0025712E` | `0x0025714A` | `0x00BF3F60` | registry | retail registration ActivateModuleSpecialPower -> data factory RVA 0x00256DC5 -> ctor RVA 0x00256DA1; primary vptr store RVA 0x00256DB5 |
| CreateCrateDieModuleData | `0x00257339` | `0x00257355` | `0x00BF40A8` | registry | retail registration CreateCrateDie -> data factory RVA 0x0025739D -> ctor RVA 0x002572EE; primary vptr store RVA 0x00257313 |
| CaveContainModuleData | `0x002576F3` | `0x0025770F` | `0x00C43F40` | registry | retail registration CaveContain -> data factory RVA 0x00257714 -> ctor RVA 0x00466D37; primary vptr store RVA 0x00466D46; constructor also used by HealContain (no exclusive owner claim) |
| SubObjectsUpgradeModuleData | `0x002577F0` | `0x004B5214` | `0x00BF41A8` | registry | retail registration SubObjectsUpgrade -> data factory RVA 0x0025780C -> ctor RVA 0x00257768; primary vptr store RVA 0x0025777E |
| TransportAIUpdateModuleData | `0x0026E67D` | `0x0026E1FC` | `0x00BFA288` | registry | retail registration TransportAIUpdate -> data factory RVA 0x0024BDF2 -> ctor RVA 0x0026E5D7; primary vptr store RVA 0x0026E5F2; constructor also used by AIUpdateInterface, HordeAIUpdate, HordeWorkerAIUpdate (no exclusive owner claim) |
| ObjectSMCHelper | `0x00292894` | `0x004DE767` | `0x00BFC088` | retail name string | retail slot 4 -> RVA 0x00292849 uses class-name string "ObjectSMCHelper" |
| PlayerList | `0x002A7ED5` | `0x002A79A9` | `0x00BFD618` | corroborated donor | donor reset at RVA 0x002A7AA0 in slot 9, corroborated by ctor RVA 0x002A7F80 and dtor RVA 0x002A79A9 managing 20 Player pointers at +0x18; donor class attribution |
| SmudgeManager | `0x002D2A83` | `0x002D29F7` | `0x00C02A60` | corroborated donor | ctor RVA 0x002D25BA stores primary vptr at RVA 0x002D25BE and distinct list vptrs at +0x08/+0x14; reset RVA 0x002D27CC and dtor RVA 0x002D29F7 agree with donor used/free-list ownership |
| ImageCollection | `0x002D9362` | `0x002D9283` | `0x00C03878` | corroborated donor | ctor RVA 0x002D932B stores primary vptr at RVA 0x002D9348; caller RVA 0x0023A1BB stores result at VA 0x00DFF078; donor findImageByName/addImage bodies corroborate image-map ownership |
| LaserUpdateModuleData | `0x003631CC` | `0x003631E8` | `0x00C17120` | registry | retail registration LaserUpdate -> data factory RVA 0x0024D55A -> ctor RVA 0x00363147; primary vptr store RVA 0x0036314E |
| CastleMemberBehaviorModuleData | `0x00396007` | `0x00395B2C` | `0x00C1A380` | registry | retail registration CastleMemberBehavior -> data factory RVA 0x0024AB26 -> ctor RVA 0x00395B03; primary vptr store RVA 0x00395B07 |
| CastleBehavior | `0x00399354` | `0x0039857D` | `0x00C1A780` | retail name string | retail slot 4 -> RVA 0x00398538 uses class-name string "CastleBehavior" |
| ThreatFinderUpdate | `0x003ED0A8` | `0x003ECF64` | `0x00C360CC` | retail name string | retail slot 4 -> RVA 0x003ECCD6 uses class-name string "ThreatFinderUpdate" |
| SpecialAbilityUpdate | `0x004522F0` | `0x00451F45` | `0x00C3FBA8` | retail name string | retail slot 4 -> RVA 0x0044F054 uses class-name string "SpecialAbilityUpdate" |
| GettingBuiltBehavior | `0x0045477E` | `0x0045448F` | `0x00C404FC` | retail name string | retail slot 4 -> RVA 0x004543EB uses class-name string "GettingBuiltBehavior" |
| BridgeBehavior | `0x00457536` | `0x00457113` | `0x00C409DC` | retail name string | retail slot 4 -> RVA 0x004571A9 uses class-name string "BridgeBehavior" |
| SiegeDockingBehavior | `0x0045A17D` | `0x00459DAA` | `0x00C414DC` | retail name string | retail slot 4 -> RVA 0x004599E5 uses class-name string "SiegeDockingBehavior" |
| AutoAbilityBehavior | `0x0045A560` | `0x0045A37F` | `0x00C4175C` | retail name string | retail slot 4 -> RVA 0x0045A3CE uses class-name string "AutoAbilityBehavior" |
| BezierProjectileBehavior | `0x0045C959` | `0x0045BF6E` | `0x00C41E04` | retail name string | retail slot 4 -> RVA 0x0045BFD9 uses class-name string "BezierProjectileBehavior" |
| InstantDeathBehaviorModuleData | `0x0045D271` | `0x0045D28D` | `0x00C41F28` | registry | retail registration InstantDeathBehavior -> data factory RVA 0x0024B213 -> ctor RVA 0x0045D176; primary vptr store RVA 0x0045D189 |
| StancesBehavior | `0x0045F068` | `0x0045F001` | `0x00C424DC` | retail name string | retail slot 4 -> RVA 0x0045EFBC uses class-name string "StancesBehavior" |
| SpawnBehavior | `0x004602D8` | `0x0045F6D3` | `0x00C426AC` | retail name string | retail slot 4 -> RVA 0x0045F688 uses class-name string "SpawnBehavior" |
| FakePathfindPortalBehaviour | `0x00461C03` | `0x004619F2` | `0x00C42C1C` | retail name string | retail slot 4 -> RVA 0x004619AD uses class-name string "FakePathfindPortalBehaviour" |
| OpenContain | `0x00464B7A` | `0x00464692` | `0x00C435E8` | retail name string | retail slot 4 -> RVA 0x00464775 uses class-name string "OpenContain" |
| TransportContain | `0x00468029` | `0x00467E61` | `0x00C44278` | retail name string | retail slot 4 -> RVA 0x00467EE1 uses class-name string "TransportContain" |
| HordeContain | `0x004704C8` | `0x0046F901` | `0x00C45050` | retail name string | retail slot 4 -> RVA 0x0046F860 uses class-name string "HordeContain" |
| HorseHordeContain | `0x0047672D` | `0x00476653` | `0x00C45C38` | retail name string | retail slot 4 -> RVA 0x004766E8 uses class-name string "HorseHordeContain" |
| HordeTransportContain | `0x004771CA` | `0x004771E6` | `0x00C45EB8` | retail name string | retail slot 4 -> RVA 0x00477185 uses class-name string "HordeTransportContain" |
| HordeTransportContainModuleData | `0x00477D73` | `0x00477D8F` | `0x00C45FB0` | registry | retail registration HordeTransportContain -> data factory RVA 0x0024BA07 -> ctor RVA 0x00477D61; primary vptr store RVA 0x00477D69 |
| GarrisonContain | `0x0047860D` | `0x00478067` | `0x00C461F8` | retail name string | retail slot 4 -> RVA 0x0047801C uses class-name string "GarrisonContain" |
| HordeGarrisonContain | `0x0047A12B` | `0x0047A147` | `0x00C46570` | retail name string | retail slot 4 -> RVA 0x0047A0E6 uses class-name string "HordeGarrisonContain" |
| AODHordeContain | `0x0047B674` | `0x0047B563` | `0x00C46D28` | retail name string | retail slot 4 -> RVA 0x0047B51E uses class-name string "AODHordeContain" |
| SiegeEngineContain | `0x0047C2D6` | `0x0047BF43` | `0x00C470F8` | retail name string | retail slot 4 -> RVA 0x0047C03A uses class-name string "SiegeEngineContain" |
| SiegeEngineContainModuleData | `0x0047C9AF` | `0x0047C9CB` | `0x00C47180` | registry | retail registration SiegeEngineContain -> data factory RVA 0x0024BBEF -> ctor RVA 0x0047C927; primary vptr store RVA 0x0047C94A |
| HordeSiegeEngineContain | `0x0047D31E` | `0x0047CFB2` | `0x00C474A0` | retail name string | retail slot 4 -> RVA 0x0047D0A2 uses class-name string "HordeSiegeEngineContain" |
| HordeSiegeEngineContainModuleData | `0x0047DA7D` | `0x0047DA99` | `0x00C47520` | registry | retail registration HordeSiegeEngineContain -> data factory RVA 0x0024BC7E -> ctor RVA 0x0047DA08; primary vptr store RVA 0x0047DA2A |
| TunnelContain | `0x0047DC59` | `0x0047DB00` | `0x00C47740` | retail name string | retail slot 4 -> RVA 0x0047DB43 uses class-name string "TunnelContain" |
| RiderChangeContain | `0x0047E4FF` | `0x0047E51B` | `0x00C47A00` | retail name string | retail slot 4 -> RVA 0x0047E2E0 uses class-name string "RiderChangeContain" |
| RiderChangeContainModuleData | `0x0047EB1A` | `0x0047EB36` | `0x00C47B00` | registry | retail registration RiderChangeContain -> data factory RVA 0x0024BD63 -> ctor RVA 0x0047EABC; primary vptr store RVA 0x0047EAEB |
| SlaughterHordeContain | `0x00480645` | `0x004803FB` | `0x00C48AA0` | retail name string | retail slot 4 -> RVA 0x004803B6 uses class-name string "SlaughterHordeContain" |
| CitadelSlaughterHordeContain | `0x004806FC` | `0x00480718` | `0x00C48CC0` | retail name string | retail slot 4 -> RVA 0x00480600 uses class-name string "CitadelSlaughterHordeContain" |
| CitadelSlaughterHordeContainModuleData | `0x004811CA` | `0x004811E6` | `0x00C48E40` | registry | retail registration CitadelSlaughterHordeContain -> data factory RVA 0x0024C100 -> ctor RVA 0x0048112F; primary vptr store RVA 0x00481155 |
| ProductionQueueHordeContain | `0x00481397` | `0x00481230` | `0x00C49040` | retail name string | retail slot 4 -> RVA 0x004812B9 uses class-name string "ProductionQueueHordeContain" |
| ProductionQueueHordeContainModuleData | `0x0048179A` | `0x004817B6` | `0x00C490F8` | registry | retail registration ProductionQueueHordeContain -> data factory RVA 0x0024C18F -> ctor RVA 0x00481776; primary vptr store RVA 0x0048178A |
| PropagandaTowerBehaviorModuleData | `0x00481BB2` | `0x00481BCE` | `0x00C49288` | registry | retail registration PropagandaTowerBehavior -> data factory RVA 0x0024C21B -> ctor RVA 0x0048197C; primary vptr store RVA 0x00481988 |
| RebuildHoleBehaviorModuleData | `0x0048332E` | `0x0048334A` | `0x00C49950` | registry | retail registration RebuildHoleBehavior -> data factory RVA 0x0024C433 -> ctor RVA 0x0048323E; primary vptr store RVA 0x00483250 |
| ReplenishUnitsBehavior | `0x004842C1` | `0x00484161` | `0x00C4A034` | retail name string | retail slot 4 -> RVA 0x00484187 uses class-name string "ReplenishUnitsBehavior" |
| SlaveWatcherBehaviorModuleData | `0x004846DE` | `0x004846FA` | `0x00C4A298` | registry | retail registration SlaveWatcherBehavior -> data factory RVA 0x0024C660 -> ctor RVA 0x004846C7; primary vptr store RVA 0x004846CB |
| DamageFilteredCreateObjectDie | `0x00485FC7` | `0x00485EC3` | `0x00C4AB54` | retail name string | retail slot 4 -> RVA 0x00485EFD uses class-name string "DamageFilteredCreateObjectDie" |
| RebuildHoleExposeDie | `0x004867DD` | `0x004867F9` | `0x00C4AE54` | retail name string | retail slot 4 -> RVA 0x00486792 uses class-name string "RebuildHoleExposeDie" |
| FloodUpdate | `0x0048E603` | `0x0048E454` | `0x00C4C948` | retail name string | retail slot 4 -> RVA 0x0048E0FA uses class-name string "FloodUpdate" |
| ArrowStormUpdateModuleData | `0x00490679` | `0x00490695` | `0x00C4D5A0` | registry | retail registration ArrowStormUpdate -> data factory RVA 0x0024D601 -> ctor RVA 0x00490639; primary vptr store RVA 0x00490647 |
| WeaponFireSpecialAbilityUpdateModuleData | `0x004927EA` | `0x00492806` | `0x00C4E108` | registry | retail registration WeaponFireSpecialAbilityUpdate -> data factory RVA 0x0024DB56 -> ctor RVA 0x004926CA; primary vptr store RVA 0x004926D4 |
| SpecialPowerModule | `0x004941D7` | `0x00493DEF` | `0x00C4E868` | retail name string | retail slot 4 -> RVA 0x00493DAA uses class-name string "SpecialPowerModule" |
| AutoPickUpUpdate | `0x00495DAA` | `0x00495C48` | `0x00C4F06C` | retail name string | retail slot 4 -> RVA 0x00495CEC uses class-name string "AutoPickUpUpdate" |
| AutoPickUpUpdateModuleData | `0x00496460` | `0x0049647C` | `0x00C4F108` | registry | retail registration AutoPickUpUpdate -> data factory RVA 0x0024E099 -> ctor RVA 0x00496308; primary vptr store RVA 0x00496321 |
| BannerCarrierUpdateModuleData | `0x004976AE` | `0x00497056` | `0x00C4F870` | registry | retail registration BannerCarrierUpdate -> data factory RVA 0x0024E1AB -> ctor RVA 0x00496FA5; primary vptr store RVA 0x00496FB7 |
| OneRingPenaltyUpdateModuleData | `0x00499C19` | `0x00499A16` | `0x00C50298` | registry | retail registration OneRingPenaltyUpdate -> data factory RVA 0x0024E42C -> ctor RVA 0x004999F1; primary vptr store RVA 0x004999F8 |
| AttributeModifierAuraUpdate | `0x0049B884` | `0x0049B6DD` | `0x00C50D2C` | retail name string | retail slot 4 -> RVA 0x0049B5DC uses class-name string "AttributeModifierAuraUpdate" |
| ProductionUpdate | `0x0049E34C` | `0x0049E1BF` | `0x00C515BC` | retail name string | retail slot 4 -> RVA 0x0049E15E uses class-name string "ProductionUpdate" |
| BroadcastStealthUpdate | `0x004A35AD` | `0x004A3555` | `0x00C52364` | retail name string | retail slot 4 -> RVA 0x004A34C6 uses class-name string "BroadcastStealthUpdate" |
| LargeGroupAudioUpdate | `0x004ABB1B` | `0x004AB8DC` | `0x00C549BC` | retail name string | retail slot 4 -> RVA 0x004AB897 uses class-name string "LargeGroupAudioUpdate" |
| DestroyEnvironmentUpdate | `0x004AC7AD` | `0x004AC767` | `0x00C54D64` | retail name string | retail slot 4 -> RVA 0x004AC686 uses class-name string "DestroyEnvironmentUpdate" |
| AIGateUpdate | `0x004B0926` | `0x004B0802` | `0x00C56480` | retail name string | retail slot 4 -> RVA 0x004B087C uses class-name string "AIGateUpdate" |
| EmotionTrackerUpdate | `0x004B15CA` | `0x004B1322` | `0x00C5667C` | retail name string | retail slot 4 -> RVA 0x004B1393 uses class-name string "EmotionTrackerUpdate" |
| ReplaceObjectUpdateModuleData | `0x004B2E5D` | `0x004B2C9A` | `0x00C56C78` | registry | retail registration ReplaceObjectUpdate -> data factory RVA 0x0024FCEA -> ctor RVA 0x004B2AC4; primary vptr store RVA 0x004B2AD8 |
| AISpecialPowerUpdateModuleData | `0x004B2FF3` | `0x004B300F` | `0x00C56F48` | registry | retail registration AISpecialPowerUpdate -> data factory RVA 0x0024FD76 -> ctor RVA 0x004B2FCD; primary vptr store RVA 0x004B2FD9 |
| LocomotorSetUpgrade | `0x004B3F3C` | `0x004B3EA0` | `0x00C57530` | retail name string | retail slot 4 -> RVA 0x004B3EC6 uses class-name string "LocomotorSetUpgrade" |
| ObjectCreationUpgradeModuleData | `0x004B45CC` | `0x004B45E8` | `0x00C577C8` | registry | retail registration ObjectCreationUpgrade -> data factory RVA 0x0024FFAC -> ctor RVA 0x004B425B; primary vptr store RVA 0x004B4264 |
| StatusBitsUpgradeIfEldestKindof | `0x004B4ADE` | `0x004B4AFA` | `0x00C57ADC` | retail name string | retail slot 4 -> RVA 0x004B4A99 uses class-name string "StatusBitsUpgradeIfEldestKindof" |
| CostModifierUpgradeModuleData | `0x004B5C64` | `0x004B5C80` | `0x00C58210` | registry | retail registration CostModifierUpgrade -> data factory RVA 0x00250316 -> ctor RVA 0x004B5BAC; primary vptr store RVA 0x004B5BD0 |
| AllowBannerSpawnUpgrade | `0x004B85B8` | `0x004B84EA` | `0x00C59030` | retail name string | retail slot 4 -> RVA 0x004B8520 uses class-name string "AllowBannerSpawnUpgrade" |
| CallHelpOnDamage | `0x004BB4B5` | `0x004BB4D1` | `0x00C59FDC` | retail name string | retail slot 4 -> RVA 0x004BB470 uses class-name string "CallHelpOnDamage" |
| ActiveBody | `0x004BF9D1` | `0x004BF951` | `0x00C5B038` | retail name string | retail slot 4 -> RVA 0x004BF848 uses class-name string "ActiveBody" |
| InvisibilitySpecialPowerModuleData | `0x004C24C3` | `0x004C24DF` | `0x00C5C558` | registry | retail registration InvisibilitySpecialPower -> data factory RVA 0x002518CB -> ctor RVA 0x004C244D; primary vptr store RVA 0x004C246C |
| CashHackSpecialPowerModuleData | `0x004C28C1` | `0x004C28DD` | `0x00C5C688` | registry | retail registration CashHackSpecialPower -> data factory RVA 0x00251957 -> ctor RVA 0x004C2889; primary vptr store RVA 0x004C289D |
| LevelGrantSpecialPower | `0x004C2C5A` | `0x004C2C76` | `0x00C5C920` | retail name string | retail slot 4 -> RVA 0x004C2BC1 uses class-name string "LevelGrantSpecialPower" |
| ProductionSpeedBonusModuleData | `0x004C3048` | `0x004C3064` | `0x00C5CA80` | registry | retail registration ProductionSpeedBonus -> data factory RVA 0x00251AFE -> ctor RVA 0x004C2FE6; primary vptr store RVA 0x004C300E |
| OCLSpecialPowerModuleData | `0x004C37A4` | `0x004C37C0` | `0x00C5CCB0` | registry | retail registration OCLSpecialPower -> data factory RVA 0x00251B8A -> ctor RVA 0x004C32BC; primary vptr store RVA 0x004C32E3 |
| ElvenWoodSpecialPowerModuleData | `0x004C3EA6` | `0x004C3EC2` | `0x00C5CF38` | registry | retail registration ElvenWoodSpecialPower -> data factory RVA 0x00251CB4 -> ctor RVA 0x004C3DA9; primary vptr store RVA 0x004C3DBA |
| WeaponChangeSpecialPowerModuleData | `0x004C42D2` | `0x004C42EE` | `0x00C5D1F0` | registry | retail registration WeaponChangeSpecialPowerModule -> data factory RVA 0x00251D40 -> ctor RVA 0x004C4257; primary vptr store RVA 0x004C4277 |
| CloudBreakSpecialPowerModuleData | `0x004C47D7` | `0x004C47F3` | `0x00C5D468` | registry | retail registration CloudBreakSpecialPower -> data factory RVA 0x00251E58 -> ctor RVA 0x004C479A; primary vptr store RVA 0x004C47AA |
| TaintSpecialPowerModuleData | `0x004C4AEB` | `0x004C4B07` | `0x00C5D608` | registry | retail registration TaintSpecialPower -> data factory RVA 0x00251EE4 -> ctor RVA 0x004C4AB8; primary vptr store RVA 0x004C4ACA |
| SiegeDeploySpecialPower | `0x004C585B` | `0x004C57C1` | `0x00C5DCFC` | retail name string | retail slot 4 -> RVA 0x004C577C uses class-name string "SiegeDeploySpecialPower" |
| PlayerUpgradeSpecialPowerModuleData | `0x004C7DB8` | `0x004C7DD4` | `0x00C5E1C0` | registry | retail registration PlayerUpgradeSpecialPower -> data factory RVA 0x0025253B -> ctor RVA 0x004C7D68; primary vptr store RVA 0x004C7D8D |
| DevastateSpecialPowerModuleData | `0x004C851B` | `0x004C8537` | `0x00C5E518` | registry | retail registration DevastateSpecialPower -> data factory RVA 0x00252653 -> ctor RVA 0x004C84BD; primary vptr store RVA 0x004C84EC |
| CritterEmitterUpdateModuleData | `0x004C8F2D` | `0x004C8F49` | `0x00C5E988` | registry | retail registration CritterEmitterUpdate -> data factory RVA 0x00252906 -> ctor RVA 0x004C8EFF; primary vptr store RVA 0x004C8F0D |
| RadarMarkerClientUpdate | `0x004C9CDB` | `0x004C9C38` | `0x00C5EDB8` | retail name string | retail slot 4 -> RVA 0x004C9BF3 uses class-name string "RadarMarkerClientUpdate" |
| RadarMarkerClientUpdateModuleData | `0x004C9D77` | `0x004C9CA5` | `0x00C5EDF8` | registry | retail registration RadarMarkerClientUpdate -> data factory RVA 0x00252B11 -> ctor RVA 0x004C9C98; primary vptr store RVA 0x004C9C9A |
| AnimationSoundClientBehavior | `0x004C9F45` | `0x004C9DC9` | `0x00C5EE80` | retail name string | retail slot 4 -> RVA 0x004C9EF3 uses class-name string "AnimationSoundClientBehavior" |
| AnimationSoundClientBehaviorModuleData | `0x004CA74C` | `0x004CA768` | `0x00C5EED0` | registry | retail registration AnimationSoundClientBehavior -> data factory RVA 0x00252BC2 -> ctor RVA 0x004CA70D; primary vptr store RVA 0x004CA725 |
| UpgradeSoundSelectorClientBehaviorModuleData | `0x004CBACE` | `0x004CBAEA` | `0x00C5F250` | registry | retail registration UpgradeSoundSelectorClientBehavior -> data factory RVA 0x00252C64 -> ctor RVA 0x004CB9F3; primary vptr store RVA 0x004CB9FF |
| ModelConditionAudioLoopClientBehavior | `0x004CC179` | `0x004CC0FE` | `0x00C5F458` | retail name string | retail slot 4 -> RVA 0x004CBF13 uses class-name string "ModelConditionAudioLoopClientBehavior" |
| ModelConditionAudioLoopClientBehaviorModuleData | `0x004CC31B` | `0x004CC226` | `0x00C5F4A8` | registry | retail registration ModelConditionAudioLoopClientBehavior -> data factory RVA 0x00252D9A -> ctor RVA 0x004CC20A; primary vptr store RVA 0x004CC216 |
| FiringTracker | `0x004DEBA5` | `0x004DEA0C` | `0x00C61530` | retail name string | retail slot 4 -> RVA 0x004DEACB uses class-name string "FiringTracker" |
| DockUpdate | `0x0058A177` | `0x0058A0F4` | `0x00C70378` | corroborated donor | donor ctor RVA 0x0058A290 stores this primary vptr at RVA 0x0058A2C5 and a separate interface vptr at +0x20; slot-3 xfer RVA 0x0058A410 corroborates the dock fields and member order |
| XferSave | `0x0060D24D` | `0x0060D0B3` | `0x00C7B010` | corroborated donor | BFME1 reconstructed donor slots 6/38 at RVAs 0x0060CA26/0x0060C935 implement save-side block finalization and stream writes; ctor/dtor RVAs 0x0060D1F7/0x0060D0B3 share this primary vptr; class spelling remains donor-derived |

## Opaque B01 audit

All 30 have separate Ghidra-inventoried wrapper and callee starts and byte-verified calls. Their destructor pins are address-derived. A pointer occurrence in a data section is recorded without claiming that it establishes a complete vtable or owner. Nine have no such occurrence; their virtual declarations remain compiler-emission scaffolds, not evidence of target virtual ownership.

| Opaque label | Wrapper RVA | Callee RVA | Pointer occurrences in .rdata/.data (VA) |
| --- | --- | --- | --- |
| Rva000C2980 | `0x000C3808` | `0x000C2980` | none found |
| Rva000D1E88 | `0x000D1E6C` | `0x000D1E88` | `0x00BCE334` |
| Rva000D1BA6 | `0x000D208D` | `0x000D1BA6` | `0x00BCE310` |
| Rva00142FE0 | `0x000E00A4` | `0x00142FE0` | none found |
| Rva000E19A3 | `0x000E1A1D` | `0x000E19A3` | `0x00BCE51C` |
| Rva000E3B41 | `0x000E3CC5` | `0x000E3B41` | `0x00BCE78C` |
| Rva000E5033 | `0x000E583E` | `0x000E5033` | none found |
| Rva000E59D3 | `0x000E5A2B` | `0x000E59D3` | `0x00BCE9E0` |
| Rva000E6387 | `0x000E63C0` | `0x000E6387` | `0x00BCEA04` |
| Rva000E6C6F | `0x000E6D78` | `0x000E6C6F` | `0x00BCEAB4` |
| Rva000E9BAC | `0x000E9CDF` | `0x000E9BAC` | `0x00BCECB8` |
| Rva000EDA94 | `0x000EDF07` | `0x000EDA94` | `0x00BCEEA4` |
| Rva000EEEF4 | `0x000EEFEC` | `0x000EEEF4` | `0x00BCEECC` |
| Rva00613B90 | `0x000F0B65` | `0x00613B90` | none found |
| Rva000EFC45 | `0x000F1698` | `0x000EFC45` | none found |
| Rva000F1B8F | `0x000F1B73` | `0x000F1B8F` | `0x00BCEFD4` |
| Rva000F26DC | `0x000F2B81` | `0x000F26DC` | `0x00BCEFC8` |
| Rva000F2797 | `0x000F2B9D` | `0x000F2797` | none found |
| Rva00102188 | `0x001021BE` | `0x00102188` | none found |
| Rva001041D8 | `0x00104723` | `0x001041D8` | `0x00BCF770` |
| Rva00104DB0 | `0x00104F16` | `0x00104DB0` | `0x00BCF814` |
| Rva00104E03 | `0x00104F73` | `0x00104E03` | `0x00BCF818` |
| Rva00109C7F | `0x00109C63` | `0x00109C7F` | `0x00BCFA0C` |
| Rva00109BEB | `0x00109DB3` | `0x00109BEB` | none found |
| Rva001095B2 | `0x0010B9C9` | `0x001095B2` | `0x00BCF9F4` |
| Rva00109610 | `0x0010BA83` | `0x00109610` | `0x00BCFA00` |
| Rva0010C785 | `0x0010C825` | `0x0010C785` | `0x00BCF9C4` |
| Rva0010F0C4 | `0x0010F6EE` | `0x0010F0C4` | `0x00BCFAAC` |
| Rva0010F7EE | `0x0010F7D2` | `0x0010F7EE` | `0x00BCFAB0` |
| Rva0010F83E | `0x0010F822` | `0x0010F83E` | `0x00BCFAB8` |

## Derived candidate output

The full gate regenerated three additional entries in `reverse/reloc_names.csv`: CaveContainModuleData at RVA `0x00257481`, HordeTransportContainModuleData at RVA `0x004684F1`, and GateProxyBehaviorModuleData at RVA `0x00498D46`. These come from following the destructor tail jumps. They are candidate names for shared terminal bodies, not three new recovered functions or proof of exclusive ownership. No corresponding `functions.csv` claims were added.

## Verification

- `python tools/build.py <audited source paths>`: initial 150/150 wrappers exact; both retracted wrappers also matched bytes, demonstrating why identity needed a separate audit.
- Ten renamed module-data base consumers: 10/10 exact; `tools/place_bodies.py` rescan found zero new bodies or pins.
- `python tools/check_module_registry.py --check`: all 329 registrations pass, with the two existing documented exceptions.
- Ledger, pin consistency, and normal pre-commit hooks pass for the completed correction commits.
- Final full gate: **all checks green**, including 36,696/36,696 function matches, string/float/import references, DIR32 and pin consistency, 329 module registrations, source claims, and the byte-identical no-op patch.

Publication rebase to `503f43679` restored obsolete versions of 119 function rows and 117 pin notes through the union merge driver. Those duplicate versions were removed, preserving all 118 audited function and pin records and the 12 new upstream function claims. A subsequent rebase to `b1bc2072a` restored 118 obsolete function notes again; the same audited records were retained. The complete gate was rerun after each merge repair.
