# 0x758DE0: call-target lowering and nonvolatile copies

Continue the assigned body. The bank is unchanged: **333 bytes, zero
relocations, 31 positional differences, first +0x94, 308/333 complete
instruction-pair bytes aligned**, score 0.924924924924925. Independent
compilation reproduces SHA256
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed, and no production source, function row or pin changed.

The reverse-only fastcall pair remains an **unproven ABI diagnostic**.
The uniform ordinary-virtual control is 333 bytes, 41 positional differences,
302 aligned bytes. These experiments establish no original callback type,
class identity or supported reason to land the alternate interface.

## Preparation and prior negative evidence

Started clean at `158fdb4fe5f2f516d465e0cbfa6f5f4f3a127373`, over
origin/master `2e703afb59223fc5e408ae1762b98b2ccceba156`, retaining two
unpublished evidence commits. Pulled/rebased, passed check_csv (98,101
function rows, 15,853 symbols, 2,139 data), claimed the assignment and
fetched the published link index. No wind-down signal was present.

The instruction read was still fresh. Read the per-RVA history through
pick-hard and the vcall, source-shapes, local-registers, lowering,
final-schedule, edges, rounds, interference, aggregate and dispatch packets.
Their control-flow, scopes/lifetimes, real-header/layout, callee visibility
and compiler-setting trials remain negative evidence; they were not
repeated as new hypotheses. The last packet's specific lead was the
volatile-slot model's late vptr load, with an unwanted separate target load.

BFME 1 freshness was due; this seat acquired the shared updater lock.
The old verified pointer and clean checkout were
`f36a4db066aa61edeee90085a31d628eb829001d`; official upstream had advanced to
`138757e9b74645fbcbb7724a7af2764e34931e11`. The freshness comparison is
recorded in `../bfme1-reference-138757e9-20261023/README.md`: both old and
new full byte/data gates pass, and the donor sweep cache was refreshed. None of the donor changes alters
this body's compiler, flags or headers.

