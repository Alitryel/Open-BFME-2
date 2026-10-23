# Portrait resolver canonical string repair

Seat2, gpt-6.1-sol, 2026-10-23. Worktree t3-7faf7255, base
b16afa9926cef309a5ecbb9e72d968f3f2bc68d9. Source:
Code/GameEngine/Source/GameLogic/Thing/Rva0033BA46Finish.cpp.
Whole TU has one matched body: ThingTemplate::rva0033BA46 at RVA0x0033BA46,
190 bytes. Existing recovery and legacy link credit only; zero new coverage.
Fresh origin80503e264a source blob matched this base before edits. File/body
claimed as sol-team-supply-20261023; retained for parent publication.

## Evidence and hypothesis

Prior attempts at this RVA concern the original portrait recovery (189/190B
and call-order/register differences), not this canonical-header repair. The
source retained a stale claim that canonical str() checks string length. Current
reference/shims/bfme2_ascii/ascii_string.h::str() instead checks only its pointer
and selects pointer+8 or the empty literal, exactly the private strOf operation.
Its canonical StringBase<char> isEmpty declaration binds real0x00001E2F and
its clear inline calls releaseBuffer0x00036410. Both are the witnessed native
call identities. The established canonical view explicitly permits the same
StringBase pointer view used by its own operations; no new class/layout or
storage bridge is introduced. AsciiString remains its canonical4-byte record.

Retail body independently read through retail_body.disasm: calls1E2F before
findImageByName2D92F6, checks debug387C0 and records38790, invokes CrashBegin
virtual+6C before either string select, streams virtual+38, CrashDone+4C,
then releaseBuffer36410. Name and portrait strings remain ThingTemplate+64/+74;
image pointer+488. Manager datumDFF078 and debuggerDE0880 unchanged. Empty
literalBBAC1C and message literalsC10528/C10508 match. Complete relocation
symbols/addresses are in relocations.json (strict cached read-only resolution,
not a compiler invocation). Target native behavior is independent of the donor.

Read-only donor pin138757e9b74645fbcbb7724a7af2764e34931e11 still contains
ThingTemplateResolveNames.cpp:97-102: portrait name lookup followed by clear.
This supports purpose only; BFME2 debug order/layout are target-proven. Parent
uses newer96c88c73 and must reverify, not inherit donor currency from this run.

## Change

Remove private StringBase/AsciiString definitions and class-gate allowance;
include existing canonical header by relative path, with no compiler flag edits.
Existing strOf delegates canonical str(). The condition and cleanup use the
canonical StringBase<char> view so the real out-of-line isEmpty and native
releaseBuffer remain the callees rather than substituting the different
AsciiString isEmpty/clear APIs. Delete precisely one AsciiString class_gate_allow
entry from hatch_baseline.tsv. No aliases, pins, wrappers, shared-header changes,
new-TU prerequisites, tool edits or ledger/provider identity changes.

## Verification

- Original baseline normal build.sh:1/1 (190B),2 literals+1 empty-string refs.
- Canonical trial normal build.sh:1/1 (190B),same references, no warnings/crash.
- Scoped --prepare-current:1 strict reusable receipt, same full gates pass.
- Cached strict relocation resolution: whole190B exact, no unresolved or masked
  relocation, all native call/data identities listed in relocations.json.
- EH verification:0 rows with EH,0 nonexact,0 missing objects. Body is EH-free;
  this is not a claim of an unmeasured EH graph being exact.
- find_declared_unmatched:all defined functions already matched.
- class_gate:exit0 without the private allowance.
- Supported default link preview exit0:LINKS; legacy index456ce161c5 from
  2026-10-23 06:28 reports189->189 bytes, reflecting its historical189B extent.
  Current native/ledger strict extent is190B. No new-byte gain, no current-ledger
  or global unresolved-closure proof is inferred from that legacy preview.
- Parent will reverify newer donor and supported scoped current proof.

Compiler ran only via normal build.sh under approved own build/orbstack/env.sh,
BFME_ORBSTACK_COMPILE_GRANTED=t3-7faf7255,BUILD_POOL=1,BFME_OBJSTORE=off.
Last guest job988963b4dc8f42df8aefa719995ceff2 produced own-worktree match object;
readonly mount/output guard unchanged, no forced include or runtime edits.
Patch-engine context failures changed no source; one intermediate verification
reused original object and is not counted as a canonical trial. Claim accepted
before trials; its automatic settlement later timed out300s in incidental
recursive donor fetch (no checkout/update). Parent approved nonrecursive
command-scoped git parameters for future sequential claim operations.
