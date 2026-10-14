# Voice-response caller ABI repair

BFME 2 base: 6a4410341df4075c91bcc7c2fc7769f7d6c18e9d.
Discovery: repair_queue.py link and link_rank.py. The committed discovery
status measures 67e1365aa9; the available local index measures cb660e4d97
(2026-10-13 04:02). Its SHA256 is in object-proof.json. These are distinct
measurements. No census, status, history or per-row measurement artifact changes.

The verified provider has now landed at 0x004DAAFD as the bool-returning
pickAndPlayUnitVoiceResponse. Callers' old void-return declarations still name
an undefined C++ symbol. Correct only the return declarations of the available
claimed consumers. They ignore the result; their calling convention, argument
types, implementation, layout, compiler settings, and complete emitted bodies
stay unchanged. No new pin or alias bridges the mismatch. The old void pin
is retained for consumers outside this batch, including actively claimed files.

Target evidence: functions.csv owns the real bool provider in
Code/GameEngine/Source/GameClient/Drawable/PickAndPlayUnitVoiceResponse.cpp,
5284 bytes (5078 code plus 206 switch data), from WB identity and complete retail
callgraph evidence. The independently gated provider defines the exact bool
symbol. object-proof.json checks each edited caller's matched native REL32
calls against 0x004DAAFD and compares all non-debug/non-directive COFF sections
before and after. Only relocation referent names change; bytes, flags, extents,
section associations and external definitions remain identical. The provider
object is unchanged. No donor identity or layout is newly asserted.

Donor review: retained verified checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 already declares the same bool ABI in
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_playMoveVoiceResponse.cpp.
This declaration repair is applicable directly, with BFME 2 native call-target
proof. Reviewed newer upstream d003077f0b7ce97622adb7a53f1fe76653433c5c:
its stream attach repair similarly binds the matched provider directly, but its
MilesAudio classes and addresses are inapplicable to this voice function.
Official master was fetched successfully; FETCH_HEAD was
e0c623620c077cc216eb49c8e74c16e6349a9a7d (origin/master advanced again during
the fetch to 8126bd5c3b43913708b1f09268fa40e9de13c15c).
The prior full old-input baseline remains blocked by long-running unchanged
MSVC compilations (build/reference-update-blocker.txt), and later session
evidence also records shared compiler-lock/stale-TU preparation blockers.
Retained the verified pointer and old freshness-success stamp; the overdue
comparative full-gate update is not claimed complete or retried unchanged.

Acceptance:

- Bounded strict reusable preparation before and after passes 185/185 existing
  matched rows in the 25 consumers and unchanged provider. The sole edited
  CRLF declaration line was normalized to LF after a whitespace finding; its
  final strict recheck passes 4/4. Final independent ./build.sh passes 185/185,
  62 literals, 10 empty-string references and 64 float literals, with zero
  baselined or skipped string references. Final object proof checks all 26
  receipts self-strict current after that last gate.
- All 25 consumers' non-debug/non-directive COFF section bytes, flags, extents,
  associations and external definitions are identical before/after. Only the
  voice return-type spelling changes in relocation referents. All 42 matched
  native calls reach 0x004DAAFD, and the independently verified unchanged
  provider defines their new exact symbol. Funclet label renumbering remains
  the normal byte gate's responsibility; the relocation proof skips those
  synthetic row labels rather than assigning them guessed identities.
- The same-index legacy preview has 391 findings both before and after across
  these 25 consumers. Exactly 25 unresolved spellings change void -> bool;
  all other findings are identical. The new provider postdates this index and
  is absent from its object set, so it cannot account for the resolved current
  call graph. LINKED remains 0 -> 0 bytes. The permitted current-ledger preview
  refuses 314 missing objects, recorded in closed-preview.txt. This is a
  verified ABI/dependency repair with self-strict objects; no new authored
  bytes, census gain, strict link closure or closed-strict gain is claimed.
- Declared-definition checks and class gate pass. Converged-data enforcement:
  26 sources, eight addresses, zero second names and zero unjudged rows.
  check_csv and git diff --check pass. Normal commit/push hooks remain active.

Remaining: CommandXlat_Rva004297bb.cpp and PlaceEventTranslator.cpp are held by
other contributors and retain their void declarations. Other consumers absent
from this historical index need a separate current review (including
ControlBarCommandProcessing.cpp). Keep the legacy void pin until all remaining
users are reconciled. The older index also reports independent global-provider,
STLport/COMDAT and other ABI blockers unchanged by this repair. Census refresh,
closed-strict closure and overdue donor comparative verification remain
outstanding. No full census, link cycle, nightly, boot or scheduler run started.
Unrelated untracked reverse/zh_sweep/ preparation is preserved.
