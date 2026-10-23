# Ladder preference providers, 2026-10-23

At d4fa46f19a plus terrain repair 709ebee9f1, current-object legacy previews
against the refreshed retail-truth-4 index show addRecentLadder and
LadderPrefCompare both unlinked (0/223 nonpadding bytes). The donor inline
LadderPref equality calls an unprovided StringBase equality template and
competes with the rowed comparison at 0x5DFC0B. Donor UnicodeString::set is
also unprovided; the actual rowed provider is StringBase<unsigned short>::set.

Keep the donor LadderPref fields, time_t map key, UserPreferences base and
LadderPreferences declaration, but declare comparison without its donor body.
Use the canonical UnicodeString header, whose inline assignment binds the
actual wide StringBase provider. Native addRecentLadder calls the 5DFC0B
comparison; its generated record assignment calls the wide set at 37150.
The normal byte and relocation gates reproduce all four existing rows with
these bindings. No new pin, alias or coverage is introduced.

After: both current objects link, 0 -> 223 B. Four unchanged peers (online
preferences main/unresolved, ladder map helpers, record copy) remain linked
at 3424/3424 B. Other LadderPref definitions already declare comparison only.
Normal build 4/4, strings/floats/imports, frozen-definition check, strict
reusable compiler receipt preparation and new-variant admission pass. This
is a bounded legacy preview gain, not self-strict or closed-strict cycle credit.
