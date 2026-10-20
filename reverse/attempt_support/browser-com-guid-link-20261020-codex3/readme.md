Browser COM GUID relocation repair

Parent eddf9cf195. The 141-byte CreateInstance row at 176F10 was exact,
but its COMDAT differed from the kept SDK-emitted copy in
DX8WebBrowserInitialize.cpp. All bytes were equal; relocations at +34,
+82 and +105 used private GUID global names instead of compiler UUID names.
Use ThisIIID::GetIID() and __uuidof(IUnknown), with the standard IUnknown
UUID declaration, to reproduce the real comip.h references. The resulting
whole body and every relocation agree with the kept copy. Existing runtime
GUID globals remain because browser wrappers still reference their row names.
No address, pin, interface layout or method behavior changes.

Donor review: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790 uses
real comip.h in game/GameEngine/Source/GameNetwork/WOLBrowser/
WebBrowserComCreateInstance.cpp. That toolchain header, include/comip.h:69
and :624, independently provides these exact GUID expressions. Target retail
references and the existing UUID declarations establish the GUID identities.
An rg sweep found this to be the only private CreateInstance implementation;
the other copy uses the SDK header already. Other named GUID uses are wrappers
with different identities and remain intact.

Acceptance: strict self verification before/after 1/1; normal byte, string,
float and three named import checks clean; EH0; declared definitions clean;
converged data 0 second names. Same published census 5366c4f808
(2026-10-20 12:21), same-unit legacy closure preview: 0 -> 141 bytes, LINKS.
No closed-strict measurement or authored recovery growth is claimed.

Shadow data-name verification reports two names for the SDK UUID constants
against the legacy runtime GUID row names. Those compiler constants already
exist in the kept SDK copy; no new address or pin was introduced. Converged
data enforcement passes. This remains a limitation for full data/link proof.

Publication rebase note: upstream c6cf3219f4 independently landed the same
Matrix3D repair as local c70feaa3e0. That local commit now retains evidence
only; do not count its 2,453-byte preview gain as new over origin/master.
