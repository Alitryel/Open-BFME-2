# AIStatCollector native lifecycle investigation, seat 2

Investigation and authorized isolated trials by gpt-6.1-sol, 2026-10-23. Worktree
`t3-7faf7255`, HEAD `b070af86da230bf77203cfc1d73c45a2b400865e`.
Observed origin/master `8dbeb84c3c082da3fa2b17ef12fef4529d5e56a1` has
the identical AIStatCollector.cpp blob. File and 0x004E030B claims belong
to `sol-team-supply-20261023`; they remain held for coordination.
The initial phase was read-only; later narrow compiler grants enabled the
trials below. This bank is evidence, not a production or linking result.

## Prior evidence reviewed

- `ai-countmap-constructor-link-20261022.md`: constructor visibility and EH
  trials, including rejected imported-inline/extern-template variants.
- `link-countmap-20261022.md` and its provider patch: distinct initializer
  addresses; no valid second int-table initializer pin.
- `ai-countmap-visible-ctors-20261023/readme.md`: 31-byte map / 64-byte
  table instruction resemblance still has a wrong initializer relocation.
- `opencontain-link-astra-s2-20261023/readme.md`: successful construction /
  unwind reconciliation elsewhere is not proof for this count map.
- Relevant AIStatCollector entries in `reverse/re_attempts.log`.

## Independently checked target facts

Disassembly below refers to RVAs in the local workshop-vanilla-1.06
`game.dat`, read through `tools/retail_body.py`, not compiler output.

1. Constructor 0x004E030B calls 0x004E02B8 on receiver+0x14. Player storage
   starts at+0x28, bounding the table to 20 bytes. The default construction
   body at 0x004E02B8 is 31 bytes, passes 100 and three temporary references
   to 0x004E007A, and returns its original receiver without stack arguments.
2. Table construction 0x004E007A (64 bytes) constructs the bucket-vector
   header on receiver+4 through 0x00025100, zeros receiver+0x10, and calls
   0x00148DDF with its initial count. It returns with RET 0x10.
3. Constructor unwind action beginning at the valid instruction boundary
   0x00791864 adds 0x14 to ECX; 0x00791867 jumps to 0x004DFCE1.
   That complete 5-byte body jumps to 0x004DFC20 with unchanged ECX.
   The latter complete 57-byte destructor calls clear 0x001DBCDC and frees
   the bucket buffer at+4 through 0x00030830. No payload destructor is called.
   These are actual existing neutral destructor providers, not signatures
   inferred from the opaque mapped type in a sweep TU.
4. The registration body at 0x004E01E3, owned by
   `Code/GameEngine/Source/Common/Rva004E0425Dispatch.cpp`, is distinct from
   the listener-callback Register at 0x004DF98B in the approved TU.
   On a successful lookup it increments DWORD[node+8]. On a miss,
   0x004E02A6 calls findSlot 0x0041F4E5 on the same table; 0x004E02AB stores
   DWORD 1 through the returned slot.
5. The complete 63-byte findSlot calls 0x00148B27, then on a miss builds a
   two-word {key, zero} temporary and calls 0x0053F3B1. That complete
   73-byte insert body resizes, hashes the integer key, calls 0x003ED191,
   links the node and increments receiver+0x10.
6. Allocator 0x003ED191 (37 bytes) explicitly requests **12 bytes** via
   0x000307F0, zeros node+0, and invokes 0x0060C9D9 on node+4.
   The complete 23-byte construction helper copies exactly two DWORDs.
   Thus this witnessed insertion path allocates next+key+mapped as 4+4+4,
   not a node containing an eight-byte mapped value. UnRegister decrements
   the same DWORD[node+8]. Count use and four-byte mapped storage are target
   facts; the original C++ enum/template spelling remains uncertain.

## Provider identity and remaining prerequisite

The rowed constructor providers in StlSweepW4Rva004E02B8.cpp and
StlSweepW5Rva004E007A.cpp instantiate `hash_map<int,Rva004E007AElement>`;
their mapped element has eight opaque bytes. Their source explicitly records
element identity as structural inference. Constructor byte equality does not
make that mapped layout the collector's layout. Transplanting that complete
type would contradict the independently witnessed 12-byte node allocation.

