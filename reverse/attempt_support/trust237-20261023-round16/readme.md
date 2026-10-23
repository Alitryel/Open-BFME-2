# 0x237D3D: exact NOP16 span has a documented patch producer

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, extent **226**.
Previous handoff: `../trust237-20261023-round15/readme.md`. Inputs:
BFME2 `0d571ab1ee`, verified BFME1 `f36a4db066aa61edeee90085a31d628eb829001d`,
unchanged RTM compiler, `/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc`.
Model GPT-6.1-sol. No game source, ledger, baseline, pin or verifier changed.

## New primary evidence: a patch at this exact address

[withmorten/bfme12x-dll, pinned revision d44d7fca7854a7c81c17f6d273c4d585ab929c50,
src/bfme2.cpp](https://github.com/withmorten/bfme12x-dll/blob/d44d7fca7854a7c81c17f6d273c4d585ab929c50/src/bfme2.cpp)
(Git blob `342ed89bd122ae89cbc0c14cf7216c3f196ad5a6`) explicitly contains:

```cpp
// disable WinVerifyTrust check, fixes random version
Nop(0x00637E0A, 6 + 2 + 6 + 2);
```

This is **RVA 0x237E0A**, parent offset **+CD**, length **16**, precisely
the entire unresolved span in our 226-byte bank. The companion
[bfme2.h](https://github.com/withmorten/bfme12x-dll/blob/d44d7fca7854a7c81c17f6d273c4d585ab929c50/src/bfme2.h)
identifies BFME2 by a DWORD at VA 0x402C39 equal to 0xB5B5AAB8; our image
passes that check. The separately pinned
[patcher.h](https://github.com/withmorten/patcher/blob/502bb3dffa54bfce9f4ae798b616099485f92911/patcher.h)
(blob `54e0e53f1e20f94c3696c2b64925e1417e2fab9b`) implements Nop by
calling SetBytes with value 0x90, which writes through memset between
memory-protection changes. This is a concrete producer of the exact NOP run,
unlike the earlier unsuccessful compiler-producer searches.

**Limit:** this DLL applies patches at runtime. Its source does not establish
which program produced our on-disk image, nor supply the overwritten bytes.
Other edits in its must_have block are absent: the launcher checks at
0x4030B0 are still calls/branches, 0x632D38 is not the B0 01 C3 stub, and
0xC19734 still contains langdata.dat. Do not attribute the complete DLL patch
set to this baseline. The strongest supported inference is that the isolated
span is a known WinVerifyTrust-disabling patch, rather than an unexplained
compiler scheduling residue. An unmodified original tail remains unverified.

## Image provenance and protected EA update

Read-only GitHub inspection found two artifacts in
[jcoester/bfme-resfix-storage](https://github.com/jcoester/bfme-resfix-storage/tree/1a8e211779ddaacb91c552f7b2fdddbec12b89a7),
pinned revision `1a8e211779ddaacb91c552f7b2fdddbec12b89a7`:

* `NoDVD/game_BFME2_noDVD.dat`, Git blob
  `2401ca1edb5447c52fddffcf7eab8b28283a33fb`, is **the entire local baseline**:
  10,969,600 bytes, SHA256
  `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
  It cannot independently verify an original tail.
* `Patches/BFME2_1.06_English.exe`, Git blob
  `70cafdff22cc731969dbe51e7e669a65b4a6dd87`, has 26,482,497 bytes, SHA256
  `14d9f7159e7f2410a9b501d0f5a71fa8039922aea2e5d3b5071e0fa7bb054867`.
  No installer was executed. A read-only RTPatch decoder recovered its
  game.dat payload, with **both embedded rolling checksums matching**.

The decoder is
[7tg/sahin launcher/tools/rtpatch.py](https://github.com/7tg/sahin/blob/511d4dab0d4884faab5d20226bdc2499cc85ca8d/launcher/tools/rtpatch.py),
revision `511d4dab0d4884faab5d20226bdc2499cc85ca8d`, blob
`3e18bc666cff814859c408506a13e0c27b10e6ae`. It stays scratch-only.
Its general container parser does not handle this installer's extra header
and kind-5 envelopes; `decode_target.py.txt` uses the identified target entry
directly and validates the installer hash, output length and both checksums.
This is not a claim to have implemented the whole BFME2 container format.

The descriptor is at file offset **0x1EC001**, compressed stream **0x1EC035**,
compressed length **11,122,513**, decoded length **12,300,200**. Checksums:
**945053055**, **884336136**. Decoded game.dat SHA256:
`52416719aef6cbbf1378165c6e4c443216d5edb69f15e47a0b6debdd3df68f2a`.

The decoded executable still has protected code. Its last sections are
stxt774/stxt371, and both entry RVA 0xADC06E and import-directory RVA
0xADC140 lie in stxt371. These satisfy the SafeDisc section/entry/import
signature in
[Detect-It-Easy](https://github.com/horsicq/Detect-It-Easy/blob/8664dc5b20ef5b4ff2e81336bbd855c46ecf1bda/db/PE/protector_SafeDisc.2.sg).
At RVA 0x237D3D it has ciphertext, not a usable original C++ check.
`image-audit.json` retains the PE layout and hashes; no executable is committed.

A bounded Unicorn 2.1.4 probe used
[pcrecomp's generic loader emulator](https://github.com/sp00nznet/pcrecomp/blob/e3c9e025a9093242487c96b47eec321792dc0928/tools/drm/emu_unpack.py)
(blob `706732487560c13b7504b8bb25e6da9ca8c5a51b`) plus small allocation
and single-process mutex shims. It stops on **GetModuleFileNameA**, called
from **VA 0xEDBB05**, before any target-byte change or transfer to original
.text. Limit: ten million instructions / ten seconds; this run stopped in
about 12 ms. No unpacked image was written. API success shims are diagnostic
assumptions, not an original-image authenticity proof. The initial unmodified
emulator stopped at GlobalAlloc; intermediate steps reached GlobalFree,
CreateMutexA and WaitForSingleObject. Final wrapper/receipt are retained.

## Separate compiler-map lead

A public, OMAP-adjusted SP1 compiler symbol map was found in
[th10-decomp](https://github.com/levzzz5154/th10-decomp/blob/beb2f081b4b55a4adc093df2daf9b2cf0a375041/matching2/reference/compiler_traces/symbols/c2_symbols.json),
blob `343cec221e583881bfbf1976809bafbd5fd4cd3c`. Local SP1 c2.dll's RSDS
GUID **5360F7BD-AFB5-4288-A53F-1FBE04D63911**, age **2**, matches that map's
PDB identity. `compiler-publics.json` records the binary hash and selected names.
This is **not** the RTM address map. Nearest preceding publics cannot establish
ownership of split cold blocks.

Bounded static inspection located IfilePatchNbytes at 0x107BB72B, with observed
direct callers in FpoEndframedata and FpoObjSetDb (debug metadata); AllocatePad
and CalculatePadSize belong to stack layout; the hotpatch functions concern
function starts; enop_pc_ui is RET. The NOP table access at 0x1075ECA7 lies in
a split encoder block, not necessarily the nearest public. These names give
better future breakpoint leads, but no new compiler execution used this map,
and none establishes a native internal NOP16 producer. Earlier matrices and
the original two-error-code controls in round5 were not rerun.

## Checks, retained bank and handoff

An independent tools/variant.py compile reproduces the existing **226-byte**
bank, raw SHA256
`ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`,
**16 differences**, exactly +CD..DC. The audit additionally checks actual IAT
names and the memset/WinVerifyTrust thunks, rather than accepting masked
operands alone. The source and score **70/86 = 0.813953** remain unchanged.
This is still a partial bank, never a byte-exact landing.

`./build.sh Code/GameEngine/Source/Common/VersionDestructor.cpp` passes:
**36/36 functions**, one data row, source claims and all 20 string references.
check_csv and diff checks pass. No authored C++ bytes are claimed.

To reproduce the image audit, fetch the pinned installer and decoder into
build/trust237-round16 (git show from pinned repositories works), copy the
retained decode wrapper there, and run it. Recompile the bank as r16_bank.cpp
with tools/variant.py, and run audit.py.txt from the repository root after
copying it to build/trust237-round16/audit.py. The optional loader probe needs
the separately fetched pinned emu_unpack.py, pefile and Unicorn 2.1.4.
All large artifacts and third-party code remain ignored in build/.

**Next concrete work:** establish the original pre-patch bytes or a verified
unmodified unpack of this exact EA update before another source/flag matrix.
The patch-source finding addresses an input-provenance explanation the earlier
sessions had not tested. Do not repeat the two-code controls, NOP encoder
emulation, or intrinsic/flag matrices unchanged. Do not edit the protected
baseline, weaken the byte gate, or add an asm/emit substitute for this span.
The claim is released after banking; the same assigned body remains unfinished.
