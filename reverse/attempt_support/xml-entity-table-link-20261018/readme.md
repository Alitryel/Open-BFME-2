# XML entity-table link repair, 2026-10-18

The published c2c5ac8c27 index leaves the rowed decoder in
`Rva005426DBDecode.cpp` unlinked solely through its undefined table name.
The native 0x005426DB loop bounds establish five eight-byte EntityEntry records
at RVA 0x009D1E74. Retail contains name pointers in order lt, gt, amp, quot,
apos and byte values 60, 62, 38, 34, 39. Each three-byte padding field is zero.
Define precisely that table under its existing address-derived name and row
its full 40 bytes, including verification of every string relocation and sizeof.
No original global name or new decoder identity is inferred.

The paired frozen-index check predicts 0 -> 96 linked nonpadding bytes (one
native 96-byte code row), with a strict reusable current object receipt.
`proof.py` proves every existing COMDAT and retained nondebug section, flag,
external definition and symbolic relocation identical; only the table's data
section and its five native strings are new. Data integrity/identity checks,
normal byte gate and new-variant checks accompany the measurement. The
self-strict currency of these inputs does not establish closed-strict or
full-game closure; this is a legacy index prediction. No census or full link
runner was invoked. Local before objects and the index digest are kept under
`build/xml-entity-table-link-20261018/`.
