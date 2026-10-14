# Quit-menu link repair, 2026-10-14

Source base: `08590b8cd20e8babc5b56160bcc300fd76d2fa83`.
Legacy census/index: `147cfae2cb`, 2026-10-14 07:27; its SHA256 is in
`object-proof.json`. No census, status or baseline was edited.

The affected consumer is
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptQuitMenuCallbacks.cpp`.
It had two unresolved donor names for background dispatch and a losing local
20-byte Unicode `isNotEmpty` COMDAT. The current ledger already owns the
background bodies at 0x00222F55 (186 bytes) and 0x002233A6 (74 bytes) in
`Code/Libraries/Source/WWVegas/WWLib/Rva00222F55Background.cpp`.
Existing symbols.csv alias notes tie the donor names to exactly those addresses.
The calls now name these existing target-owned members. No original class or
method spelling is inferred from this equivalence. Their declarations share
the unit's existing address-derived invoke view; there is no layout change.

`Code/Libraries/Source/WWVegas/WWLib/string_base_inline.cpp` owns the retail
40-byte out-of-line predicate at 0x000358E0. A dllimport/forceinline specialization
suppresses the consumer's distinct out-of-line copy while retaining its existing
inlined replay test. The consumer emits no new import reference.

The local paired check refreshes the same legacy index in memory with current,
byte-verified objects for both providers and the consumer, using either the
saved before object or the after object. Consumer findings fall from two
unresolved names plus one COMDAT loser to zero; both providers have zero findings
before and after. Existing consumer bytes are 3,788; new authored C++ bytes are
zero. This is a **legacy local prediction**, not a measured self-strict or
closed-strict gain. The explicit objects have strict reusable compiler receipts;
that establishes input currency, not full closure. A maintainer-run full link
cycle remains outstanding and was not started.

The independent object comparison retains 62 COMDATs and 77 nondebug sections
unchanged except for the two documented external relocation-name substitutions.
Exactly one 20-byte predicate COMDAT disappears. Strong/undefined/weak bindings,
common definitions and alternates retain their identities after those two
substitutions. Local relocation targets are compared by section definitions,
contents, value and storage rather than unstable COFF numbering. SafeSEH
`.sxdata` indices resolve to unchanged handler identities. Data bindings and data
definitions compare equal between both objects. Object hashes and full paired
findings are recorded in `object-proof.json`; saved objects and the exploratory
proof script remain under ignored `build/link-seat-20261014/`.

Checks:

- `./build.sh` consumer: 22/22 exact, 34 literals exact, zero unverified or
  baselined literals, zero compiler float literals and zero named imports.
- `link_check.py --prepare-current` consumer/background: 24/24 exact, 42 literals;
  string provider: 52/52 exact, 12 empty references and 16 named imports. Strict
  reusable receipts were produced without expanding the ledger or index.
- `eh_verify.py` consumer/background: five EXACT EH records, no missing objects,
  no baseline; string provider has no EH records.
- `link_check.py` consumer plus both providers: all three link cleanly against
  the legacy index after current-object substitution; see `link-check.txt`.
- `link_check.py --new-variants` all three: exit 0.
- `find_declared_unmatched.py` consumer: all definitions matched; `class_gate.py`
  consumer: exit 0; `check_csv.py`: 88,418/17,029/426 rows OK.
- `data_check.py --converged` all three: eight addresses, zero second names or
  unjudged rows. Data shadow check retains one pre-existing wrong-name finding
  for `?MessageStreamSubsystem@@3PAVMessageStream@@A` at 0x00A00950; the proof
  confirms data bindings and definitions are unchanged.
- `place_bodies.py` consumer: zero additional bodies or pins. `git diff --check`
  passes. No ledger rows, pins, baselines or shared headers change.

Donor review: BFME 1 `de59a7e9f891b3ed2d4221d151ca881f4b75a583` demonstrates
normalizing an incidental Apt predicate to a verified keeper; `d003077f0b7ce97622adb7a53f1fe76653433c5c`
demonstrates calling an existing matched owner instead of a competing wrapper.
These mechanisms are applicable; no BFME 1 address, class layout or expression
was imported. Current committed donor inputs remain at
`a7c38d3b2597121f178ab5190b3062478823257d`; official master was fetched at
`16c79ec657766fe5455c4f8fda00eef108080fa5`. Freshness remains due: the recorded
old-input baseline requires thousands of stale TUs and has not completed. No
pointer advancement or freshness success stamp was made in this bounded repair.

Queue context: `repair_queue.py link` and `link_rank.py` supplied candidates.
The mapper/Ascii destructor candidate already links after upstream repair
`d4fe1a7b5b`, and its file claim was released. `name_globals.py --dry-run` finds
zero rewrites. `rehome_rows.py --limit 5` cannot run without the missing
`build/link_census/census.log`; this is an artifact blocker, not an empty queue.
