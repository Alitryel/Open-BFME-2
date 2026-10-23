# TeamFactory constructor contract repair

Reuse TeamFactoryDtor.cpp's retail-supported eleven-slot SubsystemInterface
contract and TeamFactory init/reset/update overrides in the constructor view.
The native primary table is 0x0081AE2C, with init/reset/update slots documented
by the matched destructor unit. Object fields and body remain unchanged.
Declare the POD tree destructor specialization so this final family caller
uses the shared provider selected by the preceding repair.

The paired previews overlay all four POD-map family units against census
b73720bed9. Before: three units / 1,201 bytes. After: four units / 1,320 bytes.
The incremental improvement is 119 bytes (109-byte constructor and 10-byte
EH handler), not the preceding repair's 1,201 bytes. Both rows byte-match;
strict self preparation, new-variant, frozen-definition and CSV checks pass.
This is a legacy preview gain with self-strict receipts, not closed-strict
or a completed full link/census measurement.

Remaining identity debt: the allocator base's kept 36-byte copy at the old
0x0023E863 pin matches masked bytes but cannot certify its alloc-proxy call
at 0x0014F3C4: that symbol has no known address. The shadow classifier changed
from divergent to wrong/unknown when the conflicting 33-byte copy disappeared.
No new pin, fold assertion or baseline waiver is introduced. Existing divergent
helper definitions and _M_create_node extent findings also remain. These
limitations prevent claiming full identity closure for this family.