The current collector's `hash_map<int,int>` is compatible with the witnessed
node width and count operations, but its existing initializer identity at
0x00622410 is not native 0x00148DDF. Independent disassembly confirms the
difference: native 59-byte initialization calls next-size 0x0005571B,
reserve 0x00029BE0 and insert 0x00029CA0; the 106-byte int initializer expands
the prime lookup using lower_bound 0x00568D2F, then calls the same reserve and
insert addresses. The vendor and bfmehashtable shim initializer source is
identical; the shim's separate new-node rewrite does not explain this
initializer difference. Callee visibility remains a concrete question, not
evidence for changing payload width or assigning a second address to a name.

The existing neutral providers define only destruction/clear at these native
addresses. They do not supply an actual neutral default constructor symbol.
Declaring an invented neutral constructor without its genuine body, or
constructing the opaque-eight-byte STL type in cast/union storage and later
destroying it through the neutral view, would not establish a correct C++
lifecycle. No such wrapper, alias, pin or storage bridge is prepared.

Candidate continuation after compiler authorization: reconcile the genuine
four-byte count-table construction and its complete initializer/callee chain,
while requiring the existing native unwind destruction on the same 20-byte
object. The name-key producer supports investigating a NameKeyType count-map
spelling, but does not independently prove the original template parameters.
Do not treat a different spelling as a way to evade the int initializer debt.

## Authorized isolated lifecycle trials

Parent granted narrow compilation under build/orbstack/env.sh with
BFME_ORBSTACK_COMPILE_GRANTED=t3-7faf7255; BUILD_POOL=1 and BFME_OBJSTORE=off.
The clean local donor remains138757e9b74645fbcbb7724a7af2764e34931e11.
Parent integration against newer96c88c73 requires independent re-verification.
No runtime, donor, shared header, root cache or wrapper was modified.

The scoped original source baseline passed10/10 rows. A genuine typed
NameKeyType/int table trial exposes31B default-map construction,64B table
construction,59B initialization and48B next-size matching native shapes.
The generated map destructor is5B. Explicitly defining the implicit map
destructor specialization is rejected C2995; do not repeat that experiment.
Visibility of the real vector insert implementation is necessary: leaving
the declaration-only suppression calls3B insert2A2D0 rather than native
fill-insert29CA0. Same-TU clear visibility reduces table destruction to24B
and eliminates required EH; declaration then definition in that TU does not
restore it.

Parent approved AIStatCollectorCountTable.cpp in the same owning directory.
Moving the genuine typed clear specialization there makes the consumer
destructor53B and restores its EH prologue and clear-protection state.
Native57B additionally sets state-1 immediately before freeing bucket storage;
the53B trial omits that four-byte store. The shim allocator calls global
CRT-declared ::free and /EHsc assumes C callees do not throw. Native neutral
provider instead declares C++ _STL::free. Both names bind the actual game
free30830 provider; exception visibility remains a distinct unresolved
prerequisite, not justification for a fake wrapper or forced throw.

The separate typed clear was checked with normal explain_mismatch: all72B
and resolved call bytes match native1DBCDC. Both TUs use identical enum,
rts hash specialization and hashtable typedef declarations, retaining20B
table ownership and4B mapped counts. Original template spelling is still
an inference, not newly established target provenance.

A prior attempt to redeclare _STL::free after STL headers ended exit2 with
real C2883: conflict with cstdlib using-declaration. Wine also printed
Unhandled illegal instruction at70D92A0F for threads0084 and007c. These are
runtime observations, not successful execution evidence or a reason to
ignore C2883. Parent/runtime owner were notified; the declaration was removed.
The subsequent separate-clear compile completed without that observation.

Current diagnostics are worktree-local build/seat2-clear-external-consumer.log,
build/seat2-external-clear.log and build/seat2-clear-admission.log. The first
still refuses the collector constructor unresolved typed map ctor and reports
ambiguous equal-shaped EH labels. No collector success or link result is
claimed from those provisional inputs. Complete relocation/EH and paired
provider/consumer linkage remain required before any source commit.

## Final verified bank and operational prerequisite

