# GridWSEnv mapper: preserve exact C++, remove four link blockers

The existing 0x00186F10/1166-byte Calculate_Texture_Matrix row moves from
GridWSEnvMapperCalculate.cpp into its real mapper.cpp home. The implementation
is unchanged apart from whitespace. Target identity remains the constructors'
vftable slot +0x24 and the named WB 0x00A38240 twin; the body is EA GeneralsMD
mapper.cpp source, available through BFME1 pointer
92f6bbe8e1dcdb46b5d27da0674313efc822b790.

The full home already supplies the exact temporal-state and UV-offset bodies,
the target Get_Transform shape, and the existing ZH Matrix4 rows-link view.
Its established native vector-construction profile emits the 34-byte iterator.
The standalone file instead emitted competing Vector4(float4), vector iterator,
Matrix4(Vector4 x4), and Transpose bodies. Rehome removes those four blockers.
No new helper anchor, optimization pragma, private class or pin is introduced.
The pre-existing mapper.cpp helper anchor is retained.

Normal byte/ref verification passes all 72 home rows, including the preceding
1174-byte WSEnv recovery. Strict prepare-current proves 75 rows across mapper.cpp
and GridTextureMapperCalculate.cpp. A scoped current-object link preview says
both retained providers link: mapper.cpp has 8123 nonpadding bytes and the
GridTextureMapper sibling has 525. The mapper's Get_Transform difference is an
unreferenced diagnostic, not a blocker. This credits no new unique C++ bytes;
the grid function was already recovered. It makes its existing 1165 nonpadding
bytes linkable in the home.

For the preview, the removed source is proved absent, staged as deleted, and
absent from the current ledger. Its definitions are removed from an in-memory
copy of the published index with link_check.forget, exactly the removal
operation used by --update-index. Only the two explicit retained providers are
refreshed from current strict-receipt objects; every other census definition
is unchanged. The normal check_object/report functions judge both providers.
No index, status, census or linker output is written. This is a scoped preview,
not a claim of a new repository-wide census or link cycle.

Negative controls: omitting the home's /O2 /G7 /arch:SSE profile changes 31 of
71 pre-existing rows and produces a 991-byte grid body. Applying the row-ctor
link declaration in the standalone unit produces 1383 bytes instead of 1166.
Appending the donor body to its actual native-profile home preserves all rows.
The isolated placement scan finds no further bodies or pins.

Transient replay: build/envmapper-next-controls-oct20.py and
build/grid-home-link-preview-oct20.py. The latter refuses any stale retained
object, any remaining ledger row for the deleted unit, or a missing staged
deletion before applying the in-memory removal.
