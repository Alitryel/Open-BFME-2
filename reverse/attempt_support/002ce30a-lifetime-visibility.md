# privateFireWeapon stack-lifetime follow-up

Blocked. The existing caller and helper banks remain byte-for-byte unchanged. No production source, function row, symbol pin, verifier or compiler override changed. All changes remain uncommitted. Input revision: 8c8b04d8d4dbc349a8c745865493e349a2471da0. model=gpt-6.1-sol.

The target is `?privateFireWeapon@Weapon@@QAE_NPBVObject@@PBUCoord3D@@0H1_N2IPAH@Z`, RVA 0x002CE30A, 955 bytes. Its destination is Code/GameEngine/Source/GameLogic/Object/Weapon.cpp. The bank is reverse/attempts/0x002ce30a.cpp. The same-unit return-by-value getLinearPosition helper is 0x002CB594, 199 bytes, and remains independently byte-exact with the real caller. It is not landed separately.

## Remaining mismatch

Before and after: 955 emitted bytes; 0 structural regions, 6 DIR32-only memory operand differences and 8 frame/bonus operand differences. Normal resolution leaves 12 differing bytes because the local helper is not in the ledger. Resolving only the independently exact helper diagnostically leaves 8 differing bytes, at offsets 0x5, 0x18, 0x1D, 0xE6, 0x130, 0x1A9, 0x2E4 and 0x2F1. The first is frame size 0x30 versus retail 0x24; the other seven are bonus addresses EBP-0x30 versus EBP-0x24. There is no qualifying closer candidate.

The complete provider-visibility trial independently verifies computeBonus (86 bytes), both append helpers (52 and 39 bytes), the special provider (93 bytes), the firing provider (1561 bytes) and delay getter (90 bytes). Resolving that trial only through independently exact same-unit providers and helper still leaves the same eight caller differences. These diagnostic maps change neither pins nor the ledger. The delay getter carries its owner's unchanged, already documented x87 conversion asm; no assembly was added to the caller or helper.

## Experiments and refutation

Every hypothesis, supporting evidence and refutation criterion was recorded before its trial in build/worker-002ce30a-lifetimes/hypotheses.md. Real computeBonus visibility, firing-provider visibility, special-provider visibility, the entire append chain, all bonus consumers including the delay getter, EHs-c-, the donor clear-member constructor and elidable temporary construction were inert. A lexical bonus scope ending immediately after the firing calls, expressed with an equivalent early no-ammo return, regressed alignment with and without real provider visibility. No overlays, shortened objects, expired pointers, volatile stores or synthetic caller were used.

| Trial | Emitted bytes | Structural regions | Memory differences | Register differences |
|---|---:|---:|---:|---:|
| before | 955 | 0 | 6 | 8 |
| compute-visible | 955 | 0 | 6 | 8 |
| compute-fire-visible | 955 | 0 | 6 | 8 |
| all-consumers-visible | 955 | 0 | 6 | 8 |
| full-bonus-chain-visible | 955 | 0 | 6 | 8 |
| no-eh | 955 | 0 | 6 | 8 |
| donor-clear-ctor | 955 | 0 | 6 | 8 |
| bonus-temporary | 955 | 0 | 6 | 8 |
| narrow-bonus | 949 | 10 | 22 | 11 |
| narrow-bonus-visible | 949 | 10 | 22 | 11 |
| complete-bonus-visibility | 955 | 0 | 6 | 8 |

The full visibility trial has additional unresolved typed firing-provider names before diagnostic resolution; its raw positional count is not a closeness gain. The scope trials emit fewer bytes and have more differences in every alignment class, so they are rejected. All before and trial objects were freshly compiled through align_diff.py with BFME_OBJSTORE=off; each trial has its own source path and the harness also removes the object and dependency receipt.

## Identity and provenance

Native 0x006CE307 RET 8 precedes the entry at 0x006CE30A; the target ends in RET 0x24 at 0x006CE6C2 before the next wrapper at 0x006CE6C5. WorldBuilder 0x00BB7C40 identifies privateFireWeapon with the same nine stack words and linear/scatter branches. Native 0x006CE497 supplies the helper's ECX vector, EAX index, EDI object and ESI result. The fresh raw retail/WB disassembly is build/worker-002ce30a-lifetimes/retail.log. Existing byte-verified provider rows establish the callees and six-float bonus layout. The old range-predicate identity remains refuted.

Donor semantic facts remain as documented in reverse/attempt_support/002ce30a-real-caller.md and reverse/attempt_support/002cb594-return-value.md. This pass reads the existing matched BFME2 providers rather than importing new donor code. The constructor/clear spelling follows the GeneralsMD Weapon.h donor; its six-field target adaptation is independently supported by native and existing provider bytes. Both banks, including every historical comment, remain unchanged. The current opt-in Coord3DDerivedView.h already supplies the helper's proven constructor/copy/destructor view, so a future exact landing can use it without editing the canonical POD header. Existing wrapper signature reconciliation is still required when landing.

## Raw evidence and checks

All new trial sources, preparation/probe scripts and raw logs are retained under build/worker-002ce30a-lifetimes. Each table trial has a matching -align.log, -bytes.log and -run.log. before-align.log and before-bytes.log reproduce the bank. providers-correct-extent.log verifies every full provider extent; providers.log preserves the initial wrong size hint for the append helper. prior-verdicts.log captures all previous target/helper verdicts. dest.log records the approved destination. timing.json records elapsed time from an external clock receipt. STOP_WORKER was absent at each new experiment. No background jobs were started.

check-csv.log and pin-consistency.log pass, with exit receipts beside them. banks-unchanged.log and its exit receipt prove both banks unchanged. No add_match.py, build.sh or find_declared_unmatched.py landing gate was run because no exact production source exists. The blocked verdict is written only through re_log.py and its raw output is record.log.

Elapsed at verdict: 8.30 measured minutes. No further justified experiment was identified after these negative tests. Repeating these visibility, constructor and scope trials without new evidence is not useful.
