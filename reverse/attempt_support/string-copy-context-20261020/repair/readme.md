# Copy-helper caller-context controls

This is blocked repair evidence, not a conversion or linked-byte gain. No
production source, pin, ledger or verifier change was made by this seat.
GPT-6 Astra prepared and audited the controls; the parent Codex seat ran the
compiler diagnostics. `results.json` records **25 measured translation units
and 61 normal `explain_mismatch` checks**, with source hashes and actual results.
Three first-batch baseline copies were prepared but not compiled; they are not
included in those counts. Root and reference-seat trials are separate evidence.

The shared neutral helper
`_STL::Rva000179B0UninitializedCopy<char*,char*>` is pinned to RVA 0x179B0,
whose complete native copy worker is 41 bytes. The original four consumers
emit an incorrect 68-byte definition. A correct isolated provider is
insufficient while those definitions remain.

## Inputs and measured controls

The committed BFME1 pointer is
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`. Source content hashes, repository
head, the best candidate's compiler/header receipt and all measured summaries
are in `results.json`. Main source flags are `/Od /Ob1`; the newer range owner
uses inline depth 6 and its two wrappers use the default depth. All controls
kept the functions' algorithms and native call signatures.

| Labels | Measured TUs | Result |
| --- | ---: | --- |
| 01: canonical worker `throw()` | 3 | Exact 740/501 owner and 149/170 wrappers, including their emitted 740-byte insertion; wrong copy remains 68. |
| 02/03: force outer copy / all four copy layers | 6 | Both policies identical: copy suppressed, insertion expands to 1045; 501 remains exact, wrappers retain sizes but frames grow by 16. |
| 10–14: older sibling baseline, ordinary inline only, const-reference tags only, both, both at depth 6 | 5 | All byte/relocation identical: exact 848/511, wrong copy 68. |
| 20/21: root's optimized specialization context, default depth / depth 6, on both wrappers | 4 | Exact 740 and 41. V21 shrinks from 149 to 116 at both depths; V22 shrinks from 170 to 134 at default depth and 131 at depth 6. |
| 22/23: same specialization context on older sibling, default depth / depth 6 | 2 | **Exact 848, 511 and 41**, but new wrong helper definitions and cross-TU specialization requirements remain. |
| 24/25: extern-template suppression of forced inner layers, after / before specialization | 2 | Insertion shrinks to 737 and copy to 35; 511 remains exact. |
| 26: primary template plus explicit instantiation under optimized scope | 1 | Exact 848/511, copy grows to 102. |
| 27: same primary, optimization enabled at EOF | 1 | Exact 511/41; insertion becomes 840 with frame 0x8C rather than 0x90 and outlined distance/advance calls absent from native. |
| 28: force the four genuine distance/advance helpers inline in 27 | 1 | Exact 511/41; insertion becomes 824 and still differs. |

The older sibling's `explain_mismatch` baseline prints 1360 compiled bytes
for its 511-byte replacement because the following 848-byte insertion shares
the non-COMDAT section. Independent next-symbol bounds are 512 bytes: the
511-byte body ending RET20 plus one CC alignment byte. The audit checked
that alignment byte against native too. No 1360-byte function is claimed.

The first batch's three 68-byte copies are byte-and-relocation identical to
production, SHA256
`038f7ab27195d2771e676cdc8f12fddab747c34e92387187933fe182da8fb593`.
Outer-only and full-chain forcing emit identical 1045-byte insertions in all
three contexts, SHA256
`2996c8325a69268ffa2e6e1bcbf9d0c306df59d8fb4291ab90454e20b4938e93`.
The five older-sibling policy controls are identical for both callers and
the copy, including all relocations.

## Best candidate and blockers

`best-sibling22.patch` reconstructs the exact measured control 22 from
`Code/Libraries/Source/STLport/Rva008312E0StringReplace.cpp`. Its source base
SHA256 is checked before applying. It is a diagnostic patch, not a proposed
production edit. Its inherited prefix comments mention the newer 740/501
family; the actual sibling targets checked here are **0x284D0/848 and
0x2AE50/511**, plus the copy at **0x179B0/41**.

The candidate uses `/O2 /Ob1`, disables optimization for ordinary caller
definitions, and enables it for an explicit char-pointer specialization of
the copy dispatch. Empty tags remain empty. The leaf uses the real STLport
conditional-expression memmove operation. Force-inline declarations retain
that operation through the genuine POD dispatch chain. No added storage,
dummy statement, assembly, import substitution or new symbol binding appears.
This compiler policy is a reconstruction setting, not a claim about retail's
original build.

All three relevant emitted sections are exactly 848, 511 and 41 bytes.
The helper's sole relocation is DIR32 `__imp__memmove` at +0x1E, with zero
addend, equal to the canonical worker. The separate audit seat independently
verified every byte and relocation.

It is not landable:

- Applying the same context to the other wrappers loses their required frames;
  the parent's 501-byte replacement also has the wrong frame.
- The explicit specialization must be declared before instantiating use in
  every affected TU. Leaving the other consumers on implicit primary
  instantiations is not a valid cross-TU fix.
- The candidate emits wrong native-known helpers: `__copy_aux<char*,char*>`
  86 bytes, `__uninitialized_copy<char*,char*>` 97 bytes, and global
  `max<unsigned int>` 45 bytes. Suppressing the inner definitions also changes
  the verified caller and provider. Existing erase/replaceBase debt remains.

The next required fact is a consistent definition/optimization context that
preserves the native 501/149/170 caller frames and all 848/740 bodies while
emitting correct or no competing helper definitions. The source-supported
controls above do not establish that context. Do not repeat extern/import/
force-inline variants already rejected merely to reproduce the same mismatch.

## Replay

Preparation is deterministic and does not compile:

```sh
python3 reverse/attempt_support/string-copy-context-20261020/repair/replay.py.txt --prepare-only
```

It writes only `build/string-copy-context-replay/repair/candidate.cpp` and
asserts that its SHA256 equals the measured source. Without `--prepare-only`,
the script verifies recorded header inputs and runs normal
`tools/explain_mismatch.py` for 848/511/41 using `BFME_OBJSTORE=off`. Those
three expected matches do **not** mean the candidate links or may be admitted.
The parallel `audit/` evidence provides an independent read-only object audit.
