# GameSpy startGame empty data binding, 2026-10-21

Input BFME2 7c06faa3fc, verified BFME1 pointer 68c5ce27, published census
2b4d1fb42a (2026-10-21 06:00). Before: link_check holds the unit solely for
undefined g_bfmeEmptyF9 at the retail folded empty-data address 0x007BAC1C.
The original recovery used that synthetic name to keep the quick-match
literal distinct from the shim AsciiString::str fallback during compilation.

Use the existing StringBase<char>::str for the name lookup, preserving its
function-local const null character (the donor structure and data-ledger
owner), and ordinary empty literals for both quick-match calls. The shared
shim already treats AsciiString as a one-pointer StringBase view. Target
proof: all 360 body bytes and the empty reference still verify; the change
adds no global, pin, class view, or data alias. The function ledger's old
synthetic-global note is updated to describe the final source.

Acceptance: ./build.sh 1/1 row exact, empty-string reference verified, zero
skipped string/import references; --prepare-current passes with a strict
reusable receipt. No EH handler rows in this unit. Declared-definition,
class gate, enforced converged-data (10 addresses, zero second names or
unjudged rows), check_csv, and whitespace checks pass. Same-index current
legacy link preview changes 0 -> 355 B, unit LINKS. The census owns 355 B
although the current ledger extent is 360 B; the measured gain is 355 B.
Self-strict byte evidence and legacy link prediction only; no closed-strict
or actual placement gain claimed.

Cause sweep: PeerDefs.cpp (7,256 B) and Thread/PeerThread.cpp (19,155 B)
also reference the synthetic global but have independent losing/selected
copies and unresolved symbols. No edits or gains claimed there. Other
StagingRoom split units contain unused declarations, not live references.
Scratch: build/seat-staging-{before-byte,before-link,trial1-byte,
trial1-link,strict}.txt and build/seat-empty-cause-sweep.txt.

This commit also preserves five independent failed link attempts from the
session; object476-link-20261021 and collect-assets-link-20261021 contain
resumable diagnostic candidates. Their source edits were fully reverted,
blocked verdicts recorded through re_log.py, and claims released.

Independent seat corroboration

Upstream independently landed the same source repair before this seat rebased.
The following evidence and adjacent blocked handoffs are retained; this
rebased evidence commit claims zero additional linked bytes.

GameSpy quick-match empty strings, 2026-10-21

startGame (4FF09F..4FF207, 360B) was held out of linking by the undefined
char-array stand-in g_bfmeEmptyF9. Its pinned address 7BAC1C is the same
retail empty value as exported StringBase<char>::str()::TheNullChr.
Native lookup falls back to that character; the two quick-match names are
ordinary empty literals. The shim AsciiString::str() instead uses a literal.

Replacing only the stand-in with literals fails: MSVC shares the lookup
fallback with the quick-match names and hoists EDI's constant load, shortening
the parent by 3B. Calling the already shared StringBase<char>::str() for the
lookup restores the two native constant expressions and the entire 360B body.
No new global, pin, alias, class view or helper was introduced.

Checks: normal byte/literal/import gate 1/1; strict reusable receipt before
and after; after also checks string_base.cpp (38 rows combined, four normal
and 16 empty refs, three imports); undeclared definitions clean; no new COMDAT
variants. proof.py compares complete parent bytes with relocation fields
normalized and asserts exactly two changed relocation names, at offsets108
and172. Both now bind real constants. All other parent relocations agree.
Paired consumer/provider checks refresh only memory and preserve the published
index SHA: 0 ->355 nonpadding bytes for this consumer. This is a legacy preview
with self-strict current objects, not closed-strict or runtime verification.

Related units: PeerDefs.cpp is live-claimed by another worker and has14 other
blockers; PeerThread.cpp has85 others; Rva0020EE29Clear.cpp has24 others. A
literal fix alone cannot link those units. The two older startGame container
units own no matched rows for this body. No zero-gain sibling edit was made.

Donor review: BFME1 verified5987fd1b859e86801d093256eadc6fb63d87785f;
ZH-derived GameSpy behavior is preserved. Constant ownership and compiler
shape here are established from BFME2's native caller and shared string header.
Local diagnostic objects/logs: build/empty-string-link. Reproduce proof.py by
saving the parent commit's consumer object in before/ with its original name,
then restoring/building the repaired source and preparing string_base.cpp.
