# Extra helper copies: +5,843 B in the legacy link preview

Base: BFME2 7ee4cb14e0; frozen published census 5366c4f808, 2026-10-20
12:21. Paired current-object previews use this same index. Three existing
units newly link: mapper 5,784 B, wide filebuf underflow/facet lookup 25 B,
and ArchiveFile allocator 34 B (retail padding excluded). No authored C++
byte increase or closed-strict closure gain is claimed.

The newly landed GridWSEnv matrix unit emitted a SELECT_ANY copy of
GridTextureMapperClass::calculate_uv_offset beside mapper's strong owner.
Both copies reproduce retail; this is a real duplicate-definition failure.
Reuse the existing bfme_grid_mapper_link view and imported forceinline body,
as GridTextureMapperCalculate already does. The 1,166-byte matrix body stays
exact and the surplus copy disappears. Mapper is unchanged and now links.
Changing mapper's owner to inline instead suppresses its required row; that
trial was reverted. GridWSEnv itself still has four independent blockers:
Vector4(float x4), vector constructor iterator, Matrix4(Vector4 x4), and
Matrix4::Transpose. Its change is the verified prerequisite for mapper.

ArchiveFile suppresses its non-retail _Construct<AsciiString,AsciiString>
copy; its independent 34-byte allocator remains exact. Wide filebuf binds
_M_setup_codecvt to the existing retail provider. Explicitly instantiate its
independently rowed use_facet: suppressing setup alone removed this 15-byte
row, so that incomplete trial was corrected before acceptance.

Checks: all 74 existing rows across the four involved units pass full-byte,
string, float and named-import gates, with strict reusable current receipts.
EH: 15/15 EXACT. Frozen-source check passes; converged data: 10 addresses,
zero second names or unjudged rows; shadow data: zero findings. Code identity
reports four shadow divergent-definition findings, identical with restored
original sources and with the final sources (one tree iterator and three
Matrix4 helpers); no new identity finding is introduced. Normal hooks also
run on the staged change. The attached previews are
legacy predictions, not a new census, link.exe placement or closed-strict
measurement. No maintainer-only runner was started.

Donor review reuses the recorded helper-binding/vector-accessor linking
review at a2c8039e61ad (including 51b97cd79). The retained, independently
verified BFME1 pointer is 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
Official master fetched as 08c81de69cb26c45bd5544d0200d8d14cf5b9ea6;
its due comparative update is owned by the live file:reference/open-bfme-1
claim (yasinschroeder-codex2). Inputs and success stamp were preserved; no
freshness success is claimed. These repairs import no new donor identity or
layout; existing target evidence and provenance remain unchanged.

## Reverted attempts and handoff

AITeamBuilder idle-team vector<Object*>::push_back declaration/extern
variants change the 402-byte parent to 403 bytes and alter register/EH shape.
Screen lookup's native temporary cleanup targets 0x410688, whereas declaring
its pair destructor selects the distinct 0x2175CE owner. All five rows pass
bytes under that declaration, but the binding check correctly rejects it.
Replacing the temporary with a distinct wrapper changes lifetime scheduling
(156 to 169 bytes). Preserve full-expression lifetime and reconcile the pair
identity before retrying; simple declarations/import wrappers are exhausted.

Path 0x365B8A requires body-visible Coord3D length and normalize. Scoped
import-forceinline length preserves the 614-byte parent but leaves normalize
as a blocker; importing both changes scheduling, and ordinary inline imports
expand its frame from 0x4c to 0x58. Original source restored. Independent
inline-analysis/outline-binding reconciliation is required.

Narrow string assign dispatch's const-pointer range call preserves all 96
bytes, but the selected append provider at 0x1B3E0 also conflicts, so it links
zero bytes. Restore source; repair provider ownership before this consumer.
All four failed candidates were logged and their claims released. No failed
reconstruction or experimental header is retained in Code.
