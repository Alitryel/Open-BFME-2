# Tribute update caller binding

At e1add84209, the 18:42 published census (d08db10acb) lacks the newly
rowed 0x0050F306 provider in its cached definitions. Check the caller together
with Common/System/Rva0050F0AB.cpp so both current objects participate.

Target evidence: rva0050FF1C tail-jumps to 0x0050F306 with unchanged ECX;
the existing caller comments and constructor 0x0050FC54 independently identify
that shared destination. The ledger now owns it as
`?rva0050F306@Rva0050F0AB@@QAEXXZ` (154 bytes). Call that rowed method
through its address-derived view; no new target class identity is asserted.
No donor source was used. BFME1 donor review: current fetched cea1e973's
applyPacket ILT binding is a different cause, inapplicable to this repair.

Before: current-object preview of caller, constructor, and provider links only
the provider (728 nonpadding bytes); caller has unresolved old method name.
After: caller + provider preview links both, 853 bytes. Increment attributable
to this change: **125 nonpadding bytes** (126 bytes of ledger extents).
The provider's separate 154-byte improvement against the old census predates
this change and is excluded. Constructor remains unchanged: it additionally
needs the two destructor owner identities reconciled (0x0050FDDC and the
local-row destructor); no gain is claimed there.

Checks: caller build.sh passes 2/2 functions, one data row, string/float/import
checks. `link_check.py --prepare-current` on caller + provider passes 12/12
functions with strict reusable receipts, one data row, four string references,
one float literal and one import. Rechecking these same objects links 2/2.
This is a self-strict current-object preview against the published index;
closed-strict provider closure and a full link cycle are not established.
