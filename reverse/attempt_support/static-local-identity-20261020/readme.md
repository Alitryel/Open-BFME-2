# Private MD5 helper identity false rejection

Recorded 2026-10-20. Investigation started from the
`_MD5Update` false-reject entry in `reverse/re_attempts.log` (2026-10-19).
The post-sync baseline was BFME 2 `063b128c47`, with the committed BFME 1
reference at `92f6bbe8e1dcdb46b5d27da0674313efc822b790`. No game source,
symbol pin, baseline or ledger row was changed for this verifier repair.

## Evidence and hypotheses

The GameSpy C object defines `_MD5Transform` as a STATIC function in a separate
code section. Its complete 2,268-byte body reproduces the independently rowed
WWLib owner `?MD5Transform@@YAXQAKQAE@Z` at RVA `0x00606360`
(raw file offset `0x00605960`). It already received the `retail` verdict.

`_MD5Update` has the complete 185-byte extent
`[0x00606C40, 0x00606CF9)` (raw file offset `0x00606240`).
Its REL32 operands at `+0x60` and `+0x7E` both name that exact local COFF
definition. Retail's instructions are:

| Instruction RVA | Retail bytes | Target RVA |
| --- | --- | --- |
| `0x00606C9F` | `E8 BC F6 FF FF` | `0x00606360` |
| `0x00606CBD` | `E8 9E F6 FF FF` | `0x00606360` |

The parent also matches all 185 bytes after these verified relocations.
The old `Identity.certify` nevertheless returned `unknown`: `RetailTruth`
does not resolve a cross-section STATIC function through the global ledger.
The existing recursive fold-pin receipt path was not applicable because this
private function has no fold-proof pin. This was a missing proof, not a source
or compiler mismatch.

A minimal real-COFF fixture reproduced the same result without a compiler:
an exact three-byte local helper certified as `retail`, while its exact
six-byte caller returned `unknown`. That ruled out an MD5-specific source
adaptation. The repair adds a scoped certificate for this call relationship.

## Proof limits

Only a decoded five-byte direct `E8`/`E9` instruction with a zero REL32 addend
can use the new proof. The referent must be the unique actual STATIC function
definition in another code section of the same object. A repeated local name,
section symbol, data reference or instruction-looking byte inside an immediate
does not qualify.

The target must have an independent ledger or Ghidra start and positive extent,
must lie in retail `.text`, and must not be inside another row. The callee must
match the entire extent, including every relocation, through the existing
`RetailTruth._judge`. Its bytes must fit the declared COFF section and file;
same-section references outside the callee's own body cannot establish another
unjudged helper. Nonpadding tails, overlapping/crossed/trailing relocations and
missing boundaries fail closed.

The callee proof is one level only. It does not recursively infer static calls,
so unknown deeper chains and cycles remain unknown. Every qualifying call to
one local symbol within a caller must agree on its target. The synthetic binding
exists only while judging that caller and never enters the shared ledger.
This certifies per-caller code equivalence; it does not establish one global
placement across different parent callers. Placement conflicts across parents
remain the linker's responsibility.

`_MD5Final` remains `unknown`: its DIR32 operand at `+0x52` references private
static data `_PADDING` at RVA `0x009D5158`. This separate prerequisite is not
relaxed by the code-helper repair.

## Reproduction and validation

First produce current objects using the supported build entry point:

```powershell
& 'C:\Program Files\Git\bin\bash.exe' ./build.sh Code/GameEngine/Source/GameNetwork/GameSpy/md5c.c Code/Libraries/Source/WWVegas/WWLib/md5.cpp
python3 reverse/attempt_support/static-local-identity-20261020/reproduce.py --expect-fixed
```

The source-unit baseline passed 10/10 rows, one string reference and one import.
The reproduction reads only the two relevant sources' ledger rows and current
objects; it invokes no compiler or linker.

| Symbol | RVA | Size | Before | After |
| --- | --- | ---: | --- | --- |
| `_MD5Transform` | `0x00606360` | 2268 | retail | retail |
| `_MD5Update` | `0x00606C40` | 185 | unknown | retail |
| `_MD5Final` | `0x00606D00` | 174 | unknown | unknown |
| `_MD5Digest` | `0x00606DB0` | 105 | retail | retail |

Run the identity tests and every gate-exploit case:

```powershell
python3 -c "import pathlib,tempfile,pytest; tempfile.tempdir=str(pathlib.Path('build').resolve()); raise SystemExit(pytest.main(['-q','-s','--tb=short','--basetemp=build/pytest-static-local-20261020','tools/tests/test_code_identity.py','tools/tests/test_gate_exploits.py']))"
```

Result: 83 passed, one empty audit-fixture parametrization skipped. The 34 new
COFF cases include matching direct calls/tail jumps, nonzero symbol offsets,
padding, verified external child calls, wrong parent/child bytes, wrong or
unknown child calls, deeper static chains, cycles, positive/negative addends,
conflicting call sites, duplicate local names, opcode spoofing, nonfunction and
noncode symbols, external or missing definitions, invalid symbol indices,
missing/interior/out-of-image boundaries, empty/wrong extents, section overruns,
same-section unjudged grandchildren, and overlapping/crossing/trailing
relocations. One further test checks missing-body refusal. Existing
local-data receipt and exploit tests retain their rejection behavior.

An independent real-COFF audit also passed: a valid direct call certifies;
a relocation selecting a bad second duplicate local name and an `E8` byte
inside a `MOV` immediate both remain unknown. Two additional falsification
cases exposed and then confirmed rejection of conflicting overlapping external
relocations and a child body spilling beyond its declared COFF section.
No private binary bytes beyond the two diagnostic call instructions are stored
in this handoff.
