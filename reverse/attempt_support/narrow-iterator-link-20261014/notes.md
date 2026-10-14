# Narrow iterator equality: one competing copy removed

At BFME 2 input commit 8d49474a47, the narrow money-string reader emitted a
46-byte `istreambuf_iterator<char>::equal` COMDAT. Retail's same symbol is the
existing 126-byte matched body at RVA 0x0000FA00, owned by
`stlport_narrow_istreambuf_iterator_equal.cpp`. The shorter copy calls `_M_getc`
twice; the owner inlines cache fill and `sgetc`. This is a supported identity:
the seven direct REL32 equality calls in the matched money reader all resolve
to 0xFA00 in retail. No new pin, symbol, layout claim or compiler flag was used.

The money reader now declares its existing noinline specialization instead of
emitting that competing definition. All other retained nondebug sections,
COMDAT bytes and relocation targets are unchanged. SafeSEH symbol indices are
normalized to their handler bodies in the section comparison. `object-proof.json`
records the removed body, all eight object hashes, strict receipt currency,
the owner's complete bytes/relocations and the seven native destinations.
The local proof script remains in `build/narrow-iterator-link-20261014/proof.py`;
preparation backups and before objects remain alongside it.

## Acceptance and limits

- `link_check.py --prepare-current --paths-from cohort.txt`: before and after,
  64/64 matched rows pass across eight strict-current providers. The edited
  reader has 16 matched rows / 2,557 bytes; owner is 126 bytes. All source,
  string, float and import checks pass.
- Object comparison: one 46-byte definition removed, no other nondebug body,
  definition or relocation changed; no added COMDATs. Other seven units are
  unchanged. Self-strict evidence covers this cohort only.
- `eh_verify.py` on the edited reader: one EH-bearing parent EXACT, no debt.
- `data_check.py` scoped shadow: zero findings; enforced converged check:
  eight addresses, zero second names. Class gate, declared-definition check,
  and diff whitespace check pass. `place_bodies.py`: zero bodies / zero pins.
- Normal pre-commit hooks pass. The shadow code-identity gate reports two
  divergent definitions not present in its baseline: narrow `get_allocator`
  and `__stl_alloc_rebind<char,char>`. Both definitions are identical to the
  preserved before object (covered by the all-retained-COMDAT proof); this
  equality repair does not resolve those existing identities.
- Local `link_check.py` before/after refreshes the explicit cohort in memory:
  the reader's own equality COMDAT rejection disappears (seven wrong equality
  emitters in the cohort become six). All eight files still fail overall;
  other wrong equality emitters still win selection, along with independent
  string/iterator/facet blockers. This is removal of a competing definition,
  not an increase in linked or newly authored C++ bytes.
- Legacy census discovery/preview uses measurement commit 147cfae2cb,
  2026-10-14 07:27. Index SHA256:
  690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
  The committed link_status is older and was not treated as a new measurement.
- Closed-strict `link_check.py --current-ledger --refresh` refuses 383 missing
  current-ledger objects. No closed-strict link gain is claimed; no census,
  link cycle, nightly or runtime smoke was run. Ordinary `--refresh` was
  interrupted after expanding into unrelated tree-wide compilation; the
  bounded local preview above is the before/after comparison. Census/index/
  status were not rewritten.

## Remaining cohort and donor review

A shared declaration-only trial was checked once in the other six consumers.
`trial-cohort.txt` records seven byte failures in five units: narrow num_get's
rowed ==/!= operators, bool num_get, long-double money_get, time_get readers,
and formatted-time. Their retail comparisons require the existing inline
shape; all five edits were restored. The generic money_get's eight matched
rows pass, but six other retained COMDATs change (== 48 to 15 bytes and != 52
to 20 bytes among them), so that edit was also restored. Those copies need a
separate evidence-backed inline/outline reconciliation; repeating the same
opaque-declaration trial would not help. The blocked shared attempt is logged
through re_log.py, and all restored files pass the full cohort byte gate.

BFME 1 donor revision reviewed: 23b143233b5a8664a3bdf8572df6d905c310a5a1.
The clean narrow equality owner has the same cache-fill/sgetc structure;
its num_get_bool unit also retains visible noinline helper bodies for compiler
side-effect analysis, so it supplies no ready-made repair for the remaining
copies. Reviewed donor declaration-only link repair d003077f0b7 and inline
COMDAT reconciliation de59a7e9f891 as technique leads; this change relies on
BFME 2's native calls and existing verified provider, not donor bytes alone.

Reference freshness is overdue. Official master was fetched and is
 a7c38d3b2597121f178ab5190b3062478823257d; committed/checked-out verified donor
remains 23b143233b5a8664a3bdf8572df6d905c310a5a1. Another live seat owns the
file:reference/open-bfme-1 claim (yasinschroeder-claude2). Its pointer update and
full verification must complete there; no donor checkout, gitlink or success
stamp was changed in this seat.
