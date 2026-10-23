# SpecialAbilityUpdate::finishAbility handoff

Result: blocked; the existing bank is kept. The candidate below trades one structural region and one register difference for one memory difference and a body 5 bytes short of retail (789 against 794), which the coordinator did not accept as closer. Symbol `?finishAbility@SpecialAbilityUpdate@@UAEXXZ`, retail RVA `0x00451B92`, extent 794 bytes, destination `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`. No production source, pins, or function rows changed. Model: gpt-6.1-sol.

Inputs: BFME2 checkout `fb5b8848171738ca8cdd8e92e959c6824291efed`; BFME1 checkout `a18d9ed50607e9175de4d6568798d7d73119de09`. The current bank carries the existing BFME1/ZH semantic recovery and W9 coordinate helpers. This round adds no donor implementation. Flags remain the bank's `/O1 /G7 /arch:SSE /GX /DNDEBUG /MD /I. /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Oy- /Op`.

Identity is independently supported by the named WB body at VA `0x10E7810`, its callgraph and completion-button branch, the retail base vtable at VA `0xC3FBA8` slot 19, and the EvacuateGarrisonSpecialPower override's direct base call. The target ends in plain RET at RVA `0x451EAB`; the next inventoried function begins at `0x451EAC`. Native calls and field accesses agree with the bank (normalize `0x35B6`, object position `+0x38`, AI `+0x258`, module flee range `+0x58`, command button `+0xC0`, completion callback slot 13). The owned Object::doCommandButton declaration at `0x296749` takes int and bool. Raw evidence: `build/finishability_w6/identity.wb.log`, `scale.wb.log`, `add.wb.log`, and `native_evidence.log` in that task folder. Names are supported by WB and donor relationships; padded views remain accessed prefixes rather than recovered complete layouts.

The selected source is `build/finishability_w6/best.cpp`; the original bank is preserved byte for byte as `build/finishability_w6/baseline.cpp`. The mine block snapshots the flee range and normalized direction components before copying the mine position, computes three sums in a local Coord3D, then sets pos from the sum. Each multiply remains binary32 SSE arithmetic; there are no added calls, volatile accesses, assembly, or new helper dependencies. The redundant trial PHIs were removed because plain snapshots produce identical bytes.

Measurements from `align_diff.py`:

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Positional nonrelocation differing bytes |
|---|---:|---:|---:|---:|---:|
| Original bank | 793 | 4 | 12 | 3 | 222 |
| Selected | 789 | 3 | 13 | 2 | 219 |

The five memory entries involving relocated vtables/globals are relocation noise in both reports. Relocation and branch lines are not counted as defects. The positional count includes the missing-byte tail and is supplementary; the fewer structural regions is the reason to replace the bank. Raw outputs are `baseline.align.log`, `best.align.log`, their `.explain.log` and `.rawdisasm.log` siblings, and `.metrics.json` receipts under `build/finishability_w6/`.

Remaining mismatch: retail preloads direction y/z at offsets `+0x201` and `+0x206` before the three-movsd position copy, holds range in xmm3 and results in xmm2/xmm0/xmm1, then uses a register-register z multiply at `+0x227`. The selected source folds those inputs into memory multiplies, reuses the range register, and is five bytes shorter. Its last three stores now follow all three additions. The function is not byte-exact and must not be rowed as matched.

Hypotheses tested, with sources and raw logs retained in the task folder:

| Hypothesis | Trial stems | Observation |
|---|---|---|
| Native base-subobject assignment information | base_implicit, base_explicit, base_parameters | Same body as original bank. |
| Native empty destructor and shared direction lifetime | dtor, dtor_no_throw, shared_dtor, shared_dtor_no_throw | Destructor alone unchanged; other forms regress to 812 or 821 bytes. The 821-byte trials fail explain_mismatch's extent check; align_diff still measures their raw objects. |
| Stale explicit precision/frame flags | no_op, no_oy, no_op_oy | Same body as original bank. |
| Grouped result lifetime | sum_fields, sum_ctor, sum_set, offset_copy | Sums group their stores but retain four structural regions. Offset copy unchanged. |
| Input snapshots plus grouped results | phi1, phi2, phi3, phi7, plain_inputs, reversed_inputs, best | Plain snapshots improve to three structural regions; y/z PHIs add nothing, range PHI introduces an unwanted float comparison, reversed declarations unchanged. |
| Scale retimed after position copy | delayed_scale, delayed_scale_sums | Returns the original or grouped-result four-region shape. |

Every experiment checked `build/STOP_WORKER`. No background tasks or subagents were started. No further evidence-backed experiment remains among these hypotheses. Preserve the early-load/register-coloring blocker for the next round; do not repeat base, destructor, flag, result-constructor, or retimed-scale trials without a new dependency or compiler-shape explanation.
