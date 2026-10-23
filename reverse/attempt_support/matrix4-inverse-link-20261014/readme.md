# Matrix4 inverse constructor COMDAT repair

At checkout b69af954d2, `Rva007133F0MatrixInverse.cpp` emitted a 110-byte
`Matrix4(const Matrix3D &)` COMDAT that differs from retail's 129-byte owner
at 0x0006A2CD (`Matrix4FromMatrix3DO1.cpp`). Default construction followed by
the existing row-wise widening, inlined through `Init`, preserves the inverse
body while removing that constructor copy. The imported forceinline `Init`
does not emit another copy of camera.cpp's 0x00068FEF provider. Vector4's
default constructor is empty in the existing verified donor headers.

The inverse's target boundary remains 0x007133F0, 332 bytes. Its original
donor provenance and address-derived identity qualifications remain in the
source; this repair establishes compiler/link behavior, not additional target
class identities. Compiler flags and dependencies are unchanged. BFME 1's
verified gitlink remains 23b143233b5a8664a3bdf8572df6d905c310a5a1.

## Local evidence

The runner index is dated 2026-10-14 07:27, measurement commit 147cfae2cb,
SHA256 `690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
No census/status files or index were modified.

| Scoped legacy preview | Before | After |
| --- | ---: | ---: |
| Inverse unit findings | 4 | 2 |
| Material-rendering unit findings | 9 | 9 |
| Constructor owner findings | 1 | 1 |
| Dynamic-shadow consumer findings | 1 | 1 |
| Clean units | 0/4 | 0/4 |
| Linked bytes | 0 | 0 |

Only the inverse's constructor COMDAT and selected-wrong constructor findings
disappear. Remaining inverse findings are the unresolved
`?Inverse@Matrix4@@QBE?AV1@XZ` and retail-wrong
`??_H@YGXPAXIHP6EPAX0@Z@Z`. Other wrong constructor copies still prevent the
129-byte owner and dynamic-shadow consumer from linking.

Object comparison removed the constructor and its three unused inline helpers
(Vector4 assignment, Vector4 Set, Matrix3D const indexing), added only a
three-byte empty Matrix4 default constructor, and changed no retained COMDAT.
Strong definitions, external-reference sets and weak bindings are unchanged.
No out-of-line Init or imported call was added. All seven directly readable
cohort row bodies and relocations compare equal before/after; the two shadow
EH labels are verified by the gate's compiler-label remapping.

Inverse raw 332-byte object-body SHA256:
`8b9e0240c5b40ae1f7be870fe6dff03cf6f61c17c9055861a66e64cff05566fd`.
Relocation SHA256 (JSON, sorted keys):
`a8c5e7a891b7b0ed799d76ab991c4dc6c76b6154373141c76a56e3ff2cf20d4f`.

## Acceptance checks

- Before: `link_check.py --prepare-current` on the four units, strict 9/9
  matched rows, string/float/import checks and EH labels verified.
- After: `./build.sh Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp`
  passes 1/1, including the float reference. `link_check.py --prepare-current`
  on that source passes with a strict reusable receipt.
- The same four-source `link_check.py` preview gives the table above. Its exit
  status remains 1 because the documented blockers remain.
- New-COMDAT-variant admission, class gate, undeclared-definition check,
  converged-data check and CSV validation pass.

This is a self-strict byte-verified repair with a legacy local finding
reduction. It adds zero authored C++ bytes and claims no closed-strict or full
link-cycle gain. Maintainer-only runners were not started.

## Refused sibling and donor review

The material-rendering sibling at 0x0014A880 (2482-byte extent) was restored
after two failed byte trials: importing its constructor changed the frame
from 0x100 to 0x140; default construction plus Init retained the frame but
changed SSE scheduling and relocation positions. Its restored body passes
the byte gate. The blocker was recorded and its file claim released.

BFME 1 commit 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 was reviewed for its
StringBase COMDAT-owner reconciliation. Suppressing a competing wrong inline
copy is applicable here; that commit's string repair itself is inapplicable
to Matrix4. Upstream HEAD a7c38d3b2597121f178ab5190b3062478823257d is newer,
but the reference submodule has another seat's live claim and its freshness
verification remains outstanding. No pointer or headers were substituted.

Full logs, original object/source backups and object snapshots are local in
`build/matrix4-inline-comdat-link-20261014/`.
