# Rva004CE36 vector callback reconciliation: blocked

Inputs: BFME2 a3fd8b3fcb; verified BFME1 pointer 96c88c73a5cd1a58fc2f8db691beea50acd996db. Published census b711de3634, retail-truth-4. Original flags /O1 /MD /EHsc. Trials add STLport and /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc. Original source restored; no aliases or pins added.

Target evidence: parent constructor 4CDCD (91B) builds two 12B headers at +AC with constructor callback256646 (13B) and cleanup4CDAF (30B). Destructor4CE36 (79B) uses the same cleanup. Complete parent rows and both EH rows pass in both candidates. Existing rowed vector<RvaSmartPtr12>::_M_clear owns4CDAF; existing ModuleFactory default-vector closure owns256646. The vector/header interpretation is structural evidence; original derived and record identities remain unknown. RvaSmartPtr12 is an established local element view, not a recovered target name.

Before: current scoped link_check reports0/170B, unresolved Rva0004CDAFSlot ctor and dtor. The growth-provider unit itself has many independent blockers; adding it to the cohort does not free either unit.

Trials:
- wrapper.cpp.txt: raw three-pointer header calls the canonical ObjectCreationList pointer-vector allocator constructor and destroys through existing _Destroy<RvaSmartPtr12*> then conditional free. Original four rows pass. add_match --icf-owner of the 13B closure refuses the ordinary slot constructor: allocator call relocation begins at +10 and needs extent >=14. A constructor returning this is not the void callback. Initial missing STLport marker was corrected before this comparison.
- native.cpp.txt: actual vector<RvaSmartPtr12>[2] removes both unresolveds. Legacy link_check misleadingly previews0->170B; this is NOT a verified gain. Original four rows pass, but adding its vector destructor as a whole-body twin of _M_clear4CDAF fails: _Destroy relocation at +27 needs extent >=31 versus retail30B. The /EHsc native destructor contains additional exception machinery. No callback alias was retained.

Next hypothesis (untested): reconcile the throwing visibility of _Destroy with target's EH-free callback and the exact default-allocator closure, preserving the complete parent EH graph. Do not repeat ordinary default-constructor alias or accept the legacy preview alone. Both best diagnostic sources are preserved. All authored source changes reverted, claims released. No linked-byte gain.

## Lane audit

Ran link_rank --top30 --near2 and --top120 --near3, class_views --blockers, repair_queue link, name_globals --dry-run (zero rewrites), and a read-only rehome_rows --limit10 scan. Current-provider previews distinguish stale improvements from genuine work: AIStatCollector already links362B; ArmySummary and Hashable repairs are upstream. Fresh checks of CreateAHeroDtor, DX8Skin, GameLOD, Rva00801CB0, Geometry, Rva00066A9ABody, Rva003F86F9Ctor, LargeGroupAudioKeyMapBfmeAddKey, BfmeRectVNH_ctor and LivingWorldRegionCtor still depend on documented identity/layout/provider prerequisites. No matching cycle-bundle artifact is available for data-back ranking. Large class-view families need broader shared contracts; existing banks remain applicable and were not replayed. BFME1 official upstream fetched f5140c1c; reviewed its EAStringC/peer-request/string-assign and global/provider leads, retaining the verified96c88c73 pointer because full update verification was not completed. No maintainer-only runner or census build started.

Restored source passes build.sh4/4, source claims, funclet resolution, string/float/import checks, find_declared_unmatched, and check_csv. Current legacy link_check after restoration returns0/170B, matching before. No self-strict or closed-strict improvement claimed.
