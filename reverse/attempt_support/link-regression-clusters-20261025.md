# Linking regression follow-up, 2026-10-25

Base: `aa31e9bac4`, plus the protected BehaviorModule destructor declarations
in SpecialPowerModuleCtor.cpp and WeaponModeSpecialPowerUpdateCtorThunk.cpp.
Published index: `763dc8759f`, 2026-10-26 00:54 UTC, retail-truth-4.
This is a bounded ordinary preview; the census and headline are unchanged.

## Verified scope

Normal build: 26/26 rows across the destructor and 14 public consumers;
626/626 across the other regression units and six residual candidates;
6/6 across the two corrected consumers and DumbProjectileBehavior provider.
Both corrected consumers' EH graphs are EXACT.

All supplied objects were refreshed together in the final 39-source preview.
It reports 32 clean units, LINKED 5,761 -> 22,601 B against the census.
These totals include inherited repairs and previously linked providers.
Reproduce the bounded preview with
`python tools/link_check.py --paths-from reverse/attempt_support/link-regression-clusters-20261025-scope.txt`.
Its nonzero exit records the seven remaining blocked units listed below.

| Scope | Current linked bytes | Result |
| --- | ---: | --- |
| SpecialPower dtor and 14 public consumers | 1,434 | Clean |
| Eight AsciiString insert_unique / _M_find units | 11,872 | Clean |
| htree.cpp | 2,175 | Clean |
| Three stlport_vector_e8 owners | 928 | Clean |
| FXParticleSystemDefaultTemplateDtor.cpp | 64 | Clean |
| BfmeConv499.cpp | 27 | Clean |
| SpecialPowerModuleCtor.cpp | 340 | Clean after protected base-dtor declaration |
| WeaponModeSpecialPowerUpdateCtorThunk.cpp | 112 | Previously linked bytes preserved |
| FXParticleSystem.cpp | 5,649 | Previously linked provider bytes preserved |

The two consumers used `??1BehaviorModule@@UAE@XZ`, whose indexed provider
was the old minimal SpecialPower view. Sixteen existing providers instead
define `??1BehaviorModule@@MAE@XZ`. Aligning the local declarations binds
those existing bodies without adding a pin, alias, helper, or shared header.
The native cleanup address 0x004607E1 and the existing UpgradeModule view
were also inspected. Forwarding-view trials preserved the parent bytes but
introduced EH import indirection or a duplicate empty ObjectModule dtor;
those trials were discarded in favor of the declaration corrections.

## Candidate snapshot at aa31e9bac4

During publication, upstream LINK-015 repaired VectorClass<Vector3> ownership
and LINK-016 supplied XferSave's bucket initializer in SelectionIDMap.cpp.
Those newer results supersede the two corresponding failures below. The pull
also advanced the repository's BFME 1 pin to ff391a5e90; the measurements in
this document retain their explicitly recorded c0385ef6ba input scope.

| Unit | Own bytes | Current blocker |
| --- | ---: | --- |
| OCLSpecialPower.cpp | 40 | Protected SpecialPower dtor spelling, findPositionAround, FindPositionOptions ctor |
| XferSave.cpp | 1,060 | Int-keyed hashtable _M_initialize_buckets remains unresolved; fca5deac8f's declaration is already present |
| Rva0056616BCopyDeferred.cpp | 333 | Kept vector<BfmePod32> copy constructor is not retail's |
| stlport_float_format.cpp | 2,619 | Const-pointer range append COMDAT |
| vector_class_vector3_ctor.cpp | 194 | Kept VectorClass<Vector3> scalar deleting destructor is not retail's |
| GameWindowDtor.cpp | 249 | GameWindow vtable differs from the first copy |

DumbProjectileBehavior.cpp supplies an existing protected destructor copy;
its own 13-byte unit remains blocked by its independent legacy imports,
damage-transfer, INI, module, projectile and COMDAT dependencies. Its full
unit is not cleared by checking that provider.

Float-format has two append declarations inside an inactive HP-UX branch.
Moving the double-template declaration into active Windows code triggers
VC7.1 C1001 at _string.h:573. The single-template spelling fails C2768,
C2244 and C1506. Both attempts were restored; the source and its original
23 byte-matched rows were reverified. A supported compiler/emission repair
is still needed; the inactive declarations alone are not a completed fix.

## Inputs and limits

BFME 1 remained at the pinned verified c0385ef6ba. Official upstream was
checked at ac4f726f3446c291a86422b3a76744a7afd50d93; advancing that reference
requires the separate full regression-verification procedure. No successful
freshness timestamp or pointer update was recorded. The published object
bundle imported 22,830 entries into the reusable store. No census or global
index update was run. Unreferenced diagnostic COMDAT differences remain
diagnostics; this evidence does not establish closed-strict runtime closure.
