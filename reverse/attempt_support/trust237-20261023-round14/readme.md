# 0x237D3D: all differences confined to NOP16

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, extent **226**.
Previous handoff: `../trust237-20261023-round13/readme.md`. Session inputs:
BFME2 `2b4135789a`, committed/checked-out BFME1 `42bba2ddbd5c`, unchanged RTM
compiler and flags `/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc` for the new bank.
Model GPT-6.1-sol. No game source, ledger, pins, compiler or verifier changed.

Read the scoped pick-hard history before these trials. Earlier padding-encoder,
barrier, loop, atomic, return-carrier, cleanup, lifetime, layout, visibility and
compiler matrices remain finite negative results. In particular, round13's
regional k0166 had retail's prefix and return order but was one byte long;
simply preserving a constant mask's type did not shorten it. These trials do
not repeat those constant-bound matrices.

## New source-shape hypothesis and results

Use a status-dependent bound in a tautological mask/range test, then vary its
type together with duplicated cleanup. This changes both the short accumulator
encoding and zeroing lifetime. It is a compiler-shape experiment, not recovered
source identity. Target evidence continues to establish the API sequence, GUID,
file16/data44 fields and constant return; no new donor or layout claim is made.

| Family | Finite choices | Compiles | Distinct raw bodies |
| --- | --- | ---: | ---: |
| bounds | Eight dynamic bounds; four equality values; four direct/local/ref/helper forms; if/goto cleanup; G6/G7 | 512 | 77 |
| zero_lifetime | Twelve result updates; four predicates; four arm/label layouts; G6/G7 | 384 | 24 |
| narrow_dynamic | Three unsigned mask widths crossed with three bound widths; four value/ref/direct/helper forms; OR/XOR bound; two arm layouts; G6/G7 | 288 | 96 |

All **1,184** compile successfully, producing **184 distinct raw bodies** and
no decoded NOP. The wide dynamic-bound family first produced 226 bytes with
18 differences: retail's return position was correct, but zeroing sank into a
branch. Twelve updates including addition, OR, conditional increment and goto
failed to bring it back. Narrowing both operands of the dynamic OR-bound test
under G6 then restored the initial XOR and kept the short AL encoding.

**New bank d0016:** **226 bytes**, prefix **205**, **16 differing bytes**, all
at **+CD..+DC**, exactly retail's NOP16 span. The old bank was 219 bytes and
had 21 differences. New mnemonic score **70/86 = 0.813953** (old 69/86).
Raw body SHA256:
`ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`.

The residue is now exclusively:

```
       retail                         bank d0016
+CD    90 * 16                        cmp ebx,2 / jne +D5 / inc eax
                                      jmp +DE / mov al,bl / or al,1
                                      cmp al,bl / sbb eax,eax
+DD    inc eax                        inc eax
+DE    pop esi / pop ebx / leave / ret (identical at identical offsets)
```

`alternate-d0018.cpp.txt` is another 226-byte body differing only in that same
span, with the condition's arm order reversed. Both remain partial C++, not
byte-exact recoveries. No NOP producer has been established. There is no basis
to replace this residue with an asm/emit escape hatch or to claim the input was
patched. Preserve these region winners; do not repeat the matrices unchanged.

## Checks and separate compiler prerequisite

`audit.py.txt` independently rereads all 1,184 objects, disassembles each fully,
and verifies hashes, relocations, lengths, scores and differing positions.
An independent `tools/variant.py` compile of d0016 reproduces its raw body and
relocations and reports **226B / 16 differences / first +CD**. The diagnostic
resolver fills DIR32 operands from retail; the audit additionally checks each
such operand against the actual target import name and checks both REL32
callees through their target import thunks (memset and WinVerifyTrust). These
are diagnostic receipts, not a full-byte gate landing.

`emulate.py.txt` relocates APIs by symbol to independent hooks, rather than
borrowing target call operands. The matrices, previous bank and independent
selected object form **185 code/relocation groups**. All **122,840 runs pass**
(166 statuses times four LocalFree-return/argc combinations per group):
return=1, stack balance, callee-saved registers, caller-saved clobbers, API
counts/order, GUID and file/data fields. These finite checks are not identity
or byte-match proof. audit.json and summary.json retain checked counts, hashes,
selected relocations/bytes, group digest and matrix/script digests.

A separate, previously untested producer possibility is profile-guided code
generation. RTM link.exe advertises `/LTCG:PGINSTRUMENT` / `PGOPTIMIZE`; that is
not evidence its code generator produces this NOP span. `pgo.py.txt` uses the
complete, hash-checked SP1 and DDK4035 profiles already used successfully for
ordinary LTCG in round5. Baseline and wide-dynamic bodies compile with `/GL`
for both profiles. All **four** instrumentation links fail with **C1350:
error loading dll 'pogodb71.dll': dll not found**, then LNK1257. No matching
DLL is present in the local profile/toolchain files. This is a setup blocker,
not evidence against PGO source shapes; no instrumented body or optimization
run was produced. RTM ordinary LTCG's previously known missing msobj71.dll
was not retried. pgo.json preserves full commands, errors and tool hashes.

## Resume and session state

Restore the six saved scripts without `.txt` to `build/trust237-round14` and
round9's `frontends.py.txt` to `build/trust237-round9/frontends.py`; generators
use round5's tracked base.cpp.txt. Run each generator once, with its existing
eight-worker isolated objects/PDBs. Do not use build.compile_source for scratch
trials. Independently reproduce the selected object with:

```
python3 tools/variant.py build/trust237-round14/d0016.cpp \
  '=?Rva00237D3DCheck@@YAHXZ' 0x237D3D 226 \
  _memset=0x6291ae _WinVerifyTrust@12=0x655652
```

For audit/emulation, also reproduce the previous 219-byte bank from the parent
commit under build/scratch/0x00237d3d.obj; its raw hash is recorded in audit.json.
The emulator uses round4's scratch Unicorn install. Inspect new evidence for
the NOP producer or complete PGO prerequisites before rerunning old matrices.
No missing game callee has been identified. The concrete unfinished task is
now the **16-byte internal NOP span**, with size and all other bytes resolved
in the diagnostic comparison.

check_csv passes. BFME1 freshness update is skipped under the recent shared
lock owned by codexb, per runner instructions; no success stamp was written.
No unchanged linking repair is claimed: the preceding session's link checks
already established VersionDestructor links 1,275 bytes and VersionInitGlobals
has 200 bytes withheld by this check. Claim released after banking. Preserve
unrelated untracked reverse/zh_sweep/. Outcome: in_progress on this same body.
