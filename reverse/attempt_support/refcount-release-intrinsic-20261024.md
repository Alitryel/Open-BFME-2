# Refcount-release breakpoint intrinsic, 2026-10-24

Existing target: `?rva006E05B0@Rva006E05B0@@QAEXXZ`, RVA0x6E05B0,81B,
in Rva006E05B0Cluster.cpp. This is the address-named existing AptCIH refcount
helper: assert positive count, retain the flag/count early return, otherwise
qualified member Release tail call. No stronger identity or type claim is added.

Replace the sole inline INT3 with the genuine VC7.1 __debugbreak intrinsic.
No memory barrier or other constraint is necessary for this complete81B match.
The existing argument domain, refcount/flag checks, layout, types and bindings
are unchanged; emitted extent, every byte and relocations remain exact.

Normal add_match --replace-existing preserves every field and existing notes,
verifies the whole file1/1 plus both string references with none skipped, and
queues the ordinary landing receipt. Published-index link preview at7e43384268
reports LINKS80->80 under that existing census metric. Normal hooks are required
on integration. No flags, pins, import declarations or data ownership changed.

The file already counts as C++ coverage; classification delta is zero.
Private diagnostics: build/refcount-release/bare.json and link.log.
