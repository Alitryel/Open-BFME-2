# Shroud finite independent review

Target `?onComingOutOfShroud@Drawable@@AAEXXZ`, RVA 0x0027893E,
747 bytes through RET (end 0x00278C29). Read current AGENTS.md, all 12
attempt-log entries, both existing shroud handoffs and full bank before work.
WB 0xCA3700 and the complete verified 214-byte nearest-object producer were
also read. Assignment was a finite fresh review; no Code, bank, ledger, pin,
index, commit or publication change was made.

Inputs: BFME2 886b6b1a5a / bank from 50b6f372cc; verified BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790. Parent flags remain
O1/G7/SSE/MD/EHsc, Ob1/d2inlS100, static target STLport 4.5. The whole-owner
ABI controls use the prior proven Ob2/d2inlS100 context.

## New negative results

1. Declare the four REAL live pointers (template, object, holder, local player)
   at function entry without initialization, preserving the original assignment
   statements and their order. All 24 declaration permutations compile to
   exactly the same raw 740-byte parent as the baseline. No unused diagnostic
   locals, volatile, equal-arm conditions or artificial operations were added.
   This closes the suggested changed-input live-declaration-order hypothesis.
2. Replace the nearest-object helper's artificial Drawable member receiver with
   an explicit Object pointer in ECX: both a free `__fastcall` function and a
   static member `__fastcall` function. Preserve the actual whole filter-chain
   body, with position at Object+0x38 independently proven by native accesses;
   retain existing uncertain helper names as views. **Both complete producers
   reproduce all 214 bytes at 0x00272AD5**, including cleanup/EH. Their parents
   are nevertheless the same raw 740 bytes as the baseline. The normal parent
   mismatch CLI reports the new trial-only helper name unresolved, as expected;
   no trial name was pinned, aliased or published. Thus the explicit argument
   versus member `this` representation does not explain the parent mismatch.
   A free `__thiscall` function is refused by MSVC (C4234) and is not a candidate.

All 27 successfully compiled parent controls have raw SHA256
`1e686f97ee55fdf82d36e884acccd48587fb8a4a36def42d7bfc4ee836f388d7`.
They each have 39 COFF relocations. Equality here excludes changes in relocation
symbol names: the ABI controls use different trial callee names. It proves that
neither new hypothesis alters the allocator or emitted parent instructions;
it is not a byte-match result.

## Remaining mismatch and resumption

The original clean 740-byte bank is preserved. Fresh align_diff reproduces two
structural regions: native stores the context event from EDX at +0xE6 and reloads
template from its -0x14 home at +0x10A; ours omits those instructions because
it keeps the template in EDI. Holder uses EBX in ours versus EDI in retail,
with the associated template/event loads and kind-7 test differences described
in drawable-shroud-bitset-20261020.md. No new exact candidate or C++ bytes.

Normal compile CLI only; no build.compile_source invocation, stand-in producer,
fake pin or shared cache mutation outside the CLI. Results and full logs:
`build/shroud-finite-review-oct20/{results.json,abi-results.json,hashes.json}`.
Replay drivers: `build/shroud-finite-review-oct20.py` (baseline + 24 real-live
declaration permutations), `build/shroud-finite-abi-oct20.py` (whole producer ABI
controls, based on the previous whole-owner replay). Compiler-correct static
name is `?NearestEnemyInView@Drawable@@SIPAVObject@@PAV2@@Z`; its explicit normal
CLI rerun was exact. About five minutes, gpt-6.1-sol.

Remote claim owner `codex-01a1071d-shroud-finite-oct20` acquired 0x0027893E
before trials and released after this nonmatching finite review. Root retains
control of the shared attempt log and can batch this handoff with current work.
