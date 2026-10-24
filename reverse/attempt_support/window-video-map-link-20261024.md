# Window video map linking repair, 2026-10-24

Inputs: BFME2 fd42dca104; BFME1 verified32774ab03393; published
retail-truth-4 index268f876e3b (2026-10-24 02:54). No shared tools changed.
The earlier donor review and freshness evidence remain applicable:
bfme1-reference-32774ab0-20261024/readme.md. The earlier audio follow-up
correctly flagged a node-size discrepancy; this repair resolves it from
native call edges rather than suppressing the wrong allocator definition.

## Native ownership

Target call edges independently establish two different map insertions:

* WindowVideoManager::playMovie53F63D -> operator[]41F4E5 -> insert53F3B1
  -> allocator3ED191 (37B, allocation12) -> pair construction60C9D9 (23B).
* MoveTo map operator[]5474E7 -> insert547430 -> allocator5472D3 (37B,
  allocation20); its pair holds ObjectID and Coord3D,16B in total.
* Both insertions call resize53F1EC (184B). Native resize only inspects
  next pointer and32-bit hash key; it never copies the mapped payload.

The WindowVideo insertion row was wrongly at547430 with a corresponding
wrong allocator pin. Its original exact byte comparison trusted that pin.
The row now points to53F3B1, ICF with NameKeyGenerator's established owner;
the old(name,address) claim is tombstoned. The proper MoveTo insertion now
owns547430. The total set of unique covered addresses does not grow.
The WindowVideo allocator pin is replaced, never retained as a second
candidate. pin_admission --add proves its whole body and recursively proves
the pair construction; the two MoveTo helper pins pass the same admission.

The pointer-key and mapped-type spellings come from the existing donor
source and target callers. Native instructions prove offsets, sizes and
call relationships; they do not independently recover template spellings.
No pointer/hash signature, public ABI or class layout was changed.

## Compiler visibility

Use the established bfmealloc allocation policy in WindowVideo. Its bucket
cleanup and stateless allocator swap follow FXListStoreParse's existing
pattern. Keep allocator and both bucket constructors visible: opaque
specializations make VC7 treat the temporary bucket storage as escaping,
producing a191B resize even after cleanup is visible. Removing only either
constructor declaration still gives191B; removing both plus allocator::allocate
restores the native184B body. MoveTo had the same visibility cause (222B).

Keep the allocator-proxy destructor opaque; making it inline breaks the
matched WindowVideo hashtable constructor. Its vector destructor must be
ordinary forceinline here: dllimport leaves an unresolved imported cleanup
reference in an emitted helper. The normal body binds the existing provider.
No custom resize algorithm or temporary diagnostic node view was retained.

Isolated tests of hash parameter/direct-hash variants and G6/G7/SSE did not
resolve the191B difference. Reference/pointer bucket-cell variants produced
181B or184B with wrong ordering/registers. These were discarded. Minimal
constructor-visibility trials isolated the actual cause. Scratch files live
only under ignored build/link-window-20261024/.

## Verification and scope

* Original WindowVideo source atfd42dca104: link_check0/2116B, blocked by
  resize, new_node and operator[] copies/selected definitions.
* Repaired WindowVideo: normal byte gate38/38, EH7/7 EXACT; LINKS2116B.
* MoveTo source: existing8/8 rows remain exact; newly correct insertion73B
  passes add_match's full byte gate (9/9). Its existing1147B already linked
  before this repair and are not credited as a linking gain.
* Both source frozen-file checks pass. pin_consistency --check has zero new
  or baselined findings. The official pin helper generated the hatch-register
  data update and stale-pin count cleanup; no baseline code was changed.

Const begin/index visibility additionally restores the native47B _M_find at
2888D4, with no accessor relocation, while all38 callers remain exact.
Inline-only pointer exchange avoids a new divergent swap<void**> definition.

Paired identity audit with isolated HEAD objects and original source rows:
15 findings before,8 after, zero introduced,7 removed (six lookup bindings
and MoveTo insert_unique). The eight inherited findings concern the existing
WindowVideo bucket initializer, four AsciiString destructor bindings, and
allocator-proxy constructor / Coord3D copy / bucket_count definitions.
The same current pin inputs were used on both sides; no baseline was enlarged.
The scratch report is build/link-window-20261024/identity-pair.json.

Final normal byte gate:47/47 across both sources. EH:7/7 exact.
Joint legacy linking preview:1147 ->3336 source-owned bytes. This includes
the corrected73B ownership record; it must not be reported as new coverage.

These are scoped legacy current-object previews, not a census or a closed
strict measurement. The relocated/fixed73B insertion is not new authored
coverage; no overlapping or folded bytes are counted as new recovery.
No maintainer-only runner was used.
