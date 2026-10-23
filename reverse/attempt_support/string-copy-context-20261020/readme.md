# Shared string-copy link debt: blocked context repair

No production repair is accepted by this investigation. No source, ledger row,
pin, gate or baseline was changed. Existing production passed **26/26** byte
checks across the four consumers and canonical provider at the end of the
investigation. New recovered bytes and newly linked bytes are both **zero**.

Inputs: BFME2 `cbf7608fb05a1180b2e2c7fa19a5a523e1f95d7c`;
BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`. Production source SHA256s
are in `production-inputs.json`. Three GPT-6 Astra investigation seats covered
donor context, compiler experiments and independent byte/provider audits;
the lead coordinated claims, ran the normal compiler diagnostics and checked
additional compiler-state hypotheses. No census, link cycle or publisher ran.

Before publication, rebasing brought in BFME1 pointer
`4483e88da1c2f3b9a273f779baac7458bd8bb891`. The donor diff from `92f6bbe8`
does not change the reviewed STLport sources or headers. None of the five
BFME2 production sources or verifier tools changed in that incoming range.
The receipts above intentionally retain the revisions actually investigated.

## Observed format and behavior

This is x86 PE/COFF recovery, not an encrypted payload. The relevant native
body is `[0x179B0,0x179D9)`, 41 bytes, file offset `0x16FB0`. It implements
STLport's trivial pointer-range copy: return the destination for an empty
range; otherwise `memmove(destination, first, last-first)` and return the
result plus the byte count. It supports overlap. The semantic source is
STLport `_algobase.h`; the retail instruction and import evidence independently
establish the pointer subtraction, empty-range path, copy and returned end.

```text
8b442404 56 8b74240c 3bf0 7506 8b442410 5e c3
2bf0 56 50 8b442418 50 ff1588a6bb00 83c40c 03c6 5e c3
```

The sole COFF fixup is DIR32 at `+0x1E`, `__imp__memmove`, zero addend.
Native resolves it to VA `0x00BBA688`. Resolved native SHA256:
`952c777620edc9bdfcb28614aa77f7ddfa5bcc7fe7cc0cc0a0e7aaf845ce819a`.
The zero-addend COFF SHA differs, correctly:
`07d84357dc85cbcdfcfccbb4e7b9f4c6e342b9f26802457e6d29523d941653a4`.

All four current consumers instead emit the identical 68-byte legacy
`Rva000179B0UninitializedCopy<char*,char*>`, with REL32 `+0x39` to the canonical
copy body. Its pin explains a call destination; it does not certify those
68 bytes. Installing another provider alone cannot repair these definitions.

## Positive results and why they cannot land

| Candidate | Complete byte/relocation matches | Remaining contradiction |
| --- | --- | --- |
| `exact-copy-Od-depth6.cpp.txt` | 740-byte insertion and 41-byte copy | 501-byte replacement frame `0xFC`, native `0x118`; specialization must be visible in every using TU |
| `primary-timing-in-class.cpp.txt` | Same 740 and 41 bytes; no explicit specialization | Same replacement-frame mismatch; extra emitted `__uninitialized_copy` is 41 bytes but wrong for its existing folded address |
| `repair/best-sibling22.patch` | Older 848-byte insertion, 511-byte replacement, 41-byte copy | Isolated specialization is not valid across all four TUs; additional wrong helper providers |

For the 740 insertion the four mutable-copy operand fields are
`+0x7E/+0x15D/+0x23B/+0x26C`; the two direct-copy fields are `+0x131/+0x252`.
All six native destinations are `0x179B0`. The 848 insertion's mutable fields
are `+0x96/+0x161/+0x196/+0x28C/+0x2A3/+0x2C0`.
Independent receipts account for every relocation and all function bytes.
In baseline COFF, the 511-byte sibling replacement precedes one CC alignment
byte and the 848-byte insertion; the diagnostic's 1360-byte section is not
the replacement's extent. This describes object layout, not native address order.

## Hypothesis log

| Explanation tested | Evidence/result |
| --- | --- |
| Missing genuine donor/trait context | Actual vendored `_uninitialized.h` preserves the parents and reproduces the same wrong 68-byte copy. No complete BFME1 linking repair exists at the reviewed pointer. |
| Nothrow or ordinary/forced dispatch declarations | Nothrow is inert. Forcing the copy chain expands insertion to 1045 bytes. Older sibling tag/reference and depth controls preserve 848/511 but retain 68. |
| Template definition versus instantiation optimization timing | A scoped optimized primary still emits 68 or 102 when deferred under the caller policy. EOF optimization can emit 41 but changes caller expansion. |
| Explicit specialization with complete forced inner dispatch | Produces exact 41 with exact 740, or exact 848/511, but the other callers fail. V21 becomes 116 versus 149; V22 becomes 131 at depth6 (134 at default depth) versus 170. |
| Suppress the new inner copies | Early/late extern-template controls shrink the older insertion to 737 and copy to 35; not a repair. |
| Correct the actual outlined iterator operations under EOF optimization | Restores the newer insertion to exact 740, still wrong 501. Older insertion becomes 824 versus 848; 511 and 41 remain exact. |
| Restore member inline visibility, including in-class placement | Preserves 740/41 but leaves the 501 frame at FC. `/Ob1` versus `/Ob2` does not resolve it. |
| Add an empty tag constructor | Diagnostic only: 929-byte insertion; conflicts with the canonical aggregate's definition. Rejected, not proposed production code. |

`root-controls.json` records 33 actual root source controls / 99 diagnostic
checks, including failed symbol checks. The other seats' separate results are
under `repair/` and `reference/`; their counts must not be added to the root
counts without accounting for reused candidates. Exit zero from
`explain_mismatch.py` does not mean byte equality: its classification and full
object audit decide. A result-summary filename exceeded Windows' path limit
in one run; individual source/log results survived and were packaged directly.

## Reproduce and resume

From the repository root, with the normal supported VC7.1 environment:

```powershell
python3 reverse/attempt_support/string-copy-context-20261020/replay.py primary
python3 reverse/attempt_support/string-copy-context-20261020/replay.py specialization
```

These commands materialize diagnostic `.cpp` files only under `build/` and use
the normal `explain_mismatch.py` CLI. Neither writes Code or ledgers. The
replacement mismatch is expected. `replay_root_controls.py` regenerates the
broader root controls against the recorded production inputs; use the recorded
revision when replaying after those sources change. Read `audit/` for the
independent full-body/relocation and provider checks.

The precise blocker is **one consistent compiler/source context that emits the
retail copy provider while preserving all 848/511/740/501/149/170-byte callers
and introducing no wrong named copies**. The strongest next evidence would be
the original caller-TU optimization/inline configuration or a source/object
pair demonstrating those nested inline decisions. No additional runtime input
sample is needed to establish the copy operation. Existing erase/replaceBase
debt is separate and would remain even after this helper is fixed.

Confidence is high in the native copy semantics, boundaries, imports and
positive byte receipts. The original source spelling and original build policy
remain uncertain. The new contexts are experiments, not proof of that policy.
