# LivingWorld tally and picker comparison link repair

At base `a0bb54ecd9595d3003b3036d39b76f503c281457`, repair the single consumer
`Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva0059DA34.cpp`.
The file contains the tally at 0x0059DA34 and picker at 0x0059DB48, their two
EH handlers, and the parent-proven cleanup funclet. No ledger, pin, shared
header, compiler option, class layout or external ABI changes.

A TU-local typed tree-iterator inequality compares the same node pointers as
the library base helper. An inline dllimport specialization retains the integer
comparison while avoiding a conflicting external `less<int>` definition.
These remove two unreferenced external COMDAT definitions. All 69 retained
COMDAT byte strings, extents and relocation digests are identical. The only
other nondebug section changes are three unreferenced, 12-byte local iterator
comparisons. All other normalized sections, external bindings, directives and
data facts are identical; object-proof.json records the complete comparison.
This establishes the compiler effect locally, without inferring new identities.

## Measurement

The paired check uses independent copies of the same frozen index, refreshed
with only the old or new consumer object. Index SHA256:
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
Its update receipt is commit `19a2565407`, 2026-10-15 09:33, clean tree;
underlying census `5986a99448`, 2026-10-15 04:52. Discovery's committed
link_status.csv came from `28269d8e8d`; it is not a fresh measurement of this
change. Neither index nor status nor census was rewritten.

Local findings decrease **6 to 4**, exactly removing iterator inequality's
first-copy conflict and the retail-wrong `less<int>` conflict. All other finding
collections are identical. The measured consumer has 798 unique nonpadding
bytes. Legacy LINKED remains **0 to 0**. New authored C++ bytes: **0**.
Strict compile receipts establish current objects and byte verification;
self-strict and closed-strict placement gains were not measured or claimed.
No full link cycle or census was run.

Remaining findings are two unresolved providers in this older index and the
retail-wrong vector<BfmeE8> overflow copy plus wrong selected provider. The two
callee bodies now exist in the ledger as LivingWorldAIHasUnitToFightType.cpp
(0x0050010D) and LivingWorldAIGetUnitToFightType.cpp (0x0050024C); index freshness
must be resolved before interpreting them as absent providers. The canonical
overflow body at 0x00057C80 lives in stlport_vector_e8_allocate_copy.cpp; a correct
body there does not displace every conflicting copy in the existing link order.

## Acceptance

- link_check.py --prepare: 5/5 byte rows with strict reusable receipts.
- ./build.sh on the consumer: 5/5, string/float/import checks pass. The funclet
  label renumbering is verified through its parent EH record.
- eh_verify.py: 2 EXACT, zero baseline exceptions.
- data_check.py --enforce: zero findings; --converged: eight addresses, zero
  second names. Paired object data facts/findings identical.
- link_check.py: expected exit 1, exactly four remaining findings. Paired
  link-proof.py asserts these are the original findings minus the two repairs.
- link_check.py --new-variants, class_gate.py, find_declared_unmatched.py and
  git diff --check pass. place_bodies.py reports zero new bodies or pins.
- check_csv.py passed at session start; hooks recheck the committed change.

Proof scripts are saved evidence, not new production tools. They read the
private prechange object under build/tally-tree-link-20261015/0, the current
object and the frozen local index; JSON records preserve their results without
committing object files. Run scripts from the repository root, in object,
link, data order while those inputs remain available.

## Reverted overflow trial and donor review

A declaration-only vector<BfmeE8> overflow specialization retained all five
matched rows but changed its external push_back from 55 to 64 bytes, producing
a new retail-wrong variant; selected overflow remained wrong. The two-source
check included the existing canonical overflow provider. The trial was fully
reverted; prepare-growth-trial.txt and link-growth.txt record it. A successful
new-variants check alone did not establish acceptance, so the full local link
check and object comparison controlled the decision. Future repair needs a
supported shared vector dependency reconciliation, not this declaration alone.

Reviewed official BFME1 master `37b26691e`, including commit
`66b19a8e95a4add525ef808fcea088e306798e2b`: suppressing an incidental external
helper while retaining inlining is applicable, with local target verification.
Existing BFME2 FormationPreviewPoolLookup.cpp and Rva0059D7C4ArmyTally.cpp
support the typed-iterator pattern. No donor layout or address was imported.
The verified BFME1 checkout remains `a7c38d3b2597121f178ab5190b3062478823257d`;
its scope is claimed by another worker and the documented old/new baseline
verification blockers remain. Fetch/review did not advance that pointer or
mark the stale freshness stamp successful. Prior audio iterator attempts with
unparented funclet false rejects were not retried.
