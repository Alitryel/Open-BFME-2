# UnicodeString comparator link repair

Source base: e4dfd1e4d73662ad379c496b10168aeab5617f66. Actual local index:
147cfae2cb, 2026-10-14 07:27, SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Committed link_status.csv at 67e1365aa9 is discovery evidence only. No index,
census, status, history, ledger, pin, shared header or compiler flags changed.

The wide file-list consumer and UnicodeString set provider emitted the same
25-byte rts::less_than_nocase<UnicodeString>::operator() copy (92413eedb0b6).
The established comparator owner at 0x00037B40 emits retail's whole 26-byte
body (164f6151cef0). Both call the same StringBase<ushort>::compareNoCase:
the difference is the encoding of the argument push. The losing copies have
no separate target address. Declare the exact member specialization in each
consumer so their tree helpers retain calls to the existing external provider.
The generic predicate expression remains unchanged. No alias or escape hatch
was added and no new class layout or target identity is claimed.

Target evidence stays with the existing rows: Win32LocalFileSystem's wide
file-list body is 619 bytes at 0x006050B9, with its native vftable slot and
recursive-call evidence; comparator37B40 has the established UnicodeString
key/constructor and compareNoCase callee evidence. All five set-instantiation
rows remain byte-exact. Existing donor provenance and original application
owner uncertainty are preserved. No donor source was imported.

Reference review: verified BFME 1 gitlink 23b143233b5a8664a3bdf8572df6d905c310a5a1;
reviewed de59a7e9f891b3ed2d4221d151ca881f4b75a583 (reconcile competing
inline COMDATs) and a7c38d3b2597121f178ab5190b3062478823257d (remove an
unresolved sized-delete stand-in). The surplus-emission principle applies;
Apt-specific expressions, aliases and layouts are inapplicable here.

Acceptance:

- Ordinary byte gates: consumer 1/1 and set provider 5/5 exact. Final bounded
  link_check --prepare-current on both consumers and comparator owner: 7/7
  exact with strict reusable receipts; five literals and six named imports
  verified, zero string baselines/skips. Frozen definitions and class gates pass.
- Object proof: all retained nondebug sections, directives, extents,
  relocations and external definitions are identical after removing only each
  surplus comparator section and normalizing section numbering. All 26 wide
  consumer and 36 set provider retained COMDATs agree, including literal
  contents. Strong and weak bindings agree. The sole undefined-symbol change
  in each unit replaces removed compareNoCase with the external comparator.
- EH: wide consumer 1/1 EXACT; set has no EH rows; zero missing objects.
  Converged-data checks cover eight addresses with zero second names/unjudged
  rows; shadow checks have zero findings. CSV, new-variants admission and
  whitespace checks pass. Both affected placement resweeps find zero bodies
  and zero pins.
- Paired same-index legacy preview substitutes saved before objects and
  strict-current after objects with the same strict-current comparator owner:
  three-unit cohort 1/3 -> 2/3 LINKS, existing linked bytes 26 -> 645.
  Wide consumer: one losing COMDAT -> zero findings, 0 -> 619 bytes.
  Set provider: three -> two losing COMDATs, still 0 linked bytes; the remaining
  allocator<tree node<UnicodeString>>::allocate and alloc_proxy::allocate
  variants are independent unresolved codegen debt. Comparator owner stays
  clean at 26 bytes. CLI local checks independently agree.

A forceinline trial was rejected locally: it rewrote _M_find from 86 to 73
bytes and introduced a new COMDAT finding even though the 619-byte parent
passed. The final declaration-only change preserves _M_find exactly. Neither
that rejected source nor any changed helper body is included in this commit.

Authored C++ growth is zero. Compiler currency is self-strict for the three
explicit units. Closed-strict dependency closure, actual link.exe placement
and a fresh census were not measured. No maintainer verification runner,
census build/measure/history, nightly, boot or shadow publisher was started.
Scratch source/object/receipt snapshots and reproducible proof scripts remain
under build/wide-comparator-link-20261014 and
build/unicode-set-comparator-link-20261014.

BFME 1 freshness remains due. Official master was fetched and compared with
the clean verified checkout. Only an Apt source repair and attempt records
changed; no changed headers or direct BFME 2 use of that source were found.
The existing resolver maps upstream's game/ and inputs/reference/ layout;
resolved directories and string headers exist and 43 resolver tests pass.
Full old-input byte verification required 2982 stale TUs; after about 21
minutes 2806 remained. It was interrupted with exit130 before source edits,
because completing it would take several hours in this bounded seat. The new
comparison was not started; pointer and checkout remain23b14323, no success
stamp was written, and the reference claim was released. reference-comparison
records the exact incomplete gate and log hash; build/link-seat-freshness-20261014
retains its log. This is an incomplete verification, not a byte failure or
proof of an upstream regression. A later freshness pass still needs the full
old/new comparison before advancing the pointer.

Lane probes: repair_queue link; link_rank top/near and sole L/S candidates.
Already repaired accessors were skipped after their evidence was read; deferred
Matrix4/Physics/terrain repairs were not retried. name_globals --dry-run kept
zero changes. rehome_rows --limit4 produced four positive unclaimed leads
without applying them; that fallback was not exhausted.
