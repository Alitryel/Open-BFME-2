# Font-buffer vector provider ownership

Rehome the existing named 71-byte deleting destructor
`??_G?$VectorClass@PAVFontCharsBuffer@@@@UAEPAXI@Z` at RVA 0x001213B0
from render2dsentence.cpp to FontCharsClassConstructorBFME.cpp, both under
Code/Libraries/Source/WWVegas/WW3D2/. The receiving source already constructs
the FontCharsClass buffer vector using the same shared vector.h template and
emits the complete named body. Its ordinary byte verification reproduces
retail including every resolved relocation, without weak matching.

No source, compiler settings, pins, class identities, ABI or layout changes.
The substantive rendering source and its remaining 30 matched rows stay in
place. The existing target and donor identity evidence is retained; this is
ownership of an existing implementation, not a newly reconstructed function.
The BFME1 provider review remains f5140c1cff6a58e16276fd6de6788186286953d4,
as surveyed in link-seat-provider-audit-20261024.md. No new donor import or
unchanged donor scan is needed for this existing BFME2 consumer.

Paired current-object link_check on the same two sources and the same
retail-truth-4 index 11b3872700 (2026-10-23 23:06 UTC) reports
**734 -> 805 bytes linked, +71 bytes scoped linked availability**.
The rendering unit remains blocked on its existing surface and pending-surface
interfaces; the constructor unit links cleanly before and after. Its older
448-byte census figure omits inherited work and is not the incremental baseline.
No new census, full-image link result or unique recovered-byte gain is claimed.

Verification: ordinary build gate 12/12 constructor rows and 30/30 rendering
rows exact; string, float and import references pass. EH verify EXACT 2 with
zero failures. Paired code_identity_gate.check on both sources reports 42 rows
and zero findings before and after. Frozen-definition preflight passes.
All measured input objects are the existing unchanged source implementations.

Reproduction: run tools/link_check.py on the two source paths before and after
tools/add_match.py --replace-existing; run tools/build.py and tools/eh_verify.py
on both units. The ledger tool retains the full existing symbol and boundary.
