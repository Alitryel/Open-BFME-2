# FXShaderGeometry::Init: identify the allocator's extra live values

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
BFME 2 input `20ec906f7e`; verified BFME 1 inputs
`37c3022de1ab944c7ffe536440d637dc8199091c`.
Compiler flags: `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The best bank remains **2333 bytes, nine differing bytes in seven instructions,
EH EXACT, zero unresolved calls**, score `0.9961423060437206`. Only its handoff
comment changes. A fresh private compile reproduced the previous bank's
function bytes and relocations. No production source, pin, gate or compiler
was changed. This is an unfinished assignment, not a new exact recovery.

## Continue here

The previous task was to identify serials 644/645 and the anonymous values
in the link-pointer split's cost calculation. That identification is now done.
Next follow **splitting/rematerialization and live-list reconstruction**: why
do the bank's tangent/binormal cursors and constant 2 disappear from the
flagged list before the link-pointer split is priced? Find a source spelling
that changes those decisions while retaining the native two-bone copy arm.

The split cost call returns to c2 RVA `0x8AB8A`; its call site at `0x8AB85`
calls `0x82473`. Earlier in that caller, `0x8AB61` calls `0x8B2AA`, then
`0x8AB76` calls `0xAFAC0`. These are concrete **uninvestigated** points for
tracing how the list changes, not established names for compiler functions.
Do not repeat the families below or the previous cost/scheduler sweeps.
There is no identified missing-callee prerequisite; the short-vector
constructor identity is already solved.

## New evidence, including a correction

Read-only snapshots from stock MSVC 13.10.3077 c2, loaded at `0x10700000`,
followed the candidate's first-use tuple and the function's linked IR.
Snapshots were taken at RVA `0x8292A`, immediately before the cost write.
Both completed traced objects reproduce their ordinary builds' complete
Init bytes **and relocations** (`bank-verification.json`).

The successor diagnostic is `pn_300000` from
`../fxinit-schedule-20261022/pn_300000.patch`: P/N copies outside the arm,
2326 bytes, unsuitable for landing. It is only an allocation diagnostic.

| Diagnostic flagged candidate | Meaning established from the same-run IR |
| --- | --- |
| 130, serial 644 | Cursor initialized from named `_binormals`; increased by 12 at the vertex-loop tail |
| 128, serial 645 | Cursor initialized from **`_tangents + 4`**, i.e. the Y field; increased by 12 at the tail |
| 129, serial 0 | Literal **0**, loaded by opcode `0x26A` with an immediate operand |
| 109, serial 0 | Literal **2**, likewise an immediate operand |
| 131, serial 647 | The existing link-pointer range, subsequently split into candidate 174 |

The cursor identities are supported by readable compiler symbol names,
initialization chains, the LEA displacement, and loop increments. These
cursors also participate in strength-reduced P/N address expressions; they
are not confined to the tangent/binormal stores.

**Correction to `fxinit-cost-20261022/readme.md`:** the bank's candidate 1
(serial 0), removed from the initial remap-base cost list in the diagnostic,
is a literal **zero**, not a condition flag. Its first defining tuple is
`0xD8DCC8`, opcode `0x26A`, immediate 0. The later P-null comparison consumes
it. Candidate 29/serial 405 is still consistent with the second-position
pointer; that interpretation is not being upgraded to a readable source-name
observation here.

Representative addresses in the saved diagnostic snapshot:

- `D5F148 -> D08B70 -> C4D19C`: load `_tangents`, LEA with displacement 4,
  store serial 645. `C4F95C -> D8BC38`: load `_binormals`, store serial 644.
- `CB7240`: immediate 2 to candidate 109; `CB81B8`: immediate 0 to 129.
- `D15658`: immediate 12; `C49050` and `C415DC`: cursor increments.

The earlier measured priorities remain: bank base 60 versus pointer split
36; diagnostic base 48 versus pointer split 54. This session maps the
previously anonymous contributors; it does not claim that changing any one
cost alone suffices. `observations.json` preserves selected raw tuples,
operands, symbols and cost events. Full snapshots remain in ignored
`build/fxinit-live22/`.

## New source trials and results

Each family used private objects and eight compile workers. Counts are
**generated combinations, not unique emitted bodies**. Overall: 13,902
attempted variants, 12,772 compiling and resolving within the scoring row,
288 compile failures and 842 extent/relocation refusals. None improves the
bank. `measurements.json` separates these outcomes and retains the best
byte/alignment scores per family.

| Family | Trials | Hypothesis |
| --- | ---: | --- |
| byteivs | 1016 | Explicit byte counters for subsets of six Vector3 streams and links/weights, signedness, scopes and update positions |
| streamloops | 1296 | Optional T/B/P/N copies expressed as pointer-controlled loops; all reproduce the bank |
| tailclone | 288 | Duplicate vertex/index updates across branch exits, staged next values and stride references |
| groupcursor | 1008 | Common tangent/binormal address cursors and stream-relative offsets |
| contextnull | 768 | Derive P/N null-test zero from already-proven bone/link conditions; direct or staged comparisons |
| streamviews | 4096 | Factorial across six copy sites: assignment, float-pointer fields, scalar-argument helper and Vector3 references |
| prebiased / prebiasedinline | 1512 + 1512 | Native-like +4/+8 cursor origins, invariant offsets in three scopes, explicit increment or per-iteration address |
| literalweb | 576 | Signed/unsigned/64-bit types for bone equality and pointer-null constants |
| copyprep | 1110 | Prepare source/destination addresses for T/B/P/N in five scopes, integer or typed pointers |
| uvvisibility | 96 | Actual target UV accessor body and legacy fallback, before/after Init, inline/noinline, valid nonthrowing forwarder |
| dispatchinline / corrected const subset | 288 + 144 | Inline the whole pass/bone dispatch, early returns, array/reference/scalar parameters, argument groups and const map access |
| recombine | 48 | Cross the best byte-counter region variants with staged-link and prior relative-map region candidates |

A first 144-case const-map correction used stale source slice offsets after
inserting the missing const overload and failed compilation. It contributes
to the overall count, not to an excluded hypothesis. The corrected 144-case
subset uses the const `begin`/`operator[]` spelling at STLport `_vector.h`
lines 173/188 and resolves completely. The original dispatch family's 144
const-map failures were missing that overload. The generators retained here
include the working correction; malformed generated sources are not banked.

Regional comparison found the byte-counter family can reduce the seven
remap operand lines to six by changing the SIB ordering. **The register roles
remain wrong**, with additional changes elsewhere. Recombining that result
with the earlier relative-map/staged-link candidates did not improve it.
The prebiased cursor families cause large changes to the surrounding loop;
the independent-copy and literal families commonly compile identically.
No useful independent region winner was discarded.

Callee visibility was checked against BFME 2's rowed
`MeshMatDescGetUVArrayByIndex.cpp` (125 B at `0xD1F40`) and
`MeshMatDescGetUVArrayRva000D1F1A.cpp` (38 B), plus BFME 1's header at the
revision above. BFME 1 lacks BFME 2's legacy fallback, so it was not silently
substituted. Eighty variants reproduce the bank; sixteen inline the accessor
and produce 2391-byte Init bodies. This does not establish a new helper match.

The independent explanations now have concrete evidence: native control
flow remains supported by WB; declaration/lifetime and constant families
above fail; field/layout and copy views fail; the loop callee visibility
trial fails. Compiler-setting and earlier WB/reference checks remain in
`fxinit-remap-order-20261020`, `fxinit-wbinline-20261020` and the previous
cost/scheduler handoffs. The remaining issue is still allocation/splitting.

## Verification and reproduction

`check_csv.py` passed at session start. Published object-cache refresh
completed. BFME 1 freshness was skipped under the runner's active update
lock owned by `claudec2`; the verified pointer was retained. No success
stamp or other seat's lock was changed.

`verify_bank.py` freshly compiled the bank, checked all resolved bytes,
verified EH EXACT, and compared ordinary/traced bytes and relocations.
`tools/align_diff.py` reports 2333 B / 735 instructions on both sides,
zero structural regions and seven real memory-operand differences; five
additional memory lines are address relocations. See `bank-align.txt`.
This partial does not pass the exact-body gate and was not put in `Code/`.

Generators import the existing helper in
`../fxinit-schedule-20261022/search.py.txt`; restore it as
`build/fxinit-seat22/search.py`. Restore this directory's `*.py.txt` files
without `.txt` under `build/fxinit-live22/`. Run `search.py FAMILY` for the
first four families; other named generators take no arguments. The tracer
also imports `wdbg.py` from the scheduler handoff, restored to
`build/netpacket-20261022e/wdbg.py`. Its two arguments are source and private
object paths. `live_trace.py` snapshots the pointer split; `base_trace.py`
snapshots the initial remap base. Only debugger reads/breakpoints are used.
The verification script's old control-object paths are listed in its source;
recreate them from the unchanged bank and the existing diagnostic patch.

Eventual home, select-any helper and EH-handler landing requirements remain
in `../fxinit-wbinline-20261020/readme.md` and the assignment instructions.
