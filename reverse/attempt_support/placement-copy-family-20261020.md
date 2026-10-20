# Distinct placement-copy family owners

The verified typed-owner repair in c19900ef50 applies to the same established
placement-copy pattern in stlport_construct_game_structs.cpp. Thirteen legacy
dup rows borrowed three template object names that already had other owners.
Their real native bodies are separate, null-guarded, 45-byte placement-copy
operations calling the existing rowed constructors. Replace each alias with
an actual typed, address-derived C++ function performing that operation.

The original application names and record identities remain unknown. Existing
opaque record interfaces and caller ABI views are inherited evidence, not new
layout or template-identity claims. In particular, IntIntValue in the size-built
map unit remains an inherited eight-byte source view; the caller's exact native
callee edge, rather than the view's guessed application meaning, is the basis
for its typed binding.

Isolated trials copy the source's actual effective compiler flags and include
dependencies. Every whole 45-byte body and full associated EH graph is EXACT.
After applying, the provider and four direct callers pass all 67 existing rows
with strict current-object receipts. No shared header or compiler flag changes.
The callers now declare the actual typed owners and call them directly, removing
four obsolete synthetic pins and the linker alias that selected another body.

Ten existing compiler cleanup rows are rebound through their complete native
parent EH graphs. A borrowed template parent spelling is resolved by the actual
cleanup address in that graph, never by instruction similarity or adjacency.
Seven legacy object-symbol cleanup aliases become genuine compiler-local labels
with explicit, proven parent ownership. These cleanup bytes were already covered.

| Native copy owner | Natural handler | Previously owned handler |
| --- | --- | --- |
| 0023FC3E | 007711B4 | yes |
| 0026061A | 00772CF4 | no |
| 000BBA47 | 00761BF4 | yes |
| 000CF4D6 | 0076278E | no |
| 000D0469 | 0076288D | no |
| 002889E4 | 00774218 | yes |
| 002927CB | 00774518 | no |
| 0029FB9C | 00774DC7 | yes |
| 002A8C17 | 00775789 | no |
| 00382BC3 | 0077F55B | yes |
| 004634DC | 0078AA86 | yes |
| 0048C81F | 0078C680 | no |
| 003814A6 | 0077F375 | no |

Native parent handler relocations and exact EH graphs establish all thirteen
relationships. The six already-owned handler addresses keep their existing
rows and names; no second owner or fold pin is added. Each of the seven newly
banked ten-byte compiler handlers loads its own retail FuncInfo and jumps to
CxxFrameHandler at 00629182. Whole handler code and relocation bytes agree with
retail in strict current objects. No assembly, emitted-byte scaffold, new pin,
object alias or verifier exception is used.

Result: 70 newly covered retail bytes; 20 object aliases, four obsolete pins,
and one linker alias removed. Eighteen existing register entries are deleted;
the seven removed cleanup aliases had no register entries. No entry is added. Normal
whole-unit byte, identity, dependency and EH gates remain required. No census
or full-link gain is claimed.
