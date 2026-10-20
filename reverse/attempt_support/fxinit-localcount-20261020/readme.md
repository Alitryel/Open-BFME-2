# FXShaderGeometry::Init: local-count and temp-count sweeps on the two-bone block

Target `?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z`, retail 0x0018C84E, 2,333 bytes. Result: blocked. The bank `reverse/attempts/0x0018c84e.cpp` (partial, 0.995) is unchanged and still the best body. No Code source, ledger row or pin changed. Model claude-opus-5-5.

## Measurement of the retained bank

`tools/align_diff.py` on a fresh copy: 2,333 B and 735 instructions on both sides, 0 structural regions, 12 memory lines (five are absolute relocation slots), 0 register lines. The seven real lines are the two-bone block at retail +0x707..+0x71E. The unresolved short `_Vector_base` constructor call (0x211E58) is unchanged.

## Hypothesis tested and refuted

The 0x00561564 lever (operand picks rotating with the count of surviving locals, mod 8) does not exist in this body.

- Chains of 1 to 9 used pointer-copy locals at four sites (a `MeshModelClass *` copy at the top of Init, the `vertices` pointer, the bone-link pointer and the mesh pointer at the index-buffer allocation) compile to an Init body that is byte-identical to the bank's. The local count has no effect on anything here.
- Temp-count probes that survive the optimizer (repeated stores of `mesh->Get_Vertex_Count()+k` to a global in the stream setup, n = 0..160, and at the end of the function, n = 1..32) never change the two-bone registers. This holds even where they change the frame (n >= 42) and where they flip the links[1] SIB operand order (n = 120). Unused-local probes (`{int d=mesh->Get_Vertex_Count();}`) and constant stores are inert, so they create no relevant temps.
- The WorldBuilder-shown normals test (WB 0xA3A127 tests the address of the `normals` array, so the source reads `(m_FVF & 0x10) && normals`) is inert. `|` and `^` in place of `+` add one region.

## What the block actually differs in

Retail: `mov ecx,[diff]; mov eax,[iv]; movzx edx,[ecx+eax]; movzx eax,[eax]; mov ecx,[remap]; movsx eax,[ecx+eax*2]; movsx edx,[ecx+edx*2]`. So the link-pointer induction variable sits in eax, links[1] is loaded before links[0], links[0] overwrites the induction variable, and remap[links[0]] is computed first into eax with the remap base in ecx.

Ours puts the difference in eax and the induction variable in ecx. That register pair is the same whichever way the SIB is ordered: the bank encodes `[diff+iv]` and a named-vertex-count variant encodes `[iv+diff]`, and both keep iv in ecx. The SIB order follows the temp numbering, but the register pair is a separate decision that the numbering does not reach.

Diagnostic (not bankable): declaring `int link0=links[0][i];` before the two-bone store makes +0x717..+0x73B match retail exactly, with remap[links[0]] first into eax and the base in ecx. What remains are the first four instructions: ours loads the induction variable into ecx and links[0] first, retail loads diff into ecx and the induction variable into eax and reads links[1] first. align_diff then gives 2 regions, 3 memory lines and 0 register lines. It is not closer under the regions-first rule, and WB 0xA3A315 rules the local out, because the debug build pushes `links[0][i]` straight into `operator[]` without storing it.

## Other natural variants measured, none closer

Measured: a named vertex count for the links and weights setup (6 block lines, but four offset-0 SIB sites flip); a hoisted inner loop bound (frame grows by 4); `remap[*bone]=index++`; a named `Vector2` weight; named bone0 and bone1 values; named 16-bit or int link0 and link1 in either order; `*256`; a stride local; a bones-per-vertex local; a reference to the destination; `int` or `unsigned` casts on either remap index; and `operator[]` taking `int`, `const unsigned &` or `unsigned short`, or reading through a local `begin()`.

## Next hypothesis

Retail's order looks like the code generator evaluated the links[1] load as a materialized value before the sum, with links[0] then targeted to eax. A source shape that WB does not show as a local could produce that, for example an inline layer of the real STLport `vector<short>` or WW3D accessor that materializes its argument. The observation that would confirm a candidate is retail's seven instructions at +0x707 with the rest of the body unchanged.
