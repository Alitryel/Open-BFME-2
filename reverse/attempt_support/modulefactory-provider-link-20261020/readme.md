# ModuleFactory insertion ownership, 2026-10-20

Inputs: BFME2 6c78e61c47 (parent cec1ad5f20); unchanged published retail-truth-2
census 3f413ed3ff, 2026-10-20 18:52. BFME1 donor4483e88da1 was already reviewed
for this shared-library lane. These are target-backed ownership repairs; no
new reference transfer, name, layout, alias, pin or ledger range is asserted.

The independently matched134B tree insertion at413740 and20B map wrapper at
4138A1 could not link: their unit emitted generic node allocation instead of
the rowed34B creator29E11A, and the main ModuleFactory unit supplied a competing
non-retail insert_unique. Declare the existing factory specialization in the
consumer and declare the no-hint insertion specialization in the main unit.
ModuleTemplate is protected in the original header; a derived typedef exposes
that same type for the declaration without changing the shared header or ABI.
An initial direct typedef failed access checking; the derived typedef fixes it.

Sweep: LivingWorldBonusMapParsers.cpp is the only other authored consumer with
this selected insertion blocker in the census. Its two120B parsers also emitted
an incompatible outline of the key/payload pair constructor. Keep the existing
inline raw-POD copy with an imported forceinline specialization; no outline or
IAT reference is emitted by either callback. The rowed27B outline at29B260 in
ModuleFactory.cpp remains exact. This uses the file's already established ABI
view of twelve-byte bonus data; it does not claim the bonus is a module template.

Paired bounded legacy link predictions against the same frozen census:

| Unit | Before | After |
|---|---:|---:|
| stlport_modulefactory_map_insert_unique.cpp |0|154|
| LivingWorldBonusMapParsers.cpp |0|240|
| ModuleFactory.cpp |0|0|
| Total |0|394|

ModuleFactory.cpp is an exact prerequisite for the other two units, not a
newly linked unit itself. Its other unresolved and competing definitions remain
listed below. The gain is394B in the legacy link prediction; self-strict receipts
cover57/57 rows in all three files. Closed-strict closure was not measured.
No full link cycle, census, nightly or boot runner was started. C++ coverage is
unchanged. All string, float and import reference gates pass. eh_verify reports
23/23 EXACT EH graphs, none baselined. No compiler or verifier changes.

Commands: link_check.py --prepare-current on the three explicit sources;
link_check.py with the consumer and provider sources together; eh_verify.py on
ModuleFactory.cpp and LivingWorldBonusMapParsers.cpp; find_declared_unmatched.py
on all changed sources; check_csv.py. The normal commit hook repeats build.sh's
byte and reference gates for the full staged cohort.

