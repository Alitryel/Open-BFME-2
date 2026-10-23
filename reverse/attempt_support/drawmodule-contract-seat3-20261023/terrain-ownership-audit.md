# Terrain-track ownership prerequisite audit — Seat3, 2026-10-23

Evidence only; migration BLOCKED. No source/header/ledger/pin/claim edits,
compiler, runtime mapping, wrapper change, or coverage/linking gain.
Owner: sol-team-vp6-20261023. Research HEAD 1da70e112222372e65fedf007fa0f20734c1f6d2;
origin snapshot 778d2ec547baf74d65638c4bf144182af2a5631e.
Donor remains 138757e9b74645fbcbb7724a7af2764e34931e11, untouched.
Retail input and SHA256 are the same as adjacent provenance.json.
Method: filesystem/git inspection; Capstone x86-32 from known whole-body
boundaries; raw E8 rel32 candidate scan and literal-address scan of initialized
PE sections. No new trial of the prior 505-versus-507 destructor mismatch.

## Caller and manager identity: target facts

83CD7/18 ignores ECX and performs exactly:

```text
00083CD7 8b442404       mov eax,[esp+4]
00083CDB 83603800       and dword ptr [eax+38],0
00083CDF c6801113000000 mov byte ptr [eax+1311],0
00083CE6 c20400         ret 4
```

The executable .text E8 scan finds one candidate, validated inside the known
C79C9/507 scripted destructor. No literal VA 00483CD7 occurs in any initialized
section. This does not exclude computed indirect calls.

```text
000C7A1A 8b4660       mov eax,[esi+60]
000C7A1D 3bc7         cmp eax,edi
000C7A1F 7413         je C7A34
000C7A21 8b0d1420de00 mov ecx,[DE2014]
000C7A27 3bcf         cmp ecx,edi
000C7A29 7409         je C7A34
000C7A2B 50           push eax
000C7A2C e8a6c2fbff   call 83CD7
000C7A31 897e60       mov [esi+60],edi
```

DE2014 is the existing sole global TheTerrainTracksRenderObjClassSystem.
Independent lifecycle witnesses establish that this is the manager receiver:

- Init 91AEA/445: calls manager ctor 84CA5 at 91B5E; moves result EAX to
  ECX at 91B6D, publishes EAX to DE2014 at 91B72, calls 84D01 at 91B77.
- Reset 91CA7/102: loads ECX from DE2014 at 91CDC, null-checks it, calls
  84002 at 91CE6. That body walks manager+10, record next+1320, passing each
  record on stack and the manager in ECX to releaseTrack 83CE9 at 84016.
- Destructor 9203A/233: loads ECX from DE2014 at 9206E, calls 84CEF at
  9207B, frees that allocation, clears DE2014 at 92087. 84CEF calls full
  release 83E87 at 84CF2 and clears manager+08/+18.
- 83E87/136 tests record+1311 at 83E95, preserves next+1320, and calls
  83CE9 at 83EA6 on unbound records; subsequently drains manager+14.
- 83CE9/107 unlinks record+1320/+1324 from manager+10, pushes onto
  manager+14, then calls record reset 83CB2 at 83D4C.

The manager identity is corroborated. Its ownership of 83CD7 is NOT proven:
ECX also implements the caller null-check, and the callee never consumes it.
RET4 alone cannot distinguish free stdcall from an unused-this member.

## Separate record versus renderer: new explanatory evidence

84D01/171 allocates 1328 bytes at 84D4C/84D51, calls record constructor
840F1 at 84D63, and links records using +1320/+1324. Bind 84C05/160 moves
records from manager+14 to +10, calls record init 84206 at 84C90, and sets
record bound+1311 at 84C96. Constructor 840F1 initializes owner-like +38,
bound+1311, links+1320/+1324 and a 100-element, 30-byte edge array at +3C.
Record ctor/dtor 840F1/277 and 84096/63 install vtable RVA 7C743C; record
dtor resets via 83CB2 and releases texture+2C.

