# AI command parameter lifetime ownership

The ranked linking queue served
`Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceAttackCommands.cpp`.
The complete file has 65 existing matched rows and 55 exact parent EH graphs.
Its current link preview is clean (5,922 source bytes); the older census entry
is not evidence of a remaining local link defect.

## Destructor and providers

`AICommandParms::~AICommandParms` at `0x001E7E9F` is the complete 15-byte
destructor emitted by the real command parameter object. It tests the coordinate
buffer at offset `0x20` and releases it through `_free` at `0x00030830`.
The normal byte gate and `explain_mismatch` prove all 15 bytes, the actual
emitted extent, and the resolved call. The free provider is the existing
17-byte game-memory wrapper. The existing parameter constructor at
`0x00351BD0` is 120 bytes and is checked with its own source.

The destructor's former `gen-alias;object-symbol=` notes describe neither a
different emitted symbol nor a second address owner. Replacing them with this
direct source attribution removes obsolete escape-hatch metadata. No symbol
pin, provider name, class view, or source body changes.

## Compiler-generated cleanup bodies

Each body below is exactly 11 bytes: `lea ecx,[ebp-0xCC]` followed by a tail jump
to the complete destructor at `0x001E7E9F`. The next entry is its existing
10-byte EH handler. Complete native parent EH graphs establish both the frame
slot and cleanup address; neither adjacency nor masked-byte similarity supplies
ownership. Multiple exact parents sometimes share one native action. Only one
row is retained per address.

| Native cleanup | Emitted label | Representative exact parent | Exact parents sharing action |
|---|---|---|---:|
| `0x0076A114` | `$L1075` | `AICommandInterface::aiIdle` | 1 |
| `0x00772F01` | `$L1164` | `AICommandInterface::rva0026C3AC` | 5 |
| `0x00774658` | `$L1128` | `AICommandInterface::aiAttackPosition` | 1 |
| `0x00775AE3` | `$L1368` | `AICommandInterface::aiEvacuate` | 2 |
| `0x0077E69B` | `$L1104` | `AICommandInterface::aiForceAttackObject` | 33 |
| `0x0077E838` | `$L1669` | `AICommandInterface::rva0037379B` | 1 |
| `0x007830EA` | `$L1140` | `AICommandInterface::aiFacePosition` | 8 |
| `0x00789B24` | `$L1392` | `AICommandInterface::rva0045003E` | 3 |
| `0x0078B192` | `$L1284` | `AICommandInterface::aiBfmeObjectCommand3D` | 1 |

These rows replace anonymous `uw_` harness ownership through the supported
`add_match.py --replace-rva` path. The generated source is not hand-edited.
Explicit `gen-funclet;parent=` notes bind each compiler-local label to its exact
same-source parent, and the ordinary admission gate verifies the whole file.
This restores real C++ lifetime ownership of 99 already-exact bytes; it does
not add 99 bytes of unique exact coverage.

## Provenance and checks

The source already records the BFME 1 / Zero Hour command semantics and each
target command ID, field offset and caller relationship. This change introduces
no new class-identity claim. Native EH metadata, exact parent bodies and exact
destructor bytes establish the cleanup identities independently of donor names.

Read-only receipts are under `build/next-batch-oct19c/`: `ai-build.txt`,
`ai-eh.json`, `ai-cleanups.json`, `ai-dtor.txt`, `ai-providers.txt`, and
`ai-link.txt`. Each ownership change is admitted and committed separately
through normal hooks. No runtime or fresh census result is claimed.
