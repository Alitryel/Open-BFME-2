# CreateAHeroData assignment cleanup

Removing BFME_ASCII_DTOR_DECL makes the existing inline AsciiString destructor
visible. The implicit pair<const AsciiString,TreeHintPayload001F8ACB> destructor
then tail-calls releaseBuffer at 0x00036410, matching the five-byte retail cleanup
at 0x0048BA39. Previously it tail-called AsciiString's out-of-line destructor
instead; this was an unproven differing live COMDAT in the published index.
No fields, semantics, pin, or shared-header contents change. All seven owned
rows (384 nonpadding bytes) remain exact. The only changed COMDAT is this pair
destructor; the newly emitted AsciiString destructor is the retail copy too.

Acceptance: ./build.sh passes 7/7. link_check.py and the paired before/after
object substitution measure legacy 0 -> 384 B against census 5366c4f808
(2026-10-20 12:21). --prepare-current establishes self-strict current-object
proof. No closed-strict gain is measured. See paired.json for hashes and checks.

Sweep: the only other sole AsciiString pair-destructor blocker is
Rva00410DDFInsert.cpp, whose screen-reference cleanup differs from the rowed
map-record cleanup. Imported-forceinline emits an unresolved IAT cleanup and
loses a funclet: trial reverted and recorded in re_attempts.log. Other indexed
pair-cleanup consumers have independent unresolved/provider prerequisites and
are outside this homogeneous fix. Donor checkout reviewed at 92f6bbe8; the
existing BFME 2 AsciiString shim and matched cleanup provide this repair's proof.