## seat-mf-pair-before.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 2,421)
  unresolved  ?DAMAGE_TYPE_FLAGS_NONE@@3V?$BitFlags@$0CG@@@A
  unresolved  ?buildFieldParse@GrantScienceUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
  comdat      ??$max@I@_STL@@YAABIABI0@Z  (retail: not retail's body)
  comdat      ??1ModuleData@@UAE@XZ  (retail: unproven and differs from the kept copy)
  comdat      ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ  (retail: unproven and differs from the kept copy)
  comdat      ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z  (retail: not retail's body)
  comdat      ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z  (retail: not retail's body)
  comdat      ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?erase@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEPAUAngleFXInfo@@PAU3@0@Z  (retail: not retail's body)
  comdat      ??1UpgradeModuleData@@UAE@XZ  (retail: not retail's body)
  selected    ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z  (the definition the link keeps is not retail's)
  selected    ??1UpgradeModuleData@@UAE@XZ  (the definition the link keeps is not retail's)
  selected    ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z  (the definition the link keeps is not retail's)
  selected    ?erase@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEPAUAngleFXInfo@@PAU3@0@Z  (the definition the link keeps is not retail's)
  selected    ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z  (the definition the link keeps is not retail's)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAUAngleFXInfo@@U1@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEXPAUAngleFXInfo@@I@Z  (codegen-like: 20 bytes against the majority copy's 18; unreferenced, not a blocker)
Code/Libraries/Source/WWVegas/WWLib/stlport_modulefactory_map_insert_unique.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 154)
  comdat      ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@IPBX@Z  (retail: not retail's body)
  comdat      ?_M_create_node@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z  (retail: unproven and differs from the kept copy)
  selected    ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z  (the definition the link keeps is not retail's)
link_check: 0 of 2 link cleanly; LINKED 0 -> 0 bytes (4.0s)
```

## seat-mf-bonus-before.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/INI/LivingWorldBonusMapParsers.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 240)
  comdat      ??0?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@QAE@ABW4NameKeyType@@ABVModuleTemplate@ModuleFactory@@@Z  (retail: not retail's body)
  selected    ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z  (the definition the link keeps is not retail's)
link_check: 0 of 1 link cleanly; LINKED 0 -> 0 bytes (3.3s)
```

## seat-mf-all-after.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/INI/LivingWorldBonusMapParsers.cpp: LINKS  LINKED 0 -> 240 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 240)
Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 2,421)
  unresolved  ?DAMAGE_TYPE_FLAGS_NONE@@3V?$BitFlags@$0CG@@@A
  unresolved  ?buildFieldParse@GrantScienceUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
  comdat      ??$max@I@_STL@@YAABIABI0@Z  (retail: not retail's body)
  comdat      ??1ModuleData@@UAE@XZ  (retail: unproven and differs from the kept copy)
  comdat      ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ  (retail: unproven and differs from the kept copy)
  comdat      ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z  (retail: not retail's body)
  comdat      ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?erase@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEPAUAngleFXInfo@@PAU3@0@Z  (retail: not retail's body)
  comdat      ??1UpgradeModuleData@@UAE@XZ  (retail: not retail's body)
  selected    ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z  (the definition the link keeps is not retail's)
  selected    ??1UpgradeModuleData@@UAE@XZ  (the definition the link keeps is not retail's)
  selected    ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z  (the definition the link keeps is not retail's)
  selected    ?erase@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEPAUAngleFXInfo@@PAU3@0@Z  (the definition the link keeps is not retail's)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAUAngleFXInfo@@U1@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEXPAUAngleFXInfo@@I@Z  (codegen-like: 20 bytes against the majority copy's 18; unreferenced, not a blocker)
Code/Libraries/Source/WWVegas/WWLib/stlport_modulefactory_map_insert_unique.cpp: LINKS  LINKED 0 -> 154 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 154)
link_check: 2 of 3 link cleanly; LINKED 0 -> 394 bytes (5.6s)
```

## seat-mf-trial2.txt

```text
link_check: preparing 2 explicit safe provider(s), no extra sources
Source claims: OK (2 sources, scoped byte-verified)
Compile: 0 of 2 TU(s) (deps-cache: 2 current)
Funclet pins: 1 row(s) verified past a renumbered $L label
    uw_00771bbb (Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp): $L110052 was renumbered; verified parent EH data places $L103859 at 0x00771BBB
Functions: OK 55/55 matched across 2 source file(s)
String-ref verify: OK (0 literals + 1 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
link_check: 2 explicit providers byte-verified with strict reusable receipts; census/index/status unchanged, LINK closure not yet checked
```

## seat-mf-bonus-trial.txt

```text
link_check: preparing 1 explicit safe provider(s), no extra sources
Source claims: OK (1 sources, scoped byte-verified)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Functions: OK 2/2 matched across 1 source file(s)
String-ref verify: OK (2 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (2 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
link_check: 1 explicit providers byte-verified with strict reusable receipts; census/index/status unchanged, LINK closure not yet checked
```

## seat-mf-all-eh.txt

```text
EH verify: 23 row(s) with EH data (EXACT 23); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
```
