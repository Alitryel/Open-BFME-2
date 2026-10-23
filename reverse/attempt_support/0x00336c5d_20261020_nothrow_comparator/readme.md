# 0x00336C5D: exact body, landing blocked by an overlapping row

## What the coordinator needs to do

The banked body `reverse/attempts/0x00336c5d.cpp` now compiles to all 595 retail bytes of `?rva002E9680ParseModelConditionEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z` (RVA 0x00336C5D, 0x00336C5D..0x00336EB0 including both catch handlers). It was not landed because `add_match.py` refuses the range: the matched row `?Rva00336E72Get@@YAHXZ` (0x00336E72, 6 bytes, `Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp`) claims this body's `catch(...)` funclet, and add_match only takes over scaffold rows ("retract a real claim in its own commit").

To land it:

1. In its own commit, retract `?Rva00336E72Get@@YAHXZ`: delete its row from `reverse/functions.csv` and its definition (with its comment block) from `ConstIntGettersAddr.cpp`. Ownership evidence is in `reverse/attempt_support/00336e1e-boundary-20261019.md`: FuncInfo 0x00D258C4 lists the catch-all handler 0x00736E72 for this parent, and the handler returns the parent's continuation 0x00736E78. Its "byte-identical dead twin" at 0x00336E6C is the tail of the typed `INIException` handler.
2. Apply `homes-select-any.patch` from this folder. It gives the two predicate homes select-any linkage with absent-from-retail anchors, because the new unit compiles identical COMDAT copies of both. Both homes were rebuilt with the patch applied and stayed exact (`Rva00332F5BCtor.cpp` 2/2, `Rva00045473Equal.cpp` 1/1); `find_declared_unmatched` passed on both.
3. Create `Code/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseModelConditionEvent.cpp` from the bank without its `// ?rva002E9680...` and `// partial score=` lines (the remaining first line is `// stlport`), then run `python tools/add_match.py '?rva002E9680ParseModelConditionEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z' 0x00336C5D 595 <that path>`. The path mirrors the BFME 1 donor file; `repair_queue.py dest` offers only a neighbour heuristic (`StlportVectorPushBackFamily.cpp`), and the class's other bodies live in one file per function in that folder.

No pin is needed. The link census was not previewed, because no local census index exists in the seat and fetching one is not allowed there.

## Mechanism

The lone residue of every earlier attempt was `cmp al, bl` (ours) against retail's `test al, al` after the comparator call at +0x17D. Inside a `try`, cl 7.1 treats the bool result of a call that may throw as a variable-backed value and compares it against the zero register; the result of a call it can prove nothrow stays a plain temporary and gets `test al, al`. Retail's own rb-tree `insert_unique` (0x0032CB55) shows the variable-versus-temporary split within one body: `cmp al, bl` where the result is stored to a named bool, `test al, al` where it only feeds a branch.

Diagnostics on copies of the old bank (measured, n=1 each):

| Variant | Size | Test after the comparator call |
| --- | ---: | --- |
| old bank | 595 | `cmp al, bl` |
| no found flag, early `return` in the loop | 591 | `cmp al, bl` |
| no `try`/`catch` | 470 | `test al, al` |
| comparator declared `throw()` | 595 | exact |
| comparator declared `__declspec(nothrow)` | 595 | exact |
| visible comparator, opaque `Rva00045473Equal` | 595 | `cmp al, bl` |
| visible comparator and visible `Rva00045473Equal` (memcmp is `extern "C"`, nothrow under /EHsc) | 595 | exact |

The bank uses the last form, which needs no exception specification: byte-faithful `__declspec(noinline) inline` copies of the rowed comparator 0x00332F81 and the memcmp predicate 0x00045473, so cl proves the call cannot throw. `explain_mismatch` confirms both copies equal retail (64 B and 24 B, exact). The record class now names its fields (`m_nameKey` from the BFME 1 donor, then the required and excluded 76-byte sets, matching the ctor's argument order); its size and the caller's bytes are unchanged.

## Measurements

`align_diff.py` at 595 bytes, `BFME_OBJSTORE=off`:

| Source | Emitted | Structural regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| old bank | 595 B | 1 (`test al, al` vs `cmp al, bl` at +0x17D) | 2 | 0 |
| new bank | 595 B | 0 | 2 | 0 |

Both memory lines are the unrelocated `theDebug` DIR32 (`[0xde0880]` against `[0]`), which the gate fills and checks for consistency. Raw logs: `before-align.txt`, `after-align.txt`.

The scoped byte gate was previewed by `gate_preview.py.txt`, which loads `tools/build.py`, points it at a scratch copy of the ledger with the 0x00336E72 row dropped and this row added, and runs the scoped verification, the DIR32 consistency check and `eh_verify`. Result (`gate-preview.txt`): functions 1/1 OK, string refs 3 + 1 empty OK, DIR32 consistency OK, EH verify EXACT 1/1.

## Identity

Unchanged and partly donor-derived: the semantics come from BFME 1 9cbfb551 `LuaScriptEngineParseModelConditionEvent.cpp`, and the symbol keeps the existing pin's spelling (`reverse/symbols.csv`, callee of the dispatcher 0x003371F4). Target evidence for a real name: the WorldBuilder twin 0xBFFF80 (`tools/wb_show.py 0x00336C5D`) carries assert strings naming `LuaScriptEngine::ProcessModelConditionEvent` in `LuaScriptEngine.cpp`, the same body shape (found flag, comparator loop, push_back on miss) and a DEBUG_CRASH "Duplicate model condition." on the found path. A rename to `ProcessModelConditionEvent` would also touch the dispatcher's call and the pin, so it was left for a separate change.

Model: claude-opus-5-5.
