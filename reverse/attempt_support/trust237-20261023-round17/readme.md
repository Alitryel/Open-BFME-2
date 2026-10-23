# 0x237D3D: independently recovered comparisons under the NOP16 patch

Assignment: `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, **226 bytes**.
Continue from `../trust237-20261023-round16/readme.md`; do not repeat its
unchanged compiler/padding matrices. BFME2 base `a8bde66544`, verified BFME1
`f36a4db066aa61edeee90085a31d628eb829001d`, MSVC 7.1 RTM,
`/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc`, model GPT-6.1-sol.

## New evidence and its limits

Read-only inspection of
[ValheruGR/BFME2 at b19965c2abdb65d29cd0d7a07b60e9933e7555d9](https://github.com/ValheruGR/BFME2/tree/b19965c2abdb65d29cd0d7a07b60e9933e7555d9/1.06)
found two independent artifacts, retrieved with `git show`, never executed:

| Path | Bytes | Git blob | SHA256 |
| --- | ---: | --- | --- |
| `1.06/game(cracked).dat` | 10969600 | `11d988d5f00ecc8c8e8f2915fea886c95bbda1d9` | `1aa5dca6595820e508df31352275e533cce93dd3be7b0ed7528530413ce99c5d` |
| `1.06/game.dat` | 12300200 | `405bfba809295e23546826c718d9fbe5f66fb409` | `52416719aef6cbbf1378165c6e4c443216d5edb69f15e47a0b6debdd3df68f2a` |

The protected companion equals **every byte** of round16's checksum-validated
EA 1.06 update payload. The cracked artifact differs from our entire baseline
(SHA256 `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`)
in **exactly 26 bytes in two runs**:

* File offset `0x359`, ten bytes: baseline zeroes, independent `*DEV!ANCE*`.
* File offset `0x23740A`, sixteen bytes, RVA **0x237E0A**, parent **+CD..DC**:
  baseline `90909090909090909090909090909090`, independent
  `81fb10600980740981fb00010b807401`.

Every other byte of the files agrees. In particular the surrounding original
status save, cleanup, zero and increment instructions agree. The independent
tail is:

```text
+C3  mov ebx,eax
+C5  call [LocalFree]
+CB  xor eax,eax
+CD  cmp ebx,80096010h
+D3  je +DE
+D5  cmp ebx,800B0100h
+DB  je +DE
+DD  inc eax
+DE  pop esi
+DF  pop ebx
+E0  leave
+E1  ret
```

This explains both the retained status save and the NOP span. Together with
round16's primary patch source, it supports a deliberate removal of these two
comparisons. It does **not** identify who patched our on-disk baseline. The
independent executable is a community cracked artifact, not an official
unprotected EA signature. Keep those provenance limits explicit.

The independent check returns zero for `0x80096010` and `0x800B0100`; the
canonical NOP baseline returns one for both. Recovering this original source
shape alone therefore cannot pass the current baseline gate.

## New trials; unchanged best eligible bank

Previous history already exhausted repeated padding/alignment encoders,
always-one expression families, declaration/lifetime permutations, callee
visibility and compiler settings without explaining NOP16. The new hypothesis
was **input provenance**, followed by source controls using the independently
recovered comparison order, rather than guessing that order again.

`original_check.py.txt` generated 32 combinations of eight return forms,
direct/forceinline cleanup and signed/unsigned status. `original_flow.py.txt`
generated 128 combinations of eight cleanup/control-flow arrangements, four
result types, G6/G7 and the cleanup declaration's throw specification. Every
compile succeeded. No control matched even the independent unpatched body:
best 230 B, prefix 203, 26 differing bytes; the flow family's best was 231 B,
prefix 194, 36 differences. These are **diagnostic controls that may return
zero**, never replacements for the always-one bank. Source shape and original
compiler settings are not established by these negative results.

The retained scoring resolves imports to their actual IAT addresses even when
their offsets move, and resolves both direct calls by their established thunk
identities. It does not copy arbitrary comparison bytes into shifted import
relocations. Objects are isolated under `build/trust237-round17/`; the shared
match cache was not used for these trials.

Fresh `tools/variant.py` compilation of the existing bank still emits **226 B**,
raw SHA256 `ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`,
prefix **205**, exactly **16 differences at +CD..DC**, score **70/86 =
0.813953**. Keep that bank unchanged. It is a partial, not a landing.

`audit.py.txt` independently checks complete file hashes and Git blob IDs, all
26 differing positions, the recovered disassembly, actual bank imports and
callee thunks, and every compiled control's source/object hashes and score.
It also executes the baseline, independent body and freshly resolved bank:
142 status values (including both exact errors and adjacent values), four
argc/cleanup-return combinations, **1704 executions**. API arguments/layouts,
call order/count, result, stack and callee-saved registers all pass; caller
volatile registers/flags are clobbered by the API shims. The independent body
alone returns zero for those two errors. See `evidence.json`.

## Protected-loader continuation, before the independent artifact was found

The bounded round16 Unicorn probe gained an explicit in-memory filesystem,
self-image reads and temporary-file writes, PID and module/temp paths. It
extracts a 72192 B child, 57344 B PFD and 744988 B DLL, then stops at the
unhandled `CreateProcessA` from VA **0xEDAEB9**. No child/driver executes, no
unknown API is silently accepted, no unpacked image is claimed, and the target
remains encrypted and unchanged. `loader-summary.json` retains hashes and the
last calls; `probe.py.txt` retains the wrapper, using round16's pinned external
emulator. Do not bank the encrypted target or commit extracted binaries.

## Acceptance checks and reproduction

* `python3 tools/check_csv.py`: passes (98094 functions, 15852 symbols,
  2139 data rows at this input revision).
* `./build.sh Code/GameEngine/Source/Common/VersionDestructor.cpp`: **36/36**,
  one data row, all 20 string references and source claims pass.
* `python3 tools/link_check.py Code/GameEngine/Source/Common/VersionDestructor.cpp`:
  **LINKS**, 1275 matched bytes, published census `0fa62a2841`.
* The corresponding check of `VersionInitGlobals.cpp` reports its 200 B held
  out by unresolved `?Rva00237D3DCheck@@YAHXZ`. The standing assignment's
  older claim that VersionDestructor itself cannot link is stale. This is a
  predictor result, not a newly run link cycle or a new link repair.
* Syntax, evidence JSON, audit and `git diff --check` pass.

To reproduce: retrieve both pinned Git blobs into ignored
`build/trust237-round17/community-106-{cracked,game}.dat`; retain round16's
verified `game-patch.dat`. Copy the retained Python text files there without
`.txt`. Copy the existing bank to `r17_bank.cpp`, then run:

```sh
python3 tools/variant.py build/trust237-round17/r17_bank.cpp Rva00237D3DCheck 0x237D3D 226 _memset=0x6291AE _WinVerifyTrust@12=0x655652
python3 build/trust237-round17/original_check.py
python3 build/trust237-round17/original_flow.py
python3 build/trust237-round17/audit.py
```

The audit uses pefile, Capstone and Unicorn. All large artifacts, third-party
emulator source and objects remain ignored in `build/`.

**Remaining task:** the original comparisons are now recovered; do not repeat
their provenance search or unchanged source matrices. The outstanding legal
C++ reconstruction still has to reproduce the canonical patched NOP16 while
returning one. Alternatively, an upstream decision about representing proven
binary patches is a prerequisite outside this seat's authorization. No
baseline/verifier edits, asm/emit padding, or a zero-returning substitution are
authorized by this evidence. No C++ bytes or exact landing are claimed. The
best bank is preserved and the claim is released after recording this round.
