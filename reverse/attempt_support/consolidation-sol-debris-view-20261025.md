# W3DDebrisDraw composition prerequisite, 2026-10-25

Seat codexb, family B shard 0. The allocated destination is
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp.
The original ordinary dry run accepts no merge: ReactToTransformChange loses
bytes and Xfer collides with the seed's legacy StringBase declaration. Merely
switching the string include exposes the legacy Xfer collision; moving the
transfer declarations into an included header also keeps canonical Xfer's
operand declarations ahead of it when the merger hoists includes.

BfmeDebrisDrawView.h shares the transfer donor's existing BFME 2 fields and
second interface with setAnimNames. The animation enum and derived method
signatures already exist in the seed's previous declaration. Animation/render
and shadow pointers replace the transfer-only void pointers without changing
layout. Both sources use canonical AsciiString and Xfer. The seed retains
WW3D2/HAnim.h for its existing Release_Ref implementation and stops including
unneeded legacy game headers. Neither function body changes. The unused local
Xfer::Version definition and StringInlineData declaration are removed.
Target layout evidence remains the existing rowed constructor/destructor and
transfer accesses, rather than a claim that a donor layout proves BFME 2's ABI.

Acceptance: ./build.sh on W3DDebrisDraw.cpp and W3DDebrisDrawXfer.cpp preserves
9/9 rows (308-byte animation parent and 268-byte transfer parent, their two
EH handlers and five funclets). One literal, one empty-string reference and
one named import verify. tools/eh_verify.py reports EXACT 2, no missing objects.
find_declared_unmatched.py and class_gate.py pass both sources and the new
header. tools/data_check.py reports zero findings; code_identity_gate.check
on both sources reports 9 rows, zero new findings, shadow, with the same
scoped reference records as before. ms_header_audit.py scans three files with
no local Microsoft declarations; the scoped owning queue refresh is unchanged.
No data, code-identity or header-register key moves or retires.

The ordinary final --merge TU --dry-run accepts the seed and transfer donor
with all 9 rows. The transfer's four rows are newly compatible with this seed.
Leave the actual merge for Luna. ReactToTransformChange still brings legacy
StringBase/Module declarations and is rejected; the four protected-register
donors and two mixed sources remain untouched. No merge/split was applied.

Binding verification uses allowed_symbols._object_defs/row_object on the
baseline and final objects: both sources' external code definitions (digest,
size, exclusivity) and undefined references are identical, including every
AsciiString COMDAT. The final composed trial object c4348bedd32d349b.obj has
exactly the union of those baseline definitions and external references.
Thus this trial changes no provider variant or consumer reference; shared
copies are identical. link_check.py --new-variants --staged-peers --shadow on
both sources completes without a new-variant report. This is scoped object
and binding evidence, not a new link census or a game-link claim.

Receipts: build/sol-debris-{before,canonical-after,shared-build,eh,data-before,
data-after,identity-before,identity-after,headers,composition-bindings,
link-variants}.txt and build/sol-debris-{object-before,canonical-object-after}.json.
The refreshed planner is build/consolidation/sol-draw, checked current after
the final dry run. Its first refresh overlapped the verifier's temporary source
and correctly refused an unstable snapshot; the sequential refresh succeeds.

Publication audit: origin/master advanced from 97b2c77498 to d9a2d3b8f0 while
working. Reviewed origin/master..HEAD, its merge-base/outgoing-commit scope,
and this staged prerequisite together. The pending inherited AptString commit
and this repair change no existing source path and absorb/delete no file.
Active tools, hooks, workflows, includes, build inputs and registries have no
old-to-new path to repoint. Both new local includes resolve to the tracked
header. Historical EA paths stay as evidence. Protected registers and the TU
map are unchanged. C++ files removed, recovered bytes and identity keys retired:
zero; one local header is added.

Keep file claims for the destination, Xfer donor, BfmeDebrisDrawView.h and this
handoff, plus RVAs 0x000B1DC3, 0x007614A1, 0x007614A9 and 0x007614B1 until
publication is confirmed. The publisher may retain this batch; the inherited
AptString split handoff lists its separate outstanding claims. Release file
claims after landing and settle RVAs with claims.py release --landed.
