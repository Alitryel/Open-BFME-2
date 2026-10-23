# MessageBoxOk consumer ABI reconciliation

At BFME2 58573e9797, eleven private declarations still gave MessageBoxOk a
GameWindow-pointer return type, while the existing complete 158-byte matched
provider in MessageBox.cpp at 0x0044C0A8 returns void. Nine consumers emitted
fourteen matched retail calls to that body; all discard the result. The other
two declarations are unused. Change all eleven declarations to the provider's
void ABI. Remove their obsolete pointer-return pin and lower only its keyed
hatch count at 0x0044C0A8 from two to one. The independent opaque-argument pin
at that address is outside this repair's scope. No row, extent, class layout,
header, flag, definition, marker, data symbol or alias is added or changed.

Target evidence: object-proof.json records all fourteen REL32 operands and
computes the native destination from each complete row's retail bytes. Every
one reaches 0x0044C0A8. The already rowed provider supplies the void declaration
and complete byte/relocation proof. Changing the declarations preserves every
non-debug/non-directive section's bytes, sizes and flags, every relocation's
offset/type and referent except the one return-type spelling substitution,
and every external definition. The unchanged provider object defines exactly
the new call spelling. This compares all emitted code, including unrowed
siblings, rather than only the ledger bodies. Raw before objects, source
backups, proposed files and the proof script remain in ignored
build/messagebox-link-20261014. Original source line endings are preserved.

Acceptance:

- Bounded --prepare-current before and after: all twelve providers have
  strict reusable receipts and 166/166 exact rows. Ordinary ./build.sh also
  passes 166/166; 175 literals, 20 empty-string refs and 15 imports verified,
  zero baselined or skipped references. Four funclet labels are already
  renumbered and resolve through their independently verified parent EH data.
- EH verifier: 53 EXACT graphs; zero missing objects, nonexact or baselined
  graphs. Enforced converged-data: eight addresses, zero second names or
  unjudged rows. Data shadow retains five pre-existing findings (four outside
  baseline); object proof preserves every data relocation and section byte.
- Declaration coverage, CSV, pin consistency and placement resweep pass;
  placement returns zero new bodies or pins. Whitespace check uses Git's
  cr-at-eol setting for the already CRLF source. Class, case, identity, hatch
  and variant admission also run in the normal commit hook.
- The available local census index measures 147cfae2cb at 2026-10-14 07:27.
  The committed queue at 67e1365aa9 is discovery only. That index lacks
  MessageBox.cpp and Rva0043F483PopulatePlayerCombo.cpp. The ordinary paired
  legacy previews cover the other ten consumers: zero units link before or
  after, 0 -> 0 linked bytes. Nine old unresolved spellings become the real
  provider spelling, which this stale index also lacks. Other findings stay
  unchanged. No index/status/history or data-back artifact is modified.
- --refresh --current-ledger before and after refuses 362 missing provider
  objects before judging closure. No whole-tree compile or maintainer-only
  census, link cycle, nightly, boot or scheduler operation was started.

Verified improvement: eleven consistent declarations, fourteen emitted calls
bound to the existing provider's name, and one fewer incorrect pin/escape
hatch. Authored coverage does not grow. Strict receipts and complete object
proof establish current bytes and dependency identity; they do not establish
self-strict placed linkage, closed-strict closure or measured census gains.
A refreshed runner census is needed to measure those outcomes.

Donor review: official BFME1 master fetched at a7c38d3b2; the retained verified
checkout/gitlink is 23b143233. Reviewed direct-provider repair d003077f0 and its
scoped-byte/local-link evidence: applicable principle is to call the existing
matched provider, without importing that unrelated stream class or layout.
BFME1's GUI/GUICallbacks/MessageBoxOk.cpp still has a pointer-return shim, so
that donor ABI is inapplicable here; BFME2's rowed provider and retail calls
supply the local proof. The overdue reference-pointer update remains held by
the foreign file:reference/open-bfme-1 claim (yasinschroeder-claude2). No pointer
or freshness-success stamp changed, and no successful update is claimed.

This resumes the prior compiler-lock deferral after the lock became available.
All twelve file claims were reacquired before editing; the provider is a
verification witness only. Unrelated reverse/zh_sweep preparation is preserved.
