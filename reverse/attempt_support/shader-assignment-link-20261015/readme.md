# Particle shader assignment emission repair

Source base: `0959ecbec0be3859b23557a2a0e758c370ddc97c`. Frozen runner census: `ac77c85054`, 2026-10-15 14:25 UTC, SHA256 `a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`. The published-index fetch retained this index. No census, index, status or history was rewritten.

The StreakDrawModuleDoParticles and FXParticleDefaultModule6 units each emitted an unused 13-byte `ShaderClass::operator=` COMDAT, digest `0977a7baecfc`. The first indexed copy is in `sharebuf_shader_copy_ctor.cpp`, digest `b73ef41a446f`. The copies differ in register scheduling. None has an independently established retail address; this repairs first-copy findings rather than asserting a new helper identity or proving the first copy native.

Both consumers retain the complete assignment expression and add `__declspec(dllimport) __forceinline` to suppress their surplus standalone copies. The copy constructor already uses this mechanism. All three files were claimed before editing; the first-copy witness remains unchanged. No shared header, layout, compiler settings, pin or allowance changes.

## Paired object and link evidence

All three objects are strict-current before and after. The consumers have version-2 include-inventory receipts; the header-free witness has an ordinary receipt accepted by the strict header-free rule. Source, object, receipt and index hashes are in `proof.json`.

The ignored `build/shader-assignment-link-20261015/proof.py` compares saved before objects to after objects. Each consumer removes exactly the assignment COMDAT, one section and one external definition. Every retained nondebug section preserves its bytes, size, flags, symbolic relocations and external bindings; linker directives remain identical. Local relocation targets are compared by actual section contents and offsets. No code or data relocation references the removed helpers or their sections. No imports or replacement definitions appear. The first-copy witness is byte-identical.

The paired check refreshes only these three strict-current objects into separate in-memory copies of the same frozen index. Streak findings fall from two to one; DefaultModule6 findings fall from three to two. Each loses exactly the assignment COMDAT finding. The witness stays link-clean with 301 nonpadding bytes. The index contained only these three assignment copies, and the unchanged witness is now the only copy. This drains the supported assignment-copy conflict in that index.

Remaining findings are unchanged: both consumers reference unresolved `?g_00DB6250@@3VShaderClass@@A`; DefaultModule6 additionally references unresolved `?RenderVolumeParticle@PointGroupClass@@QAEXAAVRenderInfoClass@@IPAX@Z`. The ordinary prescribed local CLI exits 1 for those existing unresolveds. Local legacy LINKED bytes remain 301 -> 301 across the three units; authored C++ byte growth is zero. No closed-strict closure or full-link improvement is claimed. No maintainer-only runner was started.

## Acceptance and donor review

- Bounded strict preparation: 6/6 matched rows across all three sources, before and after.
- Edited-source byte gate: 2/2 matched; string, float and import checks pass.
- EH: three EXACT rows, no nonexact or missing objects.
- Paired data findings identical; enforced data check has zero findings. Converged-data check: eight addresses, zero second names or unjudged rows.
- Declared-definition, class and no-new-variants checks pass; placement resweep finds zero bodies or pins.
- Ledger and whitespace checks pass before commit.

BFME1 verified checkout remains `a7c38d3b2597121f178ab5190b3062478823257d`. Reviewed donor repair `53d32d6b4b377317a3397971629ca3ad20b870e9` (Apt default constructors): its suppression mechanism applies; its class identity, ABI and layouts are not imported. BFME2 byte gates and complete retained-object preservation prove this local adaptation independently.

Official upstream fetch found `7afa50f4cfe2205fab66de58312bc722dccf8cbe`. Another live worker holds `file:reference/open-bfme-1`; verified inputs were preserved, no pointer advance or freshness-success stamp recorded. Comparative update verification remains outstanding with that worker.

Reproduce by strictly preparing the three sources at the recorded base and saving their objects and receipts; apply the patch, strictly prepare again, and compare all retained nondebug object facts and paired local link results with the recorded frozen index. Saved before sources, objects, receipts and the comparison script remain ignored under `build/shader-assignment-link-20261015/`.

Publication rebase: retained upstream comment wording for the already-landed MathCoord2D repair while preserving earlier evidence commits. After rebasing onto `07ba78ba8e`, strict preparation again passes 6/6 rows, all three objects are reused as strict-current, and the complete paired preservation/link proof passes unchanged. Particle sources and frozen index hashes remain the recorded ones.
