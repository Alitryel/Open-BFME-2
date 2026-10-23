# Bridge local model accessors and unused getter emission

Base checkout: 3a666355dd. Measurement index: 147cfae2cb, 2026-10-14
07:27, SHA256 recorded in object-proof.json. The committed link_status queue
is discovery evidence from a different measurement. No census, index, status
or history was changed.

W3DBridgeLoad.cpp and W3DBridgeGetModelVertices.cpp have local MeshClass
views that load their model at +0xC4. Both emit Peek_Model under the shared
name, despite that name's matched owner in decalmsh.cpp reading +0x94 at
retail 0x005BE199. Rename the implementation helper to bridgeModel in both
views and their inline uses. This claims no new retail identity. Native bridge
rows 0x000DE648/2774 and 0x000DDE13/1179 independently verify their +C4
accesses; the shared owner passes its existing seven-byte retail row.

The loader's donor Get_Instance call supplies an unused local. Its incidental
getter COMDAT references an undefined WW3DAssetManager::TheInstance and
differs from the index's first getter copy. Mark this inline definition
dllimport plus forceinline to suppress its unused emission. Neither an import
reference nor a call to that getter remains in the object. Its global datum
is no longer referenced. Removing the unused statement instead changed native
register allocation and was discarded. The final bridge body, flags and
layouts remain unchanged.

Acceptance and controlled comparison:

- Bounded link_check.py --prepare-current before and after supplies strict
  reusable byte receipts for both edited sources. The unchanged decalmsh.cpp
  owner also passes 21/21 matched rows with a strict receipt.
- Final ./build.sh on both edited units passes 2/2 rows: 2774 and 1179 bytes,
  five strings plus four empty strings, six float references and three named
  imports; none baselined or skipped. EH verification is EXACT for its one
  applicable row, with zero missing objects or baseline entries.
- Paired checks refresh only these objects and the verified shared owner in
  memory against the same index. Loader findings change 4 -> 0; vertex-builder
  findings change 5 -> 3. Local legacy LINKED preview gains 2765 existing
  bytes, excluding retail padding. No new authored C++ bytes are claimed.
- All 35 retained external COMDATs in the loader and 19 in the vertex builder
  have identical raw bytes, extents, normalized relocation targets and digests.
  The renamed seven-byte helper remains 8b81c4000000c3 with no relocations.
  COFF symbol indices and physical section numbers are normalized in the proof.
  Strong definitions and weak bindings are unchanged. No undefined name is
  added; only the unused TheInstance reference is removed.
- The shared owner remains 8b8194000000c3, verdict retail, with a current
  strict receipt. Removing these losing local copies leaves the existing
  selected shared providers untouched. The new helper copies agree with each
  other and have no external callers introduced by this repair.
- Frozen-definition, class, new-variant admission, CSV, whitespace and shadow
  data checks pass. Enforced converged-data check covers eight addresses with
  zero second names or unjudged rows. Placement resweep finds zero bodies or
  pins. No header, alias, pin or protected baseline changes.

Reproduction: run ./build.sh with the two edited paths, link_check.py
--prepare-current with those paths and decalmsh.cpp, then ordinary
link_check.py on those three paths. Full paired snapshots, original objects,
receipts, logs and proof.py remain in build/bridge-load-link-20261014.
The committed JSON records source/object/index hashes and paired findings.

These are self-strict byte checks and a bounded legacy link preview.
Closed-strict closure, actual link.exe placement and a new census gain remain
unmeasured. The shared owner's independent blockers are unchanged. No
maintainer-only verification runner was started.

Sweep and handoff: W3DBuffBufferFill.cpp already isolates its +C4 view.
W3DBridgeGetModelVerticesFixed.cpp still gets the same conflicting accessor
through shared donor headers and emits an intentionally retained nonmatching
getModelVertices sibling for register allocation. It also has independent
pool, lighting, index-builder and UV blockers. Reconciling those headers and
duplicate ownership requires a separate supported repair. The edited vertex
builder retains its duplicate getModelVertices finding and two UV findings;
the loader is locally clean. Other renderer users require their own layout
and family reconciliation; no broad header substitution was attempted.

Donor review: verified BFME 1 gitlink a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed donor linking repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d,
which removes incidental per-unit string constructor emitters. That ownership
principle applies here; no donor code, names or layouts were imported.
Target byte evidence establishes applicability independently. Freshness fetch
finds official master 16c79ec657766fe5455c4f8fda00eef108080fa5 ahead of the
verified pointer. Prior old-input baseline preparation remains blocked by
compiler stalls and thousands of stale units (count-tree-ai-link-20261014);
that unchanged full-gate prerequisite was not repeated or marked successful.

Earlier independent attempt: Rva00079554RecordDtor.cpp retained three local
link findings. Two carefully scoped destructor-emission trials failed its
byte gate. Its original source was restored and verified, the blocked evidence
was recorded with re_log.py, and both claims were released. It is not part of
the bridge gain and should not be retried without new code-generation evidence.
