# DXErr9 August 2005 lookup recovery

The four lookup functions are reconstructed as ordinary C++ switches. This
replaces prebuilt library coverage with compilable C++; it does not establish
new game-class identities or layouts.

## Inputs and identity

The existing tracked `vendor/dxerr9-aug2005/dxerr9.lib` is DirectX 9.0c SDK
(August 2005), dated 2005-07-22. Its existing `PROVENANCE.txt` documents SDK
selection, archive order, full COMDAT placement, internal calls and A/W string
width evidence. SHA256:

`81204fd2c9e1be4abc63772e694f9d4c82b057611b4b64e81c2c58910fdcbe0a`

Member `obj\i386\dxerr9.obj` is 2,871,773 bytes, SHA256:

`071e8dd0a617831f2b15c675a45de1464fa9839b53fbc55fdff22c2e4234b9dc`

The member's real symbols, complete code sections and retail placement establish
each function's identity, stdcall ABI and extent. These are library identities,
not names inferred from a byte-pattern resemblance. Its S_COMPILE2 record gives
frontend/backend 13.10.4035 and machine 6. The explicit authenticated
`vc71-ddk-4035` profile, `/O1 /G6 /MT /DNDEBUG /hotpatch /Oy- /GS`, reproduces
these lookup bodies. Compiler provenance is recorded separately under
`vendor/vc71-ddk-4035/`.

Microsoft DXUT commit `2c3ad3ceaf99a7aaff5278dabc2cc952c727d8c1`,
`Core/dxerr.cpp`, supplies the readable semantic guide: switch on HRESULT,
group aliases, return a name or description. Its MIT license is preserved as
`Code/Libraries/Source/DirectX/license.dxut.txt`. No modern case table was
assumed identical: all emitted case values, literals and source ordering below
were independently established from the original object and target execution.

## Recovery evidence

| Symbol | Retail RVA | Full bytes | Enumerated inputs | Nondefault cases | Original source groups | COFF line entries |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `_DXGetErrorString9A@4` | `0x0062B16A` | 72,878 | 8,434 | 5,467 | 3,688 | 3,920 |
| `_DXGetErrorString9W@4` | `0x0063CE18` | 72,450 | 8,138 | 5,449 | 3,679 | 3,915 |
| `_DXGetErrorDescription9A@4` | `0x0064E91A` | 11,497 | 868 | 656 | 625 | 704 |
| `_DXGetErrorDescription9W@4` | `0x00651603` | 11,497 | 868 | 656 | 625 | 704 |

Total: **168,322 retail bytes**. Names default to `"Unknown"`; descriptions
default to `"n/a"`. A and W were recovered independently; their name tables
are different. No assumption of A/W case parity was made.

The read-only traversal follows instructions reachable from each real function
entry. It tracks an affine HRESULT value through register copies and integer
arithmetic, takes both direct conditional edges, records equality roots, and
enumerates every proven bounded index domain before an indirect jump or table
load. It includes coalesced unsigned ranges. It stops at table data rather than
disassembling it as code. All four traversals finished with zero unsupported
operations, unknown loads, unbounded indirect edges or paths outside the extent.

Every enumerated input was run against the mapped retail PE in Unicorn. Each
execution had to reach the return sentinel within the instruction limit and
return an in-image pointer. ANSI strings were read to their byte terminator;
wide strings to an aligned UTF-16 terminator. The execution also recorded the
actual immediate-pointer return instruction offset for each nondefault case.

The original object retains legacy COFF line-number tables on its four function
sections, even though its minimal CodeView records have no C13 source-line
subsections. For each function, read PointerToLinenumbers and
NumberOfLinenumbers from that function's COFF section header; records are
`DWORD offset; WORD relative_source_line`. The zero-line symbol record and
32767 hotpatch marker are not source cases. Every observed pointer-return
instruction has an **exact** entry in this table; no line interpolation was
needed. Cases sharing an original line and literal form a source group; emit
groups in increasing original line order. Source comments retain those original
relative line numbers alongside the actual cases and literals.

This ordering is necessary evidence. Sorting numerically gave the same semantics
but a different shared-tail instruction and return-block order. Simply grouping
identical descriptions retained the wrong numeric-first-appearance group order. Preliminary
`explain_mismatch.py` comparisons masked the relocation sites and therefore
could report an exact match while the full gate correctly refused jump-table
targets and literal locations. The COFF-line reconstruction fixes the source
ordering instead of masking those differences or changing verification.

## Verification

The final scratch objects independently passed the existing byte comparison,
`body_extent_problems` with zero extent/jump-table findings, and
`verify_string_refs` with **8,621 literal references**, zero baselined,
unverified or skipped references. These read-only checks are additional evidence;
the production source and ledger replacements still use ordinary `add_match`,
`build.sh`, commit hooks and push hooks. No gate code or baseline was changed for
these reconstructions, and no new pins, assembly, emitted bytes or hard-coded
global addresses are needed.
