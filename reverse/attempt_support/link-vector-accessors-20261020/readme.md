# Vector accessor link repair, 2026-10-20

Input: 7bb590012b. Published census: b73720bed9, 2026-10-20 05:34,
retail-truth-2 legacy predictor. No census or status file was rewritten.

Paired checks of the original and edited objects against that same index:

| Unit | Before | After |
| --- | ---: | ---: |
| Common/INI/INI.cpp | 0 | 156 |
| Common/RTS/PlayerXferStringMaps.cpp | 0 | 585 |
| Total matched bytes predicted to link | 0 | 741 |

Both units need STLport vector<void*> accessors visible to the compiler to
preserve their existing native bodies. Their /O1 outlined accessor copies
are not the common retail implementations. Imported forceinline explicit
specializations retain the vendor expressions and inlining, while binding
outlined uses to the shared implementations. INI uses const begin and size;
the player unit uses mutable begin, size and subscript. No pin, alias, layout,
address or semantic identity was added. Target facts are the existing row
identities, full bytes, relocation targets and exact EH graphs. The accessor
expressions come from the existing STLport headers. BFME 1's declaration
binding repairs (reviewed at a2c8039e61ad4dfb20c095d8eafe048248d31f25,
including 51b97cd79) supply the technique, not target identity evidence.

Both original and edited sources pass --prepare-current: two strict reusable
compiler receipts and 6/6 full-byte rows, including extent and reference
checks. The final normal build passes 6/6; EH verification is EXACT 3/3.
The staged code-identity gate has zero new findings. Frozen-file checks pass.
The attached paired previews document the legacy gain; these strict byte
receipts do not establish closed-strict link closure. No authored C++ byte
coverage growth or full link-cycle result is claimed.

The donor checkout remains at its verified pointer. Official upstream fetch
finds 0dc8a26a9c6041c73dc564754cd059dc54faa72a, a newer data-only EDI label
commit. Advancing it requires the full old/new dependency verification; no
freshness success was recorded and no headers were substituted.
