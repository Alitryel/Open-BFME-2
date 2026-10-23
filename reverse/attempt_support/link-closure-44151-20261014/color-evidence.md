# Color provider discovery
Read-only discovery only. No claims, compiles, source/header/index/ledger/git mutations.

Donor a7c38d3 reviewed through b955ec48 (exact owner instead of competing geometry helper) and d003077f (declaration-only native direct owner call). Applicable suppression principle; no donor layout fact inherited.

Target Get_Color_Array native owner is MeshMatDescClassGetColorArray.cpp, D1FBD 105B, ColorArray +50. Existing row documents Define_FVF native calls at144286 and14429E and native MeshModel forwarder D205F delegates D1FBD. No alias/pin needed.

Read-only current object references:
- dx8renderer Define_FVF REL32 native name +71/+95; MeshModel forwarder +7; Vertex_Split_Table getter +16.
- meshmdlio native MeshModel forwarder +7; read_vertex_colors +35; read_dcg +67/+332; read_dig +70/+376.
- dynamesh DynamicMeshModel getter +14; End_Vertex +154; Change_Vertex_Color +91; Switch_To_Multi_Vertex_Color +25.
All use existing external symbol references. Declaration-only suppression preserves native call binding better than import-forceinline.

Scope complication: dx8renderer and meshmdlio explicitly include reference/shims/meshmatdesclayout/meshmatdesc.h (+4C ColorArray). dynamesh dependency receipt uses upstream inputs/reference/.../WW3D2/meshmatdesc.h, a different layout. Do not replace dynamesh header blindly. Current shared shim has no suppression opt-in.

Concrete proposed repair awaiting parent scope/claim authorization:
1. Add opt-in guard around ONLY Get_Color_Array inline definition in meshmatdesclayout header; define opt-in in dx8renderer and meshmdlio. Declaration unchanged. Preserve every layout and other inline body.
2. For dynamesh, source-local exact upstream meshmatdesc view with only this definition omitted, retaining existing include guard/layout, or a specifically authorized equivalent narrow mechanism. No submodule edits.
3. Isolated before/after try_compile_source; require all retained code bytes+relocation triples identical, no __imp, and all EH graph retained except removed incidental getter graph. Current strict before/after with provider/reader variants only after isolated proof.
4. Combine existing Vector4/color conversion suppression readers from link07/batch2 only after provider closure, using current byte/gate proof. Root claims files before trials.

No countable new clean bytes yet. No production edits to revert. Shared opt-in is required for an honest minimal fix; source macro manipulation that changes unrelated inline functions is rejected.


## Authorized isolated trial update
Root holds three Code files + meshmatdesclayout header under codex-link-3528-color. Native compiler required escalation because sandbox WinError623; elevated isolated trials succeed. Production untouched.

Both declaration-only after objects suppress Get_Color_Array and incidental ShareBuffer<unsigned> ctor/dtor/deleting-dtor/Get_Array. meshmdlio all retained external CODE BYTES identical; four switch-owning functions change only compiler local-label relocation names. Original __imp__stricmp remains (not introduced). dx8renderer Define_FVF code bytes and native calls remain exact; local switch-label numbering changes. Two unrowed functions Add_Mesh@DX8RigidFVFCategoryContainer and Render@DX8SkinFVFCategoryContainer change actual code, previously getter inliners. Neither has a matched ledger row. All other retained external code bytes preserved. Need parent decision whether these legitimate unrowed calls to existing native owner are acceptable or preserve old +4C inline shape with narrowly supported local helpers.

No clean-byte gain credited; all three providers must be removed. dynamesh shadow path reference/shims/dynamesh_color_link/meshmatdesc.h proposed, awaiting parent claim confirmation before trial. MeshMatDescClass absent from canonical_classes.csv, so class_gate would require no allowance for exact view. No submodule edits.


## Production result
Root approved three provider files, two headers and three reader files; all applied. Claims retained under codex-link-3528-color: file:Code/Libraries/Source/WWVegas/WW3D2/{dx8renderer.cpp,dynamesh.cpp,meshmdlio.cpp,MeshModelReadDcg.cpp,MeshModelReadDig.cpp,MeshModelReadVertexColors.cpp}, file:reference/shims/meshmatdesclayout/meshmatdesc.h, file:reference/shims/dynamesh_color_link/meshmatdesc.h. Root acquired claims.

Ordinary provider gate89/89, reader gate3/3; float/string/import refs pass. EH4/4 EXACT for providers,0 applicable readers,0 missing. Frozen definitions/class gate/newvariants pass. No aliases/pins/shared layouts/submodule changes. Production-before source+objects saved; production.patch holds tracked provider changes, new dynamesh header is untracked for explicit parent staging. Full patch must include reader diff and new header at integration.

Actual paired current-object same-index before/after witness current-paired-proof.json: readers before6/5/2 COMDAT +1 selected each, after0; native owner before2 selected,after0. Providers partial reductions only and excluded. Current normal link_check seven paths: MeshModelReadDcg559 + MeshModelReadDig842 + MeshModelReadVertexColors391 + native owner115 =1907 unique newly clean indexed existing bytes. Three providers still blocked. No real linker/census run claimed.

Strict bounded prepare-current6 refused because preparation inputs moved during concurrent edits; no witnesses accepted. Root must rerun final bounded preparation once integrated sources settle. All normal current objects are deps-current and normal byte gates passed; final strict closure still pending.

Unrowed codegen changes documented, uncounted: Add_Mesh@DX8RigidFVFCategoryContainer, Render@DX8SkinFVFCategoryContainer, Render@DynamicMeshModel. Their former header-inlined getter accesses now use existing native Get_Color_Array declaration with identical signature/thiscall ABI. Native identity independently established by current matched MeshModel forwarder D205F -> D1FBD and Define_FVF calls144286/14429E. No invented local substitute preserves wrong offsets. All MATCHED bodies, switch mappings and EH pass ordinary gates.


## Final frozen color + UV package
Production frozen, no further edits. Manifest final-manifest.json names nine edited Code sources, two headers, and two unchanged native owners (11 paired sources). Full actual paired before/after is uv-current-paired-proof.json; normal current paired output uv-current-link-check.txt. Before context uses ORIGINAL precolor objects plus fresh prebatch shattersystem/bridge/buff objects, not intermediate color baseline. Historical indexed shattersystem matched-copy assumption was stale: fresh prebatch rebuild emits wrong color copy; enabling existing color opt-in is required and included.

Six newly clean units: readers559+842+391, color owner115, W3DBuff1527, UV owner125 =3559 unique existing indexed bytes; additional over previous color package1652. Both native owners use identical current objects in before/after; their own normal gate4/4 and EH2/2 EXACT pass. No new rows, pin aliases, reference source changes or wrong-offset helpers.

Final extension gate94/94 across six source files, reader gate3/3 retained, native owner gate4/4. Affected provider EH4/4 EXACT, native owner EH2/2 EXACT, readers/Buff no EH. Frozen/class/newvariants/diffcheck pass. Final shared preparation reserved for root, no strict prepare launched during active edits. Claims all retained for integration.

UV suppression removes incidental ShareBuffer<Vector2>/UVBuffer copies and upstream memory-pool symbols from bridge; all retained MATCHED code, switch mappings and EH pass native gates. Unrowed Add_Mesh/Render changes remain the only actual retained code changes; not counted. W3DBuff loop compares the same STLport _M_node fields directly; isolated retained bytes+relocation triples identical after source-path anonymous-namespace hash normalization, only incidental iterator!= copy removed.
