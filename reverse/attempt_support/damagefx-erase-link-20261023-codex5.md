# Isolate DamageFX range erase from the linking helper family

2026-10-23, gpt-6.1-sol; parent 7f8ad7d896. Retain the existing
`/EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc`
settings, `_STLP_NO_EXCEPTIONS`, STLport headers and type declarations.
No donor or shared-header change. Published census 456ce161c5,
retail-truth-4, 2026-10-23 06:28.

The current DamageFX_hashtableNewNode.cpp object has one linking blocker:
its 42-byte hash_map::erase(iterator,iterator) at 0x00056B0A calls the
undefined typed hashtable::erase(const_iterator,const_iterator). Move only
that explicit instantiation and its ledger source to DamageFX_mapEraseRange.cpp.
The new source retains the existing NameKeyType, 0x780-byte DamageFX view,
hash/equality definitions and typed table-erase declaration. Neither the wrapper's
identity nor its unresolved callee is changed or claimed newly established.
The native 0x788 node allocation and 0x1E0-word copy evidence for the existing
value layout remain in the original unit's header comment.

Paired legacy current-object previews with the same four indexed sources:

- DamageFX_hashtableNewNode.cpp: 0/368 before, 326/326 after, LINKS.
- DamageFX_hashtableResize.cpp remains 252/252, LINKS.
- DamageFXHashSubscript.cpp remains 0/175 with independent wrong-copy blockers.
- StlSweepW4Rva003609F7.cpp remains 0/73 with independent wrong-copy blockers.
- Cohort: 252 -> 578 B, **+326 B linked**.

The new split unit is absent from the published index and normal link_check
reports it unpreviewable. No gain is claimed for its 42 bytes. Its typed
const-iterator range-erase provider remains a prerequisite. This result is a
scoped legacy preview, not self-strict or closed-strict link closure; no
census/index/status file is updated.

Acceptance: `./build.sh DamageFX_` passes 14/14 rows across four units;
find_declared_unmatched passes both touched sources. `link_check.py
--prepare-current` passes all 11 touched rows with strict reusable compiler
receipts on a sequential retry (the first attempt refused moved inputs while
another check was running). `--new-variants --staged-peers` passes. The original
constructor's renumbered cleanup label is resolved through its native parent
EH data; no funclet source or extent changes.

Diagnostics: build/link-seat-damage-cohort-before.log and
build/link-seat-damage-split-{after,gate,strict-retry,variants,new-unit}.log.
The extra broad `--refresh` probe was stopped before measurement; all reported
gains use the bounded same-cohort current-object previews above.
