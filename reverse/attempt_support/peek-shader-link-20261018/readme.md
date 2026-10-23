# Renderer shader provider ownership, 2026-10-18

Base: 0fd933de24; published census c2c5ac8c27 (2026-10-18 11:36).
BFME1 donor linking repairs at 67f4eab2437e reviewed using the earlier
vector-cleanup-link-20261018 survey. Verified donor pointer stays 64d369b90170:
the independently recorded freshness/vtable regression remains unresolved.

## Verified repair

`dx8renderer.cpp` emitted a non-retail `Vertex_Split_Table::Peek_Shader`
COMDAT that won over the existing whole-byte 131B provider at 0x001443D0 in
`VertexSplitTablePeekShader.cpp`. Keep the donor inline body available for
its existing callers, but import its outlined copy. Taking the address of
`GapFillerClass::Get_Shader_Array` keeps that already rowed 11B accessor at
0x005FD05E emitting; otherwise removing the shader COMDAT removes its last
emission trigger. The anchor is compilation scaffolding, not retail data.
Neither class identity nor layout is newly inferred by this change.

Paired same-index local LEGACY preview, identical five-source cohort:
146 -> 277 linked bytes; the unchanged Siege constructor accounts for the
146B baseline, and the shader unit alone newly links 131B. The renderer
still has independent blockers. This is no closed-strict or self-strict
LINK gain claim. Strict byte receipts cover 84/84 function rows across
the two providers; all five EH graphs are EXACT. String, float, import,
class and declared-definition checks pass. The new-variants comparison
retains pre-existing neighboring-copy refusals; see paired logs.

No new authored C++ coverage or ledger rows. Full link cycles were not run.

## Deferred Horde list trial

HordeContainChangeToFormation.cpp (0x00472D43/811) comparison-only
imported-forceinline passed both byte rows but freed zero linked bytes:
the separately emitted list `find` still lost. Declaration-only `find`,
with and without `nothrow`, lost compiler call summaries, shrinking the
native 0x74 frame to 0x70 and changing scheduling. Two failed byte builds;
all Horde source edits restored and its claims released. The blocked
verdict is in re_attempts.log; ignored detailed trials are in
build/horde-list-link-20261018. Do not repeat without new provider evidence.

## Queue assessment

Ranked sole/name blockers and near-2/near-1 units were checked, including
current-provider cohorts for Mesh/render helpers, Coord3D allocation,
field parse tables and constructors. Many old census blockers are already
fixed on master; do not count their preview improvements again. Secondary
`repair_queue.py link` likewise serves stale fixed entries.
`name_globals.py --dry-run` kept zero rewrites; `rehome_rows.py --limit 100`
found no moves. `class_views.py --blockers` still points at broad class/ABI
reconciliation. Screen-filter stage-state consumers additionally need
unrowed helpers and pixel constants, so suppressing a copy alone gains zero.
The packed color 0xDCF0FA false reject is already recorded (0x005966DD).

## Preparation recovery

Upstream 9338f64595 independently landed this provider repair, including
accessor emission anchors and additional mesh helper repairs. During recovery
onto c206b2a7e0, retain its declaration-only shader implementation unchanged.
The logs above document the earlier trial, not an additional gain over upstream.
