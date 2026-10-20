# 0x00307EDC: exact loader and verified fold pins

The three pins below have now passed `pin_admission.py --add` using their
actual matched provider objects. The /Od provider explicitly instantiates the
char allocator-proxy swap; its existing rows remain exact. The 372-byte loader
is recovered in the **existing** `Code/GameEngine/Source/Common/Rva00240000Load308050.cpp`
alongside its sole 90-byte caller, preserving the caller's opaque loader call
by defining the loader afterwards. No new split unit was needed. Normal source
verification passes 2/2 bodies and EH verification passes 2/2 parents. The two
fold-provider units pass 173/173 existing bodies, and pin consistency is clean.
The old bank is removed by verified `add_match`. This recovers 372 unique C++
bytes; shared fold pins and already-rowed helpers are not additional byte credit.

The remainder records the original bank's evidence and prerequisite discovery.

Link follow-up: the ordinary census-based preview does **not** yet link the
loader unit. Four small visibility repairs retain 372/372 bytes: declare the
already-rowed count constructor, use a TU-local unsigned max, suppress the
out-of-line fill_n instantiation, and keep the allocator-proxy deallocate
body inline-only as in the matched provider. This reduces its preview blockers
from twelve to seven. Remaining: char fill, proxy copy/allocate/swap copies,
the private _M_fill_insert copy, and selected __uninitialized_copy/fill_n
providers. The companion /Od provider still links (578 bytes unchanged).
No linked-byte gain or closed-strict result is claimed for this recovery.
Removing the vector destructor body or making proxy swap opaque loses the
exact loader shape (297/unresolved or 376 bytes); do not replay those changes.
Normal byte, EH and pin gates are separate from this diagnostic link debt.
Scratch controls: build/loader-inline-visibility-oct20/; final ordinary
preview: build/loader-307edc-final-link-preview-oct20.txt.

Symbol `?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z`, retail RVA 0x00307EDC, 372 bytes, cdecl. The banked body in `reverse/attempts/0x00307edc.cpp` now compiles to retail's 372 bytes with every non-relocation byte equal. It was not landed because its two out-of-line STLport calls have no ledger address yet, and adding the fold pins they need was refused by this seat's permission system. Model: claude-opus-5-5.

## What closed the codegen gap

The earlier residue (retail keeps `bytes._M_start` in EBX for the read-fail and decompress-fail destructors, then reuses the zero in EAX, where the old bank reloaded `[ebp-0x18]` and cached zero in EDI) had one cause. The bank's `vector<char>` specialization declared `erase` and `_M_fill_insert` without bodies, so the out-of-line `resize` handed `this` to opaque functions and cl had to assume every later call could change the vector. With STLport 4.5.3's bodies for `erase`, `_M_clear`, `_M_set`, `_M_insert_overflow` and `_M_fill_insert` in the unit, cl proves the vector's address is not retained and keeps `_M_start` in a register across the virtual file calls and the CompressionManager calls, exactly as retail does. Retail's TU had every member visible because STLport is header-only.

Controlled probes (scratch, cl 13.10.3077 /O1): a local object's field is forwarded across an opaque virtual call only when every call that receives the object's address has a visible body that does not leak it. With the constructor or the grow call opaque, cl reloads.

## Measurements (align_diff, BFME_OBJSTORE=off)

| Source | Emitted | Structural regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| previous bank (score 0.9) | 376 B | 4 | 4 (one is the TheFileSystem DIR32) | 0 |
| new bank | 372 B | 0 | 1 (the TheFileSystem DIR32 only) | 0 |

`/Oa` and `/Ow` on the old bank compiled byte-identically to it (ruled out). The result is the same with and without `/G7 /arch:SSE`; the bank carries the GameEngine region flags. Resolving the new body against the byte gate's symbol map leaves only three call displacements unresolved (offsets 0x17, 0x12D, 0x14C). With the two pins below added to the map, all 372 bytes equal retail.

## Remaining prerequisite: three ICF fold pins

1. `??0?$_Vector_base@DV?$allocator@D@_STL@@@_STL@@QAE@ABV?$allocator@D@1@@Z` at 0x0007FAEA, `fold-proof=Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp`. A read-only dry run of `pin_admission.fold_proof_problems` returned PROVEN.
2. `??$swap@V?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@@_STL@@YAXAAV?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@0@0@Z` at 0x00025AD0. Retail 0x003079C1 calls the 34-byte /Od body at 0x00025AD0, so the linker kept an /Od copy of this char instantiation. No matched unit defines it at /Od yet. Adding `template void _STL::swap(_STL::_STLP_alloc_proxy<char *, char, _STL::allocator<char> > &, _STL::_STLP_alloc_proxy<char *, char, _STL::allocator<char> > &);` to the /Od /Ob1 unit `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr.cpp` (owner of 0x00025AD0) would supply it: a scratch TU with exactly those flags compiles it to retail's 34 bytes with no relocations. Then pin it with `fold-proof=Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr.cpp`. That unit's existing rows were not re-verified with the line added.
3. `?swap@?$vector@DV?$allocator@D@_STL@@@_STL@@QAEXAAV12@@Z` at 0x003079C1, `fold-proof=Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp`. The dry run refuses it today (that unit compiles the inner char swap to 31 bytes, not 34). With pin 2 assumed in the symbol map, the dry run returned PROVEN.

After the pins, land with `add_match.py` into a new unit. `repair_queue.py dest` offers only the neighbour heuristic (DataChunkOutputWriteDict.cpp, a single-function /EHsc unit without STLport). Retail's layout puts the body in the DataChunk.cpp TU (between DataChunkOutput::writeDict 0x00307D85 and its caller 0x00308050, with the vector<char>(n) constructor 0x00307C43 emitted just before), but `Code/GameEngine/Source/Common/System/DataChunk.cpp` is /GX without STLport, and this body needs STLport with /EHs. The proposed home is therefore a new unit, for example `Code/GameEngine/Source/Common/System/Rva00307EDCReadFileBytes.cpp`, holding the bank minus its `// ?symbol` and `// partial score=` header lines. `find_declared_unmatched.find_defined_functions` reports no definitions in that text.

## Link notes

The unit emits COMDAT copies of vector<char>'s `erase`, `_M_fill_insert` and `_M_insert_overflow`; retail's own erase is 0x0031BD55. `_M_fill_insert` is defined `inline` so it stays selectany. Retail's unwind funclets call 0x0007FAB3 (vector destructor fold) for states 0 and 2, and 0x00306EF5 (the rowed file-closer destructor, placeholder name `bfmeRunEF@BfmeThingEF`) for state 1.

## Identity

Unchanged from earlier attempts: the File virtual slots (+0x2C size, +0x0C read, +0x08 close), openFile(name, 0x141, 0), the rowed resize 0x000826E3 and vector<char>(n) 0x00307C43, and the CompressionManager statics. A scan of every direct `call rel32` in .text finds only this function calling decompressData 0x0068A4E0 and the vector<char>(n) constructor 0x00307C43. Its sole caller 0x00308050 takes the name by value, like Zero Hour's `CachedFileInputStream::open(AsciiString)` in DataChunk.cpp, which is a structural lead, not a proven name. The name stays address-derived.

Scratch evidence: `build/t307/` in the seat checkout (notes.txt, align logs, probes, dry-run scripts), which is not tracked.
