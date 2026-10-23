# Link seat: current-object triage and STL visibility refusals

Inputs: BFME2 checkout based on 456ce161c5 published index (2026-10-23
06:28); retained verified BFME1 pointer 138757e9b74645fbcbb7724a7af2764e34931e11.
BFME1 origin/master fetched; pointer update remains blocked by the prior
FireWeaponWhenDeadBehavior UpdateModule vtable relocation conflict documented
in link-seat-20261023-recovery.md. No freshness success was recorded.

## Narrow string owner

`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp`, default
existing compiler flags, 21 matched rows. New append and byte-copy providers
have removed earlier blockers. Three current independent leftovers are
`basic_string<char>::_M_compare`, `insert<char*>` (forward iterator overload),
and `_M_range_initialize<char*>` (forward iterator overload). Legacy linked
preview remains 0/881 B; no closed-strict measurement.

Combined declaration-only specializations for those members crash VC7.1 at
`vendor/stlport/stl/_string.h:801`. The initial attempt-log record mistakenly
used 0x8990 for the comparator; the subsequent correction identifies the real
pin 0x24FC0, 135 B. This was a link visibility trial, not reconstruction there.

A new independent lead from `multibyte-link-astra-s4.md` avoids the ICE by
retaining the inner iterator parameter:

```cpp
namespace _STL {
template <> int basic_string<char>::_M_compare(const char *, const char *, const char *, const char *);
template <> template <class ForwardIterator> void basic_string<char>::insert(char *, ForwardIterator, ForwardIterator, const forward_iterator_tag &);
template <> template <class ForwardIterator> void basic_string<char>::_M_range_initialize(ForwardIterator, ForwardIterator, const forward_iterator_tag &);
}
```

Placed immediately after `<string>`, this compiles but fails 2/21 rows:
`char_traits<char>::compare` is no longer emitted, and mutable
`_M_initialize_dispatch` changes the native 13-byte tail wrapper beginning
`8d4424088944240ce9` into argument setup beginning `8b5424088d44240850`.
Needs exact visible nested bodies or supported provider/emission reconciliation.
Both trials were restored. Normal byte gate then passes 21/21, imports 5/5.

## Wide ios imbue

`stlport_wide_ios_imbue.cpp`, native 0x16200, 238 B. The current sole blocker
is the unproven narrow copy-assignment COMDAT differing from the kept copy.
The primary assignment must stay visible for the native inlined self-test.
An explicit imported forceinline specialization with the verbatim vendor
body, immediately after `<string>`, adds the initialized iterator-tag byte
and changes locale temporary stack placement. Imported ordinary `inline`
at EOF emits an unwanted import call. Restored source passes its normal
1/1 byte gate. Prior 81691 evidence already describes the same visibility
problem; do not repeat either spelling without a changed prerequisite.

## Queue interpretation

Several census blockers already disappear with current objects/providers:
registry, wide_ifstream, float_format, narrow_money_get_string, particle
emitter constructor/copy/destructor, GettingBuiltBehaviorModuleData ctor,
and the SidesList ctor. The paired SidesList preview includes its sidesInfo
and SubsystemNameGetters2 providers and links 999 B; this is existing upstream
work, no new gain credited here. Similar paired GettingBuilt ctor/dtor links
388 B including the existing 179 B dtor. No source change claimed for either.

`name_globals.py --dry-run` over nine non-generated address-blocked sources
finds no supported replacements. DX8Skin's row claims are held by another
seat, and its full vector-table/ICF reconciliation remains deferred. The
largest EVA and vector<E16> blockers retain recent unresolved handoffs.

All trial source edits were restored and all claims taken here released.
No new authored or newly linked bytes are claimed by these refusals.

## Verified classic-locale data repair

The locale handle at VA DA6214 has the four retail loader bytes `18 e1 dd 00`.
`locale::classic` (71B0, 6 B) returns DA6214. `make_classic_locale` (B730,
908 B) constructs its existing 24-byte `_S_classic_locale` buffer at DDE118;
all 24 loader bytes are zero. Those target facts establish the relationship
independently of the STLport donor name. The global locale handle's name was
already referenced by the rowed locale implementation.

Expose that existing buffer with C linkage, retaining its COFF name
`__S_classic_locale`, and own both objects in data_rows.csv. A deliberately
reconstruction-only tag constructor initializes the handle pointer without
acquiring a reference before the implementation has been constructed. It is
not claimed as an original STLport constructor or as recovered code.

The existing address-named 7B6890 callback loads DA6214 and dispatches slot 2.
Its global now names the same locale object, and its implementation view uses
the established `_Locale_impl` destructor/incr/decr slots. No original callback
name is inferred. The unused old candidate pin is not a second definition.

Paired legacy link_check previews: locale 0 -> 182 B, classic builder remains
1369 -> 1369 B, release callback 0 -> 11 B: **+193 newly linked B**. The
refresh replaced 63 stale ledger objects and 93 objects rebuilt since census;
no gain from those unrelated changes is attributed here. All 46 touched
function rows and both data rows byte-verify. `--prepare-current` also produced
strict reusable receipts for the three touched providers and repeated their
ordinary gates. No self-strict or closed-strict linked-byte gain was measured;
no full link cycle was run.


## Follow-up queue handoff

The first narrow append provider has already been repaired upstream in
1a5cf68cc3 and b8613df467. The six-consumer preview against the old published
index still reports selected copies, but refreshing that upstream provider is
not a new repair. The tracked narrow-append-static-allocator-20261023 handoff
records its +3,840 B result. Similarly, HordeContainRva00475F61 now links
1,671 B, and the Render2DSentence Thai/word-vector pair has already been
repaired upstream; no additional gain is credited here.

Fresh current-object probes still refuse the AIStatCollector count-map
constructor (container/initializer identity prerequisite), the unowned
StructureToppleUpdate and CollisionManager destructors, and CreateAHeroData's
inconsistent virtual views. The CreateAHeroData target table at C38D88 has
409D31/B3FD0/409353/408C11; the existing name-getter and DoXfer owner names do
not establish the private crc/xfer overrides. Existing handoffs were read;
no alias or fabricated table provider was added.

The remaining smaller vtable probes also fail: Rva003FD4DADtor 0/123 B and
Rva003FD3EFDtor 0/126 B differ from the first LivingWorldLogicDelayedEventXfer
copies. Those first copies inherit a seven-slot structural event view, while
the destructor units inherit abstract Snapshot directly; the parameterized
constructor has yet another BfmeBaseVNH view. Merely copying the first
unproven table would not prove the native class contract. The 84 B
PartitionFilterRejectBuildings constructor similarly differs from the first
private table and remains below the standalone repair threshold. No source
trial or new queue verdict was made for these read-only probes.

Permitted fallback checks: repair_queue.py link was inspected and current
objects probed; class_views.py --blockers and selected --class views were read;
name_globals.py --dry-run found zero supported rewrites in nine address-blocked
sources. rehome_rows.py cannot run without the unpublished census.log artifact.
No census rebuild or full link cycle was started. Reviewed donor linking repair
c20e733a1574 and related BFME1 history at the retained verified revision; no
additional directly applicable, independently proven repair was found. DX8Skin
and deque row scopes are held by other seats. All this seat's claims are
released. Remaining actionable work requires the named provider/compiler/class
prerequisites or a refreshed measurement artifact rather than another copy of
these unchanged trials.
