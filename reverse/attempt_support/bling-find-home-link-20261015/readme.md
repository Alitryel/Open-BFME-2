# CreateAHero bling helper ownership and COMDAT repair

At source base 0d9ff5763d, the standalone Rva0021BC0DFind.cpp and its
GetBlingIndex caller both emit the exact 31-byte find helper. The caller must
see the definition so MSVC knows ECX survives the call. Move the existing row
to Rva0021BD41GetBlingIndex.cpp with add_match --replace-existing and remove
the redundant standalone source. Preserve the original row's layout evidence:
map at +0x24, through the rowed _M_find sibling Rva0021BD22Find.

The caller also emits three unreferenced vector<unsigned int> accessor
COMDATs (begin, end and operator[]) that differ from the index's first copies.
Use the established per-TU dllimport/forceinline specialization pattern with
STLport 4.5.3's exact accessor expressions. This suppresses the unused copies
while retaining every emitted caller instruction. No import reference survives.
No headers, flags, pins, aliases, gate rules, algorithm or layout change.

Target evidence: the existing row at 0x0021BC0D searches the tree at +0x24 and
returns a node; GetBlingIndex at 0x0021BD41 walks its vector at +0x14/+0x18,
calls GetBling and compares the name at +8. Its WorldBuilder name/callgraph
identity is preserved. The helper retains its address-derived name. The source
comments distinguish the map view from the target node accesses. This repair
makes no new donor identity or layout claim.

Measurement uses runner index 825b86983f (2026-10-15 12:37; original census
5986a99448). proof.json records its hash, complete before findings, strict
object/receipt hashes and after assertions. Before: both units have the helper
duplicate; the caller additionally loses the three accessor COMDATs. After:
refresh the home and canonically forget the deleted owner on an isolated index
copy. All findings clear, and the prescribed local link_check CLI reports
LINKS, 0 -> 137 existing retail bytes. Shared index and census/status unchanged.

Acceptance: before both sources pass bounded --prepare-current; after the home
passes both retail rows and gets strict reusable receipts. The first after
preparation refused to issue witnesses because the notes update changed its
inputs; rerunning after all edits passed. Proof normalizes every non-debug COFF
section, bytes, flags, extents, relocations, local references, data, directives
and EH symbol references. Exactly the three unreferenced accessor text sections
are removed; every retained section and all strong/undefined/weak bindings and
retained COMDAT facts are identical. All 13 external copies from the deleted
owner survive identically in the home, including the retail helper digest
87bc87d5f517. The proof and snapshots remain under
build/bling-find-home-link-20261015/. EH has zero applicable rows; declarations,
canonical classes, CSV, shadow data and enforced converged data pass. Placement
resweep reports zero bodies/pins. Authored C++ and matched bytes grow by zero.

This is strict self currency plus a legacy local prediction. Closed-strict
closure, fresh census, link.exe placement and data-back gains are unmeasured.
The unchanged helper symbol and relocation body preserve existing consumers
Rva0021BCA7Find.cpp and Rva0021C970Find.cpp. Their prescribed local CLI checks
pass against both the original and isolated after index, retaining 280 existing
linked bytes without claiming an additional gain.

BFME1 review: retain clean verified gitlink
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor emission repair
4966496c5ae401ec877a044e1ae6dd04f9d9f65c and COMDAT-expression repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583 with their verification evidence;
apply only their established suppression principle using target-verified code.
Official master fetched at 3a5eb7a27d25a9192ca16872ae5446a5cde592f1. The
freshness update remains owned by another worker's live submodule claim and
requires its outstanding old/new full-byte comparison. No success stamp or
pointer change. No maintainer-only verification runner was invoked.