Compiler: stock RTM c2.dll 13.10.3077, base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`;
`/O2 /MD /EHsc /I.`. Native extent remains 0x758DE0..0x758F2D (333 bytes,
RET then three INT3 bytes). Private objects used compiler_command; no
scratch trial wrote the shared match cache. No maintainer-only runner ran.

## Read-only compiler comparison

Three traced compilations completed and reproduced independently compiled
ordinary objects exactly, with zero relocations (`trace-checks.json`). The
debugger inspected state; it did not change compiler operands or codegen.
The selected first-response blocks are in `selected-ir.txt`.

* In the bank, general lowering at c2+0x73108 has made the inner vtable load
  explicit by +0x5fa74, **before the argument moves**. At +0xb0030 those
  moves become PUSH nodes and the vtable load remains before both pushes.
  Before local allocation (+0xb0037), global allocation has already put
  normal address H307 in EDI and point address H308 in EAX. The early inner
  vptr H382 therefore conflicts with the point's EAX lifetime. After local
  allocation H382 uses EDX; outer table H384 uses EBP.
* The volatile-vptr control v00256 keeps its inner vptr load early too.
  It does not provide the desired short target lifetime.
* The volatile-**slot** control v00384 puts both argument moves before
  `vptr -> H378; [H378+0xc] -> H213; CALL H213` already at +0x5fa74.
  After argument lowering the two pushes precede both loads. After local
  allocation H378 is EAX and H213 is EDX. This explains the late EAX vptr,
  but leaves `mov edx,[eax+0xc]; call edx` instead of retail's memory call.
* All three ordinary first-response prepare CALLs have word 14 = 0x140000
  before argument lowering and 0x10140000 afterward. That field alone
  does not explain this volatile-slot distinction. The operand graph
  differs: a memory target versus a separately loaded scalar target.

The decoder follows the argument list's next links separately from nested
memory bases. The earlier decoder's recursive list concatenation could
make bases appear to have extra operands. Symbol numbers Hn and physical
register IDs Rn are diagnostic labels, not recovered internal names.

## New source hypotheses and results

**7,492 corrected variants compiled successfully with zero relocations**;
another 512 were rejected for unsupported attributes. No exact body or
whole-body improvement was found. Complete `(mnemonic, operands)` scoring
and regional winners are in `summary.json`; search.py's mnemonic-first
metric is separate. Positional counts there include an extent difference.

| Family | Successful / generated | Distinct bodies | Evidence-backed question |
| --- | ---: | ---: | --- |
| contracts | 512 / 1,024 | 3 | Can callback cv qualification or nothrow change target lifetimes? Independently vary prepare/test/respond cv, prepare attribute, bridge and reverse-interface control. |
| targetcopy | 2,048 / 2,048 | 80 | Can a nonvolatile copy of the one-word member target get the volatile-slot model's late lowering while retaining memory-call folding? |
| slotaddr | 2,048 / 2,048 | 330 | Instead copy the target slot's address or raw vptr, then read an ordinary memory target; independently vary both inner sites, pointer/reference return and reverse control. |
| argstores | 2,500 / 2,500 | 4 | Can identity stores inside the point/normal argument expressions alter call-target ordering? Four independently selected argument positions, bridge/direct and reverse controls. |
| hybrid | 256 / 256 | 46 | Recombine targetcopy and slotaddr response winners with the original ordinary test call rather than always changing both sites. |
| operators | 128 / 128 | 2 | Does call-operator syntax produce different call lowering under the same ABI? Three independent callback names and invocation forms, bank and uniform controls. |

Target copies test direct/local/union/intrinsic-memcpy copies, complement,
inverse rotates, halfword rotations, implicit object copies, byte and
halfword copies, double negation and an assumption. The copy parameter is
by value or const reference and its inline helper is cdecl or fastcall.
Slot-address copies test analogous identities, a widened integer roundtrip,
zero-count memcpy/memset, masks and pointer/reference returns. These raw
member-table interfaces are diagnostics, not proven production declarations.

Ordinary target copies force an explicit register-target load and lose
memory-call folding. The slotaddr/v1756 response has 31 aligned bytes
versus the bank's 19, but it reconstructs the vptr through halfword stack
stores and a reload, and emits 356 bytes overall. It is not the desired
short vptr lifetime. Hybrid recombination yields at most the unchanged
direct-response control overall; its best response region is 27 bytes,
again with extra stack work. There is no useful local edit to splice.

Argument identity stores target either data pointer or source pointer,
inside the four point/normal argument expressions. This differs from the
earlier aggregate packet's receiver-expression stores. Every variant
reproduces one of the four existing controls, with no regional improvement.
They propose no new fact about callback effects or production writes.

The operator family uses distinct pointer result/test types, an explicit
void-pointer response argument and declaring-base receiver casts to select
overloads. Named-method controls reproduce the bank. Every corrected
call-operator model reproduces exactly the bank or uniform control too. All
six call operands and zero relocations were checked in every one of the 128
emitted bodies (`operator-checks.json`). Initial same-class overloads grouped
the vtable slots differently. Splitting declarations across inherited slot
boundaries fixed prepare, but an early using declaration still pulled test
before its padding slots. Moving using after the padding fixed the offsets;
explicit receiver-base casts resolved inherited same-name ambiguities. The
initial ABI-invalid/rejected layouts were excluded. `operator-v112.cpp.txt`
retains all three operators in the corrected hierarchy. These are diagnostic
compiler models, not evidence for original operators or target inheritance.

MSVC 7.1 rejects noalias and restrict with C2485; `compiler-rejections.txt`
preserves representative errors. Those attributes were not successful
models. An initial targetcopy generator omitted a space in helper names;
it was corrected and all 2,048 cases rebuilt. Only the corrected run is
counted. No verifier false reject was encountered.

## Reproduction and continuation

Copy the .py.txt and .cpp.txt files to a directory immediately under build/,
dropping .txt. Run each generator then `search.py FAMILY` with eight private
workers. Hybrid reads the preceding targetcopy and slotaddr source families.
Run `regions.py contracts targetcopy slotaddr argstores hybrid operators`. Independent
variant.py builds of six retained sources confirmed sizes, relocations,
hashes and scores (`independent-checks.json`). The bank is unchanged.

For traces, run `capture.py bank`, `capture.py v00256` and `capture.py v00384`,
then `decode.py TAG-capture.json`. The debugger helper expects Wine and
the compiler image above. It records fw[2]'s graph at +0x5f923, +0x5fa5a,
+0x5fa74, +0xb0029, +0xb0030, +0xb0037 and +0xb003e, then lets compilation
finish. Full raw snapshots remain scratch; selected blocks are retained.

Do not repeat these target-copy/slot-address identities, argument stores,
qualification matrices or ABI-correct call-operator models unchanged. The next question remains how an
ordinary virtual-call representation can place the vptr definition after
the point argument's last use before local allocation, while retaining a
memory target and the cached outer table. The traces distinguish this from
merely rescheduling the bank after allocation. As the earlier 69-byte probe
already showed, final scheduling can move an early vptr load after a push;
early reordering is a source hypothesis, not a necessary condition for a
solution. The first response additionally needs compatible register lifetimes. They do not identify a
missing callee or external prerequisite, so no blocked-on RVA is justified.
Continue this assignment across sessions; no other body was started.
