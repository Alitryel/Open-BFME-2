# Packed-color pure C++ follow-up, 2026-10-24

Target: Rva000ABC43ExpandColor, RVA000ABC43, whole46B cdecl body.
BFME2:2c7d0eefe5; pinned BFME1:32774ab03393709a7f14331ba8d98d281a55ffd9.
Prior exact assembly body and better scalar near-miss banks were preserved.
No production, ledger, pin, gate, or shared object-cache edit was made.

New independent hypotheses tested:

* Pinned unmodified Clang23-x86:72 isolated trials across8 source forms and
  stock optimization/tuning/selector controls. Forms include the proven scalar
  spread, byte/word unions, scalar byte updates and bitfield/bitcast views.
  Target comparison is full46 bytes and whole emitted symbol, never masked.
* Both later supported VC7.1 compilers (SP1 and DDK4035):24 isolated trials
  over6 equivalent scalar/byte/word forms under O1/O2, original G7/SSE ABI.
  This tests a backend-version explanation independently of old RTM trials.

Results:0 exact. Clang's shortest is57B, with masks/LEA and no native BH/AX
splice. SP1 and DDK's best scalar is55B, identical to one another; byte forms
start at60B and wider union forms spill. These do not improve the prior53B
scalar bank, so no partial score or replacement bank is claimed.

The concrete remaining native shape is SHL BH,3 followed by MOV AX,BX, with
EBX/EDI saves despite free caller-saved ECX/EDX. None of these ordinary
source or stock compiler contexts reproduces that full register-only shape.
The count is not evidence that all possible C++ expressions are impossible.
No false15-bit input bound, new returned register, fake live value, instruction
insertion, explicit register binding or changed calling convention was used.

All sources and objects were emitted under ignored build/seat_colorcpp_20261024
using build.compiler_command and unique outputs, never build.compile_source.
trial.py regenerates72 Clang controls; msvc_trial.py regenerates24 later-MSVC
controls. results.json and msvc_results.json retain full bytes/disassemblies.
Preferred portable semantic source is scalar_base.cpp; diagnostic alias/union
variants are not preferred source-language reconstructions.

The original mnemonic inline-assembly production body is retained exactly.
This follow-up adds zero C++ or matched-byte coverage and does not land a body.