Renderer destructor 8E4EC/63 instead installs tables RVA 7C7850 and 7C784C
(secondary vptr at +8), calls renderer-resource release 8E187, then RenderObj
destructor 13BE20. These are distinct native object lifecycles.

Existing record owner Rva0084096 in TerrainTracksRenderObjClassConstructor.cpp
and W3DTerrainTrackOpaqueDestructor.cpp explicitly retains an unknown name.
Donor/ZH unbindTrack(TerrainTracksRenderObjClass*) is semantic guidance only:
its combined RenderObj record layout is not the target split layout. This
explains donor owner/bound offsets FC/13D5 versus target 38/1311; it does not
justify renaming the opaque target record or importing donor parameter types.

## Provenance and normal-tool constraints

Free provider Rva00083CD7Clear was recovered by commit
954f7e895044819b4673b8a08e9602ba883edc5a from stores/gap/caller evidence, not
original free/member identity. No relevant name_basis row exists. Consumer
pin Rva00083CD7Owner::rva00083CD7 merely records the thiscall hypothesis.
Prior re_attempts entries 36975/37097 record donor-layout mismatch; entry
50418 records the free-call 505-versus-507 trial. Do not repeat that trial.

rename.py allows identifier-only rewrites, not YGX-to-QAEX signature changes
(docs/naming.md, identifier restriction). add_match.py --replace-rva refuses
this authored C++ row: only scaffolding can be taken over; a real claim needs
a separately reviewable retraction. --replace-existing keys the same name.
The documented manual canonical rename exception is not evidence for an
unproved signature. No retraction, alias, wrapper, extra pin or inferred-name
shortcut is authorized. Provider and every consumer must migrate coherently
only after independent ownership/type evidence and explicit approval.

Minimum whole-TU verification footprint if later supported: producer
TerrainTrackEdgeInfoO1.cpp has six rows, 289B (83C8A/40, 84002/34, 83CD7/18,
83E5C/43, 84CEF/18, 83E87/136); scripted destructor has four rows, 566B
(C79C9/507, 761A18/24, 76199E/24, CEB6F/11), including complete EH ownership.
Its incomplete hierarchy remains an independent prerequisite. Existing
Rva00083CE9Host is a genuine partial manager view, not proof of full ownership.

## Static include audit, NOT an observed compiler failure

Pure filesystem source_extra_flags resolution finds all 26 producer /I roots
inside this worktree. Flags include O1, arch:SSE, G7, NDEBUG, WIN32, _WINDOWS,
MD and EHsc. Ordered roots: bfme2_ascii_zh, bfme2_ascii, bfmeterraintracks,
sweep; translated inputs/reference/.../GeneralsMD/Code engine/device/library
roots; game/Libraries/Source/WWVegas library roots and Compression; sweep.
The exact original operand list is producer line 1. STLport vendor/stlport
and pinned VS2003 Vc7/include exist locally; PlatformSDK is not requested.
Direct terrain header selects bfmeterraintracks, Debug/camera/TerrainLogic/
Object select sweep, other direct headers select the translated ZH roots.
Intended forced header bfme2_ascii_zh/zh_ascii.h includes bfme2_ascii/
ascii_string.h before shielding donor ASCIISTRING_H. Consumer flags are
O1/G7/arch:SSE/NDEBUG/MD/EHsc, bfme2_ascii and moduledata, no forced include.

However guest_run.py input_path resolves relative inputs against cwd; its
compile_arguments maps attached -FIzh_ascii.h to an absolute worktree-root
zh_ascii.h. That file does not exist; the intended header is under the shim
include directory. This is a STATIC mapping discrepancy, NOT an observed
compiler failure or wrapper refusal. No compiler_command, winepath, guest
process, mapping experiment, wrapper edit or fallback was invoked. Parent
review of any future mapping resolution is required independently of ABI proof.
