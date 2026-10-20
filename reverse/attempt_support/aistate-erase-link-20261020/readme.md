# AIStateMachine range-erase binding

At c7eaca2ec9, AIStateMachineUpdate.cpp passes its four byte rows but
link_check reports clear's COMDAT and selected definition as non-retail.
The clear row at 00352B41/92 calls range erase at RVA 002A133B (relocation
site 00352B64), as its existing pin notes record. The source instead calls
vector<Coord3D>::erase, whose ledger owner is the distinct 00081A24/38 body
in this same unit. The old pin therefore cannot establish a correct link
binding. The row at 002A133B/38 already has the Gen_p12pod erase name.

Follow the existing Coord3DVectorResizeValue.cpp binding pattern: pass the
unchanged three-pointer vector view and the unchanged begin/end pointers
to the rowed Gen_p12pod erase specialization. The 12-byte element stride
and call target are retail facts; the Gen_p12pod spelling remains an opaque
view, not a recovered application record. Retain the separately rowed
Coord3D erase with an explicit instantiation. No flags, pins, row extents,
ABI, aliases or data definitions change.

Checks:

- Before: current link_check, 0 -> 0 bytes, clear COMDAT/selected blockers.
- After: ./build.sh 4/4 rows; string/float/import checks pass.
- After: link_check consumer and unchanged Rva007D85C0FilterShutdown.cpp
  provider: both clean, 143 -> 473 B total; consumer 0 -> 330 B.
- Scoped strict reusable receipts: 6/6 rows across consumer and provider.
- find_declared_unmatched: all definitions already matched.

The gain is a legacy local prediction against the b73720bed9 published
census from 2026-10-20 05:34, not self-strict placement or closed-strict
link measurement. The recorded rank's other two dependents of clear,
JetAIUpdate and HackInternetAIUpdate, have many independent unresolved
and class-view blockers; no additional whole-unit gain is claimed.
