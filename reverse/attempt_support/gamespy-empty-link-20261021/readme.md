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
