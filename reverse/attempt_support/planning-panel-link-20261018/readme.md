# Planning-panel interface linkage, 2026-10-18

Against published retail-truth-2 census c2c5ac8c27 (2026-10-18 11:36), paired
current-object checks of Rva005CDVirtualDtors.cpp and Rva005CDCEEConstructor.cpp
change 1/2 clean units, 572 linked bytes, to 2/2 and 754 bytes: **+182 legacy
LINKED bytes**. The constructor's matched 218 ledger bytes include EH/funclet
rows that the link metric excludes. No authored-byte or closed-strict gain.

The destructor unit's Rva005F64F5 private view omitted its already recovered
ArmyDetailsMovieClip base and thus the two inherited callback slots. Reuse the
same base declaration already present in this unit, replacing opaque storage
at +4 with its real Impl member and retaining the owned member at +8. This
aligns the derived Rva005CDCEE vtable with the constructor's three-slot view.
The same base relationship and layout are independently established in
Rva005F6806Ctor.cpp, MemberBaseDtorsB01.cpp and Rva005CDCEEConstructor.cpp.
Callbacks are the existing verified empty hooks at RVA 000B3FD0; no pin added.

Acceptance: build.sh 20/20 rows exact across provider and consumer, including
renumbered funclets recovered through their parent EH graphs. EH verify 4/4
EXACT. Explicit provider prepare-current passes byte gates with strict reusable
receipts. Class/frozen/converged ownership/diff checks pass. Data enforcement
reports one pre-existing wrong-name for the Rva005E54F7/Rva005E3AE1 vbtable
at RVA 00874EFC: rebuilding the original source reports the identical finding.
The shadow identity check also reports the existing root deleting-destructor
divergence; its declaration and inline implementation are unchanged. Six-unit peer
preview preserves all previously linked bytes (2351 ->2533); the existing
Rva005E4F6DConstructor.cpp deleting-wrapper blocker remains, with no new blocker.

BFME1 review and freshness ownership are documented in the preceding
camera-overlap repair. This target-specific interface repair uses existing
BFME2 retail/constructor/destructor evidence, not a donor name assumption.
The accompanying timer attempt was restored after two failed selective-import
trials and is recorded separately; it adds no linked bytes.
