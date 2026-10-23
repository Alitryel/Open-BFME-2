# 0x237D3D: wide values, cleanup lifetimes and alignment controls

Continuation of `../trust237-20261022-round2/readme.md`, confined to
`?Rva00237D3DCheck@@YAHXZ`, RVA `0x237D3D`, extent 226. BFME2 input
`a790037b2f141f00314ade0cb9c85ad2464bfeea`; BFME1 verified pointer
`37c3022de1ab944c7ffe536440d637dc8199091c`; MSVC 7.1 RTM through Wine.
Model: GPT-6.1-sol. No Code source, ledger row, pin or compiler binary changed.

## Retained bank and remaining mismatch

Keep `reverse/attempts/0x00237d3d.cpp`, score 69/86 = 0.802326. An independent
`tools/variant.py` compile reproduced 219 bytes, 21 diagnostic positional
differences, first at +0xCD. Its raw body hash remains
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
The matching prefix includes the formerly missing status save and xor.
Retail still has sixteen consecutive 0x90 bytes at +0xCD..+0xDC, followed
by `inc eax; pop esi; pop ebx; leave; ret`. The bank has a live byte-range
comparison and different return-tail scheduling. It is not an exact match.

`w1920.cpp.txt` is a regional alternative: a 64-bit cast of an unsigned byte
compared with 255 emits 216 bytes and ties the bank's prefix, difference
count, mnemonic alignment and two structural regions. Its tail uses
`or al,0xff; cmp al,bl` after the matching xor. It does not improve the bank.
RAII variants independently reproduced both this body and the current bank.

All target scores use diagnostic DIR32 masking from retail, with REL32 maps
memset=0x6291AE and WinVerifyTrust=0x655652. A shifted or new data relocation
can be masked incorrectly; these scores are not relocation proof or byte
admission. Floating-point variants are shape diagnostics only: they can
affect floating-point status and introduce literal relocations. Do not land
one on the strength of its masked score. No admission gate passed here.

## New hypotheses tested; do not repeat unchanged

Before generating variants, read the per-RVA history, both October 22
handoffs and the relevant recipes. Earlier evidence already rejected SDK
48-byte layout substitution, ordinary compiler flag changes, numerous
status/cleanup/control-flow forms and simple Boolean/range families.
This round tested wider lowering and destructor lifetimes in combination,
then investigated actual compiler alignment instructions as a positive
control for the unexplained padding.

| Family | Successful compiles | Distinct raw bodies | Choices |
| --- | ---: | ---: | --- |
| wide | 3072 | 272 | 24 unsigned 64-bit identities, eight return/control shapes, conversion before/after LocalFree, G6/G7, direct/forceinline, flat/nested scope |
| float | 1728 | 316 | 12 finite-range predicates, four return shapes, float/double/long double, conversion timing, G6/G7, SSE/Op/IA32 |
| raii | 1152 | 45 | six identities, four return shapes, three owner lifetimes, G6/G7, ordinary/forceinline destructor, throw()/unspecified, void*/typed member |
| align_targets | 96 | 31 | 12 regional inputs, G6/G7, O1/O2, default/bzalign |

All 6,048 target compiles succeeded, yielding 644 distinct raw bodies across
families. None contains a NOP instruction, and none improves the retained
bank. The 48 paired target compilations with/without `/d2bzalign` emitted
identical raw bodies. These finite matrices do not prove that a C++ source
or another compiler mechanism cannot produce the retail tail.

RAII cleanup retains exactly one LocalFree on normal return. Its lifetime
variants either reproduce existing bodies or move the predicate evaluation
before cleanup and lose the retail status/return ordering. They did not
expose an EH or late-cleanup path that emits the padding.

## Compiler alignment evidence

`padding.py.txt` compiled 768 controls: six independently selected integer
prefix operations, G5/G6/G7, O1/O2 and default/bzalign. All succeeded, with
216 distinct raw bodies. All 384 bzalign pairs are identical. Eighteen
compilations contain a single-byte NOP; every NOP ends at a 16-byte boundary,
and no run exceeds one byte.

The same controls show other padding before a backedge's loop head.
`analyze_padding.py.txt` recognizes contiguous identity instructions
immediately before that head. Across the three CPU settings it found 18
recipes, all under O2, of lengths 1, 2, 3, 4, 6 and 7 bytes:
`90`, `8bff`, `8d4900`, `8d642400`, `8d9b00000000`, and
`8da42400000000`. These are nop, register self-move or self-address lea.
This is observed coverage, not an exhaustive enumeration of possible pads.

`pad0046.cpp.txt` independently recompiles to the same 48-byte raw body
(`847f9d3b4cd00647f20ed85c2abc6213921da3bdbf103f5a1254becd94442088`).
Its compiler listing, `pad0046.asm.txt`, explicitly says `npad 7` before
the loop at +0x20; the object encodes `lea esp,[esp+0]`, not seven NOPs.
The listing is compiler output, not an assembly source or conversion.

The c2.dll option string `-bzalign` suggested `/d2bzalign`. It is accepted
but changed neither the controls nor the target inputs. Numeric suffixes
1, 2, 4, 8, 16, 32 and 64 are rejected with C1007; those seven setup errors
are excluded from successful counts. `alignment_flags.json` preserves the
two successful control probes and seven errors. The prior finding that the
retail NOP successor has address mod 16 = 10 remains unexplained. Ordinary
loop alignment is weakened as an explanation, not disproven universally.

## Reproduce or continue

Do not rerun these matrices without a new finding. Drivers and compact
results are retained to avoid that repetition. To reproduce a particular
case, restore `search.py.txt` and its companion drivers as `.py` in
`build/trust237-round3/`, and copy `base.cpp.txt` there as `base.cpp`.
Run from the repository root. `late.py wide`, `late.py float`, `raii.py`,
`padding.py`, `alignment_flags.py`, and `align_targets.py` name the families.
The saved alignment driver reads its twelve tracked `inputNN.cpp.txt`
parents directly, so it does not require the earlier scratch matrices.
Every compile has its own object; no shared match-cache entry is written.
`summary.json`, `grouped.tsv`, `padding_recipes.json` and the saved listing
retain the useful measurements without thousands of redundant objects.

Next work remains this same body. A useful new hypothesis must explain why
the dead status save survives, why the zero-result setup precedes sixteen
single-byte NOPs, and why the restore follows increment. Distinguish
compiler padding/late optimization from any independently evidenced image
transformation; current experiments establish neither an original source
shape nor permission for an escape hatch. Preserve the best bank.

The ledger check passed before work. BFME1 freshness update was skipped
under another seat's live `claudec2` update lock; the committed and checked-out
verified pointer agree. Preserve unrelated untracked `reverse/zh_sweep/`.
