# UnicodeString comparator provider repair

At BFME 2 base 29ed91ba8a, the wide Win32 directory-listing consumer and its
UnicodeString set helper emitted non-retail copies of
`rts::less_than_nocase<UnicodeString>::operator()`. The existing verified
26-byte provider at 0x00037B40 belongs to stlport_unicode_string_compare.cpp.
The caller's set-find and insert operations already use this same decorated
comparator. Declare its explicit specialization in both consumers so those
calls use the existing provider. No algorithm, ABI, layout, flags, ledger row,
pin, alias, marker, global, shared header or baseline changes.

## Evidence and acceptance

- Target identity is the existing comparator row: StringBase comparison at
  0x00006AA4 and the string node constructor at 0x00054DF6 independently anchor
  UnicodeString. The set-find 0x00604D0E, set-insert 0x00604E11 and directory
  body 0x006050B9 retain their exact bytes and original relocations.
- The directory-listing unit's ordinary gate passes 1/1 rows (619 B), and the
  set provider's passes 5/5. Bounded `link_check.py --prepare-current` on the
  two consumers and comparator provider verifies 7/7 rows, all three objects
  with current strict reusable receipts. Five literals and six imports pass.
- object-proof.json compares full retained COMDAT bytes, sizes and relocation
  digests: 26 directory, 36 set and 2 comparator COMDATs are identical.
  Each edited object loses only its wrong comparator. Its external reference
  to StringBase::compareNoCase disappears because only that removed copy used
  it; the comparator name becomes an undefined reference to the real provider.
  No other binding changes. Nondebug sections, relocation targets and linker
  directives are unchanged. The provider object is byte-identical.
  Before/after objects, source backups and the comparison script are retained
  under ignored build/unicode-compare-link-20261014.
- EH verification: one EXACT parent, no nonexact/baseline/missing objects.
  Class gate, declared-function gate, new-variant admission, CSV and whitespace
  checks pass. Converged-data check: three sources, eight protected addresses,
  zero second names or unjudged rows; shadow data check: zero findings.
- Placement resweep on both edited units: zero bodies and zero pins.

## Local result and limits

The unchanged runner index was measured at 147cfae2cb, 2026-10-14 07:27.
Its SHA256 and the full base commit are in object-proof.json. The committed
repair_queue status at 67e1365aa9 is older discovery evidence, not the local
measurement. Both local checks use the same index and three explicit objects.

| Unit | Findings before -> after | Existing local LINKED bytes before -> after |
| --- | ---: | ---: |
| Win32LocalFileSystemGetFileListWide.cpp | 1 -> 0 | 0 -> 619 |
| stlport_unicode_string_compare.cpp | 0 -> 0 | 26 -> 26 |
| stlport_unicode_string_set.cpp | 3 -> 2 | 0 -> 0 |

This enables 619 existing authored bytes in the legacy local preview, with
zero added C++ coverage. The two set allocator copies remain blockers.
cohort.json lists the complete indexed comparator blocker cohort: these two
consumers are the entire cohort, and the index has three comparator copies.
No wider improvement is claimed.

Strict receipts prove current compilation and byte matching, not self-strict
LINK closure. `link_check.py --refresh --current-ledger` refuses a closure
judgment because 388 current-ledger objects are missing (closed-after.txt).
No closed-strict gain, fresh census placement or runtime result is claimed.
No census build/measure/history, full link cycle, nightly or boot runner ran.

## Donor review and reference state

Reviewed BFME 1 repair d003077f0b7ce97622adb7a53f1fe76653433c5c from the
verified donor revision 23b143233b5a8664a3bdf8572df6d905c310a5a1. It removes
an incidental attach definition and declares the member so it uses an existing
matched provider. That provider-reconciliation principle applies here;
BFME 2's comparator and call relationships are independently verified above.
No donor source, type layout or address is imported.

Official BFME 1 master was fetched to a7c38d3b2597121f178ab5190b3062478823257d.
The clean checkout and gitlink agree at 23b143233; its successful full gate
is recorded in BFME 2 commit 9b6bf3e581 (2026-10-14). The local ignored
freshness stamp still refers to an older pointer. This repair retains the
verified inputs and does not advance the pointer or write a success stamp
for the newer upstream revision. A subsequent reference update needs the
prescribed old/new full verification and affected sweep refresh.
