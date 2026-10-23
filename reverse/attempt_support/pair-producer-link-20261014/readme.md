# Pair-producer link repair

Source base: 3aa670037fb43fd71b5403ef55aa8c0b73954d1b. Actual local index:
147cfae2cb, 2026-10-14 07:27, SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Committed link_status.csv at 67e1365aa9 is discovery evidence only. The index,
census, status, history, ledger, pins, shared headers and compiler flags are
unchanged.

The two-word factory and qualified-name splitter produce returned BfmePairEL
objects without destroying one. Their implicit destructors nevertheless emit
two incompatible unused 53-byte COMDATs, e5a8bc4194e7 and 590124a26d0e. The
factory copy is selected first in this census. Both actual consuming units,
PlayerListValidateTeam and TeamFactoryFindQualifiedPrototype, emit the same
five-byte destructor (cc24d668550a) that jumps to the established
_STL::pair<const AsciiString, AsciiString> destructor. Declare the destructor
without a definition in each producer to leave destruction with the existing
consumers. No destructor call is introduced, removed or redirected. This removes
the two unused competing implementations and their associative EH data.

This is a dependency/emission repair, not a new target identity or class-layout
claim. BfmeWordEL/BfmePairEL and the splitter retain their existing structural
spellings and donor uncertainty. Target factory 0x0002C621 (27 bytes) retains
its verified hidden return-buffer ABI and pair-constructor call; splitter
0x0032ABDA (184 bytes) retains its verified character scan, substring calls,
factory calls and string cleanup. PlayerList::validateTeam at 0x002A851D
retains all 717 target bytes and its existing caller/WB identity evidence.
The preview accounts 712 bytes after excluding 0xCC padding. TeamFactory's two
141-byte rows retain their previous evidence. No row or pin was added.

Acceptance:

- Both producer byte gates pass (2/2). Strict bounded preparation of all four
  explicit units before and after passes 5/5 rows, two literals, zero string
  baselines or skips, and issues strict reusable receipts.
- Object comparison removes only the named unused destructor section, its
  COFF associative EH children, and its .sxdata handler entry. Debug sections
  are excluded; section numbers, .sxdata symbol indices and .sxdata section
  order are normalized. All remaining nondebug sections, directives, bytes,
  extents, relocations, external definitions, strong/weak bindings and retained
  COMDAT referent contents agree. One factory and eight splitter COMDATs are
  retained unchanged; both consumer objects are byte-identical. No undefined
  reference is added. Factory loses four unused cleanup/EH imports; splitter
  references are unchanged. Hashes and comparisons are in object-proof.json.
- All four EH parents are EXACT, zero baseline, zero missing objects. Frozen
  definition and class gates pass. Converged-data checks cover eight addresses
  with zero second names or unjudged rows. New-variant admission, CSV and
  whitespace checks pass. Affected placement resweep: zero bodies, zero pins.
- Paired previews refresh the same unchanged index in memory with the saved
  before objects, then strict-current after objects for all four units.
  Legacy local result: 0/4 -> 1/4 clean, existing linked bytes 0 -> 712.
  PlayerListValidateTeam loses its sole COMDAT blocker and has no findings.
  The standalone CLI local check agrees. Compiler currency is self-strict for
  the explicit cohort; no closed-strict gain, actual link.exe placement or
  fresh maintained census result is claimed. New authored C++ bytes: zero.

Remaining independent blockers: factory has no provider for its structural
BfmePairEL constructor; splitter still emits/selects a nonretail
StringBase<char>::getCharAt; TeamFactory still emits/selects a nonretail
_STL::pair scalar-deleting destructor. These do not prevent the measured
PlayerList gain and were not folded into this repair.

A rejected consumer trial declared a dllimport forceinline destructor. Its
717-byte parent passed, but the EH gate found a changed 13-byte .text$x thunk
at 0x00775716 and it introduced an unresolved __imp_ destructor. The consumer
was restored before this final repair; none of that trial is included.

Reference review: clean verified gitlink and checkout
23b143233b5a8664a3bdf8572df6d905c310a5a1, official master fetched at
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor commit
de59a7e9f891b3ed2d4221d151ca881f4b75a583 (competing incidental COMDAT
reconciliation): removing unused competing emission is applicable, donor
layouts and Apt-specific details are not. No donor source was imported.
BFME 1 freshness remains due: the earlier old-input full gate required 2982
stale TUs and was interrupted after about 21 minutes with 2806 remaining.
This unchanged blocker and exact evidence live in
../unicode-comparator-link-20261014/readme.md and its reference-comparison.
No new full gate, pointer update or success stamp was attempted here; the last
verified inputs were preserved.

Lane probes: repair_queue link; link_rank help/top/near and L candidates.
Already repaired/deferred blockers and live claims were respected.
rehome_rows --limit8 produced eight unclaimed leads without applying them;
this fallback is not exhausted. No maintainer verification runner, census
build/measure/history, nightly, boot or shadow publisher was started.
Scratch sources, objects, strict receipts, and proof script remain under
build/player-team-pair-link-20261014. The proof asserts saved/current object
comparisons, strict receipt currency, index hash stability and both previews.
