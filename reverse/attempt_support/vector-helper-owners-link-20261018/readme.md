# Vector element helper ownership

At BFME2 f25e2e7c57 and census c2c5ac8c27 (retail-truth-2), paired current objects for thirteen units preview 4,348 -> 4,927 legacy linked bytes (+579 B). Each 183-byte overflow consumer becomes clean; the existing 30-byte outer-vector clear at 500EDC also becomes clean. Other providers retain unrelated unresolved/selected/COMDAT blockers. This is a legacy preview, not self-strict or closed-strict closure evidence; no authored C++ coverage gain is claimed.

Target calls establish helper ownership independently for each opaque view:

| Overflow RVA | Placement-copy call | Clear -> Destroy -> element destructor |
| --- | --- | --- |
| 50129F | 500B11, existing _Construct<vector<BfmePod88>> | 500EDC -> 500AF8 -> 4FABE2, existing vector<BfmePod88> destructor |
| 5C856D | 5C83CD, existing _Construct<Rva005C8624Element> | 5C84D3 -> 5C847B -> 5C8FBD, existing Rva005C8FBD destructor |
| B059B | AD77B, existing _Construct<BfmeStringRecord00111ACF> | B0298 -> AFF52 -> 111B25, existing Rva00111B25Record destructor |

The original STLport4.5.3 overflow implementations, storage widths, row names, pins, compiler settings and template instantiations remain. Forced-inline ABI views bind placement-copy and clear calls to existing whole-body owners; the full byte gate checks each relocation. These bindings identify helper bodies, not the unknown application records. No new pin, alias, global or data layout is introduced. All ten other files are included in both measurements. Declaring the outer clear specialization in VectorPod88CopyConstructor.cpp prevents its unrowed competing definition from displacing the native 500EDC owner; this is a verified prerequisite for the 183-byte overflow and the 30-byte clear, even though that constructor unit retains separate blockers. Clear ownership is explicit in all three consumers, so they do not emit competing private copies. The destructor paths above are target evidence, while final source directly calls each existing clear owner. An initial B059B helper emission produced a new identity finding; the corrected external owner binding removes it. No new identity findings remain across the four edited units.

A fourth trial, 3F3277, is restored and recorded blocked. Native _Construct<vector<unsigned>> is 3F1A5F, while the same-name pin selects 460F18 (another rowed copy is 796E8). Its parent fails the strict REL32 check even though the legacy link preview is clean. No pin or alias workaround is retained. The fourth-trial gate log records this refusal; only the three independent passing consumers are committed.

Acceptance: strict reusable receipts plus normal scoped byte gates pass 189/189 functions across all thirteen files, including current providers; two literals plus two empty-string references pass. Frozen-file, class, and converged-data checks pass on the four edited units (zero second names or unjudged rows). check_csv and diff whitespace pass. No full census or LINK runner was invoked.
