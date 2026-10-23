# EnumeratedIP layout link repair (2026-10-18)

At BFME2 revision 8423f1a10b, OptionsMenu.cpp was the census's only provider
of EnumeratedIP::getIPstring, pinned at 0x002E4336. Its Zero Hour class view
inherited MemoryPoolObject, placing the AsciiString at +4. Retail's getter
copies the member at +0. BFME2's rowed EnumeratedIPCtor.cpp and the 12-byte
allocation in IPEnumerationGetAddresses.cpp independently establish the
string/IP/next layout at offsets 0/4/8. These are target facts; the getter's
name and purpose come from the donor source, corroborated by the LAN
preference caller and its existing pin. No new pin or alias was added.

Use that established view locally in OptionsMenu.cpp. The getter changes
from 27 bytes to retail's complete 24-byte body, removing add ecx,4. A direct
build.compile_function(..., allow_weak=False) on the existing getter symbol
returns exact=True, unresolved=[], masked=False, including its sole REL32
to StringBase<char>'s copy constructor at 0x000365F0. The existing pin's
consistency check also passes. The source's sole matched row remains exact;
find_declared_unmatched passes and --prepare-current issues one strict
provider receipt. No shared header or baseline was changed.

Same four current providers, same published index c2c5ac8c27 (2026-10-18
11:36): legacy prediction 2,315 -> 2,519 linked bytes (+204). The LAN
preference unit (194-byte body and 10-byte handler) newly links. GameSpy's
194 bytes and Apt's 2,121 already linked and are not counted as gains.
OptionsMenu's own 27 matched bytes still have independent unresolved and
STL/getOnlineIPAddress blockers, listed in after.log. Other emitted IP and
next accessors now share BFME2's verified offsets too; these were diagnostic
rather than blocking differences. This is a legacy prediction with a
self-strict current provider receipt, not closed-strict or a full link run.

Session total: five separate verified link repairs predict +1,094 linked
bytes (300 + 112 + 246 + 232 + 204), without growing authored C++ coverage.
Remaining investigations and BFME1 freshness blockers are documented in the
preceding repair evidence; no maintainer-only verification runner was used.
