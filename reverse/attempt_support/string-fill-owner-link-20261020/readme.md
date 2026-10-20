# String fill insertion owner binding

Two existing BFME1-derived wrappers call the recovered STLport 4.5.3
`basic_string<char>::insert(char*, unsigned, char)` at RVA 0x00029530:

- BfmeConv1453.cpp: assign at 0x000297D0, 119 bytes.
- BfmeThreeHundredSix.cpp: indexed insertion at 0x0002A140, 104 bytes.

Both now declare and call the rowed member instead of private placeholder
members pinned to that address. The second wrapper retains its public unsigned
byte ABI and converts the argument to the recovered member's char parameter.
The complete caller machine bytes and relocation offsets are unchanged after
normalizing only each callee name. No pin, alias, helper implementation or
layout assertion is added. The pre-existing forwarding alias is unchanged.

Paired **legacy-index preview: +223 B (119 + 104)**. The same frozen census
3f413ed3ff (2026-10-20 18:52) is used before and after. Each original has one
unresolved placeholder; both repaired wrappers have no blockers. The ordinary
`link_check.py` consumer preview independently reports both units linking.
`receipt.json` records hashes, callee relocation offsets and all blocker lists.

The recovered native 662-byte insertion provider is also strictly compiled
and byte-verified. It is newer than the frozen census, so it cannot be added
by the legacy preview's refresh: that preview still uses the census's existing
STLport narrow-string provider. It proves consumer binding, not current
provider selection or whole-link closure. **Closed-strict gain is unmeasured.**
No census, link cycle or runtime runner was started, and no index/status was
changed. This limitation is explicit in the receipt rather than presenting a
new-provider subset as a current-ledger closure result.

Acceptance: original callers pass strict prepare-current (2/2 rows); final
callers plus native insertion pass strict prepare-current (3/3), including
string, float and import checks. Ordinary build.sh passes both caller rows.
find_declared_unmatched and check_csv pass. An object comparison proves every
retained body and relocation equal after callee normalization.

The wrappers' donor provenance is unchanged. The recovered insertion's own
source and ledger record establish its member ABI; the target calls and exact
bytes establish these bindings. No reference code is imported. The unchanged
BFME1 linking-repair review at 4483e88da1 and prior seat handoffs was reused.