Final status supersedes the provisional diagnostics above. The approved
`/EHsc /EHc-` trial on both TUs restores native destructor state-1 before
actual extern-C `_free` at RVA0x00030830, whose real owner is
`Code/GameEngine/Source/Common/System/GameMemoryFree.cpp` and whose body calls
`__gameMemFreePtr(block,3)`. No alias, wrapper, pin or forced throw was added.
The opaque mapped payload remains unknown; only the witnessed count use and
four-byte mapped width are target-established. Original enum/template naming
is inference. Both TUs use token-identical enum/hash/table declarations and
compatible explicit specialization declarations; construction and destruction
own the same genuine 20-byte table, not cast/union bridge storage.

The complete replayable `verified-trial.patch` in the adjacent directory
contains both real sources and seven proposed rows, but deliberately excludes
temporary landed attempt-log entries. Full source snapshots are also banked.
The provider default constructor needs its explicit instantiation for MSVC
emission. Native prerequisites independently byte/ref verified:

| RVA | Size | Genuine typed provider |
| --- | ---: | --- |
| 0x001DBCDC | 72 | hashtable::clear |
| 0x0005571B | 48 | hashtable::_M_next_size |
| 0x00148DDF | 59 | hashtable::_M_initialize_buckets |
| 0x004E007A | 64 | hashtable constructor |
| 0x004E02B8 | 31 | hash_map constructor |
| 0x004DFC20 | 57 | hashtable destructor |
| 0x004DFCE1 | 5 | generated hash_map destructor |

Normal strict paired preparation passed **17/17** rows (consumer12,
provider5), with two current strict reusable receipts. Normal EH verification
passed **3/3 EXACT** complete graphs, no baseline debt. Declared-definition
check passed both files. These are zero new unique retail bytes, not recovery
coverage. `relocations-and-definitions.json` retains every exact decorated
provider/callee, all body relocations, complete internal/external EH edge
bindings, and all emitted definitions (45 consumer,40 provider). Twelve named
non-funclet rows resolve strictly with no weak/unresolved/masked call binding.
Prime array112B is checked at native begin0x00BBD410/end0x00BBD480; existing
manager datum0x00DFEEF8, callback0x008DF983, `__except_list` and local graph-owned
FuncInfo labels remain their real identities. Incidental emitted definitions
are a manifest, not claims of additional recovered bodies or closure.

Default paired preview exit1: new provider is **not in census456ce161c5**.
Worker current-ledger preview exit1: **23,426 current-ledger objects missing**.
Exact refusals and successful gates are banked beside this note. Parent reports
its supported root `--refresh --current-ledger` readiness independently refused
**1,418 current-ledger objects missing**, log
`build/orbstack/counttable-current-ledger-readiness.log` (parent observation,
not reproduced by worker). No full unresolved-closure proof is available.
COMDAT-only `--new-variants --staged-peers` would not supply that proof and was
not substituted. No census, global build, copied/index-linked cache or fabricated
receipt was used. This is an **operational current-index prerequisite**, not
semantic failure, lane exhaustion, or permission to broaden into Common.

Future normal two-TU verification after supported index/object provisioning
and reapplication/admission of the banked trial:

```sh
consumer=Code/GameEngine/Source/GameLogic/SkirmishAI/AIStatCollector/AIStatCollector.cpp
provider=Code/GameEngine/Source/GameLogic/SkirmishAI/AIStatCollector/AIStatCollectorCountTable.cpp
./build.sh "$consumer" "$provider"
python3 tools/eh_verify.py "$consumer" "$provider" --json build/counttable-eh.json
python3 tools/link_check.py --prepare-current "$consumer" "$provider"
python3 tools/link_check.py --refresh --current-ledger "$consumer" "$provider"
```

Use the then-approved environment; parent must reverify newer donor96c88c73
rather than treating this138757e9 trial as current. Recursive fold-owner/global
closure is not asserted. Production sources/ledger are restored before this
evidence-only commit; baseline re-verification is recorded below. Claims stay
held for parent publication. No further compiler launches after baseline.
No Wine crash recurred in successful trials; earlier alert remains observation.

Restored original production baseline passed10/10 with normal build.sh, exit0;
see restored-baseline.log. The complete replay patch passes git apply --check
against this restored tree. Source and functions.csv have no production diff.
Record uses blocked (operational prerequisite), not partial: check_csv.py
rejects reverse/attempts stashes on already-real-C++ matched RVAs as orphans;
the full candidate is therefore preserved here as evidence, not in the picker
stash. Temporary trial landed entries were restored, not committed.
