# MapCache and ios link-binding handoff

Base 2584a0290c; refreshed published retail-truth-4 index b711de3634,
2026-10-23 14:28. BFME1 verified input96c88c73a5cd1a58fc2f8db691beea50acd996db.
Model gpt-6.1-sol; existing source compiler settings retained in all trials.
No retained C++ changes and no new linked-byte or coverage credit.

## MapCache metadata erase

Current paired preview: MapCacheClearUnseenMaps_Rva0030469e.cpp0/322B.
The sole blocker is pair<const AsciiString,MapMetaData>'s implicit destructor,
which differs from the kept copy. Native range erase at RVA003042DD (68B) calls303DA4: symbols.csv already locates the template name there,
but the real definition is Rva00303DA4::rva00303DA4 in Rva00303DA4Erase.cpp.
That provider explicitly rebalances, destroys the value at node+16, frees,
and decrements tree count; its existing address-derived identity is preserved.
The source's native row notes and REL32 establish the relationship; a pin
alone was not treated as a link definition or identity proof.

Trials:

- A declaration-only implicit pair destructor specialization passes7/7 byte
  rows and exact EH, but VC7.1 still emits the conflicting destructor.
- Moving it before tree use requires the complete metadata view. With that
  definition moved too, the byte gate still passes and the conflict remains.
  An incomplete-view trial fails C2079 and was corrected immediately.
- dllimport on that declaration passes7/7 row bytes but produces an unresolved
  __imp destructor and a wrong unrowed single-node erase copy. Discarded.
- Declaring single-node erase externally removes the pair conflict while
  passing7/7 byte rows. The template spelling then has no actual provider;
  its existing pin to303DA4 does not define that symbol.
- The attached range specialization calls the rowed opaque owner directly.
  It fails only the68B range row: retail passes the postfix iterator's
  by-value result through a stack temporary and preserves this at EBP-4;
  extracting _M_node into a pointer argument removes that temporary and uses
  EDI for this. The source preserves the STL algorithm but does not preserve
  compiler ABI handling. range-diagnostic.txt records the whole mismatch.

Do not repeat implicit-destructor declaration suppression or assume the
opaque provider is available under the template spelling. A useful next
hypothesis must preserve the iterator argument's compiler treatment, or
reconcile the real metadata tree identity and provider family. The original
source is restored and its7/7 byte gate passes. All eight claims released.

## Narrow/wide ios imbue

Current narrow325B/wide238B both0 linked. Their sole conflict is
basic_string<char>::_M_assign_dispatch<char*>; its standalone96B provider
already links. Declaring the member-template specialization before ios
instantiation ICEs VC7.1 (C1001, _string.h629, compiler main.c148).
Calling _M_assign_dispatch directly from the local grouping adapter also
ICEs, now at that call. Original .assign spelling restored;11/11 combined
byte rows pass, no repair retained. All four claims released.

## Other lanes checked

Refreshed rank(top30,near2), class_views --blockers, repair_queue link.
Current-object checks remove stale leads: ArmySummaryCopy803B and
Rva003F2D03Dtor1132B already link. Hashable family repairdc623d4c10 is
already inherited. GeometryInfoCtor/B3FD0 and broad class work are claimed
or require complete ABI/provider reconciliation; existing handoffs remain
applicable. DamageFX erase and int-float map callers retain documented
hash/type and twin-insert blockers (81974 and39901); no repeated source
experiments. Current float-map consumer pair remains0/106B.

name_globals --dry-run finds0 edits. rehome_rows --limit10 tests the
compatible split-unit queue; its exact4F6318 candidate is already linked
in both units (29+2441B). The second exact placement, View::getPosition,
also already links in both units (17+802B). The third exact placement,
GenP12pod insert into its subscript unit, already links too (712+431B).
None earns a repair. No measurement-matched
data-back artifact exists locally; data_back_rank was not fabricated.

Official BFME1 masterf5140c1cff6a58e16276fd6de6788186286953d4 was fetched
and its intervening link repairs reviewed. No pointer update or successful
freshness stamp: the paired-verification prerequisite baseline waited
roughly five minutes on the shared compiler lock (locks_lock_inode_wait)
and was cancelled. Retain verified96c88c7 inputs until the paired full
gates can complete. No maintainer-only runner was started.
