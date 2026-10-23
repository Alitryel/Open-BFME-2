# Vector fill consumer provider repair, 2026-10-21

Parent 7b04693218; census e20daa4e78, 2026-10-21 21:42.
This follows vector-1504a1-provider-link-20261021.md. That note and its
blocked log entry incorrectly described 0014F4E3 as missing: it is already
matched as SourceNamespace_Shadow's copy constructor in fxshadernamespacesas.cpp.
The re_log tool flagged the mistake, prompting this check rather than an
unchanged retry. StlportConstructFamilyW3G15.cpp already forwards its element
copy to precisely that owner.

The 258-byte fill-insert's native call at 00150990 reaches 0014F4E3. Use
the same declaration-only canonical view and constructor forwarding pattern.
The temporary's local view remains 76 bytes (vptr and 72 opaque bytes), with
its existing out-of-line virtual destructor. It needs no duplicate private
base, TextureClass or RefCountPtr definitions. Removing those unused views
also removes one present-unmatched annotation and address-bound base vtable.
No function is renamed or pinned.

Forward Construct and clear to the same native providers verified by the
previous overflow repair, and declare that independently rowed overflow
specialization rather than instantiate an incompatible imported allocator.
The surviving unresolved range Destroy is forwarded to rowed
Rva0014F8AEDestroy, whose native dispatch uses the 76-byte element range and
virtual destruction. This preserves the existing element/operation ABI.

Acceptance:
- Before: consumer blocked, 0 B; previously repaired overflow already 258 B.
- After paired link_check: both units link, 516 B total; this commit adds
  **258 B legacy preview**, not 516 B.
- ./build.sh and --prepare-current: 3/3 consumer rows exact, strict reusable
  receipt, literals/imports pass. EH EXACT 1/1; the funclet label renumbering
  is independently resolved by the unchanged parent EH graph.
- find_declared_unmatched and new-variants staged-peers shadow check pass.
- Closed-strict closure and full-link runtime behavior are unmeasured.
