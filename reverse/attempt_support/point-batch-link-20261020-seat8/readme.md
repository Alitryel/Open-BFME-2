# Point-batch renderer: historical +3,766 B legacy preview

Recovery note (2026-10-20): upstream commit 91ef85a6bc already repairs this
unit with its scoped SSE Vector4 view and inline DX8 transform ownership.
The duplicate local source commit acc029c884 was skipped during preparation
recovery; upstream implementation is retained. The results below describe
the original local trial, not an additional gain over current upstream.

At BFME2 a2444c51d1, the unchanged frozen index is 144ed0ccab,
2026-10-20 15:34. Paired current-object previews move the renderer at
0x00177F82 from 0 to 3,766 linked matched bytes (row extent 3,781 B;
retail padding is excluded). No authored growth or closed-strict gain claimed.

Use the existing bfme_vp_math Vector4 view to preserve inline constructor
semantics without another conflicting external copy. Use the existing
bfme_seglinerender DX8Wrapper header: its Set_Transform projection path and
flag/store ordering match the established retail provider instead of the
banked donor header's nonretail helper. The complete renderer remains byte
exact, including every relocation, and current-object link_check has no
blocker. Its unused Get_Transform copy is diagnostic only under retail-truth-2.

Acceptance: normal byte/string/float/import gates 1/1 exact, self-strict
current receipt via link_check --prepare-current, EH 1/1 EXACT,
converged-data check clean. Frozen-source check passes. Ordinary commit hooks
also apply. This is a legacy local preview, not a new census or closed-strict
closure proof; no full link cycle was started.

Donor review reuses the helper-binding review recorded at a2c8039e61ad and
51b97cd79; retained verified reference pointer 92f6bbe8e. Official master
was fetched as 2c6c8f89bacf381fd6f736b9f2a2b90ff1e8f2d1. The due pointer
update remains pending the comparative full-gate update
reported in link-extra-copies-20261020/readme.md; no freshness success stamp
was written. This repair imports no new donor identity or target layout.
