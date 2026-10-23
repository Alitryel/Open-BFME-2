# GenericAIObjectType cache owner repair

BFME 2 base `6f1a5ade180dedd0d6ec92376725353f83d224c9`; local census index
measurement `cb660e4d97`, 2026-10-13 04:02. The committed link-status snapshot
at `67e1365aa9` served queue discovery only. No per-row data-back artifact was
used; no census/index/status file or counter is changed.

Remove the second cache definition `g_00DBDC84` in Rva0030D4F2Getter.cpp.
Both its getter and Rva0030D773Method.cpp now declare the existing real
`const StaticNameKey TheKey_GenericAIObjectType` owner from WorldHeightMap.cpp,
then cast the owner's address to their established cache view at the call.
Add its eight-byte verified data row. WorldHeightMap.cpp remains unchanged.
Rva0030DBD5Lifecycle.cpp already uses the canonical declaration and view cast;
there are no remaining definitions or declarations of the old spelling in Code.
No new header, private class definition, code pin, alias, function row, range,
compiler setting or hatch annotation is added.

## Target proof and donor distinction

Retail RVA `0x009BDC84` contains `00000000 1c91c000`. VA `0x00C0911C`
is the full `GenericAIObjectType` string including its terminator. The canonical
provider's initializer emits zero key and a single DIR32 string relocation at
+4. The normal data gate proves compiler sizeof eight, allocation extent,
initializer bytes and relocation destination. The two changed code DIR32 sites
contain native VA `0x00DBDC84`. Before/after current-object proofs record their
full function extents, operand offsets, relocation kinds and canonical binding.
The original cache accessor, dictionary receiver and method ABI are retained.
The accessor's write is to the cache key; the string pointer is read.

The `TheKey_` spelling and StaticNameKey contract are carried from reference
source, not claimed to be original BFME 2 debug symbols. Reviewed verified
BFME 1 pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`, especially
`targets/game/reverse/identity_evidence/012a77a8-012ac510-data-identities.md`
and `inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h`:
its const StaticNameKey data owners retain a mutable key at +0 and name pointer
at +4, and consumers bind the owner's exact const decoration. That ownership
repair applies as a principle. GenericAIObjectType itself is a BFME 2 extension;
no BFME 1 address, initializer or function body is imported. Independent target
initializer and consumer byte proofs establish the BFME 2 address and behavior.

Official freshness fetch found upstream BFME 1 master at
`9c10f33bd57564b7a6829a7dd3d5656d8764b58c`. The last session's comparative
pointer update has no successful full baseline verdict: its baseline gate was
interrupted. Retain the clean verified checkout/pointer and do not write a
freshness success stamp. Comparative full verification and pointer publication
remain outstanding; the bounded checks here use the last verified inputs.

## Acceptance

Acceptance logs and before/after object proofs accompany this record.
The legacy preview's consumer linked bytes are already 403 before this repair;
its printed 149 -> 403 compares with the older census, not this change.
WorldHeightMap.cpp has independent unresolved and COMDAT/selected-provider debt.
Self-strict compiler receipts do not establish closed-strict closure or a real
link.exe/data-back placement. No maintainer-only census build, full link cycle,
nightly, boot or scheduler runner was started.

- Normal byte gate: 17/17 matched function rows, two verified data rows
  (including the new eight-byte canonical owner), two literals, zero
  baselines or skips, zero float/import refs.
- Bounded `link_check.py --prepare-current --paths-from sources.txt` accepts
  all three sources before and after with strict reusable self receipts and
  normal byte/data gates. Neither census nor status is rewritten.
- Before/after object proof: all 17 matched body digests and normalized
  relocation tuples unchanged; exactly two native DIR32 operands change only
  the bound symbol. Canonical provider is the sole cache definition in the
  checked cohort. Removing the duplicate does not alter the provider.
- Shadow data identity audit on both edited consumers: **2 -> 0 findings**
  (one duplicate-def and one wrong-name removed), zero residual findings.
- Enforced converged-data check: three sources, eight protected addresses,
  zero second names and zero unjudged rows. CSV, frozen-file, pin-consistency
  and diff checks pass.
- Local legacy link preview: **2/3 units, 403 -> 403 existing authored bytes**
  before/after; the unchanged provider has the same 55 findings in both
  previews. No incremental legacy linked-byte gain or closed-strict gain is
  claimed. The recorded improvement is eight newly owned retail data bytes,
  one removed duplicate datum and two resolved consumer data findings;
  authored C++ growth is zero.

Remaining blockers: WorldHeightMap's independent unresolved constructors,
parser/Dict/MemoryPool providers and differing COMDAT/selected bodies;
closed-strict closure and actual data-back placement are unmeasured. The BFME 1
comparative full verification/update remains pending as described above.
