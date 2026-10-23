# Fast_Cos owner repair

Base bc0f184d9b; published census b711de3634, retail-truth-4. The indexed
Fast_Cos providers are light.cpp, PointGroupClassInit.cpp and
TextureMapperApply.cpp. Current legacy previews initially link the latter
two units (1,803 + 6,954 B), but light.cpp is excluded by its PersistFactory
constructor/destructor and Register_Pointer dependencies.

The Fast_Cos row at 179950 was still assigned to light.cpp. Its current
header view emits 182 bytes, beginning push ecx/fld, whereas the 194-byte
retail body begins movss/addss/mulss. PointGroupClassInit.cpp already emits
the complete retail body, independently verified by add_match with every
relocation and compiler literal. Move that unchanged header row there.
No target name, identity or pin changes. The point-group unit's existing
provenance and scoped WWMath header establish its inputs; no new donor ABI
claim or donor pointer update is made.

Rehoming alone exposes the non-retail first copy still emitted by light.cpp
and excludes PointGroup too. Scope light's Fast_Cos helper to
BfmeLightInlineFastCos, exactly as its existing private Float_To_Int_Floor
helper is scoped. The real WWMath::Fast_Cos owner and all target callers
retain their name. This prevents the stale 182-byte donor helper from
replacing the rowed retail implementation. No code or layout is fabricated.

Final paired three-unit legacy preview: light remains 0/6 B with its same
three factory/SaveLoad unresolved names; PointGroup LINKS 1,803 -> 1,997 B;
TextureMapperApply LINKS 6,954 -> 6,954 B. Total 8,757 -> 8,951 B, +194 B.
This is legacy preview evidence, not self-strict or closed-strict link
closure or an executable link. New authored C++ bytes: zero.

Acceptance: both touched ledger owners byte-exact 8/8 with strict reusable
receipts; 19 compiler float literals and string/import checks pass; EH
EXACT 1/1; class, declared-definition and new-variant admission pass. No
shared headers, verifier, flags, baselines or reference pointers changed.
Diagnostic output: build/link-seat-stats-isolation/{light-fastcos-diff,
fastcos-cohort-after,fastcos-strict-final,fastcos-variants}.log.
