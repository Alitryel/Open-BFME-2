# Distance opacity math-header link repair

Base checkout: `1e31a5d3dc`. The runner index measures `147cfae2cb`,
2026-10-14 07:27, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
The committed link-status queue measures `67e1365aa9` and serves discovery
only. No census, status, history or data-back artifact was changed.

Claimed the W3DModelDrawDistanceOpacity.cpp file before editing. Its sole
current link finding is a surplus `_sqrtf` COMDAT emitted by MSVC math.h.
That seven-byte body has digest `b8b5523737ca`; the first index definition
is WWMath/coord3d.obj with digest `99747d18cb82`, without a retail address.
The opacity row's square root already inlines. Scope math.h's inline float
overloads to static linkage, using the established technique in BFME 2's
Rva009F66F0.cpp. The inline macro is restored immediately after the include.

Native 0x000B5A72..0x000B5C41 is still the complete 463-byte RET4 row.
Existing target/WB identity and layout qualifications remain unchanged;
the original method name remains unknown. This repair imports no donor body,
class layout, pin, alias, global or new function identity.

## Verification

- Before and after bounded `link_check.py --prepare-current` pass 1/1 rows
  with strict reusable compiler receipts. Ordinary `./build.sh` passes 1/1,
  both float references and all string/import checks, with no baselined or
  skipped references.
- Object comparison removes only `_sqrtf`. All four retained COMDATs have
  identical complete bytes, extents, digests and relocation facts. External
  undefined references and weak bindings are unchanged. The removed copy
  was a loser, so the index's existing first definition is untouched.
- Against the same index, the ordinary legacy local preview changes from
  one COMDAT finding to clean: 0/1 to 1/1 units, LINKED 0 to 463 existing
  authored bytes. There are no new undefined dependencies. No shared header
  or provider changed; the affected current consumer is this one unit.
- New-variant admission, class gate, declared-definition check, shadow data,
  CSV and whitespace checks pass. Converged-data checking finds zero second
  names or unjudged rows at eight addresses. EH checking has no applicable
  rows or missing objects.
- Placement resweep reports zero bodies and zero pins. The same-cause index
  sweep finds nine other losing sqrtf units, each with 36 to 192 findings;
  none is another sole-blocker repair. The queue facts are in object-proof.json.

This establishes self-strict object currency and a legacy local preview
gain, with zero new authored C++ bytes. Closed-strict closure, actual
link.exe placement and fresh census gains remain unmeasured. No full census,
link cycle, nightly or boot runner was started. Detailed acceptance and
before/after logs accompany this record; source/object backups and the
comparison script remain local under build/opacity-sqrt-link-20261014/.

## Reference review and remaining prerequisites

The clean verified BFME 1 checkout/gitlink remains
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. Reviewed available donor linking
repair `fea964f85433012ec0c95a44a8d88f77b4c29af5`: its direct allocator
provider bindings are inapplicable to this unused math emitter. The broader
unchanged donor scan is recorded in prior geometry/math repair evidence;
the applicable local sibling already contains the scoped math-header fix.

Official BFME 1 master was fetched to
`a7c38d3b2597121f178ab5190b3062478823257d`. Freshness remains blocked on
the previously recorded full old-input baseline rebuild (thousands of stale
TUs), required before a controlled old/new comparison. Kept the verified
inputs and did not write a success stamp or retry the unchanged blocker.
